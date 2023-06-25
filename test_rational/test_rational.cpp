#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

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

class Rational
{
public:
    Rational()
    {
        _numerator = 0;
        _denominator = 1;
    }

    Rational(int numerator, int denominator)
    {
        int nod = gcd(numerator, denominator);
        if (numerator == 0)
        {
            _numerator = numerator;
            _denominator = 1;
        }
        else if (denominator < 0)
        {
            _numerator = numerator / nod * -1;
            _denominator = denominator / nod * -1;
        }
        else
        {
            _numerator = numerator / nod;
            _denominator = denominator / nod;
        }
    }

    int Numerator() const
    {
        return _numerator;
    }

    int Denominator() const
    {
        return _denominator;
    }

private:
    int _numerator;
    int _denominator;
};

void TestDefaultConstructor()
{
    Rational rational;
    AssertEqual(rational.Numerator(), 0);
    AssertEqual(rational.Denominator(), 1);
}

void TestRedaction()
{
    Rational rational = {3, 15};
    AssertEqual(rational.Numerator(), 1);
    AssertEqual(rational.Denominator(), 5);
}

void TestNegative()
{
    Rational rational1 = {-3, 15};
    Rational rational2 = {3, -15};
    Rational rational3 = {-3, -15};
    AssertEqual(rational1.Numerator(), -1);
    AssertEqual(rational1.Denominator(), 5);
    AssertEqual(rational2.Numerator(), -1);
    AssertEqual(rational2.Denominator(), 5);
    AssertEqual(rational3.Numerator(), 1);
    AssertEqual(rational3.Denominator(), 5);
}

void TestPositive()
{
    Rational rational1 = {3, 15};
    Rational rational2 = {-3, -15};
    AssertEqual(rational1.Numerator(), 1);
    AssertEqual(rational1.Denominator(), 5);
    AssertEqual(rational2.Numerator(), 1);
    AssertEqual(rational2.Denominator(), 5);
}

void TestOneNumenator()
{
    Rational rational = {0, 3};
    AssertEqual(rational.Numerator(), 0);
    AssertEqual(rational.Denominator(), 1);
}

int main()
{
    TestRunner runner;
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestRedaction, "TestReduction");
    runner.RunTest(TestNegative, "TestNegative");
    runner.RunTest(TestPositive, "TestPositive");
    runner.RunTest(TestOneNumenator, "TestOneNumenator");
    return 0;
}
