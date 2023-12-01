#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>

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

    bool operator>(const Date& date2) const;
    bool operator==(const Date& date2) const;
};

#endif