#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<
    std::is_integral<T>::value,
    void
>::type
print(T value)
{
    std::cout << "Integral: "
              << value << std::endl;
}


template<typename T>
typename std::enable_if<
    std::is_floating_point<T>::value
>::type
print(T x)
{
    std::cout << "Float\n";
}


int main()
{
    print(10); // Calls the integral version
    print(3.14); // Compilation error: no matching function for call to 'print(double)'
    return 0;
}