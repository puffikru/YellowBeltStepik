#include <iostream>
#include <map>
#include <set>
#include <string>
#include <exception>
#include <sstream>

using namespace std;

using Sinonims = map<string, set<string>>;

void AddSinonims(Sinonims& sinonims, const string& first_word, const string& second_word)
{
    sinonims[first_word].insert(second_word);
    sinonims[second_word].insert(first_word);
}


size_t GetSinonimCount(Sinonims& sinonims, const string& first_word)
{
    return sinonims[first_word].size();
}


bool AreSinonims(Sinonims& sinonims, const string& first_word, const string& second_word)
{
    return (sinonims.count(first_word) > 0 && sinonims[first_word].count(second_word) > 0) || 
    (sinonims.count(second_word) > 0 && sinonims[second_word].count(first_word) > 0);
}

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


void Assert(bool b, const string& hint)
{
    AssertEqual(b, true, hint);
}


void TestAddSinonims()
{
    {
        Sinonims empty;
        AddSinonims(empty, "a", "b");
        const Sinonims expected = {
            {"a", {"b"}},
            {"b", {"a"}}
        };
        AssertEqual(empty, expected, "Add to empty");
    }
    {
        Sinonims sinonims = {
            {"a", {"b"}},
            {"b", {"a", "c"}},
            {"c", {"b"}}
        };
        AddSinonims(sinonims, "a", "c");
        const Sinonims expected = {
            {"a", {"b", "c"}},
            {"b", {"a", "c"}},
            {"c", {"b", "a"}}
        };
        AssertEqual(sinonims, expected, "Add to non-empty");
    }
}


void TestCount()
{
    {
        Sinonims empty;
        AssertEqual(GetSinonimCount(empty, "a"), 0u, "count for empty");
    }
    {
        Sinonims sinonims = {
            {"a", {"b", "c"}},
            {"b", {"a"}},
            {"c", {"a"}}
        };
        AssertEqual(GetSinonimCount(sinonims, "a"), 2u, "count for a");
        AssertEqual(GetSinonimCount(sinonims, "b"), 1u, "count for b");
        AssertEqual(GetSinonimCount(sinonims, "z"), 0u, "count for z");
    }
}


void TestAreSinonims()
{
    {
        Sinonims empty;
        Assert(!AreSinonims(empty, "a", "b"), "empty a b");
        Assert(!AreSinonims(empty, "b", "a"), "empty b a");
    }
    {
        Sinonims sinonims = {
            {"a", {"b", "c"}},
            {"b", {"a"}},
            {"c", {"a"}}  
        };
        Assert(AreSinonims(sinonims, "a", "b"), "a b");
        Assert(AreSinonims(sinonims, "b", "a"), "b a");
        Assert(AreSinonims(sinonims, "a", "c"), "a c");
        Assert(AreSinonims(sinonims, "c", "a"), "c a");
        Assert(!AreSinonims(sinonims, "b", "c"), "b c");
        Assert(!AreSinonims(sinonims, "c", "b"), "c b");
    }
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

void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestAreSinonims, "TestAreSinonims");
    tr.RunTest(TestAddSinonims, "TestAddSinonims");
    tr.RunTest(TestCount, "TestCount");
}

int main()
{
    TestAll();

    int Q;
    cin >> Q;

    map<string, set<string>> sinonims;

    for (int i = 0; i < Q; ++i)
    {
        string command;
        cin >> command;

        if (command == "ADD")
        {
            string word1, word2;
            cin >> word1 >> word2;
            AddSinonims(sinonims, word1, word2);
        }
        else if (command == "COUNT")
        {
            string word;
            cin >> word;
            cout << GetSinonimCount(sinonims, word) << endl;
        }
        else if (command == "CHECK")
        {
            string word1, word2;
            cin >> word1 >> word2;

            if (AreSinonims(sinonims, word1, word2))
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}