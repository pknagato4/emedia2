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

using samples_container = std::pair<std::vector<int16_t>, std::vector<int16_t>>;

enum class CodeType {
    XOR,
    RSA,
    DES,
    DES_RSA
};


class Encrypter {
public:
    samples_container Code(CodeType code_type, samples_container channels);
private:
    int16_t CodeSample(CodeType code_type, int16_t sample);
    std::unique_ptr<CoderInterface> xorCoder;
    std::unique_ptr<CoderInterface> rsaCoder;

};


#endif //EMEDIA_CODER_H
