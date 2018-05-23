*    [Basic Concepts](#basic-concepts)
     * [Datasets](#datasets)
*    [Supervised Approaches](#supervised-approaches)
     *  [Feature-based Methods](#feature-based-methods)
     *  [Kernel Methods](#kernel-methods)
        * [Sequence Kernel](#sequence-kernel)
        * [Syntactic Tree Kernel](#syntactic-tree-kernel)
        * [Dependency Tree Kernel](#dependency-tree-kernel)
        * [Dependency Graph Path Kernel](#dependency-graph-path-kernel)
        * [Composite Kernels](#composite-kernels)
     *  [NN](#nn)
        * [Simple CNN Model](#simple-cnn-model)
        * [CNN with Max Pooling and word embedding](#cnn-with-max-pooling-and-word-embedding)
        * [CNN with Rank Loss](#cnn-with-rank-loss)
        * [BiLSTM Attention](#bilstm-attention)
        * [Multi-Level Attention CNN](#multi-level-attention-cnn)

*    [Semi-supervised Approaches](#semi-supervised-approaches)
     * [Bootstrapping Approaches](#bootstrapping-approaches)
     * [Active Learning](#active-learning)
     * [Label Propagation Method](#label-propagation-method)
*    [Unsupervised Relation Extraction](#unsupervised-relation-extraction)
     * [Clustering based approaches](#clustering-based-approaches)
*    [Distant Supervision](#distant-supervision)
     * [MIML-RE](#miml-re)
     * [NN](#nn-1)
        * [Piecewise Convolutional Neural Networks](#piecewise-convolutional-neural-networks)
        * [Selective Attention over Instances](#selective-attention-over-instances)
        * [Multi-instance Multi-label CNNs](#multi-instance-multi-label-cnns)
        * [<a href="https://blog.csdn.net/sinat_36972314/article/details/80266698" rel="nofollow">总结</a>](#总结)

# Basic Concepts

## Datasets

Automatic Content Extraction (ACE), 有关系的type和subtype

![](https://ws3.sinaimg.cn/large/006tNc79ly1frjxqwyc4hj30oi0k67aj.jpg)			

SemiEval 2010 Task8 Dataset:

- 19 types
- train data: 8000
- test data: 2717

NYT+FreeBase:

- 53 types
- train data: 522611 sentences; 需要注意的是，这里面有近80%的句子的标签为NA
- test data: 172448 sentences;

Message Understanding Conference (MUC-7) 

# Supervised Approaches

每个\<S, P>预定义一个type，type NONE用来标注不属于任何一个type的关系。变成一个多个类分类问题。

## Feature-based Methods

两个要素：Feature & Classifier

Kambhatla<sup id="a1">[1](#f1)</sup> maximum entropy classifier + features:

e.g. 	Top leaders of Italy’s left-wing government were in Venice.

![](https://ws1.sinaimg.cn/large/006tNc79ly1frjyeq7juwj30uw0fuwj9.jpg)

Zhou<sup id="a2">[2](#f2)</sup> SVM classifier + features:

1. Word based features: SP之间的词，前后的词，headwords，SP是否是包含关系
2. **Base phrase chunking based features**: phrase heads， 前后的phrase heads，连接SP的phrase labels的路径
3. Features based on semantic resources: 用wordnet计算语义相近的类

Phrase 效果非常好，因为ACE中的数据大部分是短距离关系。

Nguyen<sup id="a3">[3](#f3)</sup> 提出 core tree 来表示关系。包含SP再依赖树上的最短路径和最短路径上结点到句子keywords的路径。 core tree 的子树作为特征。

Chan and Roth<sup id="a4">[4](#f4)</sup> 提出syntactico-semantic structures. 主要是部分ACE关系里的表达有规律。		

Kambhatla<sup id="a5">[5](#f5)</sup> Class Imbalance 无关系的SP远大于有关系的。所以用一组clasifier 投票的方法来提高召回。

## Kernel Methods

计算关系的表示(e.g. sequence, syntacitc parse tree)的相似度(e.g. 树的相似度)，再用SVM分类。先把所有关系组成一个类训练分类器来判断SP是不是有关系，在用一个multi-class SVM具体分类。

### Sequence Kernel

Bunescu and Mooney<sup id="a6">[6](#f6)</sup>每个关系表示成一系列的特征向量，每个词变成一个feature vector。目标是设计一个kernel function来发现一个subsequences(想办法用Features找pattern)。

Feature: 

![](https://ws2.sinaimg.cn/large/006tNc79ly1frjz09gx55j30p604m754.jpg)

e.g. Top leaders of Italy’s left-wing government were in Venice.

![](https://ws4.sinaimg.cn/large/006tNc79ly1frjz1wa0mbj30q206s759.jpg)

### Syntactic Tree Kernel

用句子的句法特征，比如noun phrases (NP), verb phrases (VP), prepositional phrases (PP), POS tags(NN, VB, IN, etc.)构建解析树。

关系的表达：

![](https://ws2.sinaimg.cn/large/006tNc79ly1frke0am0uhj30ug0diwi2.jpg)


![](https://ws3.sinaimg.cn/large/006tNc79ly1frkdy8hr8sj30ug14aamh.jpg)

计算相似度方法：

![](https://ws3.sinaimg.cn/large/006tNc79ly1frlaij3sbuj31gu0rejxc.jpg)

See: [Syntactic Tree Kernel](https://github.com/Moirai7/blog/blob/master/Research/NLP/RE_Syntactic_Tree_Kernel.md)

### Dependency Tree Kernel

依存树：句子中词的语法关系。除了head，每个词有一个parent，词到parent形成有向边。

![](https://ws4.sinaimg.cn/large/006tNc79ly1frjzk5kulcj30fy0ckwfq.jpg)

Culotta and Sorensen<sup id="a7">[7](#f7)</sup> + Zelenko<sup id="a8">[8](#f8)</sup> 提出一个计算相似度方法：依赖树上每个结点都扩展为Word, POS, Generalized POS, Chunk tag, Entity type, Entity-level, Relation argument等。比较两个结点，如果有important features一样，就认为两个结点相似。

![](https://ws1.sinaimg.cn/large/006tNc79ly1frjzoigc7aj30ec0dctap.jpg)	

### 	Dependency Graph Path Kernel

Bunescu and Mooney<sup id="a9">[9](#f9)</sup> 计算SP在依赖树上的路径。如\<leaders, Venice>, the shortest path is : leaders were in Venice。但完全使用路径会让数据很稀疏，所以最短路径上结点都加上 POS,Generalized POS, Entity type etc。所有的路径都是一个feature。

![](https://ws1.sinaimg.cn/large/006tNc79ly1frjzve51jkj30mg04et94.jpg)

### Composite Kernels

组合Syntactic Tree Kernel & Sequence Kernel / tokenization, sentence parsing and deep dependency analysis/ relation topics: sum, product, linear combination.

## NN

### Simple CNN Model 

> Liu,(2013). Convolution neural network for relation extraction. 8347 LNAI(PART 2), 231–242.

输入是one-hot，卷积网络+一个普通的全连接层以及softmax分类。

### CNN with Max Pooling and word embedding

> Zeng, . (2014). Relation Classification via Convolutional Deep Neural Network. Coling, 2335–2344

输入是(Turian 2010ACL Word representations: a simple and general method for semi-supervised learning.)提供的word embedding。

lexical-level feature：

- L1: entity1
- L2: entity2
- L3: entity1的左右两个tokens
- L4: entity2的左右两个tokens
- L5: WordNet中两个entity的上位词。在wordNet中找到两个entity的上位词。上位词就是包含关系，比如parrot这个词的上位词就是bird. 这种包含关系其实类似于指明了实体的类型特征。

sentence-level feature：

NN。输入是word embedding + position feature（每个word与两个entity的相对距离），卷积操作+Max Pooling。

![img](http://7xotye.com1.z0.glb.clouddn.com/blog/relation-extraction/6.jpg)

将上面的lexical-feature 与 sentence-level feature 直接串起来，作为整个句子的特征去做分类。

![img](http://7xotye.com1.z0.glb.clouddn.com/blog/relation-extraction/5.jpg)

### CNN with Rank Loss

> Santos(2015). Classifying Relations by Ranking with Convolutional Neural Networks. ACL

最大的变化是损失函数，不再使用softmax+cross-entropy的方式，而是margin based的ranking-loss.

- 输入层: 利用word embedding + position embedding,同zeng 2014
- 卷积层: 固定尺寸的卷积核(window-size=3)
- Pooling层: 直接Max Pooling得到 
- 全连接层: 得到每个类别的score，其中的每一列可以看成 label 的embedding。

### BiLSTM Attention

> Zhou. (2016). Attention-Based Bidirectional Long Short-Term Memory Networks for Relation Classification. ACL

基于RNN对句子建模，使用标准的的Attention + BiLSTM

![](http://7xotye.com1.z0.glb.clouddn.com/blog/relation-extraction/bilstm-1.png)

Attention Layer, 其实就是一个对LSTM的每一个step的输出做一个加权的过程，而非仅仅只取最后一个step.

### Multi-Level Attention CNN

> Wang. (2016). Relation Classification via Multi-Level Attention CNNs. ACL

两层Attention机制来尽可能突出句子中哪些部分对relation label有更大的贡献。使用了word similarity来定义句子中word与target entity的相似度，从而根据相似度来引入权重，这是第一层的Attention. 第二层Attention则是对卷积之后Pooling阶段，采用Attention Pooling 而不是Max Pooling. 

# Semi-supervised Approaches

## Bootstrapping Approaches

Pattern Relation Duality: Pattern包含命名实体，前缀后缀等。 bootstrapping的性能受种子的影响很大。

DIPRE  (Brin, 1998)算法：

![](https://ws4.sinaimg.cn/large/006tNc79ly1frk2iolv44j30v8072myn.jpg)

SnowBall (Agichtein & Gravano, 2000)算法：

![](https://ws3.sinaimg.cn/large/006tNc79ly1frlaocyv9wj31cq0dy40h.jpg)

KnowItAll (Etzioni et al. 2005)算法：

​	基于 general Noun Phrase (NP) chunker 手写pattern

TextRunner (Banko et al. 2007)算法：

​	没有预定义关系，自动抽取关系。

![](https://ws4.sinaimg.cn/large/006tNc79ly1frlaqd48haj31h013e4fl.jpg)

**总结：**

![](https://ws4.sinaimg.cn/large/006tNc79ly1frlavp6buqj31e40pqwiz.jpg)

## Active Learning

训练多个分类器，对instances 预测，用KL散度计算所有分类器最不确定的instance，然后给这个instance做标注，最后放回到训练集中

See: [Active Learning](https://github.com/Moirai7/blog/blob/master/Research/NLP/RE_Active_Learning.md)		

## Label Propagation Method

Zhu and Ghahramani<sup id="a10">[10](#f10)</sup>标注和为标注的实体转化为图中的结点，边为结点的相似度。

# Unsupervised Relation Extraction

## Clustering based approaches			

1. The named entities in the text corpora are tagged
2. Co-occurring named entity pairs are formed and their contexts are recorded
3. Context similarities among the pairs identified in the step 2, are computed
4. Using the similarity values computed in previous step, the pairs are clustered
5. As each of these clusters represent one relation, a label is automatically assigned to each cluster describing the relation type represented by it


# Distant Supervision

Mintz<sup id="a11">[11](#f11)</sup> 给文章自动标注，组合监督和半监督两种思路。噪声很多，但大量数据可以抵消这些噪声。

假设：如果两个实体存在一个关系，那么任何包含这两实体的句子都可能表述此关系。而Freebase上没有关联的两个实体就作为negative instance。

##  MIML-RE

Surdeanu<sup id="a12">[12](#f12)</sup> 提出 MIML-RE 解决overlapping relation的问题。假设SO存在一个关系，那一堆包含SO的句子至少有一个反应了这个关系。假设训练数据集中的每个数据是一个包(Bag)，每个包都是一个示例(instance)的集合,每个包都有一个训练标记，而包中的示例是没有标记的；如果包中至少存在一个正标记的示例，则包被赋予正标记；而对于一个有负标记的包，其中所有的示例均为负标记。

所有提到SO的实例i都都放到一个bag里，并打上标签z(P或者None)，再训练|R|(一共|R|个P)binary classifiers y来表示提到SO的实例i是否真的表示P。训练z binary classifiers.这些classifiers特点: 实例i中至少有一个在表述P；关系的共现包含在内。

![](https://ws1.sinaimg.cn/large/006tNc79ly1frl15bflzkj30kk0si0wn.jpg)

<!--没有知识库的话，距离监督很难实现，因为需要大量的spo三元组。Zhang<sup id="a13">[13](#f13)</sup> 提出Ontological Smoothing，假设种子中至少有一部分是正确的。生成relation of interest和知识库的mapping，再用mapping生成种子的训练数据，然后用距离监督抽取关系。

Nguyen<sup id="a14">[14](#f14)</sup>联合 distant & direct supervison。把不同数据源的realtion 类型关联起来，创建一个距离监督标注的数据集，再分别对数据源用人工标注和距离监督训练不同分类器，用这些分类器的联合概率作为最终概率。

Angeli<sup id="a15">[15](#f15)</sup> 主动学习 + 距离监督。效果比 MIML-RE 好。-->

## NN

### Piecewise Convolutional Neural Networks

> Zeng (2015). Distant Supervision for Relation Extraction via Piecewise Convolutional Neural Networks. EMNLP

![img](http://7xotye.com1.z0.glb.clouddn.com/blog/relation-extraction/pcnn-1.png)

输入仍然是一个sentence，Input Layer依然是word embedding(word2vec) + position embedding, 后面接卷积操作。 之后的Pooling层并没有直接使用全局的Max Pooling, 而是局部的max pooling. 文中把一个句子分为三部分，以两个entity为边界把句子分为三段，然后卷积之后对每一段取max pooling, 这样可以得到三个值，相比传统的max-pooling 每个卷积核只能得到一个值，这样可以更加充分有效的得到句子特征信息。经过softmax 就可以计算每一个类别的概率了。

前面是一个instance级别的，根据MIML定义，需要计算bag的label，因此取bag里instance概率最大的作为bag概率。

![img](http://7xotye.com1.z0.glb.clouddn.com/blog/relation-extraction/pcnn-4.png)

### Selective Attention over Instances

> Lin (2016). Neural Relation Extraction with Selective Attention over Instances.ACL

在Zeng 2015中的MIL部分，每一个bag仅仅取了置信度最高的instance，这样会丢失很多的信息，因此一个bag内可能有很多个positive instance。应用Attention机制可以减弱噪音，加强正样本，因此可以更充分的利用信息。

为了能够充分的利用bag内的信息，我们可以对所有instance取加权: 

- Average: 直接取平均:  ，这种将所有instance同等对待的方式还是有缺陷，放大了噪音影响。
- Attention: 目标是增加positive instance的权重，减小noise instance的权重。但是并不知道每个instance的groud truth，但是知道每个bag的label，因此就可以用instance 与 该relation label的相关度大小引入Attention

### Multi-instance Multi-label CNNs

> Jiang (2016). Relation Extraction with Multi-instance Multi-label Convolutional Neural Networks. Coling

![img](http://7xotye.com1.z0.glb.clouddn.com/blog/relation-extraction/miml-1.png)

输入也是一个bag，然后利用CNN/PCNN来计算每个sentence的embedding，之后的融合方式很直接，直接对embedding的每一维度取所有sentence的对应维度的最大值。

### [总结](https://blog.csdn.net/sinat_36972314/article/details/80266698)

> general的总结:
>
> - 输入层: 基本word embedding + position emebdding
> - Sentence Embedding: 基本使用CNN/PCNN
> - Multi Instance Learning: 基本使用Attention 来处理(Attention的选择有待改进)
> - Evaluate:
>   - Held-out: P-R 曲线
>   - Manual: 选择Negative False的标签为NA的数据， 手工检测是否的确为NA
>
> 其他Tips:
>
> - Word-Entity的相关度，同一个word在不同的entity pair内有不同的重要性。(Deep Memory Network, Multi-Level Att )
> - Word-Relation的相关度，同一个word在不同的relation下有不同的重要性。()
> - 多标签分类(MIMLCNN, Memory Network)
> - relation之间的依赖性(Memory Network)

-----

总体流程，主动学习 + MIMC_RE：

* 对关系P，找出一堆SO及其instances，分为训练集和测试集
* 对训练集和测试集所有数据，每个instance先算PCNN特征。输入为word embedding(word2vec) + position embedding + POS等。
* 每个SO的instances是一个bag，用训练集训练一个global分类器
* 每个SO的instances是一个bag，训练集每个bag里的instances有放回抽样，用[Multi-instance Multi-label CNNs](#multi-instance-multi-label-cnns)或[Selective Attention over Instances](#selective-attention-over-instances)的思路，训练多个local分类器。
* 用主动学习的思路，local分类器打分，选实例，人工标注。
* 人工标注的实例，加入到训练集中，重新训练global分类器，并用测试集判断准确召回，到达阈值后结束。

----

<b id = 'f1'>1</b> N. Kambhatla. Combining lexical, syntactic, and semantic features with maximum entropy models for extracting relations. [↩](#a1)

<b id = 'f2'>2</b> Zhou GuoDong, Su Jian, Zhang Jie, and Zhang Min. Exploring various knowledge in relation extraction.[↩](#a2)

<b id = 'f3'>3</b> Dat PT Nguyen, Yutaka Matsuo, and Mitsuru Ishizuka. Relation extraction from wikipedia using subtree mining. [↩](#a3)

<b id = 'f4'>4</b> Yee Seng Chan and Dan Roth. Exploiting syntactico-semantic structures for relation extraction. [↩](#a4)

<b id = 'f5'>5</b> Nanda Kambhatla. Minority vote: at-least-n voting improves recall for extracting relations. [↩](#a5)

<b id = 'f6'>6</b> Raymond J Mooney and Razvan C Bunescu. Subsequence kernels for relation extraction. [↩](#a6)

<b id = 'f7'>7</b> Aron Culotta and Je↵rey Sorensen. Dependency tree kernels for relation extraction. [↩](#a7)

<b id = 'f8'>8</b> Dmitry Zelenko, Chinatsu Aone, and Anthony Richardella. Kernel methods for relation extraction. [↩](#a8)

<b id = 'f9'> 9</b> Razvan C Bunescu and Raymond J Mooney. A shortest path dependency kernel for relation extraction. [↩](#a9)

<b id = 'f10'>10</b> Zhu Xiaojin and Ghahramani Zoubin. Learning from labeled and unlabeled data with label propagation. [↩](#a10)

<b id = 'f11'>11</b> Mike Mintz, Steven Bills, Rion Snow, and Dan Jurafsky. Distant supervision for relation extraction without labeled data.[↩](#a11)

<b id = 'f12'>12</b> Mihai Surdeanu, Julie Tibshirani, Ramesh Nallapati, and Christopher D Manning. Multi-instance multi-label learning for relation extraction.[↩](#a12)

<b id = 'f13'>13 </b> Congle Zhang, Raphael Hoffmann, and Daniel S Weld. Ontological smoothing for relation extraction with minimal supervision.[↩](#a13)

<b id = 'f14'>14 </b> Truc-Vien T Nguyen and Alessandro Moschitti. Joint distant and direct supervision for relation extraction. [↩](#a14)

<b id = 'f15'>15</b> Gabor Angeli, Julie Tibshirani, Jean Y Wu, and Christopher D Man-ning. Combining distant and partial supervision for relation extraction. [↩](#a15)
