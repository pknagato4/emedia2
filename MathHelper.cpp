//
// Created by patryk on 14.04.18.
//

#include "MathHelper.h"


int16_t CalculateEulerFunc(int16_t p, int16_t q) {
    return static_cast<int16_t>((p-1)*(q-1));
}

int16_t CalculateModule(int16_t p, int16_t q) {
    return p*q;
}

std::vector<int16_t> FindCoprimeList(int16_t begin, int16_t end, int16_t coPrimeWith) {
    std::vector<int16_t> coPrimes;
    int ax, bx, t;
    for(int i = begin; i <= end; i++)
    {
        ax = i; bx = coPrimeWith;
        while(bx)
        {
            t  = bx;
            bx = ax % bx;
            ax = t;
        }
        if(ax == 1) coPrimes.emplace_back(i);
    }
    return coPrimes;
}

int16_t FindCoprine(int16_t eulerFunc) {
    return FindCoprimeList(1, eulerFunc,eulerFunc).back();
}


int16_t GetReverseModulo(int16_t coprime, int16_t eulerFunc) {
    int16_t u,w,x,z,q;
    u = 1; w = coprime;
    x = 0; z = eulerFunc;
    while(w)
    {
        if(w < z)
        {
            q = u; u = x; x = q;
            q = w; w = z; z = q;
        }
        q = w / z;
        u -= q * x;
        w -= q * z;
    }
    if(z == 1)
    {
        if(x < 0) x += eulerFunc;
        return x;
    }
    return 0;
}