#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

struct BusesForStopResponse
{
    string error;
    vector<string> success;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);

struct StopsForBusResponse
{
    string error;
    string bus;
    vector<string> stops;
    map<string, vector<string>> buses;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r);

struct AllBusesResponse
{
    string error;
    map<string, vector<string>> success;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r);