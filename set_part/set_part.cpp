#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
    vector<T> result;
    auto first_greater = find_if(begin(elements), end(elements), [border](T element){
        return element > border;
    });
    if (first_greater != end(elements))
    {
        for (auto it = first_greater; it != end(elements); ++it)
        {
            result.push_back(*it);
        }
    }
    return result;
}

// int main()
// {
//     for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
//         cout << x << " ";
//     }
//     cout << endl;
    
//     string to_find = "Python";
//     cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
//     return 0;
// }