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

map<int, bool> isWin;

vector<vector<bool> > getStateFromCompress(int state)
{
    vector<vector<bool> > ret(4, vector<bool>(4, false));
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ret[i][j] = (state & (1 << (i * 4 + j))) > 0;
    return ret;
}

int getCompressState(vector<vector<bool> >& s)
{
    int ret = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (s[i][j]) ret += (1 << (i * 4 + j));
    return ret;
}

bool getIsWin(int state)
{
    if (isWin.find(state) != isWin.end()) return isWin[state];
    
    vector<vector<bool> > cur = getStateFromCompress(state);
    isWin[state] = false;
    
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            if (cur[i][j]) continue;
            if (i > 0 && cur[i - 1][j]) continue;
            if (j > 0 && cur[i][j - 1]) continue;
            if (i < 3 && cur[i + 1][j]) continue;
            if (j < 3 && cur[i][j + 1]) continue;
            cur[i][j] = true;
            isWin[state] |= (!getIsWin(getCompressState(cur)));
            cur[i][j] = false;
        }
    return isWin[state];
}

class GridGame
{
public:
    int winningMoves(vector <string> grid)
    {
        isWin.clear();
        vector<vector<bool> > s(4, vector<bool>(4, false));
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                s[i][j] = (grid[i][j] == 'X');
        
        int ans = 0;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
            {
                if (s[i][j]) continue;
                if (i > 0 && s[i - 1][j]) continue;
                if (j > 0 && s[i][j - 1]) continue;
                if (i < 3 && s[i + 1][j]) continue;
                if (j < 3 && s[i][j + 1]) continue;
                s[i][j] = true;
                //cout << getCompressState(s) << endl;
                if (!getIsWin(getCompressState(s))) ans++;
                s[i][j] = false;
            }
        
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"....",
        "....",
        "....",
        "...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, winningMoves(Arg0)); }
	void test_case_1() { string Arr0[] = {"....",
        "....",
        ".X..",
        "...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 11; verify_case(1, Arg1, winningMoves(Arg0)); }
	void test_case_2() { string Arr0[] = {".X.X",
        "..X.",
        ".X..",
        "...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, winningMoves(Arg0)); }
	void test_case_3() { string Arr0[] = {".X.X",
        "..X.",
        "X..X",
        "..X."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, winningMoves(Arg0)); }
	void test_case_4() { string Arr0[] = {"X..X",
        "..X.",
        ".X..",
        "X..X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(4, Arg1, winningMoves(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    GridGame ___test;
    ___test.run_test(-1);
} 
// END CUT HERE 
