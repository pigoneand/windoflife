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

struct Segment
{
    int l;
    int r;
    int ones;
    int zeros;
    double f;
};


Segment merge(const Segment& a, const Segment& b)
{
    Segment ret;
    ret.l = a.l;
    ret.r = b.r;
    ret.ones = a.ones + b.ones;
    ret.zeros = a.zeros + b.zeros;
    ret.f = 1.0 * ret.ones / (ret.ones + ret.zeros);
    return ret;
}

class MonotoneSEMin
{
public:
    double min(vector<string> bits)
    {
        string s = "";
        for (int i = 0; i < bits.size(); ++i)
            s += bits[i];
        
        vector<Segment> segs;
        for (int i = 0; i < s.size(); ++i)
        {
            Segment seg;
            seg.l = seg.r = i;
            seg.ones = (s[i] == '1' ? 1 : 0);
            seg.zeros = (s[i] == '0' ? 1 : 0);
            seg.f = 1.0 * seg.ones / (seg.ones + seg.zeros);
            segs.push_back(seg);
        }
        
        bool found = false;
        do
        {
            vector<Segment> newsegs;
            found = false;
            
            for (int i = 0; i < segs.size(); ++i)
            {
                if (i + 1 < segs.size() && segs[i].f > segs[i + 1].f)
                {
                    newsegs.push_back(merge(segs[i], segs[i + 1]));
                    i++;
                    found = true;
                }
                else
                    newsegs.push_back(segs[i]);
            }
            segs = newsegs;
        } while (found);
        
        double ans = 0;
        for (int i = 0; i < segs.size(); ++i)
        {
            for (int x = segs[i].l; x <= segs[i].r; ++x)
                ans += (segs[i].f - (s[x] - '0')) * (segs[i].f - (s[x] - '0'));
        }
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"10001110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.5; verify_case(0, Arg1, min(Arg0)); }
	void test_case_1() { string Arr0[] = {"00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(1, Arg1, min(Arg0)); }
	void test_case_2() { string Arr0[] = {"11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.0; verify_case(2, Arg1, min(Arg0)); }
	void test_case_3() { string Arr0[] = {"1010100101010101001010101001",
        "0101010100100010010001010101",
        "1110110101001011010111011011",
        "1010111101110110111000111100"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 26.244842801985662; verify_case(3, Arg1, min(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    MonotoneSEMin ___test;
    ___test.run_test(-1);
}
// END CUT HERE
