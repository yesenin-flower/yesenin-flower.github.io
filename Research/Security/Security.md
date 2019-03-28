#  Ryoan: A Distributed Sandbox for Untrusted Computation on Secret Data

##  问题

data-processing services中**sensitive info**, 有点像但解决思路完全不一样。文章是系统层面的解决方案，我们用的是加密，适用范围也比较小，解决距离相关的算法。文章应用范围更广。

##  以前的解决方法及缺陷：

外包SaaS 23andMe和amazon的合作：不能保证secret data

SGX: Intel Software Guard Extension. Intel指令集架构（ISA）的扩展，主要提供了一些指令用于创建一个可信执行环境（TEE）Enclave。**对于软件的保护并不是识别或者隔离系统中出现的恶意软件，而是将合法软件对于敏感数据（如加密密钥、密码、用户数据等）的操作封装在一个enclave中，使得恶意软件无法对这些数据进行访问**。用户态应用程序可以在Enclave中安全执行，而不被恶意的OS、hypervisor(VMM)所攻击。SGX的保护是针对应用程序的地址空间的。SGX利用处理器提供的指令，**在内存中划分处一部分区域（叫做EPC）**，并将应用程序地址空间中的Enclave映射到这部分内存区域。这部分内存区域是加密的，通过CPU中的内存控制单元进行加密和地址转化。**EPC中的内存内容只有当进入CPU package时，才会解密；返回EPC内存中会被加密。** 可以保证用户信任的程序不会通过side channels(边信道攻击:**隐密数据在程序运行发生错误并输出错误信息时被发现、使理应被删除的敏感数据被读取出来**)泄露数据 *Ryoan中程序和infrastructure不受用户控制，即使有Enclave protection，也可能存在covert channels(允许进程以危害系统安全策略的方式传输信息的通信信道:不同APP间数据通信不受控制)，所以要阻止app使用modulate events 如 系统调用 来和其它程序通信。*

**NaCl 作为沙盒的基础: 从浏览器直接运行程序机器代码**，独立于用户的操作系统之外，使Web应用程序可以用接近于机器代码运作的速度来运行，同时兼顾安全性 

##  论文方案：

**user和provider信任自己的代码和平台，信任Ryoan和SGX，不信任别人的。计算层不信任任何software。**Ryoan不保护计算层自己的secrets，不提供调度，保证software interface的covert channel，不保证hardare limitations 和execution time这种covert/side channel

支持written for libc的程序，不支持just in time compiler，程序是linux program or contain library operating system

![](https://ws4.sinaimg.cn/large/006tNc79ly1fvt6g8clj1j30kk0aat9w.jpg)

Ryoan 分布式sandbox环境:

1. 可信通信。可信硬件，远程认证用户信息
2. 防止数据泄漏
3. 控制module通信。**每个SGX enclave允许一个NaCl沙盒实例来执行modules(code, 初始data, 最大动态分配内存)。NaCl间通信（secure TLS connection）形成分布式沙盒。**

## Communicaiton

### topology

**module初始状态的hash作为一个indentity+public key/product indentifier/security version number作为一个indentity。**

**先要有DAG+init code给master，master建立instance。neighbors认证instance，通过key exchange来保护通信channel，topology建好后，建立entry and exit enclaves，就开始处理数据了。** master 方便但是不是必须的。

![](https://ws4.sinaimg.cn/large/006tNc79ly1fvt7gf13x0j315q09cn0r.jpg)

### labels

Ryoan提供simple label来保护数据，数据进入DAG以后，防止被不受信的modules操作。用户可以加user tag，module 有自己的tag。**user tag是user的 public key，用 private key标注module。一个用户可以有不同的key pair来分离程序。数据经过module Ryoan都会merge 他的tag，同一个key生成的module有权利去掉其tag，connect user的instance可以remove user tag。**

还有一个概念，**没有label，则module 没有受限，可以操作任何文件系统、通信、修改space；一旦有了tag，相当于see secret data就要防止leak data，符合request-oriented data model，只能读一次，之后不能读写persistent storage，不能再和untrusted OS通过syscall通讯**。

audit trail可以用来track modules。用户可以自己设计audit trail。

##  Leaking sensitive data

decoupling externally visible behaviors from content of secret data. 把操作和隐私数据分离开。 **限制使用unprotected memory（通过NaCl tool chain 和run time）和syscalls（只在NaCl里使用他们的func）如只能读写固定大小内存，不能访问address range外的内存，必须通过ryoan intervation接口来调用syscalls**

![](https://ws2.sinaimg.cn/large/006tNc79ly1fvtawreqt3j30ka09ytad.jpg)

### in-memory virtual file system

**module受限前必须preloaded file 放在内存。用POSIX-compatible APIs来使用这些files。confined module可以在enclave里创建临时文件，module销毁，这些文件也销毁，preloaded文件revert重置**。因为访问persistent files就可能存在ocvert channel的问题

### mmap

**动态内存分配，使用的是预先分配好的内存地址**。如果要大量的空间，一个module做不到，就要分块给几个module。

**Ryoan instance要check OS返回的结果。Ryoan-libc管理syscalls arguments并check return**。

**Ryoan-libc维护一个数据结构记录virtual memory area，在请求mapping check内存：untrusted code通过Ryoan-libc 请求kernel；kernal选一个enclave page frame，修改page table；user开始使用encave code；code通过EACCEPT认证mapping完成**

##  modules

**执行module前必须拿到所有数据，output size被pad or trunc 固定，output数据要输出给所有连接的module**

使用NaCl's load time code validator确保module‘s code满足strict format。module在NaCl的基础上+限制module可不包含SGX指令，code必须和init一样。

**生命周期：creation init wait process output destruction/reset。init时可以没有label，可以有一个non confining label。这样让creation更efficient。init结束就wait_for_work。处理完数据输出后，就destruction/reset，以防止累计secret data。request-oriented，input可以是任何size，但是必须是unit of work(one email/ a file).  creat和init很慢，又不能多次接收input，+checkpoint roll back to untainted**. 如果不reset一次batch多个文件，可能leak数据。

**因为OS不知道module完成处理了没，Fixed processing time**。少了就wait。执行特定的可预测的run times(比如决策树模型)。以后可以加参数确定执行时间。

如果user许可，可以使用RDRAND指令randomness。confined modules不能randomness。

One-shot policy**阻止module重复access数据：DAG无环；reset时删除所有数据；connection break就要重新初始化**。

![](https://ws2.sinaimg.cn/large/006tNc79ly1fvtf4i8ierj30j406odh0.jpg)

##  论文实验：

三个实验，一是比较不同应用的在五种方法下的时间，二是比较不同应用module在不同阶段的时间和内存，三是比较SGX指令消耗的时间。

![](https://ws1.sinaimg.cn/large/006tNc79ly1fvtfeiosr2j30lw0g8mzq.jpg)

![](https://ws1.sinaimg.cn/large/006tNc79ly1fvtfele4h5j30k60mgjws.jpg)

![](https://ws2.sinaimg.cn/large/006tNc79ly1fvtflnm7smj30k00e0jtq.jpg)

##  总结：

1. 文章没有以前的解决方案，baseline用的是native linux
2. 从实验来看效果好些很不错，但是实验有几个地方没想通，为什么用了checkpoint效果反而变差了，他说health的数据workload 1ms这样page fault的时间就很显著了，所以慢了，但每个checkpoint都有些于变慢了。checkpoint本来是提升效率的，creat和init很慢
3. 另外她说SGX的flush TLB的时间影响了他的性能。从第三个实验来看确实是指令消耗的时间变大了，可能还有其它的影响，比如fix time（pad to wait）带来的影响。因为每个module都是fix time，input又是 unit of work，health单个work的处理时间短，但数量大（health2w 而其它的是几十条几百条数据），直接影响了他的性能。这点再image里也可以体现出来，我觉得可以讨论一下排除指令影响后不同workloads对性能的影响。
4. 如果说这篇文章，我最感兴趣的点，是他提到的批处理那里。因为我感觉本身fix time fix input&output限制非常大，如果是单个文件进行工作，只能按最长的那个去估测，消耗的时间和内存都很大，这也是为什么我在意后面实验没有workload的比较的原因。我没有理解他说的module累积隐私数据会slow leak，但是隐约感觉这个地方解决可以提高性能。	
5. SGX本身并不是“防弹”的，特别是英特尔的性能监测单元（PMU），可以让不受信任的平台深入了解系统正在进行的工作