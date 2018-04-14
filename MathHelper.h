//
// Created by patryk on 14.04.18.
//

#ifndef EMEDIA_MATHHELPER_H
#define EMEDIA_MATHHELPER_H

#pragma once

#include <cstdint>
#include <ctime>
#include <cstdlib>
#include <vector>

template <class T>
T GetRandom() {
    std::srand(std::time(nullptr));
    return static_cast<T>(std::rand());
}

int16_t CalculateEulerFunc(int16_t p, int16_t q);
int16_t CalculateModule(int16_t p, int16_t q);
std::vector<int16_t> FindCoprimeList(int16_t begin, int16_t end, int16_t coPrimeWith);

int16_t FindCoprine(int16_t eulerFunc);

int16_t GetReverseModulo(int16_t coprime, int16_t eulerFunc);
#endif //EMEDIA_MATHHELPER_H
