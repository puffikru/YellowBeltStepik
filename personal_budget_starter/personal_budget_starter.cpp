#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;


class Date
{
public:
    Date() {};

    Date(int new_year, int new_month, int new_day)
    {
        if (new_month < 1 || new_month > 12)
        {
            throw invalid_argument("Month value is invalid: " + to_string(new_month));
        }
        else if (new_day < 1 || new_day > 31)
        {
            throw invalid_argument("Day value is invalid: " + to_string(new_day));
        }
        year_ = new_year;
        month_ = new_month;
        day_ = new_day;
    }

    int GetYear() const
    {
        return year_;
    }

    int GetMonth() const
    {
        return month_;
    }

    int GetDay() const
    {
        return day_;
    }

    time_t AsTimestamp() const
    {
        std::tm t;
        t.tm_sec   = 0;
        t.tm_min   = 0;
        t.tm_hour  = 0;
        t.tm_mday  = day_;
        t.tm_mon   = month_ - 1;
        t.tm_year  = year_ - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }

private:
    int year_ = 1;
    int month_ = 1;
    int day_ = 1;
};

istream &operator>>(istream &is, Date &date)
{
    int year, month, day;
    char op1, op2;

    if (is)
    {
        string query;
        is >> query;
        stringstream ss(query);
        if (ss.peek() == '+') ss.ignore(1);
        ss >> year >> op1;
        if (ss.peek() == '+') ss.ignore(1);
        ss >> month >> op2;
        if (ss.peek() == '+') ss.ignore(1);
        ss >> day;

        if (ss && op1 == '-' && op2 == '-' && ss.peek() == -1)
        {
            date = Date(year, month, day);
        }
        else
        {
            throw invalid_argument("Wrong date format: " + query);
        }
    }

    return is;
}

int ComputeDaysDiff(const Date& date_to, const Date& date_from)
{
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static const int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}


class Budget
{
public:
    Budget();

private:

};


int main()
{
    string q, from, to;
    float value;
    cin >> q >> from >> to;

    if (q == "ComputeIncome")
    {

    }
    else if (q == "Earn")
    {
        cin >> value;
    }

    return 0;
}