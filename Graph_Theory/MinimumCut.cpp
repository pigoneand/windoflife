#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdio>
using namespace std;

/** Union Find Set 
 * O(1) to merge two set
 * O(1) to find which set the given element belong to 
 */
class UnionFindSet
{
  private:
    vector<int> belongTo;

    /** How many different sets exist now */
    int setCount;

  public:
    UnionFindSet(int size)
    {
      belongTo = vector<int>(size);
      clear();
    }

    /** Reset the union find set data */
    void clear()
    {
      for (int i = 0; i < belongTo.size(); ++i) 
        belongTo[i] = -1;
      setCount = belongTo.size();
    }

    /** Return element i's set's representive element */
    int find(int elementID)
    {
      if (belongTo[elementID] < 0)
        return elementID;
      else 
        return belongTo[elementID] = find(belongTo[elementID]);
    }

    /** Return the element i's set's size */
    int getSize(int elementID)
    { 
      int representiveElement = find(elementID);
      return -belongTo[representiveElement];
    }

    /** merge two element */
    void Union(int elementID1, int elementID2)
    {
      int representiveElement1 = find(elementID1);
      int representiveElement2 = find(elementID2);
      if (representiveElement1 == representiveElement2) 
        return;

      setCount--;
      int size1 = -belongTo[representiveElement1];
      int size2 = -belongTo[representiveElement2];

      if (size1 <= size2) {
        belongTo[representiveElement1] = representiveElement2;
        belongTo[representiveElement2] -= size1;
      }
      else {
        belongTo[representiveElement2] = representiveElement1;
        belongTo[representiveElement1] -= size2;
      }
    }

    /** Return different set count */
    inline int getSetCount() 
    {
      return setCount;
    }

    void output(ostream & out)
    {
      out << setCount << endl;
      for (int i = 0; i < belongTo.size(); ++i)
        out << find(i) << "\t";
      out << endl;
    }

    vector<vector<int> > getAllSets() 
    {
      map<int, vector<int> > sets;
      for (int i = 0; i < belongTo.size(); ++i) 
        sets[find(i)].push_back(i);

      vector<vector<int> > ret;
      for (map<int, vector<int> >::iterator itr = sets.begin(); itr != sets.end(); ++itr) 
        ret.push_back(vector<int>(itr->second.begin(), itr->second.end()));
      return ret;
    }
};


/**
 * The class solved the minimum cut problem, 
 * We present an algorithm for finding the minimum cut of an undirected edge-weighted graph. 
 * Source: A Simple Min-Cut Algorithm Mechthild stoer and Frank Wanger
 */

class MinimumCut
{
  public:
    int N;
    vector<bool> avail;

    int minimumCutPhase(vector<vector<int> > & graph)
    {
      vector<int> path;
      vector<bool> inA(N, false);
      vector<int> distToA(N, 0);

      int totalNode = 0;
      int firstNode = -1;
      for (int i = 0; i < avail.size(); ++i)
        if (avail[i])
        {
          totalNode++;
          firstNode = i;
        }

      inA[firstNode] = true;
      for (int i = 0; i < N; ++i)
        if (avail[i] && !inA[i])
          distToA[i] = graph[i][firstNode];
      path.push_back(firstNode);

      int cutofthephase = 0;
      for (int k = 1; k < totalNode; ++k)
      {
        int maxDistToA = -1;
        int nextNode = -1;
        for (int i = 0; i < N; ++i)
          if (avail[i] && !inA[i] && distToA[i] > maxDistToA)
          {
            maxDistToA = distToA[i];
            nextNode = i;
          }

        inA[nextNode] = true;
        for (int i = 0; i < N; ++i)
          if (avail[i] && !inA[i])
            distToA[i] += graph[i][nextNode];
        path.push_back(nextNode);

        cutofthephase = maxDistToA;
      }

      /** contracton the last two nodes */
      int lastID = path[path.size() - 1];
      int lastlastID = path[path.size() - 2];
      avail[lastID] = false;
      for (int i = 0; i < N; ++i)
      {
        if (i != lastlastID)
        {
          graph[lastlastID][i] += graph[lastID][i];
          graph[i][lastlastID] += graph[lastID][i];
        }
        graph[lastID][i] = graph[i][lastID] = 0;
      }

      return cutofthephase;
    }

    /** input format : adjacency matrix 
     * @return the minimum cut
     * @constrain : undirect graph, positive weight
     * @constrain : graph size >= 2
     * @constrain : graph is connected
     */
    int getMinimumCut(vector<vector<int> > & graph)
    {
      N = graph.size();
      avail = vector<bool>(N, true);
      int minimumCut = 999999999;

      for (int i = 1; i <= N - 1; ++i)
      {
        int nowMinCut = minimumCutPhase(graph);
        minimumCut = min(minimumCut, nowMinCut);
      }
      return minimumCut;
    }
};

/** ZJU 2753 AC */
int main()
{
  int N, M;
  MinimumCut cut;
  while (scanf("%d%d", &N, &M) == 2)
  {
    vector<vector<int> > graph(N, vector<int>(N, 0));
    UnionFindSet unionSet(N);
    for (int i = 0; i < M; ++i)
    {
      int t1, t2, w;
      scanf("%d%d%d", &t1, &t2, &w);
      graph[t1][t2] += w;
      graph[t2][t1] += w;
      unionSet.Union(t1, t2);
    }

    if (unionSet.getSetCount() > 1)
      printf("0\n");
    else
    {
      printf("%d\n", cut.getMinimumCut(graph));
    }
  }
  return 0;
}
