#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template <typename T> T Sqr(T x);
template <typename T> vector<T> Sqr(const vector<T>& x);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& x);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& x);
template <typename First, typename Second> pair<First, Second> operator*(const pair<First, Second>& lhs, const pair<First, Second>& rhs);

template <typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& lhs, const pair<First, Second>& rhs)
{
    return make_pair(lhs.first * rhs.first, lhs.second * rhs.second);
}

template <typename T>
T Sqr(T x)
{
    return x * x;
}

template <typename T>
vector<T> Sqr(const vector<T>& x)
{
    vector<T> result;
    for (const auto &i : x)
    {
        result.push_back(Sqr(i));
    }
    return result;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& x)
{
    return make_pair(Sqr(x.first), Sqr(x.second));
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& x)
{
    map<Key, Value> result;
    for (auto &[key, value] : x)
    {
        result[key] = Sqr(value);
    }
    return result;
}

int main()
{
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v))
    {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}};
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs))
    {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}