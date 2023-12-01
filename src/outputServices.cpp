#include "../include/outputServices.hpp"
#include <iostream>
#include <string>
#include <iomanip>

void numeroDeVagasEleicao(const Eleicao &eleicao);
void candidatosEleitos(const Eleicao &eleicao);
void candidatosMaisVotados(const Eleicao &eleicao);
void candidatosPrejudicados(const Eleicao &eleicao);
void candidatosBeneficiados(const Eleicao &eleicao);
void votacaoPartidosCandidatosEleitos(const Eleicao &eleicao);
void primeiroEUltimoCandidatoDosPartidos(const Eleicao &eleicao);
void eleitosPorIdade(const Eleicao& eleicao);
void eleitosPorGenero(const Eleicao &eleicao);
void totalVotos(const Eleicao &eleicao);
string plural_singular_filter(string out, int value);

void outputServices::geracaoRelatorios(const Eleicao& eleicao){
    numeroDeVagasEleicao(eleicao);
    candidatosEleitos(eleicao);
    candidatosMaisVotados(eleicao);
    candidatosPrejudicados(eleicao);
    candidatosBeneficiados(eleicao);
    votacaoPartidosCandidatosEleitos(eleicao);
    primeiroEUltimoCandidatoDosPartidos(eleicao);
    eleitosPorIdade(eleicao);
    eleitosPorGenero(eleicao);
    totalVotos(eleicao);
}

void numeroDeVagasEleicao(const Eleicao &eleicao){
    cout.imbue(locale("pt_BR.utf8"));
    cout << "Número de vagas: " << eleicao.getQuantidadeEleitos() << endl << endl;
    cout.imbue(locale("C"));
}

void candidatosEleitos(const Eleicao &eleicao){
    string categoria = "";

    if(eleicao.getTipoEleicao() == 6){
        categoria = "federais";
    } else if(eleicao.getTipoEleicao() == 7){
        categoria = "estaduais";
    }

    cout << "Deputados " << categoria <<" eleitos:" << endl;

    string vot;
    for(Candidato c : eleicao.getCandidatosEleitos()){
        cout << c.getPosicaoEleito() << " - ";

        if(c.getPartido()->getFederacao() != -1){
            cout << "*";
        }
        
        vot = "voto";
        vot = plural_singular_filter(vot, c.getQuantidadeVotos());

        cout << c.getNomeUrnaCandidato() << " (" << c.getPartido()->getSiglaPartido() << ", ";
        cout.imbue(locale("pt_BR.utf8"));
        cout << c.getQuantidadeVotos() << " " << vot << ")" << endl;
        cout.imbue(locale("C"));
    }
    cout << endl;
}

void candidatosMaisVotados(const Eleicao &eleicao){
    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;

    string vot;
    for(Candidato c : eleicao.getCandidatosMaisVotados()){
        cout << c.getPosicaoGeral() << " - ";

        if(c.getPartido()->getFederacao() != -1){
            cout << "*";
        }

        vot = "voto";
        vot = plural_singular_filter(vot, c.getQuantidadeVotos());
        cout << c.getNomeUrnaCandidato() << " (" << c.getPartido()->getSiglaPartido() << ", ";
        
        cout.imbue(locale("pt_BR.utf8"));
        cout << c.getQuantidadeVotos() << " " << vot << ")" << endl;
        cout.imbue(locale("C"));
    }
    cout << endl;
}

void candidatosPrejudicados(const Eleicao &eleicao){
    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;
    string vot;

    for(Candidato c : eleicao.getCandidatosEleitosSeSistemaMajoritario()){
        cout << c.getPosicaoGeral() << " - ";

        if(c.getPartido()->getFederacao() != -1){
            cout << "*";
        }
        
        vot = "voto";
        vot = plural_singular_filter(vot, c.getQuantidadeVotos());
        cout << c.getNomeUrnaCandidato() << " (" << c.getPartido()->getSiglaPartido() << ", ";
        
        cout.imbue(locale("pt_BR.utf8"));
        cout << c.getQuantidadeVotos() << " " << vot << ")" << endl;
        cout.imbue(locale("C"));
    }
    cout << endl;
}

void candidatosBeneficiados(const Eleicao &eleicao){
    cout << "Eleitos, que se beneficiaram do sistema proporcional:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;
    
    string vot;
    for(Candidato c : eleicao.getCandidatosEleitosSistemaProporcional()){

        cout << c.getPosicaoGeral() << " - ";
        
        if(c.getPartido()->getFederacao() != -1){
            cout << "*";
        }

        vot = "voto";
        vot = plural_singular_filter(vot, c.getQuantidadeVotos());
        cout << c.getNomeUrnaCandidato() << " (" << c.getPartido()->getSiglaPartido() << ", ";
        
        cout.imbue(locale("pt_BR.utf8"));
        cout << c.getQuantidadeVotos() << " " << vot << ")" << endl;
        cout.imbue(locale("C"));
    }
    cout << endl;
}

void votacaoPartidosCandidatosEleitos(const Eleicao &eleicao){
    cout << "Votação dos partidos e número de candidatos eleitos:" << endl;
    
    string vot, nom, cand, ele;
    for(Partido p : eleicao.getPartidosList()){
        vot = "voto";
        nom = "nominal";
        cand = "candidato";
        ele = "eleito";

        vot = plural_singular_filter(vot, p.getVotosTotais());
        nom = plural_singular_filter(nom, p.getVotosNominais());
        cand = plural_singular_filter(cand, p.getQuantidadeEleitos());
        ele = plural_singular_filter(ele, p.getQuantidadeEleitos());

        cout << p.getPosicaoPartido() << " - ";
        cout.imbue(locale("pt_BR.utf8"));
        cout << p.getSiglaPartido() << " - " << p.getNumeroPartido() << ", " << p.getVotosTotais() << " " << vot
        << " (" << p.getVotosNominais() << " " << nom <<  " e " << p.getVotosDeLegenda() << " de legenda), "
        << p.getQuantidadeEleitos() << " " << cand << " " << ele << endl;

        cout.imbue(locale("C"));
    }
    cout << endl;
}

void primeiroEUltimoCandidatoDosPartidos(const Eleicao &eleicao){
    cout << "Primeiro e último colocados de cada partido:" << endl;
    
    string maisVotado, menosVotado;
    for(Partido p : eleicao.getPartidosOrdenadosPorCandidatos()){
        maisVotado = "voto";
        menosVotado = "voto";
        maisVotado = plural_singular_filter(maisVotado, p.getCandidatoMaisVotado().getQuantidadeVotos());
        menosVotado = plural_singular_filter(menosVotado, p.getCandidatoMenosVotado().getQuantidadeVotos());

        cout << p.getPosicaoPartido() << " - " << p.getSiglaPartido() << " - " << p.getNumeroPartido() << ", " 
        << p.getCandidatoMaisVotado().getNomeUrnaCandidato() << " (" << p.getCandidatoMaisVotado().getNumeroCandidato();
        cout.imbue(locale("pt_BR.utf8"));

        cout << ", " << p.getCandidatoMaisVotado().getQuantidadeVotos() << " " << maisVotado << ") / ";
        cout.imbue(locale("C"));

        cout << p.getCandidatoMenosVotado().getNomeUrnaCandidato() << " (" << p.getCandidatoMenosVotado().getNumeroCandidato();
        cout.imbue(locale("pt_BR.utf8"));
        cout << ", " << p.getCandidatoMenosVotado().getQuantidadeVotos() << " " << menosVotado << ")" << endl;
        cout.imbue(locale("C"));
    }
    cout << endl;
}

void eleitosPorIdade(const Eleicao& eleicao){
    cout <<"Eleitos, por faixa etária (na data da eleição):" << endl;

    int totalEleitos = eleicao.getQuantidadeEleitos();
    int f1 = eleicao.getQuantidadeEleitosPorIdade(0, 30);
    int f2 = eleicao.getQuantidadeEleitosPorIdade(30, 40);
    int f3 = eleicao.getQuantidadeEleitosPorIdade(40, 50);
    int f4 = eleicao.getQuantidadeEleitosPorIdade(50, 60);
    int f5 = eleicao.getQuantidadeEleitosPorIdade(60, 120);

    float p1 = ((float) f1 / (float) totalEleitos) * 100;
    float p2 = ((float) f2 / (float) totalEleitos) * 100;
    float p3 = ((float) f3 / (float) totalEleitos) * 100;
    float p4 = ((float) f4 / (float) totalEleitos) * 100;
    float p5 = ((float) f5 / (float) totalEleitos) * 100;

    cout.imbue(locale("pt_BR.utf8"));
    cout << fixed << setprecision(2) << "      Idade < 30: " << f1 << " (" << p1 << "%)" << endl;
    cout << fixed << setprecision(2) << "30 <= Idade < 40: " << f2 << " (" << p2 << "%)" << endl;
    cout << fixed << setprecision(2) << "40 <= Idade < 50: " << f3 << " (" << p3 << "%)" << endl;
    cout << fixed << setprecision(2) << "50 <= Idade < 60: " << f4 << " (" << p4 << "%)" << endl;
    cout << fixed << setprecision(2) << "60 <= Idade     : " << f5 << " (" << p5 << "%)" << endl;
    cout.imbue(locale("C"));
    cout << endl;
}

void eleitosPorGenero(const Eleicao &eleicao){
    int totalEleitos = eleicao.getQuantidadeEleitos();

    cout << "Eleitos, por gênero:" << endl;

    int homens = eleicao.getQuantidadeHomensEleitos();
    int mulheres = eleicao.getQuantidadeMulheresEleitas();

    float pHomens = ((float)homens / (float)totalEleitos) * 100;
    float pMulheres = ((float)mulheres / (float)totalEleitos) * 100;

    cout.imbue(locale("pt_BR.utf8"));
    cout << fixed << setprecision(2) << "Feminino:  " << mulheres << " (" << pMulheres << "%)" << endl;
    cout << fixed << setprecision(2) << "Masculino: " << homens << " (" << pHomens << "%)" << endl << endl;
    cout.imbue(locale("C"));
}

void totalVotos(const Eleicao &eleicao){
    int votosValidos = eleicao.getVotosLegenda() + eleicao.getVotosNominais();
    int nominal = eleicao.getVotosNominais();
    int legenda = eleicao.getVotosLegenda();

    float p_nominal = ((float)nominal / (float)votosValidos) * 100;
    float p_legenda = ((float)legenda / (float)votosValidos) * 100;
    
    cout.imbue(locale("pt_BR.utf8"));
    cout << "Total de votos válidos:    " << votosValidos << endl;
    cout << "Total de votos nominais:   " << fixed << setprecision(2) << nominal << " (" << p_nominal << "%)" << endl;
    cout << "Total de votos de legenda: " << fixed << setprecision(2) << legenda << " (" << p_legenda << "%)" << endl << endl;
    cout.imbue(locale("C"));
}

string plural_singular_filter(string out, int value){
    if(value > 1){
        if(out == "nominal") {
            return "nominais";
        }

        return out + "s";
    }

    return out;
}