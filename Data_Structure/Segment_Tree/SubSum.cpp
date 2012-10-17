#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <algorithm>
#include <queue>
#include <utility>
#include <sstream>
#include <bitset>
#include <stdio.h>
using namespace std;

#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

template <class T>
ostream & operator << (ostream & out, const vector<T> & data)
{ out << "["; for (int i = 0; i < data.size(); ++i) out << data[i] << " "; out << "]"; return out; }

template <class T>
ostream & operator << (ostream & out, const set<T> & s)
{ out << "{"; for (typename set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

template <class T>
ostream & operator << (ostream & out, const multiset<T> & s)
{ out << "{"; for (typename multiset<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

/////// BEGIN CODE //////////////////
//////////////////////////
// QUERY [L, R] subsum or 
// QUERY [L, R] f[i] * i^k subsum
const int ORDER = 3;
const int MAXN = 100000;
long long powsums[ORDER][MAXN + 1];
void initpowsums()
{
  memset(powsums, 0, sizeof(powsums));
  for (int k = 0; k < ORDER; ++k)
  {
    powsums[k][1] = 1;
    for (int i = 2; i <= MAXN; ++i)
    {
      long long d = 1;
      for (int j = 0; j < k; ++j) d = d * i;
      powsums[k][i] = powsums[k][i - 1] + d;
    }
  }
}

struct Node
{
  long long delta[ORDER];
  long long subsum[ORDER];
  int l, r, mid;
  int len;
  Node * ls, * rs;
  
  void output(ostream & out, int indent)
  {
    for (int i = 0; i < indent; ++i) out << " ";
    out << "[" << l << "," << r << "] " << subsum[0] << "," << delta[0] << endl;
    if (ls != NULL) ls->output(out, indent + 1);
    if (rs != NULL) rs->output(out, indent + 1);
  }
  
  Node(int ll, int rr)
  {
    l = ll; r = rr;
    len = r - l + 1;
    mid = (l + r) >> 1;
    memset(delta, 0, sizeof(delta));
    memset(subsum, 0, sizeof(subsum));
    ls = rs = NULL;
    if (l == r) return;
    
    ls = new Node(l, mid);
    rs = new Node(mid + 1, r);
  }
  
  void update(int ll, int rr, long long d)
  {
    for (int k = 0; k < ORDER; ++k)
      subsum[k] += d * (powsums[k][rr] - powsums[k][ll - 1]);
    
    if (l == ll && r == rr) 
    {
      for (int k = 0; k < ORDER; ++k)
        delta[k] += d;
      return;
    }
    
    if (rr <= mid) return ls->update(ll, rr, d);
    if (ll > mid) return rs->update(ll, rr, d);
    ls->update(ll, mid, d);
    rs->update(mid + 1, rr, d);
  }
  
  long long query(int ll, int rr, int k)
  {
    if (l == ll && r == rr) return subsum[k];
    
    long long ret = delta[k] * (powsums[k][rr] - powsums[k][ll - 1]);
    if (ll <= mid) ret += ls->query(ll, min(rr, mid), k);
    if (rr > mid) ret += rs->query(max(mid + 1, ll), rr, k);
    return ret;
  }
};

Node * root;
int N, M;

long long tt[1000];
void brute_update(int a, int b, int d)
{
  for (int i = a; i <= b; ++i)
    tt[i] += d;
}

long long brute_query(int a, int b)
{
  long long ans = 0;
  for (int i = a; i <= b; ++i)
  {
    long long t = tt[i];
    ans += t * (i - a + 1) * (b - i + 1);
  }
  return ans;
}

vector<char> oper;
vector<int> a, b, d;

void init()
{
  initpowsums();
  scanf("%d%d", &N ,&M);
  //N = 100; M = 400;
  
  oper.resize(M);
  a.resize(M);
  b.resize(M);
  d.resize(M);
  //  
  //  for (int i = 0; i < M; ++i)
  //  {
  //    oper[i] = (rand() % 2) ? 'c' : 'e';
  //    do 
  //    {
  //      a[i] = rand() % N + 1;
  //      b[i] = rand() % N + 1;
  //      d[i] = rand() % 100;
  //    } while(a[i] >= b[i]);
  //  }
  
  char temp[20];
  for (int i = 0; i < M; ++i)
  {
    scanf("%s", temp);
    oper[i] = temp[0];
    if (oper[i] == 'c')
      scanf("%d%d%d", &a[i], &b[i], &d[i]);
    else
      scanf("%d%d", &a[i], &b[i]);
  }
  
  root = new Node(1, N - 1);
  
  
  memset(tt, 0, sizeof(tt));
  for (int i = 0; i < M; ++i)
  {
    if (oper[i] == 'c')
    {
      root->update(a[i], b[i] - 1, d[i]);
      //      brute_update(a[i], b[i] - 1, d[i]);
      //debug3(a[i], b[i], d[i]);
      //root->output(cout, 0);
    }
    else
    {
      //debug2(a[i], b[i]);
      long long coff1 = (long long) b[i] - (long long) a[i] * b[i];
      long long ans1 = root->query(a[i], b[i] - 1, 0);
      long long coff2 = (long long) (b[i] + a[i] - 1);
      long long ans2 = root->query(a[i], b[i] - 1, 1);
      long long coff3 = -1;
      long long ans3 = root->query(a[i], b[i] - 1, 2);
      //debug3(ans1, ans2, ans3);
      //debug3(coff1, coff2, coff3);
      long long ans = ans1 * coff1 + ans2 * coff2 + ans3 * coff3;
      
      //      long long ansb = brute_query(a[i], b[i] - 1);
      //      if (ansb != ans) 
      //      {
      //        debug2(ansb, ans); 
      //        return;
      //      }
      long long way = b[i] - a[i] + 1;
      way = (way - 1) * way / 2;
      double da = (double) ans / (double) way;
      printf("%.8f\n", da);
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