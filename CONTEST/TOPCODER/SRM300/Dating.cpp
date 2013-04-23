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

class Dating
        { 
        public: 
        string dates(string circle, int k) 
            { 
            
            } 
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "abXCd"; int Arg1 = 2; string Arg2 = "bC dX"; verify_case(0, Arg2, dates(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "abXCd"; int Arg1 = 8; string Arg2 = "Xa dC"; verify_case(1, Arg2, dates(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "HGFhgfz"; int Arg1 = 1; string Arg2 = "Hf Gg Fh"; verify_case(2, Arg2, dates(Arg0, Arg1)); }

// END CUT HERE
 
        }; 

    // BEGIN CUT HERE 
    int main()
        {
        Dating ___test; 
        ___test.run_test(-1); 
        } 
    // END CUT HERE 
