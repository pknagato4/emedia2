//
// Created by patryk on 12.04.18.
//`1245780`


#include "WaveSaver.h"

void WaveSaver::Save() {
    std::fstream file (file_name_, std::ios::binary | std::ios::out);
    SaveHeader(file);
    SaveSamples(file);
}

void WaveSaver::SaveHeader(std::fstream &file) const {
    SaveMainChunk(file);
    SaveSubChunk1(file);
    SaveSubChunk2(file);
}

void WaveSaver::SaveSubChunk2(std::fstream &file) const {
    SaveStrAsBin(file, header_.sub_chank2_id_);
    SaveDecAsBin(file, header_.sub_chank2_size_);
}

void WaveSaver::SaveSubChunk1(std::fstream &file) const {
    SaveStrAsBin(file, header_.sub_chank1_id_);
    SaveDecAsBin(file, header_.chunk1_size_);
    SaveDecAsBin(file, header_.format_code_);
    SaveDecAsBin(file, header_.number_of_channels_);
    SaveDecAsBin(file, header_.samples_per_second_);
    SaveDecAsBin(file, header_.bytes_per_second_);
    SaveDecAsBin(file, header_.bytes_per_sample_frame_);
    SaveDecAsBin(file, header_.bits_per_sample_);
}

void WaveSaver::SaveMainChunk(std::fstream &file) const {
    SaveStrAsBin(file, header_.chunk_id_);
    SaveDecAsBin(file, header_.chunk_size_);
    SaveStrAsBin(file, header_.format_);
}

void WaveSaver::SaveSamples(std::fstream& file) {
    IsSingleChannel ? SaveSingleChannel(file): SaveDoubleChannel(file);
}

void WaveSaver::SaveSingleChannel(std::fstream &file) {
    for (const auto& sample : channels_.first) {
        SaveDecAsBin(file, sample);
    }
}

void WaveSaver::SaveDoubleChannel(std::fstream &file) {
    for (int i = 0; i<channels_.first.size(); i++) {
        SaveDecAsBin(file, channels_.first[i]);
        SaveDecAsBin(file, channels_.second[i]);
    }
}
