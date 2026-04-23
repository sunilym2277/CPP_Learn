#include <iostream>
using namespace std;

int buggyFunction(int n) {
    int arr[5] = {1, 2, 3, 4, 5};
    int sum = 0;
    // ❌ Bug: loop goes out of bounds
    for (int i = 0; i <= n; i++) {
        sum += arr[i];
    }
    return sum;
}

void leakMemory() {
    int *p = new int[100]; // ❌ Leak: never freed
    for (int i = 0; i < 100; i++) {
        p[i] = i;
    }
    cout << "Leaked 100 integers!" << endl;
}

void slowFunction() {
    long long total = 0;
    for (long long i = 0; i < 100000000; i++) { // ❌ Slow loop
        total += i % 10;
    }
    cout << "Slow function total: " << total << endl;
}

int main() {
    cout << "Debug demo start" << endl;

    int result = buggyFunction(5); // ❌ This will go out of bounds
    cout << "Result: " << result << endl;

    leakMemory();   // ❌ Leak check with Valgrind / Dr.Memory
    slowFunction(); // ❌ Profile hotspot

    cout << "Demo done" << endl;
    return 0;
}
