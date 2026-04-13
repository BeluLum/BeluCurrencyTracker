#pragma once
#include <string>

class Currency
{
public:
    std::string name;
    double xchange_rate;
    std::string cur_Abbreviation;

    Currency(std::string nname, double xxchange_rate, std::string ccur_Abbreviation);
    double Transfer(double units);
};