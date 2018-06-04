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

union ByteSplit{
    ByteSplit() {}
    ~ByteSplit() {}
    rsa_size_type coded_sample;
    int16_t splited_samples[16];
};

samples_container splitCodedSamplesTo16bitSamples(std::pair<std::vector<rsa_size_type >, std::vector<rsa_size_type >> channels) {
    samples_container splited{};
    for(auto sample : channels.first) {
        ByteSplit bytes;
        bytes.coded_sample = sample;
        for(int i = 0; i<16 ;i++) {
            splited.first.push_back(bytes.splited_samples[i]);
        }
    }
    for(auto sample : channels.second) {
        ByteSplit bytes;
        bytes.coded_sample = sample;
        for(int i = 0; i<16 ;i++) {
            splited.second.push_back(bytes.splited_samples[i]);
        }
    }
    return splited;
}

std::pair<std::vector<rsa_size_type >, std::vector<rsa_size_type >> fetchCodedSamplesTo256BitSamples(samples_container channels) {
    std::pair<std::vector<rsa_size_type >, std::vector<rsa_size_type >> fetched{};
    ByteSplit bytes;
    for(int i = 0; i <  channels.first.size(); i++) {
        bytes.splited_samples[i%16] = channels.first[i];
        if(i%16 == 15) {
            fetched.first.push_back(bytes.coded_sample);
        }
    }
    for(int i = 0; i <  channels.second.size(); i++) {
        bytes.splited_samples[i%16] = channels.second[i];
        if(i%16 == 15) {
            fetched.second.push_back(bytes.coded_sample);
        }
    }
    return fetched;
};

std::pair<std::vector<rsa_size_type >, std::vector<rsa_size_type >> chunkSamples(samples_container channels) {
    std::pair<std::vector<rsa_size_type >, std::vector<rsa_size_type >> chunked{};
    ByteSplit bytes;
    std::vector<int16_t> tmp;
    for(int i = 0 ; i <  channels.first.size();i++)  {
        if (tmp.size() == 15) {
            bytes.splited_samples[0] = 0;
            for (int j = 1 ; j <= tmp.size() ; j++) {
                bytes.splited_samples[j] = tmp[j-1];
            }
            chunked.first.push_back(bytes.coded_sample);
            tmp.clear();
        }
        tmp.push_back(channels.first[i]);

    }
    for(int i = 0; i <  channels.second.size(); i++) {
        if (tmp.size() == 15) {
            bytes.splited_samples[0] = 0;
            for (int j = 1 ; j <= tmp.size() ; j++) {
                bytes.splited_samples[j] = tmp[j-1];
            }
            chunked.second.push_back(bytes.coded_sample);
            tmp.clear();
        }
        tmp.push_back(channels.second[i]);
    }
    return chunked;
};

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


    //test

    auto chunked = chunkSamples(samples);
    auto samples2 = codeSamples(key, samples);
    auto splited = splitCodedSamplesTo16bitSamples(samples2);
    auto fetched = fetchCodedSamplesTo256BitSamples(splited);
    auto samples3 = decodeSamples(key, samples2);
    auto dechunked ;

    for ( int i=0; i < fetched.first.size(); i++) {
        if ( fetched.first[i] != samples2.first[i]) {
            std::cout<<"error";
            break;
        }
    }

    std::cout<<"Coded size: "<<samples2.first.size()<<" splited size: "<<splited.first.size();



    WaveSaver saver2("test_encoded.wav", header, samples3);
    saver2.Save();
    header.sub_chank2_size_ = header.sub_chank2_size_*16;
    WaveSaver saver("test_coded.wav", header, splited);
    saver.Save();


}