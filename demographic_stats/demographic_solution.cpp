// #include "structs.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintStats(vector<Person> persons)
{
    cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;

    auto female = partition(begin(persons), end(persons), [](Person p){ return p.gender == Gender::FEMALE; });
    cout << "Median age for females = " << ComputeMedianAge(begin(persons), female) << endl;
    cout << "Median age for males = " << ComputeMedianAge(female, end(persons)) << endl;

    auto employed_females = partition(begin(persons), end(persons), [](Person p) { return p.gender == Gender::FEMALE && p.is_employed == true; });
    cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), employed_females) << endl;

    auto unemployed_females = partition(begin(persons), end(persons), [](Person p) { return p.gender == Gender::FEMALE && p.is_employed == false; });
    cout << "Median age for unemployed females = " << ComputeMedianAge(begin(persons), unemployed_females) << endl;

    auto employed_males = partition(begin(persons), end(persons), [](Person p) { return p.gender == Gender::MALE && p.is_employed == true; });
    cout << "Median age for employed males = " << ComputeMedianAge(begin(persons), employed_males) << endl;
    auto unemployed_males = partition(begin(persons), end(persons), [](Person p) { return p.gender == Gender::MALE && p.is_employed == false; });
    cout << "Median age for unemployed males = " << ComputeMedianAge(begin(persons), unemployed_males) << endl;
}

// int main()
// {
//     vector<Person> persons = {
//         {31, Gender::MALE, false},
//         {40, Gender::FEMALE, true},
//         {24, Gender::MALE, true},
//         {20, Gender::FEMALE, true},
//         {80, Gender::FEMALE, false},
//         {78, Gender::MALE, false},
//         {10, Gender::FEMALE, false},
//         {55, Gender::MALE, true},
//     };
//     PrintStats(persons);
//     return 0;
// }