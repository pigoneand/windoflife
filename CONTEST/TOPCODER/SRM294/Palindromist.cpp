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

class Palindromist
{
public:
    
    bool isLess(const vector<int>& l1, const vector<int>& l2)
    {
        if (l2.empty()) return true;
        for (int i = 0; i < l1.size() && i < l2.size(); ++i)
        {
            if (l1[i] < l2[i]) return true;
            if (l1[i] > l2[i]) return false;
        }
        return false;
    }
    
    string solve(const string& s, vector<string>& words)
    {
        int N = (int) s.length();
        vector<vector<int> > f(N, vector<int>());
        vector<bool> hasS(N, false);
        
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                string curWord = s.substr(j, i - j + 1);
                bool found = false;
                for (int k = 0; k < words.size(); ++k)
                    if (words[k] == curWord) found = true;
                if (found)
                {
                    if (j > 0 && !hasS[j - 1]) continue;
                    vector<int> lastL = (j > 0 ? f[j - 1] : vector<int>());
                    lastL.push_back(i - j + 1);
                    if (isLess(lastL, f[i])) { f[i] = lastL; hasS[i] = true; }
                }
            }
        }
        
        string result = "";
        int curOffset = 0;
        for (int i = 0; i < f[N - 1].size(); ++i)
        {
            int l = f[N - 1][i];
            result += s.substr(curOffset, l);
            if (i + 1 < f[N - 1].size()) result += " ";
            curOffset += l;
        }
        return result;
    }
    
    string palindrome(string text, vector <string> words)
    {
        string revtext = text;
        reverse(revtext.begin(), revtext.end());
        
        //cout << revtext << endl;
        string ans1 = solve(text + revtext, words);
        string ans2 = solve(text + revtext.substr(1), words);
        if (ans1.empty()) return ans2;
        if (ans2.empty()) return ans1;
        return ans1 < ans2 ? ans1 : ans2;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "AMANAPLANAC"; string Arr1[] = { "A", "CANAL", "MAN", "PANAMA", "PLAN" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "A MAN A PLAN A CANAL PANAMA"; verify_case(0, Arg2, palindrome(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "AAAAA"; string Arr1[] = { "AA", "A", "AAA" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "A A A A A A A A A"; verify_case(1, Arg2, palindrome(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "CBA"; string Arr1[] = { "CBABC", "CBAABC" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "CBAABC"; verify_case(2, Arg2, palindrome(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "RACEFAST"; string Arr1[] = { "AR", "CAR", "FAST", "RACE", "SAFE", "CEFA", "ACE", "STTS", "AFEC" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "RACE FAST SAFE CAR"; verify_case(3, Arg2, palindrome(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "AABAABA"; string Arr1[] = { "AA", "AAB", "BAA", "BAB" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "AA BAA BAA BAA BAA"; verify_case(4, Arg2, palindrome(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "STRAWNOTOOSTUPIDAF"; string Arr1[] = { "WARTS", "I", "TOO", "A", "FAD", "STUPID", "STRAW", "PUT", "NO", "ON", "SOOT" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "STRAW NO TOO STUPID A FAD I PUT SOOT ON WARTS"; verify_case(5, Arg2, palindrome(Arg0, Arg1)); }
	void test_case_6() { string Arg0 = "AAAAA"; string Arr1[] = { "AAAA" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = ""; verify_case(6, Arg2, palindrome(Arg0, Arg1)); }
	void test_case_7() { string Arg0 = "A"; string Arr1[] = { "A", "AA" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "A"; verify_case(7, Arg2, palindrome(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    Palindromist ___test;
    ___test.run_test(-1);
}
// END CUT HERE
