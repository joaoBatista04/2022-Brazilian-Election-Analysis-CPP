#ifndef ELEICAO_H
#define ELEICAO_H

#include <list>
#include <map>
#include <string>

#include "./candidato.hpp"
#include "./partido.hpp"
#include "./date.hpp"
#include "./tipoEleicao.hpp"

using std::string;

class Eleicao{

private:
    map<int, Candidato*> candidatos;
    map<int, Partido*> partidos;
    map<int, Partido*> legendasPartidosCandidatos;
    
    int votosLegenda;
    int votosNominais;

    Date dataEleicao;
    TipoEleicao tipo;

public:
    Eleicao(string tipo, string data);

    int getTipoEleicao() const;
    int getVotosLegenda() const;
    int getVotosNominais() const;
    int getQuantidadeEleitos() const;
    int getQuantidadeHomensEleitos() const;
    int getQuantidadeMulheresEleitas() const;
    int getQuantidadeEleitosPorIdade(int dataInicio, int dataFim) const;

    void setVotosLegenda(int votosLegenda);
    void setVotosNominais(int votosNominais);
    void addLegendasPartidosCandidatos(int key, Partido* value);
    void addCandidato(int numeroCandidato, string nomeUrnaCandidato, string nomeTipoDestinacaoVotos, Date& dataNascimento, bool codigoSituacaoTotalTurno, int genero, Partido* partido);

    map<int, Candidato*> getCandidatosMap() const;
    map<int, Partido*> getPartidosMap() const;
    map<int, Partido*> getLegendaPartidosCandidatosMap() const;

    list<Candidato> getCandidatosEleitos() const;
    list<Candidato> getTodosOsCandidatos() const;
    list<Candidato> getCandidatosMaisVotados() const;
    list<Candidato> getCandidatosEleitosSistemaProporcional() const;
    list<Candidato> getCandidatosEleitosSeSistemaMajoritario() const;
    list<Partido> getPartidosList() const;
    list<Partido> getPartidosOrdenadosPorCandidatos() const;

    Date getDataAtual() const;

    Partido* addPartido(int numeroPartido, string siglaPartido, int federacaoPartido);

    ~Eleicao();
};

#endif