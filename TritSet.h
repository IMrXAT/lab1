#include "Trit.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned int uint;

class TritSet {
private:
    std::vector <uint> array;
    size_t initialSize, countTrits, countTrue, countFalse;

    void valueInMas(int index, Trit value); /// запись трита в массив

    class TritProxy {
        friend class TritSet;
    private:
        TritSet &mas;
        int index;
    public:
        TritProxy(TritSet *Mas, int _index); /// конструктор

        TritProxy &operator=(Trit val);

        bool operator==(const TritProxy &tritProxy) const;

        bool operator==(const Trit &trit) const;

        explicit operator Trit();
    };


public:
    explicit TritSet(int size); /// конструктор, если нам подали размер массива
    TritSet(const TritSet& a); /// конструктор копирования
    TritSet(); /// конструктор, если нам не подают размер массива
    ~TritSet();

    size_t Size() const; /// возвращает количество тритов
    size_t ArraySize() const; /// размер вектора
    uint ValueCell(int index) const; /// значение ячейки
    size_t Capacity() const; /// ёмкость вектора
    Trit Value(int index) const; /// достаём значение трита по индексу ячейки в векторе
    void Shrink(); /// подчищение векторара от пустых ячеек и "пустых" значений тритов
    size_t length() const; /// индекс последнего не Unknown трита + 1

    TritProxy operator[] (int index);
    TritSet &operator=(const TritSet &set);

    friend std::ostream& operator<<(std::ostream& out, TritSet &set);
};

TritSet operator~ (const TritSet &set);

TritSet operator& (const TritSet &set1, const TritSet &set2);

TritSet operator| (const TritSet &set1, const TritSet &set2);


