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

class VideoEncode
{
public:
    double bitrate(string length, int desiredSize)
    {
        int h, m, s;
        sscanf(length.data(), "%d:%d:%d", &h, &m, &s);
        double t = h * 3600 + m * 60 + s;
        double l = 1.0 * desiredSize * 1024 * 1024 * 8;
        return l / t / 1000;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "00:00:01"; int Arg1 = 50; double Arg2 = 419430.4; verify_case(0, Arg2, bitrate(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "20:59:59"; int Arg1 = 8000; double Arg2 = 887.695128242437; verify_case(1, Arg2, bitrate(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "02:00:00"; int Arg1 = 4000; double Arg2 = 4660.337777777778; verify_case(2, Arg2, bitrate(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "20:59:59"; int Arg1 = 50; double Arg2 = 5.548094551515232; verify_case(3, Arg2, bitrate(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "00:00:01"; int Arg1 = 8000; double Arg2 = 6.7108864E7; verify_case(4, Arg2, bitrate(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    VideoEncode ___test;
    ___test.run_test(-1);
}
// END CUT HERE
