#include "corridor.h"
#include <iostream>

using namespace std;

// The main program for the Corridor problem.  If the program
// is run with any extra arguments, debug output is done,
// otherwise non-debug output is done.
int main(int argc, char* argv[]) {
    unsigned int numTests;
    cin >> numTests;

    while (numTests-- > 0) {
        Corridor c;
        if (argc > 1) cout << c;
        cout << "Fits? " << c.check() << endl;
    }

    return 0;
}
