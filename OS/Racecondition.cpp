#include<iostream>
#include<thread>
#include<chrono>
#include<atomic>
#include<mutex>
using namespace std;

atomic<int> atomiccounter=1;
mutex  m;
int counter=1;
void print(int p)
{
    for(int i=0;i<1000000;++i)
    {
    //    this_thread::sleep_for(std::chrono::milliseconds(100));
    //    this_thread:: sleep_for(chrono::milliseconds(100));
        // lock_guard<mutex> lock(m);
        // m.lock();
        counter++;
        // m.unlock();
    
        // cout<<counter<< " " << p << endl;
    }
}
void atomicprint()
{
    for(int i=0;i<1000000;++i)
    {
        atomiccounter++;
    }
    
}
int main()
{
    thread t1(print,1);
    thread t2(print,2);
    
    t1.join();
    cout<<"Counter value: "<<counter<<endl;
    t2.join();
    cout<<"Counter actual value: "<<counter<<endl;
    cout<<"Counter Expected value: 2000000"<<endl;

    // thread t3(atomicprint);
    // thread t4(atomicprint);
    
    // t3.join();
    // t4.join();
    cout<<"Counter actual value: "<<atomiccounter<<endl;
    cout<<"Counter Expected value: 2000000"<<endl;


    return 0;
}










// /**
//  * This program demonstrates:
//  * 1. A Race Condition: Two threads incrementing a non-atomic shared counter.
//  * 2. Thread Safety: Using std::atomic to ensure correct results without mutexes.
//  */

// #include <iostream>
// #include <thread>
// #include <atomic>
// #include <vector>

// // 1. UNSAFE COUNTER (Race Condition)
// int unsafe_counter = 0;

// // 2. SAFE COUNTER (Atomic)
// // std::atomic provides lock-free operations for simple types.
// std::atomic<int> safe_counter(0);

// const int ITERATIONS = 1000000;

// void incrementUnsafe() {
//     for (int i = 0; i < ITERATIONS; ++i) {
//         // This is not a single CPU instruction. It's read-modify-write.
//         // Two threads can read the same value, increment it, and write it back,
//         // essentially "losing" one of the increments.
//         unsafe_counter++; 
//     }
// }

// void incrementSafe() {
//     for (int i = 0; i < ITERATIONS; ++i) {
//         // std::atomic overrides the ++ operator to use specialized 
//         // CPU instructions (like Fetch-and-Add) that are indivisible.
//         safe_counter++; 
//     }
// }

// int main() {
//     std::cout << "Starting threads for " << ITERATIONS * 2 << " total increments...\n\n";

//     // --- TEST 1: RACE CONDITION ---
//     std::thread t1(incrementUnsafe);
//     std::thread t2(incrementUnsafe);
//     t1.join();
//     t2.join();

//     std::cout << "--- Unsafe Counter Results ---" << std::endl;
//     std::cout << "Expected: " << ITERATIONS * 2 << std::endl;
//     std::cout << "Actual:   " << unsafe_counter << std::endl;
//     std::cout << "Status:   " << (unsafe_counter == ITERATIONS * 2 ? "Success" : "Race Condition Detected!") << "\n\n";

//     // --- TEST 2: ATOMIC (THREAD SAFE) ---
//     std::thread t3(incrementSafe);
//     std::thread t4(incrementSafe);
//     t3.join();
//     t4.join();

//     std::cout << "--- Atomic Counter Results ---" << std::endl;
//     std::cout << "Expected: " << ITERATIONS * 2 << std::endl;
//     std::cout << "Actual:   " << safe_counter.load() << std::endl;
//     std::cout << "Status:   " << (safe_counter == ITERATIONS * 2 ? "Success" : "Failure") << std::endl;

//     return 0;
// }