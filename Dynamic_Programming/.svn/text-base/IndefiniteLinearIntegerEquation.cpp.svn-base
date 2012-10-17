#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

/**
 * For those linear indifinite equation, all coefficient is positive integer 
 * return the number of solutions which all x_i is non negative
 * K is non negative
 */
class IndifiniteLinearIntegerEquation
{
  public:
    static const int MOD = 1000000009;
    static int getNumberOfSolution(vector<int> coef, int K)
    {
      int N = coef.size();
      if (N == 0) return 0;
      vector<int> now(K + 1, 0);
      vector<int> next(K + 1, 0);

      for (int s = 0; s <= K; s += coef[0])
        now[s] = 1;

      for (int i = 1; i < N; ++i)
      {
        for (int s = 0; s <= K; ++s)
        {
          next[s] = 0;
          if (s >= coef[i]) 
            next[s] += next[s - coef[i]];
          next[s] += now[s];
          next[s] %= MOD;
        }
        for (int s = 0; s <= K; ++s)
          now[s] = next[s];
      }

      return now[K];
    }
};

int main()
{
  vector<int> a;
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);
  cout << IndifiniteLinearIntegerEquation::getNumberOfSolution(a, 8) << endl;
  return 0;
}
