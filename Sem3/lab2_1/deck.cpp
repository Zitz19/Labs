#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>

#include "include/deck.h"

const std::vector<std::string> Deck::Suits = {"H", "D", "C", "S"};
const std::vector<std::string> Deck::Ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

int Deck::nameToInt(const std::vector<std::string>& nameVector, const std::string& name) {
    for (int i = 0; i < nameVector.size(); i++)
        if (nameVector[i] == name) return i;
    return -1;
}

void Deck::swap(Card &x, Card &y) {
    Card t = x;
    x = y;
    y = t;
}

bool Deck::find(int suit, int rank) {
    for (int i = 0; i < num; i++) {
        if (cards[i].suit == suit && cards[i].rank == rank)
            return 1;
    }
    return 0;
}

Deck::Deck(int num): num(num) {
    if (num < 0 || num > 52) throw std::invalid_argument("___Num is invalid value___");
    std::srand(time(nullptr));
    std::vector<Card> rand_vector;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 13; j++) {
            Card tmp;
            tmp.suit = i;
            tmp.rank = j;
            rand_vector.push_back(tmp);
        }
    std::random_shuffle(rand_vector.begin(), rand_vector.end());
    for (int i = 0; i < num; i++) {
        cards[i].suit = rand_vector[i].suit;
        cards[i].rank = rand_vector[i].rank;
    }
}

Deck::Deck(std::string& suit, std::string& rank): num(1) {
    int i_suit = nameToInt(Deck::Suits, suit);
    int i_rank = nameToInt(Deck::Ranks, rank);
    if (i_suit == -1 || i_rank == -1) {
        num = 0;
        throw std::invalid_argument("___Invalid input___");
    }
    cards[0].suit = i_suit;
    cards[0].rank = i_rank;
}
/*
// OLD INPUT
std::istream& Deck::Input(std::istream& in, int num) {
    if (num < 0 || num > 52) throw std::invalid_argument("___Invalid number___");
    memset(this->cards, 0, sizeof(this->cards));
    this->num = num;
    std::string suit, rank;
    int i_suit, i_rank;
    for (int i = 0; i < num; i++) {
        in >> rank >> suit;
        i_suit = nameToInt(Deck::Suits, suit);
        i_rank = nameToInt(Deck::Ranks, rank);
        if (i_suit == -1 || i_rank == -1) {
            this->num = i;
            throw std::invalid_argument("___Invalid card input___");
        }
        if (find(i_suit, i_rank)) {
            this->num = i;
            throw std::invalid_argument("___Card repetition___");
        }
        cards[i].suit = i_suit;
        cards[i].rank = i_rank;
    }
    return in;
}
*/
// OLD OUTPUT
/*
std::ostream& Deck::Output(std::ostream& out) const {
    for (int i = 0; i < this->num; i++) {
        out << Ranks[cards[i].rank] << ' ' << Suits[cards[i].suit] << std::endl;
    }
    return out;
}
*/
/*
// OLD INCREMENT
void Deck::addRandCard() {
    std::srand(time(nullptr));
    int suit, rank;
    if (num == 52) {
        throw std::invalid_argument("___Deck overflow___");
    }
    do {
        suit = std::rand() % Deck::Suits.size();
        rank = std::rand() % Deck::Ranks.size();
    } while (find(suit, rank));
    num++;
    cards[num - 1].suit = suit;
    cards[num - 1].rank = rank;
}
*/
/*
// OLD GETTERS
const std::string& Deck::getSuit(int pos) const {
    if (pos < 0 || pos > 52) throw std::invalid_argument("___Invalid index___");
    return Deck::Suits[cards[pos].suit];
}

const std::string& Deck::getRank(int pos) const {
    if (pos < 0 || pos > 52) throw std::invalid_argument("___Invalid index___");
    return Deck::Ranks[cards[pos].rank];
}
*/
void Deck::Sort() {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (cards[j].suit * 100 + cards[j].rank < cards[j + 1].suit * 100 + cards[j + 1].rank)
                swap(cards[j], cards[j + 1]);
        }
    }
}

void Deck::getAllBySuit(std::string suit) {
    int i_suit = nameToInt(Deck::Suits, suit);
    if (i_suit == -1) {
        throw std::invalid_argument("___Invalid suit___");
    }
    for (int i = 0; i < num; i++)
        if (cards[i].suit == i_suit)
            std::cout << Deck::Ranks[cards[i].rank] << Deck::Suits[cards[i].suit] << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Deck& deck) {
    for (int i = 0; i < deck.num; i++) {
        out << Deck::Ranks[deck.cards[i].rank] << ' ' << Deck::Suits[deck.cards[i].suit] << std::endl;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Deck& deck) {
    int num;
    in >> num;
    if (num < 0 || num > 52) throw std::invalid_argument("___Invalid number___");
    memset(deck.cards, 0, sizeof(deck.cards));
    deck.num = num;
    std::string suit, rank;
    int i_suit, i_rank;
    for (int i = 0; i < num; i++) {
        in >> rank >> suit;
        i_suit = deck.nameToInt(Deck::Suits, suit);
        i_rank = deck.nameToInt(Deck::Ranks, rank);
        if (i_suit == -1 || i_rank == -1) {
            deck.num = i;
            throw std::invalid_argument("___Invalid card input___");
        }
        if (deck.find(i_suit, i_rank)) {
            deck.num = i;
            throw std::invalid_argument("___Card repetition___");
        }
        deck.cards[i].suit = i_suit;
        deck.cards[i].rank = i_rank;
    }
    return in;
}

const std::string Deck::operator[](int pos) const {
    if (pos < 0 || pos > 52 || pos >= this->num) throw std::invalid_argument("___Invalid index___");
    return Deck::Ranks[this->cards[pos - 1].rank] + ' ' + Deck::Suits[this->cards[pos - 1].suit];
}

Deck& Deck::operator++() {
    std::srand(time(nullptr));
    int suit, rank;
    if (num == 52) {
        throw std::invalid_argument("___Deck overflow___");
    }
    do {
        suit = std::rand() % Deck::Suits.size();
        rank = std::rand() % Deck::Ranks.size();
    } while (find(suit, rank));
    num++;
    cards[num - 1].suit = suit;
    cards[num - 1].rank = rank;
    return *this;
}