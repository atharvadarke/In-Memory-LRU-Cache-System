# High-Performance In-Memory LRU Cache System in C++

> A resume-quality C++ project demonstrating **O(1)** get and put operations using a custom doubly linked list and a hash map — no STL `list` used.

---

## Table of Contents
1. [What is an LRU Cache?](#what-is-an-lru-cache)
2. [How It Works](#how-it-works)
3. [Data Structures Used](#data-structures-used)
4. [Time & Space Complexity](#time--space-complexity)
5. [Project Structure](#project-structure)
6. [How to Compile & Run](#how-to-compile--run)
7. [Example Output](#example-output)
8. [Features](#features)

---

## What is an LRU Cache?

An **LRU (Least Recently Used)** cache is a fixed-capacity data structure that automatically evicts the **least recently accessed** entry when the cache is full and a new item needs to be inserted.

**Real-world uses:**
- CPU / hardware caches
- OS page replacement
- Browser / DNS caches
- Database query result caching (e.g., Redis, Memcached)

---

## How It Works

The cache maintains an **access order** internally:

```
head(dummy) ⟷ [LRU node] ⟷ ... ⟷ [MRU node] ⟷ tail(dummy)
```

| Operation | Action |
|-----------|--------|
| `get(key)` | Find node via hash map → **promote** it to MRU end → return value |
| `put(key, value)` – key exists | Update value → **promote** to MRU |
| `put(key, value)` – key new + cache full | **Evict** LRU node → insert new node at MRU |
| `put(key, value)` – key new + cache not full | Insert new node at MRU |

---

## Data Structures Used

### 1. Custom Doubly Linked List (`DoublyLinkedList`)
- Maintains nodes in access-time order (LRU ↔ MRU).
- Dummy `head` and `tail` sentinel nodes eliminate edge-case checks.
- Supports O(1) `addToFront`, `removeNode`, and `removeLRU`.

### 2. Hash Map (`std::unordered_map<int, Node*>`)
- Maps each key directly to its `Node*` in the linked list.
- Provides O(1) average-case lookup, insert, and erase.

### 3. Node Class
- Stores `key`, `value`, `prev*`, `next*`.
- The key is stored in the node so that on eviction the hash map entry can be erased in O(1) without a linear search.

---

## Time & Space Complexity

| Operation | Time Complexity | Reason |
|-----------|:--------------:|---------|
| `get(key)` | **O(1)** | Hash map lookup + O(1) DLL pointer ops |
| `put(key, value)` | **O(1)** | Hash map insert + O(1) DLL pointer ops |
| Eviction (LRU removal) | **O(1)** | Remove head->next + hash map erase by key |

| Resource | Space Complexity |
|----------|:---------------:|
| Overall  | **O(n)** where n = capacity |

---

## Project Structure

```
LRU-Cache/
├── src/
│   ├── Node.h                  # Node class (key, value, prev, next)
│   ├── DoublyLinkedList.h      # DLL declaration
│   ├── DoublyLinkedList.cpp    # DLL implementation (sentinel-based)
│   ├── LRUCache.h              # LRUCache declaration
│   ├── LRUCache.cpp            # LRUCache implementation
│   └── main.cpp                # Demo driver (3 scenarios)
├── tests/
│   └── test_cases.cpp          # 8 unit-style test functions
└── README.md
```

---

## How to Compile & Run

### Requirements
- A C++17-compatible compiler (`g++`, `clang++`, or MSVC)

### Linux / macOS

```bash
# From the LRU-Cache/ directory

# ── Build the demo ──────────────────────────────────────────────────────
g++ -std=c++17 -Wall -Wextra -o lru_demo \
    src/main.cpp src/LRUCache.cpp src/DoublyLinkedList.cpp -I src

./lru_demo

# ── Build & run the test suite ──────────────────────────────────────────
g++ -std=c++17 -Wall -Wextra -o run_tests \
    tests/test_cases.cpp src/LRUCache.cpp src/DoublyLinkedList.cpp -I src

./run_tests
```

### Windows (PowerShell / cmd)

```powershell
# ── Demo ────────────────────────────────────────────────────────────────
g++ -std=c++17 -Wall -Wextra -o lru_demo.exe `
    src/main.cpp src/LRUCache.cpp src/DoublyLinkedList.cpp -I src

.\lru_demo.exe

# ── Tests ───────────────────────────────────────────────────────────────
g++ -std=c++17 -Wall -Wextra -o run_tests.exe `
    tests/test_cases.cpp src/LRUCache.cpp src/DoublyLinkedList.cpp -I src

.\run_tests.exe
```

---

## Example Output

```
>>> put(1, 10) | put(2, 20) | put(3, 30)
>>> get(1)  → 10   (promotes key=1 to MRU)
>>> put(4, 40)   [cache full → evict LRU = key 2]

========================================
  Cache State  (size=3 / capacity=3)
========================================
  Order: [MRU] 4:40 -> 1:10 -> 3:30 [LRU]
========================================

  [LRU] key=3  value=30
  [MRU] key=4  value=40

--- Cache Statistics ---
  Cache Hits:    1
  Cache Misses:  0
  Total Gets:    1
  Hit Rate:      100.0%
```

---

## Features

| Feature | Description |
|---------|-------------|
| **O(1) get / put** | Hash map + DLL pointer arithmetic |
| **Custom DLL** | No STL `list` — raw `Node*` with sentinel guards |
| **Auto eviction** | LRU entry removed when capacity is exceeded |
| **printCache()** | Displays full cache state MRU → LRU |
| **printLRU() / printMRU()** | Identifies boundary nodes in O(1) |
| **printStats()** | Hit count, miss count, hit-rate percentage |
| **Test suite** | 8 test cases; returns exit code 1 on failure |
| **Clean OOP** | Node / DoublyLinkedList / LRUCache cleanly separated |

---

*Built as a resume-level systems programming project demonstrating mastery of pointers, custom data structures, and O(1) algorithm design in C++.*
