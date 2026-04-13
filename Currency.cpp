#include "Currency.h"

Currency::Currency(std::string nname, double xxchange_rate, std::string ccur_Abbreviation)
{
    name = nname;
    xchange_rate = xxchange_rate;
    cur_Abbreviation = ccur_Abbreviation;
}

double Currency::Transfer(double units)
{
    return units * xchange_rate;
}