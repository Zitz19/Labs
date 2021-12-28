#ifndef LAB3_MYMAP_H
#define LAB3_MYMAP_H

#include <vector>
#include <algorithm>

/**
 * @brief Итератор для контейнерного класса
 * @tparam Tk Первый параметр в паре. Является ключем
 * @tparam Tv Второй параметр в паре. Информация, хранящаяся под соответсвующим ключем
 * @param CelPtr Указатель на ячейку контейнерного класса
 *
 * Реализованы основные операторы: ==, !=, *, ++
 */

template <class Tk, class Tv>
class Iterator {
private:
    std::pair<Tk, Tv>* CellPtr;
public:
    /**
     * Стандартный конструктор от указателя
     * @param ptr Указатель на ячейку контейнерного класса
     *
     */
    Iterator(std::pair<Tk, Tv>* ptr): CellPtr(ptr) {}
    /**
     * Стандартный конструктор копирования
     * @param copy Объект класса, от которого создается копия
     */
    Iterator(const Iterator<Tk, Tv>& copy) = default;
    /**
     * Стандартный деструктор
     */
    ~Iterator() = default;

    /**
     * Перегруженный оператор "равно"
     * @param tmp Объект, с которым идет сравнение
     * @return Правда, если итераторы указывают на одинаковые ячейки, иначе ложь
     */
    bool operator==(const Iterator<Tk, Tv>& tmp) { return CellPtr == tmp.CellPtr; }
    /**
     * Перегруженный оператор "не равно"
     * @param tmp Объект, с которым идет сравнение
     * @return Правда, если итераторы указывают на разные ячейки, иначе ложь
     */
    bool operator!=(const Iterator<Tk, Tv>& tmp) { return CellPtr != tmp.CellPtr; }
    /**
     * Перегруженный оператор разыменования
     * @return Ссылку на константную ячейку, на которую указывает итератор
     */
    const std::pair<Tk, Tv>& operator*() const { return *CellPtr; }
    std::pair<const Tk, Tv>& operator*() { return reinterpret_cast<std::pair<const Tk, Tv>&>(*CellPtr); }
    /**
     * Перегруженный префиксный инкремент
     * @return Ссылку на итератор на следующую ячейку
     */
    Iterator<Tk, Tv>& operator++() {
        CellPtr++;
        return *this;
    }
    /**
     * Перегруженный постфиксный инкремент
     * @return Копию итератора до изменения
     */
    Iterator<Tk, Tv> operator++(int) {
        Iterator<Tk, Tv> copy(*this);
        ++(*this);
        return copy;
    }
};

/**
 * @brief Контейнерный класс
 * @tparam Tk Первый параметр в паре. Является ключем
 * @tparam Tv Второй параметр в паре. Информация, хранящаяся под соответсвующим ключем
 * @param vect Вектор пар ключ-значение.
 *
 * Контейнер по типу std::map, хранящий пары ключ-значение в неотсортированном по ключу порядке.
 */

template <class Tk, class Tv>
class Map {
private:
    std::vector<std::pair<Tk, Tv>> vect;
public:
    /**
     * Стандартный конструктор
     */
    Map() = default;
    /**
     * Стандартный конструктор копирования
     * @param copy Объект, от которого создается копия
     */
    Map(const Map<Tk, Tv>& copy) = default;
    /**
     * Стандартный деструктор
     */
    ~Map() = default;

    /**
     * Метод, возвращающий итератор на начало
     * @return Итератор, указывающий на начало контейнера
     */
    Iterator<Tk, Tv> begin() { return Iterator<Tk, Tv>(&*vect.begin()); }
    /**
     * Метод, возвращающий итератор на конец
     * @return Итератор, указывающий на пустую ячейку в конце контейнера
     */
    Iterator<Tk, Tv> end() { return Iterator<Tk, Tv>(&*vect.end()); }

    /**
     * Метод, реализующий вставку в контейнер
     * @param key Значение ключа
     * @param value Информация, соответствующая ключу
     */
    void emplaceMap(Tk key, Tv value) { vect.push_back(std::pair<Tk, Tv>(key, value)); }

    /**
     * Метод, реализующий поиск по контейнеру
     * @param key Ключ, по которому ищем значение
     * @return Итератор, указывающий на первую найденную ячейку в случае успеха
     * и указывающий на конец контейнера в случае провала
     */
    Iterator<Tk, Tv> findMap(const Tk key) {
        Iterator<Tk, Tv> res = Iterator<Tk, Tv>(&*vect.end());
        for (auto it = vect.begin(); it != vect.end(); it++)
            if (it->first == key) res = &(*it);
        return res;
    }

    /**
     * Метод, реализующий удаление из контейнера
     * @param x Итератор, указывающий на удаляемую ячейку
     */
    void eraseMap(const Iterator<Tk, Tv> x) {
        std::vector<std::pair<Tk, Tv>> buf;
        for (int i = 0; i < vect.size(); i++) {
            if (vect[i].first != (*x).first) buf.push_back(vect[i]);
            else continue;
        }
        vect.swap(buf);
    }
};

#endif //LAB3_MYMAP_H
