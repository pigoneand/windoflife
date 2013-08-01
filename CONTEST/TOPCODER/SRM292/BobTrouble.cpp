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

class BobTrouble
{
public:
    
    bool check(vector<vector<bool> >& isBoss)
    {
        int N = (int) isBoss.size();
        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    isBoss[i][j] = isBoss[i][j] || (isBoss[i][k] && isBoss[k][j]);
        
        for (int i = 0; i < N; ++i)
            if (isBoss[i][i]) return false;
        return true;
    }
    
    int minSupers(vector <string> name, vector <string> bossName)
    {
        int N = (int) name.size();
        
        map<string, int> nameMap;
        for (int i = 0; i < name.size(); ++i) nameMap[name[i]] = i;
        
        int ans = N + 1;
        
        if (nameMap.find("BOB") == nameMap.end())
        {
            vector<vector<bool> > isBoss(N, vector<bool>(N, false));
            set<int> bosses;
            for (int j = 0; j < name.size(); ++j)
            {
                if (bossName[j] == "*") continue;
                int bossID = nameMap[bossName[j]];
                isBoss[bossID][j] = true;
                bosses.insert(bossID);
            }
            
            if (check(isBoss))
                ans = min(ans, (int) bosses.size());
        }
        
        for (int i = 0; i < name.size(); ++i)
        {
            if (name[i] == "BOB")
            {
                nameMap["BOB"] = i;
                
                vector<vector<bool> > isBoss(N, vector<bool>(N, false));
                set<int> bosses;
                for (int j = 0; j < name.size(); ++j)
                {
                    if (bossName[j] == "*") continue;
                    int bossID = nameMap[bossName[j]];
                    isBoss[bossID][j] = true;
                    bosses.insert(bossID);
                }
                
                if (check(isBoss))
                    ans = min(ans, (int) bosses.size());
                //cout << check(isBoss) << endl;
            }
        }
        
        if (ans == N + 1) return -1; else return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BOB","BOB","BOB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"BOB","*","BOB"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, minSupers(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"JOHN","AL","DON","BOB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"*","*","*","*"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, minSupers(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"BOB","BOB","BOB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"*","*","BOB"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, minSupers(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"BOB", "BOB", "J", "K"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"K", "J", "BOB", "J"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(3, Arg2, minSupers(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    BobTrouble ___test;
    ___test.run_test(-1);
}
// END CUT HERE
