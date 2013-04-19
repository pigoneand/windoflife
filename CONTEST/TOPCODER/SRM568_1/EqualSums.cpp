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
const int UNFILL = -99999999;

class EqualSums
{
public:
    
    vector<vector<int> > m;
    int N;

    vector<int> row;
    vector<int> col;
    
    bool check(vector<int>& nr, vector<int>& nc)
    {
        for (int i = 0; i < N; ++i) if ((nr[i] < 0 || nr[i] > 9) && nr[i] != UNFILL) return false;
        for (int j = 0; j < N; ++j) if ((nc[j] < 0 || nc[j] > 9) && nc[j] != UNFILL) return false;
        
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (nr[i] != UNFILL && nc[j] != UNFILL && m[i][j] != UNFILL)
                    if (nr[i] + nc[j] != m[i][j]) return false;
        return true;
    }
    
    void fillRow(vector<int>& nr, vector<int>& nc, int r, int value)
    {
        nr[r] = value;
        for (int c = 0; c < N; ++c)
            if (nc[c] == UNFILL && m[r][c] != UNFILL)
                fillCol(nr, nc, c, m[r][c] - nr[r]);
    }
    
    void fillCol(vector<int>& nr, vector<int>& nc, int c, int value)
    {
        nc[c] = value;
        for (int r = 0; r < N; ++r)
            if (nr[r] == UNFILL && m[r][c] != UNFILL)
                fillRow(nr, nc, r, m[r][c] - nc[c]);
    }
    
    int count(vector<string> board)
    {
        N = (int) board.size();
        m = vector<vector<int> >(N, vector<int>(N, UNFILL));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                m[i][j] = (board[i][j] == '-') ? UNFILL : board[i][j] - '0';
        row = col = vector<int>(N, UNFILL);
        
        long long ansall = 1;
        long long ansnozero = 1;
        for (int i = 0; i < N; ++i)
        {
            if (row[i] == UNFILL)
            {
                long long nowall = 0;
                long long nownozero = 0;
                vector<int> validnr, validnc;
                for (int value = 0; value <= 9; ++value)
                {
                    vector<int> nr = row;
                    vector<int> nc = col;
                    fillRow(nr, nc, i, value);
                    if (check(nr, nc))
                    {
                        nowall++;
                        //if (value > 0) nownozero++;
                        bool haszero = false;
                        for (int r = 0; r < N; ++r)
                            if (nr[r] != row[r] && nr[r] == 0) haszero = true;
                        if (!haszero) nownozero++;
                        validnr = nr;
                        validnc = nc;
                        //cout << value << " ";
                    }
                }
                //cout << " : ";
                ansall = ansall * nowall % moder;
                ansnozero = ansnozero * nownozero % moder;
                if (nowall == 0) return 0;
                
                //cout << i << " " << nowall << " " << nownozero << endl;
                
                row = validnr;
                col = validnc;
            }
        }
        
        return (int) ((ansall - ansnozero + moder) % moder);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1-",
        "-2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {"123",
        "4--",
        "--9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"9--",
        "-9-",
        "--9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 271; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"11",
        "12"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { string Arr0[] = {"-4--",
        "-0-2",
        "--1-",
        "4---"}
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(4, Arg1, count(Arg0)); }
	void test_case_5() { string Arr0[] = {"--2",
        "02-",
        "-10"}
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(5, Arg1, count(Arg0)); }
	void test_case_6() { string Arr0[] = {"----------1---------------0-----7-----------------",
        "-----4--------------------------------------------",
        "--------5-------------5-3---5---------------6-----",
        "-------2----------1-------------------------------",
        "-----4--------------------------------------------",
        "-----3--------------------------------------------",
        "-6----------5-------------------------------------",
        "-------------------------------7---5----------6---",
        "--------6-------------6-4---6---------------7-----",
        "-------------4----------------5-------------------",
        "3------------------------------------------6------",
        "3------------------------------------------6------",
        "-------------4----------------5-------------------",
        "---------------2-------------------------3--------",
        "--2------------------------------------------2----",
        "---8---------------1-------------------3----------",
        "---------------3----------------------------------",
        "----7----------------5---0-----------------------5",
        "----------------5-------------------------3-----1-",
        "----------1---------------0-----7-----------------",
        "-------------5----------------6-------------------",
        "-7----------6-------------------------------------",
        "---8---------------1-------------------3----------",
        "-----------------------3--------------------------",
        "----8----------------6---1-----------------------6",
        "------------------------------------------4-----2-",
        "-----------5---------------5----------------------",
        "-----------------------------6--------------------",
        "----8----------------6---1-----------------------6",
        "----------------5-------------------------3-----1-",
        "-------------------------------6---4--2-------5---",
        "-6----------5-------------------------------------",
        "--------5-------------5-3---5---------------6-----",
        "-------------5----------------6-------------------",
        "-----3--------------------------------------------",
        "---------------2-------------------------3--------",
        "---------4---------------------------6------------",
        "-------------------------------6---4--2-------5---",
        "------2-------------1------------22---------------",
        "--------5-------------5-3---5---------------6-----",
        "-----------5--3------------5----------------------",
        "--2------------------------------------------2----",
        "---------5---------------------------7------------",
        "-------------4----------------5-------------------",
        "-----------------5------------------4---6------2--",
        "-------------------------------6---4--2-------5---",
        "-----------------------2--------------------------",
        "----------------6-------------------------4-----2-",
        "-------------------------------6---4--2-------5---",
        "--------5-------------5-3---5---------------6-----"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 45094393; verify_case(6, Arg1, count(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    EqualSums ___test;
    ___test.run_test(-1);
}
// END CUT HERE
