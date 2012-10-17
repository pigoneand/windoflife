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
#include <cassert>
#include <fstream>
#include <sstream>
#include <bitset>
#include <stack>
#include <list>
#include <ctime>
using namespace std;
#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

// http://acm.timus.ru/problem.aspx?space=1&num=1774
// http://acm.timus.ru/problem.aspx?space=1&num=1736
/**
 template <class T>
 ostream & operator << (ostream & out, const vector<T> & t)
 {	out << t.size() << " {";	for (int i = 0; i < t.size(); ++i) 		out << t[i] << " ";	out << "}";	return out;}
 
 template <class T>
 ostream & operator << (ostream & out, const set<T> & t)
 {	out << "{";	for (set<T>::iterator itr = t.begin(); itr != t.end(); ++itr)		out << *itr << " ";	out << "}";	return out;}
 */

const  int MAXN = 2048;   
const  int MAXM = 2000000;   
const  int INF  = 1000000000;   

struct  Edge   
{   
	int  st, ed;   //边的起点和终点 
	int  next;     //以st为起点的下一条边的下标 
	int  flow;     //边的剩余容量 
  
	friend ostream & operator << (ostream & out, Edge & edge)
	{
		out << edge.st << "->" << edge.ed << " " << edge.flow;
		return out;
	}
}edge[MAXM];   

//head 链接表的头结点， d是剩余图中每个点对应的层次 
int head[MAXN], d[MAXN];    

//N = V, 题目输入边的条数，E是构图后边的条数,src = 源点，dest = 汇点 
int E, src, dest;   

// 属于割集S的顶点
vector<int> inCutS;
vector<int> inCutT;

void Init(int s, int t)   
{   
  E = 0;   
  src = s;   
  dest = t;   
  memset(head, -1, sizeof(head));   
}   

inline void add_edge(int  u, int v, int w1, int w2)   
{   
  edge[E].st = u; edge[E].ed = v;   
  edge[E].flow = w1; edge[E].next = head[u];   
  head[u] = E++;   
  
  edge[E].st = v; edge[E].ed = u;   
  edge[E].flow = w2; edge[E].next = head[v];   
  head[v] = E++;   
}   

inline void add_edge(int u, int v, int w)
{
  edge[E].st = u; edge[E].ed = v;   
  edge[E].flow = w; edge[E].next = head[u];   
  head[u] = E++;   
  
  edge[E].st = v; edge[E].ed = u;   
  edge[E].flow = 0; edge[E].next = head[v];   
  head[v] = E++;   
}

inline bool dinic_bfs()   
{   
  int  i, j;   
  memset(d, -1, sizeof(d));   
  int  que[MAXN], rear = 1;   
  que[0] = src; d[src] = 0;   
  for(i = 0; i < rear; i++)   
    for(j = head[que[i]]; j != -1; j = edge[j].next)   
      if(d[edge[j].ed] == -1 && edge[j].flow > 0)   
      {   
        d[edge[j].ed] = d[que[i]]+1;   
        que[rear++] = edge[j].ed;   
      }   
  
  if (d[dest] < 0)
  {
    inCutS.clear();
    inCutT.clear();
    for (int i = 0; i < MAXN; ++i) 
      if (d[i] >= 0) inCutS.push_back(i);
      else inCutT.push_back(i);
  }
  
  return  d[dest] >= 0;   
}   

inline int dinic_dfs()   
{   
  int  stk[MAXN], top = 0;   
  int  ans = 0, cur, ptr, pre[MAXN], minf, i;   
  bool  del[MAXN];   
  memset(del, false, sizeof(del));   
  
  stk[top++] = 0;    
  pre[src] = 0; cur = src;   
  while(top)   
  {   
    while(cur != dest && top)   
    {   
      for(i = head[cur]; i != -1; i = edge[i].next)   
      {   
        if(d[edge[i].ed] == d[cur]+1 && edge[i].flow > 0 && !del[edge[i].ed])   
        {   
          stk[top++] = edge[i].ed;   
          cur = edge[i].ed;   
          pre[edge[i].ed] = i;   
          break;   
        }   
      }   
      if(i == -1)   
      {   
        del[cur] = 1;   
        top--;   
        if(top) cur = stk[top-1];   
      }   
    }   
    //update the flow   
    if(cur == dest)   
    {   
      minf = INF;   
      while(cur != src)   
      {   
        cur = pre[cur];   
        if(edge[cur].flow < minf) minf = edge[cur].flow;   
        cur = edge[cur].st;   
      }   
      cur = dest;   
      while(cur != src)   
      {   
        cur = pre[cur];   
        edge[cur].flow -= minf;   
        edge[cur^1].flow += minf;   
        if(edge[cur].flow == 0) ptr = edge[cur].st;   
        cur = edge[cur].st;   
      }   
      while(top > 0 && stk[top-1] != ptr) top--;   
      if(top)  cur = stk[top-1];   
      ans += minf;   
    }   
  }   
  return  ans;   
}   

inline int Dinic()   
{   
  int  ans = 0, t;   
  while(dinic_bfs())   
  {   
    t = dinic_dfs();   
    if(t) ans += t;   
    else  break;   
  }   
  return  ans;   
}   

inline void outputEdge(int nodeid)
{
  int id = head[nodeid];
  while (id >= 0)
  {
    cout << edge[id] << endl;
    id = edge[id].next;
  }
}

///////////////////////////////////////////////
// TEMPLATE FINISHED
///////////////////////////////////////////////

string line, pattern;
inline char random_char()
{
  int x = rand() % 3;
  if (x == 0) return '0';
  if (x == 1) return '1';
  return '?';
}

void init()
{
  /**
  line = string(1000, ' ');
  pattern = string(500, ' ');
  for (int i = 0; i < line.length(); ++i)
    line[i] = random_char();
  for (int i = 0; i < pattern.length(); ++i)
    pattern[i] = random_char();
  */
  
  int start = clock();
  cin >> line >> pattern;
  int source = 0;
  int N = (int) line.length();
  int M = (int) pattern.length();
  int sink = N + M + 1;
  
  Init(source, sink);
  
  vector<int> line0(N, 0);
  vector<int> line1(N, 0);
  vector<int> pattern0(M, 0);
  vector<int> pattern1(M, 0);
  for (int i = 0; i < line.length(); ++i)
  {
    if (line[i] == '1') line0[i] = INF;
    if (line[i] == '0') line1[i] = INF;
  }
  
  for (int i = 0; i < pattern.length(); ++i)
  {
    if (pattern[i] == '1') pattern0[i] = INF;
    if (pattern[i] == '0') pattern1[i] = INF;
  }
  
  int ans = 0;
  for (int i = 0; i + M - 1 < N; ++i)
    for (int j = 0; j < M; ++j)
    {
      int ni = i + j;
      if (line[ni] == '?' && pattern[j] == '?')
      {
        add_edge(ni + 1, N + 1 + j, 1, 1);
        continue;
      }
      if (line[ni] == '?')
      {
        if (pattern[j] == '1') line0[ni]++; 
        else line1[ni]++;
        continue;
      }
      if (pattern[j] == '?')
      {
        if (line[ni] == '1') pattern0[j]++;
        else pattern1[j]++;
        continue;
      }
      if (line[ni] != pattern[j]) ans++;
    }
  
  for (int i = 0; i < N; ++i)
  {
    if (line0[i] > 0) add_edge(i + 1, sink, line0[i], 0);
    if (line1[i] > 0) add_edge(source, i + 1, line1[i], 0);
  }
  
  for (int i = 0; i < M; ++i)
  {
    if (pattern0[i] > 0) add_edge(i + N + 1, sink, pattern0[i], 0);
    if (pattern1[i] > 0) add_edge(source, i + N + 1, pattern1[i], 0);
  }
  
  ans += Dinic();
  cout << ans << endl;
  for (int i = 0; i < N; ++i) 
    if (line[i] == '?') line[i] = '1';
  for (int i = 0; i < M; ++i)
    if (pattern[i] == '?') pattern[i] = '1';
  
  for (int i = 0; i < inCutS.size(); ++i)
  {
    int id = inCutS[i];
    if (id >= 1 && id <= N) line[id - 1] = '0'; 
    if (id >= N + 1 && id <= N + M) pattern[id - N - 1] = '0';
  }
  
  cout << line << endl;
  cout << pattern << endl;
  
  //cout << (clock() - start) / 1000 << endl;
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