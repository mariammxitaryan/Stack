#include "stackHeader.hpp"

template <typename T>
Stack<T>::Node::Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

template <typename T>
Stack<T>::iterator::iterator(Stack<T>::Node* ptr) : node_ptr(ptr) { }

template <typename T>
typename Stack<T>::iterator::reference Stack<T>::iterator::operator*() const {
    return node_ptr->data;
}

template <typename T>
typename Stack<T>::iterator::pointer Stack<T>::iterator::operator->() const {
    return &node_ptr->data;
}

template <typename T>
typename Stack<T>::iterator& Stack<T>::iterator::operator++() {
    node_ptr = node_ptr->next;
    return *this;
}

template <typename T>
typename Stack<T>::iterator& Stack<T>::iterator::operator--() {
    node_ptr = node_ptr->prev;
    return *this;
}

template <typename T>
typename Stack<T>::iterator Stack<T>::iterator::operator++(int) {
    typename Stack<T>::iterator it = *this;
    node_ptr = node_ptr->next;
    return it;
}

template <typename T>
typename Stack<T>::iterator Stack<T>::iterator::operator--(int) {
    typename Stack<T>::iterator it = *this;
    node_ptr = node_ptr->prev;
    return it;
}

template <typename T>
bool Stack<T>::iterator::operator==(const typename Stack<T>::iterator& other) const {
    return node_ptr == other.node_ptr;
}

template <typename T>
bool Stack<T>::iterator::operator!=(const typename Stack<T>::iterator& other) const {
    return node_ptr != other.node_ptr;
}

template <typename T>
Stack<T>::const_iterator::const_iterator(typename Stack<T>::Node* ptr) : node_ptr(ptr) {}

template <typename T>
typename Stack<T>::const_iterator::reference Stack<T>::const_iterator::operator*() const {
    return node_ptr->data;
}

template <typename T>
typename Stack<T>::const_iterator::pointer Stack<T>::const_iterator::operator->() const {
    return &node_ptr->data;
}

template <typename T>
Stack<T>::const_iterator& Stack<T>::const_iterator::operator++() {
    node_ptr = node_ptr->next;
    return *this;
}

template <typename T>
typename Stack<T>::const_iterator& Stack<T>::const_iterator::operator--() {
    node_ptr = node_ptr->prev;
    return *this;
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::const_iterator::operator++(int) {
    Stack<T>::const_iterator it = *this;
    node_ptr = node_ptr->next;
    return it;
}

template <typename T>
Stack<T>::const_iterator Stack<T>::const_iterator::operator--(int) {
    Stack<T>::const_iterator it = *this;
    node_ptr = node_ptr->prev;
    return it;
}

template <typename T>
bool Stack<T>::const_iterator::operator==(const typename Stack<T>::const_iterator& other) const {
    return node_ptr == other.node_ptr;
}

template <typename T>
bool  Stack<T>::const_iterator::operator!=(const typename Stack<T>::const_iterator& other) const {
    return node_ptr != other.node_ptr;
}

template <typename T>
Stack<T>::Stack() : head(nullptr), stack_size(0) { }

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
void Stack<T>::push(const T& value) {
    typename Stack<T>::Node* new_node = new typename Stack<T>::Node(value);
    if (!head) {
        head = new_node;
    }
    else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    ++stack_size;
}

template <typename T>
void Stack<T>::push_range(std::initializer_list<T> iStack) {
    for (const auto& elem : iStack) {
        push(elem);
    }
}

template <typename T>
template <typename... Args>
void Stack<T>::emplace(Args&&... args) {
    push(T(std::forward<Args>(args)...));
}

template <typename T>
void Stack<T>::swap(Stack& other) {
    std::swap(head, other.head);
    std::swap(stack_size, other.stack_size);
}

template <typename T>
void Stack<T>::pop() {
    if (!head) {
        throw std::out_of_range("Stack is empty. Cannot pop.");
    }
    typename Stack<T>::Node* tmp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        head = nullptr; 
    }
    delete tmp;
    --stack_size;
}


template <typename T>
typename Stack<T>::reference Stack<T>::top() {
    if (!head) {
        throw std::out_of_range("Stack is empty. Cannot access top.\n");
    }
    return head->data;
}

template <typename T>
bool Stack<T>::empty() const {
    return head == nullptr;
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
    return stack_size;
}

template <typename T>
void Stack<T>::clear() {
    while (head) {
        typename Stack<T>::Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    stack_size = 0;
}

template <typename T>
typename Stack<T>::iterator Stack<T>::begin() {
    return typename Stack<T>::iterator(head);
}

template <typename T>
typename Stack<T>::iterator Stack<T>::end() {
    return typename Stack<T>::iterator(nullptr);
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::cbegin() const {
    return typename Stack<T>::const_iterator(head);
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::cend() const {
    return typename Stack<T>::const_iterator(nullptr);
}
