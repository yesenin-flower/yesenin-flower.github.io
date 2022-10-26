[TOC]

# 基本定义

input space $X$

action space $A$   : to predict the number/score; probabilty(number between 0 and 1)

output space $y$   : the final score/ the final label

Decision function   $f(x)$

Loss function $l$ :   $l: A \times y$        or         $l(f(x), y)$



The risk of a Decision function: $R(f) = \mathbb{E}l(f(x), y)$

A bayes decision function: $f* = argmin_fR(f)$

The empricial risk of $f(x)$ with respect to dataset $D_n$: $R_n(f) = \frac{1}{n}\sum_i^nl(f(x_i), y_i)$

empricial risk minimizer(ERM): $\hat{f}_n = argmin_f\frac{1}{n}\sum_i^nl(f(x_i), y_i)$



**Feature Extraction**: One-Hot Encoding

**k-Fold Cross Validation**

**Sample bias**: Test inputs and deployment inputs have different distributions.

**overfitting**: 

```
1. Reducing model complexity 
2. Getting more training data
```

**Hyperparameter control**: 

```
1. model complexity (e.g. polynomial order)
2. type of model complexity control (e.g. L1 vs L2 regularization)
3. optimization algorithm (e.g. learning rate)
4. model type (e.g. loss function, kernel type,...)
```

**Confusion matrix**: Accuracy, Error rate

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h5jn74rmn5j20gs04smx7.jpg" alt="image-20220825155435034" style="zoom: 50%;" />

The **precision** is the accuracy of the positive predictions: $\frac{TP}{(TP + FP)} $

The **recall(True positive rate)** is the accuracy of the positive class: $\frac{TP}{(TP + FN)} $

**False negative rate** is the error rate on the positive class: $\frac{FN }{(FN + TP)}$  (“miss rate”)

**False positive rate** is error rate on the negative class: $\frac{FP}{(FP + TN)} $ (" false alarm rate")

**True negative rate** is accuracy on the negative class: $\frac{TN }{ (FP + TN) }$

**F1** score: =$2 · \frac{precision ·recall}{precision+recall}$  

**Receiver Operating Characteristic (ROC) Curve**

**AUC ROC = area under the ROC curve**

## Regression

Liner models: $y = W^Tx$

Ridge Regression: 

(Tikhonov Form) $\hat{w} = argmin\frac{1}{n}\sum_i(w^Tx_i-y_i)^2+\lambda||w||_2^2$

(Ivanov Form)      $\hat{w} = argmin_{||w||_2^2\leq r}\frac{1}{n}\sum_i(w^Tx_i-y_i)^2$

Lasso Regression: (coefficient = 0, lasso gives feature sparsity)

(Tikhonov Form) $\hat{w} = argmin\frac{1}{n}\sum_i(w^Tx_i-y_i)^2+\lambda||w||_1$

(Ivanov Form)      $\hat{w} = argmin_{||w||_1\leq r}\frac{1}{n}\sum_i(w^Tx_i-y_i)^2$​

**Why L1 regularization is more sparsity than L2?**

contour of L2 is an circle centered at $\hat{w}$; while L1 is a square. 

# 梯度下降

(batch) Gradient Descent: whole dataset

minibatch Gradient Descent: a random subset with size m

Stochasic Gradient Descent: use a single random datapoint to determine the direction

Projected SGD:

Coordinate Descent: insteading updating all entries of $W$, each step update a single $w_i$





Assumption: f is convex & finite 

local/global minimum

Saddles

# Loss function

Robustness: how affected a learning algorithm is by outliers

## Regression

**regression loss usually depend on the residual $r = \hat{y} - y$**

**square loss**: $l(r) = r^2$ (not robust)

**absolute loss**: $l(r) = |r|$ (not differentiable)

**huber loss**: $l(r) =\left\{\begin{matrix}
\frac{1}{2}r^2 & for  |r| < \delta \\ 
\delta(|r|-\frac{1}{2}\delta) & otherwise
\end{matrix}\right.$

Generally, L2 Loss Function is preferred in most of the cases. But when the outliers are present in the dataset, then the squared differences lead to the much larger error. Prefer L1 Loss Function as it is not affected by the outliers or remove the out liers and then use L2 Loss Function.

## Classification

$f(x) \in \{-1, 1\}$

**0-1 loss**: $l(y, \hat{y}) = 1(\hat{y} \neq y)$



$f(x) \in  R$ 

The value of $f(x)$ is th **score** of the input $x$. The magnitude of the score represents the confidence of the prediction.

The **margin** on an example (x, y) is $yf(x)$. It measures how correct we are.

**Most classification loss based on the margin. we wanna maximize the margin.**

**empirical 0-1 loss**: $l(y, \hat{y}) = \frac{1}{n}\sum_i^n1(\hat{y+i}y_i\leq 0)$

**hinge loss**: $l_{hinge} = max(1-yf(x), 0) =(1-yf(x))_+$ (*not differentiable* at 1)

**logistic loss**: $l_{log} = log(1+e^{-m})$

**square loss**: $l_{square} = (f(x) - y)^2$

# [矩阵求导](https://fei-wang.github.io/matrix.html)

# [Convex](https://liyanxu.blog/2018/11/02/overview-svm-optimization/)

convex

concave

可行解

Lagrangian; Lagrange multipliers(dual variables)

Lagrange  dual function



---

1. RL的bellman equation怎么推的，
2. SVM vs logistic regression
3. 描述 logistic regression的loss是什么意思，和cross entropy联系，和MLE的联系
4. 写gradient decent
5. how to avoid overfitting 
6. write L2 norm equation
7. k-fold cross-validation
8. precision, recall, F1 score, 
9. binary classification loss
10. word2vec 
11. adam vs sgd 
12. mean, variance
13. missing data
14. Activation function
15. 先问不平衡分类问题怎么解决，我说了一个cost sensitive，一个对负样本下采样然后ensemble，然后追问ensemble的基本原理，和boosting的区别，简单说rf和gdbt的区别，问了我很多xgboost的细节，会的我就答了，不会的我就说我不记得这一个细节了，最后回过头来问我不平衡问题选什么metric，为什么
16. 然后聊regularization，我举了L0, L1, L2, L_infinity，让我说了首尾两个的定义，对比了一下中间两个，问我什么情况下用什么
17. 然后问我dropout在inference的时候怎么实现
18. batch norm
19. 接着问DL怎么调参，如果要调学习率怎么调，怎么防止很差的局部最优
20. 还问了Q-Learning的具体原理
21. Gaussian Mixture Model (GMM) & Hidden Markov Model (HMM)
22. GRU & LSTM & RNN

----

pandas常见的一些功能, 现在有印象的就是groupby还有sort



