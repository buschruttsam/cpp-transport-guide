#include <utility>
#include <map>
#include <vector>
#include <set>


class BusStop {
public:

    void setStopCoordinates(const std::pair<double, double> &stop_coordinates){
        stop_coordinates_ = stop_coordinates;
    };

    void SetStopName(const std::string& stop_name) {
        stop_name_ = stop_name;
    }

private:
    std::pair<double, double> stop_coordinates_;
    std::string stop_name_;

};


class BusData {
public:
    enum BusType{
        CHAIN,
        CIRCLE
    };

    void SetBusName(const std::string& bus_name, BusType bus_type = CIRCLE) {
        map_name_type_.first = bus_name;
        map_name_type_.second = bus_type;
    }

    void SetBusStop(const std::string& bus_stop) {
        bus_stops_.push_back(bus_stop);
    }

private:
    std::pair<std::string, BusType> map_name_type_;
    std::vector<std::string> bus_stops_;
};


class TransportCatalogue{

public:
    void SetStop(const BusStop& bus_stop){
        stops_data_.push_back(bus_stop);
    }
    void SetBus(const BusData& bus){
        buses_data_.push_back(bus);
    }

private:
    std::vector<BusStop> stops_data_;
    std::vector<BusData> buses_data_;
};



