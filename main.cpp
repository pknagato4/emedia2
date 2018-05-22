#include "WaveReader.hpp"
#include <iostream>

#include "GNUPlot.h"
#include "WaveSaver.h"
#include "Encrypter.h"
#include "RsaCoder.h"
#include <boost/multiprecision/cpp_int.hpp>


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
//    wav.PrintInfo();
    auto header = wav.getHeader_();
    auto samples = wav.getChannels_();

    std::cout<<samples.first.back()<<"\n";
    Encrypter coder;
    auto samples2 = coder.CodeXor(samples);
    WaveSaver saver("test_coded.wav", header, samples);
    saver.Save();

    auto samples3 = coder.CodeXor(samples);
    std::cout<<samples.first.back()<<"\n";
    WaveSaver saver2("test_encoded.wav", header, samples);
    saver2.Save();

//    plot(PrepareScript("\"channel1fft.txt\""));
//    if (wav.getHeader_().number_of_channels_ == 2)
//        plot(PrepareScript("\"channel2fft.txt\""));

//
//    RsaCoder code;
//    code.Code(123);

    rsa_size_type first_prime = 11;
    rsa_size_type second_prime = 13;
    RsaKey key = RsaKeyGenerator::Generate(first_prime, second_prime);
    RsaCoder rc;
    rc.setKey(key.public_key.first, key.public_key.second);
    auto coded = rc.Code(123);
    rc.setKey(key.private_key.first, key.private_key.second);
    auto encoded = rc.Decode(coded);
    std::cout<<"\nPrivate key: "<<key.private_key.first<<" : "<<key.private_key.second
             <<"\nPublic key: "<<key.public_key.first<<" : "<<key.public_key.second
             <<"\nCoded: "<<coded<<" Encoded: "<<encoded<<"\n";


}