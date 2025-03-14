#include "stackHeader.hpp"

template <typename T>
Stack<T>::Node::Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

template <typename T>
Stack<T>::iterator::iterator(Stack<T>::Node* ptr) : node_ptr(ptr) { }

template <typename T>
typename List<T>::iterator::reference List<T>::iterator::operator*() const {
    return node_ptr->data;
}

template <typename T>
typename List<T>::iterator::pointer List<T>::iterator::operator->() const {
    return &node_ptr->data;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++() {
    node_ptr = node_ptr->next;
    return *this;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--() {
    node_ptr = node_ptr->prev;
    return *this;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++(int) {
    typename List<T>::iterator it = *this;
    node_ptr = node_ptr->next;
    return it;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--(int) {
    typename List<T>::iterator it = *this;
    node_ptr = node_ptr->prev;
    return it;
}

template <typename T>
bool List<T>::iterator::operator==(const typename List<T>::iterator& other) {
    return node_ptr == other.node_ptr;
}

bool List<T>::iterator::operator!=(const typename List<T>::iterator& other) {
    return node_ptr != other.node_ptr;
}

template <typename T>
List<T>::const_iterator::const_iterator(typename List<T>::Node* ptr) : node_ptr(ptr) {}

template <typename T>
typename List<T>::const_iterator::reference List<T>::const_iterator::operator*() const {
    return node_ptr->data;
}

template <typename T>
typename List<T>::const_iterator::pointer List<T>::const_iterator::operator->() const {
    return &node_ptr->data;
}

template <typename T>
List<T>::const_iterator::const_iterator& List<T>::const_iterator::operator++() {
    node_ptr = node_ptr->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--() {
    node_ptr = node_ptr->prev;
    return *this;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++(int) {
    List<T>::const_iterator it = *this;
    node_ptr = node_ptr->next;
    return it;
}

template <typename T>
List<T>::const_iterator::const_iterator& List<T>::const_iterator::operator--(int) {
    List<T>::const_iterator it = *this;
    node_ptr = node_ptr->prev;
    return it;
}

template <typename T>
bool List<T>::const_iterator::operator==(const typename List<T>::const_iterator& other) const {
    return node_ptr == other.node_ptr;
}

template <typename T>
bool  List<T>::const_iterator::operator!=(const typename List<T>::const_iterator& other) const {
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
void Stack<T>::push_range(std::initializer_list<T> ilist) {
    for (const auto& elem : ilist) {
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
        throw std::out_of_range("List is empty");
    }
    typename Stack<T>::Node* tmp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
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
    head = nullptr;
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
