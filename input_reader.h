#include <iostream>
#include <string>
#include "transport_catalogue.h"

void dbw_request_parsing (const std::string& input_string, TransportCatalogue& catalogue) {
    if (input_string.substr(0, 4) == "Bus "){
        BusData bus_data;
        auto pos = input_string.find_first_of(':');
        std::string bus_name = input_string.substr(4, pos - 4);
        std::string value_string = input_string.substr(pos + 1);
        if (value_string.find_last_of('>') != std::string::npos){
            bus_data.SetBusName(bus_name);
            std::string word_to_push;
            for (char char_value : value_string){
                if (char_value != '>'){
                    word_to_push += char_value;
                } else {
                    bus_data.SetBusStop(word_to_push.substr(1, word_to_push.find_last_not_of(' ')));
                    word_to_push.clear();
                }
            }
            bus_data.SetBusStop(word_to_push.substr(1));
            catalogue.SetBus(bus_data);
        } else {
            bus_data.SetBusName(bus_name, bus_data.CHAIN);
            std::string word_to_push;
            for (char char_value : value_string){
                if (char_value != '-'){
                    word_to_push += char_value;
                } else {
                    bus_data.SetBusStop(word_to_push.substr(1, word_to_push.find_last_not_of(' ')));
                    word_to_push.clear();
                }
            }
            bus_data.SetBusStop(word_to_push.substr(1));
            catalogue.SetBus(bus_data);
        }
    } else if (input_string.substr(0, 4) == "Stop"){
        BusStop bus_stop;
        auto colon_pos = input_string.find(':');
        auto comma_pos = input_string.find_first_of(',');
        bus_stop.SetStopName(input_string.substr(5, colon_pos - 5));
        double double_first = std::stoi(input_string.substr(colon_pos + 2, comma_pos - colon_pos - 2));
        double double_second = std::stoi(input_string.substr(comma_pos + 2));
        bus_stop.setStopCoordinates({double_first, double_second});
        catalogue.SetStop(bus_stop);
    }
}

void dbw_data_input (TransportCatalogue& catalogue) {
    int request_count;
    std::cin >> request_count;
    std::string input_string;
    for (int i = 0; i <= request_count; i++){
        getline (std::cin, input_string);
        dbw_request_parsing (input_string, catalogue);
    }
}