[TOC]

# 简单的命令

## Table

```sql
CREATE DATABASE databasename;
DROP DATABASE databasename;
CREATE TABLE table_name (
  ID int NOT NULL,
    column1 datatype,
    column2 datatype,
    column3 datatype,
  PersonID int,
  UNIQUE (ID),
  PRIMARY KEY (ID),
  FOREIGN KEY (PersonID) REFERENCES Persons(PersonID)
   ....
);
DROP TABLE table_name;

ALTER TABLE table_name
ADD column_name datatype;

ALTER TABLE table_name
DROP COLUMN column_name;

ALTER TABLE table_name
MODIFY COLUMN column_name datatype;

```



## Select

```sql
select * from table as t
```

## Insert

```sql
INSERT INTO table_name (column1, column2, column3, ...)
VALUES (value1, value2, value3, ...);

INSERT INTO table2
SELECT * FROM table1
WHERE condition;
```

## Update

```sql
UPDATE table_name
SET column1 = value1, column2 = value2, ...
WHERE condition;
```

```sql
UPDATE salary
SET
    sex = CASE sex
        WHEN 'm' THEN 'f'
        ELSE 'm'
    END;
```

## Delete

```sql
DELETE FROM table_name WHERE condition;
```

# 条件

##Where 

```
=								Equal	
>								Greater than	
<								Less than	
>=							Greater than or equal	
<=							Less than or equal
<>							Not equal. Note: In some versions of SQL this operator may be written as !=	
BETWEEN	AND			Between a certain range	
IN							To specify multiple possible values for a column
AND
OR
NOT
IS NULL
IS NOT NULL
```

## Order by

```sql
SELECT column1, column2, ...
FROM table_name
ORDER BY column1, column2, ... ASC|DESC;
```

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

#Not Boring Movies
select * from Cinema as c where mod(c.id, 2) = 1 and c.description != "boring" order by c.rating DESC;
```

## Limit

```sql
SELECT column_name(s)
FROM table_name
WHERE condition
LIMIT number;
```

## Like

```
%	Represents zero or more characters
_	Represents a single character
WHERE CustomerName LIKE 'a%'		Finds any values that start with "a"
WHERE CustomerName LIKE '%a'		Finds any values that end with "a"
WHERE CustomerName LIKE '%or%'	Finds any values that have "or" in any position
WHERE CustomerName LIKE '_r%'		Finds any values that have "r" in the second position
WHERE CustomerName LIKE 'a_%'		Finds any values that start with "a" and are at least 2 characters in length
WHERE CustomerName LIKE 'a__%'	Finds any values that start with "a" and are at least 3 characters in length
WHERE ContactName LIKE 'a%o'		Finds any values that start with "a" and ends with "o"
```

## IS NULL

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

select actor_id, director_id from ActorDirector group by actor_id, director_id having count(*) >= 3;
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

## IFNULL()

```sql
SELECT ProductName, UnitPrice * (UnitsInStock + IFNULL(UnitsOnOrder, 0))
FROM Products;
```



## Join

![Screen Shot 2022-09-13 at 1.40.30 PM](https://tva1.sinaimg.cn/large/e6c9d24egy1h65i3nc89dj21cm0fa41o.jpg)

```sql
SELECT column_name(s)
FROM table1
INNER JOIN table2
ON table1.column_name = table2.column_name;
```

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

## Union

```sql
SELECT column_name(s) FROM table1
UNION
SELECT column_name(s) FROM table2;

# The UNION operator selects only distinct values by default. To allow duplicate values, use UNION ALL
SELECT column_name(s) FROM table1
UNION ALL
SELECT column_name(s) FROM table2;
```

## group by

```sql
SELECT column_name(s)
FROM table_name
WHERE condition
GROUP BY column_name(s)
ORDER BY column_name(s);
```

## HAVING

```sql
#The HAVING clause was added to SQL because the WHERE keyword cannot be used with aggregate functions.
SELECT column_name(s)
FROM table_name
WHERE condition
GROUP BY column_name(s)
HAVING condition
ORDER BY column_name(s);
```

## Exist

```sql
#The EXISTS operator is used to test for the existence of any record in a subquery.
#The EXISTS operator returns TRUE if the subquery returns one or more records.
SELECT column_name(s)
FROM table_name
WHERE EXISTS
(SELECT column_name FROM table_name WHERE condition);
```

## Any ALL

```sql
#The ANY operator:
#returns a boolean value as a result
#returns TRUE if ANY of the subquery values meet the condition

SELECT column_name(s)
FROM table_name
WHERE column_name operator ANY
  (SELECT column_name
  FROM table_name
  WHERE condition);
  
#The ALL operator:
#returns a boolean value as a result
#returns TRUE if ALL of the subquery values meet the condition
#is used with SELECT, WHERE and HAVING statements
SELECT ALL column_name(s)
FROM table_name
WHERE condition;

SELECT column_name(s)
FROM table_name
WHERE column_name operator ALL
  (SELECT column_name
  FROM table_name
  WHERE condition);
```

```sql
SELECT ProductName
FROM Products
WHERE ProductID = ANY
  (SELECT ProductID
  FROM OrderDetails
  WHERE Quantity = 10);
```

## Case

```sql
CASE
    WHEN condition1 THEN result1
    WHEN condition2 THEN result2
    WHEN conditionN THEN resultN
    ELSE result
END;


select user_id  as buyer_id, join_date, COUNT(CASE WHEN YEAR(order_date) = 2019 THEN 1 END) as orders_in_2019
from Users as u left join orders as o 
on u.user_id = o.buyer_id 
group by user_id
```

## MIN MAX

```sql
SELECT MIN(column_name), MAX(name)
FROM table_name
WHERE condition;
```

## Count AVG SUM

```sql
SELECT COUNT(column_name), AVG(column_name), SUM(column_name)
FROM table_name
WHERE condition;
```

#Others

## DATE

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

#511. Game Play Analysis I
select player_id, min(event_date) as first_login from Activity group by player_id;
```

## String

```mysql
SELECT user_id, CONCAT(UPPER(SUBSTRING(name,1,1)), LOWER(SUBSTRING(name,2))) as name
FROM Users
ORDER BY user_id;

SELECT a.sell_date, COUNT(DISTINCT a.product) AS num_sold,
GROUP_CONCAT(DISTINCT a.product ORDER BY a.product) as products
FROM Activities a
GROUP By sell_date
ORDER BY sell_date;

select patient_id, patient_name, conditions from Patients 
where conditions LIKE 'DIAB1%' OR conditions LIKE '% DIAB1%';
```

