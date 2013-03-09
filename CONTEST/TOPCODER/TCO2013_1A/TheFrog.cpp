//BEGIN CUT HERE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <string.h>
#include <sstream>
using namespace std;
//END CUT HERE

class TheFrog
{
public:
    
    bool check(int s, int m, vector<int>& L, vector<int>& R)
    {
        int N = (int) L.size();
        for (int i = 0; i < N; ++i)
        {
            int x1, x2;
            if (L[i] * m % s == 0) x1 = L[i] * m / s + 1; else x1 = L[i] * m / s + 1;
            if (R[i] * m % s == 0) x2 = R[i] * m / s - 1; else x2 = R[i] * m / s;
            if (x2 >= x1) return false;
        }
        return true;
    }
    
    double getMinimum(int D, vector <int> L, vector <int> R)
    {
        double ans = D;
        int maxInterval = 0;
        int N = (int) L.size();
        for (int i = 0; i < N; ++i)
            maxInterval = max(maxInterval, R[i] - L[i]);
        
        vector<int> xs;
        for (int i = 0; i < N; ++i) xs.push_back(L[i]);
        for (int i = 0; i < N; ++i) xs.push_back(R[i]);
        sort(xs.begin(), xs.end());
        xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
        
        for (int i = 0; i < xs.size(); ++i)
        {
            int x = xs[i];
            if (x == 0) continue;
            for (int s = 1; s * maxInterval <= x; ++s)
            {
                int curStepSon = x;
                int curStepMom = s;
                if (check(curStepSon, curStepMom, L, R))
                    ans = min(ans, 1.0 * x / s);
            }
        }
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 16; int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 7.0; verify_case(0, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 25; int Arr1[] = {11, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {21, 7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 10.5; verify_case(1, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 100; int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 100.0; verify_case(2, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 100; int Arr1[] = {0, 50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {50, 100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 50.0; verify_case(3, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 30000; int Arr1[] = {17, 25281, 5775, 2825, 14040}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {55, 26000, 5791, 3150, 14092}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 787.8787878787879; verify_case(4, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    TheFrog ___test;
    ___test.run_test(-1);
}
// END CUT HERE
