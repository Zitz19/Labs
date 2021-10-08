#include <vector>
#include <cstdlib>
#include <algorithm>

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
        std::cout << "___ERROR___\n";
        num = 0;
        return;
    }
    cards[0].suit = i_suit;
    cards[0].rank = i_rank;
}

void Deck::Input() {
    std::cout << "Enter the number of cards: ";
    int num;
    std::cin >> num;
    if (num <= 0 || num > 52) {
        std::cout << "___ERROR___\n";
        return;
    }
    this->num = num;
    std::cout << "Enter " << num << " cards in format '10 H':\n";
    std::string suit, rank, err;
    int i_suit, i_rank;
    for (int i = 0; i < num; i++) {
        err = "";
        do {
            std::cout << err;
            std::cin >> rank >> suit;
            i_suit = nameToInt(Deck::Suits, suit);
            i_rank = nameToInt(Deck::Ranks, rank);
            err = "This card exist, try again.\n";
        } while (find(i_suit, i_rank));
        if (i_suit == -1 || i_rank == -1) {
            std::cout << "___ERROR___\n";
            num = 0;
            return;
        }
        cards[i].suit = i_suit;
        cards[i].rank = i_rank;
    }
}

void Deck::Output() {
    for (int i = 0; i < this->num; i++) {
        std::cout << Ranks[cards[i].rank] << Suits[cards[i].suit] << std::endl;
    }
}

void Deck::addRandCard() {
    std::srand(time(nullptr));
    int suit = std::rand() % Deck::Suits.size();
    int rank = std::rand() % Deck::Ranks.size();
    if (find(suit, rank)) {
        std::cout << "This card exist\n";
        return;
    }
    num++;
    if (num > 52) {
        std::cout << "___ERROR___\n";
        num--;
        return;
    }
    cards[num - 1].suit = suit;
    cards[num - 1].rank = rank;
}

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
    for (int i = 0; i < num; i++)
        if (cards[i].suit == i_suit)
            std::cout << Deck::Ranks[cards[i].rank] << Deck::Suits[cards[i].suit] << std::endl;
}