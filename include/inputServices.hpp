#ifndef INPUT_SERVICES_H
#define INPUT_SERVICES_H

#include <fstream>
#include <vector>
#include <string>
#include "./eleicao.hpp"

namespace inputServices{
    ifstream createReadingStream(string filePath);
    void processamentoArquivoCandidatos(string filePath, Eleicao& eleicao);
    void processamentoArquivoVotos(string filePath, Eleicao& eleicao);
    vector<string> split(string input, char delimiter);
}

#endif