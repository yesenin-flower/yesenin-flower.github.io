[TOC]

# Linux 操作系统

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h4zskvesnsj20mc0kg0uj.jpg)

## 进程管理

进程是处于执行期的程序及其资源的总称.

线程(thread)是进程中活动的对象.linux并没有特别的调度算法或者数据结构来表示线程.线程被视为一个和其他进程共享资源(地址空间,系统资源,文件描述符,信号处理程序)的进程

每个线程有独立的程序计数器,进程栈,和进程寄存器.

内核调度的对象是线程.

内核讲进程列表存在任务队列(task list)的双向循环链表中.链表中的每一项类型都是**task_struct**的结构体(进程描述符process descriptor), 包括打开的文件,地址空间,挂起信号,状态等.

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h4vadbfjmrj20ju0f8wfm.jpg)

linux进程都继承PID=1的init进程.进程的关系都写在task_struct里,包含一个父进程指针,和子进程链表.

linux使用slab动态生成task_struct,并在栈底(对于向下增长的栈来说)或栈顶(向上增长的栈)创建一个新的结构 thread_info.相当于该进程的内核尾端存着**thread_info**,指向task_struct的地址

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h4vak5zwm5j20lw0hk3zs.jpg)

### 进程状态

创建进程fork()(kernel/fork.c),调用clone,再调用do_fork(),再调用copy_process():

1. 调用dup_task_struct()创建内核栈,thread_info,thread_struct,此时描述符内容完全等于父进程
2. 子进程开始修改描述符,状态为task_uninterruptiable
3. copy_process()调用copy_flags()更新task_struct的flags(用户权限等)
4. assign一个有效的pid
5. 文件信息,信号处理函数等
6. 返回指向子进程的指针

进程结束调用exec().最后调用do_exit()(kernel/exit.c):

1. tast_struct的标识位改成PF_EXITING
2. 调用del_timer_sync删除内核定时器
3. 释放mm_struct
4. 离开进程队列
5. 递减文件描述符、系统文件数据引用计数
6. 像父进程发信号,给自己找个养父(其他进程/init),并把进程状态改为EXIT_ZOMBIE
7. 调用schedule()切换到新进程.处于EXIT_ZOMBIE不会被调用,do_exit永不返回,此时占用的内容就是内核栈,info和struct结构
8. 等父进程确定无用了以后,才释放所有内存release_task()

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h4vavgz6t5j20u00kwq4t.jpg)

### 进程调度

抢占式多任务(preemptive multitasking):调度程序决定什么时候停止一个进程的运行,让其他进程执行.单个进程能持续运行时间被预设好(**时间片timeslice**)

非抢占式多任务(cooperative multitasking):除非进程主动停止/让步(yielding),否则一直执行

### Linux策略

I/O消耗型:等待I/O请求,每次运行只是短短一会儿;为了保证交互,linux倾向于优先调用

处理器耗费型:大部分执行代码

#### 进程优先级

优先级高时间片长;时间片未用尽, 且优先级高先调用

Linux采用俩种优先级范围:

1. nice值,[-20,+19],默认为0,值越大,优先级越低
2. **实时优先级**,[0,99],越高优先级越高.任何实时进程的优先级都高于普通进程

#### 完全公平调度CFS

允许美国进程运行一段时间,循环轮转,选择运行最少的进程作为下一个进程.

在所有可运行进程总数基础上计算出一个进程应该运行多久,而不是靠nice来计算时间片.

nice值在CFS中被作为进程获得的处理器运行比的**权重**,任何进程所获得的**CPU时间**由它和其他所有可运行进程nice值的相对差决定.nice值对应的是CPU的使用比

每个进程运行时获得的时间片底线,默认1ms.以避免大量的进程切换

#### 实时调度

Linux提供俩种实时调度策略(kernel/sched_rt.c):SCHED_FIFO和SCHED_RR.普通的调度策略是SCHED_NORMAL

SCHED_FIFO 先入先出调度算法.处于SCHED_FIFO 的进程会比所有的SCHED_NORMAL进程先调度.一旦执行就不会停止,直到自己受阻塞或释放处理器为止;只有更高优先级的SCHED_FIFO和SCHED_RR才能抢占

SCHED_RR类似SCHED_FIFO , 但SCHED_RR的进程在用尽实现分配的时间后就不能再继续执行了,是一种有时间片的SCHED_FIFO 

#### 调度器类scheduler classes

可动态添加多个调度算法(base 在kernel/sched.c),每个调度器有一个优先级,会按照优先级顺序遍历调度类(公平调用,实时调用),然后去选择下面要执行的程序.

进程运行的时间记账(linux/sched.h  struct_sched_entity)追踪进程运行记账,保存在进程描述符中task_struct.

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h4vk4gaz8ej20pm0d8q3t.jpg)

进程的虚拟运行时间(通过计算所有可运行进程总数)放在vruntime(kernel/sched_fair.c),记录了一个程序到底运行了多长时间以及还应该运行多久

CFS使用红黑树组织可运行进程队列,每次找到vruntime最小的进程

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h4vkan5lfsj20mo0ewmyi.jpg)

用户抢占发生在:1)从系统调用返回用户空间时;2)从中断处理程序返回用户空间中

内核只要没有锁就可以直接抢占.每个thread_info引入preempt_count计数器,有锁+1,为0时就可以抢占

### 系统调用 

通过C库调用系统函数

应用程序应该先通知内核需要执行系统调用,切换到内核态

通过软中断(引发一个**异常**来促使系统切换到内核态)去执行异常处理程序;同时将**系统调用号**和**参数**存在寄存器传递给内核,这样系统调用可以得到数据

自己写的系统调用要放在kernel/下,比如sys.c,并加入到系统调用表中(entry.s),再把对应的系统调用号放到asm/unistd.h中

## 中断

不同中断有不同的中断处理程序(interrupt handler), 通过中断号(IRQ)区分

驱动程序可以通过request_irq()(linux/interrupt.h)函数注册一个中断处理程序

卸载驱动程序时,需要free_irq()释放中断线,如果该中断线上没有中断处理程序后,会被禁用

共享的中断处理程序request_irq()的参数flags必须设置IRQF_SHARED标志.内核接收到一个中断后,会依次调用该中断线上注册的所有处理程序

### bottom halves下半部

执行与中断处理密切相关但中断处理程序本身不执行的部分

### 软中断softirq

网络和SCSI两个子系统直接使用软中断, 内核定时器和tasklet建立在软中断上

当内核处理软中断,就会调用softirq_handler,参数时指向对应softirq_action结构体的指针

中断处理程序会在返回前标记它的软中断,然后在适合的时刻,软中断就会被执行

### tasklet

tasklet和软中断本质相似,行为表现相近,但接口更简单,锁保护要求较低

大多数情况下,为了控制一个寻常的硬件设备,tasklet是最佳选择.可以动态创建,使用方便

### 工作队列work queue

工作队列可以把工作推后,交给一个内核线程去执行

如果任务需要睡眠/重新调度,就选择工作队列

工作队列开销大,需要内核线程甚至上下文切换

## 内核同步

### 进程同步synchronization->race condition

用户空间可能会被调度程序抢占和重新调度;而新进程在操作共享内存时,就可能发生竞争

### 死锁

自死锁:线程试图获取一个已经持有的锁

n个线程n个锁,每个线程都持有一把其他进程需要得到的锁

如果对重要资源锁的太严重,就容易造成系统性能瓶颈;锁争用不明显时,加锁过细会加大系统开销,带来浪费

### spin lock自旋锁

自旋锁最多只能被一个可执行的线程持有,如果一个执行线程试图获得一个被已经持有的自旋锁,那么该线程就会一直循环等待(可以在中断中用),直到锁重新可用

### 信号量init_MUTEX

一种睡眠锁, 当任务试图获得一个不可用的信号量时,就会被推入等待队列,进入睡眠

### 互斥体mutex_lock

任何可以睡眠的强制互斥锁,任何时刻只有一个任务可以持有mutex

必须在同一个上下文中上锁和解锁

不能递归的上锁和解锁,持有锁时进程不能退出

mutex不能在中断或者下半部中使用

除非mutex某个约束妨碍使用,相比信号量优先选择mutex

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h503mctr30j210e086758.jpg)

### BKL 大内核锁lock_kernel

BKL保护代码(保护foo()函数的调用者进行同步),而不是保护数据(结构foo)

用得少了,也不鼓励使用

### 顺序锁DEFINE_SEQLOCK

用户读写共享数据.写入时加锁,序列计数器增加;读取数据之前和之后,序列号都会被读取;如果读取的序列号值相同(都是偶数),说明读操作时没有被写操作打断过.

## 内存管理

### 页struct page

内存用这个结构管理系统中所有的页,描述物理内存本身,并不包含其中的数据

定义在linux/mm_types.h. 

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h5056e2sbbj20fu098dg5.jpg)

flag存放页的状态(是不是脏的,是不是锁在内存中了,每一位是一个单独的状态,至少可以表示32种状态)

_count存放页的引用计数,等于-1时就可以重新分配.一个页可以由页缓存使用,或者作为私有数据,或者作为进程页表中的映射

virtual域是页的虚拟地址

alloc_pages()分配$2^{order}$个连续的物理页,并返回一个指针

free_pages释放页

### 区zone

内核将相似特性的页进行分区:

1. ZONE_DMA & ZONE_DMA32(32位设备访问):只能用特定的内存地址来执行DMA(直接访问内存)
2. ZONE_HIGHEM一些体系结构的内存的物理寻址范围比虚拟寻址范围大得多,这样就有一些内存不能永久地映射到内核空间. 使用alloc_pages进行分配,返回一个指向page结构的指针;通过kmap(),将高端内存映射到内核的逻辑地址空间.
3. ZONE_NORMAL能正常映射的页.如果不需要物理连续的的页使用vmalloc()来分配;否则使用kmalloc()

### Slab分配器

如果要创建和撤销很多大的数据结构,就考虑建立slab高速缓存,提高对象分配和回收的性能.它并不会分配和释放内存,而是把实现分配好的对象存在高速缓存,每次需要新内存就直接得到对象

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h506kn7eyij20oy0i4dgm.jpg)

通用数据结构缓存层:

1. 高速缓存(kmem_cache)被划分为slab,由一个或多个物理连续的页组成
2. 每个slab里有一些对象成员,即被缓存的数据结构:满(slabs_full)、部分满(slabs_partial)、空(slabs_empty).
3. 当内核需要一个新对象时,就先从部分满的slab中进行分配;然后找空的slab;如果没有空的,就创建一个新的slab

## 虚拟文件系统VFS

内核在底层文件系统接口上建立了一个抽象层,支持各种文件系统

VFS抽象层定义了所有文件系统都支持的、基本的、概念上的接口和数据结构;而文件系统也将“如何打开文件”,“目录是什么”等概念在形式上与VFS的定义保持一致

![](https://tva1.sinaimg.cn/large/e6c9d24egy1h50tc3ue43j20sg06awf0.jpg)

### Unix文件系统

unix使用了四种和文件系统相关的传统抽象概念:文件、目录项、索引节点和安装点(mount point)

所有文件都作为根文件系统树的枝叶保存;目录也属于普通文件,记录了其中所有的文件,所以也可以对目录执行和文件相同的操作

文件的元数据(访问权限,大小,owner,创建时间等信息)被存储在一个单独的数据结构中,该结构被称为索引节点(inode)

VFS有四个主要的对象类型:

1. 超级块对象,super_operations.存储特定文件系统的信息,通常对应于存放在磁盘特定扇区中的文件系统超级块或文件系统控制块
2. 索引节点对象,inode_operations.表示一个具体文件.
3. 目录项对象,dentry_operations.表示一个目录项,是路径的一个组成部分.
4. 文件对象,file_operations,表示由进程打开的文件.

## Linux 基础

### 基本command

1. 文件操作: vi; vim; ls; cd; ll; mkdir; rm -rf; cp -r; mv; 

   - **rmdir**; 

   - **touch**生成文件会修改时间; 
   - **stat**文件状态 inode, links; 
   - **ln** ori new 硬链接 直接指向inode 删除原来的文件ori, new还是能找到那个文件,因为inode没变,inode的links减1
   - **ln -s** ori new软链接 创建新inode,指向一个ori,删除原来的文件ori 就找不到对应inode了

2. 读取文件:

   - **cat** load文件到内存

   - **tac** 逆向load文件
   - **more less** 一页一页加载
   - head -4;
   - **tail**; 读取新增加的数据 tail -F/f; f监听inode;F监听文件名字
   - **find /etc -name lan*lan**

3. 用户权限

   - useradd luckyboy新增用户
   - passwd luckyboy设置密码
   - userdel -r luckyboy删除用户
   - usermod -l luckyss luckyls 修改用户名
   - usermod -L luckyss 锁定用户名 usermod -U luckyss 解锁用户名
   - su luckyboy 切换账户

4. 组权限

   - groupadd;groupdel
   - groupmod -n school lucky修改组名字
   - groups schoolboy查看用户对应的组
     - 当我们创建用户的时候，会默认创建一个同名的主组

   - 修改用户的组
     - usermod -g lucky schoolboy (主组)
     - usermod -G lucky schoolls (附属组)

5. **权限**

   - drw-r-xr-x 4 emma  staff 4096 Nov 13 00:30 apache-tomcat-7.0.61

   - 三组权限(所属用户user (u),所属组group (g),其他用户other (o))，每组3个字母

     - r :读取权限
     - w :写入权限 
     - x :执行权限 
     - -:没有权限

   - change owner: 

     - 文件所属

       - **chown** emma  fn
       - **chown** staff:emma fn
       - chown -R staff:emma dir
       - chgrp emma lucky

     - 文件权限

       - **chmod ugo+/-rwx** fn

       - 权限RWX分别对应数字 4 2 1; 5= 4+0+1 r-x

         chmod 664 lucky4 ->(rw- rw-r--)

6. 常见命令: 

   - whereis 命令位置
   - file 文件类型
   - who, whoami 在线用户
   - pwd绝对路径 
   - uname -a内核信息
   - history -c

7. **文件大小**

   - 分区信息 df -h
   - 指定文件目录大小 du -h --max-depth=1 /etc

8. 文件传输

   - **Window--Linux** xftp
   - **Linux--Linux** scp -r

6. **文件压缩** 
   - 解压缩  tar -zx(解压)v(过程)f(文件) lucky.tar.gz
   - 压缩      tar -zc(压缩)f(文件) lucky.tar.gz(压缩后的名字) lucky(源文件)
7. 进程信息
   - ps -ef:UID, PID当前进程编号, PPID当前进程编号的父进程编号,TIME CMD
   - ps -aux
   - ps -aux --sort -pcpu
   - top当前服务器内存使用率
   - jobs -l可以查看当前的后台进程,但是只有当前用户界面可以获取到
   - kill -9 17599

### Shell编程

1. |管道: 将前面命令的结果作为参数传递给后面的命令 
2. 后台运行+&
3. root 后台运行nohup ping www.baidu.com >> baidu 2>error &
4. ls /etc /abc >> lucky **2>1.txt** 错误信息写到1.txt
5. **cut 用指定的规则来切分文本**
   - cut -d ':' -f1,2,3 fn 用:切分文件,并取出前3列
6. **sort 排序** 
   - 对文本中的行进行排序 
     - sort fn
   - 对每一行的数据进行切分，按照第二列进行排序
     - sort -t ':' -k2 fn
   - 逆序
     - sort -t' ' -k2 -r fn
   - 按照数值大小进行排序,如果有字母，字母在前
     - sort -t' ' -k2 -n lucky
7. **wc 统计单词的数量**
   - -l行
   - -w word 以空格来分割单词
   - -c char
8. **grep 对文本内容进行搜索**
   - 同时搜索多个文件 grep keywords fn2 fn1
   - 显示匹配的行号 grep -n keywords fn2
   - 显示不匹配的忽略大小写 grep -nvi keywords fn2 
   - 正则匹配 grep -E "[1-9]+" fn1
9. **sed **从文件或管道中读取一行，处理一行，输出一行
   - 行的选择
     - [m, n]第m行到第n行
     - /u1/,/u4/-->从匹配u1到匹配u4的行
   - **option**
     - -i 直接修改到文件
     - -r 使用扩展正则表达式，默认情况sed只识别基本正则表达式*
   - 增
     - i 插入，在指定行前添加一行或多行文本*
     - a 追加，在指定行后添加一行或多行文本*
     - sed '2i luckyisgood' passwd
     - sed -i '2a luckyisgood' passwd
   - 删
     - sed '3,10d' passwd
   - 改
     - 整行替换
       - c 取代指定的行
       - sed '3,20c hahaha' passwd
       - sed '3~1c hehehe' passwd
     - 字符替换
       - 取代，s#old#new#g  ==>这里g是s命令的替代标志
       - sed '1,5 s/root/lucky/g' passwd 
       - sed '1,5 s#a#b#g' passwd
10. **awk**
11. shell 文件
    - 执行./a.sh; sh a.sh会新开一个bash 进程,而source a.sh直接执行不新开bash

```bash
#! /bin/bash
#参数传递 ./a.sh a b c
echo $0
echo $1

#变量声明
name=abc
echo $name
unset name

#单引号不取变量
name=abc
n2="hello, $name"
echo n2 # hello, abc
n1='hello, $name' 
echo n1 #'hello, $name'

#字符串长度
echo ${#n1} 

#数组
a=("a" "b" "c")
echo ${a[0]}
echo ${a[@]} #取所有数据  "a" "b" "c"
echo ${#a[@]} #取数组长度 3

a=10
b=20
#-eq -ne -gt -lt -ge -le
if [$a -eq $b  && $a != 0]
then
	echo "$a -eq $b"
elif [$a == 0]
then 
 	echo "0"
else
	echo "$a not eq $b"
fi

#``当命令执行
val=`expr $a + $b`
echo "a+b: $val"

#case 
case $a in 
	1) echo "1"
	;;
	2|3|4) echo "2"
	;;
	*) echo "others"
esac

#for
for loop in 1 2 3 4 5
do
	echo "a: $loop"
done

#while
while [$a -ne 0]
do
	let "a--"
done

#func
demo(){
	echo "a"
	echo $0
	echo $1
	echo ${11}
	read anum
	read bnum
	return $(($anum+$bnum))
}
demo 0 1 2 3 4 
#返回值通过$?获取
echo $0

:<<ABC
批量注释
ABC
```

### 文件系统:

1. 万事万物都是文件,进程文件 cd /proc
2. 硬盘挂载 mount /dev/disk1 /usr/download

3. bin可执行命令;boot系统启动的引导程序;dev设备信息;etc配置文件;home普通用户的家目录;lib库目录;mnt硬盘挂载的目录;opt软件安装的目录;proc进程信息;root家目录;run运行时的系统变量;sbin管理员可行性的权限和命令;srv/sys系统信息;tmp临时数据,关机清空;usr多个用户共享的程序;var变量不会被清空操作系统

### 网络相关命令

1. vi /etc/hosts 修改DNS
2. ifconfig 查看当前网卡的配置信息
3. netstat 查看当前网络的状态信息
   - netstat -anp 端口占用情况
   - netstat -r 核心路由表
4. ping
5. telnet 192.168.31.44 22 查看与目标IP的指定端口是否能够连通
6. curl -X GET http://www.baidu.com网页数据

### race condition

1. PC driver的race condition是well-modelled的  比如PCIE是最popular的接口  但是firmware还是最基本的MMIO

2. 关于hardware software交互，PCIE也有interrupt和DMA，但x86 外设少且fixed
3. 已有driver code的data race分析还是只停留在data上 最多考虑一下interrupt 应用在driver上,仅仅是因为driver发送race的概率大;pasan的peripheral的race 还是第一次提出,应该在pc的driver也有 但是估计pcie的driver已经测试的很好了 只剩下data的race了;具体方法 我perfer用under constrained symbolic execution 结合细粒度的peripheral transaction边界
4. 以前的driver race condition都是memory object;pasan mmio race的是firmware specific
5. MMIO:Memory map IO,将用户空间的一段内存区域映射到内核空间，映射成功后，用户对这段内存区域的修改可以直接反映到内核空间，同样，内核空间对这段区域的修改也直接反映用户空间

# **攻防基础**

### 虚拟机vmware, vsphere

寄生架构和原生架构

### 渗透测试流程

1. 信息收集: nslookup, whois(域名 子域名 邮箱)
2. 扫描漏洞:nmap(ip地址 端口 端口上的服务apache, IIS);高级扫描(版本信息, 版本漏洞);网站漏洞(SQL注入)
3. 漏洞利用;暴力破解(hydra, pwdump, saminside)
4. 拿到最高管理权 shell环境 桌面环境
5. 删日志,留后门

### 中间人攻击Man in the middle attacks

If communication protocols are not secured or attackers find a way to circumvent that security, they can steal data that is being transmitted, obtain user credentials and hijack their sessions.

Kali Linux is an open-source, Debian-based Linux distribution geared towards various information security tasks, such as Penetration Testing, Security Research, Computer Forensics and Reverse Engineering

1. Address Resolution Protocol (ARP) Poisoning attacks:host发ARP请求给router,得到ip的MAC地址.attacker伪装成target machine发送假的mac地址,再把假的router地址发给target machine.Machines usually automatically cache all ARP replies they receive.这样他就能接收到所有的通信
   - When an Internet Protocol (IP) datagram is sent from one host to another in a LAN, the destination IP address must be **resolved to a MAC address for transmission via the ETH layer**. To resolve the IP address, **an ARP request is sent out on the LAN to ask which MAC address matches the destination IP.** The destination host possessing this IP will respond with its MAC address in the ARP reply. **ARP is a stateless protocol.** Machines usually automatically cache all ARP replies they receive, regardless of whether they have requested them or not. Even ARP entries that have not yet expired will be overwritten when a new ARP reply packet is received. The host cannot verify where the ARP packets come from. By spoofing ARP responses, the attacker can trick the victim into falsified mappings between IP addresses and MAC addresses, and thus intervening the network communication. 

![img](https://lh3.googleusercontent.com/4iCXMRbiT_rZ3rL7P7cWdPt-tLP7BNiz215Hh5Y6rmafj4dkUMZqZGPp0gTTii_mdkPPYGLDsco6gKJVYSoNxzJfHuGdlRlnaL3THP1jxNUOLbejtJ54rpEQyxiXyCtWU1TwalAsX5ZpiF3tTg)

2. Domain Name System (DNS) Cache Poisoning attacks:

   - When a client program on a user machine refers to a domain name, the domain name needs to be translated to an IP address for network communication. The DNS servers are responsible to perform such translation.The user machine gets to know the IP address after receiving the responseHowever, the DNS server cannot verify the response at the second stage, and this is where the attacker can fool the local DNS server. Pretending as the global DNS server, the attacker can send a spoofed DNS response to the local DNS server with the falsified DNS record. As long as the fake response arrives earlier than the real one, the local DNS server will forward it to the user machine and save the falsified record to its cache

     ![img](https://lh3.googleusercontent.com/XluBgQkufAxiUf4avvvDGIJXTlLJXFn9FiQZHCbJqlPukiSZJZsX5FYCsEWTnv1ensTUcJPL7gsKvI97bzKH-a4pr8YAcvGMS4SwSl0Ei7xDwhAnjIlwmpkINv7iC4x-PPKhhHrJGiJUNKbx2Q)

### DNS欺骗与钓鱼

### 漏洞和木马

拷贝到目标主机 IPC$ 端口号445.

灰鸽子软件生成木马放到service里,自动启动

防御:利用防火墙,关闭端口

### 病毒

# **网络基础**

IP 地址:网络地址,主机地址 182.102.101.105

子网掩码(net mask):划分IP地址,判断两个IP是否在一个子网里 255.255.0.0

```
网络地址: 182.102.0.0
ip地址范围:182.102.0.1-182.102.255.254
广播地址:182.102.255.255 用于同时向网络中所有工作站进行发送的一个地址
```

默认网关gateway(182.102.101.1):消息转发DNS(域名解析)

局域网(内网):pc->交换机->路由器(网关x.x.x.1 or x.x.x.255)

内网环境:

​	1)工作组:人人平等,不方便管理

​	2)域:人人不平等,集中管理,统一管理

- 域控制器domain controller
- 成员机

# **加密算法,网络协议**

**不可逆加密算法** hash,md5

**对称加密算法** Symmetric Key Encryption 加密和解密使用相同的秘钥

**非对称加密算法** Asymmetric Key Encryption(**ssh 免密码登录**, HTTPS)

- 公开密钥(public key)与私有密钥(private key)生成时是一对	

- 公钥加密，对应的私钥解密，同理用私钥加密只能用对应的公钥解密

- TCP:

  - OSI 7层 TCP/UDP5层

    <img src="https://pic2.zhimg.com/v2-92f16468f88bb7bcdf1a8f1451805115_r.jpg" style="zoom:33%;" />

    <img src="/Users/emma/Work/blog/summary/九章/ip.png" alt="ip" style="zoom:33%;" />

- UDP:
  
  - no retransmission
  - not guarantee dilivery
  
- TLS: 
  
  1. encrypting the communication between web applications and servers
  2. a client connects to a TLS-enabled server requesting a secure connection
  3. server picks a cipher and hash function and notifies the client of the decision.
  4. The server sends the client its certificate and public key.The certificate contains the [server name](https://en.wikipedia.org/wiki/Hostname), the trusted [certificate authority](https://en.wikipedia.org/wiki/Certificate_authority) (CA), and the server's public encryption key.
  5. The client confirms the validity of the certificate before proceeding.
  6. The client encrypts a session (secret) key with the server’s public key, and sends it back to the server. 
  7. The server decrypts the client communication with its private key, and the session is established.
  8. The session key (symmetric encryption) is now used to encrypt and decrypt data transmitted between the client and server. 
  
- HTTP:
  1. [HTTPS](https://www.cloudflare.com/learning/ssl/what-is-https/) is an implementation of TLS encryption on top of the [HTTP](https://www.cloudflare.com/learning/ddos/glossary/hypertext-transfer-protocol-http/) protocol
  2. Open a TCP connection: syn, syn-ack,ack
  3. Send an HTTP message: method(get, post), path, header(host, lanuage) and content
  4. Read the response sent by the server, code(200 ok, 404)...
  5. Close or reuse the connection for further requests.
  6. Cache resource/ cookies. stateful information for the [stateless](https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview#http_is_stateless_but_not_sessionless) HTTP protocol.
  
- SSH:
  1. TCP connection
  2. Client sent Identification string exchange(ssh version/software version)
  3. Sever sent Identification string exchange(ssh version/software version)
  4. The client sent a key exchange message: list of supported algorithms
  5. The server sent a key exchange message: list of supported algorithms
  6. The server chose algorithm and the client agree
  7. The client sends public key to server
  8. The server use the public key and its own public key to calculate the secret key, and the hash code. And use its private key to sign the hash
  9. The server sent the hash, and its public key to the client and new keys(used for further message exchange)
  10. The clent first use server’s public keys to get the secret key. And calculate the hash
  11. The client verify the certicates, and check if the hash is the same
  12. The client generates new keys
  
- SMB: 
  1. Transfer file(printer)
  2. use TCP port 445 as the SMB port
  
- SMTP:
  1. Between two mail servers
  2. The client sent EHLO message the mail server 
  3. The server reply okay
  4. The client identify the sender
  5. Reply okay
  6. The client identify the recipient
  7. Reply okay
  8. The client ask for ready to sent message
  9. Reply okay
  10. Send content

![img](https://lh5.googleusercontent.com/WrIvfRj_ymzUSbHpEZ3bPNCwuuq4q7pXkpC_sJKG69k5FrK4eAYBcbvFb9z06NDckWbBNLXfywnfHG4MWCM4KFZI64xC_vmUDHrSjWc8B8jnAzQ1FwGG6rDOBTFi2M2ZjWHL_TmPDAsPI2GFPQ)![img](https://lh4.googleusercontent.com/Vz5DfTH8gUjW5vmFfL3UD4PHDM7wHBv8rGIV_TYYHmG38TBByH8-FKfuQwjN5r8LvzC0xcSYDHjWGt6xPmkM2yyYO2MXaUk-OTto1LB6ZPiuS7LcqqhFCnYcQta2uWXWhhdhgh7W-OstR6VgUQ)![img](https://lh3.googleusercontent.com/_tG-syH4ynMpplP7CUEW-q909FB9lLvgr6-7rE16nRGPZACZvATqLAeBWZ9tI7FEwq-JNFQykvFg1eQxpiMuN2rM0B-OOSTRKbCEbQFcjmJb6egVEZQMLCN-zIyB8UDiltJqjlKlCKsRw4ryng)![img](https://lh3.googleusercontent.com/S6Pu3e9k87h-_7ijy709cpyiDybHq-H1ugcUUtYC-IOsq24Ie1W83dpKrNSqHxt2uodxG7vTGCRRBDT4xleAqwdC_E-MZR0sEmuNE48c3CTObH61h1Jr8iIP1vNe4TpA-ood9VaWmXHO3YxUkg)

**ssh服务安全加强的建议（仅供参考，工作中根据需求来就好行）**

1、不要使用默认端口

2、禁止使用protocol version 1

3、限制可登录用户

4、设定空闲会话超时时长

5、利用防火墙设置ssh访问策略

6、仅监听特定的IP地址

7、基于口令认证时，使用强密码策略

tr -dc A-Za-z0-9_ 

8、使用基于密钥的认证

9、禁止使用空密码

10、禁止root用户直接登录

11、限制ssh的访问频度和并发在线数

12、做好日志，经常分析

13、锁死sshd服务的配置文件，防止篡改，修改锁文件命令