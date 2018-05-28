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

//od janka
rsa_size_type Losuj(rsa_size_type a, rsa_size_type b);
rsa_size_type MnozModulo(rsa_size_type a, rsa_size_type b, rsa_size_type n);
rsa_size_type PotegujModulo(rsa_size_type a, rsa_size_type e, rsa_size_type n);
rsa_size_type RSALosuj();
rsa_size_type odwr_mod(rsa_size_type a, rsa_size_type n);
rsa_size_type nwd(rsa_size_type a, rsa_size_type b);
bool Miller(rsa_size_type n, rsa_size_type p);
rsa_size_type pot_mod(rsa_size_type a, rsa_size_type w, rsa_size_type n);
void RSA_klucz(rsa_size_type &pub, rsa_size_type &priv, rsa_size_type &n1);
#endif //EMEDIA_MATHHELPER_H
