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

class TreeReconstruct
{
    inline int getInt(char c)
    {
        if (c >= '0' && c <= '9') return c - '0'; else return c - 'A' + 10;
    }
    
public:
    int reconstruct(vector <string> g1, vector <string> g2)
    {
        int N = (int) g1.size();
        vector<vector<int> > dis(N, vector<int>(N, 0));
        
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                dis[i][j] = getInt(g1[i][j]) * 16 + getInt(g2[i][j]);
        
        set<vector<int> > vs;
        for (int i = 0; i < N; ++i)
        {
            vector<int> v;
            for (int j = 0; j < N; ++j) v.push_back(dis[i][j]);
            vs.insert(v);
        }
        
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                for (int k = j + 1; k < N; ++k)
                {
                    int sum = dis[i][j]+ dis[i][k] + dis[k][j];
                    if (sum % 2 != 0) return -1;
                    sum /= 2;
                    int da = sum - dis[j][k];
                    int db = sum - dis[i][k];
                    int dc = sum - dis[i][j];
                    
                    vector<int> v;
                    for (int l = 0; l < N; ++l)
                    {
                        int ae = dis[i][l];
                        int be = dis[j][l];
                        int ce = dis[k][l];
                        if (ae - da == be - db && be - db == ce - dc && ce - dc >= 0)
                        {
                            v.push_back(ae - da);
                            continue;
                        }
                        if (ae - da == be - db && ae - da >= 0 && (ae - da + dc >= ce))
                        {
                            v.push_back(ae - da);
                            continue;
                        }
                        
                        if (be - db == ce - dc && be - db >= 0 && (be - db + da >= ae))
                        {
                            v.push_back(be - db);
                            continue;
                        }
                        
                        if (ae - da == ce - dc && ae - da >= 0 && (ae - da + db >= be))
                        {
                            v.push_back(ae - da);
                            continue;
                        }
                        return -1;
                    }
                    vs.insert(v);
                }
        
        return (int) vs.size();
    }
    
    // BEGIN CUT HERE
public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { string Arr0[] = {"0000",
        "0000",
        "0000",
        "0000"}
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0444",
            "4044",
            "4404",
            "4440"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(0, Arg2, reconstruct(Arg0, Arg1)); }
    void test_case_1() { string Arr0[] = {"0000",
        "0000",
        "0000",
        "0000"}
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0233",
            "2033",
            "3302",
            "3320"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(1, Arg2, reconstruct(Arg0, Arg1)); }
    void test_case_2() { string Arr0[] = {"00001",
        "00001",
        "00011",
        "00100",
        "11100"}
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"066C6",
            "60CA4",
            "6C02C",
            "CA20A",
            "64CA0"}
        ; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(2, Arg2, reconstruct(Arg0, Arg1)); }
    void test_case_3() { string Arr0[] = {"00000",
        "00000",
        "00001",
        "00000",
        "00100"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"06839",
            "60E7B",
            "8E0B1",
            "37B0A",
            "9B1A0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(3, Arg2, reconstruct(Arg0, Arg1)); }
    void test_case_4() { string Arr0[] = {"023825",
        "202704",
        "320633",
        "876084",
        "203805",
        "543450"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0198AA",
            "10ED9F",
            "9E0D7F",
            "8DD06E",
            "A97608",
            "AFFE80"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(4, Arg2, reconstruct(Arg0, Arg1)); }
    void test_case_5() { string Arr0[] = {"0000",
        "0000",
        "0000",
        "0000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0121",
            "1012",
            "2101",
            "1210"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(5, Arg2, reconstruct(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    TreeReconstruct ___test;
    ___test.run_test(-1);
}
// END CUT HERE
