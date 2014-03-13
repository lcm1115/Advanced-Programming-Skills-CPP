#include "place.h"

#include <cmath>
#include <cstdlib>
#include <ostream>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

const double TO_RADIANS = M_PI / 180;
const double EARTH_RADIUS = 3961;

Place::Place(const vector<string>& data) {
    _country = data.at(0);
    _city = data.at(1);
    _region = data.at(3);
    _latitude = atof(data.at(5).c_str());
    _longitude = atof(data.at(6).c_str());
}

double Place::dist(const Place* other) const {
    double dlon = (other->_longitude - _longitude) * TO_RADIANS;
    double dlat = (other->_latitude - _latitude) * TO_RADIANS;
    double slat = sin(dlat / 2) * sin(dlat / 2);
    double slon = sin(dlon / 2) * sin(dlon / 2);
    double clat1 = cos(_latitude * TO_RADIANS);
    double clat2 = cos(other->_latitude * TO_RADIANS);
    double a = slat + clat1 * clat2 * slon;
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = EARTH_RADIUS * c;
    return d;
}

const Place* Place::closest(const vector<Place*>& places) const {
    int index = 0;
    double d = INFINITY;
    for (unsigned int i = 0; i < places.size(); ++i) {
        if (_latitude == places.at(i)->_latitude &&
            _longitude == places.at(i)->_longitude) {
            continue;
        }

        double temp_d = dist(places.at(i));
        if (temp_d < d) {
            d = temp_d;
            index = i;
        }
    }

    return places.at(index);
}

bool Place::operator<(const Place& other) const {
    return _latitude < other._latitude;
}

const string& Place::getCountry() const {
    return _country;
}

const string& Place::getCity() const {
    return _city;
}

const string& Place::getRegion() const {
    return _region;
}

double Place::getLatitude() const {
    return _latitude;
}

double Place::getLongitude() const {
    return _longitude;
}

ostream& operator<<(ostream& os, const Place& p) {
    os << "Country: " << p.getCountry() << ", "
       << "City: " << p.getCity() << ", "
       << "Region: " << p.getRegion() << ", "
       << "Latitude: " << p.getLatitude() << ", "
       << "Longitude: " << p.getLongitude();
    return os;
}
