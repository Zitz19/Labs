#include <iostream>
#include <vector>
#include <limits>

#include "include/deck.h"

namespace mns {
    const std::vector<std::string> menu = {"0. Quit", "1. Rules", "2. Default init", "3. Random num init",
                                           "4. One card init", "5. Input", "6. Output",
                                           "7. Add one card", "8. Get card by number",
                                           "9. Sorting", "10. Get by suit"};
}

int main() {
    int c = 0;
    Deck deck;
    do {
        for (int i = 0; i < mns::menu.size(); i++)
            std::cout << "\n" << mns::menu[i];
        std::cout << std::endl << "Choose an option: ";
        std::cin >> c;
        while (std::cin.fail()) {
            if (std::cin.eof()) {
                c = 0;
                break;
            }
            std::cout << "___Not valid value___";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> c;
        }
        int num;
        std::string suit, rank;
        switch (c) {
            case 0:
                break;
            case 1:
                std::cout << "Enter a card in format '10 H' or 'K S'\n";
                break;
            case 2:
                deck = Deck();
                break;
            case 3:
                std::cout << "Enter number of cards:\n";
                std::cin >> num;
                try {
                    deck = Deck(num);
                }
                catch (std::invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 4:
                std::cin >> rank >> suit;
                try {
                    deck = Deck(suit, rank);
                }
                catch (std::invalid_argument& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case 5:
                std::cout << "Enter the number of cards: ";
                try {
                    std::cin >> deck;
                }
                catch (std::invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 6:
                std::cout << deck;
                break;
            case 7:
                try {
                    ++deck;
                }
                catch (std::invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 8:
                std::cout << "Enter card index: ";
                std::cin >> num;
                try {
                    std::cout << deck[num] << std::endl;
                }
                catch (std::invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 9:
                deck.Sort();
                break;
            case 10:
                std::cout << "Enter a suit: ";
                std::cin >> suit;
                try {
                    deck.getAllBySuit(cout, suit);
                }
                catch (std::invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
        }
    } while(c);
    return 0;
}