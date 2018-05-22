//
// Created by patryk on 22.05.18.
//

#include "RsaKeyGenerator.h"
#include "types.h"
#include "MathHelper.h"

RsaKey RsaKeyGenerator::Generate(rsa_size_type first_prime, rsa_size_type second_prime){
    auto euler = CalculateEulerFunc(first_prime, second_prime);
    auto module = CalculateModule(first_prime, second_prime);
    auto lista = FindCoprimeList(1, euler, euler);
    auto e = lista[1];
    auto d = GetReverseModulo(e, euler);
    RsaKey rk;
    rk.public_key = std::make_pair(e, module);
    rk.private_key = std::make_pair(d, module);
    return rk;
}
