// File: skyscraperconfig.cpp
// Author: Liam Morris
// Description: Implements functions described in skyscraperconfig.h for
//              generating successor configs, validating configs, and
//              determining if a config is a goal.

#include "skyscraperconfig.h"

#include <cstdio>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using std::ostream;
using std::ostringstream;
using std::set;
using std::string;
using std::vector;

SkyscraperConfig::SkyscraperConfig(int n,
                                   const vector<vector<int>>& clues)
    : _failure(false), _row(0), _col(0), _n(n), _clues(clues) {
    for (int i = 0; i < n; ++i) {
        _board.push_back(vector<int>());
        for (int j = 0; j < n; ++j) {
            _board.at(i).push_back(0);
        }
    }
}

SkyscraperConfig::SkyscraperConfig(bool failure) : _failure(failure) { }

void SkyscraperConfig::clickPos(int pos) {
    int row = pos / 5;
    int col = pos % 5;
    ++_board.at(row).at(col);
    _board.at(row).at(col) %= 6;
}

void SkyscraperConfig::clear() {
    for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n; ++j) {
            _board.at(i).at(j) = 0;
        }
    }
}

void SkyscraperConfig::setValueAtPos(int value, int pos) {
    _board.at(pos / 5).at(pos % 5) = value;
}

int SkyscraperConfig::getValueAtPos(int pos) const {
    return _board.at(pos / 5).at(pos % 5);
}

void SkyscraperConfig::setPos() {
    for (int i = 0; i < _n; ++i) {
        _row = i;
        for (int j = 0; j < _n; ++j) {
            _col = j;
            if (_board.at(i).at(j) == 0) {
                return;
            }
        }
    }

    _row = _n;
}

int SkyscraperConfig::getRow() const {
    return _row;
}

int SkyscraperConfig::getCol() const {
    return _col;
}

bool SkyscraperConfig::isFailure() const {
    return _failure;
}

bool SkyscraperConfig::isGoal() const {
    return _row == _n;
}

bool SkyscraperConfig::isValid() const {
    for (int cur = 0; cur < 5; ++cur) {
        int numSeenLR = 0;
        int numSeenRL = 0;
        int lastSeenLR = 0;
        int lastSeenRL = 0;
        int numSeenUD = 0;
        int numSeenDU = 0;
        int lastSeenUD = 0;
        int lastSeenDU = 0;
        int clueUD = _clues.at(0).at(cur);
        int clueLR = _clues.at(1).at(cur);
        int clueRL = _clues.at(2).at(cur);
        int clueDU = _clues.at(3).at(cur);
        set<int> valuesR, valuesC;
        for (int i = 0; i < _n; ++i) {
            // Keep track of how many skyscrapers are visible going from:
            //     Left to right
            //     Right to left
            //     Up to down
            //     Down to up
            int currentLR = _board.at(cur).at(i);
            int currentRL = _board.at(cur).at(_n - i - 1);
            int currentUD = _board.at(i).at(cur);
            int currentDU = _board.at(_n - i - 1).at(cur);

            // If values are invalid return false
            if (currentLR != 0) {
                if (valuesR.find(currentLR) != valuesR.end()) {
                    return false;
                }

                valuesR.insert(currentLR);
            }

            if (currentDU != 0) {
                if (valuesC.find(currentDU) != valuesC.end()) {
                    return false;
                }

                valuesC.insert(currentDU);
            }

            if (currentUD > lastSeenUD) {
                lastSeenUD = currentUD;
                ++numSeenUD;
                if (clueUD != 0 && numSeenUD > clueUD) {
                    return false;
                }
            }

            if (currentLR > lastSeenLR) {
                lastSeenLR = currentLR;
                ++numSeenLR;
                if (clueLR != 0 && numSeenLR > clueLR) {
                    return false;
                }
            }

            if (currentRL > lastSeenRL) {
                lastSeenRL = currentRL;
                ++numSeenRL;
            }

            if (currentDU > lastSeenDU) {
                lastSeenDU = currentDU;
                ++numSeenDU;
            }
        }

        if (valuesR.size() == (unsigned int) _n) {
            if ((clueLR != 0 && numSeenLR != clueLR) ||
                (clueRL != 0 && numSeenRL != clueRL)) {
                return false;
            }
        }

        if (valuesC.size() == (unsigned int) _n) {
            if ((clueUD != 0 && numSeenUD != clueUD) ||
                (clueDU != 0 && numSeenDU != clueDU)) {
                return false;
            }
        }
    }

    return true;
}

vector<SkyscraperConfig> SkyscraperConfig::getSuccessors() const {
    vector<SkyscraperConfig> successors;

    // Determine row and column of next position to be filled
    int row = _row;
    int col = _col + 1;

    if (col == _n) {
        col = 0;
        ++row;
    }

    // If position on board is non-empty then move past it
    while (row < _n && _board.at(row).at(col) != 0) {
        ++col;

        if (col == _n) {
            col = 0;
            ++row;
        }
    }

    for (int i = 1; i <= _n; ++i) {
        SkyscraperConfig config(*this);
        config._board.at(_row).at(_col) = i;
        config._row = row;
        config._col = col;

        successors.push_back(config);
    }

    return successors;
}

string SkyscraperConfig::str() const {
    ostringstream oss;
    oss << *this;
    return oss.str();
}

ostream& operator<<(ostream& os, const SkyscraperConfig& config) {
    os << "    ";
    for (int i = 0; i < config._n; ++i) {
        os << config._clues.at(0).at(i) << " ";
    }
    os << "\n";
    os << "  ";
    for (int i = 0; i < 2 * config._n + 3; ++i) {
        os << "-";
    }
    os << "\n";
    for (int i = 0; i < config._n; ++i) {
        os << config._clues.at(1).at(i) << " | ";
        for (int j = 0; j < config._n; ++j) {
            os << config._board.at(i).at(j) << " ";
        }
        os << "| " << config._clues.at(2).at(i) << "\n";
    }
    os << "  ";
    for (int i = 0; i < 2 * config._n + 3; ++i) {
        os << "-";
    }
    os << "\n";
    os << "    ";
    for (int i = 0; i < config._n; ++i) {
        os << config._clues.at(3).at(i) << " ";
    }
    return os;
}
