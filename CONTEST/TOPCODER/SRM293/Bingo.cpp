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
#include <numeric>
#include <functional>
using namespace std;
//END CUT HERE

#define DEBUG 1
#define debug1(x) if (DEBUG) cout << #x" = " << x << endl;
#define debug2(x, y) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

template <class T1, class T2>
ostream & operator << (ostream & out, const pair<T1, T2> & p)
{ out << "(" << p.first << "," << p.second << ")"; return out; }

template <class T>
ostream & operator << (ostream & out, const vector<T> & data)
{ out << "["; for (int i = 0; i < data.size(); ++i) out << data[i] << (i == data.size() - 1 ? "" : ","); out << "]"; return out; }

template <class T>
ostream & operator << (ostream & out, const set<T> & s)
{ out << "{"; for (typename set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

template <class T>
ostream & operator << (ostream & out, const multiset<T> & s)
{ out << "{"; for (typename multiset<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

template <class T1, class T2>
ostream & operator << (ostream & out, const map<T1, T2> & m)
{
    for (typename map<T1, T2>::const_iterator itr = m.begin(); itr != m.end(); ++itr)
        out << itr->first << "->" << itr->second << " ";
    return out;
}

class Bingo
{
public:
    bool s[5][5];
    map<string, pair<int, int> > cmap;
    map<pair<int, int>, string> cmap_rev;
    map<pair<int, int>, int> callseq;
    
    bool isFinish()
    {
        for (int i = 0; i < 5; ++i)
        {
            bool all = true;
            for (int j = 0; j < 5; ++j)
                if (s[i][j] == false) all = false;
            if (all) return true;
        }
        
        for (int j = 0; j < 5; ++j)
        {
            bool all = true;
            for (int i = 0; i < 5; ++i)
                if (s[i][j] == false) all = false;
            if (all) return true;
        }
        
        if (s[0][0] && s[1][1] && s[3][3] && s[4][4]) return true;
        if (s[0][4] && s[1][3] && s[3][1] && s[4][0]) return true;
        return false;
    }
    
    bool isBetterSeq(vector<int>& v, vector<int>& pv)
    {
        if (pv.empty()) return true;
        return v[0] < pv[0];
    }
    
    vector<int> winCallSeqs(int x, int y)
    {
        vector<int> ret;
        
        // test row
        bool ok = true;
        vector<int> nowret;
        for (int j = 0; j < 5; ++j)
        {
            if (!s[x][j]) ok = false;
            else
            {
                if (x != 2 || j != 2) nowret.push_back(callseq[make_pair(x, j)]);
            }
        }
        sort(nowret.begin(), nowret.end());
        if (ok && isBetterSeq(nowret, ret)) ret = nowret;
        
        // test col
        ok = true;
        nowret.clear();
        for (int i = 0; i < 5; ++i)
        {
            if (!s[i][y]) ok = false;
            else
            {
                if (i != 2 || y != 2) nowret.push_back(callseq[make_pair(i, y)]);
            }
        }
        sort(nowret.begin(), nowret.end());
        if (ok && isBetterSeq(nowret, ret)) ret = nowret;
        
        // test dag
        ok = true;
        nowret.clear();
        for (int i = 0; i < 5; ++i)
        {
            if (!s[i][i]) ok = false;
            else
            {
                if (i != 2) nowret.push_back(callseq[make_pair(i, i)]);
            }
        }
        sort(nowret.begin(), nowret.end());
        if (ok && isBetterSeq(nowret, ret)) ret = nowret;
        
        ok = true;
        nowret.clear();
        for (int i = 0; i < 5; ++i)
        {
            if (!s[i][4 - i]) ok = false;
            else
            {
                if (i != 2) nowret.push_back(callseq[make_pair(i, 4 - i)]);
            }
        }
        sort(nowret.begin(), nowret.end());
        if (ok && isBetterSeq(nowret, ret)) ret = nowret;
        
        return ret;
    }
    
    string winner(vector <string> card, vector <string> calls)
    {
        memset(s, false, sizeof(s));
        s[2][2] = true;
        cmap.clear(); cmap_rev.clear(); callseq.clear();
        
        string bingo = "BINGO";
        for (int i = 1; i <= 5; ++i)
        {
            istringstream isin(card[i]);
            //cout << card[i] << endl;
            for (int j = 1; j <= 5; ++j)
            {
                string num;
                isin >> num;
                string nowcard = string("") + bingo[j - 1] + num;
                cmap[nowcard] = make_pair(i - 1, j - 1);
                cmap_rev[make_pair(i - 1, j - 1)] = nowcard;
            }
        }
        
        for (int i = 0; i < calls.size(); ++i)
        {
            if (calls[i] == "BINGO") return "YOU LOSE";
            if (cmap.find(calls[i]) == cmap.end()) continue;
            pair<int, int> nowposi = cmap[calls[i]];

            s[nowposi.first][nowposi.second] = true;
            callseq[nowposi] = i;
            
            if (isFinish())
            {
                vector<int> seq = winCallSeqs(nowposi.first, nowposi.second);
                string ans = "";
                for (int j = 0; j < seq.size(); ++j)
                    ans = ans + calls[seq[j]] + ",";
                return ans.substr(0, ans.length() - 1);
            }
        }
        
        return "YOU LOSE";
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { "  B  I  N  G  O",
        " 12 22 33 55 66",
        "  9 23 34 52 72",
        "  1 24  F 59 71",
        "  4 16 40 48 61",
        "  3 18 41 49 63"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"B12","B3","I16","N40","B2","O70","B1","B9","O71","B4","B7","B11","O68","BINGO"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "B12,B3,B1,B9,B4"; verify_case(0, Arg2, winner(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = { "  B  I  N  G  O",
        " 12 22 33 55 66",
        "  9 23 34 52 72",
        "  1 24  F 59 71",
        "  4 16 40 48 61",
        "  3 18 41 49 63"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"B12","B3","I16","N40","B2","O70","B1","B9","BINGO"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "YOU LOSE"; verify_case(1, Arg2, winner(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = { "  B  I  N  G  O",
        " 12 22 33 55 66",
        "  9 23 34 52 72",
        "  1 24  F 59 71",
        "  4 16 40 48 61",
        "  3 18 41 49 63"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"O63","G48","I23","B9","B1","B4","B3","B7","B12","G49","BINGO"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "O63,G48,I23,B12"; verify_case(2, Arg2, winner(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    Bingo ___test;
    ___test.run_test(-1);
}
// END CUT HERE
