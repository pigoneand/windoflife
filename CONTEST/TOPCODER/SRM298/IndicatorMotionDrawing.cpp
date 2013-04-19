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
#include <queue>
using namespace std;
//END CUT HERE

int N, M;
struct State
{
    int s; /// meet the desiredstate
    int x, y; /// current position
    char c; /// current display
    int cost;
    
    State()
    {
        s = 0;
        x = 0; y = 0;
        c = 0;
        cost = 0;
    }
    
    void set(int x, int y, bool ok)
    {
        int offset = x * M + y;
        if (ok) s |= (1 << offset);
        else s &= ~(1 << offset);
    }
    
    bool get(int x, int y)
    {
        int offset = x * M + y;
        return (s & (1 << offset));
    }
};

bool visit[1 << 12][4][4][128];

class IndicatorMotionDrawing
{
public:
    int getMinSteps(vector <string> desiredState, char startState)
    {
        char chars[4] = { '-', '|', '/', '\\' };
        
        if (desiredState[0][0] == ' ') return -1;
        N = (int) desiredState.size();
        M = (int) desiredState[0].size();
        
        State init;
        init.c = startState;
        init.set(0, 0, init.c == desiredState[0][0]);
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                if (i == 0 && j == 0) continue;
                if (desiredState[i][j] == ' ') init.set(i, j, true);
                else init.set(i, j, false);
            }
        }
        
        memset(visit, false, sizeof(visit));
        visit[init.s][init.x][init.y][init.c] = true;
        queue<State> q;
        q.push(init);
        
        int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        
        while (q.size() > 0)
        {
            State now = q.front();
            q.pop();
            
            /// check find answer or not
            if (now.s == (1 << (N * M)) - 1) return now.cost;
            
            /// try change char
            for (int i = 0; i < 4; ++i)
            {
                State ns = now;
                ns.cost++;
                ns.c = chars[i];
                ns.set(ns.x, ns.y, ns.c == desiredState[ns.x][ns.y]);
                if (!visit[ns.s][ns.x][ns.y][ns.c])
                {
                    visit[ns.s][ns.x][ns.y][ns.c] = true;
                    q.push(ns);
                }
            }
            
            /// try move
            for (int k = 0; k < 4; ++k)
            {
                State ns = now;
                ns.cost++;
                ns.x += dir[k][0];
                ns.y += dir[k][1];
                
                if (ns.x >= 0 && ns.y >= 0 && ns.x < N && ns.y < M && desiredState[ns.x][ns.y] != ' ')
                {
                    ns.set(ns.x, ns.y, ns.c == desiredState[ns.x][ns.y]);
                    if (!visit[ns.s][ns.x][ns.y][ns.c])
                    {
                        visit[ns.s][ns.x][ns.y][ns.c] = true;
                        q.push(ns);
                    }
                }
            }
        }
        
        return -1;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"///",
        "///",
        "---"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = '-'; int Arg2 = 10; verify_case(0, Arg2, getMinSteps(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {" ||",
        "|||",
        "|||"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = '|'; int Arg2 = -1; verify_case(1, Arg2, getMinSteps(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"/- ",
        "/  ",
        "/--"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = '/'; int Arg2 = 9; verify_case(2, Arg2, getMinSteps(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"/-|/",
        "/ |/",
        "-/\\/"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = '\\'; int Arg2 = 18; verify_case(3, Arg2, getMinSteps(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    IndicatorMotionDrawing ___test;
    ___test.run_test(-1);
}
// END CUT HERE
