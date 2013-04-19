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


bool visit[1001];
bool g[1001][1001];

class OrderDoesMatter
{
public:
    
    vector<int> path;
    void dfs(int now)
    {
        visit[now] = true;
        path.push_back(now);
        for (int j = 1; j <= 1000; ++j)
            if ((g[now][j] || g[j][now]) && !visit[j])
                dfs(j);
    }
    
    int getOrder(vector <int> a, vector <int> b)
    {
        memset(g, false, sizeof(g));
        memset(visit, false, sizeof(visit));
        path.clear();
        
        vector<int> inDeg(1001, 0);
        vector<int> outDeg(1001, 0);
        vector<int> apps;
        
        // get graph and in-out degree
        int N = (int) a.size();
        for (int i = 0; i < N; ++i)
        {
            outDeg[a[i]]++;
            inDeg[b[i]]++;
            g[a[i]][b[i]] = true;
            apps.push_back(a[i]);
            apps.push_back(b[i]);
        }
        sort(apps.begin(), apps.end());
        apps.resize(unique(apps.begin(), apps.end()) - apps.begin());
        
        /// check connected
        dfs(apps[0]);
        sort(path.begin(), path.end());
        if (path != apps) return -1;
        
        /// check euler condition
        vector<int> diffIDs;
        for (int i = 0; i < apps.size(); ++i)
            if (inDeg[apps[i]] != outDeg[apps[i]]) diffIDs.push_back(apps[i]);
        if (diffIDs.size() > 2 || diffIDs.size() == 1) return -1;
        
        /// get ans
        if (diffIDs.size() == 0) return *max_element(a.begin(), a.end()) * (*max_element(b.begin(), b.end()));
        int id1 = diffIDs[0];
        int id2 = diffIDs[1];
        int deg1 = outDeg[id1] - inDeg[id1];
        int deg2 = outDeg[id2] - inDeg[id2];
        if (deg1 * deg2 == -1 && deg1 + deg2 == 0)
        {
            return id1 * id2;
        }
        else return -1;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {7,3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,7,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 49; verify_case(0, Arg2, getOrder(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {3,5,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,1,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(1, Arg2, getOrder(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {3,5,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,2,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, getOrder(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {5,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,5,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(3, Arg2, getOrder(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(4, Arg2, getOrder(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    OrderDoesMatter ___test;
    ___test.run_test(-1);
}
// END CUT HERE
