#include "include/table.h"

bool Table::addGroup(std::string type, int num, int kaf, int term, std::string specialization,
              std::string addInfo) {
    std::stringstream info;
    info << addInfo;
    if (type == "Daytime") {
        int money, numMoney;
        info >> money >> numMoney;
        Daytime* ch = new Daytime(totalIndex, kaf, term, specialization, num,
                                     money, numMoney);
        m_map.emplaceMap(this->totalIndex, *ch);
    } else if (type == "Evening") {
        int age;
        std::string qualification;
        info >> age >> qualification;
        Evening* ch = new Evening(totalIndex, kaf, term, specialization, num,
                                 age, qualification);
        m_map.emplaceMap(this->totalIndex, *ch);
    } else if (type == "Commercial") {
        int contract, price;
        info >> contract >> price;
        Commercial* ch = new Commercial(totalIndex, kaf, term, specialization, num,
                                 contract, price);
        m_map.emplaceMap(this->totalIndex, *ch);
    } else { return false; }
    totalIndex++;
    return true;
}

bool Table::removeGroup(int index) {
    auto tmp = m_map.findMap(index);
    if (tmp == m_map.end()) return false;
    delete &((*tmp).second);
    m_map.eraseMap(tmp);
    return true;
}

void Table::printTable() {
    for (auto it = m_map.begin(); it != m_map.end(); it++) {
        std::cout << "INDEX: " << (*it).first << std::endl;
        (*it).second.printInfo(std::cout);
    }
}