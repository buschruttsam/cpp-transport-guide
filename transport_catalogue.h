#include <utility>
#include <map>
#include <vector>
#include <set>
#include "geo.h"


class BusStop {
public:

    void setStopCoordinates(const Coordinates &stop_coordinates){
        stop_coordinates_ = stop_coordinates;
    };

    void SetStopName(const std::string& stop_name) {
        stop_name_ = stop_name;
    }

    std::string GetStopName() {
        return stop_name_;
    }

    Coordinates GetCoordinates (){
        return stop_coordinates_;
    }

private:
    Coordinates stop_coordinates_;
    std::string stop_name_;

};


class BusData {
public:
    enum BusType{
        CHAIN,
        CIRCLE
    };

    [[nodiscard]] std::string GetBusName() const {
        return map_name_type_.first;
    }

    [[nodiscard]] BusType GetBusType() const {
        return map_name_type_.second;
    }

    [[nodiscard]] size_t GetStopsCount() const {
        return bus_stops_.size();
    }

    [[nodiscard]] size_t GetUniqStopsCount() const {
        std::set<std::string> buffer;
        for (const std::string& stop : bus_stops_){
            buffer.insert(stop);
        }
        return buffer.size();
    }

    [[nodiscard]] double GetRouteLength(const std::vector<BusStop>& stops_data_) const {
        Coordinates c_origin{};
        Coordinates c_destination{};
        double route_length = 0.0;
        for (int i = 1; i < bus_stops_.size(); i++){
            for (BusStop stop : stops_data_){
                if (stop.GetStopName() == bus_stops_[i]){
                    c_destination = stop.GetCoordinates();
                }
                if (stop.GetStopName() == bus_stops_[i-1]){
                    c_origin = stop.GetCoordinates();
                }
            }
            route_length += ComputeDistance(c_origin, c_destination);
        }
        if (map_name_type_.second == CHAIN){
            route_length += route_length;
        }
        return route_length;
    }

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

    size_t BusStopCount(const std::string &bus_name){
        for (const BusData& bus : buses_data_){
            if (bus.GetBusName() == bus_name){
                if (bus.GetBusType() == BusData::CHAIN){
                    return bus.GetStopsCount() + (bus.GetStopsCount() - 1);
                } else {
                    return bus.GetStopsCount();
                }

            }
        }
        return 0;
    };

    size_t BusUniqStopCount(const std::string &bus_name){
        std::set<BusData> buffer;
        for (const BusData& bus : buses_data_){
            if (bus.GetBusName() == bus_name){
                return bus.GetUniqStopsCount();
            }
        }
        return 0;
    };

    double BusRouteLength(const std::string &bus_name){
        for (const BusData& bus : buses_data_){
            if (bus.GetBusName() == bus_name){
                return bus.GetRouteLength(stops_data_);
            }
        }
        return 1.0;
    };

private:
    std::vector<BusStop> stops_data_;
    std::vector<BusData> buses_data_;
};



