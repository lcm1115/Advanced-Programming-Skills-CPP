#ifndef PRISONER_H
#define PRISONER_H

#include <future>
#include <mutex>
#include <string>
#include <utility>

class Semaphore;

class Prisoner {
    public:
        Prisoner(int id,
                 Semaphore* shower);

        void shower(std::promise<std::pair<int, int>>* prom);
        
        bool dropped();

        int getId() const;

        int getDropped() const;

        int getTime() const;

        void print(const std::string& str) const;

    private:
        int _id;
        int _dropped;
        int _time;
        int _time_remaining;
        Semaphore* _shower;
        static std::mutex _write_mutex;
};

#endif  // PRISONER_H
