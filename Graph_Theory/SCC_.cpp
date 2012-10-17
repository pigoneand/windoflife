#include <iostream>
#include <vector>
using namespace std;

/*
   STRONGLY-CONNECTED-COMPONENTS(G)
   1 call DFS(G) to compute finishing times f[u] for each vertex u
   2 compute G'
   3 call DFS(G') but in the main loop of DFS, consider the vertices 
   in order of decreasing f[u] (as computed in line 1)
   4 output the vertices of each tree in the depth-first forest formed in line 3 as a 
   separate strongly connected component
   */

// 最大顶点数
const int MaxN = 2000 + 1;

vector<int> edge_in[MaxN];
vector<int> edge_out[MaxN];

int Count;
int pre[MaxN];
int post[MaxN];
int index[MaxN];

int post_stack[MaxN];
int sp;

int T,N,M;
bool visit[MaxN];

void DFS(int now)
{
  visit[now]=true;
  pre[now]=(++Count);
  for (int i=0;i<edge_out[now].size();++i)
  {
    if (!visit[edge_out[now][i]])
      DFS(edge_out[now][i]);
  }
  post[now]=(++Count);
  post_stack[++sp]=now;
}

void DFS_(int now,int ID)
{
  visit[now]=true;
  index[now]=ID;

  for (int i=0;i<edge_in[now].size();++i)
  {
    if (!visit[edge_in[now][i]])
      DFS_(edge_in[now][i],ID);
  }
}

int ans;

bool map[MaxN][MaxN];
vector<int> new_out[MaxN];
vector<int> new_in[MaxN];
int newN;


int main()
{
  int i,j,k;
  int open,closed,path[MaxN],dis[MaxN];

  scanf("%d",&T);
  while (T--)
  {
    scanf("%d%d",&N,&M);
    for (i=1;i<=N;++i) 
    {
      edge_out[i].clear();
      edge_in[i].clear();
    }

    for (k=1;k<=M;++k)
    {
      scanf("%d%d",&i,&j);
      edge_out[i].push_back(j);
      edge_in[j].push_back(i);
    }

    // 第一次DFS,计算 finished time
    memset(visit,false,sizeof(visit));
    Count=0;
    sp=0;
    for (i=1;i<=N;++i) if (!visit[i]) DFS(i);

    // 第二次DFS,计算 STRONGLY_CONN_COM
    memset(visit,false,sizeof(visit));
    newN=0;
    for (i=N;i>=1;--i) if (!visit[post_stack[i]])
    {
      newN++;
      DFS_(post_stack[i],newN);
    }


    // 构造收缩图
    memset(map,false,sizeof(map));
    for (i=1;i<=N;++i)
      for (j=0;j<edge_out[i].size();++j)
        map[index[i]][index[edge_out[i][j]]]=true;

    // 构造收缩图的临街链表
    for (i=1;i<=newN;++i) 
    {
      new_out[i].clear();
      new_in[i].clear();
    }
    for (i=1;i<=newN;++i)
      for (j=1;j<=newN;++j)
        if (j!=i && map[i][j]) 
        {
          new_out[i].push_back(j);
          new_in[j].push_back(i);
        }


    // 寻找入度为0的点
    ans=0;
    int tar=0;
    for (i=1;i<=newN;++i) if (new_in[i].size()==0) 
    { ans++; tar=i; }

    // 如果入度为0的个数>1，对不起，不用找了，无解
    if (ans>1) 
    {
      printf("No\n");
      continue;
    }

    // 从入度为0的开始找最长路
    memset(dis,0,sizeof(dis));
    dis[tar]=1;

    bool change;
    for (i=1;i<=newN;++i)
    {
      change=false;
      for (j=1;j<=newN;++j)
        for (k=0;k<new_out[j].size();++k)
        {
          if ( dis[j] +1 > dis[ new_out[j][k] ] ) 
          {
            dis[ new_out[j][k] ] =dis[j]+1;
            change=true;
          }
        }
      if (!change) break;
    }

    // 如果存在最长路经过所有节点，则可行
    ans=false;
    for (i=1;i<=newN;++i) if (dis[i]==newN) ans=true;		

    if (ans) printf("Yes\n"); else printf("No\n");
  }

  return 0;
}


