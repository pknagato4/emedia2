#include "WaveReader.hpp"
#include <iostream>

#include "GNUPlot.h"
#include "WaveSaver.h"
#include "Encrypter.h"
#include <boost/multiprecision/cpp_int.hpp>
#include "MathHelper.h"
#include <boost/numeric/conversion/cast.hpp>
using boost::numeric_cast;

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

rsa_size_type codeRsaI(RsaKey key, int16_t sample) {
    rsa_size_type sam = sample;
    return pot_mod(sam, key.public_key.first, key.public_key.second);
}

int16_t codeRsaK(RsaKey key, rsa_size_type sample) {
    return numeric_cast<int16_t>(pot_mod(sample, key.private_key.first, key.private_key.second));
}

std::pair<std::vector<rsa_size_type >, std::vector<rsa_size_type >> codeSamples(RsaKey key, samples_container channels) {
    std::pair<std::vector<rsa_size_type >, std::vector<rsa_size_type >> coded;
    for(auto sample : channels.first) {
        coded.first.emplace_back(codeRsaI(key, sample));
    }
    for(auto sample : channels.second) {
        coded.second.emplace_back(codeRsaI(key, sample));
    }
    return coded;
};

samples_container decodeSamples(RsaKey key, std::pair<std::vector<rsa_size_type >, std::vector<rsa_size_type >> channels) {
    samples_container decoded;
    for(auto sample : channels.first) {
        decoded.first.emplace_back(codeRsaK(key, sample));
    }
    for(auto sample : channels.second) {
        decoded.second.emplace_back(codeRsaK(key, sample));
    }
    return decoded;
}

int main(int argc, char** argv) {
    WaveReader wav(argv[1]);
    wav.Read();
//    wav.PrintInfo();
    auto header = wav.getHeader_();
    auto samples = wav.getChannels_();

    rsa_size_type first_prime = 11;
    rsa_size_type second_prime = 13;
    RsaKey key ;
    rsa_size_type priv, pub, n1;
    RSA_klucz(pub, priv, n1);
    key.private_key.first = priv;
    key.private_key.second = n1;
    key.public_key.first = pub;
    key.public_key.second = n1;

    std::cout<<samples.first.back()<<"\n";
    Encrypter coder;
    auto samples2 = codeSamples(key, samples);//coder.CodeRsa(samples, key.public_key);
//    WaveSaver saver("test_coded.wav", header, samples2);
//    saver.Save();

    auto samples3 = decodeSamples(key, samples2);//coder.CodeRsa(samples2, key.private_key);
    std::cout<<samples3.first.back()<<"\n";
    WaveSaver saver2("test_encoded.wav", header, samples3);
    saver2.Save();

    for (int i =0 ; i < samples3.first.size(); i++) {
        if (samples.first.at(i) != samples3.first.at(i)) {
            std::cout<<i<<" of "<<samples3.first.size();
            break;
        }
    }

////    plot(PrepareScript("\"channel1fft.txt\""));
////    if (wav.getHeader_().number_of_channels_ == 2)
////        plot(PrepareScript("\"channel2fft.txt\""));
//
//    std::cout<<"\nPrivate key: "<<key.private_key.first<<" : "<<key.private_key.second
//             <<"\nPublic key: "<<key.public_key.first<<" : "<<key.public_key.second;

}