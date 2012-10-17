#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <sstream>
#include <set>
#include <map>
#include <ctime>
#include <string>
#include <vector>
#include <utility>
#include <string.h>
#include <cassert>
#include <queue>

using namespace std;

#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

template <class T>
ostream & operator << (ostream & out, const vector<T> & data)
{ out << "["; for (int i = 0; i < (int) data.size(); ++i) out << data[i] << (i == data.size() - 1 ? "" : ","); out << "]"; return out; }

template <class T>
ostream & operator << (ostream & out, const set<T> & s)
{ out << "{"; for (typename set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

template <class T>
ostream & operator << (ostream & out, const multiset<T> & s)
{ out << "{"; for (typename multiset<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

template <class T1, class T2>
ostream & operator << (ostream & out, const pair<T1, T2> & p)
{ out << "(" << p.first << "," << p.second << ")"; return out; }

template <class T1, class T2>
ostream & operator << (ostream & out, const map<T1, T2> & m)
{ 
  for (typename map<T1, T2>::const_iterator itr = m.begin(); itr != m.end(); ++itr)
    out << itr->first << "->" << itr->second << " ";
  return out;
}

template <class T>
void sortandunique(vector<T> & a)
{
  sort(a.begin(), a.end());
  a.resize(unique(a.begin(), a.end()) - a.begin());
}

/**
 @ OMG Segment Tree range from 1 .. N
 @ warning : valid offset start from 1
 */
const long long INFI = 999999999LL * 99999999LL;

struct SegmentTree
{
  // fix
  int N;
  vector<int> height;
  vector<int> len;
  int M;
  void up(int x) { while (x > 1) { inlineup(x >> 1); x >>= 1; } }
  void down(int x) { for (int i = height[1]; i >= 1; --i) inlinedown(x >> i); }
  
  // prob spec
  vector<long long> delta;
  vector<long long> sum;

  SegmentTree(int n)
  {
    // fix
    N = n;
    M = 1;
    while (M < N + 2) M <<= 1;
    height.resize(M + M, 0);
    len.resize(M + M, 0);
    for (int i = M; i < M + M; ++i) len[i] = 1;
    for (int i = M - 1; i >= 1; --i)
    {
      len[i] = len[i + i] << 1;
      height[i] = height[i + i] + 1;
    }
    
    // problem spec
    delta.resize(M + M, 0);
    sum.resize(M + M, 0);
  }
  
  // init the segment by initial value, important for spped up
  void init(vector<int> & ps, vector<int> & vs)
  {
    for (int i = 0; i < ps.size(); ++i)
    {
      int p = ps[i] + M;
      int v = vs[i];
      // prob spec 
      delta[p] = v;
      sum[p] = v;
    }
    for (int i = M - 1; i >= 1; --i) inlineup(i);
  }
  
  inline void inlinedown(int f)
  {
    int ls = f + f;
    int rs = f + f + 1;
    
    // prob spec
    delta[ls] += delta[f]; 
    delta[rs] += delta[f];
    sum[ls] += delta[f] * len[ls];
    sum[rs] += delta[f] * len[rs];
    delta[f] = 0;
  }
  
  inline void inlineup(int f)
  {
    int ls = f + f;
    int rs = f + f + 1;
    
    // prob spec
    sum[f] = sum[ls] + sum[rs] + delta[f] * len[f];
  }
  
  void update(int l, int r, int d)
  {
    if (l > r) return;
    l += M - 1; r += M + 1;
    int ll = l; int rr = r;
    //down(ll); down(rr);
    while (true)
    {
      if ((l ^ r) == 1) break;
      if ((l & 1) == 0) 
      {
        // prob spec
        int n = l ^ 1;
        delta[n] += d;
        sum[n] += (long long) d * len[n];
      }
      if ((r & 1) == 1)
      {
        // prob spec
        int n = r ^ 1;
        delta[n] += d;
        sum[n] += (long long) d * len[n];
      }
      l >>= 1; r >>= 1;
    }
    up(ll); up(rr);
  }
  
  long long query(int l, int r)
  {
    l += M - 1; r += M + 1;
    down(l); down(r);
    
    long long ret = 0;
    while (true)
    {
      if ((l ^ r) == 1) break;
      if ((l & 1) == 0)
      {
        // prob spec
        int n = l ^ 1;
        ret += sum[n];
      }
      if ((r & 1) == 1)
      {
        // prob spec
        int n = r ^ 1;
        ret += sum[n];
      }
      l >>= 1; r >>= 1;
    }
    return ret;
  }
};

int N, Q;
void init()
{
  vector<int> p, v;
  scanf("%d%d", &N, &Q);
  
  for (int i = 0; i < N; ++i)
  {
    int a;
    scanf("%d", &a);
    p.push_back(i + 1);
    v.push_back(a);
  }
  
  SegmentTree tree(N);
  tree.init(p, v);
  
  while (Q--)
  {
    char c;
    int a, b;
    scanf(" %c %d%d", &c, &a, &b);
    if (c == 'Q')
    {
      //debug2(a, b);
      long long ans = tree.query(a, b);
      cout << ans << endl;
    }
    else
    {
      int d;
      scanf("%d", &d);
      tree.update(a, b, d);
    }
  }
}

void york()
{
  
}

int main()
{
  init();
  york();
  return 0;
}
