//
// Created by patryk on 22.05.18.
//

#ifndef EMEDIA_RSAKEYGENERATOR_H
#define EMEDIA_RSAKEYGENERATOR_H


#include <utility>
#include "types.h"

struct RsaKey
{
    rsa_key public_key;
    rsa_key private_key;
};

class RsaKeyGenerator {
public:
    static RsaKey Generate(rsa_size_type first_prime, rsa_size_type second_prime);
};


#endif //EMEDIA_RSAKEYGENERATOR_H
