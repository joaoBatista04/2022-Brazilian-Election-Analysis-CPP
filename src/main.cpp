#include "../include/candidato.hpp"
#include "../include/partido.hpp"
#include "../include/eleicao.hpp"
#include "../include/inputServices.hpp"
#include "../include/outputServices.hpp"
#include "../include/date.hpp"
#include "../include/fileInputException.hpp"

using std::cout;

int main(int argc, char const *argv[])
{
    int tipo;
    string estadual = "--estadual";
    string federal = "--federal";

    if (argv[1] == estadual){
        tipo = 7;
    } else if (argv[1] == federal){
        tipo = 6;
    } else{
        exit(1);
    }

    Eleicao eleicao = Eleicao(tipo, argv[4]);

    inputServices::processamentoArquivoCandidatos(argv[2], eleicao);

    inputServices::processamentoArquivoVotos(argv[3], eleicao);
    
    outputServices::geracaoRelatorios(eleicao);

    return 0;
}