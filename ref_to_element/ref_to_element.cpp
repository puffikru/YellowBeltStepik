#include <iostream>
#include <map>
#include <exception>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key x)
{
    if (m.count(x) > 0)
    {
        return m.at(x);
    }
    else
    {
        throw runtime_error("");
    }
}

int main()
{
    try
    {
        map<int, string> m = {{0, "value"}};
        string& item = GetRefStrict(m, 0);
        item = "newvalue";
        cout << m[0] << endl;
    }
    catch(runtime_error& e)
    {
        cout << e.what() << '\n';
    }
    
    return 0;
}