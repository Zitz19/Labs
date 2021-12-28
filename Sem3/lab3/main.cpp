#include <vector>

#include "include/table.h"
#include "include/mymap.h"

namespace mns {
    std::vector<std::string> menu = {"0. Quit", "1. Add Daytime group", "2. Add Evening group",
                                     "3. Add Commercial group", "4. Print Table", "5. Remove group"};
}

int main() {
    Table table;
    std::string specialization, addInfo;
    int num, kaf, term;
    int index;
    int c = 0;
    do {
        std::cout << std::endl;
        for (int i = 0; i < mns::menu.size(); i++)
            std::cout << mns::menu[i] << std::endl;
        std::cout << "\nChoose option: ";
        std::cin >> c;
        switch (c) {
            case 0:
                break;
            case 1:
                std::cout << "Enter a Daytime group info. Format is: \n\n"
                << "'Number of students' 'Number of kaf' 'Term of studying' 'Specialization'\n"
                << "'Stipendia' 'Number of stipendiats'\n";
                std::cin >> num >> kaf >> term >> specialization;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, addInfo);
                table.addGroup("Daytime", num, kaf, term, specialization, addInfo);
                break;
            case 2:
                std::cout << "Enter a Daytime group info. Format is: \n\n"
                << "'Number of students' 'Number of kaf' 'Term of studying' 'Specialization'\n"
                << "'Group age' 'Qualification'\n";
                std::cin >> num >> kaf >> term >> specialization;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, addInfo);
                table.addGroup("Evening", num, kaf, term, specialization, addInfo);
                break;
            case 3:
                std::cout << "Enter a Daytime group info. Format is: \n\n"
                << "'Number of students' 'Number of kaf' 'Term of studying' 'Specialization'\n"
                << "'Contract number' 'Price'\n";
                std::cin >> num >> kaf >> term >> specialization;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, addInfo);
                table.addGroup("Commercial", num, kaf, term, specialization, addInfo);
                break;
            case 4:
                table.printTable();
                break;
            case 5:
                std::cout << "Enter group index: ";
                std::cin >> index;
                table.removeGroup(index);
                break;
        }
    } while (c);
    return 0;
}