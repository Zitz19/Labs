#include <iostream>
#include "include/pcb.h"
#include "include/maze.h"

Maze::Maze(std::istream& input) {
    input >> num;
    struct Contact_Input {
        contactType type;
        int first;
        int second;
    };
    Contact_Input tmp[num];
    char t;
    for (int i = 0; i < num; i++) {
        input >> tmp[i].first;
        input >> t;
        if (t == 'i')
            tmp[i].type = Lab3C::in;
        else
            tmp[i].type = Lab3C::out;
        input >> tmp[i].second;
    }
    input.get();
    int k = 0;
    for (int j = 0; j < max_y; j++) {
        for (int i = 0; i < max_x; i++) {
            matrix[i][j] = input.get();
            if (matrix[i][j] == 'o') {
                printedCircuitBoard::Contact hole = printedCircuitBoard::Contact(tmp[k].type, i, j);
                board += hole;
                if (tmp[k].type == out)
                    board.establishConnect(tmp[k].first - 1, tmp[k].second - 1);
                k++;
            }
        }
        input.get();
    }
}

void Maze::printMaze(std::ostream& output) const {
    for (int j = 0; j < max_y; j++) {
        for (int i = 0; i < max_x; i++) {
            if (i == player.x && j == player.y) output << '@';
            else output << matrix[i][j];
        }
        output << '\n';
    }
}

int Maze::findContact(int x, int y) {
    for (int i = 0; i < num; i++)
        if (board[i].x == x && board[i].y == y)
            return i;
    return -1;
}

void Maze::jumpPlayer() {
    int contact = findContact(player.x, player.y);
    player.x = board[board[contact].numberOfContact].x;
    player.y = board[board[contact].numberOfContact].y;
}

int Maze::movePlayer(char direction) {
    if (direction != 'w' && direction != 'a' && direction != 's' && direction != 'd' && direction != 'e')
        throw std::invalid_argument("___Invalid input___");
    switch (direction) {
        case 'a':
            if (matrix[player.x - 1][player.y] != '|')
                player.x--;
            break;
        case 'd':
            if (matrix[player.x + 1][player.y] != '|')
                player.x++;
            break;
        case 'w':
            if (matrix[player.x][player.y - 1] != '|')
                player.y--;
            break;
        case 's':
            if (matrix[player.x][player.y + 1] != '|')
                player.y++;
            break;
        case 'e':
            if (matrix[player.x][player.y] == 'o')
                jumpPlayer();
            else if (matrix[player.x][player.y] == 'x')
                return 1;
            break;
    }
    return 0;
}

const printedCircuitBoard& Maze::getPCB() const {
    return board;
}