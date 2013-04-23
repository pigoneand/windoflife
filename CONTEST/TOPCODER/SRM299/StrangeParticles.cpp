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

class StrangeParticles
{
public:
    bool g[51][51];
    int N;
    bool visit[51];
    vector<int> order;
    int cid[51];
    
    void dfs(int now)
    {
        visit[now] = true;
        for (int i = 0; i < N; ++i)
            if (g[now][i] && !visit[i])
                dfs(i);
        order.push_back(now);
    }
    
    void dfs2(int now, int id)
    {
        cid[now] = id;
        for (int i = 0; i < N; ++i)
            if (g[i][now] && cid[i] == -1)
                dfs2(i, id);
    }
    
    int remain(vector <string> interacts)
    {
        memset(g, false, sizeof(g));
        N = (int) interacts.size();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (interacts[i][j] == '-')
                    g[i][j] = true;
            }
        
        memset(visit, false, sizeof(visit));
        order.clear();
        for (int i = 0; i < N; ++i)
            if (!visit[i]) dfs(i);
        
        reverse(order.begin(), order.end());
        memset(cid, -1, sizeof(cid));
        int coms = 0;
        for (int i = 0; i < order.size(); ++i)
            if (cid[order[i]] == -1)
            {
                dfs2(order[i], coms);
                coms++;
            }
        
        vector<int> comInDeg(coms, 0);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (g[i][j] && cid[i] != cid[j])
                    comInDeg[cid[j]]++;
        
        return count(comInDeg.begin(), comInDeg.end(), 0);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0+-","-0+","+-0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, remain(Arg0)); }
	void test_case_1() { string Arr0[] = {"000","000","000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, remain(Arg0)); }
	void test_case_2() { string Arr0[] = {"0++++++++++++++",
        "-0+++++++++++++",
        "--0++++++++++++",
        "---0+++++++++++",
        "----0++++++++++",
        "-----0+++++++++",
        "------0++++++++",
        "-------0+++++++",
        "--------0++++++",
        "---------0+++++",
        "----------0++++",
        "-----------0+++",
        "------------0++",
        "-------------0+",
        "--------------0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, remain(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    StrangeParticles ___test;
    ___test.run_test(-1);
} 
// END CUT HERE 
