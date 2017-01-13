#include <iostream>
#include <ctime>

using namespace std;

int HorVerRectangles(int m, int n)
{
    return (m * (m + 1) * n * (n + 1)) / 4;
}

uint64_t DiagonalRectiangles(int m, int n)
{
    int temp;
    if (m < n)
    {
        temp = m;
        m = n;
        n = temp;
    }
    m = (m < n) ? n : m;
    return n * ((2 * m - n) * (4 * n * n - 1) - 3) / 6;
}

int main()
{
    time_t t = clock();
    int numberOfRectangles = 0;
    for (int m = 1; m <= 47; m++)
    {
        for (int n = 1; n <= 43; n++)
        {
            numberOfRectangles += HorVerRectangles(m, n);
            numberOfRectangles += DiagonalRectiangles(m, n);
        }
    }
    
    cout << numberOfRectangles << endl;
    cout << double(clock() - t) / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}