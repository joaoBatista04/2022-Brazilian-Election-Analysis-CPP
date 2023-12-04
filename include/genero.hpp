#ifndef GENERO_H
#define GENERO_H

class Genero{

enum class type{MASCULINO, FEMININO};
type _type;

public:
    Genero(int cd_genero);
    int getGenero() const;
};

#endif