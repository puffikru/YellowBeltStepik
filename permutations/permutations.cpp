#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Permutations(int N)
{
    vector<int> res;
    while (N >= 1)
    {
        res.push_back(N);
        N--;
    }

    do {
        for (auto r : res)
        {
            cout << r << " ";
        }
        cout << endl;
    }
    while (prev_permutation(begin(res), end(res)));
}

int main()
{
    int N;
    cin >> N;
    Permutations(N);
    return 0;
}