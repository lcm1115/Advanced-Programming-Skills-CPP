#include "place.h"
#include "places.h"
#include "util.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

using namespace std;
using std::chrono::system_clock;

void Places::insertPlace(Place* place) {
    if (!dupLocation(place)) {
        _coords.insert(pair<double, double>(place->getLatitude(),
                                           place->getLongitude()));
        _places.push_back(place);
    } else {
        delete place;
    }
}

const Place* Places::getPlace(
        string country, string region, string city) const {
    for (auto it : _places) {
        if (it->getCountry() == country &&
            it->getRegion() == region &&
            it->getCity() == city) {
            return it;
        }
    }

    return NULL;
}

Places::~Places() {
    deletePlaces();
}

bool Places::dupLocation(const Place* place) const {
    pair<double, double> p(place->getLatitude(), place->getLongitude());
    return _coords.find(p) != _coords.end();
}

const vector<Place*>& Places::getPlaces() const {
    return _places;
}

int Places::size() const {
    return _coords.size();
}

const Place* Places::readPlace() const {
    string country, region, city;
    cout << "Enter Place..." << endl;
    cout << "Country: ";
    cin >> country;
    cout << "City: ";
    cin >> city;
    cout << "Region: ";
    cin >> region;
    return getPlace(country, region, city);
}

pair<Place*, Place*> Places::closestPairBF(const vector<Place*>& points) const {
    double dist = INFINITY;
    pair<Place*, Place*> p;
    for (unsigned int i = 0; i < points.size(); ++i) {
        for (unsigned int j = i + 1; j < points.size(); ++j) {
            double d = points.at(i)->dist(points.at(j));
            if (d < dist) {
                dist = d;
                p.first = points.at(i);
                p.second = points.at(j);
            }
        }
    }

    return p;
}

pair<Place*, Place*> Places::closestPair() {
    sort(_places.begin(),
         _places.end(),
         [](const Place* p1, const Place* p2) {
            return p1->getLongitude() < p2->getLongitude();
         });

    return closestPair(_places);
}

pair<Place*, Place*> Places::closestPair(const vector<Place*>& places) {
    if (places.size() <= 3) {
        return closestPairBF(places);
    }

    unsigned int numPoints = places.size() / 2;

    double median = places.at(numPoints)->getLongitude();
    pair<Place*, Place*> p;
    vector<Place*> left, right;

    for (auto it : places) {
        if (it->getLongitude() < median) {
            left.push_back(it);
        } else {
            right.push_back(it);
        }
    }

    while (left.size() < 2) {
        Place* p = right.front();
        right.erase(right.begin());
        left.push_back(p);
    }

    while (right.size() < 2) {
        Place* p = left.back();
        left.pop_back();
        right.insert(right.begin(), p);
    }

    pair<Place*, Place*> leftClosest = closestPair(left);
    pair<Place*, Place*> rightClosest = closestPair(right);
    double ldist = leftClosest.first->dist(leftClosest.second);
    double rdist = rightClosest.first->dist(rightClosest.second);
    
    double minDist = 0;
    if (ldist < rdist) {
        p = leftClosest;
        minDist = ldist;
    } else {
        p = rightClosest;
        minDist = rdist;
    }

    vector<Place*> closeY;
    for (auto it : places) {
        if (abs(it->getLongitude() - median) < minDist) {
            closeY.push_back(it);
        }
    }

    sort(closeY.begin(),
         closeY.end(),
         [](const Place* p1, const Place* p2) {
            return p1->getLatitude() < p2->getLatitude();
         });

    if (closeY.size() > 1) {
        for (unsigned int i = 0; i < closeY.size() - 1; ++i) {
            for (unsigned int j = i + 1; j < closeY.size() && j < i + 8; ++j) {
                double dist = closeY.at(i)->dist(closeY.at(j));
                if (dist < minDist) {
                    minDist = dist;
                    p.first = closeY.at(i);
                    p.second = closeY.at(j);
                }
            }
        }
    }

    return p;
}

void Places::deletePlaces() {
    _coords.clear();
    while (!_places.empty()) {
        Place* p = _places.back();
        _places.pop_back();
        delete p;
    }
}

int main() {
    Places places;
    while (true) {
        string input;
        cout << "> ";
        cin >> input;
        system_clock::time_point start = system_clock::now();
        if (input == "read") {
            cin >> input;

            ifstream file;
            file.open(input.c_str(), ifstream::in);
            getline(file, input);
            int numLines = 0;
            places.deletePlaces();
            while (getline(file, input)) {
                vector<string> tokens = split(input, ',');
                Place* p = new Place(tokens);
                places.insertPlace(p);
                ++numLines;
            }
            if (numLines > places.size()) {
                cout << "Removed " << (numLines - places.size())
                     << " duplicate places." << endl;
            }
            cout << "There are " << places.size() << " unique places." << endl;
        } else if (input == "closest") {
            const Place* p = places.readPlace();
            start = system_clock::now();
            if (p == NULL) {
                const Place* closest = p->closest(places.getPlaces());
                cout << *p << endl;
                cout << closest << endl;
                cout << p->dist(closest) << " miles apart." << endl;
            } else {
                cout << "City not found." << endl;
            }
        } else if (input == "closestAll") {
            pair<Place*, Place*> p = places.closestPair();
            double dist = p.first->dist(p.second);
            cout << *p.first << endl;
            cout << *p.second << endl;
            cout << dist << " miles apart." << endl;
        } else if (input == "distance") {
            const Place* p1 = places.readPlace();
            if (p1 == NULL) {
                cout << "City not found." << endl;
                continue;
            }

            const Place* p2 = places.readPlace();
            if (p2 == NULL) {
                cout << "City not found." << endl;
                continue;
            }

            start = system_clock::now();
            cout << *p1 << endl;
            cout << *p2 << endl;
            cout << p1->dist(p2) << " miles away." << endl;
        } else if (input == "find") {
            const Place* p = places.readPlace();
            start = system_clock::now();
            if (p == NULL) {
                cout << *p << endl;
            } else {
                cout << "City not found." << endl;
            }

        } else if (input == "help") {
            cout << "closest: find the closest place to one place" << endl
                 << "closestAll: find the closest pair from all places" << endl
                 << "distance: find the distance between two places" << endl
                 << "find: find a place" << endl
                 << "help: display this help message" << endl
                 << "read: read a new collection of places" << endl
                 << "quit: exit the program" << endl;
        } else if (input == "quit" || cin.eof()) {
            cout << endl;
            break;
        } else {
        }
        system_clock::time_point end = system_clock::now();
        time_t diff = system_clock::to_time_t(end) -
                      system_clock::to_time_t(start);
        cout << "*** elapsed time: " << diff << " seconds." << endl;
    }

    return 0;
}
