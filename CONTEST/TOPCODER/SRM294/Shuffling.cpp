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

class Shuffling
{
public:
    vector<bool> merge(const vector<bool>& top, const vector<bool>& bot, int K)
    {
        if (K < 0) return merge(bot, top, -K);
        vector<bool> ret;
        int l = 0, r = 0;
        for (int i = 0; i < K; ++i) ret.push_back(top[l++]);
        
        while (l < top.size() || r < bot.size())
        {
            if (r < bot.size()) ret.push_back(bot[r++]);
            if (l < top.size()) ret.push_back(top[l++]);
        }
        return ret;
    }
    
    int position(int cards, vector <int> shuffles)
    {
        int N = (int) cards;
        vector<bool> deck(N, false);
        deck[N - 1] = true;
        
        for (int i = 0; i < shuffles.size(); ++i)
        {
            vector<bool> top(deck.begin(), deck.begin() + N / 2);
            vector<bool> bot(deck.begin() + N / 2, deck.end());
            deck = merge(top, bot, shuffles[i]);
        }
        
        for (int i = 0; i < N; ++i)
            if (deck[i]) return N - 1 - i;
        return -1;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arr1[] = { -2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, position(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 52; int Arr1[] = { 1, 17, 12, 26, 9 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, position(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 10; int Arr1[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(2, Arg2, position(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 100; int Arr1[] = { -50 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 50; verify_case(3, Arg2, position(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 100; int Arr1[] = { -48, -49, -2, 10 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 95; verify_case(4, Arg2, position(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    Shuffling ___test;
    ___test.run_test(-1);
}
// END CUT HERE
