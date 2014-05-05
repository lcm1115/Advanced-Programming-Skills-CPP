#include "semaphore.h"

#include <condition_variable>
#include <mutex>
#include <thread>

using std::mutex;
using std::unique_lock;

Semaphore::Semaphore(unsigned int count) : _count(count) {
}

void Semaphore::notify() {
    unique_lock<mutex> lock(_mutex);
    ++_count;
    _cond.notify_one();
}

void Semaphore::wait() {
    unique_lock<mutex> lock(_mutex);
    while (_count == 0) {
        _cond.wait(lock);
    }
    --_count;
}
