#include <string>
#include <iostream>
#include "../include/date.hpp"
#include "../include/inputServices.hpp"

Date::Date(string date){
    vector<string> dataFormatada = inputServices::split(date, '/');

    this->dia = stoi(dataFormatada[0]);
    this->mes = stoi(dataFormatada[1]);
    this->ano = stoi(dataFormatada[2]);
}

string Date::to_string() const{
    string a = std::to_string(this->dia) + '/' + std::to_string(this->mes) + '/' + std::to_string(this->ano);
  
    return a;
}

int Date::until(const Date &date) const{
    int idade = date.ano - this->ano;
  
    if(date.mes < this->mes){
      idade--;
    }

    else if(date.mes == this->mes){
      if(date.dia < this->dia){
        idade--;
      }
    }

    return idade;
}
    
bool Date::operator>(const Date& date2) const{
    if(this->ano < date2.ano){
        return true;
    }

    if(this->ano == date2.ano){
      if(this->mes < date2.mes){
          return true;
      }

      if(this->mes == date2.mes){
        if(this->dia < date2.dia){
          return true;
        }
      }
    }
    
    return false;
}
    
bool Date::operator==(const Date& date2) const{
    return this->dia == date2.dia and
           this->mes == date2.mes and
           this->ano == date2.ano;
}