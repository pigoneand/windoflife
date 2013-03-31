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

long long f[1001][1001];

class NumPermutationOrders
{
public:
    vector<int> primes;
    void genPrime()
    {
        primes.clear();
        vector<bool> isP(1000, true);
        for (int i = 2; i < 1000; ++i)
            if (isP[i])
            {
                primes.push_back(i);
                for (int j = i + i; j < 1000; j += i) isP[j] = false;
            }
        return;
    }
    
    long long getF(int remain, int offset)
    {
        if (offset >= primes.size()) return 1;
        if (f[remain][offset] >= 0) return f[remain][offset];
        
        long long & ret = f[remain][offset];
        int nowp = primes[offset];
        ret = 0;
        while (nowp <= remain)
        {
            ret += getF(remain - nowp, offset + 1);
            nowp *= primes[offset];
        }
        ret += getF(remain, offset + 1);
        return ret;
    }
    
    long long howMany(int n)
    {
        genPrime();
        
        memset(f, -1, sizeof(f));
        return getF(n, 0);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; long long Arg1 = 1LL; verify_case(0, Arg1, howMany(Arg0)); }
	void test_case_1() { int Arg0 = 2; long long Arg1 = 2LL; verify_case(1, Arg1, howMany(Arg0)); }
	void test_case_2() { int Arg0 = 3; long long Arg1 = 3LL; verify_case(2, Arg1, howMany(Arg0)); }
	void test_case_3() { int Arg0 = 4; long long Arg1 = 4LL; verify_case(3, Arg1, howMany(Arg0)); }
	void test_case_4() { int Arg0 = 10; long long Arg1 = 16LL; verify_case(4, Arg1, howMany(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    NumPermutationOrders ___test;
    ___test.run_test(-1);
}
// END CUT HERE
