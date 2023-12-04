#include "../include/tipoEleicao.hpp"

TipoEleicao::TipoEleicao(string tipoEleicao){
    if(tipoEleicao == "--estadual"){
        this->_tipoEleicao = TipoEleicao::tipoEleicao::ESTADUAL;
    } else if(tipoEleicao == "--federal"){
        this->_tipoEleicao = TipoEleicao::tipoEleicao::FEDERAL;
    } else{
        this->_tipoEleicao = TipoEleicao::tipoEleicao::FEDERAL;
    }
}

int TipoEleicao::getTipoEleicaoFn() const{
    if(this->_tipoEleicao == TipoEleicao::tipoEleicao::ESTADUAL){
        return 7;
    } else if(this->_tipoEleicao == TipoEleicao::tipoEleicao::FEDERAL){
        return 6;
    } else{
        return 6;
    }
}