#pragma once

#include <iostream>
#include <vector>

typedef struct Card {
    int suit;
    int rank;
} Card;

class Deck {
private:
    int num = 0;
    Card *cards = nullptr;
    int cap = 4;

    int nameToInt(const std::vector<std::string>& nameVector, const std::string& name);
    void swap(Card &x, Card &y);
    bool find(int suit, int rank);
    void Increase();
public:
    static const std::vector<std::string> Suits;
    static const std::vector<std::string> Ranks;

    Deck() = default;
    Deck(int num);
    Deck(const Deck& deck);
    Deck(Deck&& deck);
    Deck(std::string& suit, std::string& rank);
    ~Deck();
    void Sort();
    std::ostream& getAllBySuit(std::ostream&, std::string suit);

    friend std::ostream& operator<<(std::ostream& out, const Deck& deck);
    friend std::istream& operator>>(std::istream& in, Deck& deck);
    const std::string operator[](int pos) const;
    Deck& operator++();
    Deck& operator=(const Deck& deck);
    Deck& operator=(Deck&& deck);
};