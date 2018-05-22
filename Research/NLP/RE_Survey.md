[TOC]

# 数据集

Automatic Content Extraction (ACE), 有关系的type和subtype

![](https://ws3.sinaimg.cn/large/006tNc79ly1frjxqwyc4hj30oi0k67aj.jpg)			

# Supervised Approaches

每个\<S, P>预定义一个type，type NONE用来标注不属于任何一个type的关系。变成一个多个类分类问题。

## Feature-based Methods

两个要素：Feature & Classifier

Kambhatla[^1] maximum entropy classifier + features:

e.g. 	Top leaders of Italy’s left-wing government were in Venice.

![](https://ws1.sinaimg.cn/large/006tNc79ly1frjyeq7juwj30uw0fuwj9.jpg)

Zhou[^2] SVM classifier + features:

1. Word based features: SP之间的词，前后的词，headwords，SP是否是包含关系
2. **Base phrase chunking based features**: phrase heads， 前后的phrase heads，连接SP的phrase labels的路径
3. Features based on semantic resources: 用wordnet计算语义相近的类

Phrase 效果非常好，因为ACE中的数据大部分是短距离关系。

Nguyen[^3] 提出 core tree 来表示关系。包含SP再依赖树上的最短路径和最短路径上结点到句子keywords的路径。 core tree 的子树作为特征。

Chan and Roth[^4] 提出syntactico-semantic structures. 主要是部分ACE关系里的表达有规律。		

Kambhatla[^5] Class Imbalance 无关系的SP远大于有关系的。所以用一组clasifier 投票的方法来提高召回。

## Kernel Methods

计算关系的表示(e.g. sequence, syntacitc parse tree)的相似度(e.g. 树的相似度)，再用SVM分类。先把所有关系组成一个类训练分类器来判断SP是不是有关系，在用一个multi-class SVM具体分类。

### Sequence Kernel

Bunescu and Mooney[^6] 每个关系表示成一系列的特征向量，每个词变成一个feature vector。目标是设计一个kernel function来发现一个subsequences(想办法用Features找pattern)。

Feature: 

![](https://ws2.sinaimg.cn/large/006tNc79ly1frjz09gx55j30p604m754.jpg)

e.g. Top leaders of Italy’s left-wing government were in Venice.

![](https://ws4.sinaimg.cn/large/006tNc79ly1frjz1wa0mbj30q206s759.jpg)

### Syntactic Tree Kernel

See: [Syntactic Tree Kernel](https://github.com/Moirai7/blog/blob/master/Research/NLP/RE_Syntactic_Tree_Kernel.md)

### Dependency Tree Kernel

依存树：句子中词的语法关系。除了head，每个词有一个parent，词到parent形成有向边。

![](https://ws4.sinaimg.cn/large/006tNc79ly1frjzk5kulcj30fy0ckwfq.jpg)

Culotta and Sorensen[^7] + Zelenko[^8] 提出一个计算相似度方法：依赖树上每个结点都扩展为POS tag, chunk tag等。比较两个结点，如果有important features一样，就认为两个结点相似。

![](https://ws1.sinaimg.cn/large/006tNc79ly1frjzoigc7aj30ec0dctap.jpg)	

### 	Dependency Graph Path Kernel

Bunescu and Mooney[^9] 计算SP在依赖树上的路径。如\<leaders, Venice>, the shortest path is :


leaders were in Venice。但完全使用路径会让数据很稀疏，所以每个词都加了各种tag。所有的路径都是一个feature。

![](https://ws1.sinaimg.cn/large/006tNc79ly1frjzve51jkj30mg04et94.jpg)

### Composite Kernels

组合Syntactic Tree Kernel & Sequence Kernel / tokenization, sentence parsing and deep dependency analysis/ relation topics: sum, product, linear combination.

# Semi-supervised Approaches

## Bootstrapping Approaches

Pattern Relation Duality 基于DIPRE算法：

![](https://ws4.sinaimg.cn/large/006tNc79ly1frk2iolv44j30v8072myn.jpg)


Pattern包含命名实体


​		
​	


​		
​	









[^1]: N. Kambhatla. Combining lexical, syntactic, and semantic features with maximum entropy models for extracting relations. In Proceedings of the ACL 2004, 2004.
[^2]: Zhou GuoDong, Su Jian, Zhang Jie, and Zhang Min. Exploring various knowledge in relation extraction.
[^3]: Dat PT Nguyen, Yutaka Matsuo, and Mitsuru Ishizuka. Relation extraction from wikipedia using subtree mining. In Proceedings of the National Conference on Artificial Intelligence, volume 22, page 1414. Menlo Park, CA; Cambridge, MA; London; AAAI Press; MIT Press; 1999, 2007.
[^4]: Yee Seng Chan and Dan Roth. Exploiting syntactico-semantic structures for relation extraction. In Proceedings of the 49th Annual Meeting of the Association for Computational Linguistics: Human Language Technologies-Volume 1, pages 551–560. Association for Computational Linguistics, 2011.
[^5]: Nanda Kambhatla. Minority vote: at-least-n voting improves recall for extracting relations. In Proceedings of the COLING/ACL on Main conference poster sessions, pages 460–466. Association for Computational Linguistics,2006.
[^6]: Raymond J Mooney and Razvan C Bunescu. Subsequence kernels for relation extraction. In Advances in neural information processing systems, pages 171–178, 2005.
[^7]: Aron Culotta and Je↵rey Sorensen. Dependency tree kernels for relation extraction. In Proceedings of the 42nd Annual Meeting on Association for Computational Linguistics, page 423. Association for Computational Linguistics, 2004.
[^8]: Dmitry Zelenko, Chinatsu Aone, and Anthony Richardella. Kernel methods for relation extraction. The Journal of Machine Learning Research, 3:1083–1106, 2003.
[^9]:  Razvan C Bunescu and Raymond J Mooney. A shortest path dependency kernel for relation extraction. In Proceedings of the conference on Human Language Technology and Empirical Methods in Natural Language Processing, pages 724–731. Association for Computational Linguistics, 2005.