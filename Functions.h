#pragma once
#include <vector>
#include <string>
#include "Currency.h"
#include <chrono>
#include <iostream>

std::string transverator(std::vector<Currency> currency_info);

int menu(std::vector<Currency> currency_info, int& history_index, std::string history[]);

std::string get_date();

void get_history(std::vector<Currency>& currency_info, std::ifstream& in);

void save_history(std::vector<Currency>& currency_info);

void history_auto_saver(std::vector<Currency>& currency_info);