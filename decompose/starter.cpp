#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query
{
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator>>(istream &is, Query &q)
{
    string query;
    is >> query;
    q.stops.clear();
    if (query == "NEW_BUS")
    {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        for (int i = 0; i < stop_count; ++i)
        {
            cin >> q.stop;
            q.stops.push_back(q.stop);
        }
    }
    else if (query == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (query == "STOPS_FOR_BUS")
    {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (query == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse
{
    string error;
    vector<string> success;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{
    if (r.error != "")
    {
        os << r.error;
    }
    else
    {
        for (const string& s : r.success)
        {
            os << s << " ";
        }
    }
    return os;
}

struct StopsForBusResponse
{
    string error;
    string bus;
    vector<string> stops;
    map<string, vector<string>> buses;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{
    if (r.error != "")
    {
        os << r.error;
    }
    else
    {
        for (const string& s : r.stops)
        {
            os << "Stop " << s << ": ";
            if (r.buses.at(s).size() == 1)
            {
                os << "no interchange";
            }
            else
            {
                for (const auto& bus : r.buses.at(s))
                {
                    if (r.bus != bus)
                    {
                        os << bus << " ";
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse
{
    string error;
    map<string, vector<string>> success;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{
    if (r.error != "")
    {
        os << r.error;
    }
    else
    {
        for (const auto& [key, value] : r.success)
        {
            os << "Bus " << key << ": ";
            for (const string& v : value)
            {
                os << v << " ";
            }
            os << endl;
        }
    }
    return os;
}

class BusManager
{
public:
    void AddBus(const string &bus, const vector<string> &stops)
    {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops)
        {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const
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

    StopsForBusResponse GetStopsForBus(const string &bus) const
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

    AllBusesResponse GetAllBuses() const
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

private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main()
{
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i)
    {
        cin >> q;
        switch (q.type)
        {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
