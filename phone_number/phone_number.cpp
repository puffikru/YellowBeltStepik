#include "phone_number.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number)
{
    istringstream is(international_number);

    char sign = is.get();
    getline(is, country_code_, '-');
    getline(is, city_code_, '-');
    getline(is, local_number_);

    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
        throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-'. Symbol: " + international_number);
    }
}

string PhoneNumber::GetCountryCode() const
{
    return country_code_;
}

string PhoneNumber::GetCityCode() const
{
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const
{
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

// int main()
// {
//     try
//     {
//         PhoneNumber phNumber = PhoneNumber("+7-1233");
//         cout << phNumber.GetCountryCode() << endl;
//         cout << phNumber.GetCityCode() << endl;
//         cout << phNumber.GetLocalNumber() << endl;
//         cout << phNumber.GetInternationalNumber() << endl;
//     }
//     catch(invalid_argument& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
//     return 0;
// }