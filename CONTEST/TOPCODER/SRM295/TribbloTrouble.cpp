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

struct SquareMatrix
{
    int N;
    vector<vector<double> > m;
    
    SquareMatrix(int _N)
    {
        N = _N;
        m.assign(N, vector<double>(N, 0));
    }
    
    SquareMatrix operator* (const SquareMatrix& m2)
    {
        SquareMatrix ret(N);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < N; ++k)
                    ret.m[i][j] += m[i][k] * m2.m[k][j];
        return ret;
    }
    
    SquareMatrix()
    {
        N = 0;
    }
    
    SquareMatrix power(int power)
    {
        SquareMatrix ret(N);
        for (int i = 0; i < N; ++i) ret.m[i][i] = 1;
        
        SquareMatrix now = *this;
        while (power > 0)
        {
            if (power & 1) ret = ret * now;
            now = now * now;
            power >>= 1;
        }
        return ret;
    }
    
    friend ostream& operator << (ostream& out, const SquareMatrix& m)
    {
        for (int i = 0; i < m.N; ++i)
        {
            for (int j = 0; j < m.N; ++j)
                out << m.m[i][j] << "\t";
            out << endl;
        }
        return out;
    }
};

struct StochasticProcess
{
    int N;
    SquareMatrix transMatrix; /// prob of state i transfer to state j
    
    StochasticProcess(int _N)
    {
        N = _N;
        transMatrix = SquareMatrix(N);
    }
    
    void addEdge(int v1, int v2, double prob)
    {
        transMatrix.m[v1][v2] += prob;
    }
    
    vector<double> getStableDistribution(vector<double>& initDistribution)
    {
        normalizeVector(initDistribution);
        for (int i = 0; i < N; ++i)
            normalizeVector(transMatrix.m[i]);
        
        SquareMatrix finalMatrix = transMatrix.power(1000000000);
        vector<double> ret(N, 0);
        for (int j = 0; j < N; ++j)
            for (int i = 0; i < N; ++i)
                ret[j] += initDistribution[i] * finalMatrix.m[i][j];
        return ret;
    }
    
private:
    void normalizeVector(vector<double>& v)
    {
        double sum = 0;
        for (unsigned int i = 0; i < v.size(); ++i)
            sum += v[i];
        for (unsigned int i = 0; i < v.size(); ++i)
            v[i] /= sum;
    }
};

int R, C;
vector<string> c;
const int TERM = -1;
const int INFI = -2;
int dir[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };
int adjdir[4][2] = { {1, 3}, {0, 2}, {1, 3}, {0, 2} };

int getNewD(int d, char c)
{
    if (c == '/')
    {
        if (d == 0) return 1;
        if (d == 1) return 0;
        if (d == 2) return 3;
        if (d == 3) return 2;
    }
    if (c == '\\')
    {
        if (d == 0) return 3;
        if (d == 1) return 2;
        if (d == 2) return 1;
        if (d == 3) return 0;
    }
    return -1;
}

int move(int x, int y, int d, int& nx, int& ny)
{
    while (true)
    {
        x += dir[d][0];
        y += dir[d][1];
        nx = x;
        ny = y;
        if (x < 0 || x >= R || y < 0 || y >= C) return INFI;
        if (c[x][y] == 'S') return INFI;
        if (c[x][y] == 'T') return TERM;
        if (c[x][y] == 'W') return d;
        if (c[x][y] == '/' || c[x][y] == '\\') d = getNewD(d, c[x][y]);
    }
}



class TribbloTrouble
{
public:
    
    map<int, int> idmap;
    
    int getID(int id)
    {
        if (idmap.count(id) == 0)
        {
            int newid = (int) idmap.size();
            idmap[id] = newid;
            return newid;
        }
        else
            return idmap[id];
    }
    
    double terminates(vector <string> code)
    {
        R = (int) code.size();
        C = (int) code[0].size();
        c = code;
        idmap.clear();
        
        int S = getID(-100);
        int INFINODE = getID(INFI);
        int TERMINATENODE = getID(TERM);
        
        int wcnt = 0;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (code[i][j] == 'W') wcnt++;
        int NODES = 3 + wcnt * 4;
        
        StochasticProcess sp(NODES);
        sp.addEdge(INFINODE, INFINODE, 1);
        sp.addEdge(TERMINATENODE, TERMINATENODE, 1);
        
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (code[i][j] == 'S' || code[i][j] == 'W')
                {
                    for (int k = 0; k < 4; ++k)
                    {
                        int nowNode = S;
                        if (code[i][j] == 'W') nowNode = getID((i + 1) * C * 4 + (j + 1) * 4 + k);
                        int nx, ny;
                        int ret = move(i, j, k, nx, ny);
                        if (ret == INFI) sp.addEdge(nowNode, INFINODE, 0.25);
                        if (ret == TERM) sp.addEdge(nowNode, TERMINATENODE, 0.25);
                        if (ret >= 0)
                        {
                            for (int nd = 0; nd < 2; ++nd) 
                                sp.addEdge(nowNode, getID((nx + 1) * C * 4 + (ny + 1) * 4 + adjdir[ret][nd]), 0.125);
                        }
                    }
                }
        
        vector<double> initD(NODES, 0);
        initD[S] = 1;
        vector<double> retD = sp.getStableDistribution(initD);
        return retD[TERMINATENODE];
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"..T..",
        "T.S.T",
        "..T.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.0; verify_case(0, Arg1, terminates(Arg0)); }
	void test_case_1() { string Arr0[] = {"./..T",
        ".\\..\\",
        "S.../"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.25; verify_case(1, Arg1, terminates(Arg0)); }
	void test_case_2() { string Arr0[] = {"...W..T",
        ".......",
        "...S..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.125; verify_case(2, Arg1, terminates(Arg0)); }
	void test_case_3() { string Arr0[] = {
        "T......",
        ".......",
        "....W.T",
        ".......",
        "\\S../.."
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.375; verify_case(3, Arg1, terminates(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    TribbloTrouble ___test;
    ___test.run_test(-1);
}
// END CUT HERE
