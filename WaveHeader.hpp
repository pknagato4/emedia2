#pragma once

#include <fstream>
#include <cstdint>

struct WaveHeader {
    std::string chunck_id_;
    uint32_t chunck_size_;
    std::string format_;
    std::string sub_chank1_id_;
    uint32_t chunck1_size_;
    uint16_t format_code_;
    uint16_t number_of_channels_;
    uint32_t samples_per_second_;
    uint32_t bytes_per_second_;
    uint16_t bytes_per_sample_frame_;
    uint16_t bits_per_sample_;
};


class WaveHeaderReader {
public:
    WaveHeaderReader(std::string file_name)
            : file_(file_name, std::ios::binary|std::ios::in) {}
    void Read();
    void PrintInfo();
    void ReadXBitToString(std::string& str, const size_t X);

private:
    WaveHeader header_;
    std::fstream file_;
};