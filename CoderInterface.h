//
// Created by patryk on 14.04.18.
//

#ifndef EMEDIA_CODERINTERFACE_H
#define EMEDIA_CODERINTERFACE_H

#include <cstdint>

class CoderInterface {
public:
    virtual int16_t Code(int16_t sample) = 0;
    virtual int16_t Decode(int16_t sample) = 0;
    virtual ~CoderInterface() = default;
};

#endif //EMEDIA_CODERINTERFACE_H
