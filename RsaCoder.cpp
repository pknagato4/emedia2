#include "RsaCoder.h"
#include "MathHelper.h"
#include "types.h"
#include <iostream>
#include <boost/numeric/conversion/cast.hpp>
using boost::numeric_cast;

int16_t RsaCoder::Code(int16_t sample) {
    rsa_size_type Sample = sample;
    return numeric_cast<int16_t>(pot_mod(Sample, w, modulo));
}

void RsaCoder::setKey(rsa_size_type w, rsa_size_type modulo) {
    RsaCoder::w = w;
    RsaCoder::modulo = modulo;
}

int16_t RsaCoder::Decode(int16_t sample) {
    return Code(sample);
}
