#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

struct Matrix
{
  int R, C;
  vector<vector<long double> > data;

  Matrix(int r,int c) 
  {
    R = r;
    C = c;
    data = vector<vector<long double> >(R, vector<long double>(C, 0));
  }

  Matrix(const Matrix & x) 
  {
    R = x.R;
    C = x.C;
    data = x.data;
  }

  /** merge this matrix with matrix right */
  Matrix rightMergeMatrix(Matrix & right)
  {
    if (right.R != R) 
      return (*this);

    Matrix newMatrix(R, C + right.C);
    for (int i = 0; i < R; ++i)
      for (int j = 0; j < newMatrix.C; ++j)
        if (j < C)
          newMatrix.data[i][j] = data[i][j];
        else
          newMatrix.data[i][j] = right.data[i][j - C];
    return newMatrix;
  }
};

ostream & operator << (ostream & out , Matrix & a)
{
  for (int i = 0; i < a.R; ++i) {
    for (int j = 0; j < a.C; ++j)
      out << setprecision(3) << a.data[i][j] << "\t";
    out << endl;
  }
  return out;
}

/** 
 * Return the det of this matrix, 
 * ensure that the this is a square matrix
 * @see side effect matrix will change
 */
long double det(Matrix & a)
{
  long double ret = 1;
  long double zero = 0;
  int sign = 0;

  int i, j, k;
  long double t;
  for (i = 0; i < a.R; i++)
  {
    if (a.data[i][i] == zero)
    {
      for (j = i + 1; j < a.R; j++)
        if (!(a.data[j][i] == zero))
          break;
      if (j == a.R)
        return 0;
      for (k = i; k < a.R; k++)
        t = a.data[i][k], a.data[i][k] = a.data[j][k], a.data[j][k] = t;
      sign++;
    }

    /** if we could find leading one or negative one in this colume, swap */
    long double minusOne = -1;
    long double one = 1;
    for (j = i + 1; j < a.R; ++j)
      if (a.data[j][i] == one || a.data[j][i] == minusOne)
      {
        for (k = i; k < a.R; ++k)
          t = a.data[i][k], a.data[i][k] = a.data[j][k], a.data[j][k] = t;
        sign++;
        break;
      }

    ret = ret * a.data[i][i];
    for (k = i + 1; k < a.R; k++)
      a.data[i][k] = a.data[i][k] / a.data[i][i];

    for (j = i + 1; j < a.R; j++)
    {
      for (k = i + 1; k < a.R; k++)
      {
        long double temp = a.data[j][i] * a.data[i][k];
        a.data[j][k] = a.data[j][k] - temp;
      }
      a.data[j][i] = zero;
    }
  }
  if (sign & 1)
    ret = 0 - ret;
  return ret;
}

/** 
 * This class solve the problem which given a undirected graph, counting its different kinds of 
 * spanning tree
 * @see Kirchhoff matrix-tree theory 
 */
class CountSpanningTree
{
  public:
    
    /** 
     * @constrain input graph undirected, symmetric input 
     * @return string: the string representation of the number 
     */
    string getSpanningTreeCount(vector<vector<bool> > & graph)
    {
      int N = graph.size();
      Matrix matrix(N, N);

      for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
          matrix.data[i][j] = 0;

      long double one = 1;
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
          if (graph[i][j])
            matrix.data[i][i] = matrix.data[i][i] + one;
          if (graph[i][j])
            matrix.data[i][j] = -1;
        }

      Matrix remainMatrix(N - 1, N - 1);
      for (int i = 1; i < N; ++i)
        for (int j = 1; j < N; ++j)
          remainMatrix.data[i - 1][j - 1] = matrix.data[i][j];

      long double ret = det(remainMatrix);
      ret += 0.0001;
      long long ans = (long long)ret;
      char temp[100];
      sprintf(temp, "%lld", ans);
      return string(temp);
    }
};

int N, M, K;
void deal()
{
  vector<vector<bool> > graph(N, vector<bool>(N, true));
  for (int i = 0; i < N; ++i)
    graph[i][i] = false;

  for (int i = 0; i < M; ++i)
  {
    int s, t;
    scanf("%d%d", &s, &t);
    s--;
    t--;
    graph[s][t] = false;
    graph[t][s] = false;
  }

  CountSpanningTree cpt;
  cout << cpt.getSpanningTreeCount(graph) << endl;
}

int main()
{
  while (scanf("%d%d%d", &N, &M, &K) == 3)
    deal();
  return 0;
}
