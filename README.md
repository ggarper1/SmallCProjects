# 🧩 Small Problem Solutions

This repository is a collection of solutions written in C to various small programming and algorithmic problems. Each problem is contained within its own file.

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

### `closestSubsetSum`

**The Problem:** You are given a list of integers and you must find the sum of integers from that list that is most similar to any element from that list.

**The Solution:** Not solved yet


### `smallestInListV1`

**The Problem:** You are given a list of positive integers `l` and an integer `maxOperations` greater than 0. You must find the smallest element that can be achieved in at most `maxOperations` operations. There is only one operation you can perform: choose two elements from the list and append to it the absolute value of their difference. The results of these operations are appended to the list, meaning they can be reused in other operations and can also be considered when finding the smallest number in the list.

**The Solution:** The solution is straightforward if we can repeat operations (i.e., apply the operation on the same two numbers multiple times). The problem becomes harder if we cannot do this; see problem `smallestInListV2`.

### `smallestInListV2`

**The Problem:** You are given a list of positive integers `l` and an integer `maxOperations` greater than 0. You must find the smallest element that can be achieved in at most `maxOperations` operations. There is only one operation you can perform: choose two elements from the list and append to it the absolute value of their difference. The results of these operations are appended to the list, meaning they can be reused in other operations and can also be considered when finding the smallest number in the list. You cannot reuse numbers for operations; that is, if you have applied the operation to the items at positions 2 and 5, you cannot perform another operation using the numbers at positions 2 or 5.

**The Solution:** No solution yet.

**Example:**
Input:
- `l` = [10, 30, 34, 43]
- `maxOperations` = 3
Output: 1

### `smallestInListV3`

**The Problem:** You are given a list of positive integers `l` and an integer `maxOperations` greater than 0. You must find the smallest element that can be achieved in at most `maxOperations` operations. There is only one operation you can perform: choose two elements from the list and append to it the absolute value of their difference. The results of these operations are appended to the list, meaning they can be reused in other operations and can also be considered when finding the smallest number in the list. You cannot reuse the *same pair* of numbers for operations; that is, if you have applied the operation to the items at positions 2 and 5, you cannot perform another operation using the same pair (2, 5). However, you can perform an operation with one of them and a different number (e.g., positions 2 and 3).

**The Solution:** No solution yet.

**Example:**
Input:
- `l` = [10, 32, 34, 44]
- `maxOperations` = 3
Output: 0
