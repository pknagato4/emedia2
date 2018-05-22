//
// Created by patryk on 14.04.18.
//

#ifndef EMEDIA_CODER_H
#define EMEDIA_CODER_H

#include <cstdint>
#include <vector>
#include <memory>

#include "CoderInterface.h"
#include "XorCoder.h"
#include "RsaCoder.h"
#include "types.h"

using samples_container = std::pair<std::vector<int16_t>, std::vector<int16_t>>;

class Encrypter {
public:
    samples_container CodeXor(samples_container channels);
    samples_container CodeRsa(samples_container channels, rsa_key rsaKey);
private:
    int16_t CodeSampleXor(int16_t sample);
    int16_t CodeSampleRsa(int16_t sample);

    std::unique_ptr<XorCoder> xorCoder;
    std::unique_ptr<RsaCoder> rsaCoder;
};


#endif //EMEDIA_CODER_H
