



#include<iostream>
#include <thread>
#include <mutex>  
using namespace std;
mutex m1, m2;
int counter1=0;
int counter2=0;
void thread1()
{
    {
        lock_guard<mutex> lock(m1);
        for(int i=0;i<2000000;++i)
            counter1++;
    }
    {
        lock_guard<mutex> lock2(m2);
        for(int i=0;i<1000000;++i)
            counter2++; 
    }
    

}
int main()
{
    thread t1(thread1);
    thread t2(thread1);
    t1.join();
    t2.join();
    cout<<"Counter 1: "<<counter1<<endl;
    cout<<"Counter 2: "<<counter2<<endl;
    return 0;
}