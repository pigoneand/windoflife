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
long long C[100][100];


class WolfPackDivTwo
{
public:
    void initC()
    {
        memset(C, 0, sizeof(C));
        C[0][0] = 1;
        C[1][0] = C[1][1] = 1;
        for (int i = 2; i < 100; ++i)
        {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; ++j)
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % moder;
        }
    }
    
    long long getMoves(int m, int d)
    {
        if ((m + d) % 2 == 1) return 0;
        int p1 = (m + d) / 2;
        return C[m][p1];
    }
    
    int calc(vector <int> x, vector <int> y, int m)
    {
        int N = (int) x.size();
        initC();
        
        long long ans = 0;
        for (int tx = -50; tx <= 100; ++tx)
            for (int ty = -50; ty <= 100; ++ty)
            {
                long long nowans = 1;
                for (int i = 0; i < N; ++i)
                {
                    int d = abs(tx - x[i]) + abs(ty - y[i]);
                    int dx = abs(tx - x[i]);
                    int dy = abs(ty - y[i]);
                    if (d > m) nowans *= 0;
                    else
                    {
                        long long curAns = 0;
                        for (int xmove = 0; xmove <= m; ++xmove)
                        {
                            int ymove = m - xmove;
                            if (xmove >= dx && ymove >= dy)
                            {
                                curAns += (getMoves(xmove, dx) * getMoves(ymove, dy) % moder) * C[m][xmove] % moder;
                                curAns %= moder;
                            }
                        }
                        nowans = nowans * curAns % moder;
                    }
                }
                ans = (ans + nowans) % moder;
            }
        
        return (int) ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 0; verify_case(1, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0,2,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 4; verify_case(2, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {7,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 2; verify_case(3, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,4,4,4,6,6,6,6,6,6,6,6,6,6,8,8,8,8,8,8,8,8,8,8}
        ; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,2,4,6,8,10,12,14,16,18,0,2,4,6,8,10,12,14,16,18,0,2,4,6,8,10,12,14,16,18,0,2,4,6,8,10,12,14,16,18,0,2,4,6,8,10,12,14,16,18}
        ; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; int Arg3 = 0; verify_case(4, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,4,4,4,6,6,6,6,6,6,6,6,6,6,8,8,8,8,8,8,8,8,8,8}
        ; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,2,4,6,8,10,12,14,16,18,0,2,4,6,8,10,12,14,16,18,0,2,4,6,8,10,12,14,16,18,0,2,4,6,8,10,12,14,16,18,0,2,4,6,8,10,12,14,16,18}
        ; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 31; int Arg3 = 573748580; verify_case(5, Arg3, calc(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    WolfPackDivTwo ___test;
    ___test.run_test(-1);
}
// END CUT HERE
