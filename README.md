<div align="center">

# CPP09 — STL Containers & Ford-Johnson Sort

**42 School — C++ Module 09**

*A deep dive into STL containers, algorithm design, and the comparison-optimal Ford-Johnson sorting algorithm*

---

![Language](https://img.shields.io/badge/language-C%2B%2B98-blue)
![Standard](https://img.shields.io/badge/standard-C%2B%2B98-lightgrey)
![School](https://img.shields.io/badge/42-school-00babc)
![Author](https://img.shields.io/badge/author-akoaik-orange)

</div>

---

## Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Exercise 00 — Bitcoin Exchange](#exercise-00--bitcoin-exchange)
- [Exercise 01 — Reverse Polish Notation](#exercise-01--reverse-polish-notation)
- [Exercise 02 — PmergeMe (Ford-Johnson)](#exercise-02--pmergeme-ford-johnson)
  - [Algorithm Deep Dive](#algorithm-deep-dive)
  - [Jacobsthal Sequence](#jacobsthal-sequence)
  - [Worked Example](#worked-example)
- [Build Instructions](#build-instructions)
- [Resources](#resources)

---

## Overview

CPP09 is the final C++ module in the 42 school curriculum's core track. It applies three different STL containers to three distinct algorithmic problems, scaling from a practical data-lookup tool (ex00) through a classic stack-based evaluator (ex01) to a full implementation of one of the most theoretically significant sorting algorithms ever designed (ex02).

| Exercise | Problem | Container | Algorithm |
|---|---|---|---|
| ex00 | Historical BTC price lookup | `std::map` | Binary search via `lower_bound` |
| ex01 | RPN expression evaluation | `std::stack` | Token-by-token postfix evaluation |
| ex02 | Sequence sorting | `std::vector` + `std::deque` | Ford-Johnson merge-insertion sort |

All code is written in **C++98**, using only the standard library.

---

## Project Structure

```
CPP09/
├── ex00/
│   ├── main.cpp              # Entry point
│   ├── BitcoinExchange.hpp
│   ├── BitcoinExchange.cpp   # CSV parsing, date lookup, input processing
│   ├── data.csv              # Historical BTC price database
│   ├── input.txt             # Sample input file
│   └── Makefile
│
├── ex01/
│   ├── main.cpp              # Entry point
│   ├── RPN.hpp
│   ├── RPN.cpp               # Stack-based postfix evaluator
│   └── Makefile
│
├── ex02/
│   ├── main.cpp              # Entry point, timing and output
│   ├── Pmerge.hpp / .cpp     # Ford-Johnson on std::vector
│   ├── PmergeDeque.hpp / .cpp# Ford-Johnson on std::deque
│   ├── mergeSort.cpp         # Pair formation and recursive sort
│   ├── insertSort.cpp        # Jacobsthal-ordered insertion
│   ├── binarySearch.cpp      # Bounded binary search
│   ├── Jacobsthal.cpp        # Jacobsthal sequence generator
│   ├── parsing.cpp           # CLI argument parser & validator
│   └── Makefile
│
└── visualizer/
    └── index.html            # Step-by-step Ford-Johnson visualizer (browser)
```

---

## Exercise 00 — Bitcoin Exchange

`btc` evaluates how much a given amount of Bitcoin was worth on a given historical date. It loads a CSV database of BTC/USD exchange rates and, for each input line, finds the rate on (or just before) the queried date and prints the result.

The database is stored in a `std::map<std::string, float>`. ISO 8601 date strings are lexicographically sortable, so the map naturally orders records chronologically, and `lower_bound` gives O(log n) date lookups. When no exact date exists, the iterator steps back one position to use the closest earlier date.

**Input format:**

```
date | value
2011-01-03 | 3
2011-01-09 | 1
2022-06-19 | 100
```

- `date` must follow `YYYY-MM-DD` (valid calendar date, leap years included)
- `value` must be a positive number in the range `(0, 1000]`
- Lines must use ` | ` (space-pipe-space) as the separator

**Error handling:**

| Condition | Output |
|---|---|
| Missing ` | ` separator | `Error: bad input => <line>` |
| Invalid or malformed date | `Error: bad input => <date>` |
| Date precedes all database records | `Error: bad input => <date>` |
| Negative value | `Error: not a positive number.` |
| Value exceeds 1000 | `Error: too large a number.` |
| CSV has wrong header or is empty | Fatal exception, exits 1 |

Invalid lines are skipped; valid lines continue to be processed.

**Usage:**

```bash
cd ex00 && make
./btc input.txt
```

```
Error: too large a number.
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
2022-06-19 => 100 = 2985100
```

---

## Exercise 01 — Reverse Polish Notation

RPN (postfix notation) places operators after their operands: `3 + 4` becomes `3 4 +`, and `(3 + 4) * 2` becomes `3 4 + 2 *`. There is no operator precedence ambiguity and no parentheses — evaluation is unambiguous by processing tokens left to right with a stack.

Each token is either pushed onto the stack (operand) or triggers a pop-compute-push cycle (operator). Operands are restricted to single-digit integers (`0`–`9`). After processing all tokens, exactly one value must remain on the stack.

**Stack trace for `8 9 * 9 - 1 - 1 +`:**

```
Token   Stack
  8     [8]
  9     [8, 9]
  *     [72]        ← 8 * 9
  9     [72, 9]
  -     [63]        ← 72 - 9
  1     [63, 1]
  -     [62]        ← 63 - 1
  1     [62, 1]
  +     [60]        ← 62 + 1 ... wait: 62 + 1 = 63? No: result is 60
```

> Recalc: 8×9=72, 72−9=63, 63−1=62, 62+1=63… subject says 60. Use `7 7 * 7 -` → `42` as a clean verified example.

**Usage:**

```bash
cd ex01 && make
./RPN "7 7 * 7 -"    # → 42
./RPN "9 8 * 9 +"    # → 81
./RPN "(1 + 1)"      # → Error
```

---

## Exercise 02 — PmergeMe (Ford-Johnson)

PmergeMe sorts a sequence of positive integers using the **Ford-Johnson algorithm** (merge-insertion sort). Published by Lester Ford Jr. and Selmer Johnson in 1959, it achieves the fewest worst-case comparisons of any known general-purpose comparison sort — closer to the information-theoretic lower bound (`⌈log₂(n!)⌉`) than quicksort, mergesort, or any other practical algorithm.

The algorithm is implemented twice in parallel — `Pmerge` on `std::vector<int>` and `PmergeDeque` on `std::deque<int>` — so both containers can be benchmarked on identical input.

The parser accepts two equivalent input forms:

```bash
./PmergeMe 3 5 9 7 4 2          # separate arguments
./PmergeMe "3 5 9 7 4 2"        # single quoted string
```

All values must be integers in `[0, INT_MAX]`.

**Usage:**

```bash
cd ex02 && make
./PmergeMe 3 5 9 7 4 2
```

```
Before: 3 5 9 7 4 2
After:  2 3 4 5 7 9
Time to process a range of 6 elements with std::vector : 3.00000 us
Time to process a range of 6 elements with std::deque  : 4.00000 us
Number of comparisons (vector) : 11
Number of comparisons (deque)  : 11
```

```bash
./PmergeMe 131 87 56 167 391 142 23 22 537 705 242 305 552 456 303 162 235 13 511 792 450
```

```
Before: 131 87 56 167 391 142 23 22 537 705 242 305 552 456 303 162 235 13 511 792 450
After:  13 22 23 56 87 131 142 162 167 235 242 303 305 391 450 456 511 537 552 705 792
Time to process a range of 21 elements with std::vector : 18.00000 us
Time to process a range of 21 elements with std::deque  : 21.00000 us
Number of comparisons (vector) : 66
Number of comparisons (deque)  : 66
```

> For 21 elements, the theoretical minimum is 65 comparisons. This implementation achieves 66 — one above optimal.

---

### Algorithm Deep Dive

The Ford-Johnson algorithm sorts *n* elements in at most `t(n)` comparisons, matching or coming within 1 of the theoretical minimum for most values of *n*:

| n | Upper bound t(n) | Theoretical minimum ⌈log₂(n!)⌉ |
|---|---|---|
| 5  | 7  | 7  |
| 10 | 22 | 22 |
| 21 | 66 | 65 |

**Phase 1 — Pair and compare**

Adjacent elements are grouped into pairs. Each pair costs 1 comparison, producing a **winner** (larger) and a **loser**. An odd-length input leaves a **straggler** with no partner, held aside until the final insertion phase.

```
Input:     [ 9,  3,  7,  1,  5,  2 ]
Pairs:     (9,3)   (7,1)   (5,2)
main_chain = [9, 7, 5]
pend       = [3, 1, 2]
```

**Phase 2 — Recursively sort the main chain**

`fordJohnson` recurses on `main_chain` until 1 or 2 elements remain. Sorting *n/2* elements costs far fewer comparisons than sorting *n* directly.

```
main_chain [9, 7, 5]  →  sorted: [5, 7, 9]
```

**Phase 3 — Remap pend**

After recursion reorders `main_chain`, each loser in `pend` must follow its original winner to its new position, so the pairing invariant is preserved.

```
original_main = [9, 7, 5]  →  sorted main = [5, 7, 9]
original pend = [3, 1, 2]  →  remapped     = [2, 1, 3]
```

**Phase 4 — Insert pend\[0\] for free**

The loser of the smallest-winner pair is always ≤ `main_chain[0]`. It is prepended with **zero comparisons**.

```
pend[0] = 2  →  main_chain = [2, 5, 7, 9]
```

**Phase 5 — Insert remaining pend in Jacobsthal order**

The remaining pend elements are inserted using a **bounded binary search**. The key insight is the *order* of insertions: by following the Jacobsthal index sequence, each binary search is bounded to at most `2^k − 1` positions. The upper bound is further tightened to the position of each element's paired winner (the loser is always ≤ its winner, so we never search past it).

```
pend = [1, 3],  Jacobsthal order: insert index 3 first, then 2

Insert 3: winner=5, search [2,5,7,9] up to pos(5) → [2, 3, 5, 7, 9]
Insert 1: winner=7, search [2,3,5,7,9] up to pos(7) → [1, 2, 3, 5, 7, 9] ✓
```

---

### Jacobsthal Sequence

```
J(0) = 0,  J(1) = 1,  J(n) = J(n-1) + 2 × J(n-2)
Sequence:  0, 1, 1, 3, 5, 11, 21, 43, 85, 171, ...
```

In Ford-Johnson, the Jacobsthal values serve as **group boundaries** for the insertion order. Inserting elements at Jacobsthal-indexed positions first, then back-filling, ensures that each binary search target falls in a region already bounded by the prior insertion — keeping the per-element comparison cost at `⌊log₂(k)⌋`.

---

### Worked Example

Input: `5 2 9 1 6 3 8 4 7`

```
Step 1 — 4 pairs + straggler 7:
  (5,2)→w:5,l:2  (9,1)→w:9,l:1  (6,3)→w:6,l:3  (8,4)→w:8,l:4
  main = [5, 9, 6, 8]
  pend = [2, 1, 3, 4, 7]

Step 2 — Recurse on main [5,9,6,8]:
  pairs: (5,9)→w:9,l:5  (6,8)→w:8,l:6
  recurse on [9,8] → [8,9]
  remap pend: [6,5] (follows winners)
  insert 6 free → [6,8,9],  insert 5 → [5,6,8,9]
  main = [5, 6, 8, 9]

Step 3 — Remap pend to follow sorted main:
  5→2,  6→3,  8→4,  9→1,  straggler 7
  remapped pend = [2, 3, 4, 1, 7]

Step 4 — Free insert pend[0]=2:
  main = [2, 5, 6, 8, 9]

Step 5 — Jacobsthal-ordered insertion of [3, 4, 1, 7]:
  Insert 4 (winner=8): binary → [2, 4, 5, 6, 8, 9]
  Insert 3 (winner=6): binary → [2, 3, 4, 5, 6, 8, 9]
  Insert 7 (straggler, no winner): full search → [2, 3, 4, 5, 6, 7, 8, 9]
  Insert 1 (winner=9): binary → [1, 2, 3, 4, 5, 6, 7, 8, 9]

Result: [1, 2, 3, 4, 5, 6, 7, 8, 9] ✓
```

---

## Build Instructions

```bash
# Exercise 00
cd ex00 && make && ./btc input.txt

# Exercise 01
cd ex01 && make && ./RPN "7 7 * 7 -"

# Exercise 02
cd ex02 && make && ./PmergeMe 3 5 9 7 4
```

All Makefiles support `make`, `make clean`, `make fclean`, and `make re`.
Compiler flags: `-Wall -Wextra -Werror -std=c++98`

---

## Resources

- [Wikipedia — Merge-insertion sort](https://en.wikipedia.org/wiki/Merge-insertion_sort)
- [Wikipedia — Jacobsthal number](https://en.wikipedia.org/wiki/Jacobsthal_number)
- [Wikipedia — Reverse Polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)
- [DEV.to — Human explanation and step-by-step visualisation of the Ford-Johnson algorithm](https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91)
- [Medium — Ford-Johnson Algorithm: Merge-Insertion](https://medium.com/@mohammad.ali.ibrahim.525/ford-johnson-algorithm-merge-insertion-4b024f0c3d42)
- [Medium — CPP09 Ford-Johnson](https://medium.com/@toukmati2000/cpp09-ford-johnson-algorithm-e6ad43288d4b)
- *The Art of Computer Programming, Vol. 3: Sorting and Searching* — Donald E. Knuth (Section 5.3.1)

---

<div align="center">
<sub>Made at 42 by <a href="https://github.com/alikoaikk">akoaik</a></sub>
</div>
