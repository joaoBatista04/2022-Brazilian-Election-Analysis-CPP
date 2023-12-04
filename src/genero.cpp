#include "../include/genero.hpp" 

Genero::Genero(int cd_genero){    
    if(cd_genero == 2){
        this->_type = Genero::type::MASCULINO;
    } else if(cd_genero == 4){
        this->_type = Genero::type::FEMININO;
    } else{
        this->_type = Genero::type::FEMININO;
    }
}

int Genero::getGenero() const{
    if(this->_type == Genero::type::MASCULINO){
        return 2;
    } else if(this->_type == Genero::type::FEMININO){
        return 4;
    } else{
        return 4;
    }
}