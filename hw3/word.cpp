// File: word.cpp
// Author: Liam Morris
// Description: Implements functions defined in word.h.

#include "word.h"

#include <cmath>
#include <fstream>
#include <limits>
#include <string>
#include <map>
#include <vector>

using std::map;
using std::min;
using std::numeric_limits;
using std::string;

Word::Word(string word) : _word(word) {
    _distance = numeric_limits<int>::max();
    _visited = false;
}

int Word::distance(const Word& s) const {
    int distance = 0;
    int diff = 0;
    for (unsigned int i = 0; i < _word.length(); ++i) {
        if (_word.at(i) != s.getWord().at(i)) {
            ++diff;

            if (diff > 1) {
                return -1;
            }
        }
        distance += abs(_word.at(i) - s.getWord().at(i));
    }

    return distance;
}

map<Word*, int> Word::getNeighbors() {
    return _neighbors;
}

void Word::addNeighbor(Word* neighbor, int distance) {
    _neighbors[neighbor] = distance;
}

int Word::getDistance() const {
    return _distance;
}

void Word::setDistance(int distance) {
    _distance = distance;
}

string Word::getWord() const {
    return _word;
}

void Word::markVisited() {
    _visited = true;
}

bool Word::isVisited() const {
    return _visited;
}

bool Word::operator<(const Word& rhs) const {
    return _word < rhs._word;
}

bool Word::operator==(const Word& rhs) const {
    return _word == rhs._word;
}
