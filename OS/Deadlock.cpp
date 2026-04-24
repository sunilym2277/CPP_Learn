#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
class deadlock{
private: mutex m1, m2;

public:
        void funct1(){
            m1.lock();
            cout<<"Thread 1: Locked m1"<<endl;
            this_thread::sleep_for(chrono::milliseconds(100));
              this_thread::sleep_for(chrono::seconds(10));
             m1.unlock();
             cout<<  "Thread 1:unlock m2"<<endl;
            m2.lock();


             cout<<  "Thread 1: Locked m2 waitinggggggggggggggggggggg"<<endl;
            this_thread::sleep_for(chrono::seconds(10));
             m2.unlock();

        }
        void funct2()
        {
            m2.lock();
            cout<<"Thread 2: Locked m2"<<endl;
            this_thread::sleep_for(chrono::milliseconds(100));
            m1.lock();

            cout<<  "Thread 2: Locked m1 waitinggggggggggggggggggggg"<<endl;
            this_thread::sleep_for(chrono::seconds(10));
            m1.unlock();
             m2.unlock();

        }

};



int main()
{
    deadlock d;
    thread t1(&deadlock::funct1, &d);
    thread t2(&deadlock::funct2, &d);

    t1.join();
    t2.join();
    cout<<"Main thread: Both threads have finished execution"<<endl;

    return 0;
}