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

const long long moder = 1000000007;
long long C[1000001];

long long powerMod(long long a, long long b, long long m)
{
    long long ret = 1;
    long long cur = a;
    while (b > 0)
    {
        if (b & 1) ret = ret * cur % m;
        cur = cur * cur % m;
        b = b >> 1;
    }
    return ret;
}

long long getReverse(long long a, long long p)
{
    return powerMod(a, p - 2, p);
}

long long getWays(long long m, long long d)
{
    if ((m - d) % 2 != 0) return 0;
    long long x = (m - d) / 2;
    if (x > m) return 0;
    if (x < 0) return 0;
    return C[x];
}

class WolfPack
{
public:
    int calc(vector <int> x, vector <int> y, int m)
    {
        C[0] = 1;
        for (int k = 1; k <= m; ++k)
            C[k] = C[k - 1] * (m - k + 1) % moder * getReverse(k, moder) % moder;
        
        int N = (int) x.size();
        for (int i = 0; i < N; ++i)
        {
            x[i] = x[i] + y[i];
            y[i] = x[i] - y[i] - y[i];
        }
        
        long long ansX = 0;
        for (long long tx = x[0] - m; tx <= x[0] + m; tx += 2)
        {
            long long nowans = 1;
            for (int i = 0; i < N; ++i)
                nowans = nowans * getWays(m, abs(tx - x[i])) % moder;
            ansX = (ansX + nowans) % moder;
        }
        
        long long ansY = 0;
        for (long long ty = y[0] - m; ty <= y[0] + m; ty += 2)
        {
            long long nowans = 1;
            for (int i = 0; i < N; ++i)
                nowans = nowans * getWays(m, abs(ty - y[i])) % moder;
            ansY = (ansY + nowans) % moder;
        }
        
        return (int)((ansX * ansY) % moder);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 0; verify_case(1, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0,2,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 4; verify_case(2, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {7,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 2; verify_case(3, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {-2,-2,-2,0,0,0,2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,0,2,-2,0,2,-2,0,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; int Arg3 = 387540818; verify_case(4, Arg3, calc(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    WolfPack ___test;
    ___test.run_test(-1);
}
// END CUT HERE
