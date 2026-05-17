#include "Functions.h"
#include "Currency.h"
#include "HTTPrequest.h"
#include <iostream>
#include <windows.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>



int main()


{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
   
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.nbrb.by/exrates/rates?periodicity=0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

    }

    std::vector<Currency> currency_info = currency_maker(readBuffer);
    history_auto_saver(currency_info);

    

    std::cout << "Greetings my goat!";

    std::string history[10];
    int history_index = -1;
    menu(currency_info, history_index, history);


}
