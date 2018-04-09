#pragma once

#include <fstream>
#include <cstdint>
#include <vector>
#include <iterator>
#include <valarray>
#include <complex>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

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
    template <class inputType, class dataType>
    void SaveToFile(const inputType& input, const std::string fileName, const size_t size) {
        std::ofstream myfile(fileName);
        std::copy(input.begin(), input.begin() + size -1, std::ostream_iterator<dataType>(myfile, "\n"));
    }

    void ReadXBitToString(std::string& str, const size_t X);
    void ReadSamples(const int number_of_samples, const int channels);
    void ReadMainChank();
    void ReadSubChank1();
    void ReadSubChank2();
    uint32_t CalculateSamplesNumber();
    void CalculateFFT();

    WaveHeader header_;
public:
    const WaveHeader &getHeader_() const;

private:
    std::fstream file_;
    std::vector<int16_t > channel1_;
    std::vector<int16_t > channel2_;

    void SaveSamplesToFile();

    void PrepareDataToFFT(const std::vector<int16_t> &input, CArray &output) const;

    void SaveFFTToFile(const std::string fileName, const CArray &data);

    void CalculateFFTForChannel(const std::vector<int16_t> &channel, const std::string fileName);
};
