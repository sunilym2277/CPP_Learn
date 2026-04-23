# Race Conditions
A **race condition** occurs when **two or more threads access shared data concurrently**, and at least one thread **modifies the data**, leading to unexpected or incorrect results depending on the timing of execution.

**Example:**
Two threads increment a shared counter at the same time. Without proper synchronization, the final count may be wrong.

✅ Key idea: Outcome depends on the order of thread execution.

## How to Detect Race Conditions?
- **Review the Code :** Carefully inspecting of the code can help to identify the areas where shared resources are accessed without proper locking or synchronization.
- **Static Analysis Tools :** Specialized tools analyze the code to automatically detect potential race conditions by identifying unsafe access to shared resources.
- **Testing with Multiple Threads/Processes:** Simulate scenarios with many threads or processes running simultaneously. If unexpected behaviors like data inconsistencies or crashes occur, a race condition might be present.
- **Logging and Monitoring:** Adding logs to track resource access can reveal out-of-order operations, signaling a race condition

## How to Prevent Race Condition Attacks?
- **Use Locks:** Implement locks (like mutexes) to ensure that only one process or thread can access a resource at a time, preventing conflicting operations.
- **Proper Synchronization:** Ensure processes or threads work in a coordinated sequence when accessing shared data. Techniques like semaphores help achieve this.
- **Avoid Time-of-Check to Time-of-Use (TOCTOU) Vulnerabilities:** Reduce the gap between checking a condition (like permissions) and acting on it, minimizing opportunities for an attacker to change the state in between.
- **Priority Management:** Prioritize certain processes or threads so they get controlled access to critical resources, preventing uncoordinated access.
- **Atomic Operation in Race Conditions** Mention that atomic variables (std::atomic) can prevent race conditions without using locks, especially for simple counters or flags.
- **Lock Granularity / Performance Consideration**
Small note: Using too many locks or coarse-grained locks can hurt performance or even cause deadlocks.

# DeadLock
A **deadlock** happens when **two or more threads are waiting indefinitely for resources held by each other**, so **none of them can proceed**.

**Example:**
- Thread A holds Lock 1 and waits for Lock 2.
- Thread B holds Lock 2 and waits for Lock 1.
Both are stuck forever.

✅  Key idea: Circular wait causes threads to block each other permanently.

## Types of DeadLock PRevention / Avoidance
- Deadlock Prevention : Ensure that at least one of the necessary conditions (mutual exclusion, hold and wait,no preemption, circular wait) never occurs.
- Deadlock Avoidance : Use algorithm like Banker's Algorithm to check if granting a resource is safe
- Deadlock Detection and Recovery : Let deadlocks happen but detect them and recover(e.g., killing a thread or rolling back a transaction).

## Starvation vs Deadlock 
- Sometimes people confuse thread starvation with deadlock. You can add :
    - Starvation: A thread never gets CPU time or resource access because other threads always take precedence.
    - Deadlock: Threads are stuck waiting for each other indefinitely.

# Thread Block(Blocked State)
A **thread block** occurs when a thread **cannot proceed because it is waiting for a resource or condition**, but it is **not running.**

**Examples:**
- Waiting for a mutex/lock to become available.
- Waiting for I/O (file, network).
- Waiting on a condition variable.

✅ Key idea: Thread is alive but cannot run until the resource or condition is available.

# Key Terms in a Race Condition
- **Critical Section:** A code part where the shared resources are accessed. It is critical as multiple processes enter this section at same time leading to data corruption and errors.
- **Synchronization:** It is the process of controlling how and when multiple processes or threads access the shared resources ensuring that only one can enter the critical section at same time.
- **Mutual Exclusion (Mutex):** A mutex is like a lock that ensures only one process can access a resource at a time. If a process holds a lock, others must wait their turn preventing race conditions.
- **Deadlock:** A situation where two or more processes are stuck waiting for each other's resources, causing a deadlock(standstill).

# Conclusion
In conclusion, race conditions, deadlocks, and thread blocks are all issues that arise when multiple processes or threads compete for shared resources. Without proper management, these can lead to data errors, system freezes, or performance slowdowns. By understanding these concepts and applying techniques like synchronization, locking, and careful resource management, we can design systems that avoid these pitfalls and run smoothly.

## Race Condition Example
```cpp
#include <iostream>
#include <thread>

int counter = 0;  // Shared resource
void increment() {
    for (int i = 0; i < 100000; ++i) {
        counter++;  // Not thread-safe!
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << std::endl;
    return 0;
}
```
### Explanation:
- Two threads (t1 and t2) increment the shared variable counter.
- Because counter++ is not atomic, the threads may overwrite each other’s increments, producing a final value less than 200000.
- This is a classic race condition.
Fix: Use std::mutex or std::atomic<int> to make it thread-safe.


## DeadLock Example
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1, mtx2;

void threadA() {
    std::lock_guard<std::mutex> lock1(mtx1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(mtx2); // Waits here if threadB holds mtx2
    std::cout << "Thread A finished\n";
}

void threadB() {
    std::lock_guard<std::mutex> lock2(mtx2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock1(mtx1); // Waits here if threadA holds mtx1
    std::cout << "Thread B finished\n";
}

int main() {
    std::thread t1(threadA);
    std::thread t2(threadB);

    t1.join();
    t2.join();

    return 0;
}
```
Explanation:
- threadA locks mtx1 then tries to lock mtx2.
- threadB locks mtx2 then tries to lock mtx1.
- If timing aligns, both threads wait forever for each other, causing a deadlock.
- Fix: Always lock multiple mutexes in the same order or use std::lock().

## Semaphore
A semaphore is a synchronization primitive used to control access to shared resources in a concurrent (multi-threaded or multi-process) environment. Think of it as a counter that tracks how many threads can access a resource simultaneously.

Key Points:
1.  Types of Semaphores
    - Counting Semaphore:
        - Can have a value greater than 1.
        - Represents the number of available resources.
        - Example: A printer pool with 3 printers → semaphore initialized to 3.

    - Binary Semaphore (Mutex):
        - Can have only 0 or 1.
        - Acts like a lock for a single resource.

2. Basic Operations
    - wait() / P / acquire:
        - Decrements the semaphore.
        - If the value becomes < 0, the thread blocks until the resource is available.

    - signal() / V / release:
        - Increments the semaphore.
        - Wakes up a blocked thread if any are waiting.

### Analogy

Imagine a parking lot with 5 spots (semaphore initialized to 5):
- A car enters → wait() → reduces available spots.
- A car leaves → signal() → increases available spots.
- If the lot is full → cars wait until a spot becomes available.
```cpp
#include <iostream>
#include <thread>
#include <semaphore> // C++20

std::counting_semaphore<3> sem(3); // 3 resources

void worker(int id) {
    sem.acquire(); // wait for a resource
    std::cout << "Worker " << id << " is working\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Worker " << id << " is done\n";
    sem.release(); // release the resource
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    std::thread t4(worker, 4);

    t1.join(); t2.join(); t3.join(); t4.join();
    return 0;
}
```
#### Explanation:
- Only 3 workers can work at the same time because semaphore is initialized to 3.
- The 4th worker waits until a spot becomes available.
- ✅ Key Idea: Semaphores help coordinate access to limited resources and prevent race conditions without explicitly using mutexes for every single access.

## How to Prevent Race Condition Attacks?
### 1. Use Locks:
```cpp
#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;           // Shared resource
std::mutex mtx;            // Mutex to protect the counter

void increment() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Lock while modifying counter
        counter++;  // Now thread-safe
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << std::endl;
    return 0;
}
```
## 2. Atomic Operation in Race Conditions
```cpp

#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> counter(0); // Atomic counter

void increment() {
    for (int i = 0; i < 100000; ++i) {
        counter++; // Atomic increment
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << std::endl; // Always 200000
    return 0;
}
```
## 3. Lock Granularity / Performance Consideration
```cpp
#include <iostream>
#include <thread>
#include <mutex>

int counter1 = 0;
int counter2 = 0;
std::mutex mtx1, mtx2; // Separate locks

void increment() {
    for (int i = 0; i < 100000; ++i) {
        {
            std::lock_guard<std::mutex> lock1(mtx1);
            counter1++;
        } // Unlock mtx1 immediately

        {
            std::lock_guard<std::mutex> lock2(mtx2);
            counter2++;
        } // Unlock mtx2 immediately
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter1: " << counter1 << ", Counter2: " << counter2 << std::endl;
    return 0;
}
```
## Types of DeadLock PRevention / Avoidance
### 1. Consistent Lock Ordering (Best Practice)
Always acquire locks in the same order in every thread.
For example: always lock mtx1 before mtx2.
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1, mtx2;

void threadA() {
    std::lock(mtx1, mtx2); // lock both atomically (no deadlock)
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);

    std::cout << "Thread A finished\n";
}

void threadB() {
    std::lock(mtx1, mtx2); // same order → no deadlock
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);

    std::cout << "Thread B finished\n";
}

int main() {
    std::thread t1(threadA);
    std::thread t2(threadB);

    t1.join();
    t2.join();
}
```

## Coffman’s conditions for deadlock. 
#### A deadlock can only happen if all 4 hold true at the same time.If even one fails, deadlock cannot occur.
1. **Mutual Exclusion**
- At least one resource mult held in a non-sharable mode (only one thread can use it at a time).
- If resources are always shareable (like read-only files), deadlock wont occur
```cpp
#include <iostream>
#include <thread>
#include <shared_mutex>

std::shared_mutex sharedMtx; // multiple readers allowed

void reader(int id) {
    std::shared_lock<std::shared_mutex> lock(sharedMtx); // read lock (shared)
    std::cout << "Reader " << id << " is reading...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

int main() {
    std::thread t1(reader, 1);
    std::thread t2(reader, 2);

    t1.join();
    t2.join();
    return 0;
}
```
2. **Hold and Wait**
- A thread holds at least one resource and is waiting for additional resources that are held by others.

- If a process must request all resources at once (and gets blocked if not available), this condition fails → no deadlock.
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void task(int id) {
    // lock both at once, not one-by-one
    std::lock(m1, m2);
    std::lock_guard<std::mutex> lock1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(m2, std::adopt_lock);

    std::cout << "Thread " << id << " acquired both locks\n";
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);

    t1.join();
    t2.join();
    return 0;
}

```
3. **No Premption**
- Resources can’t be forcibly taken away; they must be released voluntarily.
- If the system allows preemption (OS can forcibly take resources back), no deadlock.
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::timed_mutex m1, m2;

void task(int id) {
    while (true) {
        if (m1.try_lock_for(std::chrono::milliseconds(100))) {
            if (m2.try_lock_for(std::chrono::milliseconds(100))) {
                std::cout << "Thread " << id << " got both locks\n";
                m2.unlock();
                m1.unlock();
                break;
            } else {
                // couldn't get m2 → release m1
                m1.unlock();
            }
        }
    }
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);

    t1.join();
    t2.join();
    return 0;
}
```
4. **Circular Wait**
- A circular chain of processes exists, each waiting for a resource held by the next process.
(e.g., P1 → waiting for P2, P2 → waiting for P3, P3 → waiting for P1).

- If you enforce a global lock ordering (e.g., always lock mtx1 before mtx2), this can’t happen.
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void taskA() {
    std::lock_guard<std::mutex> lock1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(m2);
    std::cout << "Task A done\n";
}

void taskB() {
    // Always same order: lock m1, then m2
    std::lock_guard<std::mutex> lock1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(m2);
    std::cout << "Task B done\n";
}

int main() {
    std::thread t1(taskA);
    std::thread t2(taskB);

    t1.join();
    t2.join();
    return 0;
}
```

## 1. Condition Variable (Producer–Consumer)

👉 Used to make one thread wait until another signals.
```cpp
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> q;
std::mutex mtx;
std::condition_variable cv;
bool done = false;

void producer() {
    for (int i = 1; i <= 5; i++) {
        std::unique_lock<std::mutex> lock(mtx);
        q.push(i);
        std::cout << "Produced " << i << "\n";
        cv.notify_one(); // wake up one waiting consumer
    }
    {
        std::unique_lock<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all(); // notify all consumers when finished
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !q.empty() || done; }); // block until work
        if (!q.empty()) {
            int val = q.front(); q.pop();
            std::cout << "Consumer " << id << " got " << val << "\n";
        } else if (done) break;
    }
}

int main() {
    std::thread p(producer);
    std::thread c1(consumer, 1), c2(consumer, 2);

    p.join();
    c1.join();
    c2.join();
}
```

🔑 Interview takeaway:
- cv.wait(lock, condition) → releases lock & sleeps until condition is true.
- notify_one() or notify_all() wakes waiting threads.
- Prevents busy waiting (no CPU waste).

## 2. Thread Blocking vs Busy Waiting
👉 Bad (busy wait):
- while (!done) { /* spinning → wastes CPU */ }
👉 Good (blocking wait with condition_variable):
- cv.wait(lock, [] { return done; });

## 3. Deadlock Detection (theory Q)
You already know prevention (break Coffman’s conditions).
👉 For detection:
- Build Resource Allocation Graph (RAG) → processes (P) and resources (R).
- If graph has a cycle → deadlock.
- OS can run detection periodically (Banker’s-like safety check).
(No C++ code needed, mostly theory question.)

## 4. Readers–Writers Fairness
👉 Problem: with std::shared_mutex, many readers can starve writers.
- Solution: give writers priority (e.g., block new readers when a writer is waiting).
- In C++20, std::shared_mutex is fairer but still depends on implementation.
(Just explaining is enough, code rarely asked.)

## 5. Thread Safety in STL
👉 Common interview Q:
- std::vector, std::map, etc. are not thread-safe.
Rule of thumb:
- Multiple readers → safe.
- One writer → unsafe, needs lock.

Example fix:
```cpp
#include <vector>
#include <mutex>
std::vector<int> data;
std::mutex mtx;

void safeWrite(int x) {
    std::lock_guard<std::mutex> lock(mtx);
    data.push_back(x);
}

int safeRead(size_t idx) {
    std::lock_guard<std::mutex> lock(mtx);
    return data[idx];
}
```