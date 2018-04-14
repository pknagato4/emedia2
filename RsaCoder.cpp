//
// Created by patryk on 14.04.18.
//

#include "RsaCoder.h"

int16_t RsaCoder::Code(int16_t) {

}

int16_t RsaCoder::CalculateEulerFunc(int16_t p, int16_t q) {
    return (p-1)*(q-1);
}

int16_t RsaCoder::CalculateModule(int16_t p, int16_t q) {
    return p*q;
}
