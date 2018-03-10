#include "WaveHeader.hpp"
#include <iostream>
int main() {
    WaveReader wav("disco_dancing.wav");
    wav.Read();
    wav.PrintInfo();
}