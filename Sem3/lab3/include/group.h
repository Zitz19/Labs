#ifndef LAB3_GROUP_H
#define LAB3_GROUP_H

#include <string>
#include <iostream>

class Group {
private:
    const int INDEX; // Индекс группы
    int m_num = 0; // Кол-во студентов
    int m_kaf; // Номер кафедры
    int m_term; // Срок обучения
    std::string m_specialization; // Специализация
public:
    Group(int index, int kaf, int term, std::string specialization, int num)
    : INDEX(index), m_num(num), m_kaf(kaf), m_term(term), m_specialization(specialization) {}
    virtual ~Group() = default;

    int getIndex() { return INDEX; }
    int getNum() { return m_num; }
    int getKaf() { return m_kaf; }
    int getTerm() { return m_term; }
    std::string getSpecialization() { return m_specialization; }

    void setNum(int num) { m_num = num; }

    virtual std::ostream& printInfo(std::ostream& out) = 0;
};

class Budget: public Group {
public:
    Budget(int index, int kaf, int term, std::string specialization, int num)
    : Group(index, kaf, term, specialization, num) {}
    virtual ~Budget() = default;

    virtual std::ostream& printInfo(std::ostream& out) = 0;
};

class Daytime: public Budget {
private:
    int m_money = 0; // Величина стипендии
    int m_numMoney = 0; // Кол-во стипендиатов
public:
    Daytime(int index, int kaf, int term, std::string specialization, int num,
            int money, int numMoney)
    : Budget(index, kaf, term, specialization, num), m_money(money), m_numMoney(numMoney) {}
    virtual ~Daytime() = default;

    int getScholarship() { return m_money; }

    void setScholarship(int money) { m_money = money; }

    virtual std::ostream& printInfo(std::ostream& out);
};

class Evening: public Budget {
private:
    int m_age; // 'Контингент' обучающихся
    std::string m_qualification; // Квалификация
public:
    Evening(int index, int kaf, int term, std::string specialization, int num,
            int age, std::string qualification)
    : Budget(index, kaf, term, specialization, num), m_age(age), m_qualification(qualification) {}
    virtual ~Evening() = default;

    virtual std::ostream& printInfo(std::ostream& out);
};

class Commercial: public Group {
private:
    int m_contract = 0; // Номер контракта
    int m_price = 0; // Размер платы за семестр
public:
    Commercial(int index, int kaf, int term, std::string specialization, int num,
               int contract, int price)
    : Group(index, kaf, term, specialization, num), m_contract(contract), m_price(price) {}
    virtual ~Commercial() = default;

    int getPrice() { return m_price; }

    void setPrice(int price) { m_price = price; }

    virtual std::ostream& printInfo(std::ostream& out);
};

#endif //LAB3_GROUP_H
