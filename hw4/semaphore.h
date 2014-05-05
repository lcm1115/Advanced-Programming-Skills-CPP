#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <condition_variable>
#include <mutex>
#include <thread>

class Semaphore {
    public:
        Semaphore(unsigned int count);

        void notify();

        void wait();

    private:
        std::condition_variable _cond;
        std::mutex _mutex;
        unsigned int _count;
};

#endif  // SEMAPHORE_H
