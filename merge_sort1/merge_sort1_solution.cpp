#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt begin, RandomIt end)
{
    if ((end - begin) < 2) return;

    vector<typename RandomIt::value_type> result(begin, end);
    auto middle_it = result.begin() + result.size() / 2;
    MergeSort(result.begin(), middle_it);
    MergeSort(middle_it, result.end());
    merge(result.begin(), middle_it, middle_it, result.end(), begin);
}

// int main()
// {
//     vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
//     MergeSort(begin(v), end(v));
//     for (int x : v)
//     {
//         cout << x << " ";
//     }
//     cout << endl;
//     return 0;
// }