//
// Created by patryk on 14.04.18.
//

#include "Encrypter.h"
#include "MathHelper.h"
#include "RsaCoder.h"

samples_container Encrypter::CodeXor(samples_container channels) {
    samples_container coded;
    for(auto sample : channels.first) {
        coded.first.emplace_back(CodeSampleXor(sample));
    }
    for(auto sample : channels.second) {
        coded.second.emplace_back(CodeSampleXor(sample));
    }
    return coded;
}

int16_t Encrypter::CodeSampleXor(int16_t sample) {
        if (xorCoder == nullptr)
            xorCoder = std::make_unique<XorCoder>();
        return xorCoder->Code(sample);
}

samples_container Encrypter::CodeRsa(samples_container channels, rsa_key rsaKey) {
    samples_container coded;
    if (rsaCoder == nullptr)
        rsaCoder = std::make_unique<RsaCoder>();
    rsaCoder->setKey(rsaKey.first, rsaKey.second);
    for(auto sample : channels.first) {
        coded.first.emplace_back(CodeSampleRsa(sample));
    }
    for(auto sample : channels.second) {
        coded.second.emplace_back(CodeSampleRsa(sample));
    }
    return coded;
}

int16_t Encrypter::CodeSampleRsa(int16_t sample) {
    return rsaCoder->Code(sample);
}