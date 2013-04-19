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

class MountainsEasy
{
public:
    
    /**
     * ax + by = gcd(a, b)
     * x, y may be negative
     */
    long long extgcd(long long a, long long b, long long & x, long long & y)
    {
        if (b == 0) { x = 1; y = 0; return a; }
        long long d = extgcd(b, a % b, x, y);
        long long t = x; x = y; y = t - a / b * y;
        return d;
    }
    
    /**
     * a * x mod p = 1 , (a,p) = 1
     */
    long long getReverse(long long a, long long p)
    {
        if (a == 1) return 1;
        long long x, y;
        extgcd(a, p, x, y);
        return (x % p + p) % p;
    }
    
    bool isOK(vector<string>& pic, int px, int py)
    {
        int H = (int) pic.size();
        int W = (int) pic[0].size();
        for (int x = 0; x < W; ++x)
            for (int y = 0; y <= py - abs(x - px); ++y)
                if (pic[H - 1 - y][x] == '.') return false;
        return true;
    }
    
    void fill(vector<string>& pic, int px, int py)
    {
        int H = (int) pic.size();
        int W = (int) pic[0].size();
        for (int x = 0; x < W; ++x)
            for (int y = 0; y <= py - abs(x - px); ++y)
                pic[H - 1 - y][x] = 'F';
    }
    
    int countPlacements(vector<string> picture, int N)
    {
        int K = 0;
        int H = (int) picture.size();
        int W = (int) picture[0].size();
        
        vector<string> tempPic = picture;
        for (int y = H - 1; y >= 0; --y)
            for (int x = 0; x < W; ++x)
                if (tempPic[H - 1 - y][x] == 'X' && isOK(tempPic, x, y))
                {
                    K++;
                    fill(tempPic, x, y);
                }
        
        int P = 0;
        for (int y = H - 1; y >= 0; --y)
            for (int x = 0; x < W; ++x)
                if (isOK(picture, x, y)) P++;
        
        long long ans = 0;
        long long moder = 1000000009;
        
        //cout << N << " " << P << " " << K << endl;
        vector<vector<long long> > C(N + 1, vector<long long>(K + 1, 0));
        C[0][0] = 1;
        for (int i = 1; i <= N; ++i)
            for (int j = 0; j <= K; ++j)
            {
                C[i][j] = C[i - 1][j] * (P - K + j);
                if (j > 0) C[i][j] += C[i - 1][j - 1];
                C[i][j] %= moder;
            }
        
        ans = C[N][K];
        for (int i = 1; i <= K; ++i) ans = ans * i % moder;
        return (int) ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"X.",
        "XX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"X.",
        "XX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 5; verify_case(1, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"X.X",
        "XXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; verify_case(2, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"X.X",
        "XXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 24; verify_case(3, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"......",
        "X..X..",
        "XXXXXX",
        "XXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 6; verify_case(4, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"......",
        "X..X..",
        "XXXXXX",
        "XXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 300; verify_case(5, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_6() { string Arr0[] = {"....X...X..",
        "...XXX.XXX.",
        "XXXXXXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 764632413; verify_case(6, Arg2, countPlacements(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    MountainsEasy ___test;
    ___test.run_test(-1);
}
// END CUT HERE
