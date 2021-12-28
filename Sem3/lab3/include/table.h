#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H

#include <iostream>
//#include <map>
#include <sstream>

#include "group.h"
#include "mymap.h"

class Table {
private:
    Map<int, Group&> m_map;
    int totalIndex = 0;
public:
    Table() = default;
    Table(const Table &copy) = default;
    ~Table() {
        for (auto it = m_map.begin(); it != m_map.end(); it++)
            delete &((*it).second);
    }

    bool addGroup(std::string type, int num, int kaf, int term, std::string specialization,
                  std::string addInfo);
    bool removeGroup(int index);
    void printTable();
};

#endif //LAB3_TABLE_H
