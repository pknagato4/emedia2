//
// Created by patryk on 14.04.18.
//

#ifndef EMEDIA_RSACODER_H
#define EMEDIA_RSACODER_H

#include <utility>
#include "CoderInterface.h"

class RsaCoder : public CoderInterface {
public:
    int16_t Code(int16_t) override;
    int16_t Decode(int16_t) override{};
private:
    std::pair<int16_t, int16_t> prime_ = std::make_pair(static_cast<int16_t>(13), static_cast<int16_t>(11));//to remove when GetPrime will be implemented

};

#endif //EMEDIA_RSACODER_H
