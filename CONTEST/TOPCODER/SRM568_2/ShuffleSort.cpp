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

class ShuffleSort
{
public:
    
    double getE(const vector<int>& cards)
    {
        int cnt = 0;
        for (int i = 0; i < cards.size(); ++i)
            if (cards[i] == cards[0]) cnt++;
        
        if (cnt == cards.size()) return 0;
        
        double p = 1.0 * cnt / cards.size();
        double q = 1 - p;
        return q / p + getE(vector<int>(cards.begin() + 1, cards.end()));
    }
    
    double shuffle(vector <int> cards)
    {
        sort(cards.begin(), cards.end());
        return 1.0 + getE(cards);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.0; verify_case(0, Arg1, shuffle(Arg0)); }
	void test_case_1() { int Arr0[] = {1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.0; verify_case(1, Arg1, shuffle(Arg0)); }
	void test_case_2() { int Arr0[] = {2,3,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 4.0; verify_case(2, Arg1, shuffle(Arg0)); }
	void test_case_3() { int Arr0[] = {15,16,4,8,42,23}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 16.0; verify_case(3, Arg1, shuffle(Arg0)); }
	void test_case_4() { int Arr0[] = {1,1,1,1,1,1,1,1}
        ; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.0; verify_case(4, Arg1, shuffle(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    ShuffleSort ___test;
    ___test.run_test(-1);
}
// END CUT HERE
