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

struct TwoColor
{
    vector<int> color;
    vector<vector<int> > edges;
    
    TwoColor(int N)
    {
        color = vector<int>(N, -1);
        edges = vector<vector<int> >(N);
    }
    
    void setColor(int offset, int c)
    {
        color[offset] = c;
    }
    
    void addEdge(int a, int b)
    {
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    bool dfs(int now, int c)
    {
        color[now] = c;
        for (int i = 0; i < edges[now].size(); ++i)
        {
            int nextID = edges[now][i];
            if (color[nextID] == color[now]) return false;
            if (color[nextID] == -1)
                if (!dfs(nextID, 3 - c)) return false;
        }
        return true;
    }
    
    bool evalute()
    {
        for (int i = 0; i < color.size(); ++i)
        {
            vector<int> backup = color;
            if (color[i] >= 0)
            {
                if (!dfs(i, color[i])) return false;
                color = backup;
            }
            else
            {
                bool c1 = dfs(i, 1);
                color = backup;
                bool c2 = dfs(i, 2);
                color = backup;
                if (!c1 && !c2) return false;
            }
        }
        return true;
    }
};

class FamilyTree
{
public:
    
    map<string, int> idMap;
    map<int, int> c;
    vector<pair<int, int> > parentEdges;
    
    int addUser(const string& str)
    {
        if (idMap.count(str) > 0) return idMap[str];
        int id = (int) idMap.size();
        return idMap[str] = id;
    }
    
    bool check()
    {
        int N = (int) idMap.size();
        vector<vector<bool> > g(N, vector<bool>(N, false));
        for (int i = 0; i < parentEdges.size(); ++i)
        {
            int a = parentEdges[i].first;
            int b = parentEdges[i].second;
            g[a][b] = true;
        }
        
        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    g[i][j] = g[i][j] || (g[i][k] && g[k][j]);
        
        for (int i = 0; i < N; ++i)
            if (g[i][i]) return false;
        
        TwoColor twoC(N);
        for (int i = 0; i < N; ++i)
            if (c.count(i) > 0)
                twoC.setColor(i, c[i]);
        
        for (int i = 0; i < N; ++i)
        {
            vector<int> parents;
            for (int k = 0; k < parentEdges.size(); ++k)
                if (parentEdges[k].first == i) parents.push_back(parentEdges[k].second);
            if (parents.empty()) continue;
            sort(parents.begin(), parents.end());
            parents.resize(unique(parents.begin(), parents.end()) - parents.begin());
   
            if (parents.size() > 2) return false;
            if (parents.size() == 2)
                twoC.addEdge(parents[0], parents[1]);
        }
        
        return twoC.evalute();
    }
    
    int firstBad(vector <string> data)
    {
        idMap.clear();
        c.clear();
        parentEdges.clear();
        
        for (int i = 0; i < data.size(); ++i)
        {
            istringstream istr(data[i].data());
            string name1, name2;
            istr >> name1 >> name2;
            if (isupper(name2[0]))
            {
                int u1 = addUser(name1);
                int u2 = addUser(name2);
                parentEdges.push_back(make_pair(u1, u2));
            }
            else
            {
                int u1 = addUser(name1);
                int g = (name2[0] == 'm' ? 1 : 2);
                if (c.count(u1) > 0 && c[u1] != g) return i;
                c[u1] = g;
            }
            if (!check()) return i;
        }
        return -1;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BOB JOHN","BOB JOHN","BOB MARY","BOB m","AL f"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(0, Arg1, firstBad(Arg0)); }
	void test_case_1() { string Arr0[] = {"BOB JOHN","BOB MARY","MARY JOHN","JOHN f","MARY f","AL f"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, firstBad(Arg0)); }
	void test_case_2() { string Arr0[] = {"BOB JOHN", "CARLA BOB", "JOHN CARLA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, firstBad(Arg0)); }
	void test_case_3() { string Arr0[] = {"BOB RICK", "AL RICK", "AL PAULA", "PAULA LINUS", "LINUS BOB","BOB PAULA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(3, Arg1, firstBad(Arg0)); }
	void test_case_4() { string Arr0[] = {"JOHN f", "JOHN m"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, firstBad(Arg0)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    FamilyTree ___test;
    ___test.run_test(0);
}
// END CUT HERE
