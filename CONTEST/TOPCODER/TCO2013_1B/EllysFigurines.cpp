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


class EllysFigurines
{
public:
    int getCost(vector<bool>& e, int P)
    {
        int cost = 0;
        for (int i = 0; i < e.size(); ++i)
        {
            if (e[i])
            {
                cost++;
                for (int j = i; j < i + P && j < e.size(); ++j) e[j] = false;
            }
        }
        return cost;
    }
    
    int getMoves(vector <string> b, int R, int C)
    {
        int ans = 9999;
        int Rows = b.size();
        int Cols = b[0].size();
        
        for (int s = 0; s < (1 << Rows); ++s)
        {
            vector<bool> rowE(Rows, false);
            for (int i = 0; i < Rows; ++i)
                if (s & (1 << i)) rowE[i] = true;
            
            vector<bool> colE(Cols, false);
            for (int i = 0; i < Rows; ++i)
                for (int j = 0; j < Cols; ++j)
                {
                    if (b[i][j] == '.') continue;
                    if (s & (1 << i)) continue;
                    colE[j] = true;
                }
            
            int nowcost = getCost(rowE, R) + getCost(colE, C);
            ans = min(ans, nowcost);
        }
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".X.X.",
        "XX..X",
        ".XXX.",
        "...X.",
        ".X.XX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 3; verify_case(0, Arg3, getMoves(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {".X.X.",
        "XX..X",
        ".X.X.",
        "...X.",
        ".X.XX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; verify_case(1, Arg3, getMoves(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"XXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 1; verify_case(2, Arg3, getMoves(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"XXXXX",
        "X....",
        "XXX..",
        "X....",
        "XXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 4; verify_case(3, Arg3, getMoves(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"XXX..XXX..XXX.",
        ".X..X....X...X",
        ".X..X....X...X",
        ".X..X....X...X",
        ".X...XXX..XXX.",
        "..............",
        "...XX...XXX...",
        "....X......X..",
        "....X....XXX..",
        "....X......X..",
        "...XXX..XXX..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 7; verify_case(4, Arg3, getMoves(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    EllysFigurines ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE 
