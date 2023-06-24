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

int GetDistinctRealRootCount(double a, double b, double c)
{
    // ax2 + bx + c = 0
    // ax2 + c = 0    2x2 + 5 = 0   2x2 = -5    x2 = -5 / 2   x = sqrt(-2.5)
    if (a == 0 || b == 0)
    {
        return 1;
    }
    else if (c == 0)
    {
        return 2;
    }
    else
    {
        int d = b * b - 4 * a * c;
        if (d > 0)
        {
            return 2;
        } 
        else if (d == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void TestRootCount()
{
    AssertEqual(GetDistinctRealRootCount(-3, -2, 1), 2);
}

void TestAIsZero()
{
    AssertEqual(GetDistinctRealRootCount(0, 2, 2), 1);
}

void TestBIsZero()
{
    AssertEqual(GetDistinctRealRootCount(2, 0, 5), 0);
}

void TestCIsZero()
{
    AssertEqual(GetDistinctRealRootCount(2, 2, 0), 2);
}

void TestDBelowZero()
{
    AssertEqual(GetDistinctRealRootCount(-3, 2, -1), 0);
}

void TestDIsZero()
{
    AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1);
}

void TestDAboveZero()
{
    AssertEqual(GetDistinctRealRootCount(3, 5, 2), 2);
}

void TestABIsZero()
{
    AssertEqual(GetDistinctRealRootCount(0, 0, 2), 0);
}


int main()
{
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestRootCount, "TestRootCount");
    runner.RunTest(TestDBelowZero, "TestDBelowZero");
    runner.RunTest(TestAIsZero, "TestAIsZero");
    runner.RunTest(TestBIsZero, "TestBIsZero");
    runner.RunTest(TestCIsZero, "TestCIsZero");
    runner.RunTest(TestDIsZero, "TestDIsZero");
    runner.RunTest(TestDAboveZero, "TestDAboveZero");
    runner.RunTest(TestABIsZero, "TestABIsZero");
    return 0;
}
