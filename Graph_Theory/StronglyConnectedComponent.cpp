#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <cmath>
#include <cstdio>
using namespace std;

/** 
 * The class solve the strongly connected component problem in directed graph
 * We implemented the Tarjan algorithm 
 * @see http://www.byvoid.com/blog/scc-tarjan/
 */
class SCC
{
  public:
    int N;
    int index;

    /** dfn, low start from one, set to zero means not visited yet */
    vector<int> dfn;
    vector<int> low;

    stack<int> nowStack;
    vector<bool> inStack;

    void tarjan(vector<vector<int> > & graph, int u, vector<vector<int> > & scc)
    {
      dfn[u] = low[u] = ++index;
      nowStack.push(u);
      inStack[u] = true;

      for (int i = 0; i < graph[u].size(); ++i)
      {
        int v = graph[u][i];
        if (!dfn[v])
        {
          tarjan(graph, v, scc);
          low[u] = min(low[u], low[v]);
        }
        else
        {
          if (inStack[v])
            low[u] = min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u])
      {
        vector<int> nscc;
        while (true)
        {
          int v = nowStack.top();
          nowStack.pop();
          inStack[v] = false;
          nscc.push_back(v);
          if (v == u) break;
        }
        scc.push_back(nscc);
      }
    }

    /** 
     * @param graph     the adjanency linked list 
     */
    vector<vector<int> > getSCC(vector<vector<int> > & graph)
    {
      N = graph.size();
      index = 0;
      dfn = vector<int>(N, 0);
      low = vector<int>(N);
      inStack = vector<bool>(N, false);
      nowStack = stack<int>();

      vector<vector<int> > ret;
      for (int i = 0; i < N; ++i)
      {
        if (!dfn[i])
          tarjan(graph, i, ret);
      }
      return ret;
    }
};

/** PKU 2186 */
int main()
{
  SCC scc;
  int N, M;
  while (scanf("%d%d", &N, &M) == 2)
  {
    vector<vector<int> > graph(N);
    int t1, t2;
    for (int i = 0; i < M; ++i)
    {
      scanf("%d%d", &t1, &t2);
      t1--;
      t2--;
      graph[t1].push_back(t2);
    }

    vector<vector<int> > ret = scc.getSCC(graph);

    vector<int> represent(N, 0);
    for (int i = 0; i < ret.size(); ++i)
      for (int j = 0; j < ret[i].size(); ++j)
        represent[ret[i][j]] = ret[i][0];


    vector<int> outDegree(N, 0);
    for (int i = 0; i < graph.size(); ++i)
      for (int j = 0; j < graph[i].size(); ++j)
      {
        int startNode = represent[i];
        int stopNode = represent[graph[i][j]];
        if (stopNode != startNode)
          outDegree[startNode]++;
      }

    int zeroDegree = 0;
    int representID = 0;
    for (int i = 0; i < N; ++i)
      if (represent[i] == i && outDegree[i] == 0)
      {
        zeroDegree++;
        representID = i;
      }
        
    if (zeroDegree == 1)
    {
      for (int i = 0; i < ret.size(); ++i)
        if (ret[i][0] == representID)
        {
          printf("%d\n", ret[i].size());
          break;
        }
    }
    else
      printf("0\n");
  }
  return 0;
}
