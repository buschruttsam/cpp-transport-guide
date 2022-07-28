#include <iostream>

#include "input_reader.h"
#include "stat_reader.h"
//#include "geo.h"

int main() {
    TransportCatalogue catalogue;
    std::cout << "Hello, World!" << std::endl;
    dbw_data_input(catalogue);
    dbr_data_input(catalogue);
    return 0;
}
