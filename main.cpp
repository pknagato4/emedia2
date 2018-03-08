#include "WaveHeader.hpp"

int main() {
    WaveHeaderReader wav("disco_dancing.wav");
    wav.Read();
    wav.PrintInfo();
}