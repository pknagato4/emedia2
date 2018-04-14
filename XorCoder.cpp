//
// Created by patryk on 14.04.18.
//

#include "XorCoder.h"
#include "MathHelper.h"

int16_t XorCoder::Code(int16_t sample) {
    if (xor_val == std::nullopt) {
        xor_val = GetRandom<int16_t>();
    }
    return sample^(*xor_val);
}

int16_t XorCoder::Decode(int16_t sample) {
    return Code(sample);
}
