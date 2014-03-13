#ifndef PLACES_H
#define PLACES_H

#include "place.h"

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
                const std::vector<Place*>& points) const;

        std::pair<Place*, Place*> closestPair();

        std::pair<Place*, Place*> closestPair(const std::vector<Place*>& places);

        void deletePlaces();

    private:
        std::vector<Place*> _places;

        std::set<std::pair<double, double>> _coords;
};

#endif  // PLACES_H
