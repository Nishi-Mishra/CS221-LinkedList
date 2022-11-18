#pragma once

#include <cstddef> // size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if
#include <iostream>
using std::cout, std::endl; 

template <class T>
class List {
    private:
    struct Node { // NODE DEFINED HERE !
        Node *next, *prev;
        T data;
        explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev} {}
        explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{data} {}
        explicit Node(T&& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = pointer_type;
        using reference         = reference_type;
    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node* node;

        explicit basic_iterator(Node* ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node* ptr) noexcept : node{const_cast<Node*>(ptr)} {}

    public:
        basic_iterator() : node{nullptr}{}; // changed 
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const {
            return this->node->data; // value of the data 
        }
        pointer operator->() const {
            return &(this->node->data); // pointer to data  
        }

        // Prefix Increment: ++a
        basic_iterator& operator++() {
            node = node->next; 
            return *this; 
        }
        // Postfix Increment: a++
        basic_iterator operator++(int) {
            basic_iterator node_old{node}; 
            node = node->next; 
            return node_old; 
        }
        // Prefix Decrement: --a
        basic_iterator& operator--() {
            node = node->prev; 
            return *this; 
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int) {
            basic_iterator node_old{node}; 
            node = node->prev; 
            return node_old; 
        }

        bool operator==(const basic_iterator& other) const noexcept {
            return other.node == node; // compare addresses 
        }
        bool operator!=(const basic_iterator& other) const noexcept {
            return other.node != node;
        }
    };

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = basic_iterator<pointer, reference>;
    using const_iterator  = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() : head{nullptr, &tail}, tail{&head, nullptr}, _size{0} { }

    List( size_type count, const T& value ): head{nullptr, &tail}, tail{&head, nullptr}, _size{0} { // FIX HERE  --- test : insert copies 
    
        if (count <= 0) {
            return; 
        }

        //cout << "[DEBUG] count: " << count << endl;

        for (size_t i = 0; i < count; i++) {
            insert(end(), value);
            //cout << "\x1B[93m[DEBUG] Inserting " << value << " at position " << i << ", size = " << _size << "\x1B[0m" << endl;
        }
    }
    explicit List( size_type count ) : head{nullptr, &tail}, tail{&head, nullptr}, _size{0} {
        if (count <= 0) {
            return; 
        }

        for (size_t i = 0; i < count; i++) {
            insert(end(), value_type{}); 
        }
    }
    List( const List& other ) : head{nullptr, &tail}, tail{&head, nullptr}, _size{0}{
        
        Node* curr = other.head.next;

        while (curr != &other.tail) {
            insert(end(), curr->data); 
            curr = curr->next; 
        }

    }
    List( List&& other ) {
        
        if (this == &other) // check self assignment
            return; 

        // make head and tail of the other list point together 
        // put contents inside head / tail in this list 

        // reassign all four points coming off the ends 
        head.next = other.head.next; 
        other.head.next->prev = &head; 
        tail.prev = other.tail.prev; 
        other.tail.prev->next = &tail; 
        
        _size = other._size;  
        
        other.head.next = &other.tail; 
        other.tail.prev = &other.head; 

        other._size = 0; 
        
    }
    ~List() {
        clear(); 
    }
    List& operator=( const List& other ) {
        
        if (this == &other) // check self assignment
            return *this; 

        clear(); 

        Node* curr = other.head.next;
        value_type holder; 

        while (curr != &other.tail) {
            holder = curr->data; 
            insert(end(), holder); 
            curr = curr->next; 
        }

        return *this; 

    }

    List& operator=( List&& other ) noexcept {
        
        if (this == &other) // check self assignment
            return *this; 

        clear(); 
        // simply the list copy constructor 

        head.next = other.head.next; 
        other.head.next->prev = &head; 
        tail.prev = other.tail.prev; 
        other.tail.prev->next = &tail; 
        
        _size = other._size;  
        
        other.head.next = &other.tail; 
        other.tail.prev = &other.head; 

        other._size = 0; 
        return *this; 
    }

    reference front() {
        return head.next->data; 
    }
    const_reference front() const {
        return head.next->data; 
    }
	
    reference back() {
        return tail.prev->data; 
    }
    const_reference back() const {
        return tail.prev->data; 
    }
	
    iterator begin() noexcept {
        return iterator(head.next); 
    }
    const_iterator begin() const noexcept {
        return const_iterator(head.next); 
    }
    const_iterator cbegin() const noexcept {
        return const_iterator(head.next); 
    }

    iterator end() noexcept {
        return iterator(&tail); 
    }
    const_iterator end() const noexcept {
        return const_iterator(&tail); 
    }
    const_iterator cend() const noexcept {
        return const_iterator(&tail); 
    }

    bool empty() const noexcept {
        return _size==0;  
    }

    size_type size() const noexcept {
        return _size; 
    }

    void clear() noexcept {
        if (empty()) {
            return; 
        }

        Node* curr = head.next; 
        while (curr != &tail) { // curr is pointer and tail is not pointer
            curr = curr->next; 
            delete curr->prev; 
        }
        head.next = &tail; 
        tail.prev = &head; 
        _size = 0; 
    }

    iterator insert( const_iterator pos, const T& value ) {
        Node* newNode = new Node(value, pos.node->prev, pos.node); 
        pos.node->prev->next = newNode; 
        pos.node->prev = newNode;  
        _size++; 
        return iterator(newNode);
    }
    iterator insert( const_iterator pos, T&& value ) {
        Node* newNode = new Node(std::move(value), pos.node->prev, pos.node); 
        pos.node->prev->next = newNode; 
        pos.node->prev = newNode;  
        _size++; 
        return iterator(newNode);
    }

    iterator erase( const_iterator pos ) {
        Node* currNode = pos.node; 
        currNode->next->prev = currNode->prev; 
        currNode->prev->next = currNode->next;   
        iterator retNode{currNode->next}; 
        delete currNode; 
        _size--; 

        return retNode; 
    }

    void push_back( const T& value ) {
        insert(end(), value); 
    }
    void push_back( T&& value ) {
        insert(end(), std::move(value)); 
    }

    void pop_back() {
        
        if (_size != 0) 
            erase(iterator(tail.prev)); 

    }
	
    void push_front( const T& value ) {
        insert(begin(), value); 
    }
	void push_front( T&& value ) {
        insert(begin(), std::move(value)); 
    }

    void pop_front() {
        if (_size != 0) {
            erase(begin());
        }
    }

    /*
      You do not need to modify these methods!
      
      These method provide the non-const complement 
      for the const_iterator methods provided above.
    */
    iterator insert( iterator pos, const T & value) { 
        return insert((const_iterator &) (pos), value);
    }

    iterator insert( iterator pos, T && value ) {
        return insert((const_iterator &) (pos), std::move(value));
    }

    iterator erase( iterator pos ) {
        return erase((const_iterator&)(pos));
    }
};


/*
    You do not need to modify these methods!

    These method provide a overload to compare const and 
    non-const iterators safely.
*/
 
namespace {
    template<typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator, 
            Iter
        >{} && std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
            ConstIter
        >{}, T>::type;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) == rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) == lhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) != rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) != lhs;
}