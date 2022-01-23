#include "TritSet.h"

#define TRUE 3
#define FALSE 2
#define UNKNOWN 0

TritSet::TritProxy::TritProxy(TritSet *Mas, int _index) : mas(*Mas), index(_index) {}

TritSet::TritProxy &TritSet::TritProxy::operator=(Trit val) {
    if(mas.array.size() < ceil((double)(index + 1) / (4 * sizeof(uint))) && val != Unknown) {
        mas.array.resize(ceil((double)(index + 1) / (4 * sizeof(uint))), 0);
        mas.countTrits = index + 1;
    } else if(index >= mas.countTrits && val != Unknown) {
        mas.countTrits = index + 1;
    }
    mas.valueInMas(index, val);
    return *this;
}

bool TritSet::TritProxy::operator==(const TritProxy &tritProxy) const {
    if (index < mas.countTrits && tritProxy.index < tritProxy.mas.countTrits) {
        return (mas.Value(index) == tritProxy.mas.Value(tritProxy.index));
    }
    else if (index >= mas.countTrits && tritProxy.mas.Value(tritProxy.index) == Unknown ||
    tritProxy.index >=tritProxy.mas.countTrits && mas.Value(index) == Unknown) {
        return true;
    }
    return false;
}

/// при обращении к неустановленным тритам чтение должно возвращать значение Unknown:
bool TritSet::TritProxy::operator==(const Trit &trit) const {
    if (index > mas.countTrits) {
        return trit == Unknown;
    }
    return (mas.Value(index) == trit);
}

TritSet::TritProxy::operator Trit() {
    return this->mas.Value(this->index);
}

void TritSet::valueInMas(int index, Trit value) { ///запись трита в массив
    if(Value(index) == True) {
        countTrue--;
    } else if(Value(index) == False) {
        countFalse--;
    }

    if(value == True) {
        countTrue++;
    } else if(value == False) {
        countFalse++;
    }
    int point1 = index / (4 * sizeof(uint));
    int point2 = index % (4 * sizeof(uint));
    uint a = 3;
    uint b;
    if(value == False) {
        b = FALSE;
    } else if(value == True) {
        b = TRUE;
    } else {
        b = UNKNOWN;
    }
    a <<= 2 * point2;
    b <<= 2 * point2;
    a = ~a;
    array[point1] &= a;
    array[point1] |= b;
}

TritSet::TritSet(int size) {
    array.assign(ceil((double) size / (4 * sizeof(uint))), 0);
    initialSize = array.size(); /// текущий размер = размер массива, который нам подали на входе
    countTrits = size;
    countTrue = 0;
    countFalse = 0;
}

TritSet::TritSet(const TritSet& other){
    this->initialSize = other.initialSize;
    this->countTrits = other.countTrits;
    this->countTrue = other.countTrue;
    this->countFalse = other.countFalse;
};

TritSet::TritSet() {
    initialSize = 0;
    countTrits = 0;
    countTrue = 0;
    countFalse = 0;
}

TritSet::~TritSet() { /// очистка вектора
    array.clear();
}

size_t TritSet::Size() const {
    return countTrits;
}

size_t TritSet::ArraySize() const {
    return array.size();
}

uint TritSet::ValueCell(int index) const {
    if (index >= array.size()) {
        return 0;
    }
    return array[index];
}

size_t TritSet::Capacity() const {
    return array.capacity();
}

Trit TritSet::Value(int index) const {
    if(index > countTrits) {
        return Unknown;
    }
    int point1 = index / (4 * sizeof(uint));  ///ячейке массива, в которой находится трит
    int point2 = index % (4 * sizeof(uint)); ///на каком месте в этой ячейке находится трит
    uint a = array[point1];
    a >>= 2 * point2;
    a &= 3;
    if(a == FALSE) {
        return False;
    } else if(a == TRUE) {
        return True;
    } else {
        return Unknown;
    }
}

void TritSet::Shrink() {
    int significant_size = initialSize;
    for (int k = array.size() - 1; k > initialSize; --k) {
        if (array[k] > 0) {
            significant_size = k + 1;
            break;
        }
    }
    array.resize(significant_size);
    int point1 = 4 * sizeof(uint) * (significant_size - 1);
    int point2 = 4 * sizeof(uint) * significant_size;
    for (int i = point1; i < point2; ++i) {
        if (Value(i) != Unknown) {
            countTrits = i + 1;
        }
    }
    array.shrink_to_fit(); /// уменьшает емкость контейнера до его размера и уничтожает все элементы за пределами емкости.
}


size_t TritSet::length() const {
    int lastIndex = -1;
    for (int i = array.size() - 1; i >= 0; --i) {
        if (array[i] != 0) {
            lastIndex = i;
            break;
        }
    }
    if (lastIndex == -1) {
        return 0;
    }
    int point1 = 4 * sizeof(uint) * lastIndex;
    int point2 = 4 * sizeof(uint) * (lastIndex + 1);
    for (int i = point2 + 1; i >= point1; --i) {
        if (Value(i) != Unknown) {
            return i + 1;
        }
    }
    return 0;
}

TritSet::TritProxy TritSet::operator[] (int index) {
    return TritProxy(this, index);
}

TritSet& TritSet::operator=(const TritSet &set) {
    array = set.array;
    countTrits = set.countTrits;
    countTrue = set.countTrue;
    countFalse = set.countFalse;
    return *this;
}

TritSet operator~ (const TritSet &set) {
    TritSet result(set.Size());
    for (int i = 0; i < set.ArraySize(); ++i) {
        if (set.ValueCell(i) == 0) continue;
        int point1 = i * 4 * sizeof(uint);
        int point2 = (i + 1) * 4 * sizeof(uint);
        for (int j = point1; j < point2; ++j) {
            result[j] = ~set.Value(j);
        }
    }
    return result;
}

TritSet operator& (const TritSet &set1, const TritSet &set2) {
    TritSet result(std::max(set1.Size(), set2.Size()));
    for (int i = 0; i < std::max (set1.ArraySize(), set2.ArraySize()); ++i) {
        if (set1.ValueCell(i) == 0 && set2.ValueCell(i) == 0) {
            continue;
        }
        int point1 = i * 4 * sizeof(uint);
        int point2 = (i + 1) * 4 * sizeof(uint);
        for (int j = point1; j < point2; ++j) {
            result[j] = set1.Value(j) & set2.Value(j);
        }
    }
    return result;
}

TritSet operator| (const TritSet &set1, const TritSet &set2) {
    TritSet result(std::max(set1.Size(), set2.Size()));
    for (int i = 0; i < std::max (set1.ArraySize(), set2.ArraySize()); ++i) {
        if (set1.ValueCell(i) == 0 && set2.ValueCell(i) == 0) {
            continue;
        }
        int point1 = i * 4 * sizeof(uint);
        int point2 = (i + 1) * 4 * sizeof(uint);
        for (int j = point1; j < point2; ++j) {
            result[j] = set1.Value(j) | set2.Value(j);
        }
    }
    return result;
}

ostream& operator <<(std::ostream& stream, TritSet& set){
    for(int i = 0; i < set.length(); ++i){
        stream << Trit(set[i]);
        std::cout << ' ';
    }
    return stream;
}
