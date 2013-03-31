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
#include <cassert>
using namespace std;
//END CUT HERE

class InverseCollatz
{
public:
    
    long long getReverse(long long x, char op)
    {
        if (op == 'E') return x * 2;
        if (x % 3 != 1) return 0;
        x = x - 1;
        x = x / 3;
        if (x % 2 == 0) return 0;
        return x;
    }
    
    string getForm(string s)
    {
        long long ia = 1;
        long long ib = 0;
        for (int i = (int) s.length() - 1; i >= 0; --i)
        {
            vector<long long> validx;
            for (long long x = ib; validx.size() < 2; x += ia)
            {
                if (getReverse(x, s[i]) > 0)
                    validx.push_back(getReverse(x, s[i]));
            }
            ib = validx[0];
            ia = validx[1] - validx[0];
            
            if (ib == ia) ib = 0;
        }
        
        ostringstream ostr;
        ostr << ia << "k+" << ib;
        return ostr.str();
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "EEE"; string Arg1 = "8k+0"; verify_case(0, Arg1, getForm(Arg0)); }
	void test_case_1() { string Arg0 = "OE"; string Arg1 = "2k+1"; verify_case(1, Arg1, getForm(Arg0)); }
	void test_case_2() { string Arg0 = "OEO"; string Arg1 = "4k+3"; verify_case(2, Arg1, getForm(Arg0)); }
	void test_case_3() { string Arg0 = "EEEEOEEEEOEEEEOEEEEOEEEEOEEEEOEEEEOEEEEOEEEEOEEEEO"; string Arg1 = "2199023255552k+1014933810256"; verify_case(3, Arg1, getForm(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    InverseCollatz ___test;
    ___test.run_test(-1);
}
// END CUT HERE
