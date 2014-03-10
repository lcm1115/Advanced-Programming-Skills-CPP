#ifndef PLACE_H
#define PLACE_H

#include <ostream>
#include <string>
#include <vector>

class Place {
    public:
        Place(const std::vector<std::string>& data);

        double dist(const Place* other) const;

        const Place* closest(const std::vector<Place*>& places) const;

        const std::string& getCountry() const;
        const std::string& getCity() const;
        const std::string& getRegion() const;
        double getLatitude() const;
        double getLongitude() const;

        bool operator<(const Place& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Place& p);

    private:
        std::string _country;
        std::string _city;
        std::string _region;
        double _latitude;
        double _longitude;
};

#endif  // PLACE_H
