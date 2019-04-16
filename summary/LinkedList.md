## 查找倒数第K个链表

[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
2个指针p, q初始化指向头结点.p先跑到k结点处, 然后q再开始跑, 当p跑到最后跑到尾巴时, q正好到达倒数第k个.复杂度O(n)

## 查找中间结点

[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
设两个初始化指向头结点的指针p, q.p每次前进两个结点, q每次前进一个结点, 这样当p到达链表尾巴的时候, q到达了中间.复杂度O(n)

## 回文链表

找中点，再原地反转链表，并比较是否相等。

## 逆序打印链表

[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
使用递归(即让系统使用栈), 时间复杂度O(n)

## 寻找环形链表

[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
设两个指针p, q, 初始化指向头.p以步长2的速度向前跑, q的步长是1.这样, 如果链表不存在环, p和q肯定不会相遇.如果存在环, p和q一定会相遇.(就像两个速度不同的汽车在一个环上跑绝对会相遇).复杂度O(n)

## 链表中环的入口结点

[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
还是使用俩指针fast和slow, slow扫描的步长为1, fast扫描的步长为2.它们的相遇点在环中间.

那么当fast和slow在meet处相遇的时候, 从head处再发出一个步长为1的指针r, 可以知道, r和slow会在entry处相遇!

```cpp
ListNode *detectCycle(ListNode *head) {
    if (head == NULL) return head;
    
    ListNode *fast = head, *slow = head;
    do {
        if (fast == NULL || fast->next == NULL) return NULL;
        fast = fast->next->next;
        slow = slow->next;
    } while (fast != slow);
    
    slow = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}
```
## 判断两个单链表是否相交

[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
两个指针遍历这两个链表,如果他们的尾结点相同,则必定相交.复杂度O(m+n)

## 找两个链表相交的交点

[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
p,q分别遍历链表a,b,假设q先到达NULL,此时从a的头发出一个指针t,当p到达NULL时,从b的头发出s,当s==t的时候即交点.

## O(1)删除结点(不给头结点)

[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
把d的下一个结点e的数据拷贝到d中,然后删除e

## 两个链表右对齐打印

[算法来源：](https://github.com/hit9/oldblog/blob/gh-pages/blog-src/blog/C/posts/25.mkd)
p和q两个指针分别遍历链表a和b,假如q先到达0(即a比b长),此时由a头发出t,打印完链表a.

p继续移动到0,并打印空格.

从b头发出指针s打印链表b

## 复制带随机指针的链表

```cpp
RandomListNode *copyRandomList(RandomListNode *head) {
    RandomListNode *cur = head, *newhead = new RandomListNode(-1);
    RandomListNode *pre = newhead;
    
    map<RandomListNode*, RandomListNode*> oldtonew;
    while (cur != NULL) {
        RandomListNode *tmp = new RandomListNode(cur->label);
        pre->next = tmp;
        pre = tmp;
        oldtonew[cur] = tmp;
        cur = cur->next;
    }
    pre->next = NULL;
    
    cur = head;
    pre = newhead->next;
    while (cur != NULL) {
        if (cur->random != NULL) {
            pre->random = oldtonew[cur->random];
        }
        cur = cur->next;
        pre = pre->next;
    }
    return newhead->next;
}
```

```java
private void copyNext(RandomListNode head) {
    while (head != null) {
        RandomListNode newNode = new RandomListNode(head.label);
        newNode.random = head.random;
        newNode.next = head.next;
        head.next = newNode;
        head = head.next.next;
    }
}

private void copyRandom(RandomListNode head) {
    while (head != null) {
        if (head.next.random != null) {
            head.next.random = head.random.next;
        }
        head = head.next.next;
    }
}

private RandomListNode splitList(RandomListNode head) {
    RandomListNode newHead = head.next;
    while (head != null) {
        RandomListNode temp = head.next;
        head.next = temp.next;
        head = head.next;
        if (temp.next != null) {
            temp.next = temp.next.next;
        }
    }
    return newHead;
}

public RandomListNode copyRandomList(RandomListNode head) {
    if (head == null) {
        return null;
    }
    copyNext(head);
    copyRandom(head);
    return splitList(head);
}
```

## 重排链表

```
给定链表 1->2->3->4, 重新排列为 1->4->2->3.
给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…
先找中点，翻转后半段，再合并
```

```cpp
void reorderList(ListNode* head) {
    if(!head || !head->next) return;
    ListNode *slow = head, *fast = head, *p=head, *q=head;
    while(fast->next && fast->next->next)
        slow = slow->next, fast = fast->next->next;
    fast = slow->next, slow->next = NULL;
    p = fast, q = fast->next, fast->next = NULL;
    while(q)
    {
        auto tem = q->next;
        q->next = p;
        p = q, q = tem;
    }
    q = head;
    while(q && p)
    {
        auto tem1 = q->next, tem2 = p->next;
        p->next = q->next;
        q->next = p;
        q = tem1, p = tem2;
    }
}
```
## 两数之和

```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    stack<int> s1, s2;
    while (l1) {
        s1.push(l1->val);
        l1 = l1->next;
    }
    while (l2) {
        s2.push(l2->val);
        l2 = l2->next;
    }
    int sum = 0;
    ListNode *res = new ListNode(0);
    while (!s1.empty() || !s2.empty()) {
        if (!s1.empty()) {sum += s1.top(); s1.pop();}
        if (!s2.empty()) {sum += s2.top(); s2.pop();}
        res->val = sum % 10;
        ListNode *head = new ListNode(sum / 10);
        head->next = res;
        res = head;
        sum /= 10;
    }
    return res->val == 0 ? res->next : res;
}
```