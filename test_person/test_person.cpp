#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
    os << "{";
    bool first = true;
    for (const auto &kv : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {})
{
    if (t != u)
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty())
        {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint)
{
    AssertEqual(b, true, hint);
}

class TestRunner
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name)
    {
        try
        {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception &e)
        {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...)
        {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Person
{
public:
    void ChangeFirstName(int year, const string &first_name)
    {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string &last_name)
    {
        last_names[year] = last_name;
    }
    string GetFullName(int year)
    {
        string first_name;
        string last_name;
        string full_name;

        for (const auto &[years, names] : first_names)
        {
            if (years <= year)
            {
                first_name = names;
            }
        }
        for (const auto &[years, names] : last_names)
        {
            if (years <= year)
            {
                last_name = names;
            }
        }

        if (first_name.size() == 0 && last_name.size() == 0)
        {
            full_name = "Incognito";
        }
        else if (first_name.size() == 0 && last_name.size() > 0)
        {
            full_name = last_name + " with unknown first name";
        }
        else if (first_name.size() > 0 && last_name.size() == 0)
        {
            full_name = first_name + " with unknown last name";
        }
        else
        {
            full_name = first_name + " " + last_name;
        }

        return full_name;
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;
};

void TestEmptyPerson()
{
    Person person;
    person.ChangeFirstName(1988, "Igor");
    person.ChangeLastName(1990, "Bulakh");
    AssertEqual(person.GetFullName(1987), "Incognito");
}

void TestFirstName()
{
    Person person;
    person.ChangeFirstName(1988, "Igor");
    AssertEqual(person.GetFullName(1988), "Igor with unknown last name");
    person.ChangeFirstName(1987, "Ivan");
    AssertEqual(person.GetFullName(1987), "Ivan with unknown last name");
    AssertEqual(person.GetFullName(1988), "Igor with unknown last name");
    person.ChangeFirstName(1989, "Alex");
    AssertEqual(person.GetFullName(1988), "Igor with unknown last name");
    AssertEqual(person.GetFullName(1998), "Alex with unknown last name");
    AssertEqual(person.GetFullName(1986), "Incognito");
}

void TestLastName()
{
    Person person;
    person.ChangeLastName(1990, "Ivanov");
    person.ChangeLastName(1991, "Sidorov");
    person.ChangeLastName(1992, "Ivanov");
    person.ChangeLastName(1995, "Stoyanov");
    AssertEqual(person.GetFullName(1989), "Incognito");
    AssertEqual(person.GetFullName(1990), "Ivanov with unknown first name");
    AssertEqual(person.GetFullName(1994), "Ivanov with unknown first name");
    person.ChangeLastName(1987, "Markov");
    AssertEqual(person.GetFullName(1989), "Markov with unknown first name");
    person.ChangeLastName(1999, "Kuznetsov");
    person.ChangeLastName(1994, "Ivanov");
    AssertEqual(person.GetFullName(2000), "Kuznetsov with unknown first name");
    AssertEqual(person.GetFullName(1994), "Ivanov with unknown first name");

}

void TestFullName()
{
    Person person;
    person.ChangeFirstName(1980, "Igor");
    person.ChangeFirstName(1982, "Ivan");
    AssertEqual(person.GetFullName(1982), "Ivan with unknown last name");
    person.ChangeLastName(1982, "Ivanov");
    person.ChangeFirstName(1983, "Gosha");
    person.ChangeLastName(1985, "Stepanov");
    AssertEqual(person.GetFullName(1970), "Incognito");
    AssertEqual(person.GetFullName(1981), "Igor with unknown last name");
    AssertEqual(person.GetFullName(1982), "Ivan Ivanov");
    AssertEqual(person.GetFullName(1983), "Gosha Ivanov");
    AssertEqual(person.GetFullName(1985), "Gosha Stepanov");
    person.ChangeFirstName(1990, "Michael");
    AssertEqual(person.GetFullName(1990), "Michael Stepanov");
    person.ChangeLastName(1986, "Novikov");
    AssertEqual(person.GetFullName(1990), "Michael Novikov");
}

int main()
{
    TestRunner runner;
    runner.RunTest(TestEmptyPerson, "TestEmptyPerson");
    runner.RunTest(TestFirstName, "TestFirstName");
    runner.RunTest(TestLastName, "TestLastName");
    runner.RunTest(TestFullName, "TestFullName");
    return 0;
}
