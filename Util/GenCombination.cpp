#include <iostream>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////
// Generate Combination 
// For example
// N = 3 , K = 2
// The class will generate :
// {0,1} {0,2} {1,2} 
//////////////////////////////////////////////////////////
class GenCombination
{
  private:
    /** The Set Size */
    int N;
    /** Select K element from the set */
    int K;
    /** The current subset state */
    vector<int> state;
    /** Whether this is the first call of next */
    bool firstCallNext;
  public:

    GenCombination(int n , int k)
    {
      N = n;
      K = k;
      state = vector<int>(K);
      firstCallNext = true;            
    }

    bool hasNext()
    {
      for (int i = 0; i < K; ++i)
        if (state[i] != N - K + i) return true;
      return false;
    }

    vector<int> next()
    {
      if (firstCallNext) {
        firstCallNext = false;
        for (int i = 0; i < K; ++i) state[i] = i;
        return state;
      }

      int i = K - 1;
      while (state[i] == N - K + i) i--;

      state[i]++;
      for (int j = i + 1; j < K; ++j)
        state[j] = state[j-1] + 1;
      return state;
    }
};

/** 
 * Input should be a correct combination to select R object from N object, 
 * object id range from 0 to N - 1
 */
bool next_combination(vector<int> & now, int N)
{
	int R = now.size();
	int bound = N - 1;
	int i = now.size() - 1;
	while (i >= 0 && now[i] == bound)
	{
		i--;
		bound--;
	}
	if (i < 0) return false;
	now[i]++;
	for (int j = i + 1; j < R; ++j)
		now[j] = now[j - 1] + 1;
	return true;
}

class Combination
{
  public:
    vector<vector<long long> > C;
    long long M;
    long long N;

    Combination(int m , int n) {
      M = m, N = n; 
      C = vector<vector<long long > >(M + 1, vector<long long>(N + 1));

      for (int i = 0; i <= M; ++i)
        for (int j = 0; j <= N; ++j)
          C[i][j] = 0;

      C[0][0] = 1;
      for (int i = 1; i <= M; ++i) {
        C[i][0] = 1; 
        for (int j = 1; j <= i && j <= N; ++j) {
          C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
      }
    }

    static long long getBigCom(int m , int n) {
      long long ret = 1;
      for (int i = m; i > m-n; --i)
        ret *= i;
      for (int i = 1; i <= n; ++i)
        ret /= i;
      return ret;
    }

    static long long getBigPer(int m , int n) {
      long long ret = 1;
      for (int i = m; i > m-n; --i)
        ret *= i;
      return ret; 
    }
};


int main()
{
  Combination com(10,10);

  cout << com.C[6][3] << endl;
  return 0;
}




