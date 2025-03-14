#include "stackHeader.hpp"

///////////////////////////////////////////////////////////////////////////////
//                          NODE IMPLEMENTATION                              //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs a Node with given value.
 * 
 * @param value The value to store in the node.
 */
template <typename T>
Stack<T>::Node::Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

///////////////////////////////////////////////////////////////////////////////
//                          ITERATOR IMPLEMENTATION                          //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs an iterator pointing to a node.
 * 
 * @param ptr Pointer to the current node.
 */
template <typename T>
Stack<T>::iterator::iterator(Stack<T>::Node* ptr) : node_ptr(ptr) { }

/**
 * @brief Dereferences the iterator to get the node's data.
 * 
 * @return Reference to the data stored in the current node.
 */
template <typename T>
typename Stack<T>::iterator::reference Stack<T>::iterator::operator*() const {
    return node_ptr->data;
}

/**
 * @brief Accesses the data through a pointer.
 * 
 * @return Pointer to the node's data.
 */
template <typename T>
typename Stack<T>::iterator::pointer Stack<T>::iterator::operator->() const {
    return &node_ptr->data;
}

/**
 * @brief Moves iterator to the next node (prefix).
 * 
 * @return Reference to updated iterator.
 */
template <typename T>
typename Stack<T>::iterator& Stack<T>::iterator::operator++() {
    node_ptr = node_ptr->next;
    return *this;
}

/**
 * @brief Moves iterator to the previous node (prefix).
 * 
 * @return Reference to updated iterator.
 */
template <typename T>
typename Stack<T>::iterator& Stack<T>::iterator::operator--() {
    node_ptr = node_ptr->prev;
    return *this;
}

/**
 * @brief Moves iterator to the next node (postfix).
 * 
 * @return Iterator before the increment.
 */
template <typename T>
typename Stack<T>::iterator Stack<T>::iterator::operator++(int) {
    typename Stack<T>::iterator it = *this;
    node_ptr = node_ptr->next;
    return it;
}

/**
 * @brief Moves iterator to the previous node (postfix).
 * 
 * @return Iterator before the decrement.
 */
template <typename T>
typename Stack<T>::iterator Stack<T>::iterator::operator--(int) {
    typename Stack<T>::iterator it = *this;
    node_ptr = node_ptr->prev;
    return it;
}

/**
 * @brief Checks if two iterators are equal.
 */
template <typename T>
bool Stack<T>::iterator::operator==(const typename Stack<T>::iterator& other) const {
    return node_ptr == other.node_ptr;
}

/**
 * @brief Checks if two iterators are not equal.
 */
template <typename T>
bool Stack<T>::iterator::operator!=(const typename Stack<T>::iterator& other) const {
    return node_ptr != other.node_ptr;
}

///////////////////////////////////////////////////////////////////////////////
//                      CONST ITERATOR IMPLEMENTATION                        //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs a constant iterator pointing to a node.
 */
template <typename T>
Stack<T>::const_iterator::const_iterator(typename Stack<T>::Node* ptr) : node_ptr(ptr) {}

/**
 * @brief Dereferences the constant iterator.
 */
template <typename T>
typename Stack<T>::const_iterator::reference Stack<T>::const_iterator::operator*() const {
    return node_ptr->data;
}

/**
 * @brief Accesses data through a pointer (constant).
 */
template <typename T>
typename Stack<T>::const_iterator::pointer Stack<T>::const_iterator::operator->() const {
    return &node_ptr->data;
}

/**
 * @brief Moves constant iterator to the next node (prefix).
 */
template <typename T>
Stack<T>::const_iterator& Stack<T>::const_iterator::operator++() {
    node_ptr = node_ptr->next;
    return *this;
}

/**
 * @brief Moves constant iterator to the previous node (prefix).
 */
template <typename T>
typename Stack<T>::const_iterator& Stack<T>::const_iterator::operator--() {
    node_ptr = node_ptr->prev;
    return *this;
}

/**
 * @brief Moves constant iterator to the next node (postfix).
 */
template <typename T>
typename Stack<T>::const_iterator Stack<T>::const_iterator::operator++(int) {
    Stack<T>::const_iterator it = *this;
    node_ptr = node_ptr->next;
    return it;
}

/**
 * @brief Moves constant iterator to the previous node (postfix).
 */
template <typename T>
Stack<T>::const_iterator Stack<T>::const_iterator::operator--(int) {
    Stack<T>::const_iterator it = *this;
    node_ptr = node_ptr->prev;
    return it;
}

/**
 * @brief Checks if two constant iterators are equal.
 */
template <typename T>
bool Stack<T>::const_iterator::operator==(const typename Stack<T>::const_iterator& other) const {
    return node_ptr == other.node_ptr;
}

/**
 * @brief Checks if two constant iterators are not equal.
 */
template <typename T>
bool Stack<T>::const_iterator::operator!=(const typename Stack<T>::const_iterator& other) const {
    return node_ptr != other.node_ptr;
}

///////////////////////////////////////////////////////////////////////////////
//                          STACK IMPLEMENTATION                             //
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs an empty stack.
 */
template <typename T>
Stack<T>::Stack() : head(nullptr), stack_size(0) { }

/**
 * @brief Destructor - clears the stack.
 */
template <typename T>
Stack<T>::~Stack() {
    clear();
}

/**
 * @brief Pushes an element onto the stack.
 */
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

/**
 * @brief Pushes a range of elements onto the stack.
 */
template <typename T>
void Stack<T>::push_range(std::initializer_list<T> iStack) {
    for (const auto& elem : iStack) {
        push(elem);
    }
}

/**
 * @brief Emplaces an element at the top of the stack.
 */
template <typename T>
template <typename... Args>
void Stack<T>::emplace(Args&&... args) {
    push(T(std::forward<Args>(args)...));
}

/**
 * @brief Swaps contents with another stack.
 */
template <typename T>
void Stack<T>::swap(Stack& other) {
    std::swap(head, other.head);
    std::swap(stack_size, other.stack_size);
}

/**
 * @brief Removes the top element from the stack.
 */
template <typename T>
void Stack<T>::pop() {
    if (!head) {
        throw std::out_of_range("Stack is empty. Cannot pop.");
    }
    typename Stack<T>::Node* tmp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    }
    delete tmp;
    --stack_size;
}

/**
 * @brief Returns the top element of the stack.
 */
template <typename T>
typename Stack<T>::reference Stack<T>::top() {
    if (!head) {
        throw std::out_of_range("Stack is empty. Cannot access top.\n");
    }
    return head->data;
}

/**
 * @brief Checks if the stack is empty.
 */
template <typename T>
bool Stack<T>::empty() const {
    return head == nullptr;
}

/**
 * @brief Returns the number of elements in the stack.
 */
template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
    return stack_size;
}

/**
 * @brief Clears all elements from the stack.
 */
template <typename T>
void Stack<T>::clear() {
    while (head) {
        typename Stack<T>::Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    stack_size = 0;
}

/**
 * @brief Returns an iterator to the beginning of the stack.
 */
template <typename T>
typename Stack<T>::iterator Stack<T>::begin() {
    return typename Stack<T>::iterator(head);
}

/**
 * @brief Returns an iterator to the end of the stack.
 */
template <typename T>
typename Stack<T>::iterator Stack<T>::end() {
    return typename Stack<T>::iterator(nullptr);
}

/**
 * @brief Returns a constant iterator to the beginning of the stack.
 */
template <typename T>
typename Stack<T>::const_iterator Stack<T>::cbegin() const {
    return typename Stack<T>::const_iterator(head);
}

/**
 * @brief Returns a constant iterator to the end of the stack.
 */
template <typename T>
typename Stack<T>::const_iterator Stack<T>::cend() const {
    return typename Stack<T>::const_iterator(nullptr);
}
