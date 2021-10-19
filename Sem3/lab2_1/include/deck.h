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
    Card cards[52];

    int nameToInt(const std::vector<std::string>& nameVector, const std::string& name);
    void swap(Card &x, Card &y);
    bool find(int suit, int rank);
public:
    static const std::vector<std::string> Suits;
    static const std::vector<std::string> Ranks;

    Deck() = default;
    Deck(int num);
    Deck(std::string& suit, std::string& rank);
//    const std::string& getSuit(int pos) const;
//    const std::string& getRank(int pos) const;
//    std::istream& Input(std::istream& in, int num);
//    std::ostream& Output(std::ostream& out) const;
//    void addRandCard();
    void Sort();
    void getAllBySuit(std::string suit);

    friend std::ostream& operator<<(std::ostream& out, const Deck& deck);
    friend std::istream& operator>>(std::istream& in, Deck& deck);
    const std::string operator[](int pos) const;
    Deck& operator++();
};