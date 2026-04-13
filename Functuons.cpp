#pragma once
#include "Functions.h"
#include "Currency.h"
#include "HTTPrequest.h"
#include <iostream>
#include <format>


std::string transferator(std::vector<Currency> info)
{
    bool flag;
    std::string saver;
    std::string entered_id;
    double units;

    std::cout << "Enter the currency abbreviation from the list below: " << std::endl;

    for (int i = 0; i < info.size(); i++)
    {
        std::cout << info[i].name << " - " << info[i].cur_Abbreviation << std::endl;
    }
    std::cout << std::endl << " >> ";
    std::cin >> entered_id;

    for (int j = 0; j < info.size(); j++)

    {
        if (entered_id == info[j].cur_Abbreviation)
        {
            std::cout << "Current rate: " << info[j].xchange_rate << std::endl;
            std::cout << "Please enter amount to transfer: " << std::endl;
            std::cout << std::endl << " >> ";
            std::cin >> units;
            std::cout << "Success!" << std::endl << "Result: " << info[j].Transfer(units) << "byn" << std::endl;
            saver = std::format("{} {} > {} byn", units, info[j].cur_Abbreviation, info[j].Transfer(units));
            flag = true;

        }

    }
    return saver;
}


int menu(std::string buffer, int index)
{
    std::string history[10];
    int history_index = -1;
    int selector;
    std::cout << "Please select option from the list below: " << std::endl;
    std::cout << "[1] - Currenсy transfer" << std::endl;
    std::cout << "[2] - View transfer history" << std::endl;
    std::cout << "[3] - Show current rates " << std::endl;
    std::cout << "[4] - EXIT" << std::endl;
    std::cout << std::endl << " >> ";
    std::cin >> selector;
    std::cout << std::endl;

    switch (selector)
    {
    case 1:
        index++;
        history[index] = transferator(currency_maker(buffer));
        menu(buffer, index);

    case 2:
        for (int i = 0; i <= history_index; i++)
        {
            std::cout << history[i] << std::endl;

        }
        menu(buffer, index);

    case 3:
        std::cout << std::endl;
        for (int i = 0; i < currency_maker(buffer).size(); i++)
        {
            std::cout << currency_maker(buffer)[i].name << " - " << currency_maker(buffer)[i].xchange_rate << std::endl;

        }
        menu(buffer, index);

    case 4:
        return 0;

    }

    return index;
}
