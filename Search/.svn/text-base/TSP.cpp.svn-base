#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

/** Travel Salesman Problem in Small Graph */
class TSP
{
  public:
    static const int MAXN = 16;
    static const int MAXWEIGHT = 9999999;

    /** Number of vertex in the graph */
    int N;
    int subsets;
    int startNodeID;
    int stopNodeID;

    /** The edge weight of each vertex pair */
    int weight[MAXN][MAXN];

    /** Dynamic Programming Array */
    int f[MAXN][1 << MAXN]; 
    bool fc[MAXN][1 << MAXN];

    /** Next node ID for this node in the TSP */
    int next[MAXN];

    TSP(int n)
    {
      N = n;
      subsets = (1 << N);
      clear();
    }

    void clear()
    {
      for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
          weight[i][j] = (i == j ? 0 : MAXWEIGHT);

      for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < subsets; ++j)
          fc[i][j] = false;
      
      for (int i = 0; i < N; ++i) 
        next[i] = -1;
    }

    void setWeight(int start, int stop, int w)
    {
      weight[start][stop] = w;
    }
    
  private:

    /** Get the shortest path from start to stop, remain some nodes to be visited */
    int getF(int nowNode, int remainNodes)
    {
      if (remainNodes == 0) 
        return weight[nowNode][stopNodeID];

      if (fc[nowNode][remainNodes])
        return f[nowNode][remainNodes];
      
      int minWeight = MAXWEIGHT;
      for (int i = 0; i < N; ++i)
        if (remainNodes & (1 << i))
        {
          if (weight[nowNode][i] + getF(i, remainNodes ^ (1 << i)) < minWeight)
          {
            minWeight = weight[nowNode][i] + getF(i, remainNodes ^ (1 << i));
            next[nowNode] = i;
          }
        }
      f[nowNode][remainNodes] = minWeight;
      fc[nowNode][remainNodes] = true;

      return f[nowNode][remainNodes];
    }

  public:
    int getMinimalPath(int startNode, int stopNode)
    {
      startNodeID = startNode;
      stopNodeID = stopNode;
      int remainNodes = subsets - 1;
      return getF(startNode, remainNodes ^ (1 << startNode) ^ (1 << stopNode));
    }
};


inline int abs(int x)
{
  return x > 0 ? x : -x;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
  {
    int N;
    int dist[180][180];
    char map[20][20];

    cin >> N;
    cin.getline(map[0], 20);
    for (int i = 0; i < N; ++i)
      cin.getline(map[i], 20);

    if (N == 1) 
    {
      cout << 0 << endl;
      continue;
    }

    vector<int> points;
    int nodes = N * N;
    points.push_back(0);
    points.push_back(nodes - 1);
    for (int i = 0; i < nodes; ++i)
      for (int j = 0; j < nodes; ++j)
        dist[i][j] = (i == j ? 0 : 9999);

    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j) 
      {
        int nowID = i * N + j;
        if (map[i][j] == '*')
          points.push_back(nowID);
        if (map[i][j] != '#') 
        {
          if (i > 0 && map[i-1][j] != '#') 
            dist[nowID][nowID - N] = 1;
          if (i + 1 < N && map[i+1][j] != '#') 
            dist[nowID][nowID + N] = 1;
          if (j > 0 && map[i][j-1] != '#')
            dist[nowID][nowID - 1] = 1;
          if (j + 1 < N && map[i][j+1] != '#')
            dist[nowID][nowID + 1] = 1;
        }
      }

    for (int k = 0; k < nodes; ++k)
      for (int i = 0; i < nodes; ++i)
        for (int j = 0; j < nodes; ++j)
          if (dist[i][k] + dist[k][j] < dist[i][j]) 
            dist[i][j] = dist[i][k] + dist[k][j];

    bool ok = true;
    for (int i = 0; i < points.size(); ++i)
      if (dist[0][points[i]] >= 9999) 
        ok = false;

    if (!ok) 
    {
      cout << -1 << endl;
      continue;
    }

    TSP tsp(points.size());
    for (int i = 0; i < points.size(); ++i)
      for (int j = 0; j < points.size(); ++j)
      {
        tsp.setWeight(i, j, dist[points[i]][points[j]]);
      }

    cout << tsp.getMinimalPath(0, 1) << endl;
  }
  return 0;
}
