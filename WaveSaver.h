//
// Created by patryk on 12.04.18.
//

#ifndef EMEDIA_WAVESAVER_H
#define EMEDIA_WAVESAVER_H

#include <vector>
#include <type_traits>
#include "WaveHeader.h"

class WaveSaver {
public:
        WaveSaver(std::string file_name, WaveHeader header, const std::pair<std::vector<int16_t>, std::vector<int16_t>> channels)
                : file_name_(file_name), header_(header)
                , channels_(channels), IsSingleChannel(channels.second.size() == 0 ? true : false) {}

        void Save();
private:
    std::string file_name_;
    WaveHeader header_;
    std::pair<std::vector<int16_t>, std::vector<int16_t>> channels_;
    bool IsSingleChannel;

    void SaveHeader(std::fstream &file) const;

    void SaveMainChunk(std::fstream &file) const;

    void SaveSubChunk1(std::fstream &file) const;

    void SaveSubChunk2(std::fstream &file) const;

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    void SaveDecAsBin(std::fstream& file, T toSave) const {
        file.write(reinterpret_cast<const char*>(&toSave), sizeof(toSave));
    }

    void SaveStrAsBin(std::fstream& file, std::string toSave) const {
        file.write(toSave.c_str(), toSave.size());
    }

    void SaveSamples(std::fstream& file);
    void SaveSingleChannel(std::fstream& file);
    void SaveDoubleChannel(std::fstream& file);
};


#endif //EMEDIA_WAVESAVER_H
