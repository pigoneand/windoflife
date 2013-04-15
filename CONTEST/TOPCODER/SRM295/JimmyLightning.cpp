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

vector<pair<int, int> > ds[100];
int f[1001];

class JimmyLightning
{
public:
    bool couldStolen(int t, int room, vector<int> doors)
    {
        for (int i = 0; i < room; ++i)
            if (t >= doors[i]) return false;
        return true;
    }
    
    int robTheBank(vector<int> doors, vector<string> diamonds)
    {
        int N = (int) doors.size();
        for (int i = 0; i < 100; ++i) ds[i].clear();
        
        /// read diamonds
        for (int i = 0; i < diamonds.size(); ++i)
        {
            istringstream istr(diamonds[i]);
            int value, time, room;
            istr >> value >> time >> room;
            ds[room].push_back(make_pair(value, time));
        }
        
        /// max value could get in time i
        memset(f, 0, sizeof(f));
        int maxT = doors[0];
        for (int t = 1; t <= maxT; ++t)
        {
            for (int r = 1; r <= N; ++r)
            {
                if (couldStolen(t, r, doors))
                {
                    for (int d = 0; d < ds[r].size(); ++d)
                    {
                        int value = ds[r][d].first;
                        int time = ds[r][d].second;
                        if (t - time >= 0)
                            f[t] = max(f[t], f[t - time] + value);
                    }
                }
            }
        }
            
        return *max_element(f, f + maxT + 1);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"2 1 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; verify_case(0, Arg2, robTheBank(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"999 1 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, robTheBank(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {10, 5, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1 1 1",
        "2 1 2",
        "3 1 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 14; verify_case(2, Arg2, robTheBank(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    JimmyLightning ___test;
    ___test.run_test(-1);
}
// END CUT HERE
