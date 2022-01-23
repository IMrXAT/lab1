//
// Created by mrxat on 23.01.2022.
//

#ifndef LAB1_TRIT_H
#define LAB1_TRIT_H
#include <iostream>



enum Trit{False, Unknown, True};

const std::ostream& operator<<(std::ostream& out, const Trit &trit);
Trit operator~ (Trit trit);
Trit operator& (Trit trit1, Trit trit2);
Trit operator| (Trit trit1, Trit trit2);

#endif //LAB1_TRIT_H
