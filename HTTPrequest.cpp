#pragma once
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "HTTPrequest.h"

using json = nlohmann::json;

std::vector<Currency> currency_maker(std::string buffer)
{

    std::vector<Currency> currency_info;
    json document{ json::parse(buffer) };
    int json_lenght = document.size();
    for (int i = 0; i < json_lenght; i++)
    {
        json cur = document[i];
        auto name{
      cur["Cur_Name"].get<std::string>() };

        auto xchange_rate{
      cur["Cur_OfficialRate"].get<double>() };

        auto cur_Abbreviation{
      cur["Cur_Abbreviation"].get<std::string>() };

        Currency Cur(name, xchange_rate, cur_Abbreviation);

        currency_info.push_back(Cur);
    }

    return currency_info;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp)
{
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}