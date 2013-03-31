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

vector<string> mazeMap;
int H, W;
int dir[4][2] = { {1, 0}, {0, -1}, {0, 1}, {-1, 0} };
char op[4] = {'D', 'L', 'R', 'U'};

struct Maze
{
    int s;
    
    Maze makeMove(int d)
    {
        int ns = 0;
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (s & (1 << (i * W + j)))
                {
                    int ni = i + dir[d][0];
                    int nj = j + dir[d][1];
                    if (ni >= 0 && ni < H && nj >= 0 && nj < W)
                    {
                        if (mazeMap[ni][nj] == 'X')
                        {
                            ni = i;
                            nj = j;
                        }
                    }
                    else
                    {
                        if (d == 1) continue;
                        else
                        {
                            ni = i;
                            nj = j;
                        }
                    }
                    ns |= (1 << (ni * W + nj));
                }
        Maze ret;
        ret.s = ns;
        ret.path = path + op[d];
        return ret;
    }
    
    bool operator < (const Maze& m) const
    {
        return s < m.s;
    }
    
    string path;
};

class BlindMazeSolve
{
public:
    string getSolution(vector <string> maze)
    {
        set<Maze> app;
        queue<Maze> q;
        
        Maze initS;
        initS.s = 0;
        mazeMap = maze;
        H = (int) maze.size();
        W = (int) maze[0].size();
        
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (maze[i][j] == '.')
                    initS.s |= (1 << (i * W + j));
        q.push(initS);
        app.insert(initS);
        
        while (q.size() > 0)
        {
            Maze now = q.front();
            q.pop();
            if (now.s == 0) return now.path;
            
            for (int k = 0; k < 4; ++k)
            {
                Maze news = now.makeMove(k);
                if (app.find(news) == app.end())
                {
                    app.insert(news);
                    q.push(news);
                }
            }
        }
        return "";
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "L"; verify_case(0, Arg1, getSolution(Arg0)); }
	void test_case_1() { string Arr0[] = {
        "..",
        ".."
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LL"; verify_case(1, Arg1, getSolution(Arg0)); }
	void test_case_2() { string Arr0[] = {
        "X..",
        "X..",
        "XXX"
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(2, Arg1, getSolution(Arg0)); }
	void test_case_3() { string Arr0[] = {
        "X...",
        "XXX.",
        "X...",
        "X.XX",
        "..XX"
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "RRDDLLDDLL"; verify_case(3, Arg1, getSolution(Arg0)); }
	void test_case_4() { string Arr0[] = {".XX."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(4, Arg1, getSolution(Arg0)); }
	void test_case_5() { string Arr0[] = {
        "XXX.",
        "..X.",
        "X...",
        "XX..",
        "X..."
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "DDDRULULULL"; verify_case(5, Arg1, getSolution(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    BlindMazeSolve ___test;
    ___test.run_test(-1); 
} 
// END CUT HERE 
