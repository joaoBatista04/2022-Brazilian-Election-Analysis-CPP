#include "../include/eleicao.hpp"
#include "../include/date.hpp"
#include <algorithm>

//CONSTRUTOR DA CLASSE
Eleicao::Eleicao(string tipo, string data): dataEleicao(data), tipo(tipo){
    this->votosLegenda = 0;
    this->votosNominais = 0;
}

//GETTERS
int Eleicao::getTipoEleicao() const{
    return this->tipo.getTipoEleicaoFn();
}

int Eleicao::getVotosLegenda() const{
    return this->votosLegenda;
}

int Eleicao::getVotosNominais() const{
    return this->votosNominais;
}

map<int, Candidato*> Eleicao::getCandidatosMap() const{
    return this->candidatos;
}

map<int, Partido*> Eleicao::getPartidosMap() const{
    return this->partidos;
}

map<int, Partido*> Eleicao::getLegendaPartidosCandidatosMap() const{
    return this->legendasPartidosCandidatos;
}

Date Eleicao::getDataAtual() const{
    return this->dataEleicao;
}

//SPECIAL GETTERS
int Eleicao::getQuantidadeEleitos() const{
    int resultado = 0;

    for(const auto &item : this->candidatos){
        if(item.second->getCodigoSituacaoTotalTurno()){
            resultado++;
        }
    }
    
    return resultado;
}

int Eleicao::getQuantidadeHomensEleitos() const{
    int total = 0;

    for(Candidato c : this->getCandidatosEleitos()){
        if(c.getGenero() == 2){
            total++;
        }
    }

    return total;
}

int Eleicao::getQuantidadeMulheresEleitas() const{
    int total = 0;

    for(Candidato c : this->getCandidatosEleitos()){
        if(c.getGenero() == 4){
            total++;
        }
    }

    return total;
}

int Eleicao::getQuantidadeEleitosPorIdade(int dataInicio, int dataFim) const{
    int total = 0;
    int diferenca = 0;
    list<Candidato> eleitos = this->getCandidatosEleitos();

    for(Candidato c : eleitos){
        diferenca = c.getDataNascimento().until(this->dataEleicao);

        if(diferenca >= dataInicio && diferenca < dataFim){
            total++;
        }
    }

    return total;
}

//SETTERS
void Eleicao::setVotosLegenda(int votosLegenda){
    this->votosLegenda += votosLegenda;
}

void Eleicao::setVotosNominais(int votosNominais){
    this->votosNominais += votosNominais;
}

void Eleicao::addLegendasPartidosCandidatos(int key, Partido* value){
    this->legendasPartidosCandidatos.insert(make_pair(key, value));
}

void Eleicao::addCandidato(int numeroCandidato, string nomeUrnaCandidato, string nomeTipoDestinacaoVotos, Date& dataNascimento, bool codigoSituacaoTotalTurno, int genero, Partido* partido){
    Candidato* cand = new Candidato(numeroCandidato, nomeUrnaCandidato, nomeTipoDestinacaoVotos, dataNascimento, codigoSituacaoTotalTurno, genero, partido);

    this->candidatos.insert(make_pair(numeroCandidato, cand));

    partido->addCandidato(cand);
}

//MORE SPECIAL GETTERS
list<Candidato> Eleicao::getCandidatosEleitos() const{
    list<Candidato> candidatos;

    for(Candidato c : this->getTodosOsCandidatos()){
        if(c.getCodigoSituacaoTotalTurno()){
            candidatos.push_back(c);
        }
    }

    candidatos.sort(std::greater<Candidato>());

    int x=1;
    
    for(Candidato &c : candidatos){
        c.setPosicaoEleito(x);

        x++;
    }

    return candidatos;
}

list<Candidato> Eleicao::getTodosOsCandidatos() const{
    list<Candidato> candidatosFn;

    for(const auto &item : this->candidatos){
        candidatosFn.push_back(*item.second);
    }

    candidatosFn.sort(std::greater<Candidato>());

    int x=1;

    for(Candidato &c : candidatosFn){
        c.setPosicaoGeral(x);

        x++;
    }
    
    return candidatosFn;
}

list<Candidato> Eleicao::getCandidatosMaisVotados() const{
    list<Candidato> candidatosFn;

    int x=0;

    for(Candidato c : this->getTodosOsCandidatos()){
        if(x == this->getQuantidadeEleitos()){
            break;
        }

        candidatosFn.push_back(c);

        x++;
    }

    candidatosFn.sort(std::greater<Candidato>());

    return candidatosFn;
}

list<Candidato> Eleicao::getCandidatosEleitosSistemaProporcional() const{
    list<Candidato> candidatosFn;
    bool flag;

    for(Candidato c: this->getCandidatosEleitos()){
        flag = true;

        for(Candidato c2: this->getCandidatosMaisVotados()){
            if(c == c2){
                flag = false;
            }
        }

        if(flag){
            candidatosFn.push_back(c);
        }
    }

    candidatosFn.sort(std::greater<Candidato>());

    return candidatosFn;
}

list<Candidato> Eleicao::getCandidatosEleitosSeSistemaMajoritario() const{
    list<Candidato> candidatosFn;
    list<Candidato> melhoresCandidatos = this->getCandidatosMaisVotados();
    list<Candidato> candidatosEleitos = this->getCandidatosEleitos();

    for(Candidato c: melhoresCandidatos){
        if(!count(candidatosEleitos.begin(), candidatosEleitos.end(), c)){
            candidatosFn.push_back(c);
        }
    }

    candidatosFn.sort(std::greater<Candidato>());

    return candidatosFn;
}

list<Partido> Eleicao::getPartidosList() const{
    list<Partido> partidosFn;

    for(const auto &item : this->partidos){
        partidosFn.push_back(*item.second);
    }

    partidosFn.sort(std::greater<Partido>());

    int x = 1;
    for(Partido &p : partidosFn){
        p.setPosicaoPartido(x);
        x++;
    }

    return partidosFn;
}

list<Partido> Eleicao::getPartidosOrdenadosPorCandidatos() const{
    list<Partido> partidosFn;

    for(Partido p : this->getPartidosList()){
        if(p.getVotosTotais() > 0 && p.getListaDeCandidatos().size() != 0){
            partidosFn.push_back(p);
        }
    }

    partidosFn.sort(Partido::comparadorPartidosPorCandidato);

    int x = 1;
    for(Partido &p : partidosFn){
        p.setPosicaoPartido(x);
        x++;
    }

    return partidosFn;
}

Partido* Eleicao::addPartido(int numeroPartido, string siglaPartido, int federacaoPartido){
    Partido * p = new Partido(numeroPartido, siglaPartido, federacaoPartido);

    this->partidos.insert(make_pair(numeroPartido, p));

    return p; 
}

//DESTRUTORES
Eleicao::~Eleicao(){
    for(auto &item : this->candidatos){
        delete item.second;
    }

    for(auto &item : this->partidos){
        delete item.second;
    }
}