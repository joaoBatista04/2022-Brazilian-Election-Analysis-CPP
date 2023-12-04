#include "../include/candidato.hpp"
#include "../include/genero.hpp"

//CONSTRUTOR DA CLASSE
Candidato::Candidato(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date &data_nascimento, bool cd_sit_total_turno, int genero, Partido* partido): dt_nascimento(data_nascimento), cd_genero(genero){
    this->nr_candidato = nr_candidato;
    this->nm_urna_candidato = nm_urna_candidato;
    this->nm_tipo_destino_votos = nm_tipo_destino_votos;
    this->cd_sit_tot_turno = cd_sit_total_turno;
    this->partido = partido;
    this->qtd_votos = 0;
}

// SETTERS
void Candidato::setQuantidadeVotos(int qntVotos){
    this->qtd_votos += qntVotos;
}

void Candidato::setPosicaoEleito(int posicaoEleito){
    this->posicao_eleito = posicaoEleito;
}

void Candidato::setPosicaoGeral(int posicaoGeral){
    this->posicao_geral = posicaoGeral;
}

//GETTERS
int Candidato::getQuantidadeVotos() const{
    return this->qtd_votos;
}

int Candidato::getGenero() const{
    return this->cd_genero.getGenero();
}

int Candidato::getNumeroCandidato() const{
    return this->nr_candidato;
}

int Candidato::getPosicaoGeral() const{
    return this->posicao_geral;
}

int Candidato::getPosicaoEleito() const{
    return this->posicao_eleito;
}

bool Candidato::getCodigoSituacaoTotalTurno() const{
    return this->cd_sit_tot_turno;
}

string Candidato::getNomeUrnaCandidato() const{
    return this->nm_urna_candidato;
}

string Candidato::getNomeTipoDestinoVotos() const{
    return this->nm_tipo_destino_votos;
}

Date Candidato::getDataNascimento() const{
    return this->dt_nascimento;
}

Partido* Candidato::getPartido() const{
    return this->partido;
}

//OPERATORS AND COMPARATORS
bool Candidato::operator==(const Candidato& cand2) const{
    return this->nr_candidato == cand2.nr_candidato and 
            this->nm_urna_candidato == cand2.nm_urna_candidato and
            this->nm_tipo_destino_votos == cand2.nm_tipo_destino_votos and
            this->dt_nascimento == cand2.dt_nascimento and
            this->cd_sit_tot_turno == cand2.cd_sit_tot_turno and
            this->cd_genero.getGenero() == cand2.cd_genero.getGenero() and
            this->partido == cand2.partido and
            this->qtd_votos == cand2.qtd_votos;
}

bool Candidato::operator>(const Candidato& cand2) const{
    if(this->qtd_votos == cand2.qtd_votos){
        return this->dt_nascimento > cand2.dt_nascimento;
    }

    return this->qtd_votos > cand2.qtd_votos; 
}

bool Candidato::comparadorCandidato(const Candidato* const a, const Candidato* const b){
    return *a > *b;
}
