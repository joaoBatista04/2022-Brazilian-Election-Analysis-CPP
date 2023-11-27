#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <iostream>
#include <string>
#include "./partido.hpp"
#include "./date.hpp"
#include "../enums/genero.hpp"

using std::string;

class Candidato{

private:
    int qtd_votos;
    Genero cd_genero;
    int nr_candidato;
    int posicao_geral;
    int posicao_eleito;
    bool cd_sit_tot_turno;
    string nm_urna_candidato;
    string nm_tipo_destino_votos;
    Date dt_nascimento;
    Partido* partido;

public:
    /// @brief Construtor da classe Candidato
    /// @param nr_candidato 
    /// @param nm_urna_candidato 
    /// @param nm_tipo_destino_votos 
    /// @param data_nascimento 
    /// @param cd_sit_total_turno 
    /// @param genero 
    /// @param partido 
    Candidato(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date &data_nascimento, bool cd_sit_total_turno, Genero genero, Partido* partido);

    void setQuantidadeVotos(int qntVotos);
    void setPosicaoEleito(int posicaoEleito);
    void setPosicaoGeral(int posicaoGeral);

    int getQuantidadeVotos() const;
    int getGenero() const;
    int getNumeroCandidato() const;
    int getPosicaoGeral() const;
    int getPosicaoEleito() const;

    bool getCodigoSituacaoTotalTurno() const;
    //TO-DO OPERATORS AND COMPARATORS

    string getNomeUrnaCandidato() const;
    string getNomeTipoDestinoVotos() const;

    Date getDataNascimento() const;
    Partido* getPartido() const;

};

#endif