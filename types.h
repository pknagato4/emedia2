//
// Created by patryk on 22.05.18.
//

#ifndef EMEDIA_TYPES_H
#define EMEDIA_TYPES_H

#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

using rsa_size_type = mp::int512_t;
using sample_size = int16_t;
using rsa_key = std::pair<rsa_size_type , rsa_size_type >;

#endif //EMEDIA_TYPES_H
