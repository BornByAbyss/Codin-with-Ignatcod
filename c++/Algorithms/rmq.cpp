#include <iostream>
#include <cmath>

const int n = 6;
int ST[n][n];

int rmq(int low, int high)
{
    int l = high - low + 1;
    int k = std::__lg(l);

    return (ST[low][k] < ST[high + 1 - (int)pow(2, k)][k]) ? ST[low][k] : ST[high + 1 - (int)pow(2, k)][k];
}

int main(int argc, char const *argv[])
{
    int massive[n] = {3, 1, 2, 6, 5, 1};

    int k = std::__lg(n);

    for (unsigned i = 0; i < n; i++)
        ST[i][0] = massive[i];

    for (unsigned j = 1; j <= k; j++)

        for (unsigned i = 0; i + (int)pow(2, j) - 1 < n; i++)

            if (ST[i][j - 1] < ST[i + (int)pow(2, j - 1)][j - 1])
                ST[i][j] = ST[i][j - 1];
            else
                ST[i][j] = ST[i + (int)pow(2, j - 1)][j - 1];
    return 0;
}
