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

int dir[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
vector<int> dx;
vector<int> dy;
int N;

class TheKnights
{
public:
    
    double getAttackByOne()
    {
        double ret = 0.0;
        double p = 1.0 / N / N;
        for (int k = 0; k < dx.size(); ++k)
        {
            int minx = 1, miny = 1, maxx = N, maxy = N;
            minx = max(minx, 1 - dx[k]);
            miny = max(miny, 1 - dy[k]);
            maxx = min(maxx, N - dx[k]);
            maxy = min(maxy, N - dy[k]);
            
            if (maxx >= minx && maxy >= miny)
                ret += p * (maxx - minx + 1) * (maxy - miny + 1);
        }
        return ret;
    }
    
    double getAttackByTwo()
    {
        double ret = 0.0;
        double p = 1.0 / ((1.0 * N * N) * (1.0 * N * N - 1) / 2.0);
        for (int i = 0; i < dx.size(); ++i)
            for (int j = i + 1; j < dx.size(); ++j)
            {
                int minx = 1, miny = 1, maxx = N, maxy = N;
                minx = max(minx, 1 - dx[i]);
                miny = max(miny, 1 - dy[i]);
                maxx = min(maxx, N - dx[i]);
                maxy = min(maxy, N - dy[i]);
                minx = max(minx, 1 - dx[j]);
                miny = max(miny, 1 - dy[j]);
                maxx = min(maxx, N - dx[j]);
                maxy = min(maxy, N - dy[j]);
                
                if (maxx >= minx && maxy >= miny)
                    ret += p * (maxx - minx + 1) * (maxy - miny + 1);
            }
        return ret;
    }
    
    double find(int n, int a, int b)
    {
        N = n;
        double ans = 0;
        dx.clear(); dy.clear();
        dx.push_back(0);
        dy.push_back(0);
        for (int k = 0; k < 4; ++k)
        {
            dx.push_back(dir[k][0] * a);
            dy.push_back(dir[k][1] * b);
            if (a != b)
            {
                dx.push_back(dir[k][0] * b);
                dy.push_back(dir[k][1] * a);
            }
        }
        
        ans += getAttackByOne() * 2;
        ans -= getAttackByTwo();
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 1; double Arg3 = 3.3333333333333335; verify_case(0, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 47; int Arg1 = 7; int Arg2 = 74; double Arg3 = 2.0; verify_case(1, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 1; double Arg3 = 4.888888888888889; verify_case(2, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 9999; int Arg1 = 999; int Arg2 = 99; double Arg3 = 16.25885103191273; verify_case(3, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 10; int Arg1 = 1; int Arg2 = 6; double Arg3 = 7.636363636363637; verify_case(4, Arg3, find(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    TheKnights ___test;
    ___test.run_test(-1);
}
// END CUT HERE
