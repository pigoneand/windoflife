/**
 * SGU 149 AC
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <utility>
#include <queue>
using namespace std;

/** The adjanency linkedlist format of a graph */
class Graph
{
  public:
    vector<vector<pair<int, int> > > adj;
    int N;

    Graph(int nodes)
    {
      N = nodes;
      adj = vector<vector<pair<int, int> > >(N);
    }

    Graph()
    {
      Graph(0);
    }

    void addEdge(int start, int stop, int weight)
    {
      if (stop == start) return;
      if (start < 0 || start >= N) return;
      if (stop < 0 || stop >= N) return;
      adj[start].push_back(make_pair(stop, weight));
    }

    void addUndirectEdge(int start, int stop, int weight)
    {
      addEdge(start, stop, weight);
      addEdge(stop, start, weight);
    }

    friend ostream & operator << (ostream & out, const Graph & graph)
    {
      for (int i = 0; i < graph.N; ++i)
      {
        out << i << ":\t";
        for (int j = 0; j < graph.adj[i].size(); ++j)
          out << graph.adj[i][j].first << "(" << graph.adj[i][j].second << ")\t";
        out << endl;
      }
      return out;
    }
};

class Tree : public Graph
{
  public:
    vector<pair<int ,int> > father;

    Tree(int N) : Graph(N)
    {
      father = vector<pair<int, int> >(N, make_pair(-1, 0));
    }

    Tree() 
    {
      Tree(0);
    }

    Tree(Graph & graph) : Graph(graph.N)
    {
      father = vector<pair<int, int> >(N, make_pair(-1, 0));

      vector<bool> visited(N, false);
      queue<int> q;

      visited[0] = true;
      q.push(0);
      while (q.size() > 0)
      {
        int now = q.front();
        q.pop();
        for (int i = 0; i < graph.adj[now].size(); ++i)
        {
          int adjNode = graph.adj[now][i].first;
          int weight = graph.adj[now][i].second;
          if (!visited[adjNode])
          {
            visited[adjNode] = true;
            addEdge(now, adjNode, weight);
            setFather(adjNode, now, weight);
            q.push(adjNode);
          }
        }
      }
    }

    void setFather(int node, int fat, int weight) { father[node] = make_pair(fat, weight); }
    int getFather(int node) { return father[node].first; }
    int getWeightToFather(int node) { return father[node].second; }
};

int bestToSon[10000];
int bestToSonNext[10000];
int secondToSon[10000];
int secondToSonNext[10000];
int bestToFather[10000];
Tree tree;

void dealToSon(int now)
{
  bestToSon[now] = 0;
  secondToSon[now] = 0;

  for (int i = 0; i < tree.adj[now].size(); ++i)
  {
    int son = tree.adj[now][i].first;
    int weight = tree.adj[now][i].second;
    dealToSon(son);
    int newBest = bestToSon[son] + weight;
    if (newBest > bestToSon[now])
    {
      secondToSon[now] = bestToSon[now];
      secondToSonNext[now] = bestToSonNext[now];
      bestToSon[now] = newBest;
      bestToSonNext[now] = son;
    }
    else
    {
      if (newBest > secondToSon[now])
      {
        secondToSon[now] = newBest;
        secondToSonNext[now] = son;
      }
    }
  }
  return;
}

void dealToFather(int now)
{
  bestToFather[now] = 0;
  int father = tree.getFather(now);
  int weight = tree.getWeightToFather(now);
  if (father >= 0)
  {
    bestToFather[now] = weight + bestToFather[father];
    if (secondToSonNext[father] != now)
      bestToFather[now] = max(bestToFather[now], weight + secondToSon[father]);
    if (bestToSonNext[father] != now)
      bestToFather[now] = max(bestToFather[now], weight + bestToSon[father]);
  }

  for (int i = 0; i < tree.adj[now].size(); ++i)
    dealToFather(tree.adj[now][i].first);
}

int N;
int main()
{
  scanf("%d", &N);
  Graph graph(N);
  for (int i = 1; i < N; ++i)
  {
    int t1, t2;
    scanf("%d%d", &t1, &t2);
    t1--;
    graph.addUndirectEdge(i, t1, t2);
  }

  tree = Tree(graph);
  memset(bestToSon, 0, sizeof(bestToSon));
  memset(secondToSon, 0, sizeof(secondToSon));
  memset(bestToFather, 0, sizeof(bestToFather));

  //cout << tree << endl;
  dealToSon(0);
  /**
  for (int i = 0; i < N; ++i)
    cout << bestToSon[i] << " ";
  cout << endl;

  for (int i = 0; i < N; ++i)
    cout << secondToSon[i] << " ";
  cout << endl;
  */

  dealToFather(0);
  /**
  for (int i = 0; i < N; ++i)
    cout << bestToFather[i] << " ";
  cout << endl;
  */

  for (int i = 0; i < N; ++i)
    printf("%d\n", max(bestToSon[i], bestToFather[i]));
  return 0;
}
