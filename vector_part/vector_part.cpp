// #include "../test_runner.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
    auto first = find_if(begin(numbers), end(numbers), [](int n)
    {
        return n < 0;
    });
    while (first != begin(numbers))
    {
        --first;
        cout << *first << " ";
    }
}

// int main()
// {
//     PrintVectorPart({6, 1, 8, -5, 4});
//     cout << endl;
//     PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
//     cout << endl;
//     PrintVectorPart({6, 1, 8, 5, 4});
//     cout << endl;
//     return 0;
// }