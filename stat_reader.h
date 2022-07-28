#include <iostream>
#include <string>
#include <cmath>
//#include "transport_catalogue.h"

void dbr_request_processing (const std::string& input_string, TransportCatalogue& catalogue){
    std::string bus_name = input_string.substr(4);
    if (catalogue.BusStopCount(bus_name) == 0){
        std::cout << input_string << ": not found";
        return;
    }
    std::cout << input_string << ": ";
    std::cout << catalogue.BusStopCount(bus_name) << " stops on route, ";
    std::cout << catalogue.BusUniqStopCount(bus_name) << " unique stops, ";
    std::cout << catalogue.BusRouteLength(bus_name) << " route length";
    std::cout << std::endl;
}

void dbr_data_input (TransportCatalogue& catalogue) {
    int request_count;
    std::string input_string;
    getline (std::cin, input_string);
    request_count = stoi(input_string);
    for (int i = 0; i < request_count; i++){
        getline (std::cin, input_string);

        dbr_request_processing (input_string, catalogue);
    }
}
