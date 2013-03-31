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

class SeparateConnections
{
public:
    map<int, int> f;
    vector<string> m;
    int N;
    
    int getF(int state)
    {
        if (f.find(state) != f.end()) return f[state];
        int & ret = f[state];
        
        ret = 0;
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                if (state & (1 << i))
                    if (state & (1 << j))
                        if (m[i][j] == 'Y')
                            ret = max(ret, 2 + getF(state - (1 << i) - (1 << j)));
        return ret;
    }
    
    int howMany(vector<string> mat)
    {
        f.clear();
        m = mat;
        N = (int) mat.size();
        
        return getF((1 << N) - 1);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
        "NYYYY",
        "YNNNN",
        "YNNNN",
        "YNNNN",
        "YNNNN"
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, howMany(Arg0)); }
	void test_case_1() { string Arr0[] = {
        "NYYYY",
        "YNNNN",
        "YNNNY",
        "YNNNY",
        "YNYYN"
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, howMany(Arg0)); }
	void test_case_2() { string Arr0[] = {
        "NNYYYYYYYYYYYYYYYY",
        "NNYYYYYYYYYYYYYYYY",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN",
        "YYNNNNNNNNNNNNNNNN"
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, howMany(Arg0)); }
	void test_case_3() { string Arr0[] = {
        "NNNNNNNNNYNNNNNYN",
        "NNNNNNNNNNNNNNNNN",
        "NNNNNNNYNNNNNNNNN",
        "NNNNNYNNNNNYNNYYY",
        "NNNNNNNNNNNNNNNYN",
        "NNNYNNNNNNNNNNYNN",
        "NNNNNNNNNYNNNNNNN",
        "NNYNNNNNNNNNNNNNN",
        "NNNNNNNNNYNNNNNNN",
        "YNNNNNYNYNNNNNNNY",
        "NNNNNNNNNNNNNNNNN",
        "NNNYNNNNNNNNNNNNN",
        "NNNNNNNNNNNNNNNNN",
        "NNNNNNNNNNNNNNNNN",
        "NNNYNYNNNNNNNNNNN",
        "YNNYYNNNNNNNNNNNN",
        "NNNYNNNNNYNNNNNNN"
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, howMany(Arg0)); }
    
    // END CUT HERE
    
}; 

// BEGIN CUT HERE 
int main()
{
    SeparateConnections ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE 
