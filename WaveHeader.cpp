#include "WaveHeader.hpp"
#include <iostream>

void WaveHeaderReader::Read() {
    ReadXBitToString(header_.chunck_id_, 4);
    file_.read(reinterpret_cast<char* >(&header_.chunck_size_), sizeof(header_.chunck_size_));
    ReadXBitToString(header_.format_, 4);
    ReadXBitToString(header_.sub_chank1_id_, 4);
    file_.read(reinterpret_cast<char* >(&header_.chunck1_size_), sizeof(uint32_t));
    file_.read(reinterpret_cast<char* >(&header_.format_code_), sizeof(uint16_t));
    file_.read(reinterpret_cast<char* >(&header_.number_of_channels_), sizeof(uint16_t));
    file_.read(reinterpret_cast<char* >(&header_.samples_per_second_), sizeof(uint32_t));
    file_.read(reinterpret_cast<char* >(&header_.bytes_per_second_), sizeof(uint32_t));
    file_.read(reinterpret_cast<char* >(&header_.bytes_per_sample_frame_), sizeof(uint16_t));
    file_.read(reinterpret_cast<char* >(&header_.bits_per_sample_), sizeof(uint16_t));

}

void WaveHeaderReader::PrintInfo() {
    std::cout << "ChunckID: "<<header_.chunck_id_
              <<"\nChunck size: "<<header_.chunck_size_
              <<"\nFormat: "<<header_.format_
              <<"\nSubChunck1ID: "<<header_.sub_chank1_id_
              <<"\nFormat Code: "<<header_.format_code_
              <<"\nNumber of channels: "<<header_.number_of_channels_
              <<"\nSamples per second: "<<header_.samples_per_second_
              <<"\nBytes per second: "<<header_.bytes_per_second_
              <<"\nBytes per sample frame: "<<header_.bytes_per_sample_frame_
              <<"\nBits per sample: "<<header_.bits_per_sample_;
}

void WaveHeaderReader::ReadXBitToString(std::string& str, const size_t X) {
    char tmp[X+1] {};
    for (int i = 0; i<X; i++)
        file_.get(tmp[i]);
    str = std::string(tmp);
}