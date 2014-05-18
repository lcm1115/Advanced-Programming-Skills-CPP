// File: hitoriconfig.cpp
// Author: Liam Morris
// Description: Implements functions described in hitoriconfig.h for
//              generating successor configs, validating configs, and
//              determining if a config is a goal.

#include "hitoriconfig.h"

#include <ostream>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using std::ostream;
using std::ostringstream;
using std::pair;
using std::set;
using std::stack;
using std::string;
using std::vector;

HitoriConfig::HitoriConfig(int n,
                           const std::vector<std::vector<int>>& board,
                           const std::vector<std::vector<int>>& prefilled)
    : _n(n),
      _row(0),
      _col(0),
      _white_count(n * n),
      _failure(false),
      _board(board) {
    for (auto it : prefilled) {
        int row = it.at(0);
        int col = it.at(1);
        _board.at(row).at(col) *= -1;
    }
}

HitoriConfig::HitoriConfig(bool failure) : _failure(failure) { }

bool HitoriConfig::isFailure() const {
    return _failure;
}

bool HitoriConfig::isGoal() const {
    return _row == _n && whiteConnected();
}

bool HitoriConfig::isValid() const {
    // Check previous values
    int col = _col - 1;
    int row = _row;

    if (col < 0) {
        col = _n - 1;
        --row;
    }

    if (isSurrounded(row - 1, col) || isSurrounded(row, col - 1)) {
        return false;
    }

    set<int> rowValues;
    for (int i = 0; i <= col; ++i) {
        int value = _board.at(row).at(i);
        if (value < 0) {
            continue;
        }
        if (rowValues.count(value) == 1) {
            return false;
        }
        rowValues.insert(value);
    }

    set<int> colValues;
    for (int i = 0; i <= row; ++i) {
        int value = _board.at(i).at(col);
        if (value < 0) {
            continue;
        }
        if (colValues.count(value) == 1) {
            return false;
        }
        colValues.insert(value);
    }

    if (row > 0) {
        if (_board.at(row).at(col) < 0 && _board.at(row - 1).at(col) < 0) {
            return false;
        }
    }

    if (col > 0) {
        if (_board.at(row).at(col) < 0 && _board.at(row).at(col - 1) < 0) {
            return false;
        }
    }

    return true;
}

bool HitoriConfig::isSurrounded(int row, int col) const {
    if (row < 0 || col < 0) {
        return false;
    }

    if (row > 0 && _board.at(row - 1).at(col) > 0) {
        return false;
    }

    if (row < _n - 1 && _board.at(row + 1).at(col) > 0) {
        return false;
    }

    if (col > 0 && _board.at(row).at(col - 1) > 0) {
        return false;
    }

    if (col < _n - 1 && _board.at(row).at(col + 1) > 0) {
        return false;
    }

    return true;
}

bool HitoriConfig::whiteConnected() const {
    int row, col;
    if (_board.at(0).at(0) > 0) {
        row = 0;
        col = 0;
    } else {
        row = 0;
        col = 1;
    }

    stack<pair<int, int>> st;
    st.push(pair<int, int>(row, col));
    set<pair<int, int>> visited;

    while (!st.empty()) {
        pair<int, int> current = st.top();
        visited.insert(current);
        st.pop();
        row = current.first;
        col = current.second;
        if (row > 0 && _board.at(row - 1).at(col) > 0) {
            pair<int, int> p(row - 1, col);
            if (visited.count(p) == 0) {
                visited.insert(p);
                st.push(p);
            }
        }

        if (row < _n - 1 && _board.at(row + 1).at(col) > 0) {
            pair<int, int> p(row + 1, col);
            if (visited.count(p) == 0) {
                visited.insert(p);
                st.push(p);
            }
        }

        if (col > 0 && _board.at(row).at(col - 1) > 0) {
            pair<int, int> p(row, col - 1);
            if (visited.count(p) == 0) {
                visited.insert(p);
                st.push(p);
            }
        }

        if (col < _n - 1 && _board.at(row).at(col + 1) > 0) {
            pair<int, int> p(row, col + 1);
            if (visited.count(p) == 0) {
                visited.insert(p);
                st.push(p);
            }
        }
    }

    return (int) visited.size() == _white_count;
}

vector<HitoriConfig> HitoriConfig::getSuccessors() const {
    vector<HitoriConfig> successors;

    if (_row == _n) {
        return successors;
    }

    int row = _row;
    int col = _col + 1;

    if (col == _n) {
        col = 0;
        ++row;
    }

    HitoriConfig base(*this);
    base._col = col;
    base._row = row;
    HitoriConfig flipped(*this);
    flipped._board.at(_row).at(_col) *= -1;
    flipped._col = col;
    flipped._row = row;

    if (base._board.at(_row).at(_col) < 0) {
        --base._white_count;
    } else {
        --flipped._white_count;
    }

    successors.push_back(base);
    successors.push_back(flipped);

    return successors;
}

string HitoriConfig::str() const {
    ostringstream oss;
    oss << *this;
    return oss.str();
}

ostream& operator<<(ostream& os, const HitoriConfig& config) {
    for (int row = 0; row < config._n; ++row) {
        for (auto val : config._board.at(row)) {
            os << val << "\t";
        }
        if (row < config._n - 1) {
            os << "\n";
        }
    }
    return os;
}
