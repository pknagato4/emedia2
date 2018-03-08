#pragma once

#include <fstream>

struct WaveHeader {
    char chunck_id_[4];
};


class WaveHeaderReader {
public:
    WaveHeaderReader(std::string file_name)
            : file_(file_name, std::ios::binary|std::ios::in) {}
    void Read();
    void PrintInfo();
private:
    WaveHeader header_;
    std::fstream file_;
};