#pragma once
#include <string>
#include <map>
#include <chrono>

class Currency
{
public:
    std::string name;
    double xchange_rate;
    std::string cur_Abbreviation;

    std::map<std::string, double> cur_history;

    Currency(std::string nname, double xxchange_rate, std::string ccur_Abbreviation);
    double Transfer(double units);

    void add_history();

    
    
};