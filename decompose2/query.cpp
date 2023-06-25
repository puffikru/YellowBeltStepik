#include "query.h"

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