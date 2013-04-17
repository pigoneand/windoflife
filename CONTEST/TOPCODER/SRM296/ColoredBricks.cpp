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
#include <queue>
using namespace std;
//END CUT HERE

inline void rotate1(string& s)
{
    char t = s[0];
    s[0] = s[1]; s[1] = s[2]; s[2] = s[3];
    s[3] = t;
}

inline void rotate2(string & s)
{
    char t = s[0];
    s[0] = s[5];
    s[5] = s[2];
    s[2] = s[4];
    s[4] = t;
}

inline void rotate3(string & s)
{
    char t = s[4];
    s[4] = s[1];
    s[1] = s[5];
    s[5] = s[3];
    s[3] = t;
}

string genstates(string s, vector<string>& ns)
{
    string mins = s;
    for (int i = 0; i < 4; ++i)
    {
        rotate1(s);
        for (int j = 0; j < 4; ++j)
        {
            rotate2(s);
            for (int k = 0; k < 4; ++k)
            {
                rotate3(s);
                if (s < mins) mins = s;
                ns.push_back(s);
            }
        }
    }
    return mins;
}

class ColoredBricks
{
public:
    map<string, string> minState;
    vector<string> mss;
    map<string, int> mssid;
    
    string t;
    void genState(int cur)
    {
        if (cur == 6)
        {
            if (minState.find(t) != minState.end()) return;
            
            vector<string> apps;
            string mins = genstates(t, apps);

            for (int i = 0; i < apps.size(); ++i) 
                minState[apps[i]] = mins;
            mssid[mins] = (int) mss.size();
            mss.push_back(mins);
        }
        else
        {
            for (t[cur] = '0'; t[cur] <= '6'; t[cur]++)
                genState(cur + 1);
        }
    }
    
    int minRepaints(vector <string> bricks)
    {
        minState.clear();
        mss.clear();
        t = string(6, '0');
        genState(0);
        int N = (int) bricks.size();
        
        vector<vector<int> > costs(N, vector<int>(mss.size(), 0));
        vector<vector<string> > changes(N);
        for (int i = 0; i < N; ++i)
        {
            genstates(bricks[i], changes[i]);
            sort(changes[i].begin(), changes[i].end());
            changes[i].resize(unique(changes[i].begin(), changes[i].end()) - changes[i].begin());
            
            for (int j = 0; j < mss.size(); ++j)
            {
                int cost = 999999;
                for (int k = 0; k < changes[i].size(); ++k)
                {
                    int diff = 0;
                    for (int l = 0; l < 6; ++l) if (changes[i][k][l] != mss[j][l]) diff++;
                    cost = min(cost, diff);
                }
                costs[i][j] = cost;
            }
        }
        
        int ans = 999999;
        for (int i = 0; i < mss.size(); ++i)
        {
            int curans = 0;
            for (int j = 0; j < N; ++j)
            {
                curans += costs[j][i];
            }
            ans = min(ans, curans);
        }

        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"012345", "012354"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, minRepaints(Arg0)); }
	void test_case_1() { string Arr0[] = {"012345", "301245"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, minRepaints(Arg0)); }
	void test_case_2() { string Arr0[] = {"012012", "345345"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(2, Arg1, minRepaints(Arg0)); }
	void test_case_3() { string Arr0[] = {"000000", "111111", "222222", "333333"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 18; verify_case(3, Arg1, minRepaints(Arg0)); }
	void test_case_4() { string Arr0[] = {"062413", "041246", "043134", "125611"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(4, Arg1, minRepaints(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    ColoredBricks ___test;
    ___test.run_test(-1);
}
// END CUT HERE
