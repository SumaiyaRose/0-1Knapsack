#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

#ifdef _WIN32
  #define CLEAR "cls"
#else
  #define CLEAR "clear"
#endif


void clearScreen()
{
    system(CLEAR);
}

void printDPMatrix(const vector<vector<int>>& dp, int n, int W)
{
    clearScreen();
    cout << "DP Matrix:\n";

    cout << "    |";
    for (int w = 0; w <= W; ++w)
    {
        cout << std::setw(4) << w;
    }
    cout << "\n";

    for (int i = 0; i <= n; ++i)
    {
        cout << std::setw(2) << i << " | ";
        for (int j = 0; j <= W; ++j)
        {
            cout << std::setw(4) << dp[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

int knapsack(int W, const vector<int>& weights, const vector<int>& values, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int w = 1; w <= W; ++w)
        {
            clearScreen();
            if (weights[i - 1] <= w)
            {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
            printDPMatrix(dp, n, W);
            cout << "Computing dp[" << i << "][" << w << "]\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    return dp[n][W];
}

int main()
{
    int W;
    int n;

    cout << "Enter the maximum weight of the knapsack: ";
    cin >> W;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> weights(n), values(n);

    for (int i = 0; i < n; ++i)
    {
        cout << "Enter weight for item " << i + 1 << ": ";
        cin >> weights[i];
        cout << "Enter value for item " << i + 1 << ": ";
        cin >> values[i];
    }

    int maxValue = knapsack(W, weights, values, n);
    cout << "Maximum value in Knapsack = " << maxValue << endl;

    return 0;
}
