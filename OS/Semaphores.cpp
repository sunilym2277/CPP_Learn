#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>   
using namespace std;

std::counting_semaphore<3> sem(3);
 void work()
 {
    cout<<"Thread "<<this_thread::get_id()<<" is waiting to acquire the semaphore..."<<endl;
    sem.acquire();;
    cout<<"Thread "<<this_thread::get_id()<<" is working..."<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"Thread "<<this_thread::get_id()<<" is done."<<endl;
    sem.release();
 }


 int main()
 {
    thread t1(work);
    thread t2(work);
    thread t3(work);
    thread t4(work);
    thread t5(work);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
 }