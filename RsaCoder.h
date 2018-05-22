//
// Created by patryk on 14.04.18.
//

#ifndef EMEDIA_RSACODER_H
#define EMEDIA_RSACODER_H

#include "CoderInterface.h"
#include "RsaKeyGenerator.h"

class RsaCoder : public CoderInterface {
public:
    void setKey(rsa_size_type w, rsa_size_type modulo);
    int16_t Code(int16_t) override;
    int16_t Decode(int16_t) override;

private:
    rsa_size_type w;
    rsa_size_type modulo;
};

#endif //EMEDIA_RSACODER_H
