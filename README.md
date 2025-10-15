# 🧩 Small Problem Solutions

This repository is a collection of solutions to various small programming and algorithmic problems. Each problem is contained within its own file. Some problems are solved in more than pone programming language

---

## 📝 Problem Index

| Problem File | Language | Description |
| :--- | :--- | :--- |
| `droneOptimization.py` | Python, C | Finds the minimum flight time for two drones that deliver packages. |

---

## 💡 Problem Explanations

### `droneOptimization`

**The Problem:** Two drones must deliver packages. The first drone must deliver `d1` packages, the second must deliver `d2` packages. Additionally, the first drone must charge at all hours multiple of `c1` and the second at all hours multiples of `c2`. Knowing that they cannot deliver packages at the same time, that all deliveries take 1 hour and all charges also take 1 hour, what's the minimum amount of hours all packages could be delivered in?

**The Solution:** The key to the solution is realizing that every hour at least one drone will be able to deliver a package except those hours where both drones need to charge.
