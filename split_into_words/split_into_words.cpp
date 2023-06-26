#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s)
{
    vector<string> result;
    auto space = find(begin(s), end(s), ' ');
    auto start = begin(s);
    if (space != end(s))
    {
        while (space != end(s))
        {
            result.push_back(string(start, space));
            start = space + 1;
            space = find(start, end(s), ' ');
            if (space == end(s))
            {
                result.push_back(string(start, space));
            }
        }
    }
    else
    {
        result.push_back(s);
    }
    
    return result;
}

// int main()
// {
//     string s = "C Cpp Java Python";

//     vector<string> words = SplitIntoWords(s);
//     cout << words.size() << " ";
//     for (auto it = begin(words); it != end(words); ++it) {
//         if (it != begin(words)) {
//         cout << "/";
//         }
//         cout << *it;
//     }
//     cout << endl;

//     return 0;
// }