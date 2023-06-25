#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops)
{
    buses_to_stops[bus] = stops;
    for (const string& stop : stops)
    {
        stops_to_buses[stop].push_back(bus);
    }
}


BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const
{
    BusesForStopResponse response;
    if (stops_to_buses.count(stop) == 0)
    {
        response.error = "No stop";
    }
    else
    {
        for (const string& bus : stops_to_buses.at(stop))
        {
            response.success.push_back(bus);
        }
    }
    return response;
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const
{
    StopsForBusResponse response;
    if (buses_to_stops.count(bus) == 0)
    {
        response.error = "No bus";
    }
    else
    {
        for (const string& stop : buses_to_stops.at(bus))
        {
            response.stops.push_back(stop);
        }
        response.buses = stops_to_buses;
        response.bus = bus;
    }
    return response;
}

AllBusesResponse BusManager::GetAllBuses() const
{
    AllBusesResponse response;
    if (buses_to_stops.empty())
    {
        response.error = "No buses";
    }
    else
    {
        response.success = buses_to_stops;
    }
    return response;
}