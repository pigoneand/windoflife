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

int N;
bool caled[200][200];
double f[200][200];
const double INFI = 1e30;
int T[200];
int W[200];
int maxWaitTime;

double getF(int curTime, int maxSkip)
{
    if (curTime >= maxWaitTime) return INFI;
    if (maxSkip == 0) return INFI;
    
    if (caled[curTime][maxSkip]) return f[curTime][maxSkip];
    caled[curTime][maxSkip] = true;
    
    double & ret = f[curTime][maxSkip];
    ret = 0;
    double allNotCome = 1.0;
    for (int i = 0; i < maxSkip; ++i)
    {
        int remain = W[i] - curTime;
        double pCome = remain > 0 ? 1.0 / remain : 0;
        double pNotCome = 1 - pCome;
        double pHappen = allNotCome * pCome;
        allNotCome *= pNotCome;
        
        ret += pHappen * min(curTime + T[i] * 1.0 , getF(curTime + 1, i));
    }
    ret += allNotCome * getF(curTime + 1, maxSkip);
    return ret;
}

class TakeBus
{
public:
    double expectedTime(vector <int> tripTime, vector <int> waitTime)
    {
        vector<pair<int, int> > sortT;
        N = (int) tripTime.size();
        for (int i = 0; i < N; ++i)
            sortT.push_back(make_pair(tripTime[i], waitTime[i]));
        sort(sortT.begin(), sortT.end());
        
        maxWaitTime = 0;
        for (int i = 0; i < N; ++i)
        {
            T[i] = sortT[i].first;
            W[i] = sortT[i].second;
            maxWaitTime = max(maxWaitTime, sortT[i].second);
        }
        memset(caled, false, sizeof(caled));
        
        return getF(0, N);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 5.5; verify_case(0, Arg2, expectedTime(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {100, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 9.5; verify_case(1, Arg2, expectedTime(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {6, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 5.9; verify_case(2, Arg2, expectedTime(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {100, 100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 100.33333333333333; verify_case(3, Arg2, expectedTime(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    TakeBus ___test;
    ___test.run_test(-1);
}
// END CUT HERE
