*This project has been created as part of the 42 curriculum by akoaik.*

## Description

CPP09 is a C++ module covering three exercises that apply STL containers and algorithms to real problems:

- **ex00 — Bitcoin Exchange:** reads a CSV price database and evaluates a list of dates/values, outputting the equivalent BTC value using `std::map`.
- **ex01 — Reverse Polish Notation:** evaluates mathematical expressions in RPN format using `std::stack`.
- **ex02 — PmergeMe:** sorts a sequence of positive integers using the **Ford-Johnson algorithm** (merge-insertion sort), implemented with both `std::vector` and `std::deque`. The algorithm minimizes the number of comparisons by combining recursive pair sorting, Jacobsthal-ordered insertion, and bounded binary search.

## Instructions

Each exercise has its own `Makefile`. Build and run from the exercise directory:

```bash
# ex00
cd ex00 && make
./btc input.txt

# ex01
cd ex01 && make
./RPN "3 5 8 * 7 - +"

# ex02
cd ex02 && make
./PmergeMe 3 5 9 7 4
```

For **ex02**, pass a sequence of positive integers as arguments. The program prints the unsorted and sorted sequences, processing time for each container, and the total comparison count.

## Library — PmergeMe (ex02)

### `Pmerge` — vector-based Ford-Johnson

| Method | Description |
|---|---|
| `fordJohnson(vec, cmp)` | Sorts `vec` in-place, counting comparisons into `cmp` |
| `binarySearch(arr, target)` | Inserts `target` into `arr` using binary search |
| `makePairs(arr, main, pend, cmp)` | Pairs elements, sorts each pair, splits into main chain and pend |
| `remapPend(main, orig, pend, odd)` | Realigns pend after main is reordered by recursion |
| `insertPend(main, pend, cmp)` | Inserts pend into main in Jacobsthal order |
| `buildInsertOrder(pend_size)` | Returns the Jacobsthal-based insertion index sequence |
| `findInsertPos(arr, target, l, r, cmp)` | Bounded binary search, returns insertion position |
| `jacob_seq(len)` | Generates the Jacobsthal sequence up to length `len` |

### `PmergeDeque` — deque-based Ford-Johnson

Same interface as `Pmerge`, operating on `std::deque<int>`.

## Resources

- [Wikipedia — Reverse Polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)
- [Wikipedia — Jacobsthal number](https://en.wikipedia.org/wiki/Jacobsthal_number)
- [W3Schools — C++ Vectors](https://www.w3schools.com/cpp/cpp_vectors.asp)
- [cppreference — std::pair](https://en.cppreference.com/w/cpp/utility/pair.html)
- [Wikipedia — Merge-insertion sort](https://en.wikipedia.org/wiki/Merge-insertion_sort)
- [Ford-Johnson algorithm — Medium](https://medium.com/@mohammad.ali.ibrahim.525/ford-johnson-algorithm-merge-insertion-4b024f0c3d42)
- [Human explanation and step-by-step visualisation — DEV.to](https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91)
- [CPP09 Ford-Johnson — Medium](https://medium.com/@toukmati2000/cpp09-ford-johnson-algorithm-e6ad43288d4b)
- The Art of Computer Programming, Vol. 3 — Knuth

