#ifndef DATE_H
#define DATE_H

using std::string;

class Date{

private:
    int dia;
    int mes;
    int ano;

public:
    Date(string date);

    string to_string() const;
    int until(const Date &date) const;

    //TO-DO  @todo
};

#endif