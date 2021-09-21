#include <iostream>
#include <vector>
#include "include/class.h"

namespace mns {
    std::vector<std::string> menu = {"0. Quit", "1. y = f(x)", "2. r = f(alpha)", "3. Radius of curvature",
                                     "4. Square AOM1", "5. Volume of AOM1 around OX",
                                     "6. Square between line and asymptote"};
} // A bit C-style menu, it is only 2 lab now, so no matters

int main() {
    std::cout << "Enter a: ";
    double a;
    std::cin >> a;
    Line L = Line(a);
    int c;
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
                std::cout << "\nEnter x: ";
                double x;
                std::cin >> x;
                std::cout << "f(" << x << ") = " << L.f(x) << std::endl;
                break;
            case 2:
                std::cout << "\nEnter alpha: ";
                double alpha;
                std::cin >> alpha;
                std::cout << "r(" << alpha << ") = " << L.r(alpha) << std::endl;
                break;
            case 3:
                std::cout << "R = " << L.R_zp() << std::endl;
                break;
            case 4:
                std::cout << "S1 = " << L.S1() << std::endl;
                break;
            case 5:
                std::cout << "V1 = " << L.V1() << std::endl;
                break;
            case 6:
                std::cout << "S2 = " << L.S2() << std::endl;
                break;
        }
    } while (c);
    return 0;
}
