// File: skyscraperconfig.cpp
// Author: Liam Morris
// Description: Implements functions described in skyscraperconfig.h for
//              generating successor configs, validating configs, and
//              determining if a config is a goal.

#include "skyscraperconfig.h"

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
                                   const vector<vector<int>>& clues,
                                   const vector<vector<int>>& prefilled)
    : _n(n), _clues(clues) {
    _quickfail = false;
    _failure = false;
    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for (int j = 0; j < n; ++j) {
            row.push_back(0);
        }
        _board.push_back(row);
    }

    // Fill prefilled values
    for (auto it : prefilled) {
        int row = it.at(0);
        int col = it.at(1);
        int val = it.at(2);
        _board.at(row).at(col) = val;
    }

    // Prefill top side
    for (int i = 0; i < n; ++i) {
        if (_clues.at(0).at(i) == 1) {
            _board.at(0).at(i) = n;
        } else if (_clues.at(0).at(i) == n) {
            for (int j = 0; j < n; ++j) {
                int value = _board.at(j).at(i);
                if (value != 0 && value != j + 1) {
                    _quickfail = true;
                } else {
                    _board.at(j).at(i) = j + 1;
                }
            }
        }
    }

    // Prefill left side
    for (int i = 0; i < n; ++i) {
        if (_clues.at(1).at(i) == 1) {
            _board.at(i).at(0) = n;
        } else if (_clues.at(1).at(i) == n) {
            for (int j = 0; j < n; ++j) {
                int value = _board.at(i).at(j);
                if (value != 0 && value != j + 1) {
                    _quickfail = true;
                } else {
                    _board.at(i).at(j) = j + 1;
                }
            }
        }
    }

    // Prefill right side
    for (int i = 0; i < n; ++i) {
        if (_clues.at(2).at(i) == 1) {
            _board.at(i).at(n - 1) = n;
        } else if (_clues.at(2).at(i) == n) {
            for (int j = 0; j < n; ++j) {
                int value = _board.at(i).at(j);
                if (value != 0 && value != n - j) {
                    _quickfail = true;
                } else {
                    _board.at(i).at(j) = n - j;
                }
            }
        }
    }

    // Prefill bottom side
    for (int i = 0; i < n; ++i) {
        if (_clues.at(3).at(i) == 1) {
            _board.at(n - 1).at(i) = n;
        } else if (_clues.at(3).at(i) == n) {
            for (int j = 0; j < n; ++j) {
                int value = _board.at(j).at(i);
                if (value != 0 && value != n - j) {
                    _quickfail = true;
                } else {
                    _board.at(j).at(i) = n - j;
                }
            }
        }
    }

    if (_quickfail) {
        _col = 0;
        _row = _n;
        _lastCol = 0;
        _lastRow = 0;
    } else {
        _col = 0;
        _row = 0;
        _lastRow = 0;
        _lastCol = 0;

        while (_row < n && _board.at(_row).at(_col) != 0) {
            ++_col;

            if (_col == _n) {
                _col = 0;
                ++_row;
            }
        }
    }
}

SkyscraperConfig::SkyscraperConfig(bool failure) : _failure(failure) { }

bool SkyscraperConfig::isFailure() const {
    return _failure;
}

bool SkyscraperConfig::isGoal() const {
    return _row == _n && !_quickfail;
}

bool SkyscraperConfig::isValid() const {
    int numSeenLR = 0;
    int numSeenRL = 0;
    int lastSeenLR = 0;
    int lastSeenRL = 0;
    int numSeenUD = 0;
    int numSeenDU = 0;
    int lastSeenUD = 0;
    int lastSeenDU = 0;
    int clueUD = _clues.at(0).at(_lastCol);
    int clueLR = _clues.at(1).at(_lastRow);
    int clueRL = _clues.at(2).at(_lastRow);
    int clueDU = _clues.at(3).at(_lastCol);
    set<int> valuesR, valuesC;
    for (int i = 0; i < _n; ++i) {
        // Keep track of how many skyscrapers are visible going from:
        //     Left to right
        //     Right to left
        //     Up to down
        //     Down to up
        int currentLR = _board.at(_lastRow).at(i);
        int currentRL = _board.at(_lastRow).at(_n - i - 1);
        int currentUD = _board.at(i).at(_lastCol);
        int currentDU = _board.at(_n - i - 1).at(_lastCol);

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
        config._lastRow = _row;
        config._lastCol = _col;

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
