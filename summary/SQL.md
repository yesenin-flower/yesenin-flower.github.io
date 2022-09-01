### outer join

```
Input: 
Person table:
+----------+----------+-----------+
| personId | lastName | firstName |
+----------+----------+-----------+
| 1        | Wang     | Allen     |
| 2        | Alice    | Bob       |
+----------+----------+-----------+
Address table:
+-----------+----------+---------------+------------+
| addressId | personId | city          | state      |
+-----------+----------+---------------+------------+
| 1         | 2        | New York City | New York   |
| 2         | 3        | Leetcode      | California |
+-----------+----------+---------------+------------+
Output: 
+-----------+----------+---------------+----------+
| firstName | lastName | city          | state    |
+-----------+----------+---------------+----------+
| Allen     | Wang     | Null          | Null     |
| Bob       | Alice    | New York City | New York |
+-----------+----------+---------------+----------+
Explanation: 
There is no address in the address table for the personId = 1 so we return null in their city and state.
addressId = 1 contains information about the address of personId = 2.
```

```sql
#Combine Two Tables
select FirstName, LastName, City, State
from Person left join Address
on Person.PersonId = Address.PersonId
;

#查找 Customers Who Never Order
select c.lastName as  'Customers' from Person as p  where p.personId not in (select a.personId from Address as a);
```

### IS NULL

```
Input: 
Customer table:
+----+------+------------+
| id | name | referee_id |
+----+------+------------+
| 1  | Will | null       |
| 2  | Jane | null       |
| 3  | Alex | 2          |
| 4  | Bill | null       |
| 5  | Zack | 1          |
| 6  | Mark | 2          |
+----+------+------------+
Output: 
+------+
| name |
+------+
| Will |
| Jane |
| Bill |
| Zack |
+------+
```

```sql
select name from Customer as c where c.referee_id is null or c.referee_id != 2;

#Duplicate Emails
select name from Customer group by referee_id having count(Email) > 1;

select distinct p1.email from Person as p1, Person as p2 where p1.email = p2.email and p1.id != p2.id;

select name from 
( select name, count(referee_id) as num
  from Customer
  group by Customer
) as statistic
where num > 1
;
#delete duplicate
DELETE p1 FROM Person p1, Person p2
WHERE
    p1.Email = p2.Email AND p1.Id > p2.Id
```

### DATEDIFF

```
Input: 
Weather table:
+----+------------+-------------+
| id | recordDate | temperature |
+----+------------+-------------+
| 1  | 2015-01-01 | 10          |
| 2  | 2015-01-02 | 25          |
| 3  | 2015-01-03 | 20          |
| 4  | 2015-01-04 | 30          |
+----+------------+-------------+
Output: 
+----+
| id |
+----+
| 2  |
| 4  |
+----+
Explanation: 
In 2015-01-02, the temperature was higher than the previous day (10 -> 25).
In 2015-01-04, the temperature was higher than the previous day (20 -> 30).
```

```sql
select distinct w1.id From Weather as w1, Weather as w2
where w1.temperature > w2.temperature and DATEDIFF(w1.recordDate, w2.recordDate) = 1;

SELECT
    w1.id AS 'Id'
FROM
    weather as w1
        JOIN
    weather as w2
    		ON DATEDIFF(w1.recordDate, w2.recordDate) = 1
        AND w1.Temperature > w2.Temprature
;
```

### DESC

```
Input: 
Orders table:
+--------------+-----------------+
| order_number | customer_number |
+--------------+-----------------+
| 1            | 1               |
| 2            | 2               |
| 3            | 3               |
| 4            | 3               |
+--------------+-----------------+
Output: 
+-----------------+
| customer_number |
+-----------------+
| 3               |
+-----------------+
Explanation: 
The customer with number 3 has two orders, which is greater than either customer 1 or 2 because each of them only has one order. 
So the result is customer_number 3.
```

```sql
#Customer Placing the Largest Number of Orders
select o.customer_number from Orders as o 
group by o.customer_number
order by count(*) DESC LIMIT 1;

#Calculate Special Bonus
select order_number,if(mod(order_number,2)=1 and customer_number not like "1%",customer_number,0) as bonus  from employees
order by employee_id asc;
```