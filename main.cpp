#include "WaveReader.hpp"
#include <iostream>

#include "GNUPlot.h"
#include "WaveSaver.h"


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
    auto header = wav.getHeader_();
    auto samples = wav.getChannels_();
    std::cout << "samples 1 size: "<<samples.first.size() << "sampples 2 szie"<<samples.second.size()<<"last chann1"<<samples.first.back();

    WaveSaver saver("test.wav", header, samples);
    saver.Save();
    std::cout<<"\n";
    WaveReader wav2("test.wav");
    wav2.Read();
    wav2.PrintInfo();
    auto samples2 = wav.getChannels_();
    std::cout << "samples 1 size: "<<samples2.first.size() << "sampples 2 szie"<<samples2.second.size()<<"last chann1"<<samples2.first.back();;

//    plot(PrepareScript("\"channel1fft.txt\""));
//    if (wav.getHeader_().number_of_channels_ == 2)
//        plot(PrepareScript("\"channel2fft.txt\""));

}