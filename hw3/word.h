// File: word.h
// Author: Liam Morris
// Description: A class that represents a word node in a graph of words.

#include <string>
#include <map>
#include <vector>

class Word {
    public:
        // Constructs a word with a given string.
        // Input:
        //   string word - the string to store in the word
        Word(std::string word);
       
        // Computes the distance to another word.
        // Input:
        //   const Word& w - the word to compare to
        // Output:
        //   int - the distance between the two words
        int distance(const Word& w) const;

        // Accesses a word's neighbors
        // Output:
        //   map<Word*, int> - word:distance pairs of neighbors
        std::map<Word*, int> getNeighbors();

        // Adds a word as a neighbor with a given distance.
        // Input:
        //   Word* neighbor - the word to be stored as a neighbor
        //   int distance - the distance to the word
        void addNeighbor(Word* neighbor, int distance);

        // Sets the distance from the start node (in Dijkstra's algorithm)
        // Input:
        //   int distance - the distance to be stored
        void setDistance(int distance);

        // Returns the distance from the start node (in Dijkstra's algorithm)
        // Output:
        //   int - the distance from the start node
        int getDistance() const;

        // Returns the string stored in the word.
        // Output:
        //   string - the string stored in the word
        std::string getWord() const;

        // Marks the word as visited in a run of Dijkstra's algorithm
        void markVisited();

        // Returns visited status of the word.
        // Output:
        //   bool - true if visited, false otherwise
        bool isVisited() const;

        bool operator<(const Word& rhs) const;
        
        bool operator==(const Word& rhs) const;

    private:
        // Visited status of word.
        bool _visited;

        // Distance from start node.
        int _distance;

        // String stored in word.
        std::string _word;

        // word:distance pairings of neighbors
        std::map<Word*, int> _neighbors;
};
