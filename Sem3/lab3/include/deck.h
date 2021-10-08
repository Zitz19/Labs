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
    inline std::string getSuit(int pos) { return Deck::Suits[cards[pos].suit]; }
    inline std::string getRank(int pos) { return Deck::Ranks[cards[pos].rank]; }
    void Input();
    void Output();
    void addRandCard();
    void Sort();
    void getAllBySuit(std::string suit);
};