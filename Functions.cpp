#pragma once
#include "Functions.h"
#include "Currency.h"
#include "HTTPrequest.h"
#include <iostream>
#include <format>
#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

std::string transferator(std::vector<Currency> currency_info)
{
    bool flag;
    std::string saver;
    std::string entered_id;
    double units;

    std::cout << "Enter the currency abbreviation from the list below: " << std::endl;

    for (int i = 0; i < currency_info.size(); i++)
    {
        std::cout << currency_info[i].name << " - " << currency_info[i].cur_Abbreviation << std::endl;
    }
    std::cout << std::endl << " >> ";
    std::cin >> entered_id;

    for (int j = 0; j < currency_info.size(); j++)

    {
        if (entered_id == currency_info[j].cur_Abbreviation)
        {
            std::cout << "Current rate: " << currency_info[j].xchange_rate << std::endl;
            std::cout << "Please enter amount to transfer: " << std::endl;
            std::cout << std::endl << " >> ";
            std::cin >> units;
            std::cout << "Success!" << std::endl << "Result: " << currency_info[j].Transfer(units) << "byn" << std::endl;
            saver = std::format("{} {} > {} byn", units, currency_info[j].cur_Abbreviation, currency_info[j].Transfer(units));
            flag = true;

        }

    }
    return saver;
}


int menu(std::vector<Currency> currency_info, int& history_index, std::string history[])
{
   
    int selector;
    std::cout << std::endl;
    std::cout << "Please select option from the list below: " << std::endl;
    std::cout << "[1] - Currenсy transfer" << std::endl;
    std::cout << "[2] - View transfer history" << std::endl;
    std::cout << "[3] - Show current rates " << std::endl;
    std::cout << "[4] - Show rate history " << std::endl;
    std::cout << "[5] - EXIT" << std::endl;
    std::cout << std::endl << " >> ";
    std::cin >> selector;
    std::cout << std::endl;

    switch (selector)
    {
    case 1:
        history_index++;
        history[history_index] = transferator(currency_info);
        menu(currency_info, history_index, history);
        break;
    case 2:
        for (int i = 0; i <= history_index; i++)
        {
            std::cout << history[i] << std::endl;
            std::cout << std::endl;

        }
        menu(currency_info, history_index, history);
        break;
    case 3:
        std::cout << std::endl;
        for (int i = 0; i < currency_info.size(); i++)
        {
            std::cout << currency_info[i].name << " - " << currency_info[i].xchange_rate << std::endl;

        }
        menu(currency_info, history_index, history);
        break;
    case 4:
    {
        std::string entered_id;
        std::cout << std::endl << "Enter the currency abbreviation from the list below : " << std::endl;

        for (int i = 0; i < currency_info.size(); i++)
        {
            std::cout << currency_info[i].name << " - " << currency_info[i].cur_Abbreviation << std::endl;
        }

        std::cout << std::endl << " >> ";
        std::cin >> entered_id;
        std::cout << std::endl;
        for (int i = 0; i < currency_info.size(); i++)
        {
            if (currency_info[i].cur_Abbreviation == entered_id)
            {
                for (const auto& pair : currency_info[i].cur_history)
                {
                    std::cout << pair.first << " --- " << pair.second << std::endl;
                }
            }
        }
        menu(currency_info, history_index, history);
        break;
    }
    case 5:
        return 0;

        

    }

    return 0;
}

std::string get_date() {
   
    const std::chrono::time_point now{ std::chrono::system_clock::now() };
    const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(now) };
    std::string date = std::format("{:%F}", ymd);
    return date;
}


void get_history(std::vector<Currency>& currency_info, std::ifstream& in)
{
    json file{ json::parse(in) };
    for (auto& element : file.items())
    {
        for (auto& currency : currency_info)
        {

            if (element.key() == currency.cur_Abbreviation)
            {
                auto history_data = element.value();

                if (history_data.is_object()) {
                    for (auto& history_item : history_data.items()) {

                        currency.cur_history[history_item.key()] = history_item.value().get<double>();
                    }
                }
            }
        }
    }
    
}


void save_history(std::vector<Currency>& currency_info)
{
    std::ofstream out;
    out.open("History.json");
    json file;
    for (int i = 0; i < currency_info.size(); i++)
    {

        for (const auto& pair : currency_info[i].cur_history)
        {
            file[currency_info[i].cur_Abbreviation][pair.first] = pair.second;


        }
        
    }
    out << file.dump(4);
    out.close();
}


void history_auto_saver(std::vector<Currency>& currency_info)
{
    
    std::ifstream in;
    in.open("History.json");
    if (in.is_open())
    {
        get_history(currency_info, in);
        in.close();


        for (auto& currency : currency_info)
        {
            currency.add_history();
        }

        save_history(currency_info);

    }
    else
    {
        for (int i = 0; i < currency_info.size(); i++)
        {
            currency_info[i].add_history();
        }
        save_history(currency_info);
    }
    
}

