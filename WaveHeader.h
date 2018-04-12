//
// Created by patryk on 12.04.18.
//

#ifndef EMEDIA_WAVEHEADER_H
#define EMEDIA_WAVEHEADER_H


#include <fstream>

class WaveHeader {

public:
    std::string chunk_id_ {};
    uint32_t chunk_size_ {};
    std::string format_ {};
    std::string sub_chank1_id_ {};
    uint32_t chunk1_size_ {};
    uint16_t format_code_ {};
    uint16_t number_of_channels_ {};
    uint32_t samples_per_second_ {};
    uint32_t bytes_per_second_ {};
    uint16_t bytes_per_sample_frame_ {};
    uint16_t bits_per_sample_ {};
    std::string sub_chank2_id_ {};
    uint32_t sub_chank2_size_ {};
    uint32_t number_of_samples_ {};
};


#endif //EMEDIA_WAVEHEADER_H
