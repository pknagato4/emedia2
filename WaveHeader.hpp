#pragma once

#include <fstream>
#include <cstdint>
#include <vector>

struct WaveHeader {
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


class WaveReader {
public:
    WaveReader(std::string file_name)
            : file_(file_name, std::ios::binary|std::ios::in) {}
    void Read();
    void PrintInfo();


private:
    template <class Size>
    void ReadSingleType(Size* placeHolder) {
        file_.read(reinterpret_cast<char* >(placeHolder), sizeof(Size));
    }
    void ReadXBitToString(std::string& str, const size_t X);
    void ReadSamples(const int number_of_samples);
    void ReadMainChank();
    void ReadSubChank1();
    void ReadSubChank2();
    void SaveSamplesToFile();
    uint32_t CalculateSamplesNumber();
    void CalculateFFT();

    WaveHeader header_;
    std::fstream file_;
    std::vector<int16_t > samples_;
    std::vector<int16_t > samples2_;
};
