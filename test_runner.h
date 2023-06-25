#include <iostream>
#include <map>
#include <set>
#include <string>
#include <exception>
#include <sstream>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const set<T>& s)
{
    os << "{";
    bool first = true;
    for (const auto& k : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << k;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m)
{
    os << "{";
    bool first = true;
    for (const auto& [key, value] : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << key << ": " << value;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint)
{
    if (t != u)
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;
        throw runtime_error(os.str());
    }
}

inline void Assert(bool b, const string& hint)
{
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name)
    {
        try
        {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch(runtime_error& e)
        {
            ++fail_count;
            cerr << test_name << " failed: " << e.what() << endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            cerr << fail_count << " tests failed. Terminate.";
            exit(1);
        }
    }

private:
    int fail_count = 0;
};