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
using namespace std;
//END CUT HERE

bool caled1[40][40][26];
long long f1[40][40][26];
const long long INFI = 1000000000;

bool caled2[40][40][2600];
long long f2[40][40][2600];

class ContextFreeGrammars
{
public:
    string word;
    
    long long getF2(int l, int r, int rid, int offset)
    {
        int actOffset = RsOffset[rid] + offset;
        if (caled2[l][r][actOffset]) return f2[l][r][actOffset];
        caled2[l][r][actOffset] = true;
        
        long long & ret = f2[l][r][actOffset];
        ret = 0;
        
        if (l > r && offset == Rs[rid].length()) return ret = 1;
        if (offset == Rs[rid].length()) return ret = 0;
        if (l > r) return ret = 0;
        
        char nowC = Rs[rid][offset];
        if (islower(nowC))
        {
            if (word[l] == nowC)
            {
                long long tmp = getF2(l + 1, r, rid, offset + 1);
                ret += tmp; if (ret > INFI) ret = INFI + 1;
            }
            else return ret = 0;
        }
        else
        {
            for (int nr = l; nr <= r; ++nr)
            {
                long long tmp1 = getF1(l, nr, nowC - 'A');
                long long tmp2 = getF2(nr + 1, r, rid, offset + 1);
                long long tmp = tmp1 * tmp2;
                ret += tmp; if (ret > INFI) ret = INFI + 1;
            }
        }
        return ret;
    }
    
    long long getF1(int l, int r, int c)
    {
        if (caled1[l][r][c]) return f1[l][r][c];
        caled1[l][r][c] = true;
        long long & ret = f1[l][r][c];
        
        ret = 0;
        if (l > r) return ret = 0;
        for (int i = 0; i < R[c].size(); ++i)
        {
            long long tmp = getF2(l, r, Rid[c][i], 0);
            ret += tmp;
        }
        if (ret > INFI) ret = INFI + 1;
        return ret;
    }
    
    vector<string> R[26];
    vector<int> Rid[26];
    vector<string> Rs;
    vector<int> RsOffset;

    int countParsingTrees(vector <string> rules, char seed, string _word)
    {
        //cout << _word << " " << seed << endl;
        
        /// init, parsing rules
        word = _word;
        for (int i = 0; i < 26; ++i) { R[i].clear(); Rid[i].clear(); }
        Rs.clear();
        RsOffset.clear();
        memset(caled1, false, sizeof(caled1));
        memset(caled2, false, sizeof(caled2));
        
        for (int i = 0; i < rules.size(); ++i)
        {
            string s = rules[i];
            for (int j = 0; j < s.length(); ++j) if (!islower(s[j]) && !isupper(s[j])) s[j] = ' ';
            istringstream istr(s);
            string L;
            istr >> L;
            string rule;
            while (istr >> rule)
                R[L[0] - 'A'].push_back(rule);
        }
        
        for (int i = 0; i < 26; ++i)
        {
            for (int j = 0; j < R[i].size(); ++j) 
            {
                Rs.push_back(R[i][j]);
                Rid[i].push_back((int) Rs.size() - 1);
            }
        }
        
        int offset = 0;
        for (int i = 0; i < Rs.size(); ++i)
        {
            RsOffset.push_back(offset);
            offset += Rs[i].length() + 1;
        }
        
        /// get answer is always simple, but who know the work behind desk?
        int ans = (int) getF1(0, (int) word.length() - 1, seed - 'A');
        if (ans == INFI + 1) ans = -1;
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"A ::= BD",
        "B ::= bB | b | Bb",
        "D ::= dD",
        "D ::= d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'A'; string Arg2 = "bdd"; int Arg3 = 1; verify_case(0, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"A ::= BD",
        "B ::= bB | b | Bb",
        "D ::= dD",
        "D ::= d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'A'; string Arg2 = "bbd"; int Arg3 = 2; verify_case(1, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"A ::= BD",
        "B ::= bB | b | Bb",
        "D ::= dD",
        "D ::= d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'A'; string Arg2 = "ddbb"; int Arg3 = 0; verify_case(2, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"B ::= topcoder | topcoder",
        "B ::= topcoder"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'B'; string Arg2 = "topcoder"; int Arg3 = 3; verify_case(3, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"A ::= BCD",
        "Z ::= z",
        "B ::= Cz | Dz | Zz",
        "C ::= Bz | Dz",
        "D ::= Cz | Bz"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'X'; string Arg2 = "zzz"; int Arg3 = 0; verify_case(4, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"B ::= bB | bB | bB | bB | b" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'B'; string Arg2 = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; int Arg3 = -1; verify_case(5, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    ContextFreeGrammars ___test;
    ___test.run_test(-1);
} 
// END CUT HERE 
