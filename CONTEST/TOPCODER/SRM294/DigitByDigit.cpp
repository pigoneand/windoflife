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

class DigitByDigit
{
public:
    double expectedScore(string digits)
    {
        /// init pow 10
        double pow10[50];
        pow10[0] = 1;
        for (int i = 1; i < 50; ++i) pow10[i] = pow10[i - 1] * 10;
        
        vector<double> Ed[51];
        for (int i = 1; i <= 50; ++i) Ed[i].assign(i, 0);
        Ed[1][0] = 4.5;
        
        for (int n = 2; n <= 50; ++n)
        {
            /// for each new digit, 
            for (int d = 0; d <= 9; ++d)
            {
                double maxE = -1;
                int maxPosi = -1;
                /// find max fit position to put
                for (int p = 0; p < n; ++p)
                {
                    double nowE = pow10[p] * d;
                    for (int i = 0; i < n; ++i)
                    {
                        if (i == p) continue;
                        if (i < p)
                            nowE += pow10[i] * Ed[n - 1][i];
                        else
                            nowE += pow10[i] * Ed[n - 1][i - 1];
                    }
                    if (nowE > maxE) { maxE = nowE; maxPosi = p; }
                }
                
                /// fit position would be fix number d, other position would be nature
                Ed[n][maxPosi] += 1.0 * d / 10;
                for (int p = 0; p < n; ++p)
                {
                    if (p == maxPosi) continue;
                    if (p < maxPosi) Ed[n][p] += Ed[n - 1][p] / 10;
                    else Ed[n][p] += Ed[n - 1][p - 1] / 10;
                }
            }
        }
        
        double ans = 0;
        int offset = 0;
        int blanks = count(digits.begin(), digits.end(), '_');
        reverse(digits.begin(), digits.end());
        for (int i = 0; i < digits.size(); ++i)
        {
            if (digits[i] != '_') ans += pow10[i] * (digits[i] - '0');
            else
            {
                ans += pow10[i] * Ed[blanks][offset];
                offset++;
            }
        }
        
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "_0"; double Arg1 = 45.0; verify_case(0, Arg1, expectedScore(Arg0)); }
	void test_case_1() { string Arg0 = "__"; double Arg1 = 60.75; verify_case(1, Arg1, expectedScore(Arg0)); }
	void test_case_2() { string Arg0 = "_55_"; double Arg1 = 6303.25; verify_case(2, Arg1, expectedScore(Arg0)); }
	void test_case_3() { string Arg0 = "____0000000000000000"; double Arg1 = 7.482735000000001E19; verify_case(3, Arg1, expectedScore(Arg0)); }
	void test_case_4() { string Arg0 = "___6__3___"; double Arg1 = 8.604871517066002E9; verify_case(4, Arg1, expectedScore(Arg0)); }
	void test_case_5() { string Arg0 = "__________"; double Arg1 = 8.882477600592714E9; verify_case(5, Arg1, expectedScore(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    DigitByDigit ___test;
    ___test.run_test(-1);
}
// END CUT HERE
