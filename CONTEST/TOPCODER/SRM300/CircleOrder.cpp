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

class CircleOrder
{
public:
    
    bool couldMove(const string& s, int l, int r)
    {
        if (l > r) swap(l, r);
        bool could = true;
        for (int i = l + 1; i < r; ++i)
            if (islower(s[i]) || s[i] == '#') could = false;
        if (could) return true;
        
        could = true;
        for (int i = 0; i < l; ++i)
            if (islower(s[i]) || s[i] == '#') could = false;
        for (int i = r + 1; i < s.length(); ++i)
            if (islower(s[i]) || s[i] == '#') could = false;
        return could;
    }
    
    string firstOrder(string circle)
    {        
        string ans = "";
        while (ans.length() < circle.length() / 2)
        {
            bool found = false;
            for (char c = 'a'; c <= 'z'; ++c)
            {
                int l = find(circle.begin(), circle.end(), c) - circle.begin();
                int r = find(circle.begin(), circle.end(), c - 'a' + 'A') - circle.begin();
                if (l >= 0 && l < circle.length() && r >= 0 && r < circle.length())
                    if (couldMove(circle, l, r))
                    {
                        ans += c;
                        found = true;
                        circle[l] = '.'; circle[r] = '#';
                        break;
                    }
            }
            if (!found) return "NONE";
        }
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "BACacb"; string Arg1 = "abc"; verify_case(0, Arg1, firstOrder(Arg0)); }
	void test_case_1() { string Arg0 = "ABCacb"; string Arg1 = "NONE"; verify_case(1, Arg1, firstOrder(Arg0)); }
	void test_case_2() { string Arg0 = "XYxPyp"; string Arg1 = "xyp"; verify_case(2, Arg1, firstOrder(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    CircleOrder ___test;
    ___test.run_test(-1);
}
// END CUT HERE
