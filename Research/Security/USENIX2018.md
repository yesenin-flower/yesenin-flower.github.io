### Fear the Reaper: Characterization and Fast Detection of Card Skimmers 

1. skimmer 包括：overlay(外面加一层)、EMV (在card和交易机器中间加一块flexible martial)、camera(看密码)、pad overlay(读密码)、没有蓝牙无线(不能外部检测)
2. skimmer can be detected by counting the number of read heads
3. 一通过就有circuit，voltage spikes of card 看频率，如果频率变成两倍（异常），有skimmer

### BlackIoT: IoT Botnet of High Wattage Devices Can Disrupt the Power Grid

1. 主要介绍的是问题，IoT devices会影响网络，导致网络崩溃。
2. 发电后transmission network, cyberattract on the SCADA system。
3. 以前的假设是用hourly and daily 数据做预测，但是现在high wattage IoT devices(air conditioners and heaters)发展，attacker可以操作grid里的device，从而影响1)stability of the system 2) line failures and cascades 3)increase the operating costs

### <font color=#00ffff>Skill Squatting Attacks on Amazon Alexa</font>

Amazon Alexa语音错误的翻译导致的*skill squatting*， 利用这些error来运行恶意软件

1. 找用户语音中相似的skill。attacker可以构建相似的skill，在用户未知情况下，alexa就用了这些错误的skill
2. dataset: NSP 语音数据，找到预测错误的words，找到音完全不同的词，93%可以启动不同的skill，这些skill可能是支付、下载等等
3. 根据语音构建容易出错的词的模型(另一篇文章用的是lstm算语音，然后算编辑距离)
4. 不同地区的人口音会犯相同的错，attacker可以利用地区特点来构建skill
5. 其他medium也有相似的问题

### <font color=#00ffff>CommanderSong: A Systematic Approach for Practical Adversarial Voice Recognition</font>

在音乐里加噪音(命令)影响automatic speech recognition (ASR) systems的识别 他针对的是KALDI，

![](https://ws4.sinaimg.cn/large/006tNc79ly1g2wit1cpytj31o60u0gu4.jpg)

kaldi
抽features
acoustic model(dnn) 学语音pdf-id
然后pdf id map到(transition-id) 
一系列的transition-id构成phoneme identifie
language model(hmm) 预测词的概率

![](https://ws3.sinaimg.cn/large/006tNc79ly1g2wkh4z9dgj30sq0f2n2g.jpg)

song用的dnn结果 命令用的transition-id转pdf-id

目标函数是让加了噪音的新歌进acoustic model的结果和命令的pdf-id相似

For the complex end-to-end deep learning speech recognizing system, CommanderSong will not work. Furthermore, the over-the-air adversarial example they provide have very low performance and have lots of noise.

----

### Fp-Scanner: The Privacy Implications of Browser Fingerprint Inconsistencies

通过fp的不一致性，找修改fp的countermeasures

1. browser属性：user agent/ screen resolution/ canvas

2. 防止fingerprint的方法：script block/ attributes block/ change attributes values/ blur attributes values；同样的fp也可以使用一些方法detect前面四个防范的方法
3. 可以使用user agent中  ***不一致***  的地方来判断是否用了countermeasures
4. fp-scanner就是利用这种不一致性：OS(webGL/navigator.platform)、browser(throw error)、device(不同设备的API)、canvas(...)
5. 找到真正的OS(plugin/fonts等)、browser(version/family等)

### Who Left Open the Cookie Jar? A Comprehensive Evaluation of Third-Party Cookie Policies

评估third-party policies(cross-site attacks and third-party tracking) cookie容易受到XSS攻击，为此浏览器形成了各种保护机制和政策，本文能通过一个强制执行第三方请求的框架自动化评估这些防御机制的有效性，我们评估了7个浏览器的策略实现和46个浏览器插件，我们发现即使是内置的保护机制也可以被许多新技术绕过。

1. Third-Party Cookie ，当你访问的网站里需要访问其他网站的资源，就会建立其他网站（第三方）的cookies。浏览器可以block这些cookies，也可以用扩展程序，以及same-site cookies（直接访问的网站有一个ss cookies的tag，如果简介访问，那么ss cookies不能用。比如我电脑有支付宝的cookies和直接访问时的ss cookies，用其他商户跳转到支付宝，就不能用ss cookies的信息）
2. 框架检测使用的policies和效果

###<font color=#00ffff>[Effective Detection of Multimedia Protocol Tunneling using Machine Learning](<https://blog.csdn.net/qq_30050175/article/details/88392535>)</font>

existing multimedia protocol tunneling(MPT) systems不能区分covert channel or not,  在审查的时候不安全，提供一种寻找covert channel的方法。multimedia protocol tunneling：多媒体协议隧道：通过将数据调制到多媒体应用程序输入中创建隐蔽通道。隐蔽信道建立在公开的信道中，公开信道传递合法信息，而隐蔽信道对所传信息进行特殊地编码、译码，从而传输传输非法或私密而不被人发现；利用网络隐蔽信道进行扩散攻击和信息泄漏技术，对计算机网络的安全构成巨大威胁

1. 在media里面加入信息，通过skype传播。但可以通过traffic characteristics change 和unusual pattern in encrypted network flows找到
2. 实验方法是将原视频进行修改缩放隐藏视频50％，25％和12.5％的因子，然后分类
3. Our findings suggest that the existence of manually labeled samples is a requirement for the successful detection of covert channels.

### Quack: Scalable Remote Measurement of Application-Layer Censorship

通过block的特征，主动的找到detailed national blocklists，以及各个国家block的keywords特点

Quack can effectively detect application- layer blocking triggered on HTTP and TLS headers, and it is flexible enough to support many other diverse protocols.

----

### <font color=#00ffff>ATtention Spanned: Comprehensive Vulnerability Analysis of AT Commands Within the Android Ecosystem</font>

用Android smartphone firmware images中的at命令控制系统。 the AT command interface contains an alarming amount of unconstrained functionality and represents a broad attack surface on Android devices.

1. AT可以控制android usbdebug
2. 爬app，解压等，再grep at
3. 不同vendor不同分布的at command
4. at command可以控制网络、电话、开密码等

[ATCommand是一种调制解调器的命令语言，由计算机（超级终端）发出的被用来控制和执行模块功能，通过uart串口进行通讯的命令操作方式，通过串口将命令集发送到设备端，然后设备端（手机）自有一套处理框架流程对不同的AT命令进行解析，判断，然后进行相对应的处理，并返回其对应的处理结果。](https://blog.csdn.net/laozhuxinlu/article/details/52085150 )

> ATCommands的语法格式其实就是AT Commands的输入格式，总体上说AT命令有四种形式：
>
> 1）无参数指令（基本命令语法）。 一种简洁的指令，格式：AT[＋|&]<command>举例：显示本机号码“AT+CNUM”，恢复出厂设置命令“AT&F”。
>
> 2）查询指令（读命令语法）。 查询该指令当前设置的值，格式：AT[＋|&]<command>?。举例：电话本存储区可选择的值“AT+CPBS?”。
>
> 3）帮助指令（测试命令语法）。用来列出该命令各参数的所有的可能值(并非各个组合都可能支持)，格式：AT[＋|&]<command>=?。举例：举例：AT+CMGL=?。
>
> 4）带参数指令（扩展命令语法）。用于设置相应的参数值， 比较常用的一种格式，它为指令提供了强大的灵活性，格式：AT[＋|&]<command>=<par1>,<par2>,<par3>„针对不同的AT Commands测试的输入格式是不一样的。甚至大部分都是多种测试的输入格式，具体格式在相应的AT Commands的协议介绍中有详细说明。
>
> 不同的命令其大致的语法格式是差不多的，当然也有一些自定义的AT命令，但其基本格式还是需要按照标准来定义。

### Charm: Facilitating Dynamic Analysis of Device Drivers of Mobile Systems

Charm, a system solution that facilitates dynamic analysis of device drivers of mobile systems. Charm’s key technique is remote device driver execution, which enables the device driver to execute in a virtual machine on a workstation. Charm makes this possible by using the actual mobile system only for servicing the low-level and infrequent I/O operations through a low-latency and customized USB channel. 

1. 现在动态分析用vm没有IO interface，因此分析失败
2. vm kernel的device driver 通过stub+usb channel和mobile的stub连接在一起，然后使用mobile的I/O

### Inception: System-Wide Security Testing of Real-World Embedded Systems Software

嵌入式系统软件的测试方法perform security testing of complete real-world embedded firmware. 

### <font color=#00ffff>Acquisitional Rule-based Engine for Discovering Internet-of-Things Devices</font>

an Acquisitional Rule-based Engine (ARE), which can automatically generate rules for discovering and annotating IoT devices without any training data. ARE builds device rules by leveraging application-layer response data from IoT devices and product descriptions in relevant websites for device annotations. 用频繁项集算法找到rules

-----

### <font color=#00ffff>FlowCog: Context-aware Semantics Extraction and Analysis of Information Flow Leaks in Android Apps</font>

FlowCog statically finds all the Android views that are related to the given flow via control or data dependencies, and then extracts semantics, such as texts and images, from these views and associated layouts. Next, FlowCog adopts a natural language processing (NLP) approach to infer whether the extracted semantics are correlated with the given flow. Android访问私人信息是否合法取决于应用是否向用户提供了足够的解释，FlowCog从Android视图中抽取相关的语义，再用NLP方法推断语义与给定流是否相关。

1. 用户flow的目的(eg update weather)，如果view的语义确实是这个，那这个flow合法
2. 静态分析用flowdorid得到activation event 和guarding condition(流程图中的分岔点)，知道之后用了什么隐私数据；+动态分析得到semantic extractor；+document of source &sink
3. TF-IDF+svm/boosting
4. word2vec+similarity

### <font color=#00ffff>Sensitive Information Tracking in Commodity IoT</font>

SainT, a static taint analysis tool for IoT applications. SainT operates in three phases; (a) translation of platform-specific IoT source code into an intermediate representation (IR), (b) identifying sensitive sources and sinks, and (c) performing static analysis to identify sensitive data flows. 

### <font color=#00ffff>Enabling Refinable Cross-Host Attack Investigation with Efficient Data Flow Tagging and Tracking</font>

an efficient data flow tagging and tracking mechanism that enables practical cross-host attack investigations. 分布式系统多个结点数据泄露

1. 设计了新的tag方法DIFT，构建Global and Local Tags
2. link tag propagation between 2 hosts via socket communication(TCP: counter-based, UDP: tag-embedding based)
3. 找到错误结点

### <font color=#00ffff>Dependence-Preserving Data Compaction for Scalable Forensic Analysis</font> 

数据量大的情况下如何做Forensic Analysis

1. 构件依赖图，节点是process 或者 file/network connection，边是时间戳，指向信息流方向
2. 通过时间顺序，backward找到之前的结点，forward找到之后的结点
3. Log-based: 不改变依赖的情况下删除event；去掉重复的连续事件
4. graph-based: 使用global context来剪枝；FD方法如果交叉事件不改变global dependence；SD方法不引入source nodes的新依赖

---

### How Do Tor Users Interact With Onion Services?

### Towards Predicting Efficient and Anonymous Tor Circuits

Tor是互联网上用于保护您隐私最有力的工具之一，而Tor Hidden Services则是为了隐藏自己的网站或者其他服务的一个服务。通过此服务，我们可以获取到一个通过Tor Browser来访问的Hostname，此Hostname唯一且匿名，所以我们完全可以使用这个Hostname来为我们转发流量从而达到隐匿的目的。

### BurnBox: Self-Revocable Encryption in a World Of Compelled Access

假设云环境不可信，新的环境burnbox

1. 加密信息被保存到客户端，包括key、key对应的加密后文件，以及restoration ciphertext（记录此文件是被删除还是被revoke）；云上只有加密后的文件
2. 用户选择revoke和delete敏感信息文件，这些文件则inaccessible并且加密使得不可区分（不知道具体哪个被revoke哪个被delete）
3. 用户用restoration key去revoke文件
4. file key被存储在一个append-only table里，可信设备才可以删除key

### An Empirical Analysis of Anonymity in Zcash

Zcash有shielded pool，通过value 找到此pool里的数据交换链

----



----

### **The Battle for New York: A Case Study of Applied Digital Threat Modeling at the Enterprise Level.** 

### **SAQL: A Stream-based Query System for Real-Time Abnormal System Behavior Detection.** 

---

### **Efail: Breaking S/MIME and OpenPGP Email Encryption using Exfiltration Channels.** 

### **The Dangers of Key Reuse: Practical Attacks on IPsec IKE.** 

### **One&Done: A Single-Decryption EM-Based Attack on OpenSSL's Constant-Time Blinded RSA**

### **DATA - Differential Address Trace Analysis: Finding Address-based Side-Channels in Binaries.** 

----

### **Practical Accountability of Secret Processes.** 

### **DIZK: A Distributed Zero Knowledge Proof System.**

---

### **NetHide: Secure and Practical Network Topology Obfuscation.**

### **Towards a Secure Zero-rating Framework with Three Parties.** 

---

### A Sense of Time for JavaScript and Node.js: First-Class Timeouts as a Cure for Event Handler Poisoning

First-Class Timeouts, which incorporates timeouts at the EDA framework level.

### Rampart: Protecting Web Applications from CPU-Exhaustion Denial-of-Service Attacks

Rampart detects and stops sophisticated CPU-exhaustion DoS attacks using statistical methods and function-level program profiling. Furthermore, it synthesizes and deploys filters to block subsequent attacks, and it adaptively updates them to minimize any potentially negative impact on legitimate users.

### <font color=#00ffff>NAVEX: Precise and Scalable Exploit Generation for Dynamic Web Applications</font>

通过网页动态生成的url，找到可能被注入等攻击的页面

### Freezing the Web: A Study of ReDoS Vulnerabilities in JavaScript-based Web Servers

analyzing the exploitability of deployed servers. The basic idea is to search for previously unknown vulnerabilities in popular libraries, hypothesize how these libraries may be used by servers, and to then craft targeted exploits.

----

###Better managed than memorized? Studying the Impact of Managers on Password Strength and Reuse

password重用率高，主要是数据集

1. gain a more complete picture of the factors that influence our participants' password strength and reuse(70.56%). 
2. Better generation 

### Forgetting of Passwords: Ecological Theory and Data

人的遗忘和password登陆次数等构件模型，概率的解决思路

human memory naturally adapts according to an estimate of how often a password will be needed, such that often used, important passwords are less likely to be forgotten. We derive models(概率) for login duration and odds of recall as a function of rate of use and number of uses thus far. The models achieved a root-mean-square error (RMSE) of 1.8 seconds for login duration and 0.09 for recall odds for data collected in a month-long field experiment where frequency of password use was controlled

### The Rewards and Costs of Stronger Passwords in a University: Linking Password Lifetime to Strength

根据password强度动态形成password的reset时间，Strength was measured through Shannon entropy (acknowledged to be a poor measure of password strength by the academic community, but still widely used in practice). 

### Rethinking Access Control and Authentication for the Home Internet of Things (IoT)

access control focus on IoT capabilities (i.e., certain actions that devices can perform), rather than on a per-device granularity. 

------

#### ACES: Automatic Compartments for Embedded System 

an LLVM-based compiler that automatically infers and enforces inter-component isolation on bare-metal systems, thus applying the principle of least privileges. 

#### IMIX: In-Process Memory Isolation EXtension

a lightweight, in-process memory isolation extension for the Intel-based x86 CPUs. Our solution extends the x86 ISA with a new memory-access permission to mark memory pages as security sensitive. 

#### HeapHopper: Bringing Bounded Model Checking to Heap Implementation Security

an automated approach, based on model checking and symbolic execution, to analyze the exploitability of heap implementations in the presence of memory corruption. 

#### Guarder: A Tunable Secure Allocator

Guarder ensures the desired randomization entropy, and provides an unprecedented level of security guarantee by combining all security features of existing allocators, with overhead that is comparable to performance-oriented allocators. 



#TODO

1. CommanderSong: A Systematic Approach for Practical Adversarial Voice Recognition **认真读一次**
2. Effective Detection of Multimedia Protocol Tunneling using Machine Learning：不需要label
3. ATtention Spanned: Comprehensive Vulnerability Analysis of AT Commands Within the Android Ecosystem
4. Acquisitional Rule-based Engine for Discovering Internet-of-Things Devices
5. FlowCog: Context-aware Semantics Extraction and Analysis of Information Flow Leaks in Android Apps
6. Sensitive Information Tracking in Commodity IoT
7. Dependence-Preserving Data Compaction for Scalable Forensic Analysis

