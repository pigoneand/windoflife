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

class CountingCommonSubsequences
{
public:
    
    void findNextChar(const string& s, vector<vector<int> >& v)
    {
        int N = (int) s.length();
        v.assign(N, vector<int>(26, -1));
        
        v[N - 1][s[N - 1] - 'a'] = N - 1;
        for (int i = N - 2; i >= 0; --i)
        {
            for (int j = 0; j < 26; ++j)
                v[i][j] = v[i + 1][j];
            v[i][s[i] - 'a'] = i;
        }
    }
    
    vector<vector<int> > va, vb, vc;
    long long f[51][51][51];
    bool caled[51][51][51];
    
    long long getF(int a, int b, int c)
    {
        if (caled[a][b][c]) return f[a][b][c];
        caled[a][b][c] = true;
        long long & ret = f[a][b][c];
        
        ret = 1;
        if (a >= va.size() || b >= vb.size() || c >= vc.size()) return ret;
        for (int cc = 0; cc < 26; ++cc)
        {
            int na = va[a][cc];
            int nb = vb[b][cc];
            int nc = vc[c][cc];
            if (na >= 0 && nb >= 0 && nc >= 0) ret += getF(na + 1, nb + 1, nc + 1);
        }
        return ret;
    }
    
    long long countCommonSubsequences(string a, string b, string c)
    {
        findNextChar(a, va);
        findNextChar(b, vb);
        findNextChar(c, vc);
        
        memset(caled, false, sizeof(caled));
        return getF(0, 0, 0) - 1;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "call"; string Arg1 = "accelerate"; string Arg2 = "candle"; long long Arg3 = 6LL; verify_case(0, Arg3, countCommonSubsequences(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "topcoder"; string Arg1 = "topcoder"; string Arg2 = "topcoder"; long long Arg3 = 239LL; verify_case(1, Arg3, countCommonSubsequences(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "no"; string Arg1 = "correct"; string Arg2 = "answer"; long long Arg3 = 0LL; verify_case(2, Arg3, countCommonSubsequences(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "aabbaabbaabbaabbaabbaabbaabbaabbaabbaabbaabb"; string Arg1 = "abababababababababababababababababababab"; string Arg2 = "aaaabbbbaaaabbbbaaaabbbbaaaabbbbaaaabbbb"; long long Arg3 = 1725660LL; verify_case(3, Arg3, countCommonSubsequences(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    CountingCommonSubsequences ___test;
    ___test.run_test(-1);
}
// END CUT HERE
