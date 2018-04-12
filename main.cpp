#include "WaveReader.hpp"
#include <iostream>

#include "GNUPlot.h"


std::vector<std::string> PrepareScript(const std::string fileName) {
    std::vector<std::string> script;
    script.push_back("set terminal x11");
    script.push_back("reset");
    script.push_back("plot " + fileName + " with lines");
    return script;
}

void plot(const std::vector<std::string> &script) {
    GNUPlot plotter;
    plotter.open();
    plotter.execute(script);

    getchar(); // prevent graph to close

    plotter.write("exit");
    plotter.flush();
    plotter.close();
}

int main(int argc, char** argv) {
    WaveReader wav(argv[1]);
    wav.Read();
    wav.PrintInfo();

    plot(PrepareScript("\"channel1fft.txt\""));
    if (wav.getHeader_().number_of_channels_ == 2)
        plot(PrepareScript("\"channel2fft.txt\""));

}