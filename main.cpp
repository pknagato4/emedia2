#include "WaveHeader.hpp"
#include <iostream>

#include "gnuplot-cpp-interface/GNUPlot/GNUPlot.h"

int main(int argc, char** argv) {
    std::string filename(argv[1]);
    WaveReader wav(filename);
    wav.Read();
    wav.PrintInfo();

    std::vector<std::string> script;
    script.push_back("set terminal x11");
    script.push_back("reset");
    script.push_back("plot \"sample1fft.txt\" with lines");

    GNUPlot plotter;
    plotter.open();
    plotter.execute(script);
    plotter.execute(script);

    getchar(); // prevent graph to close

    plotter.write("exit");
    plotter.flush();
    plotter.close();

}