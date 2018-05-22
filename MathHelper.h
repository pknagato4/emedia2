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
#include "types.h"

template <class T>
T GetRandom() {
    std::srand(std::time(nullptr));
    return static_cast<T>(std::rand());
}

rsa_size_type CalculateEulerFunc(rsa_size_type p, rsa_size_type q);
rsa_size_type CalculateModule(rsa_size_type p, rsa_size_type q);
std::vector<rsa_size_type> FindCoprimeList(rsa_size_type begin, rsa_size_type end, rsa_size_type coPrimeWith);

rsa_size_type FindCoprine(rsa_size_type eulerFunc);

rsa_size_type GetReverseModulo(rsa_size_type coprime, rsa_size_type eulerFunc);
rsa_size_type pot_mod(rsa_size_type a, rsa_size_type w, rsa_size_type n);
#endif //EMEDIA_MATHHELPER_H
