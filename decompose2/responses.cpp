#include "responses.h"

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