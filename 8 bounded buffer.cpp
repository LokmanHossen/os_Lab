#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 5;

class BoundedBuffer {
public:
    BoundedBuffer() : buffer(BUFFER_SIZE), in(0), out(0), count(0) {}

    void enqueue(int item) {
        std::unique_lock<std::mutex> lock(mutex);
        while (count == BUFFER_SIZE) {
            // Buffer is full, wait for dequeue
            not_full.wait(lock);
        }
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        not_empty.notify_all();
    }

    int dequeue() {
        std::unique_lock<std::mutex> lock(mutex);
        while (count == 0) {
            // Buffer is empty, wait for enqueue
            not_empty.wait(lock);
        }
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        not_full.notify_all();
        return item;
    }

private:
    std::vector<int> buffer;
    int in, out, count;
    std::mutex mutex;
    std::condition_variable not_empty, not_full;
};

void producer(BoundedBuffer& buffer) {
    for (int i = 0; i < 10; i++) {
        buffer.enqueue(i);
        std::cout << "Produced: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void consumer(BoundedBuffer& buffer) {
    for (int i = 0; i < 10; i++) {
        int item = buffer.dequeue();
        std::cout << "Consumed: " << item << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main() {
    BoundedBuffer buffer;

    std::thread producer_thread(producer, std::ref(buffer));
    std::thread consumer_thread(consumer, std::ref(buffer));

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
