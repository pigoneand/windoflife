#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
using namespace std;

class TopologicalSort
{
  public:

    /**
     * L ← Empty list that will contain the sorted elements
     * S ← Set of all nodes with no incoming edges
     * while S is non-empty do
     *     remove a node n from S
     *     insert n into L
     *     for each node m with an edge e from n to m do
     *         remove edge e from the graph
     *         if m has no other incoming edges then
     *             insert m into S
     * if graph has edges then
     *     output error message (graph has at least one cycle)
     * else 
     *     output message (proposed topologically sorted order: L)
     */

    /** 
     * @param
     * Adjacency-list representation of the graph
     * Needn't know the edge weight, only the edge connection is enough
     * Needn't ensure that the graph is DAG or non-duplicated edge
     * Won't change the graph 
     *
     * @return
     * existSolution return false indicate that this graph is not DAG
     * existSolution return true means that this graph could be topological sorted,
     * return a sorting number for each node 
     */
    static vector<int> topologicalSort(vector<vector<int> > & graph, bool & existSolution)
    {
      int N = graph.size();
      vector<int> nodeOrderNum(N);
      vector<int> inDegree(N, 0);
      queue<int> S;

      for (int i = 0; i < N; ++i)
        for (int j = 0; j < graph[i].size(); ++j)
          inDegree[graph[i][j]]++;

      for (int i = 0; i < N; ++i)
        if (inDegree[i] == 0) 
          S.push(i);

      int nowOrderNum = 0;
      while (!S.empty())
      {
        int nowID = S.front();
        S.pop();
        nodeOrderNum[nowID] = nowOrderNum++;

        for (int j = 0; j < graph[nowID].size(); ++j)
        {
          int anotherID = graph[nowID][j];
          inDegree[anotherID]--;
          if (inDegree[anotherID] == 0) 
            S.push(anotherID);
        }
      }

      if (nowOrderNum == N)
        existSolution = true;
      else
        existSolution = false;

      return nodeOrderNum;
    }
};


int main()
{
  vector<vector<int> > graph(5);
  graph[0].push_back(1);
  graph[0].push_back(2);
  graph[1].push_back(3);
  graph[2].push_back(3);
  //graph[3].push_back(4);
  //graph[4].push_back(0);

  bool existSolution;
  vector<int> nodeOrder = TopologicalSort::topologicalSort(graph, existSolution);
  cout << existSolution << endl;
  for (int i = 0; i < nodeOrder.size(); ++i)
    cout << nodeOrder[i] << "\t";
  cout << endl;
  return 0;
}
