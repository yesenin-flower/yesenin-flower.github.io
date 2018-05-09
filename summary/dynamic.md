# [ 打家劫舍](http://www.cnblogs.com/grandyang/p/4383632.html)

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

dp[i] = max(num[i] + dp[i - 2], dp[i - 1])