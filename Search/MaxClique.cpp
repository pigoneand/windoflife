#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

class MaxClique
{
  public:
    vector<int> maxCFromThisNode;
    vector<int> nodesInClique;
    vector<int> nodesInSearch;
    int N;
    int currentMax;
    bool found;

    void search(vector<vector<bool> > & graph, vector<bool> & canBe, int start, int depth)
    {
      nodesInSearch[depth - 1] = start;
      bool first = true;
      vector<bool> nextCanBe(N, false);
      for (int i = start + 1; i < N; i++)
      {
        if (canBe[i])              
        {
          if (first)
          {   
            if (depth + 1 > currentMax)
            { 
              nodesInSearch[depth] = i;
              nodesInClique = nodesInSearch;
              found = true; 
              currentMax = depth + 1; 
              return; 
            }
            first = false;
          }

          if (depth + maxCFromThisNode[i] <= currentMax) return;

          for (int j = start; j < N; j++)   
            if (canBe[j] && graph[i][j]) 
              nextCanBe[j] = true;
            else 
              nextCanBe[j] = false;

          search(graph, nextCanBe, i, depth + 1);

          if (found) return;
        }
      }
      return;
    }

    /** input: adjacency matrix
     * @return the nodes in max clique 
     */
    vector<int> getMaxClique(vector<vector<bool> > & graph)
    {
      N = graph.size();
      maxCFromThisNode = vector<int>(N, 0);
      vector<bool> canBeInClique(N, false);
      currentMax = 0;

      nodesInClique = vector<int>(N + 1, -1);
      nodesInSearch = vector<int>(N + 1, -1);

      for (int i = N - 1; i >= 0; --i)
      {
        canBeInClique = graph[i];
        found = false;
        search(graph, canBeInClique, i, 1); 
        maxCFromThisNode[i] = currentMax;
      }

      vector<int> ret;
      for (int i = 0; i < nodesInClique.size(); ++i)
        if (nodesInClique[i] >= 0)
          ret.push_back(nodesInClique[i]);

      if (ret.size() == 0)
        ret.push_back(0);

      return ret;
    }
};

/**
 * ZJU 1492 AC
int main()
{
  int N;
  MaxClique clique;

  while (scanf("%d", &N) == 1)
  {
    if (N == 0) break;

    vector<vector<bool> > graph(N, vector<bool>(N));
    int t;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
      {
        scanf("%d", &t);
        graph[i][j] = t;
      }

    cout << clique.getMaxClique(graph).size() << endl;
  }
  return 0;
}
*/

struct CRect
{
  int x1, x2, y1, y2;
};

bool CrossLine(int left, int right, int y, int top, int bottom, int x)
{
//判断一根横线和一根竖线是否交叉
//横线有三个参数：left, right和y
//竖线有三个参数：top, bottom和x
return (top <= y) && (bottom >= y)
&& (left <= x) && (right >= x);
}

bool CrossRect(CRect &r1, CRect &r2)
{
return CrossLine(r1.x1, r1.x2, r1.y1, r2.y1, r2.y2, r2.x1)
|| CrossLine(r1.x1, r1.x2, r1.y1, r2.y1, r2.y2, r2.x2)
|| CrossLine(r1.x1, r1.x2, r1.y2, r2.y1, r2.y2, r2.x1)
|| CrossLine(r1.x1, r1.x2, r1.y2, r2.y1, r2.y2, r2.x2)
|| CrossLine(r2.x1, r2.x2, r2.y1, r1.y1, r1.y2, r1.x1)
|| CrossLine(r2.x1, r2.x2, r2.y1, r1.y1, r1.y2, r1.x2)
|| CrossLine(r2.x1, r2.x2, r2.y2, r1.y1, r1.y2, r1.x1)
|| CrossLine(r2.x1, r2.x2, r2.y2, r1.y1, r1.y2, r1.x2);
}

CRect r[200];

MaxClique clique;

void deal()
{
  int N;
  scanf("%d", &N);
  for (int i = 0; i < N; ++i)
    scanf("%d%d%d%d", &r[i].x1, &r[i].x2, &r[i].y1, &r[i].y2);

  vector<vector<bool> > graph(N, vector<bool>(N, true));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (i != j)
      {
        if (CrossRect(r[i], r[j]))
          graph[i][j] = false;
      }
      else
        graph[i][j] = false;

  printf("%d\n", clique.getMaxClique(graph).size());
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T--)
    deal();
  return 0;
}
