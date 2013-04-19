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

class OptimalQueues
{
public:
    int minWaitingTime(vector <int> clientArrivals, int tellerCount, int serviceTime)
    {
        int N = (int) clientArrivals.size();
        sort(clientArrivals.begin(), clientArrivals.end(), greater<int>());
        vector<int> waitTime(N, serviceTime);
        for (int i = 0; i < N; ++i) waitTime[i] *= (i / tellerCount + 1);
        
        int ans = 0;
        for (int i = 0; i < N; ++i) ans = max(ans, clientArrivals[i] + waitTime[i]);
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 10; int Arg3 = 21; verify_case(0, Arg3, minWaitingTime(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; int Arg2 = 50; int Arg3 = 60; verify_case(1, Arg3, minWaitingTime(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {10,10,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 20; int Arg3 = 50; verify_case(2, Arg3, minWaitingTime(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {2,4,6,3,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 10; int Arg3 = 23; verify_case(3, Arg3, minWaitingTime(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    OptimalQueues ___test;
    ___test.run_test(-1);
}
// END CUT HERE
