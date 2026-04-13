#pragma once
#include <string>
#include <vector>
#include "Currency.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

std::vector<Currency> currency_maker(std::string buffer);