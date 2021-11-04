#ifndef LAB2_4_CLOCK_H
#define LAB2_4_CLOCK_H

#include "pcb.h"

using namespace Lab3C;

struct Player {
    int x = 1;
    int y = 1;
};

class Maze {
private:
    int num = 0;
    static const int max_x = 26;
    static const int max_y = 18;
    char matrix[max_x][max_y];
    Player player;
    printedCircuitBoard board;
public:
    explicit Maze(std::istream& input);
    void printMaze(std::ostream& output) const;
    int findContact(int x, int y);
    void jumpPlayer();
    int movePlayer(char direction);
    const printedCircuitBoard& getPCB() const;
};

#endif //LAB2_4_CLOCK_H
