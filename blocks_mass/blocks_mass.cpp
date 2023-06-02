#include <iostream>
#include <limits>

using namespace std;

int main()
{
    uint32_t N;
    uint16_t R;
    uint64_t W, H, D;

    uint64_t square = 0;
    uint64_t mass = 0;

    cin >> N >> R;

    for (size_t i = 0; i < N; ++i)
    {
        cin >> W >> H >> D;
        square = W * H * D;
        mass += (square * R);
    }

    cout << mass << endl;
    
    
    return 0;
}