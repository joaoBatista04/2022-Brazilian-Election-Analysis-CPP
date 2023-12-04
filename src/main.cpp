#include "../include/candidato.hpp"
#include "../include/partido.hpp"
#include "../include/eleicao.hpp"
#include "../include/inputServices.hpp"
#include "../include/outputServices.hpp"
#include "../include/date.hpp"
#include "../include/fileInputException.hpp"

int main(int argc, char const *argv[]){
    Eleicao eleicao = Eleicao(argv[1], argv[4]);

    inputServices::processamentoArquivoCandidatos(argv[2], eleicao);

    inputServices::processamentoArquivoVotos(argv[3], eleicao);
    
    outputServices::geracaoRelatorios(eleicao);

    return 0;
}