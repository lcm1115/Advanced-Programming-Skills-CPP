#include "util.h"

#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::stringstream;
using std::vector;

vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}
