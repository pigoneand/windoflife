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

class DrawTree
{
public:
    
    vector<vector<int> > childs;
    vector<string> names;
    int N;
    int root;
    
    void output(int now, bool hasSib, const vector<bool>& draw, vector<string>& result)
    {
        // output current node
        ostringstream ostr;
        for (int i = 0; i < draw.size(); ++i)
            if (draw[i])
                ostr << "| ";
            else
                ostr << "  ";
        
        ostr << "+-" << names[now];
        result.push_back(ostr.str());
        
        int cSize = (int) childs[now].size();
        for (int i = 0; i < cSize; ++i)
        {
            vector<bool> newDraw = draw;
            newDraw.push_back(hasSib);
            if (i < cSize - 1)
                output(childs[now][i], true, newDraw, result);
            else
                output(childs[now][i], false, newDraw, result);
        }
    }
    
    vector <string> draw(vector <int> parents, vector <string> n)
    {
        names = n;
        N = (int) parents.size();
        childs.assign(N, vector<int>());
        for (int i = 0; i < N; ++i)
            if (parents[i] == -1)
                root = i;
            else
                childs[parents[i]].push_back(i);
        
        vector<string> result;
        output(root, false, vector<bool>(), result);
        return result;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {-1,0,1,1,0,0,5,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"Root","SubB","LEAF1","LEAF2","LEAF3","SubA","LEAF4","LEAF5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-Root", "  +-SubB", "  | +-LEAF1", "  | +-LEAF2", "  +-LEAF3", "  +-SubA", "    +-LEAF4", "    +-LEAF5" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, draw(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,2,3,4,5,6,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A","B","C","D","E","F","G"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-G", "  +-F", "    +-E", "      +-D", "        +-C", "          +-B", "            +-A" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, draw(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,4,6,6,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A","B","C","D","E","F","G"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-G", "  +-E", "  | +-D", "  |   +-C", "  |     +-B", "  |       +-A", "  +-F" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, draw(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {6,2,3,4,5,6,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A","B","C","D","E","F","G"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-G", "  +-A", "  +-F", "    +-E", "      +-D", "        +-C", "          +-B" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, draw(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {-1,0,1,1,2,2,3,3,0,8,8,9,9,10,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"+-A", "  +-B", "  | +-C", "  | | +-E", "  | | +-F", "  | +-D", "  |   +-G", "  |   +-H", "  +-I", "    +-J", "    | +-L", "    | +-M", "    +-K", "      +-N", "      +-O" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, draw(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    DrawTree ___test;
    ___test.run_test(-1);
}
// END CUT HERE
