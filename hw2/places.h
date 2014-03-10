#ifndef PLACES_H
#define PLACES_H

#include "place.h"

#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>

class Places {
    public:
        void insertPlace(Place* place);

        const Place* getPlace(std::string country,
                              std::string region,
                              std::string city) const;

        ~Places();

        bool dupLocation(const Place* place) const;

        const std::vector<Place*>& getPlaces() const;

        int size() const;

        const Place* readPlace() const;
        
        std::pair<Place*, Place*> closestPairBF(
                const std::deque<Place*>* points) const;

        std::pair<Place*, Place*> closestPair();

        std::pair<Place*, Place*> closestPair(
                std::deque<Place*>* pointsX, std::deque<Place*>* pointsY);

        void deletePlaces();

    private:
        std::map<std::string,
                 std::map<std::string,
                          std::map<std::string, Place*>>> _placeMap;

        std::vector<Place*> _places;

        std::set<std::pair<double, double>> _coords;
};

#endif  // PLACES_H
