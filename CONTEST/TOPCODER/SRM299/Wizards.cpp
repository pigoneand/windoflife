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
#include <functional>
#include <numeric>
using namespace std;
//END CUT HERE

union State
{
    int s;
    char hats[5];
    
    State()
    {
        s = 0;
    }
};
int N;

ostream& operator << (ostream& out, const State& s)
{
    for (int i = 0; i < N; ++i) out << (int) s.hats[i] << " ";
    return out;
}

void genHats(int offset, int goal, vector<int>& curHats, vector<State>& availStates, const vector<int>& maxHats)
{
    if (offset == curHats.size())
    {
        int sum = accumulate(curHats.begin(), curHats.end(), 0);
        if (sum == goal)
        {
            State news;
            for (int i = 0; i < curHats.size(); ++i) news.hats[i] = curHats[i];
            availStates.push_back(news);
        }
    }
    else
    {
        for (curHats[offset] = 0; curHats[offset] <= maxHats[offset]; ++curHats[offset])
            genHats(offset + 1, goal, curHats, availStates, maxHats);
    }
}

class Wizards
{
public:
    int questions(int wizards, vector <int> hats, vector <int> hatsOnWizards)
    {
        N = (int) hats.size();
        
        vector<int> curHats(N, 0);
        vector<State> availStates;
        genHats(0, wizards, curHats, availStates, hats);
        
        State finalState;
        for (int i = 0; i < N; ++i)
            finalState.hats[i] = hatsOnWizards[i];
        //cout << "final = " << finalState << endl;
        
        set<int> couldNotHappenState;
        for (int ans = 1; ; ans++)
        {
            vector<State> couldBeRecognizeStates;
            for (int i = 0; i < availStates.size(); ++i)
            {
                State& s = availStates[i];
                if (couldNotHappenState.count(s.s) > 0) continue;
                
                /// judge this state could be logical judged
                /// for each type of hat, try to guess its color
                bool couldBeRecognize = false;
                for (int c = 0; c < N; ++c)
                {
                    if (s.hats[c] > 0)
                    {
                        int couldBe = 0;
                        /// for each color, could i be this color?
                        for (int nc = 0; nc < N; ++nc)
                        {
                            State ns = s;
                            ns.hats[c]--;
                            ns.hats[nc]++;
                            if (ns.hats[nc] <= hats[nc])
                            {
                                if (couldNotHappenState.count(ns.s) == 0) couldBe++;
                            }
                        }
                        /// this state could be recognize
                        if (couldBe == 1)
                        {
                            couldBeRecognize = true;
                            break;
                        }
                    }
                }
                
                if (couldBeRecognize)
                {
                    //cout << "reco = " << ans << " " << s << endl;
                    if (s.s == finalState.s) return ans;
                    couldBeRecognizeStates.push_back(s);
                }
            }
            
            for (int i = 0; i < couldBeRecognizeStates.size(); ++i)
                couldNotHappenState.insert(couldBeRecognizeStates[i].s);
            if (couldBeRecognizeStates.size() == 0) break;
        }
        
        return -1;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arr1[] = {1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(0, Arg3, questions(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arr1[] = {1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(1, Arg3, questions(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arr1[] = {2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(2, Arg3, questions(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 18; int Arr1[] = {7,8,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5,4,9}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; verify_case(3, Arg3, questions(Arg0, Arg1, Arg2)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    Wizards ___test;
    ___test.run_test(-1);
}
// END CUT HERE
