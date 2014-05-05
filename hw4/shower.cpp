// File: shower.cpp
// Author: Liam Morris
// Description: Main function for prison shower program. Reads in number of
//              prisoners and total number of shower heads available and starts
//              each prisoner on its own thread.

#include "prisoner.h"
#include "semaphore.h"

#include <algorithm>
#include <future>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::max;
using std::pair;
using std::promise;
using std::shared_ptr;
using std::stoi;
using std::thread;
using std::vector;

void usage() {
    cerr << "usage: shower <num_prisoners> <num_shower_heads>" << endl;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        usage();
        return -1;
    }

    int num_prisoners;
    int num_shower_heads;
    try {
        num_prisoners = stoi(argv[1]);
        num_shower_heads = stoi(argv[2]);
    } catch (...) {
        usage();
        return -1;
    }

    cout << "Prison Shower Simulator 2014 has begun..." << endl;

    Semaphore semaphore(num_shower_heads);

    vector<shared_ptr<Prisoner>> prisoners;
    vector<shared_ptr<promise<pair<int, int>>>> promises;

    for (int i = 0; i < num_prisoners; ++i) {
        prisoners.push_back(shared_ptr<Prisoner>(
                new Prisoner(i + 1, &semaphore)));
        promise<pair<int, int>>* prom = new promise<pair<int, int>>();
        promises.push_back(shared_ptr<promise<pair<int, int>>>(prom));
        thread t(&Prisoner::shower, prisoners.back(), prom);
        t.detach();
    }

    vector<shared_ptr<Prisoner>> max_prisoners;
    int max_dropped = -1;
    int total_dropped = 0;
    int total_time = 0;

    for (auto prom : promises) {
        pair<int, int> values = prom->get_future().get();
        total_time += values.first;
        total_dropped += values.second;
        max_dropped = max(max_dropped, values.second);
    }

    for (auto p : prisoners) {
        if (p->getDropped() == max_dropped) {
            max_prisoners.push_back(p);
        }
    }

    cout << "Prison Shower Simulator 2014 has ended..." << endl;
    cout << total_time << " minute/s of shower time were used" << endl;
    cout << total_dropped << " bar/s of soap were dropped in the shower" << endl;
    cout << "The prisoner who dropped the soap the most, " << max_dropped
         << " times, are:";

    for (auto p : max_prisoners) {
        cout << endl << "Prisoner #" << p->getId();
    }

    return 0;
}
