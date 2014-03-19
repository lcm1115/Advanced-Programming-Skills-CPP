// File: places.h
// Author: Liam Morris
// Description: Places class for closest pair. Can read in files of locations,
//              create list of places, and find closest pair of places.

#ifndef PLACES_H
#define PLACES_H

#include "place.h"

#include <map>
#include <set>
#include <string>
#include <vector>

class Places {
    public:
        // Inserts a place into list of places
        // Input:
        //   'place' - the place to be inserted
        void insertPlace(Place* place);

        // Finds a place given location parameters
        // Input:
        //   'country' - place's country
        //   'region' - place's region
        //   'city' - place's city
        const Place* getPlace(std::string country,
                              std::string region,
                              std::string city) const;

        ~Places();

        // Determines if a location is a duplicate location
        // Input:
        //   'place' - the place to check
        // Output:
        //   true if 'place' already exists, false otherwise
        bool dupLocation(const Place* place) const;

        const std::vector<Place*>& getPlaces() const;

        int size() const;

        // Reads in place parameters from stdin and constructs a Place object
        // Output:
        //   a new Place with parameters retrieved from stdin
        const Place* readPlace() const;
        
        // Brute force implementation of closest pair of points
        // Input:
        //   'points' - the list of Places to process
        // Output:
        //   the closest pair of places
        std::pair<Place*, Place*> closestPairBF(
                const std::vector<Place*>& points) const;

        std::pair<Place*, Place*> closestPair();

        // Finds closest pair of places using better algorithm
        // Input:
        //   'places' - the list of places
        // Output:
        //   the closest pair of places
        std::pair<Place*, Place*> closestPair(const std::vector<Place*>& places);

        // Deletes all places from list of places
        void deletePlaces();

    private:
        std::vector<Place*> _places;

        std::set<std::pair<double, double>> _coords;
};

#endif  // PLACES_H
