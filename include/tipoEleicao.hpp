#ifndef TIPO_ELEICAO_H
#define TIPO_ELEICAO_H

#include <string>

using std::string;

class TipoEleicao{

enum class tipoEleicao{ESTADUAL, FEDERAL};
tipoEleicao _tipoEleicao;

public:
    TipoEleicao(string tipoEleicao);
    int getTipoEleicaoFn() const;
};

#endif