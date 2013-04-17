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

class EratosthenSieve2
{
public:
    vector<int> getNew(vector<int> & a, int k)
    {
        vector<int> ret;
        for (int i = 0; i < a.size(); ++i)
            if ((i + 1) % k != 0) ret.push_back(a[i]);
        return ret;
    }
    
    int nthElement(int n)
    {
        vector<int> a(1000, 0);
        for (int i = 1; i <= 1000; ++i) a[i - 1] = i;
        
        for (int i = 2; i <= 10; ++i)
            a = getNew(a, i);
        
        return a[n - 1];
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 7; verify_case(0, Arg1, nthElement(Arg0)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; verify_case(1, Arg1, nthElement(Arg0)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 79; verify_case(2, Arg1, nthElement(Arg0)); }
	void test_case_3() { int Arg0 = 25; int Arg1 = 223; verify_case(3, Arg1, nthElement(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    EratosthenSieve2 ___test;
    ___test.run_test(-1);
}
// END CUT HERE
