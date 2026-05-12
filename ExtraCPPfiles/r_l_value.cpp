#include <iostream>
using namespace std;    
int main()
{
    int x = 10;
    int &y = x; // y is an l-value reference to x
    cout << "Value of x: " << x++ << endl; // Output: 10
    cout << "Value of y: " << ++y << endl; // Output: 10

    y = 20; // Modifying y also modifies x
    cout << "Value of x after modifying y: " << x << endl; // Output: 20
    cout << "Value of y after modifying y: " << y << endl; // Output: 20



    // Lvalue reference (&): Binds to lvalues
    int& l_ref = x;        // Valid! 'x' is an lvalue.
    // int& l_ref2 = 5;    // ERROR! Cannot bind a standard lvalue ref to an rvalue.

    // Rvalue reference (&&): Binds to rvalues
    int&& r_ref = 5;       // Valid! '5' is a temporary rvalue.
    // int&& r_ref2 = x;   // ERROR! Cannot bind an rvalue ref to an lvalue ('x' is persistent).

    cout << "Lvalue reference (l_ref): " << l_ref << endl; // Output: 20
    cout << "Rvalue reference (r_ref): " << r_ref << endl; //
    return 0;
}