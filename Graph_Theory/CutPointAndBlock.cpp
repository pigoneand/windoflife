#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <string>
#include <stack>
#include <set>
#include <cstring>
#include <cstdio>
using namespace std;

/** 
 * This class return the cut points and blocks in the undirected graph
 * @see http://www.byvoid.com/blog/biconnect/
 *
 * 该算法是R.Tarjan发明的。对图深度优先搜索，定义DFS(u)为u在搜索树（以下简称为树）中被遍历到的次序号。
 * 定义Low(u)为u或u的子树中能通过非父子边追溯到的最早的节点，即DFS序号最小的节点。根据定义，则有： *
 * Low(u)=Min
 * {
 * DFS(u)
 * DFS(v) (u,v)为后向边(返祖边) 等价于 DFS(v)<DFS(u)且v不为u的父亲节点
 * Low(v) (u,v)为树枝边(父子边)
 * }
 *
 * 一个顶点u是割点，当且仅当满足(1)或(2)
 * (1) u为树根，且u有多于一个子树。
 * (2) u不为树根，且满足存在(u,v)为树枝边(或称父子边，即u为v在搜索树中的父亲)，使得DFS(u)<=Low(v)。
 *
 * 一条无向边(u,v)是桥，当且仅当(u,v)为树枝边，且满足DFS(u)<Low(v)。
 */
class CutPointAndBlock
{
  public:
    int N;
    vector<int> dfs;
    vector<int> low;
    stack<pair<int, int> > nowStack;
    int index;

    void tarjan(vector<vector<int> > & graph, int u, int father, vector<vector<int> > & blocks)
    {
      dfs[u] = low[u] = ++index;
      for (int i = 0; i < graph[u].size(); ++i)
      {
        int v = graph[u][i];
        if (!dfs[v])
        {
          nowStack.push(make_pair(u, v));
          tarjan(graph, v, u, blocks);
          low[u] = min(low[u], low[v]);
          if (low[v] >= dfs[u]) 
          {
            set<int> inBlock;
            vector<int> nowBlock;

            while (true)
            {
              pair<int, int> edge = nowStack.top();
              nowStack.pop();
              inBlock.insert(edge.first);
              inBlock.insert(edge.second);
              if (edge.first == u && edge.second == v)
                break;
            }

            for (set<int>::iterator itr = inBlock.begin(); itr != inBlock.end(); ++itr)
              nowBlock.push_back(*itr);
            blocks.push_back(nowBlock);
          }
        }
        else
        {
          if (v != father)
            low[u] = min(low[u], dfs[v]);
        }
      }
    }


    /** 
     * @param graph     the adjanency linked list 
     * @return          the blocks
     * @constrain       undirected graph, symmetric graph input 
     * @constrain       no self loop
     *
     * 对于点双连通分支，实际上在求割点的过程中就能顺便把每个点双连通分支求出。
     * 建立一个栈，存储当前双连通分支，在搜索图时，每找到一条树枝边或后向边(非横叉边)，就把这条边加入栈中。
     * 如果遇到某时满足DFS(u)<=Low(v)，说明u是一个割点，同时把边从栈顶一个个取出，直到遇到了边
     * (u,v)，取出的这些边与其关联的点，组成一个点双连通分支。
     * 割点可以属于多个点双连通分支，其余点和每条边只属于且属于一个点双连通分支。
     *
     * 对于边双连通分支，求法更为简单。只需在求出所有的桥以后，把桥边删除，原图变成了多个连通块，
     * 则每个连通块就是一个边双连通分支。
     * 桥不属于任何一个边双连通分支，其余的边和每个顶点都属于且只属于一个边双连通分支。
     */
    vector<vector<int> > getBlocks(vector<vector<int> > & graph)
    {
      N = graph.size();
      dfs = vector<int>(N, 0);
      low = vector<int>(N, 0);
      nowStack = stack<pair<int, int> >();
      index = 0;

      vector<vector<int> > ret;

      for (int i = 0; i < N; ++i)
        if (!dfs[i])
          tarjan(graph, i, -1, ret);

      return ret;
    }
};

bool edges[1001][1001];
bool inBlock[1001];
int color[1001];
vector<vector<int> > graph;

bool hasOddCycle(int u, int nc)
{
  color[u] = nc;
  for (int i = 0; i < graph[u].size(); ++i)
  {
    int v = graph[u][i];
    if (!inBlock[v])
      continue;

    if (color[v] == 0)
    {
      if (hasOddCycle(v, 3 - nc))
        return true;
    }
    else
    {
      if (color[v] == color[u])
        return true;
    }
  }
  return false;
}

/** PKU 2942 AC */
int main()
{
  CutPointAndBlock cut;

  int N, M;
  while (scanf("%d%d", &N, &M) == 2)
  {
    if (N == 0 && M == 0) break;
    memset(edges, true, sizeof(edges));
    for (int i = 0; i < N; ++i)
      edges[i][i] = false;

    while (M--)
    {
      int t1, t2;
      scanf("%d%d", &t1, &t2);
      t1--;
      t2--;
      edges[t1][t2] = edges[t2][t1] = false;
    }

    graph = vector<vector<int> >(N);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        if (edges[i][j])
          graph[i].push_back(j);

    vector<vector<int> > blocks = cut.getBlocks(graph);
    vector<bool> ok(N, false);

    /**
    for (int i = 0; i < blocks.size(); ++i)
    {
      for (int j = 0; j < blocks[i].size(); ++j)
        cout << blocks[i][j] << " ";
      cout << endl;
    }
    */

    for (int i = 0; i < blocks.size(); ++i)
    {
      if (blocks[i].size() > 2)
      {
        memset(inBlock, false, sizeof(inBlock));
        memset(color, 0, sizeof(color));
        for (int j = 0; j < blocks[i].size(); ++j)
          inBlock[blocks[i][j]] = true;

        if (hasOddCycle(blocks[i][0], 1))
        {
          for (int j = 0; j < blocks[i].size(); ++j)
            ok[blocks[i][j]] = true;
        }
      }
    }

    int ans = N;
    for (int i = 0; i < N; ++i)
      if (ok[i]) 
        ans--;

    printf("%d\n", ans);
  }


  /**
  vector<vector<int> > graph(7);
  graph[0].push_back(1); graph[1].push_back(0);
  graph[0].push_back(2); graph[2].push_back(0);
  graph[1].push_back(3); graph[3].push_back(1);
  graph[1].push_back(4); graph[4].push_back(1);
  graph[3].push_back(4); graph[4].push_back(3);
  graph[2].push_back(5); graph[5].push_back(2);
  graph[2].push_back(6); graph[6].push_back(2);
  graph[5].push_back(6); graph[6].push_back(5);

  vector<vector<int> > blocks = cut.getBlocks(graph);
  for (int i = 0; i < blocks.size(); ++i)
  {
    for (int j = 0; j < blocks[i].size(); ++j)
      cout << blocks[i][j] << " ";
    cout << endl;
  }
  */

  return 0;
}
