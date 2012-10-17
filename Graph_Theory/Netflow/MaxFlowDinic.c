#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define MAXN 10010  
#define MAXM 2000000 
#define INF 2100000000  

struct Edge   
{   
	int  st, ed;   //边的起点和终点 
	int  next;     //以st为起点的下一条边的下标 
	int  flow;     //边的剩余容量 
  int  oriFlow;
}edge[MAXM];   

//head 链接表的头结点， d是剩余图中每个点对应的层次 
int head[MAXN], d[MAXN];    

//N = V, 题目输入边的条数，E是构图后边的条数,src = 源点，dest = 汇点 
int E, src, dest;   

// 属于割集S的顶点
//vector<int> inCutS;
//vector<int> inCutT;

void Init(int s, int t)   
{   
  E = 0;   
  src = s;   
  dest = t;   
  memset(head, -1, sizeof(head));   
}   

void add_edge(int  u, int v, int w1, int w2)   
{   
  edge[E].st = u; edge[E].ed = v;   
  edge[E].flow = w1; edge[E].next = head[u];  
  edge[E].oriFlow = w1; 
  head[u] = E++;   
  
  edge[E].st = v; edge[E].ed = u;   
  edge[E].flow = w2; edge[E].next = head[v];  
  edge[E].oriFlow = w2; 
  head[v] = E++;   
}   

/**
void add_edge(int u, int v, int w)
{
  edge[E].st = u; edge[E].ed = v;   
  edge[E].flow = w; edge[E].next = head[u];  
  edge[E].oriFlow = w;
  head[u] = E++;   
  
  edge[E].st = v; edge[E].ed = u;   
  edge[E].flow = 0; edge[E].next = head[v]; 
  edge[E].oriFlow = 0;
  head[v] = E++;   
}
*/

int dinic_bfs()   
{   
  int  i, j;   
  int que[MAXN]; int rear = 1;  

  memset(d, -1, sizeof(d));   
  que[0] = src; d[src] = 0;   
  for(i = 0; i < rear; i++)   
    for(j = head[que[i]]; j != -1; j = edge[j].next)   
      if(d[edge[j].ed] == -1 && edge[j].flow > 0)   
      {   
        d[edge[j].ed] = d[que[i]]+1;   
        que[rear++] = edge[j].ed;   
      }   
  
  /**
  if (d[dest] < 0)
  {
    inCutS.clear();
    inCutT.clear();
    for (int i = 0; i < MAXN; ++i) 
      if (d[i] >= 0) inCutS.push_back(i);
      else inCutT.push_back(i);
  }
  */
  
  return  d[dest] >= 0;   
}   

int dinic_dfs()   
{   
  int  stk[MAXN], top = 0;   
  int  ans = 0, cur, ptr, pre[MAXN], minf, i;   
  int  del[MAXN];   
  memset(del, 0, sizeof(del));   
  
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

int Dinic()   
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

void outputEdge(int nodeid)
{
  int id = head[nodeid];
  while (id >= 0)
  {
    printf("%d\n", edge[id]);
    id = edge[id].next;
  }
}

///////////////////////////////////////////////
// TEMPLATE FINISHED
///////////////////////////////////////////////

int N;
int M;
int x[20000], y[20000];

void init()
{
  int i, a, b, c, ans;

  scanf("%d", &N);
  for (i = 0; i < N; ++i)
    scanf("%d%d", &x[i], &y[i]);

  Init(0, N - 1);
  scanf("%d", &M);

  for (i = 0; i < M; ++i)
  {
    scanf("%d%d%d", &a, &b, &c);
    a--; b--;
    add_edge(a, b, c, c);
  }

  ans = Dinic();
  printf("%d\n", ans);

  for (i = 0; i < E; i += 2)
  {
      if (edge[i].oriFlow >= edge[i].flow)
        printf("%d %d %d\n", edge[i].st + 1, edge[i].ed + 1, edge[i].oriFlow - edge[i].flow);
      else
        printf("%d %d %d\n", edge[i].ed + 1, edge[i].st + 1, edge[i].flow - edge[i].oriFlow);
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