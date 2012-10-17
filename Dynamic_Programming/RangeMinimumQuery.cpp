#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

/**
* RMQ Sparse Table approach
* Init: O(N log N)
* Query: O(1)
* tested http://www.codeforces.com/problemset/problem/6/E
*/
class RMQ_ST
{
private:
  const static int RMQ_LOGMAX = 20;
  const static int RMQ_MAXN = 200000;

  /** the binary len for each int */
  vector<int> intLen;

  /** the sparse table */
  int M[RMQ_MAXN][RMQ_LOGMAX];

public:
  /** the source value */
  vector<int> value;

private:
  int N;

  /** return the len of given integer by binary representation */
  inline int getIntLen(int key)
  {
    int len = 0;
    while (key>0)
    {
      len++;
      key >>= 1;
    }
    return len;
  }

public:
  RMQ_ST(int n)
  {
    N = n;
    assert(N <= RMQ_MAXN);
    intLen = vector<int>(N + 1);
    value = vector<int>(N);

    for (int i = 0; i <= N; ++i)
      intLen[i] = getIntLen(i);
  }

  inline void setValue(int posi , int value)
  { this->value[posi] = value; }

  /** Pre calculate the RMQ array for further query */
  void initRMQ()
  {
    for (int i = 0; i < N; ++i)
      M[i][0] = i;
    for (int j = 1; (1 << j) <= N; ++j)
    {
      int upper = N + 1 - (1 << j);
      int step = 1 << (j - 1);
      for (int i = 0; i < upper; ++i)
      {
        if (value[M[i][j-1]] < value[M[i+step][j-1]])
          M[i][j] = M[i][j-1];
        else
          M[i][j] = M[i+step][j-1];
      }
    }
  }

  /** return the min value in the query range */
  int RMQ_value(int start,int stop)
  {
    int k = (stop - start +1);
    k = intLen[k] - 1;
    return min(value[M[start][k]] , value[M[stop-(1<<k)+1][k]]);
  }

  /** return the min value position in the query range */
  int RMQ_posi(int start,int stop)
  {
    int k = (stop - start + 1);
    k = intLen[k] - 1;
    if (value[M[start][k]] <= value[M[stop-(1<<k)+1][k]]) 
      return M[start][k];
    else 
      return M[stop-(1<<k)+1][k];
  }
};

/** RMQ segment tree approach 
* Init: O(N)
* Query: O(log N)
* Remember in this implementation , in segment tree 
* Node count from 1
* not Zero ~~~~~~!!!!
* because we need to cal the left son by * 2 
* 0 * 2 = 0
* but value start from 0 doesn't matter
*/
class RMQ_SEGMENT_TREE
{
private:
  int N;

  /** represent the range's minimal position */
  vector<int> tree;

  /** return the len of given integer by binary representation */
  inline int getIntLen(int key)
  {
    int len = 0;
    while (key>0)
    {
      len++;
      key >>= 1;
    }
    return len;
  }

public:
  vector<int> value;

  /**
  * Segment range [0,N]
  */
  RMQ_SEGMENT_TREE(int n)
  {
    N = n;
    value = vector<int>(N);
    int treeSpace = getIntLen(N) + 1;
    treeSpace = 1 << treeSpace;
    tree = vector<int>(treeSpace , -1);
  }


  void initRMQ(int nowNode , int begin , int end)
  {
    if (begin == end) {
      tree[nowNode] = end;
      return;
    }

    int mid = (begin + end) >> 1;
    initRMQ(nowNode * 2 , begin , mid);
    initRMQ(nowNode * 2 + 1 , mid + 1 , end);
    int leftMin = value[tree[nowNode * 2]];
    int rightMin = value[tree[nowNode * 2 + 1]];
    if (leftMin < rightMin)
      tree[nowNode] = tree[nowNode * 2];
    else
      tree[nowNode] = tree[nowNode * 2 + 1];
  }

  void initRMQ()
  {
    initRMQ(1 , 0 , N - 1);
  }


  int RMQ_posi(int nowNode, int nowRangeStart, int nowRangeStop, int begin, int end)
  {
    if (nowRangeStop < begin || nowRangeStart > end) 
      return -1;
    if (nowRangeStart >= begin && nowRangeStop <= end)
      return tree[nowNode];

    int mid = (nowRangeStart + nowRangeStop) >> 1;
    int leftMinPosi = RMQ_posi(nowNode * 2 , nowRangeStart , mid , begin , end);
    int rightMinPosi = RMQ_posi(nowNode * 2 + 1, mid + 1, nowRangeStop, begin, end);

    if (leftMinPosi == -1)
      return rightMinPosi;
    if (rightMinPosi == -1)
      return leftMinPosi;

    int leftMinValue = value[leftMinPosi];
    int rightMinValue = value[rightMinPosi];
    if (leftMinValue < rightMinValue)
      return leftMinPosi;
    else
      return rightMinPosi;
  }

  /** range [start,stop] minimal */
  int RMQ_value(int start , int stop)
  {
    int posi = RMQ_posi(1 , 0 , N - 1, start , stop);
    return value[posi];
  }

  int RMQ_posi(int start , int stop)
  {
    return RMQ_posi(1 , 0 , N - 1 , start , stop);
  }
};

int main()
{
  int N , Q;

  while (scanf("%d%d",&N,&Q)==2)
  {
    RMQ_SEGMENT_TREE * minHeight = new RMQ_SEGMENT_TREE(N);
    RMQ_SEGMENT_TREE * maxHeight = new RMQ_SEGMENT_TREE(N);

    for (int i = 0; i < N; ++i) 
      scanf("%d",&minHeight->value[i]);
    minHeight->initRMQ();

    for (int i = 0; i < N; ++i) 
      maxHeight->value[i] = -minHeight->value[i];
    maxHeight->initRMQ();

    int start , stop , minH , maxH;
    for (int i = 0; i < Q; ++i)
    {
      scanf("%d%d", &start, &stop);
      minH = minHeight->RMQ_value(start-1,stop-1);
      maxH = maxHeight->RMQ_value(start-1,stop-1);
      printf("%d\n",(-maxH) - minH);
    }

    delete minHeight;
    delete maxHeight;
  }
  return 0;
}
