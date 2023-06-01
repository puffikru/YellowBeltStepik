#include <iostream>
#include <vector>


using namespace std;

int Avg(const vector<int>& temperature)
{
    int64_t sum = 0;
    for (const int& t : temperature)
    {
        sum += t;
    }
    return sum / static_cast<int>(temperature.size());
}

int main()
{
    int N;
    vector<int> temp;
    vector<int> result;
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int t;
        cin >> t;
        temp.push_back(t);
    }

    int avg = Avg(temp);
    // cout << "avg: " << avg << endl;
    for (size_t i = 0; i < temp.size(); ++i)
    {
        if (temp[i] > avg)
        {
            result.push_back(i);
        }
    }

    cout << result.size() << endl;
    for (const auto& r : result)
    {
        cout << r << " ";
    }
    
    return 0;
}