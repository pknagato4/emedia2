//
// Created by patryk on 14.04.18.
//

#include "MathHelper.h"
#include <iostream>
using namespace std;

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

//rsa_size_type pot_mod(rsa_size_type a, rsa_size_type w, rsa_size_type n)
//{
//    rsa_size_type pot,wyn,q;
////(a^w)%n
//    pot = a; wyn = 1;
//    for(q = w; q > 0; q /= 2)
//    {
//        if(q % 2) wyn = (wyn * pot) % n;
//        pot = (pot * pot) % n;
//    }
//    return wyn;
//}


//od janka

rsa_size_type Losuj(rsa_size_type a, rsa_size_type b)
{
    rsa_size_type w;
    int i;
    for (i = 1; i <= 4; i++)
    {
        w = w << 8;
        w |= rand() % 256;
    }
    return a + (w % (b - a));
}

rsa_size_type MnozModulo(rsa_size_type a, rsa_size_type b, rsa_size_type n)
{
    rsa_size_type m, w;
    w = 0;
    for (m = 1; m; m <<= 1)
    {
        if (b & m) w = (w + a) % n;
        a = (a << 1) % n;
    }
    return w;
}

rsa_size_type PotegujModulo(rsa_size_type a, rsa_size_type e, rsa_size_type n)
{
    rsa_size_type m, p, w;
    p = a; w = 1;
    for (m = 1; m; m <<= 1)
    {
        if (e & m) w = MnozModulo(w, p, n);
        p = MnozModulo(p, p, n);
    }
    return w;
}

rsa_size_type RSALosuj()
{
    srand(time(NULL));
    rsa_size_type w = 0;
    int i;
    for (i = 1; i <= 4; i++)
    {
        w = w << 8;
        w |= rand() % 256;
    }
    return w;
}

bool Miller(rsa_size_type n, rsa_size_type p) {
    rsa_size_type d, a, x;
    int s = 0, i, j;
    bool t = true;
    s = 0;
    for (d = p - 1; d % 2 == 0; s++) d /= 2;
    t = true;
    for (i = 1; i <= n; i++)
    {
        a = Losuj(2, p - 2);
        x = PotegujModulo(a, d, p);
        if ((x == 1) || (x == p - 1)) continue;
        for (j = 1; (j < s) && (x != p - 1); j++)
        {
            x = MnozModulo(x, x, p);
            if (x == 1)
            {
                t = false; break;
            }
        }
        if (!t) break;
        if (x != p - 1)
        {
            t = false; break;
        }
    }
    return t;
}

rsa_size_type odwr_mod(rsa_size_type a, rsa_size_type n) {
    rsa_size_type p0 = 0, p1 = 1, a0 = a, n0 = n, q, r, t;
    q = n0 / a0;
    r = n0 % a0;
    while (r>0) {
        t = p0 - q * p1;
        if (t >= 0)
            t = t % n;
        else
            t = n - ((-t) % n);
        p0 = p1; p1 = t;
        n0 = a0; a0 = r;
        q = n0 / a0;
        r = n0 % a0;
        //i++;
    }
    return p1;
}

rsa_size_type nwd(rsa_size_type a, rsa_size_type b)
{
    rsa_size_type t;

    while (b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    };
    return a;
}

rsa_size_type pot_mod(rsa_size_type a, rsa_size_type w, rsa_size_type n)
{
    rsa_size_type pot, wyn, q;

    // wykładnik w rozbieramy na sumę potęg 2
    // przy pomocy algorytmu Hornera. Dla reszt
    // niezerowych tworzymy iloczyn potęg a modulo n.

    pot = a; wyn = 1;
    for (q = w; q > 0; q /= 2)
    {
        if (q % 2) wyn = (wyn * pot) % n;
        pot = (pot * pot) % n; // kolejna potęga
    }
    return wyn;
}

void RSA_klucz(rsa_size_type &pub, rsa_size_type &priv, rsa_size_type &n1) {
    rsa_size_type p, q, e, d, j = 0;
    rsa_size_type phi, n, a, b, c, w, z, pp;
    bool t1=false, t2=false;
    int i = 0;
    while (t1 == false) {
        p = RSALosuj();
        t1 = Miller(5, p);
    }
    while (t2 == false || q == p) {
        q = RSALosuj();
        t2 = Miller(5, q);
    }

    phi = (p - 1)*(q - 1);
    n = p * q;
    for (e = 3; nwd(e, phi) != 1; e += 2);
    d = odwr_mod(e, phi);
    pp = pot_mod(11, e, n);
    pub = e; priv = d; n1 = n;
    cout << "p " << p << endl;
    cout << "q " << q << endl;
    cout << "E " << e << endl;
    cout << "D " << d << endl;
    cout << "n " << n << endl;
    cout << "phi " << phi << endl;
    cout<< "pot "<<pp<<endl;
    cout << "pot " << pot_mod(pp, d, n) << endl;
    cout<<" priv : "<<priv<<"\n"
        <<" pub: " << pub << "\n"
        <<" n1L "<< n1 << "\n";
}