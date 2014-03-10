#include "place.h"
#include "places.h"
#include "util.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using std::chrono::system_clock;

void Places::insertPlace(Place* place) {
    const string& country = place->getCountry();
    const string& region = place->getRegion();
    const string& city = place->getCity();
    if (!dupLocation(place)) {
        if (_placeMap.find(country) == _placeMap.end()) {
            _placeMap[country] = map<string, map<string, Place*>>();
        }

        map<string, map<string, Place*>>& regionMap = _placeMap.at(country);
        if (regionMap.find(region) == regionMap.end()) {
            regionMap[region] = map<string, Place*>();
        }

        map<string, Place*>& cityMap = regionMap.at(region);
        cityMap.insert(pair<string, Place*>(city, place));
        _coords.insert(pair<double, double>(place->getLatitude(),
                                           place->getLongitude()));
        _places.push_back(place);
    } else {
        delete place;
    }
}

const Place* Places::getPlace(
        string country, string region, string city) const {
    if (_placeMap.find(country) != _placeMap.end()) {
        const map<string, map<string, Place*>>& regionMap = _placeMap.at(country);
        if (regionMap.find(region) != regionMap.end()) {
            const map<string, Place*>& cityMap = regionMap.at(region);
            if (cityMap.find(city) != cityMap.end()) {
                return cityMap.at(city);
            }
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

pair<Place*, Place*> Places::closestPairBF(const deque<Place*>* points) const {
    double dist = INFINITY;
    pair<Place*, Place*> p;
    for (unsigned int i = 0; i < points->size(); ++i) {
        for (unsigned int j = i + 1; j < points->size(); ++j) {
            double d = points->at(i)->dist(points->at(j));
            if (d < dist) {
                dist = d;
                p.first = points->at(i);
                p.second = points->at(j);
            }
        }
    }

    return p;
}

pair<Place*, Place*> Places::closestPair() {
    deque<Place*> pointsX, pointsY;

    for (auto it : _places) {
        pointsX.push_back(it);
        pointsY.push_back(it);
    }
    
    sort(pointsX.begin(),
         pointsX.end(),
         [](const Place* p1, const Place* p2) {
            return p1->getLongitude() < p2->getLongitude();
         });
    
    sort(pointsY.begin(),
         pointsY.end(),
         [](const Place* p1, const Place* p2) {
            return p1->getLongitude() < p2->getLongitude();
         });

    return closestPair(&pointsX, &pointsY);
}

pair<Place*, Place*> Places::closestPair(
        deque<Place*>* pointsX, deque<Place*>* pointsY) {

    if (pointsX->size() <= 3) {
        return closestPairBF(pointsX);
    }

    unsigned int numPoints = pointsX->size() / 2;

    double median = pointsX->at(numPoints)->getLongitude();
    pair<Place*, Place*> p;
    deque<Place*> leftX, leftY, rightX, rightY;

    for (auto it : *pointsX) {
        if (it->getLongitude() < median) {
            leftX.push_back(it);
        } else {
            rightX.push_back(it);
        }
    }

    for (auto it : *pointsY) {
        if (it->getLongitude() < median) {
            leftY.push_back(it);
        } else {
            rightY.push_back(it);
        }
    }

    while (leftX.size() < 2) {
        Place* pX = rightX.front();
        rightX.pop_front();
        leftX.push_back(pX);

        Place* pY = rightY.front();
        rightY.pop_front();
        leftY.push_back(pY);
    }

    while (rightX.size() < 2) {
        Place* pX = leftX.back();
        leftX.pop_back();
        rightX.push_front(pX);

        Place* pY = leftY.back();
        leftY.pop_back();
        rightY.push_front(pY);
    }

    pair<Place*, Place*> leftClosest = closestPair(&leftX, &leftY);
    pair<Place*, Place*> rightClosest = closestPair(&rightX, &rightY);
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

    deque<Place*> closeY;

    for (auto it : *pointsY) {
        if (abs(it->getLongitude() - median) < minDist) {
            closeY.push_back(it);
        }
    }

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
    _placeMap.clear();
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
