#include <iostream>
#include <vector>

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
        int num;
        std::string suit, rank;
        switch (c) {
            case 0:
                break;
            case 1:
                std::cout << "Some rules\n";
                break;
            case 2:
                deck = Deck();
                break;
            case 3:
                std::cin >> num;
                deck = Deck(num);
                break;
            case 4:
                std::cin >> rank >> suit;
                deck = Deck(suit, rank);
                break;
            case 5:
                deck.Input();
                break;
            case 6:
                deck.Output();
                break;
            case 7:
                deck.addRandCard();
                break;
            case 8:
                std::cin >> num;
                std::cout << deck.getRank(num) << deck.getSuit(num) << std::endl;
                break;
            case 9:
                deck.Sort();
                break;
            case 10:
                std::cin >> suit;
                deck.getAllBySuit(suit);
                break;
        }
    } while(c);
    return 0;
}