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

class EllysReversals
{
public:
    int getAns(vector<vector<bool> > g)
    {
        int N = (int) g.size();
        vector<bool> visit(N, false);
        
        int ret = 0;
        for (int i = 0; i < N; ++i)
            if (!visit[i])
            {
                int size = 0;
                for (int j = 0; j < N; ++j)
                    if (g[i][j])
                    {
                        size++;
                        visit[j] = true;
                    }
                ret += size % 2;
            }
        return ret;
    }
    
    bool getLink(string a, string b)
    {
        if (a.length() != b.length()) return false;
        int N = (int) a.length();
        
        if (N % 2 == 1 && a[N - 1] != b[N - 1]) return false;
        if (N == 1) return true;
        
        map<string, int> cnta, cntb;
        for (int i = 0; i < N; i += 2)
        {
            string sa = a.substr(i, 2);
            string sb = b.substr(i, 2);
            if (sa[0] > sa[1]) swap(sa[0], sa[1]);
            if (sb[0] > sb[1]) swap(sb[0], sb[1]);
            cnta[sa]++;
            cntb[sb]++;
        }
        
        for (map<string, int>::iterator itr = cnta.begin(); itr != cnta.end(); ++itr)
            if (cntb[itr->first] != itr->second) return false;
        for (map<string, int>::iterator itr = cntb.begin(); itr != cntb.end(); ++itr)
            if (cnta[itr->first] != itr->second) return false;
        return true;
    }
    
    int getMin(vector <string> words)
    {
        int N = (int) words.size();
        vector<vector<bool> > g(N, vector<bool>(N, false));
        
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                g[i][j] = getLink(words[i], words[j]);
                //cout << words[i] << " " << words[j] << " " << g[i][j] << endl;
            }
        
        return getAns(g);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"esprit", "god", "redotopc", "odcpoter", "dog"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, getMin(Arg0)); }
	void test_case_1() { string Arr0[] = {"no", "zaphod", "just", "very", "improbable"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(1, Arg1, getMin(Arg0)); }
	void test_case_2() { string Arr0[] = {"rats", "live", "stressed", "to", "act", "as", "star", "desserts", "of", "evil", "cat", "sa", "fo", "ot"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, getMin(Arg0)); }
	void test_case_3() { string Arr0[] = {"topcoder", "redocpot", "doretopc", "cpotdoer", "harlemshake"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, getMin(Arg0)); }
	void test_case_4() { string Arr0[] = {"iprlzgukfggzg", "bmhxvjbrtkbxy", "khapjiabbny", "nqlwgmcyvdikt",
        "nxromtvtpug", "leealcapovm", "ushnxwjczczbmd", "bwhykzupcux",
        "xrlboyuwlnsp", "bbjoketeheezfs", "dxfztrldomjqkv", "dkbktqdtgfujcut",
        "zfybzyuxgpnt", "ffmsldrdftode", "vopuufksxd", "pqhbsiujwda",
        "yhwbkzupcux", "hkbabnapjiy", "zqsqefrrzehtxn", "yovinyguyudmv"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(4, Arg1, getMin(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    EllysReversals ___test;
    ___test.run_test(-1);
}
// END CUT HERE
