/** SGU 122 AC */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
using namespace std;

class HamiltonCycle
{
  public:
    /** Each node in the cycle or not */
    vector<bool> in;

    /** Each node's position in cycle */
    vector<short int> posi;

    /** The current cycle */
    vector<short int> cycle;

    /** The linked matrix */
    vector<bitset<1000> > linked;

    /** just for debug */
    void print()
    {
      for (int i = 0; i < cycle.size(); ++i)
        cout << cycle[i] + 1 << " ";

      bool isPath = true;
      bool isCycle = true;
      for (int i = 0; i < cycle.size() - 1; ++i)
      {
        int now = cycle[i];
        int next = cycle[i + 1];
        if (!linked[now][next])
          isPath = false;
      }
      for (int i = 0; i < cycle.size(); ++i)
      {
        int now = cycle[i];
        int next = cycle[(i + 1) % cycle.size()];
        if (!linked[now][next])
          isCycle = false;
      }
      if (cycle.size() == 1) isCycle = true;

      if (isPath) cout << "ispath";
      else cout << "nopath";
      cout << " ";
      if (isCycle) cout << "iscycle";
      else cout << "nocycle";
      cout << endl;
    }

    void updatePosi()
    {
      for (int i = 0; i < posi.size(); ++i)
        posi[i] = -1;

      for (int i = 0; i < cycle.size(); ++i)
        posi[cycle[i]] = i;
    }

    bool buildCycle(const vector<vector<short int> > & graph)
    {
      int first = cycle[0];
      int last = cycle[cycle.size() - 1];
      int nowLen = cycle.size();

      /** If already is a cycle, return true */
      if (linked[last][first]) return true;

      /** try to construct a cycle */
      for (int i = 0; i < graph[last].size(); ++i)
      {
        int t1 = graph[last][i];
        if (in[t1])
        {
          int pt1 = posi[t1];
          int pt2 = pt1 + 1;
          int t2 = cycle[pt2];
          /** Find a way to construct a cycle */
          if (linked[t2][first])
          {
            vector<short int> newCycle;
            for (int j = 0; j <= pt1; ++j)
              newCycle.push_back(cycle[j]);
            for (int j = cycle.size() - 1; j >= pt2; --j)
              newCycle.push_back(cycle[j]);
            cycle = newCycle;
            updatePosi();
            return true;
          }
        }
      }
      return false;
    }

    bool cycleToPath(vector<vector<short int> > & graph)
    {
      for (int i = 0; i < cycle.size(); ++i)
      {
        int now = cycle[i];
        for (int j = 0; j < graph[now].size(); ++j)
        {
          int next = graph[now][j];
          if (!in[next])
          {
            in[next] = true;
            vector<short int> newCycle;
            newCycle.push_back(next);
            for (int k = i; k >= 0; --k)
              newCycle.push_back(cycle[k]);
            for (int k = cycle.size() - 1; k > i; --k)
              newCycle.push_back(cycle[k]);
            cycle = newCycle;
            updatePosi();

            return true;
          }
        }
      }
      return false;
    }

    /** 
     * @constrain       undirect graph 
     * @constrain       no self loop
     */
    bool getHamiltonCycle(vector<vector<short int> > & graph, vector<short int> & retCycle)
    {
      int N = graph.size();
      linked = vector<bitset<1000> >(N);
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < graph[i].size(); ++j)
        {
          linked[i][graph[i][j]] = true;
          linked[graph[i][j]][i] = true;
        }
      
      in = vector<bool>(N, false);
      posi = vector<short int>(N, -1);
      in[0] = true;
      posi[0] = 0;
      cycle.clear();
      cycle.push_back(0);

      /** Insert N - 1 nodes */
      for (int nowLen = 1; nowLen < N; ++nowLen)
      {
        bool found = false;
        int first = cycle[0];
        int last = cycle[nowLen - 1];

        /** Try to enlarge the path */
        for (int i = 0; i < graph[last].size(); ++i)
        {
          int newNode = graph[last][i];
          if (!in[newNode])
          {
            found = true;
            in[newNode] = true;
            cycle.push_back(newNode);
            posi[newNode] = nowLen;
            break;
          }
        }

        /** If not, or the last node, 
         * Need to construct a cycle, then change to path */
        if (!found)
        {
          if (!buildCycle(graph)) 
            return false;
          else
          {
            if (!cycleToPath(graph))
              return false;
          }
        }

        /** If it is the last node, try to construct a cycle */
        if (nowLen == N - 1)
          if (!buildCycle(graph))
            return false;
      }
      retCycle = cycle;
      return true;
    }
};

int main()
{
  int N;
  scanf("%d", &N);
  vector<vector<short int> > graph(N);
  
  char s[7000];
  int M = 6100;
  fgets(s, M, stdin);
  for(int i = 1; i <= N; i++) {
    fgets(s, M, stdin);
    int len = strlen(s);
    int k = 0;
    for (int j = 0; j < len; ++j)
    {
      if (s[j] < '0' || s[j] > '9')
      {
        if (k > 0)
        {
          graph[i - 1].push_back(k - 1);
          graph[k - 1].push_back(i - 1);
          k = 0;
        }
      }
      else
        k = k * 10 + s[j] - '0';
    }
    if (k > 0)
    {
      graph[i - 1].push_back(k - 1);
      graph[k - 1].push_back(i - 1);
    }
  }

  vector<short int> cycle;
  HamiltonCycle hc;
  bool found = hc.getHamiltonCycle(graph, cycle);

  if (!found)
  {
    cout << "No solution" << endl;
    return 0;
  }

  int onePosi = 0;
  for (int i = 0; i < cycle.size(); ++i)
    if (cycle[i] == 0) 
      onePosi = i;

  for (int i = 0; i < N; ++i)
    cout << cycle[(onePosi + i) % N] + 1 << " ";
  cout << 1 << endl;
  return 0;
}
