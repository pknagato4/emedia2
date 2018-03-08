#include "WaveHeader.hpp"
#include <iostream>

void WaveHeaderReader::Read() {
    ReadXBitToString(header_.chunck_id_, 4);
    file_.read(reinterpret_cast<char* >(&header_.chunck_size_), sizeof(header_.chunck_size_));

    ReadXBitToString(header_.format_, 4);
    ReadXBitToString(header_.sub_chank1_id_, 4);
}

void WaveHeaderReader::PrintInfo() {
    std::cout << "ChunckID: "<<header_.chunck_id_
              <<"\nChunck size: "<<header_.chunck_size_
              <<"\nFormat: "<<header_.format_
              <<"\nSubChunck1ID: "<<header_.sub_chank1_id_;
}

void WaveHeaderReader::ReadXBitToString(std::string& str, const size_t X) {
    char tmp[X+1] {};
    for (int i = 0; i<X; i++)
        file_.get(tmp[i]);
    str = std::string(tmp);
}