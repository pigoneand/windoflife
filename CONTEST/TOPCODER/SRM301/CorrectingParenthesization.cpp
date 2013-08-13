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

bool caled[100][100];
int f[100][100];
const int INFI = 9999;
char cs[6] = { '(', '[', '{', ')', ']', '}' };

class CorrectingParenthesization
{
public:
    
    int getOP(char c1, char c2)
    {
        int ans = INFI;
        for (int i = 0; i < 3; ++i)
        {
            int j = i + 3;
            int cost = 0;
            cost += (cs[i] == c1 ? 0 : 1);
            cost += (cs[j] == c2 ? 0 : 1);
            ans = min(ans, cost);
        }
        return ans;
    }
    
    int getF(int l, int r, const string& s)
    {
        if (l > r) return 0;
        if ((r - l + 1) % 2 == 1) return INFI;
        if (caled[l][r]) return f[l][r];
        caled[l][r] = true;
        
        int& ret = f[l][r];
        ret = INFI;
        for (int i = l + 1; i <= r; ++i)
            ret = min(ret, getOP(s[l], s[i]) + getF(l + 1, i - 1, s) + getF(i + 1, r, s));
        return ret;
    }
    
    
    int getMinErrors(string s)
    {
        memset(caled, false, sizeof(caled));
        return getF(0, (int) s.length() - 1, s);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "([{}])()[]{}"; int Arg1 = 0; verify_case(0, Arg1, getMinErrors(Arg0)); }
	void test_case_1() { string Arg0 = "([)]"; int Arg1 = 2; verify_case(1, Arg1, getMinErrors(Arg0)); }
	void test_case_2() { string Arg0 = "([{}[]"; int Arg1 = 1; verify_case(2, Arg1, getMinErrors(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    CorrectingParenthesization ___test;
    ___test.run_test(-1);
}
// END CUT HERE
