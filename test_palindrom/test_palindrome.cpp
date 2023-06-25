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

bool IsPalindrom(const string &str)
{
    for (int i = 0; i < str.size() / 2; ++i) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

void TestEmpty()
{
    Assert(IsPalindrom(""), "empty String");
}

void TestOneSymbol()
{
    Assert(IsPalindrom("a"), "Test one symbol");
}

void TestCount()
{
    Assert(!IsPalindrom("madam "), "string with space");
    Assert(IsPalindrom(" madam "), "string with space");
}

void TestPolindrom()
{
    Assert(!IsPalindrom("amadam"), "first symbol ignore");
    Assert(!IsPalindrom("madama"), "last symbol ignore");
    Assert(IsPalindrom("amaama"), "");
    Assert(IsPalindrom("ama ama"), "");
    Assert(IsPalindrom("ama-ama"), "");
    Assert(!IsPalindrom("amfama"), "");
    Assert(!IsPalindrom("amaama "), "");
    Assert(!IsPalindrom("ma dam"), "one space");
    Assert(IsPalindrom("ma d am"), "two spaces");
    Assert(IsPalindrom("aaaaaa"), "same char");
    Assert(IsPalindrom("aaadaaa"), "");
    Assert(!IsPalindrom("aaadaa"), "");
    Assert(!IsPalindrom("daaada"), "");
    Assert(IsPalindrom("daaad"), "");
    Assert(!IsPalindrom("  a "), "");
    Assert(IsPalindrom("   "), "");
    Assert(IsPalindrom("abba"), "");
    Assert(IsPalindrom("abxba"), "");
    Assert(!IsPalindrom("XabbaY"), "");
    Assert(IsPalindrom("  abba  "), "");
    Assert(IsPalindrom(" a b b a "), "");
    Assert(!IsPalindrom("xabba"), "");
    Assert(!IsPalindrom("abbax"), "");
    Assert(!IsPalindrom("a b ba"), "");
}

int main()
{
    TestRunner runner;
    runner.RunTest(TestEmpty, "TestEmpty");
    runner.RunTest(TestOneSymbol, "TestOneSymbol");
    runner.RunTest(TestCount, "TestCount");
    runner.RunTest(TestPolindrom, "TestPolindrom");
    return 0;
}
