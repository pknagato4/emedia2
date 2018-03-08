#include "WaveHeader.hpp"
#include <iostream>

void WaveHeaderReader::Read() {
    char c;
    for(int i=0;i<4;i++)
        file_.get(header_.chunck_id_[i]);
}

void WaveHeaderReader::PrintInfo() {
    for(int i=0;i<4;i++)
        std::cout<<header_.chunck_id_[i];
}