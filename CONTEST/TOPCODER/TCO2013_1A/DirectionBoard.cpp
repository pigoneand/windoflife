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

/**
 * @Confidence
 * timus 1076 Trash AC bipartite graph maximum-weighted matching
 */
class MaxFlowMinimalCost
{
public:
    const static int INFINITY = (1 << 30);
    const static int NMAX = 2000;
    
    /** The capacity of each edge */
    int cap[NMAX][NMAX];
    
    /** The remain capacity of this edge */
    int net[NMAX][NMAX];
    
    /** The cost of each edge */
    int cost[NMAX][NMAX];
    
    /** The Linked List edge of this net work */
    vector<vector<int> > edges;
    
    int path[NMAX], ecost[NMAX];
    int N;
    int sourceNode;
    int sinkNode;
    
    MaxFlowMinimalCost(int nodes, int source, int sink)
    { reset(nodes, source, sink); }
    
    MaxFlowMinimalCost()
    { reset(0, 0, 0); }
    
    void reset(int nodes, int source, int sink)
    {
        N = nodes;
        sourceNode = source;
        sinkNode = sink;
        edges.clear();
        edges.resize(N);
        
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                cap[i][j] = 0;
                net[i][j] = 0;
                cost[i][j] = 999999;
            }
    }
    
    void addEdge(int start, int stop, int capacity, int _cost)
    {
        //cout << start << " " << stop << " " << capacity << " " << _cost << endl;
        cap[start][stop] = capacity;
        net[start][stop] = capacity;
        cost[start][stop] = min(cost[start][stop], _cost);
        edges[start].push_back(stop);
        edges[stop].push_back(start);
    }
    
private:
    
    /** Find an path with the minimal cost to increase the total flow */
    bool bellman_ford()
    {
        for (int i = 0; i < N; ++i) {
            path[i] = -1;
            ecost[i] = INFINITY;
        }
        ecost[sourceNode] = 0;
        
        bool flag = true;
        while (flag) {
            flag = false;
            for (int i = 0; i < N; i++) {
                if (ecost[i] == INFINITY) continue;
                for (int k = 0; k < edges[i].size(); ++k) {
                    int j = edges[i][k];
                    if(net[i][j] > 0 && ecost[i] + cost[i][j] < ecost[j]) {
                        flag = true;
                        ecost[j] = ecost[i] + cost[i][j];
                        path[j] = i;
                    }
                }
            }
        }
        return ecost[sinkNode] != INFINITY;
    }
    
public:
    void maxFlowMinimalCost(int & maxFlow, int & minCost)
    {
        maxFlow = 0;
        minCost = 0;
        
        while (bellman_ford()) {
            /** Find the minimal remain capacity of the argument path */
            int now = sinkNode;
            int neck = INFINITY;
            while (now != sourceNode) {
                int pre = path[now];
                neck = min(neck, net[pre][now]);
                now = pre;
            }
            maxFlow += neck;
            
            /** maintain the netflow */
            now = sinkNode;
            while (now != sourceNode) {
                int pre = path[now];
                net[pre][now] -= neck;
                net[now][pre] += neck;
                cost[now][pre] = -cost[pre][now];
                minCost += cost[pre][now] * neck;
                now = pre;
            }
        }
    }
};



class DirectionBoard
{
public:
    int getMinimum(vector <string> board)
    {
        int N = (int) board.size();
        int M = (int) board[0].size();
        
        if (N == 1 && M == 1) return 0;
        
        MaxFlowMinimalCost * net = new MaxFlowMinimalCost();
        net->reset(N * M * 2 + 2, N * M * 2, N * M * 2 + 1);
        int source = N * M * 2;
        int sink = N * M * 2 + 1;
        
        for (int i = 0; i < N * M; ++i)
        {
            net->addEdge(source, i, 1, 0);
            net->addEdge(i + N * M, sink, 1, 0);
        }
        
        map<char, int> dmap;
        dmap['U'] = 0;
        dmap['D'] = 1;
        dmap['L'] = 2;
        dmap['R'] = 3;
        int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                for (int k = 0; k < 4; ++k)
                {
                    int ni = (i + dir[k][0] + N) % N;
                    int nj = (j + dir[k][1] + M) % M;
                    int v1 = i * M + j;
                    int v2 = ni * M + nj + N * M;
                    if (dmap[board[i][j]] == k)
                    {
                        net->addEdge(v1, v2, 1, 0);
                        //cout << v1 << " " << v2 << " " << 0 << endl;
                    }
                    else
                    {
                        net->addEdge(v1, v2, 1, 1);
                        //cout << v1 << " " << v2 << " " << 1 << endl;
                    }
                }
        int maxFlow, minCost;
        net->maxFlowMinimalCost(maxFlow, minCost);
        return minCost;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"RRRD",
        "URDD",
        "UULD",
        "ULLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, getMinimum(Arg0)); }
	void test_case_1() { string Arr0[] = {"RRRD",
        "URLL",
        "LRRR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, getMinimum(Arg0)); }
	void test_case_2() { string Arr0[] = {"RRD",
        "URD",
        "ULL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, getMinimum(Arg0)); }
	void test_case_3() { string Arr0[] = {"ULRLRD",
        "UDDLRR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(3, Arg1, getMinimum(Arg0)); }
	void test_case_4() { string Arr0[] = {"UDLRLDLD",
        "DLDLLDLR",
        "LLLLLDLD",
        "UUURRRDD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(4, Arg1, getMinimum(Arg0)); }
	void test_case_5() { string Arr0[] = {"UDUDUUDUDUDUDUR",
        "LLLLDUUDRDLUDRU",
        "DLLDLDURDURUDDL",
        "UDUDUUDUDUDUDUR",
        "LLLLDUUDRDLUDRU",
        "DLLDLDURDURUDDL",
        "UDUDUUDUDUDUDUR",
        "LLLLDUUUDDLUDRU",
        "DLLDLDURDURUDDL",
        "UDUDUUDUDUDUDUR",
        "LLLLDUUDRDLUDRU",
        "DLLDLDURDURUDDL",
        "UDUDUUDUDUDUDUR",
        "LLLLDUUDRDLUDRU",
        "RRRDLDURDURUDDR"}
        ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 73; verify_case(5, Arg1, getMinimum(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE 
int main()
{
    DirectionBoard ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE 
