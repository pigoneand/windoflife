#include <iostream>
using namespace std;

// Remember to memset C[maxn][maxn] for a new case
// 定点编号1..n
// c[i][j] 容量
const int maxn=1000;
const int INFINITE=2147483647;
int c[maxn][maxn],f[maxn][maxn],pnt[maxn],open[maxn],d[maxn],mk[maxn];

int maxflow(int n,int s,int t)
{
	int cur,tail,i,j,u,v,flow=0;
	memset(f,0,sizeof(f));

	do
	{
		memset(mk,0,sizeof(mk));
		memset(d,0,sizeof(d));
		open[0]=s;mk[s]=1;d[s]=INFINITE;
		for (pnt[s]=cur=tail=0;cur<=tail && !mk[t]; cur++)
		{
			// 此处值得商榷
			for (u=open[cur],v=1;v<=n;v++) if (!mk[v] && f[u][v]<c[u][v])
			{
				mk[v]=1;
				open[++tail]=v;
				pnt[v]=u;
				if (d[u]<c[u][v]-f[u][v]) d[v]=d[u];
					else d[v]=c[u][v]-f[u][v];
			}
		}
		if (!mk[t]) break; flow+=d[t];
		for (u=t;u!=s;) { v=u; u=pnt[v]; f[u][v]+=d[t]; f[v][u]=-f[u][v]; }

	}while (d[t]>0); 
	return flow;
}