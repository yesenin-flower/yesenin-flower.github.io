* [数据集](#数据集)
* [Supervised Approaches](#supervised-approaches)
     * [Feature-based Methods](#feature-based-methods)
     * [Kernel Methods](#kernel-methods)
        * [Sequence Kernel](#sequence-kernel)
        * [Syntactic Tree Kernel](#syntactic-tree-kernel)
        * [Dependency Tree Kernel](#dependency-tree-kernel)
        * [Dependency Graph Path Kernel](#dependency-graph-path-kernel)
        * [Composite Kernels](#composite-kernels)
* [Semi-supervised Approaches](#semi-supervised-approaches)
     * [Bootstrapping Approaches](#bootstrapping-approaches)
     * [Active Learning](#active-learning)
     * [Label Propagation Method](#label-propagation-method)
* [Unsupervised Relation Extraction](#unsupervised-relation-extraction)
     * [Clustering based approaches](#clustering-based-approaches)
* [Distant Supervision](#distant-supervision)

# 数据集

Automatic Content Extraction (ACE), 有关系的type和subtype

![](https://ws3.sinaimg.cn/large/006tNc79ly1frjxqwyc4hj30oi0k67aj.jpg)			

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


![](https://ws3.sinaimg.cn/large/006tNc79ly1frkdy8hr8sj30ug14aamh.jpg)

关系的表达：

![](https://ws2.sinaimg.cn/large/006tNc79ly1frke0am0uhj30ug0diwi2.jpg)

See: [Syntactic Tree Kernel](https://github.com/Moirai7/blog/blob/master/Research/NLP/RE_Syntactic_Tree_Kernel.md)

### Dependency Tree Kernel

依存树：句子中词的语法关系。除了head，每个词有一个parent，词到parent形成有向边。

![](https://ws4.sinaimg.cn/large/006tNc79ly1frjzk5kulcj30fy0ckwfq.jpg)

Culotta and Sorensen<sup id="a7">[7](#f7)</sup> + Zelenko<sup id="a8">[8](#f8)</sup> 提出一个计算相似度方法：依赖树上每个结点都扩展为POS tag, chunk tag等。比较两个结点，如果有important features一样，就认为两个结点相似。

![](https://ws1.sinaimg.cn/large/006tNc79ly1frjzoigc7aj30ec0dctap.jpg)	

### 	Dependency Graph Path Kernel

Bunescu and Mooney<sup id="a9">[9](#f9)</sup> 计算SP在依赖树上的路径。如\<leaders, Venice>, the shortest path is : leaders were in Venice。但完全使用路径会让数据很稀疏，所以每个词都加了各种tag。所有的路径都是一个feature。

![](https://ws1.sinaimg.cn/large/006tNc79ly1frjzve51jkj30mg04et94.jpg)

### Composite Kernels

组合Syntactic Tree Kernel & Sequence Kernel / tokenization, sentence parsing and deep dependency analysis/ relation topics: sum, product, linear combination.

# Semi-supervised Approaches

## Bootstrapping Approaches

Pattern Relation Duality: Pattern包含命名实体，前缀后缀等。 bootstrapping的性能受种子的影响很大。基于DIPRE / SnowBall算法：

![](https://ws4.sinaimg.cn/large/006tNc79ly1frk2iolv44j30v8072myn.jpg)

## Active Learning

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

Surdeanu<sup id="a12">[12](#f12)</sup> 提出 MIML-RE 解决overlapping relation的问题，给一个实体对不同instances建模多个潜在关系标签及实体对标签的依赖关系。entity pair level classifiers学会不可能出现在一个句子中的label(e.g. 出生地和配偶)，以及可能出现在一起两个label(e.g. 首都和包含于)。

没有知识库的话，距离监督很难实现，因为需要大量的spo三元组。Zhang<sup id="a13">[13](#f13)</sup> 提出Ontological Smoothing，假设种子中至少有一部分是正确的。生成relation of interest和知识库的mapping，再用mapping生成种子的训练数据，然后用距离监督抽取关系。

Nguyen<sup id="a14">[14](#f14)</sup>联合 distant & direct supervison。把不同数据源的realtion 类型关联起来，创建一个距离监督标注的数据集，再分别对数据源用人工标注和距离监督训练不同分类器，用这些分类器的联合概率作为最终概率。

Angeli<sup id="a15">[15](#f15)</sup> 主动学习 + 距离监督。效果比 MIML-RE 好。

----

<b id = 'f1'>1</b>N. Kambhatla. Combining lexical, syntactic, and semantic features with maximum entropy models for extracting relations. [↩](#a1)

<b id = 'f2'>2</b>Zhou GuoDong, Su Jian, Zhang Jie, and Zhang Min. Exploring various knowledge in relation extraction.[↩](#a2)

<b id = 'f3'>3</b>Dat PT Nguyen, Yutaka Matsuo, and Mitsuru Ishizuka. Relation extraction from wikipedia using subtree mining. [↩](#a3)

<b id = 'f4'>4</b>Yee Seng Chan and Dan Roth. Exploiting syntactico-semantic structures for relation extraction. [↩](#a4)

<b id = 'f5'>5</b>Nanda Kambhatla. Minority vote: at-least-n voting improves recall for extracting relations. [↩](#a5)

<b id = 'f6'>6</b>Raymond J Mooney and Razvan C Bunescu. Subsequence kernels for relation extraction. [↩](#a6)

<b id = 'f7'>7</b>Aron Culotta and Je↵rey Sorensen. Dependency tree kernels for relation extraction. [↩](#a7)

<b id = 'f8'>8</b>Dmitry Zelenko, Chinatsu Aone, and Anthony Richardella. Kernel methods for relation extraction. [↩](#a8)

<b id = 'f9'> 9</b>Razvan C Bunescu and Raymond J Mooney. A shortest path dependency kernel for relation extraction. [↩](#a9)

<b id = 'f10'>10</b>Zhu Xiaojin and Ghahramani Zoubin. Learning from labeled and unlabeled data with label propagation. [↩](#a10)

<b id = 'f11'>11</b>Mike Mintz, Steven Bills, Rion Snow, and Dan Jurafsky. Distant supervision for relation extraction without labeled data.[↩](#a11)

<b id = 'f12'>12</b>Mihai Surdeanu, Julie Tibshirani, Ramesh Nallapati, and Christopher D Manning. Multi-instance multi-label learning for relation extraction.[↩](#a12)

<b id = 'f13'>13 </b> Congle Zhang, Raphael Hoffmann, and Daniel S Weld. Ontological smoothing for relation extraction with minimal supervision.[↩](#a13)

<b id = 'f14'>14 </b>Truc-Vien T Nguyen and Alessandro Moschitti. Joint distant and direct supervision for relation extraction. [↩](#a14)

<b id = 'f15'>15</b>Razvan Bunescu and Raymond Mooney. Learning to extract relations from the web using minimal supervision. [↩](#a15)