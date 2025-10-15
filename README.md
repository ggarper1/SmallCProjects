# 🧩 Small Problem Solutions

This repository is a collection of solutions to various small programming and algorithmic problems. Each problem is contained within its own file. Some problems are solved in more than pone programming language

---

## 📝 Problem Index

| Problem File | Language | Description |
| :--- | :--- | :--- |
| `droneOptimization` | Python, C | Find the minimum flight time for two drones that deliver packages. |
| `smallestInListV1` | C | Find the smallest element in a list thay can be obtained after a certain amount of operations. Easy version. |
| `smallestInListV2` | C | Find the smallest element in a list thay can be obtained after a certain amount of operations. Medium version |
| `smallestInListV3` | C | Find the smallest element in a list thay can be obtained after a certain amount of operations. Harder version |

---

## 💡 Problem Explanations

### `droneOptimization`

**The Problem:** Two drones must deliver packages. The first drone must deliver `d1` packages, the second must deliver `d2` packages. Additionally, the first drone must charge at all hours multiple of `c1` and the second at all hours multiples of `c2`. Knowing that they cannot deliver packages at the same time, that all deliveries take 1 hour and all charges also take 1 hour, what's the minimum amount of hours all packages could be delivered in?

**The Solution:** The key to the solution is realizing that every hour at least one drone will be able to deliver a package except those hours where both drones need to charge.


### `smallestInListV1`

**The Problem:** You're giving a list of positive integers `l` and a int `maxOperations`. You must find the smallest element in the list that can be achieve in `maxOperations` operations. There is only one operation you can perform: choose two elements from the list and append to it the absolute value of their difference. The results of these operations are appended to the list, that means: they can be reused in other operations and they can be chosen as the smallest number of the list.

**The Solution:** The solution is easy if we can repeat operations (apply a operation on the same two numbers twice). The problem is harder if we can't do this, see problem `smallestInListV2`


### `smallestInListV2`

**The Problem:** You're giving a list of positive integers `l` and a int `maxOperations`. You must find the smallest element in the list that can be achieve in `maxOperations` operations. There is only one operation you can perform: choose two elements from the list and append to it the absolute value of their difference. The results of these operations are appended to the list, that means: they can be reused in other operations and they can be chosen as the smallest number of the list. You cannot reuse numbers for operations, that is, if you have applied the operation to the items of the list in position 2 and 5 you can't perform a operation with the number on position 2 nor number on position 5.

**The Solution:** No solution yet

**Example:**
  Input:
    - `l` = [10, 30, 34, 43]
    - `maxOperations` = 3
  Output: 1


### `smallestInListV3`

**The Problem:** You're giving a list of positive integers `l` and a int `maxOperations`. You must find the smallest element in the list that can be achieve in `maxOperations` operations. There is only one operation you can perform: choose two elements from the list and append to it the absolute value of their difference. The results of these operations are appended to the list, that means: they can be reused in other operations and they can be chosen as the smallest number of the list. You cannot reuse the same two numbers for operations, that is, if you have applied the operation to the items of the list in position 2 and 5 you can't perform a operation with the number on position 2 and number on position 5. You can however perform a operation with the number in position 2 and position 3.

**The Solution:** No solution yet

**Example:**
  Input:
    - `l` = [10, 32, 34, 44]
    - `maxOperations` = 3
 
