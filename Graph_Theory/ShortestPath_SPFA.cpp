#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <list>
#include <set>
/*
 ID: zhuyihe3
 LANG: C++
 TASK: butter
*/

using namespace std;

class SPFA
{
    public:
        static const int INFINITY = 2147483647;

        /** graph : linked edge format of this graph.
         * dim1 : each node
         * dom2 : each node's edge
         * pair.first : edge node ID
         * pair.second : edge weight
         * SLF LLL
         */
        static vector<int> shortestPath(vector<vector<pair<int, int> > > & graph, int source)
        {
            int N = graph.size();
            vector<int> dist(N, INFINITY);
            vector<int> previous(N, -1);
            vector<bool> inQueue(N, false);
            dist[source] = 0;

            list<int> queue;
            queue.push_back(source);
            inQueue[source] = true;

            int queueSize = 1;
            int queueDistSum = 0;
            while (!queue.empty()) {
                int average = queueDistSum / queueSize + 1;
                while (dist[queue.front()] > average) {
                    int tmp = queue.front();
                    queue.pop_front();
                    queue.push_back(tmp);
                }

                int node = queue.front();
                inQueue[node] = false;
                queueSize--;
                queueDistSum -= dist[node];
                queue.pop_front();

                for (int i = 0; i < graph[node].size(); ++i) {
                    int otherID = graph[node][i].first;
                    int weight = graph[node][i].second;
                    if (dist[node] + weight < dist[otherID]) {
                        dist[otherID] = dist[node] + weight;
                        previous[otherID] = node;
                        if (inQueue[otherID]) continue;
                        if (queue.empty()) 
                            queue.push_back(otherID);
                        else {
                            if (dist[otherID] < dist[queue.front()]) 
                                queue.push_front(otherID);
                            else
                                queue.push_back(otherID);
                        }
                        queueSize++;
                        queueDistSum += dist[otherID];
                        inQueue[otherID] = true;
                    }
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

    int answer = SPFA::INFINITY;

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

      vector<int> nowAns = SPFA::shortestPath(graph, N);

      if (nowAns[0] < answer) 
        answer = nowAns[0];
    }
      
    printf("%d\n", answer);

}



