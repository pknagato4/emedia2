//
// Created by patryk on 14.04.18.
//

#ifndef EMEDIA_XORCODER_H
#define EMEDIA_XORCODER_H

#include <optional>
#include "CoderInterface.h"

class XorCoder : public CoderInterface {
public:
    int16_t Code(int16_t sample) override ;
    int16_t Decode(int16_t sample) override;
private:
    std::optional<int16_t> xor_val;
};

#endif //EMEDIA_XORCODER_H
