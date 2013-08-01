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
#include <numeric>
#include <functional>
#include <cmath>
using namespace std;
//END CUT HERE

int dis[32][32][32][32];
const int INF = 999999;

inline double sqr(double x) { return x * x; }

class LongBlob
{
public:
    double maxLength(vector <string> image)
    {
        int H = (int) image.size();
        int W = (int) image[0].size();
        
        for (int x1 = 0; x1 < H; ++x1)
            for (int y1 = 0; y1 < W; ++y1)
                for (int x2 = 0; x2 < H; ++x2)
                    for (int y2 = 0; y2 < W; ++y2)
                    {
                        if (abs(x1 - x2) + abs(y1 - y2) == 1)
                        {
                            if (image[x2][y2] == '1') dis[x1][y1][x2][y2] = 1;
                            else dis[x1][y1][x2][y2] = 0;
                        }
                        else dis[x1][y1][x2][y2] = INF;
                    }
        
        for (int xk = 0; xk < H; ++xk)
            for (int yk = 0; yk < W; ++yk)
                for (int x1 = 0; x1 < H; ++x1)
                    for (int y1 = 0; y1 < W; ++y1)
                        for (int x2 = 0; x2 < H; ++x2)
                            for (int y2 = 0; y2 < W; ++y2)
                                dis[x1][y1][x2][y2] = min(dis[x1][y1][x2][y2], dis[x1][y1][xk][yk] + dis[xk][yk][x2][y2]);
        
        double ans = 0;
        for (int x1 = 0; x1 < H; ++x1)
            for (int y1 = 0; y1 < W; ++y1)
                for (int x2 = 0; x2 < H; ++x2)
                    for (int y2 = 0; y2 < W; ++y2)
                        if (dis[x1][y1][x2][y2] < 4 || (dis[x1][y1][x2][y2] == 4 && image[x1][y1] == '0'))
                        {
                            ans = max(ans, sqrt(sqr(x1 - x2) + sqr(y1 - y2)));
                        }
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0010",
        "1001",
        "0011",
        "0111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 4.242640687119285; verify_case(0, Arg1, maxLength(Arg0)); }
	void test_case_1() { string Arr0[] = {"101010101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 7.0; verify_case(1, Arg1, maxLength(Arg0)); }
	void test_case_2() { string Arr0[] = {"1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101",
        "0101010101010101010101010",
        "1010101010101010101010101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 8.0; verify_case(2, Arg1, maxLength(Arg0)); }
	void test_case_3() { string Arr0[] = {"01011",
        "11100",
        "01110",
        "11111",
        "01011",
        "11111"}
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 5.656854249492381; verify_case(3, Arg1, maxLength(Arg0)); }
    
    // END CUT HERE
    
}; 

// BEGIN CUT HERE 
int main()
{
    LongBlob ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE 
