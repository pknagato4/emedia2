//
// Created by patryk on 14.04.18.
//

#include "Coder.h"
#include "MathHelper.h"

samples_container Coder::Code(CodeType code_type, samples_container channels) {
    samples_container coded;
    for(auto sample : channels.first) {
        coded.first.emplace_back(CodeSample(code_type, sample));
    }
    for(auto sample : channels.second) {
        coded.second.emplace_back(CodeSample(code_type, sample));
    }

    return coded;
}

int16_t Coder::CodeSample(CodeType code_type, int16_t sample) {
    switch(code_type) {
        case CodeType::XOR:
            return CodeXOR(sample);
        case CodeType::RSA:
            return 0;//CodeRSA(sample);
        case CodeType::DES:
            return 0;
        case CodeType::DES_RSA:
            return 0;
    }
}

int16_t Coder::CodeXOR(int16_t sample) {
    if (xor_val == std::nullopt) {
        xor_val = GetRandom<int16_t>();
    }
    return sample^(*xor_val);
}
