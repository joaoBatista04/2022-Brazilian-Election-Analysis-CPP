#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <iostream>
#include <string>
#include "./partido.hpp"
#include "./date.hpp"

using std::string;

class Partido;
class Date;

class Candidato{

private:
    int cd_genero;

    int qtd_votos;
    int nr_candidato;
    int posicao_geral;
    int posicao_eleito;

    bool cd_sit_tot_turno;

    string nm_urna_candidato;
    string nm_tipo_destino_votos;
    
    Date dt_nascimento;
    Partido* partido;

public:
    Candidato(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date &data_nascimento, bool cd_sit_total_turno, int genero, Partido* partido);

    void setQuantidadeVotos(int qntVotos);
    void setPosicaoEleito(int posicaoEleito);
    void setPosicaoGeral(int posicaoGeral);

    int getQuantidadeVotos() const;
    int getGenero() const;
    int getNumeroCandidato() const;
    int getPosicaoGeral() const;
    int getPosicaoEleito() const;

    bool getCodigoSituacaoTotalTurno() const;
    bool operator>(const Candidato& cand2) const;
    bool operator==(const Candidato& cand2) const;
    static bool comparadorCandidato(const Candidato* const a, const Candidato* const b);

    string getNomeUrnaCandidato() const;
    string getNomeTipoDestinoVotos() const;

    Date getDataNascimento() const;
    Partido* getPartido() const;
};

#endif