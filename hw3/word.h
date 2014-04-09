#include <string>
#include <map>
#include <vector>

class Word {
    public:
        Word(std::string word);
        
        int distance(const Word& s) const;

        int diffCount(const Word& s) const;

        std::map<Word*, int> getNeighbors();

        void addNeighbor(Word* neighbor, int distance);

        void setDistance(int distance);

        int getDistance() const;

        std::string getWord() const;

        void markVisited();

        bool isVisited() const;

        bool operator<(const Word& rhs) const;
        
        bool operator==(const Word& rhs) const;
    private:
        bool _visited;
        int _distance;
        std::string _word;
        std::map<Word*, int> _neighbors;
};

class WordCompare {
    public:
        bool operator()(const Word* w1, const Word* w2) const;
};
