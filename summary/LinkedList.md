
# 查找倒数第K个链表
[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
2个指针p, q初始化指向头结点.p先跑到k结点处, 然后q再开始跑, 当p跑到最后跑到尾巴时, q正好到达倒数第k个.复杂度O(n)


# 查找中间结点
[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
设两个初始化指向头结点的指针p, q.p每次前进两个结点, q每次前进一个结点, 这样当p到达链表尾巴的时候, q到达了中间.复杂度O(n)

# 逆序打印链表
[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
使用递归(即让系统使用栈), 时间复杂度O(n)

# 寻找环形链表
[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
设两个指针p, q, 初始化指向头.p以步长2的速度向前跑, q的步长是1.这样, 如果链表不存在环, p和q肯定不会相遇.如果存在环, p和q一定会相遇.(就像两个速度不同的汽车在一个环上跑绝对会相遇).复杂度O(n)

# 链表中环的入口结点
[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
还是使用俩指针p和q, p扫描的步长为1, q扫描的步长为2.它们的相遇点在环中间.\\
那么当p和q在meet处相遇的时候, 从head处再发出一个步长为1的指针r, 可以知道, r和q会在entry处相遇!

# 判断两个单链表是否相交
[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
两个指针遍历这两个链表,如果他们的尾结点相同,则必定相交.复杂度O(m+n)

# 找两个链表相交的交点
[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
p,q分别遍历链表a,b,假设q先到达NULL,此时从a的头发出一个指针t,当p到达NULL时,从b的头发出s,当s==t的时候即交点.

# O(1)删除结点(不给头结点)
[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
把d的下一个结点e的数据拷贝到d中,然后删除e

# 两个链表右对齐打印
[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
p和q两个指针分别遍历链表a和b,假如q先到达0(即a比b长),此时由a头发出t,打印完链表a.

p继续移动到0,并打印空格.

从b头发出指针s打印链表b

