//
// Created by patryk on 14.04.18.
//

#include "RsaCoder.h"
#include "MathHelper.h"
#include <iostream>


int16_t RsaCoder::Code(int16_t) {
    auto euler = CalculateEulerFunc(prime_.first, prime_.second);
    auto module = CalculateModule(prime_.first, prime_.second);
    auto lista = FindCoprimeList(1, euler, euler);
    auto e = lista[1];
    auto d = GetReverseModulo(e, euler);
    std::cout << "Public key: "<<e<<" "<<module<<"\n"
              << "Private key: "<<d<<" "<<module;
}

