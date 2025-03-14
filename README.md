# 📦 Stack Implementation in C++

A fully functional **Stack** implemented using a **doubly linked list** in C++. This project provides a robust stack data structure with iterators and various utility functions.

---

## 🚀 Features
- **Custom Stack Class**: Implements a dynamic stack using a linked list.
- **Efficient Push & Pop**: O(1) operations for insertion and removal.
- **Iterator Support**: Bidirectional iterators for traversal.
- **Emplacement**: Constructs elements in place with `emplace()`.
- **Initializer List Support**: Bulk insertion using `{}` lists.
- **Swap Functionality**: Easily swap stacks in O(1) time.
- **Exception Safety**: Prevents invalid stack operations.

---

## 📁 Project Structure
```
📦 Stack Project
 ┣ 📜 stackHeader.hpp    # Stack class definition
 ┣ 📜 stackImplementation.cpp          # Implementation of Stack functions
 ┣ 📜 main.cpp           # Sample usage and testing
 ┣ 📜 README.md          # Documentation
```

---

## 🛠 Installation & Compilation

Clone the repository:
```bash
git clone https://github.com/your-repo/stack-implementation.git stack-implementation
cd stack-implementation
```
Compile the project:
```bash
g++ -std=c++17 main.cpp -o stack_program
```
Run the program:
```bash
./stack_program
```

---

## 📝 Usage Example

### 🔹 Pushing & Popping Elements
```cpp
Stack<int> s;
s.push(10);
s.push(20);
s.push(30);
std::cout << "Top: " << s.top() << std::endl; // Output: 30
s.pop();
```

### 🔹 Using Iterators
```cpp
for (auto it = s.begin(); it != s.end(); ++it) {
    std::cout << *it << " ";
}
```

### 🔹 Emplacing Elements
```cpp
s.emplace(40);
s.emplace(50);
```

