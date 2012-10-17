#include <iostream>
#include <string.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <map>
#include <queue>
using namespace std;

class EulerPath
{
  public:
    vector<vector<bool> > graph;
    vector<int> path;
    vector<int> degree;
    int N;

    vector<int> oddPath;
    void searchOddPath(int oddStart)
    {
      vector<bool> visited(N, false);
      vector<int> previous(N, -1);
      queue<int> q;

      visited[oddStart] = true;
      q.push(oddStart);
      while (q.size() > 0)
      {
        int now = q.front();
        q.pop();
        for (int i = 0; i < N; ++i)
          if (graph[now][i] && !visited[i])
          {
            visited[i] = true;
            previous[i] = now;
            q.push(i);
            if (degree[i] % 2 == 1)
            {
              oddPath.push_back(i);
              int track = i;
              while (previous[track] != -1)
              {
                track = previous[track];
                oddPath.push_back(track);
              }
              return;
            }
          }
      }
      cerr << "no odd path" << endl;
      exit(0);
      return;
    }

    void search(int now)
    {
      while (degree[now] > 0)
      {
        for (int i = 0; i < N; ++i)
          if (graph[now][i])
          {
            degree[now]--;
            degree[i]--;
            graph[now][i] = false;
            graph[i][now] = false;
            search(i);
          }
      }
      path.push_back(now);
    }

    /**
     * input the adjanency matrix of the graph, 
     * @constrain       make sure that it is symmetric
     * @constrain       undirected graph
     * @constrain       and it is connected 
     * @return
     *  true            if euler cycle or euler path exist, p contain the path
     *  false           if euler cycle and euler path doesn't exist, p contain a path
     *                  from an odd node to another odd node
     */
    bool getEulerPath(vector<vector<bool> > & g, vector<int> & p)
    {
      graph = g;
      N = graph.size();
      path.clear();
      degree = vector<int>(N, 0);

      for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
          if (graph[i][j])
          {
            degree[i]++;
            degree[j]++;
          }

      int odds = 0;
      int oddID = 0;
      int posID = 0;
      for (int i = 0; i < N; ++i)
      {
        if (degree[i] % 2 == 1)
        {
          odds++;
          oddID = i;
        }
        if (degree[i] > 0)
          posID = i;
      }
      
      if (odds > 2) 
      {
        oddPath.clear();
        searchOddPath(oddID);
        p = oddPath;
        return false;
      }

      if (odds == 2)
        search(oddID);
      else
        search(posID);
      p = path;
      return true;
    }
};

class ConnectedComponent
{
  public:

    vector<vector<int> > getComponent(vector<vector<int> > & graph)
    {
      int N = graph.size();
      vector<bool> visited(N, false);
      vector<vector<int> > ret;

      for (int i = 0; i < N; ++i)
      {
        if (!visited[i])
        {
          stack<int> nodes;
          vector<int> com;
          nodes.push(i);
          visited[i] = true;
          com.push_back(i);

          while (nodes.size() > 0)
          {
            int nowID = nodes.top();
            nodes.pop();
            for (int j = 0; j < graph[nowID].size(); ++j)
            {
              int otherID = graph[nowID][j];
              if (!visited[otherID])
              {
                visited[otherID] = true;
                nodes.push(otherID);
                com.push_back(otherID);
              }
            }
          }
          ret.push_back(com);
        }
      }
      return ret;
    }
};

vector<vector<bool> > graph;
vector<vector<int> > linkGraph;
vector<vector<int> > color;
vector<vector<int> > initLink;
int N;

void init()
{
  graph = vector<vector<bool> >(N, vector<bool>(N, false));
  color = vector<vector<int> >(N, vector<int>(N, 1));
  linkGraph = vector<vector<int> >(N);
  initLink = vector<vector<int> >(N);
  for (int i = 0; i < N; ++i)
  {
    int j = 0;
    while (scanf("%d", &j) == 1)
    {
      if (j == 0) break;
      j--;
      graph[i][j] = graph[j][i] = true;
      linkGraph[i].push_back(j);
      linkGraph[j].push_back(i);
      initLink[i].push_back(j);
    }
  }
}

void deal()
{
  ConnectedComponent cc;
  EulerPath ep;
  vector<vector<int> > scc = cc.getComponent(linkGraph);

  /**
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
      cout << graph[i][j] << " ";
    cout << endl;
  }
  */

  /** for each component */
  for (int k = 0; k < scc.size(); ++k)
  {
    int sN = scc[k].size();
    vector<int> & nodes = scc[k];
    vector<int> idMap(sN, 0);
    for (int i = 0; i < nodes.size(); ++i)
      idMap[i] = nodes[i];

    int edges = 0;
    vector<vector<bool> > newGraph(sN, vector<bool>(sN, false));
    for (int i = 0; i < sN; ++i)
      for (int j = 0; j < sN; ++j)
      {
        newGraph[i][j] = graph[idMap[i]][idMap[j]];
        if (newGraph[i][j]) edges++;
      }
    edges /= 2;
    int initEdges = edges;

    /** start to draw color for this component */
    while (edges > 0)
    {
      vector<int> path;
      bool ret = ep.getEulerPath(newGraph, path);

      /**
      cout << "isCycle=" << ret << "\t";
      for (int i = 0; i < path.size(); ++i)
        cout << idMap[path[i]] + 1 << " ";
      cout << endl;
      */

      if (ret)
      {
        /** If it is the init odd len cycle */
        if (sN % 2 == 1 && sN > 1 && initEdges == sN && path.size() == sN + 1 && 
            path[0] == path[path.size() - 1])
        {
          printf("No solution\n");
          return;
        }
      }

      for (int i = 0; i < path.size() - 1; ++i)
      {
        int start = path[i];
        int stop = path[i + 1];
        edges--;
        newGraph[start][stop] = false;
        newGraph[stop][start] = false;
        int oldStart = idMap[start];
        int oldStop = idMap[stop];
        color[oldStart][oldStop] = 2 - i % 2;
        color[oldStop][oldStart] = 2 - i % 2;
      }
    }
  }
  for (int i = 0; i < N; ++i)
  {
    bool white = false;
    bool black = false;
    for (int j = 0; j < initLink[i].size(); ++j)
    {
      if (color[i][initLink[i][j]] == 1) white = true;
      if (color[i][initLink[i][j]] == 2) black = true;
      printf("%d ", color[i][initLink[i][j]]);
    }
    printf("0\n");
    if (initLink[i].size() >= 2 && (!white || !black))
    {
    }
  }
}

int main()
{
  while (scanf("%d", &N) == 1)
  {
    init();
    deal();
  }
  return 0;
}
