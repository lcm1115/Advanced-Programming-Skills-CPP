#include "word.h"

#include <boost/heap/fibonacci_heap.hpp>
#include <cstring>
#include <deque>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

using boost::heap::compare;
using boost::heap::fibonacci_heap;
using namespace std;

deque<string> dijkstra(Word* start, Word* end) {
    map<Word*, fibonacci_heap<Word*,
        compare<WordCompare>>::handle_type> handles;
    map<Word*, Word*> predecessors;
    fibonacci_heap<Word*, compare<WordCompare>> heap;

    handles[start] = heap.push(start);

    while (!heap.empty() && !end->isVisited()) {
        Word* current = heap.top();
        for (auto it : current->getNeighbors()) {
            if (it.first->isVisited()) {
                continue;
            }

            int tentative = current->getDistance() + it.second;
            if (tentative < it.first->getDistance()) {
                predecessors[it.first] = current;

                it.first->setDistance(tentative);

                if (handles.count(it.first) == 1) {
                    heap.update(handles.at(it.first));
                } else {
                    handles[it.first] = heap.push(it.first);
                }
            }
        }

        heap.pop();
        handles.erase(current);
        current->markVisited();
    }

    deque<string> path;

    if (predecessors.count(end) == 1) {
        Word* current = end;
        while (current != start) {
            path.push_front(current->getWord());
            current = predecessors[current];
        }
        path.push_front(current->getWord());
    }

    return path;
}

void usage() {
    cerr << "Usage: ladder [-v] file word1 word2" << endl;
}

int main(int argc, char** argv) {
    bool verbose = false;
    if (argc < 4) {
        usage();
        return -1;
    } else {
        if (argc > 4) {
            if (strcmp(argv[1], "-v") != 0) {
                usage();
                return -1;
            } else {
                verbose = true;
            }
        }
    }

    string fp(argv[argc - 3]);
    string s(argv[argc - 2]);
    string e(argv[argc - 1]);

    ifstream input(fp, ifstream::in);
    if (!input.is_open()) {
        cerr << "Error opening input file: " << fp << endl;
        return -1;
    }

    Word* start;
    Word* end;
    string buffer;
    vector<shared_ptr<Word>> words;
    while (input >> buffer) {
        Word* w = new Word(buffer);
        if (buffer == s) {
            start = w;
            w->setDistance(0);
        } else if (buffer == e) {
            end = w;
        }
        words.push_back(shared_ptr<Word>(w));
    }

    if (!start) {
        cerr << "Starting word not found in file: " << s << endl;
        return -1;
    }

    if (!end) {
        cerr << "Ending word not found in file: " << e << endl;
        return -1;
    }

    int edges = 0;
    for (unsigned int i = 0; i < words.size() - 1; ++i) {
        for (unsigned int j = i + 1; j < words.size(); ++j) {
            int distance = words.at(i)->distance(*words.at(j));
            if (distance != -1) {
                words.at(i)->addNeighbor(words.at(j).get(), distance);
                words.at(j)->addNeighbor(words.at(i).get(), distance);
                edges += 2;
            }
        }
    }

    if (verbose) {
        cout << "GRAPH:" << endl;
        for (auto word : words) {
            cout << "    " << word->getWord() << " :";
            for (auto neighbor : word->getNeighbors()) {
                cout << " (" << neighbor.first->getWord() << ","
                     << neighbor.second << ")";
            }
            cout << endl;
        }
        cout << "Total Edges: " << edges << endl << endl;
    }

    deque<string> path = dijkstra(start, end);

    if (path.size() > 0) {
        cout << "Total distance: " << end->getDistance() << endl;

        for (auto it : path) {
            cout << it << endl;
        }
    } else {
        cerr << "No solution!" << endl;
    }

    return argc;
}
