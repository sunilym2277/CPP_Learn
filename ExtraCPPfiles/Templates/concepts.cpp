#include <iostream>
#include <concepts>
#include <type_traits>
using namespace std;


// template<class T>
// requires integral<T>

// void printi(T x)
// {
//     std::cout << "Integral\n";
// }


// int main()
// {
//     printi(10); // Calls the integral version
//     printi(3.14); // Compilation error: no matching function for call to 'printi(double)'
//     return 0;
// }



#include <iostream>
#include <concepts>
#include <string>

// Way 1: Using the 'requires' clause
template <typename T>
requires std::integral<T> || std::floating_point<T>
T add(T a, T b) {
    return a + b;
}

// Way 2: The shorter "Abbreviated Function Template" syntax
auto multiply(std::integral auto a, std::integral auto b) {
    return a * b;
}

int main() {
    std::cout << add(5, 10) << "\n";       // Works! (int is integral)
    std::cout << add(5.5, 2.2) << "\n";    // Works! (double is floating_point)
    std::cout << multiply(3, 4) << "\n";   // Works!
 
    std::string s1 = "A", s2 = "B";
    add(s1, s2); // FAILS IMMEDIATELY: "constraints not satisfied"
    // The compiler stops right here, saving you from a 50-page error log.
    
    return 0;
}