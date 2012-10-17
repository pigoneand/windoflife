#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <list>
#include <set>

using namespace std;

class Bellman_Ford
{
  public:
    /** need relax operation so this INFINITY shouldn't be too large ,
     * caution int overflow 
     */
    static const int INFINITY = 1 << 25;

    /** graph : linked edge format of this graph.
     * dim1 : each node
     * dom2 : each node's edge
     * pair.first : edge node ID
     * pair.second : edge weight
     * SLF LLL
     */
    static vector<int> shortestPath(vector<vector<pair<int, int> > > & graph, int source, bool & negativeCycle)
    {
      int N = graph.size();
      vector<int> dist(N, INFINITY);
      vector<int> previous(N, -1);
      dist[source] = 0;

      /** Iteration N - 1 times */
      for (int i = 0; i < N - 1; ++i) {
        bool update = false;
        /** For each edge , do relax operation */
        for (int j = 0; j < N; ++j) 
          for (int k = 0; k < graph[j].size(); ++k) {
            int startNode = j;
            int stopNode = graph[j][k].first;
            int weight = graph[j][k].second;
            if (dist[startNode] + weight < dist[stopNode]) {
              update = true;
              dist[stopNode] = dist[startNode] + weight;
              previous[stopNode] = startNode;
            }
          }
        if (!update) break;
      }

      /** Judge negative cycle */
      /** For each edge , check negative cycle */
      negativeCycle = false;
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < graph[i].size(); ++j) {
          int startNode = i;
          int stopNode = graph[i][j].first;
          int weight = graph[i][j].second;
          if (dist[startNode] + weight < dist[stopNode]) {
            negativeCycle = true;
          }
        }
      return dist;
    }
};

int main()
{
    int N, delta;
    scanf("%d%d", &delta, &N);

    vector<int> price(N);
    vector<int> level(N);
    vector<int> startNode;
    vector<int> stopNode;
    vector<int> weight;

    int nEdge;
    for (int i = 0; i < N; ++i) {
      scanf("%d%d%d", &price[i], &level[i], &nEdge);
      for (int j = 0; j < nEdge; ++j) {
        int start, w;
        scanf("%d%d", &start, &w);
        start--;
        startNode.push_back(start);
        stopNode.push_back(i);
        weight.push_back(w);
      }
    }

    int answer = Bellman_Ford::INFINITY;

    for (int i = 0; i < N; ++i) {
      vector<vector<pair<int, int> > > graph(N + 1);
      int nowLevel = level[i];
      for (int j = 0; j < N; ++j) 
        if (level[j] <= nowLevel && level[j] >= nowLevel - delta) 
          graph[N].push_back(make_pair(j, price[j]));

      for (int k = 0; k < startNode.size(); ++k) {
        if (level[startNode[k]] <= nowLevel && level[startNode[k]] >= nowLevel - delta) 
          if (level[stopNode[k]] <= nowLevel && level[stopNode[k]] >= nowLevel - delta) 
            graph[startNode[k]].push_back(make_pair(stopNode[k], weight[k]));
      }

      /**
      for (int i = 0; i < graph.size(); ++i) {
        cout << "Start From " << i << "\t";
        for (int j = 0; j < graph[i].size(); ++j) 
          cout << graph[i][j].first << " " << graph[i][j].second << " ";
        cout << endl;
      }
      */

      bool nega;
      vector<int> nowAns = Bellman_Ford::shortestPath(graph, N, nega);

      if (nowAns[0] < answer) 
        answer = nowAns[0];
    }
      
    printf("%d\n", answer);

}




