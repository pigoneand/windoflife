#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;

class TheCitiesAndRoadsDivTwo
{
  public:
    map<vector<int>, int> memo;

    /** Get the all connected components' size as input,
     * return the number of different ways to make the spanning tree based on 
     * the given components information. 
     * @components: each components' size in sorted order 
     * @tag: for a graph with n nodes and no edge, the spanning tree count = n ^ (n - 2)
     */
    int countSpanningTree(vector<int> & components)
    {
      if (memo.find(components) != memo.end())
        return memo[components];

      if (components.size() == 1)
        return 1;

      vector<int> left(1, components[0]);
      vector<int> right(1, components[1]);

      int ans = 0;
      int remainToAssign = components.size() - 2;
      int differentAssigns = 1 << remainToAssign;
      for (int i = 0; i < differentAssigns; ++i)
      {
        vector<int> leftPart = left;
        vector<int> rightPart = right;
        int leftSize = left[0];
        int rightSize = right[0];

        for (int k = 0; k < remainToAssign; ++k)
          if (i & (1 << k))
          {
            leftPart.push_back(components[2 + k]);
            leftSize += components[2 + k];
          }
          else
            rightPart.push_back(components[2 + k]);

        ans += leftSize * rightSize * countSpanningTree(leftPart) * countSpanningTree(rightPart);
      }

      memo[components] = ans;
      return ans;
    }


    int find(vector <string> map)
    {
      vector<int> conns;
      int N = map.size();
      for (int i = 0; i < N; ++i)
        map[i][i] = 'Y';
      for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
          for (int j = 0; j < N; ++j)
            if (map[i][k] == 'Y' && map[k][j] == 'Y')
              map[i][j] = 'Y';

      vector<bool> added(N, false);
      for (int i = 0; i < N; ++i)
        if (!added[i])
        {
          int count = 1;
          added[i] = true;
          for (int j = 0; j < N; ++j)
            if (map[i][j] == 'Y' && !added[j])
            {
              added[j] = true;
              count++;
            }
          conns.push_back(count);
        }

      sort(conns.begin(), conns.end());

      return countSpanningTree(conns);
    }

    /** BEGIN CUT HERE */

  public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
  private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { string Arr0[] = {"NN",
      "NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, find(Arg0)); }
    void test_case_1() { string Arr0[] = {"NY",
      "YN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, find(Arg0)); }
    void test_case_2() { string Arr0[] = {"NNY",
      "NNN",
      "YNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, find(Arg0)); }
    void test_case_3() { string Arr0[] = {"NYNN",
      "YNNN",
      "NNNY",
      "NNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(3, Arg1, find(Arg0)); }

    /** END CUT HERE */

};

/** BEGIN CUT HERE */
int main()
{
  TheCitiesAndRoadsDivTwo ___test;
  ___test.run_test(-1);
  return 0;
}
/** END CUT HERE */
