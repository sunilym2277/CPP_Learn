#include <iostream>
#include <cassert> // Required header

int main() {
    int x = 5;
    int y = 10;

    // Assert that x is less than y
    assert(x < y); // This will pass
    std::cout << "line 10" << std::endl;
    // Assert that x is greater than y (this will fail and terminate the program)
    assert(x > y); // This will fail

    std::cout << "This line will not be executed due to the failed assertion." << std::endl;

    return 0;
}