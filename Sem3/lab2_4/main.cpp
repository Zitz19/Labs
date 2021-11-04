#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "include/maze.h"

int main() {
    std::fstream fs;
    fs.open("maze.txt", std::fstream::in);
    Maze maze(fs);
    fs.close();
    char c;
    do {
        system("clear");
        maze.printMaze(std::cout);
        std::cout << '\n' << "Choose a direction: ";
        std::cin >> c;
        if (c == 'q') break;
        try {
            if (maze.movePlayer(c)) {
                std::cout << "( ͡° ͜ʖ ͡°) EPIC WIN!!! ༼ つ ◕_◕ ༽つ\n";
                break;
            }
        }
        catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        }
    } while (c != 'q');
    //std::cout << maze.getPCB();
    return 0;
}