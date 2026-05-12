#include<iostream>
#include<string>
using namespace std;

// template<typename T>
// void Print(T data){
//     cout<<data<<"  "<<sizeof(data)<<endl;
// }

template<typename T>
void display(T value)
{
    cout << value << endl;
}

template<>
void display<char*>(char* value)
{
    cout << "String: " << value << endl;
}


int main(){

    // Templates

    // Print(10);
    // Print(3.14);
    // Print("Hello");
    // Print('c');

// Template specialization
    display(10); // Calls the generic template
    display(3.14); // Calls the generic template   
    display("Hello"); // Calls the specialized template for char*
    display('c'); // Calls the generic template 
    return 0;
}