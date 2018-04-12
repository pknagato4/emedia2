#include "WaveReader.hpp"
#include "FFT.hpp"

void WaveReader::Read() {
    ReadMainChank();
    ReadSubChank1();
    ReadSubChank2();
}

void WaveReader::PrintInfo() {
    std::cout << "ChunckID: "<<header_.chunk_id_
              <<"\nChunck size: "<<header_.chunk_size_
              <<"\nFormat: "<<header_.format_
              <<"\nSubChunck1ID: "<<header_.sub_chank1_id_
              <<"\nSubChunck1 size: "<<header_.chunk1_size_
              <<"\nFormat Code: "<<header_.format_code_
              <<"\nNumber of channels: "<<header_.number_of_channels_
              <<"\nSamples per second: "<<header_.samples_per_second_
              <<"\nBytes per second: "<<header_.bytes_per_second_
              <<"\nBytes per sample frame: "<<header_.bytes_per_sample_frame_
              <<"\nBits per sample: "<<header_.bits_per_sample_
              <<"\nSubChank2ID: "<<header_.sub_chank2_id_
              <<"\nSubChank2Size: "<<header_.sub_chank2_size_
              <<"\nSamples: "<<header_.number_of_samples_
              <<"\n";
    SaveSamplesToFile();
    CalculateFFT();
}

void WaveReader::SaveSamplesToFile() {
    SaveToFile<decltype(channel1_), int16_t>(channel1_, "channel1.txt", channel1_.size());
    if (header_.number_of_channels_ == 2)
        SaveToFile<decltype(channel1_), int16_t>(channel2_, "channel2.txt", channel2_.size());
}

void WaveReader::ReadXBitToString(std::string& str, const size_t X) {
    char tmp[X+1] {};
    for (int i = 0; i<X; i++)
        file_.get(tmp[i]);
    str = std::string(tmp);
}

void WaveReader::ReadSamples(const int number_of_samples, const int channels) {
    int16_t sample;
    for (int i=0;i<channels*number_of_samples;i++) {
        file_.read(reinterpret_cast<char* >(&sample), sizeof(sample));

        if (channels == 2)
            (i%2==0) ? channel1_.emplace_back(sample) : channel2_.emplace_back(sample);
        else if (channels == 1)
            channel1_.emplace_back(sample);
    }
}

uint32_t WaveReader::CalculateSamplesNumber() {
    return ((8*header_.sub_chank2_size_)/(header_.number_of_channels_*header_.bits_per_sample_));
}

void WaveReader::ReadMainChank() {
    ReadXBitToString(header_.chunk_id_, 4);
    ReadSingleType<uint32_t >(&header_.chunk_size_);
    ReadXBitToString(header_.format_, 4);
}

void WaveReader::ReadSubChank1() {
    ReadXBitToString(header_.sub_chank1_id_, 4);
    ReadSingleType<uint32_t >(&header_.chunk1_size_);
    ReadSingleType<uint16_t >(&header_.format_code_);
    ReadSingleType<uint16_t >(&header_.number_of_channels_);
    ReadSingleType<uint32_t >(&header_.samples_per_second_);
    ReadSingleType<uint32_t >(&header_.bytes_per_second_);
    ReadSingleType<uint16_t >(&header_.bytes_per_sample_frame_);
    ReadSingleType<uint16_t >(&header_.bits_per_sample_);
}

void WaveReader::ReadSubChank2() {
    ReadXBitToString(header_.sub_chank2_id_, 4);
    if (header_.bytes_per_sample_frame_ == 4)
        ReadSingleType<uint32_t >(&header_.sub_chank2_size_);
    else if (header_.bytes_per_sample_frame_ == 2) {
        uint16_t tmp;
        ReadSingleType<uint16_t >(&tmp);
        header_.sub_chank2_size_ = tmp;
    }
    header_.number_of_samples_ = CalculateSamplesNumber();
    ReadSamples(header_.number_of_samples_, header_.number_of_channels_);
}

void WaveReader::CalculateFFT() {
    CalculateFFTForChannel(channel1_, "channel1fft.txt");
    if (header_.number_of_channels_ == 2)
        CalculateFFTForChannel(channel2_, "channel2fft.txt");
}

void WaveReader::CalculateFFTForChannel(const std::vector<int16_t> &channel, const std::string fileName) {
    CArray data;
    PrepareDataToFFT(channel, data);

    fft(data);

    SaveFFTToFile(fileName, data);
}

void WaveReader::SaveFFTToFile(const std::string fileName, const CArray &data) {
    std::vector<double> vec;
    for(auto dat : data) {
            vec.emplace_back(abs(dat));
        }
    SaveToFile<decltype(vec), double>(vec, fileName, vec.size()/2);
}

void WaveReader::PrepareDataToFFT(const std::vector<int16_t> &input, CArray &output) const {
    Complex v[header_.samples_per_second_];
    for (int i = 0; i < header_.samples_per_second_; i++) {
            v[i] = input[i];
        }
    output = CArray(v, header_.samples_per_second_);
}

const std::vector<int16_t> &WaveReader::getChannel1_() const {
    return channel1_;
}

const WaveHeader &WaveReader::getHeader_() const {
    return header_;
}

const std::vector<int16_t> &WaveReader::getChannel2_() const {
    return channel2_;
}
