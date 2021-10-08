#include <iostream>
#include <vector>

#include "include/deck.h"

namespace mns {
    const std::vector<std::string> menu = {"0. Quit", "1. Rules", "2. Default init",
                                           "4. One card init", "5. Input", "6. Output",
                                           "7. Add one card", "8. Get card by number",
                                           "9. Sorting", "10. Get by suit"};
}

int main() {
    int c = 0;
    do {
        for (int i = 0; mns::menu.size(); i++)
            std::cout << "\n" << mns::menu[i];
        std::cout << std::endl << "Choose an option: ";
        std::cin >> c;
        switch (c) {
            case 0:
                break;
        }
    } while(c);
    return 0;
}