#include "Currency.h"
#include "Functions.h"
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

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

void Currency::add_history()
{
    cur_history[get_date()] = xchange_rate;
}

