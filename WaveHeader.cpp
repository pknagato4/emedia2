#include "WaveHeader.hpp"
#include <iostream>

void WaveHeaderReader::Read() {
    char c;
    for(int i=0;i<4;i++)
        file_.get(header_.chunck_id_[i]);

    file_.read(reinterpret_cast<char* >(&header_.chunck_size_), sizeof(header_.chunck_size_));

    for(int i=0;i<4;i++)
        file_.get(header_.format_[i]);

    for(int i=0;i<4;i++) {
        file_.get(header_.sub_chank1_id_[i]);
    }

}

void WaveHeaderReader::PrintInfo() {
    std::cout << "ChunckID: ";
    for(int i=0;i<4;i++)
        std::cout<<header_.chunck_id_[i];
    std::cout<<"\nChunck size: ";
    std::cout<<header_.chunck_size_;
    std::cout<<"\nFormat: ";
    for(int i=0;i<4;i++)
        std::cout<<header_.format_[i];
    std::cout<<"\nSubChunck1ID: ";
    for(int i=0;i<4;i++)
        std::cout<<header_.sub_chank1_id_[i];
}