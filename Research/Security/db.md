# 	SuRF: Practical Range  ery Filtering with Fast Succinct Tries

## 问题：

Item retrieval in an LSM tree-based design

## 以前的解决方法及缺陷：

Bloom  filters 根据key找数据。 只能找一个值，不能找范围。因此要read additional table blocks from disk for range queries.

B+Tree 支持range queries。但 I/O cost 高， 因为LSM设计的时候只考虑了部分prefix Bloom  filters，不够灵活。

RocksDB 希望更灵活，但没有做到

## 论文方案：

Succinct Range Filter (SuRF) 

1. 速度快，提供精确查找、范围查找、近似范围统计
2. 保证one-sided errors
3. 平衡 false positive rate and memory consumption
4. 基于 space-effcient (succinct) data structure called the Fast Succinct Trie (FST). 空间效率高，没有人组合LOUDS-Dense和LOUDS-sparse
5. 将FST转成一个范围，用一些suffix bits替换trie
6. succinct的意思是 生成树 占用的空间接近information-theoretic lower bound

### FST

上层trie 结点更少，但出现频率更高。因此上层用 bitmap-based encoding scheme(LOUDS-Dense)，结点的查找用arrary lookup，性能好；下层用LOUDS-sparse scheme。

![](http://dl2.iteye.com/upload/attachment/0125/3526/8888956f-88fa-31a7-a1e4-a9e03eddf86a.png)

LOUDS编码ordinal tree，广度优先遍历children生成节点编码(有重复)。用rank&select primitives来查找树：

• rank(k, i): Returns the number of k ∈{0, 1} bits to the left of, and including, position i.
• select(k, i): Given an index i, returns the position of the ith k ∈ {0, 1} bit in the bit string.


assume that both node/child numbers and bit positions are zero-based:

1. Position of the i-th node = select(0,i) + 1
2. Position of the k-th child of the node started at p = select(0,rank(1,p + k)) + 1
3. Position of the parent of the node started at p=select(1,rank(0,p))

![](https://upload-images.jianshu.io/upload_images/2224-de3f04d8c5b3e31a.png?imageMogr2/auto-orient/)

上图bit string：

1110110011001110110110011000011000000

####  LOUDS-Dense

每个trie node有三个大小256的bitmap：

1. D-Labels: 记录有分支d的结点
2. D-HasChild: node 下面还有子节点
3. D-IsPrefixKey: 既是有合法前缀，又是key
4. D-Values: 根据key保存value，按层排序

如果要进行遍历 LOUDS-Dense，我们可以使用之前提到的 rank 和 select 操作。对于 bit 序列 `bs` 来说，我们用 `rank1/select1(bs, pos)` 来表示在 `bs` 上面 pos 的 rank 和 select 操作。譬如，假设 pos 是 D-Labels 上面的当前 bit pos，如果 `D-HasChild[pos] = 1`，那么第一个子节点的 pos 则是 `D-ChildNodePos(pos) = 256 x rank1(D-HasChild, pos)`，而父节点则是 `D-ParentNodePos(pos) = 256 x select1(D-HasChild, pos / 256)`。

#### LOUDS-Sparse

四个byte or bit-sequence编码一个trie node

1. S-Labels: 按照 level order 的方式记录了所有 node 的 label。$表示一个 prefix key
2. S-HasChild: node 下面还有子节点
3. S-LOUDS: label 是第一个节点
4. S-Values: 根据key保存value，按层排序

如果要遍历 LOUDS-Sparse，也是通过 rank 和 select 进行，譬如找到第一个子节点 `S-ChildNodePos(pos) = select1(S-LOUDS, ranks(S-HasChild, pos) + 1)`，而找到父节点则是 `S-ParentNodePos(pos) = select1(S-HasChild, rank1(S-LOUDS, pos) - 1)`。

#### Optimization

提高 rank 和 select 执行的效率，在 SuRF 里面，引入了 LookUp Table（LUT）

