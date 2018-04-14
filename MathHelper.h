//
// Created by patryk on 14.04.18.
//

#ifndef EMEDIA_MATHHELPER_H
#define EMEDIA_MATHHELPER_H

#include <cstdint>
#include <ctime>
#include <cstdlib>

template <class T>
T GetRandom() {
    std::srand(std::time(nullptr));
    return static_cast<T>(std::rand());
}

#endif //EMEDIA_MATHHELPER_H
