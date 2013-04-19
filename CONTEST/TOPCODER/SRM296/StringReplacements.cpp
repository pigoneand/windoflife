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

// a => "acb"
// b => "baa"
// c => "bcb"

int trans[3][3] = { {0, 2, 1}, {1, 0, 0}, {1, 2, 1} };

struct State
{
    char ori;
    int sec;
    long long cnt[3];
    long long sum;
    State(int c)
    {
        cnt[0] = cnt[1] = cnt[2] = 0;
        sec = 0;
        cnt[c]++;
        sum = 1;
    }
    
    State()
    {
        
    }
    
    State expand()
    {
        State ret = *this;
        ret.cnt[0] = cnt[0] + 2 * cnt[1];
        ret.cnt[1] = cnt[0] + cnt[1] + 2 * cnt[2];
        ret.cnt[2] = cnt[0] + cnt[2];
        ret.sec++;
        ret.sum *= 3;
        return ret;
    }
};

State cnt[3][30];

class StringReplacements
{
public:
    
    vector<int> getABC(int curC, int curSec, long long remain)
    {
        //cout << curC << " " << curSec << " " << remain << endl;
        vector<int> ret(3, 0);
        while (remain > 0)
        {
            if (cnt[curC][curSec].sum == remain)
            {
                remain = 0;
                for (int i = 0; i < 3; ++i) ret[i] += cnt[curC][curSec].cnt[i];
            }
            else
            {
                long long pSum = cnt[curC][curSec].sum / 3;
                int nextOffset = 0;
                for (int i = 0; i < 2; ++i)
                {
                    if (remain >= pSum)
                    {
                        remain -= pSum;
                        for (int j = 0; j < 3; ++j) ret[j] += cnt[trans[curC][i]][curSec - 1].cnt[j];
                        nextOffset++;
                    }
                }
                curSec--;
                curC = trans[curC][nextOffset];
            }
        }
        return ret;
    }
    
    vector <int> substringCounter(string letter, long long left, long long right, int nSeconds)
    {
        cnt[0][0] = State(0);
        cnt[1][0] = State(1);
        cnt[2][0] = State(2);
        
        for (int i = 1; i <= 20; ++i)
            for (int j = 0; j < 3; ++j)
                cnt[j][i] = cnt[j][i - 1].expand();
        
        vector<int> ans1 = getABC(letter[0] - 'a', nSeconds, right + 1);
        vector<int> ans2 = getABC(letter[0] - 'a', nSeconds, left);
        vector<int> ans(3, 0);
        for (int i = 0; i < 3; ++i) ans[i] = ans1[i] - ans2[i];
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "a"; int Arg1 = 0; int Arg2 = 2147483647; int Arg3 = 20; int Arr4[] = {0, 4, 1 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(0, Arg4, substringCounter(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arg0 = "a"; int Arg1 = 0; int Arg2 = 2; int Arg3 = 1; int Arr4[] = {1, 1, 1 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(1, Arg4, substringCounter(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arg0 = "c"; int Arg1 = 1; int Arg2 = 4; int Arg3 = 2; int Arr4[] = {2, 1, 1 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(2, Arg4, substringCounter(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arg0 = "b"; int Arg1 = 4; int Arg2 = 12; int Arg3 = 3; int Arr4[] = {2, 4, 3 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(3, Arg4, substringCounter(Arg0, Arg1, Arg2, Arg3)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    StringReplacements ___test;
    ___test.run_test(-1);
}
// END CUT HERE
