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

class SubSetSum
{
  private:
    vector<int> elements;
    vector<long long> LSums;
    vector<long long> RSums;

    void init()
    {
      /** Initialize */
      int N = elements.size();
      int L = N / 2;
      int R = N - L;
      int LCount = (1LL << L);
      int RCount = (1LL << R);

      for (int i = 1; i < LCount; ++i)
      {
        long long sum = 0;
        for (int k = 0; k < L; ++k)
          if (i & (1 << k))
            sum += elements[k];
        LSums.push_back(sum);
      }

      for (int i = 1; i < RCount; ++i)
      {
        long long sum = 0;
        for (int k = 0; k < R; ++k)
          if (i & (1 << k))
            sum += elements[k + L];
        RSums.push_back(sum);
      }

      sort(LSums.begin(), LSums.end());
      sort(RSums.begin(), RSums.end());
    }


  public:
    SubSetSum(vector<int> & ele)
    {
      elements = ele;
      LSums.clear();
      RSums.clear();
      if (elements.size() > 1) init();
    }

    /** 
     * Given a set of elements, return the count of subset which their sum is bigger or equal than a 
     * given value T
     * @param T thrashold value
     * @return long long : the count
     * @notice that the size of elements will not exceed 40 otherwise the algorithm will run slowly 
     *  also the answer will exceed the long long type's maximum number
     */
    long long getNonEmptySubsetSumBiggerOrEqualThanCount(long long T)
    {
      /** Special cases */
      if (elements.size() == 0) return 0;
      if (elements.size() == 1) return elements[0] >= T ? 1 : 0;

      /** Count the subset just in left or right part */
      long long ans = 0;
      for (int i = 0; i < LSums.size(); ++i)
        if (LSums[i] >= T) ans++;
      for (int i = 0; i < RSums.size(); ++i)
        if (RSums[i] >= T) ans++;

      /** Count the subset which across the left and the right part */
      int l = 0;
      int r = RSums.size() - 1;
      while (l < LSums.size() && r >= 0)
      {
        if (LSums[l] + RSums[r] >= T)
        {
          ans += (LSums.size() - l);
          r--;
        }
        else
          l++;
      }

      return ans;
    }


    /** 
     * Given a set of elements, return the closest subset sum 
     * which their sum is bigger or equal than a given value T
     * @param: T thrashold value
     * @return: The cloest subset sum bigger or equal than T 
     * @notice that the size of elements will not exceed 40 otherwise the algorithm will run slowly 
     */
    long long getNonEmptySubsetSumBiggerOrEqualThanClosestTo(long long T, bool & found)
    {
      /** Special case */
      if (elements.size() == 1)
      {
        if (elements[0] >= T)
        {
          found = true;
          return elements[0];
        }
        else
        {
          found = false;
          return 0;
        }
      }

      long long ans = (1LL << 40);
      for (int i = 0; i < LSums.size(); ++i)
        if (LSums[i] >= T)
          ans = min(ans, LSums[i]);
      for (int i = 0; i < RSums.size(); ++i)
        if (RSums[i] >= T)
          ans = min(ans, RSums[i]);

      int l = 0;
      int r = RSums.size() - 1;
      while (l < LSums.size() && r >= 0)
      {
        if (LSums[l] + RSums[r] >= T)
        {
          ans = min(ans, LSums[l] + RSums[r]);
          r--;
        }
        else
          l++;
      }

      found = ans < (1LL << 40);
      return ans;
    }
};


class FencingGarden
{
  public:
    long long computeWidth(vector<int> segment)
    {
      long long S = 0;
      vector<int> segment2(segment.size());
      for (int i = 0; i < segment.size(); ++i)
      {
        S += segment[i];
        segment2[i] = -segment[i];
      }

      SubSetSum set1(segment);
      SubSetSum set2(segment2);
      long long bestArea = 0;
      long long ans = 0;

      bool found = false;
      long long x1 = set1.getNonEmptySubsetSumBiggerOrEqualThanClosestTo(S / 2, found);
      if (found && x1 * (S - x1) > bestArea)
      {
        bestArea = x1 * (S - x1);
        ans = x1;
      }
      long long nextTest = S / 2;
      if (x1 == S / 2)
        nextTest++;

      long long x2 = -set2.getNonEmptySubsetSumBiggerOrEqualThanClosestTo(-nextTest, found);
      if (found && (x2 * (S - x2) > bestArea || x2 * (S - x2) == bestArea && x2 > ans))
      {
        bestArea = x2 * (S - x2);
        ans = x2;
      }

      long long x3 = -set2.getNonEmptySubsetSumBiggerOrEqualThanClosestTo(-S / 4, found);
      if (found && x3 * (S - 2 * x3) * 2 > bestArea)
      {
        bestArea = x3 * (S - 2 * x3) * 2;
        ans = S - 2 * x3;
      }
      long long test = S / 4;
      if (x3 == S / 4)
        test++;

      long long x4 = set1.getNonEmptySubsetSumBiggerOrEqualThanClosestTo(test, found);
      if (found && (x4 * (S - 2 * x4) * 2 > bestArea || x4 * (S - 2 * x4) * 2 == bestArea && S - 2 * x4 > ans))
      {
        bestArea = x4 * (S - 2 * x4) * 2;
        ans = S - 2 * x4;
      }
      return ans;
    }

    // BEGIN CUT HERE
  public:
    void run_test(int Case) { test_case_3(); if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
  private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { int Arr0[] = {1,1,1,1,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 8LL; verify_case(0, Arg1, computeWidth(Arg0)); }
    void test_case_1() { int Arr0[] = {50,25,25}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 50LL; verify_case(1, Arg1, computeWidth(Arg0)); }
    void test_case_2() { int Arr0[] = {5,7,9,13,21,581,1848,1058,57172,58281,612,528}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 60078LL; verify_case(2, Arg1, computeWidth(Arg0)); }
    void test_case_3() { int Arr0[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 67108864LL; verify_case(3, Arg1, computeWidth(Arg0)); }


    // END CUT HERE

};

// BEGIN CUT HERE
int main()
{
  FencingGarden ___test;
  ___test.run_test(-1);
  return 0;
}
// END CUT HERE
