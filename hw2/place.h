// File: place.h
// Author: Liam Morris
// Description: A class that represents a specific geographical place.

#ifndef PLACE_H
#define PLACE_H

#include <ostream>
#include <string>
#include <vector>

class Place {
    public:
        Place(const std::string& country,
              const std::string& region,
              const std::string& city,
              const std::string& latitude,
              const std::string& longitude);

        // Computes the distance to another Place
        // Input:
        //   'other' - the place to which distance is being computed
        // Output:
        //   the distance (in miles) to the location
        double dist(const Place* other) const;

        // Finds the closest Place from a list of Places
        // Input:
        //   'places' - the list of places
        // Output:
        //   the Place which is closest to this Place
        const Place* closest(const std::vector<Place*>& places) const;

        const std::string& getCountry() const;
        const std::string& getCity() const;
        const std::string& getRegion() const;
        double getLatitude() const;
        double getLongitude() const;

        friend std::ostream& operator<<(std::ostream& os, const Place& p);

    private:
        std::string _country;
        std::string _region;
        std::string _city;
        double _latitude;
        double _longitude;
};

#endif  // PLACE_H
