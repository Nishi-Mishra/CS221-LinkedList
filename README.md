# Linked Lists
In this assignment, you will program a Doubly Linked List class called `List` which parodies the [`std::list`](https://en.cppreference.com/w/cpp/container/list) class inherent to the Standard Template Library (STL) in C++.

Topics:

- Allocation (`new`) and Deallocation (`delete`)
- Stack and Heap Memory
- Bidirectional Iterators
  - Simplification of Random Access Iterators

The difficulty of the assignment is very close to that of the `Vector` assignment. You do not need to write as many functions, but there is much more nuanced work with the inner class `List::Node`.

A linked list consists of a sequence of data members in memory. Rather than maintaining adjacent elements in one contiguous memory block, a link list is a sequence of memory blocks each containing a data member and the memory location of the next memory block in the sequence. These memory blocks are often referred to as “nodes.” In C/C++, nodes are structs or classes containing a pointer (memory address) of the next node as well as a data member. Doubly linked lists also contain a pointer to the previous node in the list to permit bidirectional iteration.

## Suggested Implementation using Sentinel Nodes

There are several strategies for implementing linked lists. While any strategy conforming to the `std::list` API will be accepted, we recommend implementing the doubly-linked list using "sentinel nodes."  (The function descriptions under "Doubly Linked List Implementation" also assume the use of sentinel nodes.) In the starter code, the `List::Node` struct represents a single node in the list. Each node contains three members: `next` is a pointer to the next node in the sequence, `prev` is a pointer to the previous node in the sequence, and `data` is the data member stored in the current node. The data nodes will contain all three fields. The only exception to this is the sentinel nodes. Sentinel nodes are extra “dummy” nodes which are added before the first data node and after the last data node. While these denote the start and end of the collection, they do not themselves contain any data. (The data member can be left uninitialized.) A good analogy of this is bookends, in which the bookends are on both ends of a book collection, but are not books in the collection. When the list is first initialized, the `head`’s `next` pointer should point to the `tail` and the `tail`’s and `tail`’s previous pointer should point to the `head`. The `head` and `tail` are allocated along with the List collection since they are always present. As items are added, they will be added between the head and tail to maintain a fully linked list.

## Table of Contents
[Getting Started](#getting-started)

[Assignment](#assignment)

- [Doubly Linked List Implementation](#doubly-linked-list-implementation)

- [Implement the List's Iterator](#implement-the-lists-iterator)

- [Shuffling Cards (Application of Doubly Linked List)](#shuffling-cards-application-of-doubly-linked-list)

[Incremental Testing](#incremental-testing)

[Run Tests](#run-tests)

[Turn In](#turn-in)

## Getting started
Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-list.git && cd leyk-csce221-assignment-list
```
Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.
## Assignment
### Doubly Linked List Implementation
Implement the following [constructors](https://en.cppreference.com/w/cpp/container/list/list), [destructors](https://en.cppreference.com/w/cpp/container/list/%7Elist), and assignment operators [`operator=`](https://en.cppreference.com/w/cpp/container/list/operator%3D) which include the Rule of 5:

----
`List()` - **Default constructor**

**Description:** Constructs an empty linked list. In an empty linked list, `head` and `tail` should point to each other.

**Complexity: O(1)**

**Used in:** `constructor_default`, `insert`, `push_front`, `terminals`

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`List( size_type count, const T& value )`

**Description:** Constructs a linked list with `count` copies of elements with value `value`.

**Complexity: O(`count`)**

**Used in:** `constructor_insert_copies`, `clear_and_empty`

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`explicit List( size_type count )`

**Description:** Constructs a linked list with `count` default-inserted instances of `T`. No copies are made.

**Complexity: O(`count`)**

**Used in:** `constructor_default_inserted` & Frequently Utilized

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`List( const List& other )` - **Copy constructor** 

**Description:** Constructs a linked list with a **copy** of the contents of `other`.

**Complexity: O(`other.size()`)**

**Used in:** `constructor_copy`, `build_deck`, `shuffle`

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`List( List&& other )` - **Move constructor**

**Description:** Constructs a linked list with the contents of `other` using move semantics (i.e. the data in `other` is moved from `other` into this container). No new nodes should be made. `other` should be left in an empty state after. To call the move constructor, you can use `List<type> list1 = std::move(list2);`.

**Complexity: O(1)**

**Used in:** `constructor_move`

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`~List()` - **Destructor**

**Description:** The destructors of the elements are called and the used storage is deallocated. Note, that if the elements are pointers, the pointed-to objects are not destroyed.

**Complexity: O(`size()`)**

**Used in:** Frequently Utilized

**Link:** https://en.cppreference.com/w/cpp/container/list/%7Elist

----
`List& operator=( const List& other )` - **Copy assignment operator** 

**Description:** Replaces the linked list with a copy of the contents of `other`.

**Complexity: O(max(`size()`, `other.size()`))**

**Used in:** `operator_copy`

**Link:** https://en.cppreference.com/w/cpp/container/list/operator%3D

----
`List& operator=( List&& other ) noexcept` - **Move assignment operator** 

**Description:** Replaces the linked list with the contents of `other` using move semantics (i.e. the data in `other` is moved from `other` into this container). No new nodes should be made. `other` should be left in an empty state after. To call the move assignment operator, you can use `list1 = std::move(list2);`.

**Complexity: O(`size()`)**

**Used in:** `operator_move`

**Link:** https://en.cppreference.com/w/cpp/container/list/operator%3D

----

#### Implement the following functions for `List`:

----
`reference front()` and `const_reference front() const`

**Description:** Accesses the first element of the linked list.

**Complexity: O(1)**

**Used in:** `terminals`, `shuffle`

**Link:** https://en.cppreference.com/w/cpp/container/list/front

----
`reference back()` and `const_reference back() const`

**Description:** Accesses the last element of the linked list.

**Complexity: O(1)**

**Used in:** `terminals`, `shuffle`

**Link:** https://en.cppreference.com/w/cpp/container/list/back

----
`iterator begin()` and `const_iterator begin() const noexcept`

**Description:** Returns an iterator (or const iterator) to the first element of the linked list. Returns an iterator to `tail` if empty.

**Complexity: O(1)**

**Used in:** `terminals` & Frequently Utilized

**Link:** https://en.cppreference.com/w/cpp/container/list/begin

----
`iterator end()` and `const_iterator end() const noexcept`

**Description:** Returns an iterator (or const iterator) to the end of the list (`tail`).

**Complexity: O(1)**

**Used in:** `terminals` & Frequently Utilized

**Link:** https://en.cppreference.com/w/cpp/container/list/end

----
`const_iterator cbegin() const noexcept`

**Description:** Returns a const iterator to the first element of the linked list. Returns a const iterator to `tail` if empty.

**Complexity: O(1)**

**Used in:** `terminals` & Frequently Utilized

**Link:** https://en.cppreference.com/w/cpp/container/list/begin

----
`const_iterator cend() const noexcept`

**Description:** Returns a const iterator to the end of the list (`tail`).

**Complexity: O(1)**

**Used in:** `terminals` & Frequently Utilized

**Link:** https://en.cppreference.com/w/cpp/container/list/end

----
`bool empty() const noexcept`

**Description:** Checks whether the container is empty.

**Complexity: O(1)**

**Used in:** `clear_and_empty`, `operator_copy_consistency`

**Link:** https://en.cppreference.com/w/cpp/container/list/empty

----
`size_t size() const noexcept`

**Description:** Returns the number of elements.

**Complexity: O(1)**

**Used in:** Frequently Utilized

**Link:** https://en.cppreference.com/w/cpp/container/list/size

----
`void clear() noexcept`

**Description:** Clears the contents of the linked list. The list should be left in an empty state afterwards.

**Complexity: O(`size()`)**

**Used in:** `clear_and_empty`

**Link:** https://en.cppreference.com/w/cpp/container/list/clear

----
`iterator insert(const_iterator pos, const T& value)` and `iterator insert(const_iterator pos, T&& value)`

**Description:** Inserts `value` before `pos` .

**Complexity: O(1)**

**Used in:** `insert`, `operator_copy_consistency`, `operator_move_consistency`

**Link:** https://en.cppreference.com/w/cpp/container/list/insert

----
`iterator erase(const_iterator pos)`

**Description:** Removes the element at `pos`.

**Complexity: O(1)**

**Used in:** `erase`, `operator_copy_consistency`, `operator_move_consistency`

**Link:** https://en.cppreference.com/w/cpp/container/list/erase

----
`void push_back(const T& value)` and `void push_back(T&& value)`

**Description:** Adds `value` to the end of the list.

**Complexity: O(1)**

**Used in:** `push_back`

**Link:** https://en.cppreference.com/w/cpp/container/list/push_back

----
`void pop_back()`

**Description:** Removes the last element of the list.

**Complexity: O(1)**

**Used in:** `pop_back`, `shuffle`

**Link:** https://en.cppreference.com/w/cpp/container/list/pop_back

----
`void push_front(const T& value)` and `void push_front(T&& value)`

**Description:** Inserts `value` at the beginning of the list.

**Complexity: O(1)**

**Used in:** `push_front`

**Link:** https://en.cppreference.com/w/cpp/container/list/push_front

----
`void pop_front()`

**Description:** Removes the first element of the list.

**Complexity: O(1)**

**Used in:** `pop_front`, `shuffle`

**Link:** https://en.cppreference.com/w/cpp/container/list/pop_front

----

### Implement the List's Iterator

Implement `List::basic_iterator` which will create `iterator` and `const_iterator` for you. Write the following functions, which are **different from those of the Random Access Iterator from `Vector`.** If you reuse that code, it will not work at all because the list iterator is a **Bidirectional Iterator**.

#### Implement the following functions for `basic_iterator`:

----
`basic_iterator() noexcept` - Default Constructor

**Description:** Create a default `basic_iterator`.

**Complexity: O(1)**

**Used in:** `iterator`

----
`reference operator*() const`

**Description:** Dereference the pointer, returning a reference to the value in the managed node. **Do not return a reference to the `Node`, but instead return a reference to its managed data.**

**Complexity: O(1)**

**Used in:** Frequently Utilized

----
`pointer operator->() const`

**Description:** Return a pointer to the data managed by `Node`. **Do not return a pointer to the `Node`, but instead return a pointer to its managed data.**

**Complexity: O(1)**

**Used in:** `iterator`, `build_deck`

----
`basic_iterator& operator++()`

**Description:** **Prefix Increment.** Advance the iterator so that it points to the next node in the list. Return a reference to this iterator.

**Complexity: O(1)** 

**Used in:** `iterator` & Frequently Utilized

----
`basic_iterator operator++(int)`

**Decription:** **Postfix Increment.** Advance the iterator so that it points to the next node in the list. Return a copy of the iterator from before it was advanced.

**Complexity: O(1)**

**Used in:** `iterator` & Frequently Utilized

----
`basic_iterator& operator--()`

**Description:** **Prefix Decrement.** Retreat the iterator so that it points to the previous node in the list. Return a reference to this iterator.

**Complexity: O(1)**

**Used in:** `iterator` & Frequently Utilized

----
`basic_iterator operator--(int)`

**Description:** **Postfix Decrement.** Retreat the iterator so that it points to the previous node in the list. Return a copy of the iterator from before it was retreated.

**Complexity: O(1)**

**Used in:** `iterator` & Frequently Utilized

----
`bool operator==(const basic_iterator& other) const noexcept`

**Description:** Compare two iterators and determine if they are equivalent.

**Complexity: O(1)**

**Used in:** `iterator` & Frequently Utilized

----
`bool operator!=(const basic_iterator& other) const noexcept`

**Description:** Compare two iterators and determine if they are not equivalent.

**Complexity: O(1)**

**Used in:** `iterator` & Frequently Utilized

----

A possible implementation (followed by GCC) is to make:
```cpp
auto begin_it = begin(), end_it = end();
--begin_it; ++end_it;
begin_it == end(); // this is true
end_it == begin(); // this is true
```
Thus, the end loops back to the beginning and the beginning back to the end. **You do not have to do this, but it is an approach that you can follow to prevent Segfaults from going off the end of the list.** This form of `List` is very similar to a Circular Linked List.

#### Further Reading
- [Geeks For Geeks Doubly Linked List](https://www.geeksforgeeks.org/doubly-linked-list/)
- [Tutorials Point Double Linked List](https://www.tutorialspoint.com/data_structures_algorithms/doubly_linked_list_algorithm.htm)
- [Wikipedia Doubly Linked List](https://en.wikipedia.org/wiki/Doubly_linked_list)

### Shuffling Cards (Application of Doubly Linked List)

A standard playing card has two main pieces of information:
1. It has a Suit (Spades, Diamonds, Clubs, or Hearts)
2. It has a Number (2 - 10 inclusive) or a Face (Ace, Jack, Queen, King)
   - In many games the order is: Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, and King

We provide for you a `struct Card` in [`Cards.h`](./src/Cards.h) and ask that you implement the following two functions in [`Cards.cpp`](./src/Cards.cpp):

----
`List<Card> buildDeck(std::ifstream file)`

**Description:** Read cards from the file and add them to a `List<Card>` in the order that they are read.

**Complexity: O(n)**

**Used in:** `build_deck`, `shuffle`

----
`List<Card> shuffle(const List<Card>& deck)`

**Description:** Return a new list with the same cards in a shuffled order described [below](#simple-shuffling-algorithm).

**Complexity: O(`deck.size()`)**

**Used in:** `shuffle`

----
#### Simple Shuffling Algorithm
1. Create a new empty deck to which we will add cards as we shuffle them. We henceforth refer to this as the shuffled deck.
2. Iterate over the `deck`, and for each card, flip a coin. The coin flip must be generated using the `rand221` function in `deck.cpp` which is analogous to the [standard C function `rand()`](https://www.cplusplus.com/reference/cstdlib/rand/).
3. If the result is Heads (even), add the card to the front of the shuffled deck; otherwise, add it to the back of the shuffled deck.
4. The `deck` has been completly shuffled when each card has been added. Return this shuffled deck from the `shuffle` function.


## Incremental Testing
 
Unlike `Vector`, elements are not organized contiguously in `List`. This means we can't directly access elements. Instead, elements
must be accessed through the `iterator`. This impacts testing since the correctness of the `iterator` can't be tested independently of
the list itself. There are many possible ways to approach the assignment. Although, there are also many implicit dependencies in the test cases. To minimize test dependencies, we recommend you follow the ordering below. These methods listed in the below steps are explicitly required by the test cases. You may wish to write additional helper methods or implement methods in an alternative order to avoid repetition.
 
### 1. Implement the following methods first:
```cpp
explicit List( size_type count );
~List();
size_t size();
cbegin();
cend();
basic_iterator operator++(int);
basic_iterator& operator--();
reference operator*() const;
bool operator!=(const basic_iterator& other) const noexcept;
```
 
This is the minimal set of methods we need for rigorous testing. With a correct implementation of these methods, you will be able to pass the `constructor_default_inserted` test. 
 
### 2. Flesh out the `iterator`:
 
```cpp
pointer operator->() const;
bool operator==(const basic_iterator& other) const noexcept;
basic_iterator operator--(int);
basic_iterator& operator++();
begin();
end();
```
 
After implementing these methods, you will be able to pass the `iterator` test.
 
### 3. Finish the `List`:
 
At this point, the necessary foundation should exist for you to approach the remaining tests. The functions are listed with their corresponding test cases above. Most will require you to implement a single method on top of this foundation. Notable exceptions include:
 
- The `push` family of methods requires that you implement the default constructor
- `clear` and `empty` are aggregated into a single test
- `front` and `back` are tested in `terminals`
- `operator_copy_consistency` requires `insert`, `erase`, and the copy operator. This serves as a stress test to assert the copy operator leaves the objects in a valid state. The copy operator is also tested independently of `insert` and `erase` in `operator_copy`.
- `operator_move_consistency` requires `insert`, `erase`, and the move operator. Same rationale.
 
### 4. Finish the `Card.cpp` functions
 
`List` is utilized in `Card.cpp` and assumed to be in working condition. The `shuffle` test relies on the `build_deck` method.

## Run Tests
**First consult this guide: [`tests/README.md`](./tests/README.md)**

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `assignment-list` folder to accomplish what you need:

**Build all of the tests**
```sh
make -C tests -j12 build-all
```

**Run the test called `<test-name>`.** Replace `<test-name>` with the name of any `.cpp` file in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run/<test-name>
```

**Run every test** in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run-all -k
```

**Debugging tests** &ndash; For a detailed view, see [./tests/README.md](./tests/README.md).
```sh
make -C tests -j12 build-all -k
cd tests/build
gdb <test-name>
cd ../..
```
> Alex recommends you use `cgdb` which has the same commands as `gdb` but a better user interface. You can install it with `sudo apt install cgdb` on `WSL` or `brew install cgdb` on `MacOS` (provided you have [brew](https://brew.sh))

The first command builds the tests, the next enters the folder where the tests were built. The third invokes `gdb` (**use `lldb` if on Mac OSX**) which is used to debug the program by examining Segmentation Faults and running code line-by-line. Finally, the last command takes you back to the top-level directory.

## Turn In
Submit the following files **and no other files** to Gradescope:
- [ ] [`Cards.cpp`](src/Cards.cpp)
- [ ] [`Cards.h`](src/Cards.h) - You may not have changed this file and that's fine
- [ ] [`List.h`](src/List.h)
