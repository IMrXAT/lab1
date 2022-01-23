//
// Created by mrxat on 23.01.2022.
//

#include "Trit.h"
Trit operator~ (Trit trit) {
    if(trit == True) {
        return False;
    } else if(trit == False) {
        return True;
    } else {
        return Unknown;
    }
}

Trit operator& (Trit trit1, Trit trit2) {
    if(trit1 == False) {
        return False;
    } else if(trit1 == Unknown) {
        if(trit2 == False) {
            return False;
        } else {
            return Unknown;
        }
    } else {
        return trit2;
    }
}

Trit operator| (Trit trit1, Trit trit2) {
    if(trit1 == True) {
        return True;
    } else if(trit1 == False) {
        return trit2;
    } else {
        if(trit2 == True) {
            return True;
        } else {
            return Unknown;
        }
    }
}


const std::ostream& operator<<(std::ostream& out, const Trit &trit) {
    if(trit == True) {
        out << "True";
    } else if(trit == False) {
        out << "False";
    } else {
        out << "Unknown";
    }
    return out;
}



