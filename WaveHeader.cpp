#include "WaveHeader.hpp"
#include <iostream>

void WaveHeaderReader::Read() {
    ReadMainChank();
    ReadSubChank1();
    ReadSubChank2();
}

void WaveHeaderReader::PrintInfo() {
    std::cout << "ChunckID: "<<header_.chunk_id_
              <<"\nChunck size: "<<header_.chunk_size_
              <<"\nFormat: "<<header_.format_
              <<"\nSubChunck1ID: "<<header_.sub_chank1_id_
              <<"\nFormat Code: "<<header_.format_code_
              <<"\nNumber of channels: "<<header_.number_of_channels_
              <<"\nSamples per second: "<<header_.samples_per_second_
              <<"\nBytes per second: "<<header_.bytes_per_second_
              <<"\nBytes per sample frame: "<<header_.bytes_per_sample_frame_
              <<"\nBits per sample: "<<header_.bits_per_sample_
              <<"\nSubChank2ID: "<<header_.sub_chank2_id_
              <<"\nSubChank2Size: "<<header_.sub_chank2_size_;
    std::cout<<"\nSamples: "<<header_.number_of_samples_<<"\n";
}

void WaveHeaderReader::ReadXBitToString(std::string& str, const size_t X) {
    char tmp[X+1] {};
    for (int i = 0; i<X; i++)
        file_.get(tmp[i]);
    str = std::string(tmp);
}

void WaveHeaderReader::ReadSamples(const int number_of_samples) {
    uint16_t sample;
    for (int i=0;i<number_of_samples;i++) {
        file_.read(reinterpret_cast<char* >(&sample), sizeof(sample));
        samples_.emplace_back(sample);
    }
}

uint32_t WaveHeaderReader::CalculateSamplesNumber() {
    return ((8*header_.sub_chank2_size_)/(header_.number_of_channels_*header_.bits_per_sample_));
}

void WaveHeaderReader::ReadMainChank() {
    ReadXBitToString(header_.chunk_id_, 4);
    ReadSingleType<uint32_t >(&header_.chunk_size_);
    ReadXBitToString(header_.format_, 4);
}

void WaveHeaderReader::ReadSubChank1() {
    ReadXBitToString(header_.sub_chank1_id_, 4);
    ReadSingleType<uint32_t >(&header_.chunk1_size_);
    ReadSingleType<uint16_t >(&header_.format_code_);
    ReadSingleType<uint16_t >(&header_.number_of_channels_);
    ReadSingleType<uint32_t >(&header_.samples_per_second_);
    ReadSingleType<uint32_t >(&header_.bytes_per_second_);
    ReadSingleType<uint16_t >(&header_.bytes_per_sample_frame_);
    ReadSingleType<uint16_t >(&header_.bits_per_sample_);
}

void WaveHeaderReader::ReadSubChank2() {
    ReadXBitToString(header_.sub_chank2_id_, 4);
    ReadSingleType<uint32_t >(&header_.sub_chank2_size_);
    header_.number_of_samples_ = CalculateSamplesNumber();
    ReadSamples(header_.number_of_samples_);
}