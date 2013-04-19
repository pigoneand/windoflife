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

class IndicatorMotion
        { 
        public: 
        string getMotion(string program, char startState) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "F03L02R03S02F04"; char Arg1 = '-'; string Arg2 = "-|-|\\-\\|///\\/\\/"; verify_case(0, Arg2, getMotion(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "F10R01F10"; char Arg1 = '/'; string Arg2 = "/\\/\\/\\/\\/\\/-|-|-|-|-|-"; verify_case(1, Arg2, getMotion(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = ""; char Arg1 = '/'; string Arg2 = "/"; verify_case(2, Arg2, getMotion(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "F00R00L00S00"; char Arg1 = '\\'; string Arg2 = "\\"; verify_case(3, Arg2, getMotion(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        IndicatorMotion ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
