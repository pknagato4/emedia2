#include "WaveHeader.hpp"
#include <iostream>
int main(int argc, char** argv) {
    std::string filename(argv[1]);
    WaveReader wav(filename);
    wav.Read();
    wav.PrintInfo();
}