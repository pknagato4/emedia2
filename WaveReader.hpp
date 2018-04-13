#pragma once

#include <fstream>
#include <cstdint>
#include <vector>
#include <iterator>
#include <valarray>
#include <complex>
#include "WaveHeader.h"

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;


class WaveReader {
public:
    WaveReader(std::string file_name)
            : file_(file_name, std::ios::binary | std::ios::in) {}

    void Read();

    void PrintInfo();
    const WaveHeader &getHeader_() const;

private:
    template<class Size>
    void ReadSingleType(Size *placeHolder) {
        file_.read(reinterpret_cast<char * >(placeHolder), sizeof(Size));
    }

    template<class inputType, class dataType>
    void SaveToFile(const inputType &input, const std::string fileName, const size_t size) {
        std::ofstream myfile(fileName);
        std::copy(input.begin(), input.begin() + size - 1, std::ostream_iterator<dataType>(myfile, "\n"));
    }

    void ReadXBitToString(std::string &str, const size_t X);
    void ReadSamples(const int number_of_samples, const int channels);
    void ReadMainChank();
    void ReadSubChank1();
    void ReadSubChank2();
    uint32_t CalculateSamplesNumber();
    void CalculateFFT();
    void SaveSamplesToFile();
    void PrepareDataToFFT(const std::vector<int16_t> &input, CArray &output) const;
    void SaveFFTToFile(const std::string fileName, const CArray &data);
    void CalculateFFTForChannel(const std::vector<int16_t> &channel, const std::string fileName);


private:
    std::fstream file_;
    WaveHeader header_;
    std::pair<std::vector<int16_t>, std::vector<int16_t>> channels_;
public:
    const std::pair<std::vector<int16_t>, std::vector<int16_t>> &getChannels_() const;
};
