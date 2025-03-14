#include "stackHeader.hpp"

int main() {
    Stack<int> s;

    // Test push
    std::cout << "Pushing elements: 10, 20, 30\n";
    s.push(10);
    s.push(20);
    s.push(30);
    
    std::cout << "Top element: " << s.top() << "\n"; // Expected: 30

    // Test pop
    std::cout << "Popping top element...\n";
    s.pop();
    std::cout << "New top: " << s.top() << "\n"; // Expected: 20

    // Test size
    std::cout << "Stack size: " << s.size() << "\n"; // Expected: 2

    // Test empty
    std::cout << "Is stack empty? " << (s.empty() ? "Yes" : "No") << "\n"; // Expected: No

    // Test swap
    Stack<int> s2;
    s2.push(100);
    s2.push(200);

    std::cout << "Swapping stacks...\n";
    s.swap(s2);

    std::cout << "Stack s top after swap: " << s.top() << "\n"; // Expected: 200
    std::cout << "Stack s2 top after swap: " << s2.top() << "\n"; // Expected: 20

    // Test push_range
    std::cout << "Pushing range {1, 2, 3, 4, 5}...\n";
    s.push_range({1, 2, 3, 4, 5});
    std::cout << "New top: " << s.top() << "\n"; // Expected: 5

    // Test emplace
    std::cout << "Using emplace to push 99...\n";
    s.emplace(99);
    std::cout << "New top: " << s.top() << "\n"; // Expected: 99

    // Test iterators
    std::cout << "Stack elements: ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test clear
    std::cout << "Clearing stack...\n";
    s.clear();
    std::cout << "Stack size after clear: " << s.size() << "\n"; // Expected: 0
    std::cout << "Is stack empty? " << (s.empty() ? "Yes" : "No") << "\n"; // Expected: Yes

    // Test popping from empty stack (should throw)
    try {
        std::cout << "Attempting to pop from empty stack...\n";
        s.pop();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
