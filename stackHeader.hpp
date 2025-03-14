#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <iterator>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T&);
    };

    Node* head;
    size_t stack_size;

public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node*);
        reference operator*() const;
        pointer operator->() const;
        iterator& operator++();
        iterator& operator--();
        iterator operator++(int);
        iterator operator--(int);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
    private:
        Node* node_ptr;
    };

    class const_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator(Node*);
        reference operator*() const;
        pointer operator->() const;
        const_iterator& operator++();
        const_iterator& operator--();
        const_iterator operator++(int);
        const_iterator operator--(int);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
    private:
        Node* node_ptr;
    };

    Stack();
    ~Stack();
    void push(const T&);
    void push_range(std::initializer_list<T>);

    template <typename... Args>
    void emplace(Args&&...);

    void swap(Stack&);
    void pop();
    reference top();
    bool empty() const;
    size_type size() const;
    void clear();
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
};

#include "stackImplementation.tpp"

#endif