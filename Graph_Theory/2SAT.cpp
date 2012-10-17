#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <cmath>
#include <cstdio>
#include <utility>
using namespace std;

/** 
 * The class solve the strongly connected component problem in directed graph
 * We implemented the Tarjan algorithm 
 * @see http://www.byvoid.com/blog/scc-tarjan/
 */
class SCC
{
  public:
    int N;
    int index;

    /** dfn, low start from one, set to zero means not visited yet */
    vector<int> dfn;
    vector<int> low;

    stack<int> nowStack;
    vector<bool> inStack;

    void tarjan(vector<vector<int> > & graph, int u, vector<vector<int> > & scc)
    {
      dfn[u] = low[u] = ++index;
      nowStack.push(u);
      inStack[u] = true;

      for (int i = 0; i < graph[u].size(); ++i)
      {
        int v = graph[u][i];
        if (!dfn[v])
        {
          tarjan(graph, v, scc);
          low[u] = min(low[u], low[v]);
        }
        else
        {
          if (inStack[v])
            low[u] = min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u])
      {
        vector<int> nscc;
        while (true)
        {
          int v = nowStack.top();
          nowStack.pop();
          inStack[v] = false;
          nscc.push_back(v);
          if (v == u) break;
        }
        scc.push_back(nscc);
      }
    }

    /** 
     * @param graph     the adjanency linked list 
     */
    vector<vector<int> > getSCC(vector<vector<int> > & graph)
    {
      N = graph.size();
      index = 0;
      dfn = vector<int>(N, 0);
      low = vector<int>(N);
      inStack = vector<bool>(N, false);
      nowStack = stack<int>();

      vector<vector<int> > ret;
      for (int i = 0; i < N; ++i)
      {
        if (!dfn[i])
          tarjan(graph, i, ret);
      }
      return ret;
    }
};

/** 
 * A formula of propositional logics is in 2CNF if it has the form
 * C_1 ^ C_2 ... ^ C_m
 * where the C_i are clauses of size 2.
 * A clause of size two has the form A \/ B where A and B are literals
 * A literal has the form x or -|x where x is a variable of propositional
 * calculus that can take the values true of false
 * A formula of propositional calculus is satisfiable if there is 
 * an assignment of truth values to its variables so that the formula 
 * evaluates to true using the usual semantics of propositional calculus.
 * The 2SAT problem is to decide whether a given 2CNF formula F is satisfiable. 
 * Furthermore, if F is satisfiable, we want an assignment of 
 * truth values to its variables proving satisfiability. If F is not 
 * satisfiable, we would like to output a proof of unsatisfiability.
 */
class SAT2
{
  public:
    int nVariables;

    inline int getCorrespondID(int id)
    { return id >= nVariables ? id - nVariables : id + nVariables; }

    /** This function solve the SAT2 problem
     * @param N         the number of variables
     * @param clauses   the clauses .first the first literal, .second the second literal
     * @see input representation        1..N represent the positive literals
     *                                  -1..-N represent the negative literals
     * @see graph node representation   0..N-1 represent the positive literals
     *                                  N..2*N-1 represent the negative literals 
     * @param assign    the assignment for each literal, it SAT2 is satisfied
     * @return          F is satisfiable or not
     */
    bool solveSAT2(int N, vector<pair<int, int> > clauses, vector<bool> & assign)
    {
      nVariables = N;
      assign = vector<bool>(nVariables, false);

      /** First part, build the directed graph */
      vector<vector<int> > graph(N * 2);
      for (int i = 0; i < clauses.size(); ++i)
      {
        int x = clauses[i].first;
        x = (x > 0 ? x - 1 : -x + N - 1);
        int nx = getCorrespondID(x);

        int y = clauses[i].second;
        y = (y > 0 ? y - 1 : -y + N - 1);
        int ny = getCorrespondID(y);
        graph[nx].push_back(y);
        graph[ny].push_back(x);

        cout << nx << "\t" << y << endl;
        cout << ny << "\t" << x << endl;
      }


      /** Find SCC of this graph, contract the nodes get the DAG */
      SCC scc;
      vector<vector<int> > sccs = scc.getSCC(graph);

      /** Check whether x and -|x is in a same component, if so, return false */
      vector<int> belongTo(nVariables * 2, -1);
      for (int i = 0; i < sccs.size(); ++i)
      {
        for (int j = 0; j < sccs[i].size(); ++j)
        {
          cout << sccs[i][j] << " ";
          int id = sccs[i][j];
          int cid = getCorrespondID(id);
          /** if the corespond literal is already in this component, then return false */
          if (belongTo[cid] == i) return false;
          belongTo[id] = i;
        }
        cout << endl;
      }
      
      return true;
    }
};

int main()
{
  SAT2 sat2;
  vector<pair<int, int> > clauses;
  clauses.push_back(make_pair(1, 2));
  clauses.push_back(make_pair(-1, 2));
  clauses.push_back(make_pair(1, -2));
  int N = 2;
  vector<bool> ret;

  bool ans = sat2.solveSAT2(N, clauses, ret);
  cout << ans << endl;
  return 0;
}


