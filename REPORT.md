List Oral Report
================

For the list report, you will be asked three questions to test your conceptual understanding of the assignment. Some questions will expand on the concepts you learned. You will answer orally. We are expecting responses to be precise and concise. 1-3 sentences about each are sufficient. We may ask clarifying questions. Be prepared. (See the list of questions below.) Since we have many reports to complete in a single lab period, the report will be limited to two minutes.

The oral reports will be scored as "exemplary" (5 points), "mostly sufficient," "incomplete," or "insufficient" (0 points). The point value for "mostly sufficient" and "incomplete" will depend on the difficulty of the question. The points will be awarded in the programming assignment category.

Questions seven and five require you to present your code.

Question 1
----------

Consider the following code snippet:

```c++
void f1() {
    List<int> ll;
    ll.push_front(20);
    ll.push_back(30);
}
```

Four nodes are created by the `List` class. (1) Briefly describe the purpose of each node and (2) identify what region of memory where it is stored (stack, heap, text, uninitialized data, or initialized data).

Question 2
----------

Consider the following code snippet, which implements the `List` destructor:

```c++
template <class T>
List<T>::~List() { 
    Node * cursor = head.next;
    while(cursor != &tail) {
        delete cursor;
        cursor = cursor->next;
    }
}
```

This code contains an error. What is the error? How would you fix it?

Question 3
----------

A student is attempting to delete a node from the doubly linked list and writes the following code:

```c++
node->next->prev = node->next;
node->prev->next = node->prev;
delete node;
```
Is this scheme correct? If so, justify why it works. If not, explain the issue with their methodology.

Question 4
----------

A student implements the following move constructor:

```c++
template <class T>
List<T>::List(List && ll) : head{}, tail{}, _size{0} {
    _size = ll._size;
    if(!ll.empty()) {
        head.next = ll.head.next;
        tail.prev = ll.tail.prev;

        ll.head.next = &ll.tail;
        ll.tail.prev = &ll.head;
    } else {
        head.next = &tail;
        tail.prev = &head;
    }
    ll._size = 0;
}
```

The code contains an error. What is the source of this error? Provide a sequence of iterator operations which demonstrate the incorrect behavior.

Question 5
----------

The `List` was implemented with head and tail sentinel nodes that bookend the list. We could have implemented it in a similar (and possibly simpler) fashion using `head` and `tail` pointers as follows:

```c++
template <class T>
class List {
    // Imagine that Node class is defined here
    Node *head, *tail;
    // ...
};
```

What benefit do the `head` and `tail` nodes provide over the above implementation?

Question 6
----------

When dealing with the `Card`s, you shuffled the `deck` using the `shuffle` function. What is the asymptotic running time of the `shuffle` function? You may assume that `rand221` runs in constant time. Justify the running time you suggest. After the deck is shuffled, assuming that it contains *n* cards, what is the time complexity to find the card that was at the **front** of the deck before it was shuffled? What is the time complexity to find the card that was at the **back** of the deck before it was shuffled? Justify these time complexities.

Question 7
----------

What is the runtime of the `pop_back` and `pop_front` functions? If we implemented a singly linked list with a single head pointer, would either of these runtimes change? If not, describe why. If so, describe which runtimes will change and what the new runtime would be.

Question 8
----------

Name at least three functions (or constructors) that call (directly or indirectly) the `insert` function variants. If you do not have three such functions in your code, name three functions that you *could* have implemented in such a manner. Describe an alternate implementation where if you used `insert` (or a derivative of `insert`, e.g. `push_back`), you do not use it and vice-versa.

Name at least two functions that call (directly or indirectly) the `erase` function (or its derivatives, i.e. `pop_back`). If you do not have two such functions in your code, name two functions that you could have implemented in such a manner. Describe an alternate implementation where if you used `erase` (or a derivative of `erase`, e.g. `pop_back`), you do not use it and vice-versa.

The goal of this question is to get you thinking about alternate implementations for the functions in your program.

Question 9
----------

During the report for `assignment-vector` you were provided an example of iterator invalidation. That is when using `Vector`, an `Vector` iterator would point to invalid memory if an operation was performed to reallocate the underlying array. Now consider your implementation of `List`. Which of the following `List` methods *can* result in iterator invalidation? For each method that can result in iterator invalidation, describe the *conditions under which this occurs*.

- `push_back`
- `erase`
- `insert`
- `clear`
- `List& operator=( const List& other );`
- `List& operator=( List&& other ) noexcept;`
