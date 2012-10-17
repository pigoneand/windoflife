#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <cstdlib>
#include <cstdio>

/*
ID: zhuyihe3
LANG: C++
TASK: butter
*/
using namespace std;

class Dijkstra
{
  public:

    static const int INFINITY = (1 << 30);

    /** About priority_queue in STL
     * template < class T, class Container = vector<T>,
     *            class Compare = less<typename Container::value_type> > class priority_queue;
     *
     * T: Type of the elements.
     * Container: Type of the underlying container object used to store and access the elements.
     * Compare: Comparison class: A class such that the expression comp(a,b), 
     * where comp is an object of this class and a and b are elements of the container, 
     * returns true if a is to be placed earlier than b in a strict weak ordering operation. 
     * This can either be a class implementing a function call operator or a pointer to a function. 
     * This defaults to less<T>, which returns the same as applying the less-than operator (a<b).
     * The priority_queue object uses this expression when an element is inserted or removed from it 
     * (using push or pop, respectively) to grant that the element popped is always 
     * the greater in the priority queue.
     */

    /** 
     * @param
     * graph : adjaency list format of this graph.
     * dim1 : each node
     * dom2 : each node's edge
     * pair.first : edge node ID
     * pair.second : edge weight
     * source : start node
     * target : target node = -1 means cal each node 
     * @return
     * the shortest path length from source node to each node 
     */
    static vector<int> shortestPath(vector<vector<pair<int, int> > > & graph, int source, int target)
    {
      int N = graph.size();

      vector<int> dist(N, INFINITY);
      vector<int> previous(N, -1);
      vector<bool> visit(N, false);
      priority_queue<pair<int, int>, 
        vector<pair<int, int> >,  greater<pair<int, int> > > queue;

      dist[source] = 0;
      queue.push(make_pair(0, source));

      /** At most iteration N times, for each vertex */
      for (int i = 0; i < N; ++i) 
      {
        if (queue.empty()) break;
        while (!queue.empty() && visit[queue.top().second]) 
          queue.pop();
        if (queue.empty()) break;

        /** Find the node which has not been visited and has the minimum distance */
        pair<int, int> node = queue.top();
        int minDis = node.first;
        int minNode = node.second;
        queue.pop();

        /** If find the shortest path from source to target, then break */
        if (minNode == target) break;

        /** Mark this node to be visited, relax */
        visit[minNode] = true;
        /** For each edge this node link out */
        for (int j = 0; j < graph[minNode].size(); ++j) 
        {
          int otherID = graph[minNode][j].first;
          int weight = graph[minNode][j].second;
          if (visit[otherID]) continue;
          /** Do relaxation */
          if (dist[minNode] + weight < dist[otherID]) 
          {
            dist[otherID] = dist[minNode] + weight;
            previous[otherID] = minNode;
            queue.push(make_pair(dist[otherID], otherID)); 
          }
        }
      }

      return dist;
    }
};

/** PKU 1062 */
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

  int answer = Dijkstra::INFINITY;

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

    vector<int> nowAns = Dijkstra::shortestPath(graph, N, 0);

    if (nowAns[0] < answer) 
      answer = nowAns[0];
  }

  printf("%d\n", answer);

}



