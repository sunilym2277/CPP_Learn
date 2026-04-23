#include<bits/stdc++.h>
using namespace std;

int counter=1;
void print(int p)
{
for(int i=0;i<5;i++)
{
//    this_thread::sleep_for(std::chrono::milliseconds(100));
   this_thread:: sleep_for(chrono::milliseconds(100));
    counter++;
   
    cout<<counter<< " " << p << endl;
}
    
}
int main()
{
    thread t1(print,1);
    thread t2(print,2);

    t1.join();
    t2.join();


    return 0;
}