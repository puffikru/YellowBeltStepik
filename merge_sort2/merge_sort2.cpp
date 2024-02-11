#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt begin, RandomIt end)
{
    if ((end - begin) < 2)
        return;

    vector<typename RandomIt::value_type> result(begin, end);
    auto first_part = result.begin() + result.size() / 3;
    auto second_part = first_part + result.size() / 3;

    MergeSort(result.begin(), first_part);
    MergeSort(first_part, second_part);
    MergeSort(second_part, second_part + result.size() / 3);

    vector<typename RandomIt::value_type> middle;
    merge(result.begin(), first_part, first_part, second_part, back_inserter(middle));
    merge(middle.begin(), middle.end(), second_part, result.end(), begin);
}

// int main()
// {
//     vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
//     MergeSort(begin(v), end(v));
//     for (int x : v)
//     {
//         cout << x << " ";
//     }
//     cout << endl;
//     return 0;
// }