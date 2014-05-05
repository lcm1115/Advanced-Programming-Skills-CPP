#include "prisoner.h"
#include "semaphore.h"

#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

using std::chrono::seconds;
using std::cout;
using std::endl;
using std::lock_guard;
using std::mutex;
using std::pair;
using std::promise;
using std::string;
using std::this_thread::sleep_for;

mutex Prisoner::_write_mutex;

Prisoner::Prisoner(int id, Semaphore* shower)
    : _id(id),
      _dropped(0),
      _shower(shower) {
    _time = rand() % 5 + 1;
    _time_remaining = _time;
}

void Prisoner::shower(promise<pair<int, int>>* prom) {
    bool clean = false;
    while (!clean) {
        _shower->wait();
        print("entered shower: \"My body is ready!\"");
        while (_time_remaining > 0) {
            if (dropped()) {
                print("dropped the soap!");
                ++_dropped;
                break;
            } else {
                print("showering");
            }
            --_time_remaining;
            sleep_for(seconds(1));
        }

        clean = _time_remaining == 0;

        print("exited shower");
        _shower->notify();
    }

    prom->set_value(pair<int, int>(_time, _dropped));
}

int Prisoner::getId() const {
    return _id;
}

int Prisoner::getDropped() const {
    return _dropped;
}

int Prisoner::getTime() const {
    return _time;
}

void Prisoner::print(const string& str) const {
    lock_guard<mutex> lock(_write_mutex);
    cout << "Prisoner #" << _id << "(" << _time_remaining
         << "), " << str << endl;
}

bool Prisoner::dropped() {
    int r = rand() % 100;
    return r < 5; 
}
