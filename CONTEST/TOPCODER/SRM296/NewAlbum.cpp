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

class NewAlbum
{
public:
    
    bool couldRecord(int nSongs, int length, int cap)
    {
        int maxSongs = (cap + 1) / (length + 1);
        if (nSongs % 13 == 0) return false;
        return nSongs <= maxSongs;
    }
    
    int leastAmountOfCDs(int nSongs, int length, int cdCapacity)
    {
        vector<int> f(nSongs + 1, 0);
        for (int i = 1; i <= nSongs; ++i)
        {
            f[i] = 99999999;
            for (int j = 1; j <= i; ++j)
                if (couldRecord(j, length, cdCapacity))
                    f[i] = min(f[i], f[i - j] + 1);
        }
        return f[nSongs];
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 7; int Arg1 = 2; int Arg2 = 6; int Arg3 = 4; verify_case(0, Arg3, leastAmountOfCDs(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 20; int Arg1 = 1; int Arg2 = 100; int Arg3 = 1; verify_case(1, Arg3, leastAmountOfCDs(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 26; int Arg1 = 1; int Arg2 = 100; int Arg3 = 2; verify_case(2, Arg3, leastAmountOfCDs(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 26; int Arg1 = 3; int Arg2 = 51; int Arg3 = 3; verify_case(3, Arg3, leastAmountOfCDs(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 67; int Arg1 = 271; int Arg2 = 1000; int Arg3 = 23; verify_case(4, Arg3, leastAmountOfCDs(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 27; int Arg1 = 1; int Arg2 = 27; int Arg3 = 3; verify_case(5, Arg3, leastAmountOfCDs(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    NewAlbum ___test;
    ___test.run_test(-1);
}
// END CUT HERE
