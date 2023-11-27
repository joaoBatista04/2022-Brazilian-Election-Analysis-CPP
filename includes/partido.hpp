#ifndef PARTIDO_H
#define PARTIDO_H

using namespace std;

#include <iostream>
#include <list>

class Candidato;

class Partido{

private:
    int numeroPartido;
    int posicaoPartido;
    int federacao;
    int votosDeLegenda;

    string sigla;

    list<Candidato*> listaCandidatosPartido;

public:
    Partido(int numeroPartido, string siglaPartido, int Federacao);

    void setPosicaoPartido(int posicao);
    void setVotosDeLegenda(int votosDeLegenda);
    void addCandidato(Candidato* candidato);

    int getNumeroPartido() const;
    int getPosicaoPartido() const;
    int getFederacao() const;
    int getVotosTotais() const;
    int getVotosDeLegenda() const;
    int getVotosNominais() const;
    int getQuantidadeEleitos() const;

    //TO-DO OPERATOR

    static bool comparadorPartidosPorCandidato(const Partido &p1, const Partido &p2);

    string getSiglaPartido() const;

    list<Candidato*> getListaDeCandidatos() const;

    Candidato getCandidatoMaisVotado() const;
    Candidato getCandidatoMenosVotado() const;
};

#endif