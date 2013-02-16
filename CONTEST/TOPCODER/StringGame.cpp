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

class StringGame
{
public:
   
    bool couldDefeat(map<char, int> cnt, vector<map<char, int> > cnts)
    {
        if (cnts.size() == 0) return true;
        for (char c = 'a'; c <= 'z'; ++c)
        {
            if (cnt[c] == 0) continue;
            bool isOK = true;
            for (int i = 0; i < cnts.size(); ++i)
                if (cnt[c] <= cnts[i][c])
                    isOK = false;
            if (isOK) return true;
        }
        
        for (char c = 'a'; c <= 'z'; ++c)
        {
            if (cnt[c] == 0) continue;
            bool isOK = true;
            for (int i = 0; i < cnts.size(); ++i)
                if (cnt[c] < cnts[i][c])
                    isOK = false;
         
            if (isOK)
            {
                vector<map<char, int> > newcnts;
                for (int i = 0; i < cnts.size(); ++i)
                    if (cnts[i][c] == cnt[c])
                        newcnts.push_back(cnts[i]);
                cnt[c] = 0;
                return couldDefeat(cnt, newcnts);
            }
        }
        return false;
    }
    
    vector<int> getWinningStrings(vector<string> S)
    {
        int N = (int) S.size();
        vector<int> ans;

        for (int i = 0; i < N; ++i)
        {
            map<char, int> cnt;
            for (int j = 0; j < S[i].length(); ++j) cnt[S[i][j]]++;
            vector<map<char, int> > cnts;
            for (int j = 0; j < N; ++j)
                if (j != i)
                {
                    map<char, int> nowcnt;
                    for (int k = 0; k < S[j].length(); ++k) nowcnt[S[j][k]]++;
                    cnts.push_back(nowcnt);
                }
            
            if (couldDefeat(cnt, cnts)) ans.push_back(i);
        }
        
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"a", "b", "c", "d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getWinningStrings(Arg0)); }
	void test_case_1() { string Arr0[] = {"aabbcc", "aaabbb", "aaaccc"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getWinningStrings(Arg0)); }
	void test_case_2() { string Arr0[] = {"ab", "ba"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getWinningStrings(Arg0)); }
	void test_case_3() { string Arr0[] = {"xaocxsss", "oooxsoas", "xaooosss", "xaocssss", "coxaosxx"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getWinningStrings(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    StringGame ___test;
    ___test.run_test(-1);
}
// END CUT HERE
