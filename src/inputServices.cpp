#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdint>
#include "../include/inputServices.hpp"
#include "../include/partido.hpp"
#include "../include/fileInputException.hpp"

bool processamentoVotosValidosCandidatos(Eleicao &eleicao, vector<string> &data);
void processamentoVotosInvalidosCandidatos(Eleicao &eleicao, vector<string> &data);
void updateCandidatos(Eleicao &eleicao, Partido* partido, vector<string> &data);
void updateCandidatosInvalidos(Eleicao &eleicao, Partido * partido, vector<string> &data);

bool isCandidatoEleito(string sit);
bool isVotoValido(string cd_cargo, string nr_votavel, int type);
bool isCandidatoValido(string cd_cargo, string cd_detalhe_situacao_cand, int type);

string iso_8859_1_to_utf8(string str);
string removeChar(string input, char character);

vector<string> input_formatter(string &line);
Partido * updatePartidos(Eleicao &Eleicao, vector<string> &data);

ifstream inputServices::createReadingStream(string filePath){
    ifstream buffer(filePath);
    
    return buffer;
}

void inputServices::processamentoArquivoCandidatos(string filePath, Eleicao& eleicao){
    string linhaAtual;
    vector<string> dadosAtuais;
    Partido *partidoFn;
    ifstream f_input;

    try{
        f_input.open(filePath);

        getline(f_input, linhaAtual);

        while (getline(f_input, linhaAtual)) {

            if(linhaAtual.size() == 0){
                break;
            }

            dadosAtuais = input_formatter(linhaAtual);

            partidoFn = updatePartidos(eleicao, dadosAtuais);      

            if (isCandidatoValido(dadosAtuais[13], dadosAtuais[68], eleicao.getTipoEleicao())){
                updateCandidatos(eleicao, partidoFn, dadosAtuais);
                continue;
            }

            if (eleicao.getTipoEleicao() == stoi(dadosAtuais[13]) && dadosAtuais[67] == "Válido (legenda)"){
                updateCandidatosInvalidos(eleicao, partidoFn, dadosAtuais);
            }
        }
    } catch(const fileInputException& e){
        std::cerr <<  e.what() << endl;
        cout << "Não foi possível ver o arquivo." << endl;
    }

    f_input.close();
}

void inputServices::processamentoArquivoVotos(string filePath, Eleicao& eleicao){
    string linhaAtual;
    vector<string> dadosAtuais;
    ifstream f_input;

    f_input.open(filePath);

    getline(f_input, linhaAtual);

    while (getline(f_input, linhaAtual)) {

        dadosAtuais = input_formatter(linhaAtual);

        if (isVotoValido(dadosAtuais[17], dadosAtuais[19],  eleicao.getTipoEleicao())){
            if(!processamentoVotosValidosCandidatos(eleicao, dadosAtuais)){
                processamentoVotosInvalidosCandidatos(eleicao, dadosAtuais);
            }
        }
    }

    f_input.close();
}
    
vector<string> inputServices::split(string input, char delimiter){
    vector<string> resultado;
    string dados;
    
    input = iso_8859_1_to_utf8(input);
    stringstream stream(input);

    while (std::getline(stream, dados, delimiter)){
        resultado.push_back(dados);
    }

    return resultado;
}

//Private methods
bool processamentoVotosValidosCandidatos(Eleicao &eleicao, vector<string> &data){
    int numeroVotavel, qntdVotos;
    numeroVotavel = stoi(data[19]);
    qntdVotos = stoi(data[21]);

    if (eleicao.getCandidatosMap().count(numeroVotavel) != 0){
        eleicao.getCandidatosMap().at(numeroVotavel)->setQuantidadeVotos(qntdVotos);
        eleicao.setVotosNominais(qntdVotos);

        return true;
    }

    if (eleicao.getPartidosMap().count(numeroVotavel)){
        eleicao.getPartidosMap().at(numeroVotavel)->setVotosDeLegenda(qntdVotos);
        eleicao.setVotosLegenda(qntdVotos);

        return true;
    }

    return false;
}

void processamentoVotosInvalidosCandidatos(Eleicao &eleicao, vector<string> &data){
    int numeroVotavel, quantidadeVotos;
    numeroVotavel = stoi(data[19]);
    quantidadeVotos= stoi(data[21]);

    if (eleicao.getLegendaPartidosCandidatosMap().count(numeroVotavel)) {
        eleicao.getLegendaPartidosCandidatosMap().at(numeroVotavel)->setVotosDeLegenda(quantidadeVotos);
        eleicao.setVotosLegenda(quantidadeVotos);
    }
}

void updateCandidatos(Eleicao &eleicao, Partido* partido, vector<string> &data){
    int numeroCandidato;
    int cd_genero;
    string nomeUrnaCandidato = data[18];
    string nomeTipoDestinacaoVotos = data[67];
    Date data_nasc(data[42]);

    bool situacao;
    situacao = isCandidatoEleito(data[56]);
    numeroCandidato = stoi(data[16]);
    cd_genero = stoi(data[45]);

    eleicao.addCandidato(numeroCandidato, nomeUrnaCandidato, nomeTipoDestinacaoVotos, data_nasc, situacao, cd_genero, partido);
}

void updateCandidatosInvalidos(Eleicao &eleicao, Partido* partido, vector<string> &data){
    int numeroCandidato;

    numeroCandidato = stoi(data[16]);

    eleicao.addLegendasPartidosCandidatos(numeroCandidato, partido);
}

bool isCandidatoEleito(string situacao){
    int situacaoFn;

    situacaoFn = stoi(situacao);

    if (situacaoFn == 2 || situacaoFn == 3){
        return true;
    }

    return false;
}

bool isVotoValido(string codigoCargo, string numeroVotavel, int tipoEleicao){
    int codigoCandidato, nrV;

    codigoCandidato = stoi(codigoCargo);
    nrV = stoi(numeroVotavel);

    if (codigoCandidato == tipoEleicao && !(nrV > 94 && nrV < 99)){
        return true;
    }

    return false;
}

bool isCandidatoValido(string codigoCargo, string codigoDetalheSituacaoCargo, int tipoEleicao){
    int cdC, cdD;

    cdC = stoi(codigoCargo); 
    cdD = stoi(codigoDetalheSituacaoCargo);

    if ((cdC == tipoEleicao) && (cdD == 2 || cdD == 16)){
        return true;
    }

    return false;
}

string iso_8859_1_to_utf8(string str){
    string strOut;

    for(string::iterator it = str.begin(); it != str.end(); ++it){
      uint8_t ch = *it;
      
      if (ch < 0x80){
        strOut.push_back(ch);
      } else{
        strOut.push_back(0b11000000 | (ch >> 6));
        strOut.push_back(0b10000000 | (ch & 0b00111111));
      }
    }

    return strOut;
}

string removeChar(string input, char character){
    string resultado;

    for (char c : input){
        if (c != character) {
            resultado += character;
        }
    }

    return resultado;
}

vector<string> input_formatter(string &linha){
    vector<string> dadosAtuais = inputServices::split(linha, ';');

    for(string &s : dadosAtuais){
        s = s.substr(1,s.length() - 2);
    }

    return dadosAtuais;
}

Partido* updatePartidos(Eleicao &eleicao, vector<string> &data){
    int numeroPartido, numeroFederacao;
    string siglapartido = data[28];
    numeroPartido = stoi(data[27]);
    numeroFederacao = stoi(data[30]);

    if (eleicao.getPartidosMap().count(numeroPartido)){
        return eleicao.getPartidosMap().at(numeroPartido);
    }

    return eleicao.addPartido(numeroPartido, siglapartido, numeroFederacao);
}