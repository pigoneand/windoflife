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

const long long INFI = 1000000000LL * 1000000000LL;
class SkiResorts
{
public:
    long long minCost(vector<string> r, vector<int> h)
    {
        int N = (int) r.size();
        vector<vector<long long> > f(N, vector<long long>(N, INFI));
        vector<vector<bool> > visit(N, vector<bool>(N, false));
        f[0][0] = 0;
        for (int i = 0; i < N; ++i) f[0][i] = abs(h[i] - h[0]);
        
        while (true)
        {
            long long minDis = INFI;
            int nowid = -1, nowhid = -1;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    if (!visit[i][j] && f[i][j] < minDis)
                    {
                        minDis = f[i][j];
                        nowid = i;
                        nowhid = j;
                    }
            
            if (minDis == INFI) break;
            visit[nowid][nowhid] = true;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    if (!visit[i][j])
                        {
                            if (i == nowid) continue;
                            if (r[nowid][i] != 'Y') continue;
                            if (h[nowhid] < h[j]) continue;
                            long long nowCost = abs(h[i] - h[j]);
                            if (f[nowid][nowhid] + nowCost < f[i][j]) f[i][j] = f[nowid][nowhid] + nowCost;
                        }
        }
        
        long long ans = INFI;
        for (int i = 0; i < N; ++i) ans = min(ans, f[N - 1][i]);
        if (ans == INFI) return -1; else return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN",
        "YNY",
        "NYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {30, 20, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(0, Arg2, minCost(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"NY",
        "YN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 10LL; verify_case(1, Arg2, minCost(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"NYN",
        "YNN",
        "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {573, 573, 573}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = -1LL; verify_case(2, Arg2, minCost(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"NNYNNYYYNN",
        "NNNNYNYNNN",
        "YNNNNYYNNN",
        "NNNNNNYNYY",
        "NYNNNNNNYY",
        "YNYNNNNYNN",
        "YYYYNNNYNN",
        "YNNNNYYNNN",
        "NNNYYNNNNN",
        "NNNYYNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 4, 13, 2, 8, 1, 8, 15, 5, 15}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 12LL; verify_case(3, Arg2, minCost(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    SkiResorts ___test;
    ___test.run_test(-1);
} 
// END CUT HERE 
