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
#include <list>

using namespace std;

#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;
using namespace std;

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

////////////////////////////////////////////////////

// 度限制的最小生成树，下标从1开始，限制在1号节点上
const int N = 5002;
const int INF = 1000000000;
#define clr(x) memset(x, 0, sizeof(x))

int n, K;
int mat[N][N];
int tree[N][N], size[N];

int dist[N], pre[N];
int que[N], q;
bool mk[N];

void MDMST() {		//Prim
	fill(dist, dist + n + 1, INF);
	clr(mk);
	clr(pre);
	clr(size);
  
	for (int cnt = 1, root = 2, p, mn; cnt < n;) {
		for (; root <= n && mk[root]; root++) ;
		dist[root] = 0;
    
		for (q = 0; ; cnt++) {
			mn = INF;
			for (int i = 2; i <= n; i++)
				if (!mk[i] && dist[i] < mn)
					mn = dist[i], p = i;
			if (mn == INF) break;
			mk[p] = true;
      
			que[q++] = p;
			for (int i = 2; i <= n; i++)
				if (!mk[i] && mat[p][i] < dist[i])
					dist[i] = mat[p][i], pre[i] = p;
		}
    
		mn = INF;
		for (int i = 0; i < q; i++)
			if (mn > mat[1][que[i]])
				mn = mat[1][que[i]], p = que[i];
    
		tree[1][size[1]++] = p;
		tree[p][size[p]++] = 1;
	}
  
	for (int i = 2; i <= n; i++)
		if (pre[i]) {
			tree[i][size[i]++] = pre[i];
			tree[pre[i]][size[pre[i]]++] = i;
		}
}

int ledge[N][3];		//longest; vertex * 2

bool inc_deg() {		// O(n)
	int i, j, k, now, next, mn = INF, id;
  
	clr(mk);
	mk[1] = true;
  
	for (i = 0, q = 0; i < size[1]; i++) {
		que[q++] = tree[1][i];
		mk[tree[1][i]] = true;
		ledge[tree[1][i]][0] = -INF;
	}
  
	for (i = 0; i < q; i++)
		for (now = que[i], j = 0; j < size[now]; j++)
			if ( !mk[next = tree[now][j]] ) {
				que[q++] = next;
				mk[next] = true;
				memcpy(ledge[next], ledge[now], sizeof(ledge[now]));
				if (mat[now][next] > ledge[next][0]) {
					ledge[next][0] = mat[now][next];
					ledge[next][1] = now;
					ledge[next][2] = next;
				}
				if ( (k = mat[1][next] - ledge[next][0]) < mn )
					mn = k, id = next;
			}
	if (mn >= INF) return true;
	
	tree[1][size[1]++] = id;
	tree[id][size[id]++] = 1;
	j = ledge[id][1];
	k = ledge[id][2];
	for (i = 0; i < size[j] && tree[j][i] != k; i++) ; tree[j][i] = tree[j][--size[j]];
	for (i = 0; i < size[k] && tree[k][i] != j; i++) ; tree[k][i] = tree[k][--size[k]];
	return false;
}


int KDMST() {
	MDMST();
	while (size[1] < K) if (inc_deg()) break;
	if (size[1] != K) {
		return INF;
	}
  
  //printf("%d\n", n - 1);
	int sum = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < size[i]; j++)
			if (i < tree[i][j]) {
				//printf("%d ", idmap[make_pair(i, tree[i][j])]);
				sum += mat[i][tree[i][j]];
			}
  //printf("\n");
	return sum;
}

map<string, int> idmap;
int ids;

int getid(string s)
{
  if (idmap.find(s) == idmap.end())
  {
    ids++;
    idmap[s] = ids;
  }
  return idmap[s];
}

void init()
{
  ids = 0;

  getid("Park");

  int L;
  cin >> L;
  for (int i = 1; i <= 50; ++i)
    for (int j = 1; j <= 50; ++j)
      mat[i][j] = INF;

  while (L--)
  {
    string a, b; int len;
    cin >> a >> b >> len;
    int id1 = getid(a);
    int id2 = getid(b);
    mat[id1][id2] = len;
    mat[id2][id1] = len;
  }

  int Bound;
  cin >> Bound;
  n = ids;
  
  int ans = INF;
  for (K = 1; K <= Bound; ++K)
    ans = min(ans, KDMST());
  cout << "Total miles driven: ";
  cout << ans << endl;
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
