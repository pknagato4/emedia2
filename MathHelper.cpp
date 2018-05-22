//
// Created by patryk on 14.04.18.
//

#include "MathHelper.h"


rsa_size_type CalculateEulerFunc(rsa_size_type p, rsa_size_type q) {
    return ((p-1)*(q-1));
}

rsa_size_type CalculateModule(rsa_size_type p, rsa_size_type q) {
    return p*q;
}

std::vector<rsa_size_type> FindCoprimeList(rsa_size_type begin, rsa_size_type end, rsa_size_type coPrimeWith) {
    std::vector<rsa_size_type > coPrimes;
    rsa_size_type ax, bx, t;
    for(auto i = begin; i <= end; i++)
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

rsa_size_type FindCoprine(rsa_size_type eulerFunc) {
    rsa_size_type tmp = 1;
    return FindCoprimeList(tmp, eulerFunc,eulerFunc).back();
}


rsa_size_type GetReverseModulo(rsa_size_type coprime, rsa_size_type eulerFunc) {
    rsa_size_type u,w,x,z,q, nulll;
    nulll = 0;
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
    return nulll;
}

rsa_size_type pot_mod(rsa_size_type a, rsa_size_type w, rsa_size_type n)
{
    rsa_size_type pot,wyn,q;
//(a^w)%n
    pot = a; wyn = 1;
    for(q = w; q > 0; q /= 2)
    {
        if(q % 2) wyn = (wyn * pot) % n;
        pot = (pot * pot) % n;
    }
    return wyn;
}
