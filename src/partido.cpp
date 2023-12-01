#include "../include/partido.hpp"

//CONSTRUTOR DA CLASSE
Partido::Partido(int numeroPartido, string siglaPartido, int federacaoPartido){
    this->numeroPartido = numeroPartido;
    this->sigla = siglaPartido;
    this->federacao = federacaoPartido;
    this->votosDeLegenda = 0;
}

//SETTERS
void Partido::setPosicaoPartido(int posicao){
    this->posicaoPartido = posicao;
}

void Partido::setVotosDeLegenda(int votosDeLegenda){
    this->votosDeLegenda += votosDeLegenda;
}

void Partido::addCandidato(Candidato* candidato){
    this->listaCandidatosPartido.push_back(candidato);
}

//GETTERS
int Partido::getNumeroPartido() const{
    return this->numeroPartido;
}

int Partido::getPosicaoPartido() const{
    return this->posicaoPartido;
}

int Partido::getFederacao() const{
    return this->federacao;
}

int Partido::getVotosDeLegenda() const{
    return this->votosDeLegenda;
}

string Partido::getSiglaPartido() const{
    return this->sigla;
}

//OPERATORS AND COMPARATORS
bool Partido::operator>(const Partido &partido2) const{
    int votosTotaisP1 = this->votosDeLegenda + this->getVotosNominais();
    int votosTotaisP2 = partido2.votosDeLegenda + partido2.getVotosNominais();

    if (votosTotaisP1 > votosTotaisP2){
      return true;
    }

    if (votosTotaisP1 < votosTotaisP2){
      return false;
    }

    if (this->numeroPartido < partido2.numeroPartido){
      return true;
    }

    if (this->numeroPartido > partido2.numeroPartido){
      return false;
    }

    return false;
}

bool Partido::comparadorPartidosPorCandidato(const Partido &p1, const Partido &p2){
    if(p1.getCandidatoMaisVotado().getQuantidadeVotos() > p2.getCandidatoMaisVotado().getQuantidadeVotos()){
        return true;
    }

    if(p1.getCandidatoMaisVotado().getQuantidadeVotos() == p2.getCandidatoMaisVotado().getQuantidadeVotos()){
        if(p1.getCandidatoMaisVotado().getDataNascimento() > p2.getCandidatoMaisVotado().getDataNascimento()){
            return true;
        }
        
        if(p1.getCandidatoMaisVotado().getPartido()->getNumeroPartido() < p2.getCandidatoMaisVotado().getPartido()->getNumeroPartido()){
            return true;
        }
    }

    return false;
}

//SPECIAL GETTERS
list<Candidato*> Partido::getListaDeCandidatos() const{
    list<Candidato*> resultado = this->listaCandidatosPartido;

    resultado.sort(Candidato::comparadorCandidato);

    return resultado;
}

int Partido::getVotosTotais() const{
    return this->votosDeLegenda + getVotosNominais();
}

int Partido::getVotosNominais() const{
    int total=0;

    for(Candidato* c : this->listaCandidatosPartido){
        total += c->getQuantidadeVotos();
    }

    return total;
}

int Partido::getQuantidadeEleitos() const{
    int quantidadeEleitos=0;

    for(Candidato* c : this->listaCandidatosPartido){
        if(c->getCodigoSituacaoTotalTurno()){
            quantidadeEleitos++;
        }
    }

    return quantidadeEleitos;
}

Candidato Partido::getCandidatoMaisVotado() const{
    list<Candidato*> listaCandidatosOrdenada = this->getListaDeCandidatos();

    listaCandidatosOrdenada.sort(Candidato::comparadorCandidato);

    return *listaCandidatosOrdenada.front();
}

Candidato Partido::getCandidatoMenosVotado() const{
    list<Candidato*> listaCandidatosOrdenada = this->getListaDeCandidatos();

    listaCandidatosOrdenada.sort(Candidato::comparadorCandidato);
    
    return *listaCandidatosOrdenada.back();
}