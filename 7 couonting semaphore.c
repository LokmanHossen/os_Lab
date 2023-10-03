#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class CountingSemaphore {
public:
    CountingSemaphore(int count) : count_(count) {}

    void acquire() {
        unique_lock<mutex> lock(mutex_);
        while (count_ <= 0) {
            cv_.wait(lock);
        }
        count_--;
    }

    void release() {
        unique_lock<mutex> lock(mutex_);
        count_++;
        cv_.notify_one();
    }

private:
    int count_;
    mutex mutex_;
    condition_variable cv_;
};

CountingSemaphore sem(3); // Initialize a semaphore with a count of 3

void worker(int id) {
    sem.acquire(); // Acquire a semaphore permit
    cout << "Worker " << id << " is working." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Simulate work
    cout << "Worker " << id << " has finished." << endl;
    sem.release(); // Release the semaphore permit
}

int main() {
    thread workers[5];

    for (int i = 0; i < 5; i++) {
        workers[i] = thread(worker, i);
    }

    for (int i = 0; i < 5; i++) {
        workers[i].join();
    }

    return 0;
}
