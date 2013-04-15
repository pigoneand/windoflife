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

class PaperRockScisQuals
{
public:
    
    void play(const string& s1, const string& s2, int & score1, int & score2)
    {
        int w1 = 0;
        int w2 = 0;
        for (int i = 0; i < s1.length(); ++i)
        {
            if (s1[i] == s2[i]) continue;
            if (s1[i] == 'P') { if (s2[i] == 'R') w1++; else w2++; }
            if (s1[i] == 'R') { if (s2[i] == 'S') w1++; else w2++; }
            if (s1[i] == 'S') { if (s2[i] == 'P') w1++; else w2++; }
        }
        if (w1 == w2) { score1 = 1; score2 = 1; return; }
        if (w1 > w2) { score1 = 2; score2 = 0; return; }
        score1 = 0; score2 = 2;
        return;
    }
    
    int whoPassed(vector <string> players)
    {
        int N = (int) players.size();
        vector<int> score(N, 0);
        
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
            {
                int s1, s2;
                play(players[i], players[j], s1, s2);
                score[i] += s1;
                score[j] += s2;
            }
        
        return max_element(score.begin(), score.end()) - score.begin();
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"PPRRS","PPRRP","PPRSP","PPSSP"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, whoPassed(Arg0)); }
	void test_case_1() { string Arr0[] = {"RRRRR","PPPPP","RRRRR","PPPPP"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, whoPassed(Arg0)); }
	void test_case_2() { string Arr0[] = {"RRRRR","PPPPP","SSSSS","PPPPP"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, whoPassed(Arg0)); }
	void test_case_3() { string Arr0[] = {"RRRRR","PPPPP","SSSSS","SSSSS","RRRRR","RRRRR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, whoPassed(Arg0)); }
	void test_case_4() { string Arr0[] = {"PPRPS","RRRPR","SSPRS","SSPRR","PPRSP","SPRPS","SPRSP","PRSPR","PRSPR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(4, Arg1, whoPassed(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    PaperRockScisQuals ___test;
    ___test.run_test(-1);
}
// END CUT HERE
