#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <list>
using namespace std;

/** 
 * @Confidence 
 * timus 1076 Trash AC bipartite graph maximum-weighted matching 
 */
class MaxFlowMinimalCost
{
  public:
    const static int INFINITY = (1 << 30);
    const static int NMAX = 2000;

    /** The capacity of each edge */
    int cap[NMAX][NMAX];

    /** The remain capacity of this edge */
    int net[NMAX][NMAX];

    /** The cost of each edge */ 
    int cost[NMAX][NMAX];

    /** The Linked List edge of this net work */
    vector<vector<int> > edges;

    int path[NMAX], ecost[NMAX];
    int N;
    int sourceNode;
    int sinkNode;

    MaxFlowMinimalCost(int nodes, int source, int sink)
    { reset(nodes, source, sink); }

    MaxFlowMinimalCost()
    { reset(0, 0, 0); }

    void reset(int nodes, int source, int sink)
    {
      N = nodes;
      sourceNode = source;
      sinkNode = sink;
      edges.clear();
      edges.resize(N);

      for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N; ++j) {
          cap[i][j] = 0;
          net[i][j] = 0;
          cost[i][j] = 0;
        }
    }

    void addEdge(int start, int stop, int capacity, int _cost)
    {
      cap[start][stop] += capacity;
      net[start][stop] += capacity;
      cost[start][stop] += _cost;
      edges[start].push_back(stop);
      edges[stop].push_back(start);
    }

  private:

    bool SPFA()
    {
      for (int i = 0; i < N; ++i) {
        path[i] = -1;
        ecost[i] = INFINITY;
      }
      ecost[sourceNode] = 0;
      vector<bool> inQueue(N);
      list<int> queue;
      queue.push_back(sourceNode);
      inQueue[sourceNode] = true;

      while (!queue.empty()) {
        int node = queue.front();
        inQueue[node] = false;
        queue.pop_front();

        for (int i = 0; i < edges[node].size(); ++i) {
          int nextNode = edges[node][i];
          if(net[node][nextNode] > 0 && ecost[node] + cost[node][nextNode] < ecost[nextNode]) {
            ecost[nextNode] = ecost[node] + cost[node][nextNode];
            path[nextNode] = node;
            if (inQueue[nextNode]) continue;
            if (queue.empty())
              queue.push_back(nextNode);
            else {
              if (ecost[nextNode] < ecost[queue.front()])
                queue.push_front(nextNode);
              else
                queue.push_back(nextNode);
            }
            inQueue[nextNode] = true;
          }
        }
      }
      return ecost[sinkNode] != INFINITY;
    }

    /** Find an path with the minimal cost to increase the total flow */
    bool bellman_ford()
    {
      for (int i = 0; i < N; ++i) {
        path[i] = -1;
        ecost[i] = INFINITY;
      }
      ecost[sourceNode] = 0;

      bool flag = true;
      while (flag) {
        flag = false;
        for (int i = 0; i < N; i++) {
          if (ecost[i] == INFINITY) continue;
          for (int k = 0; k < edges[i].size(); ++k) {
            int j = edges[i][k];
            if(net[i][j] > 0 && ecost[i] + cost[i][j] < ecost[j]) {
              flag = true;
              ecost[j] = ecost[i] + cost[i][j];
              path[j] = i;
            }
          }
        }
      }
      return ecost[sinkNode] != INFINITY;
    }

  public:
    void maxFlowMinimalCost(int & maxFlow, int & minCost)
    {
      maxFlow = 0;
      minCost = 0;

      while (bellman_ford()) {
        /** Find the minimal remain capacity of the argument path */
        int now = sinkNode;
        int neck = INFINITY;
        while (now != sourceNode) {
          int pre = path[now];
          neck = min(neck, net[pre][now]);
          now = pre;
        }
        maxFlow += neck;

        /** maintain the netflow */
        now = sinkNode;
        while (now != sourceNode) {
          int pre = path[now];
          net[pre][now] -= neck;
          net[now][pre] += neck;
          cost[now][pre] = -cost[pre][now];
          minCost += cost[pre][now] * neck;
          now = pre;
        }
      }
    }

    friend ostream & operator << (ostream & out, MaxFlowMinimalCost & net)
    {
      out << "Nodes = " << net.N << endl;
      out << "SourceNode = " << net.sourceNode << endl;
      out << "SinkNode = " << net.sinkNode << endl;
      for (int i = 0; i < net.N ; ++i) 
        for (int j = 0; j < net.N; ++j) 
          if (net.cap[i][j] > 0)
            out << i << " -> " << j << "\t" << net.cap[i][j] - net.net[i][j] << "(" << net.cap[i][j] << ")" 
              << "[" << net.cost[i][j] << "]" << endl;
      return out;
    }

    vector<pair<int, int> > getPositiveFlowEdges()
    {
      vector<pair<int, int> > result;
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
          if (cap[i][j] - net[i][j] > 0) 
            result.push_back(make_pair(i, j));
      return result;
    }
};

MaxFlowMinimalCost * net = new MaxFlowMinimalCost();

int a[1000];
int cost[1000];

inline int getbits(int x)
{
  int ret = 0;
  for (int i = 0; i <= 30; ++i)
    if (x & (1 << i)) ret++;
  return ret;
}

void init()
{
  int N, M;
  cin >> N >> M;
  
  for (int i = 0; i < N; ++i)
  {
    cin >> a[i];
    cost[i] = getbits(a[i]);
  }
  
  int LS = N + M;
  int RS = N;
  int nodes = LS + RS + 2;
  int source = 0;
  int sink = nodes - 1;
  
  net->reset(nodes, source, sink);
  for (int i = 1; i <= LS; ++i)
    net->addEdge(source, i, 1, 0);
  for (int i = LS + 1; i <= LS + RS; ++i)
    net->addEdge(i, sink, 1, 0);
  
  for (int i = 0; i < N; ++i)
    for (int j = i + 1; j < N; ++j)
      if (a[i] == a[j])
        net->addEdge(i + 1, j + 1 + LS, 1, 0);
      else
        net->addEdge(i + 1, j + 1 + LS, 1, cost[j]);
  
  for (int i = 0; i < M; ++i)
    for (int j = 0; j < N; ++j)
      net->addEdge(i + 1 + N, j + 1 + LS, 1, cost[j]);
  
  int maxflow, mincost;
  net->maxFlowMinimalCost(maxflow, mincost);
  
  vector<string> ans;
  
  vector<pair<int, int> > edges = net->getPositiveFlowEdges();
  vector<int> anstar(N, -999999);
  vector<int> save(M, -1);
  for (int i = 0; i < edges.size(); ++i)
  {
    int s = edges[i].first;
    int t = edges[i].second;
    if (s == source || t == sink) continue;
    int id1 = s - 1;
    int id2 = t - LS - 1;
    //cout << id1 << " " << id2 << endl;
    if (id1 >= N) anstar[id2] = id1 - N + 1000;
    else anstar[id2] = id1;
  }
  
  for (int i = 0; i < N; ++i)
  {
    if (anstar[i] >= 1000)
    {
      anstar[i] -= 1000;
      int saveid = anstar[i];
      save[saveid] = a[i];
      char temp[30];
      sprintf(temp, "%c=%d", 'a' + saveid, a[i]);
      ans.push_back(string(temp));
      sprintf(temp, "print(%c)", 'a' + saveid);
      ans.push_back(string(temp));
    }
    else
    {
      int tar = anstar[i];
      tar = anstar[tar];
      anstar[i] = tar;
      
      char temp[30];
      if (save[tar] == a[i])
      {
        sprintf(temp, "print(%c)", 'a' + tar);
        ans.push_back(string(temp));
      }
      else
      {
        save[tar] = a[i];
        sprintf(temp, "%c=%d", 'a' + tar, a[i]);
        ans.push_back(string(temp));
        sprintf(temp, "print(%c)", 'a' + tar);
        ans.push_back(string(temp));
      }
    }
  }
  
  cout << ans.size() << " " << mincost << endl;
  for (int i = 0; i < ans.size(); ++i)
    cout << ans[i] << endl;
}

void york()
{
  
}

int main()
{
  init();
  return 0;
  
  net->reset(6, 0, 5);
  net->addEdge(0, 1, 1, 0);
  net->addEdge(0, 2, 1, 0);
  net->addEdge(3, 5, 1, 0);
  net->addEdge(4, 5, 1, 0);
  net->addEdge(1, 3, 1, -2);
  net->addEdge(1, 4, 1, -10);
  net->addEdge(2, 3, 1, -1);
  net->addEdge(2, 4, 1, -3);

  int maxFlow, minCost;
  net->maxFlowMinimalCost(maxFlow, minCost);

  cout << maxFlow << "\t" << minCost << endl;
  cout << (*net) << endl;
}

/**
  inline int abs(int x)
  {
  return x > 0 ? x : -x;
  }

  inline int dist(pair<int, int> & a, pair<int, int> & b) 
  {
  return abs(a.first - b.first) + abs(a.second - b.second);
  }

  int main()
  {
  int N, M;
  while (scanf("%d%d", &N, &M) == 2) {
  if (N == 0 && M == 0) break;
  vector<pair<int, int> > Hs;
  vector<pair<int, int> > Ms;
  string line;
  getline(cin, line);
  for (int i = 0; i < N; ++i) {
  getline(cin, line);
  for (int j = 0; j < M; ++j) {
  if (line[j] == 'm') 
  Ms.push_back(make_pair(i, j));
  if (line[j] == 'H')
  Hs.push_back(make_pair(i, j));
  }
  }

  int source = Hs.size() + Ms.size();
  int target = Hs.size() + Ms.size() + 1;
  net->reset(Hs.size() + Ms.size() + 2, source, target);
  for (int i = 0; i < Ms.size(); ++i) 
  net->addEdge(source, i, 1, 0);
  for (int j = Ms.size(); j < Ms.size() + Hs.size(); ++j)
  net->addEdge(j, target, 1, 0);

  for (int i = 0; i < Ms.size(); ++i) 
  for (int j = 0; j < Hs.size(); ++j) {
  int dis = dist(Ms[i], Hs[j]);
  net->addEdge(i, j + Ms.size(), 1, dis);
  }

  int maxFlow, minCost;
  net->maxFlowMinimalCost(maxFlow, minCost);
  printf("%d\n", minCost);
  }
  }
  */

/**
  int main()
  {
  MaxFlowMinimalCost * net = new MaxFlowMinimalCost();
  int T;
  scanf("%d", &T);
  while (T--) {
  int N;
  scanf("%d", &N);
  vector<int> balls(N);
  for (int i = 0; i < N; ++i) 
  scanf("%d", &balls[i]);

  int source = N;
  int target = N + 1;
  net->reset(N + 2, source, target);

  for (int i = 0; i < N; ++i) {
  net->addEdge(source, i, balls[i], 0);
  net->addEdge(i, target, 1, 0);
  }

  for (int i = 0; i < N; ++i) {
  int left = i - 1 + N;
  left %= N;
  int right = i + 1 + N;
  right %= N;
  net->addEdge(i, left, 99999999, 1);
  net->addEdge(i, right, 99999999, 1);
  }

  int maxFlow, minCost;
  net->maxFlowMinimalCost(maxFlow, minCost);

  printf("%d\n", minCost);
  }
  return 0;
  }
  */

/**
  int main()
  {
  MaxFlowMinimalCost * net = new MaxFlowMinimalCost();

  int N, K;
  scanf("%d%d", &N, &K);
  net->reset(N*N*4 + 2, N*N*4, N*N*4 + 1);
  int sourceNode = N*N*4;
  int targetNode = N*N*4 + 1;

  int data[200][200];
  for (int i = 0; i < N; ++i) 
  for (int j = 0; j < N; ++j) 
  scanf("%d", &data[i][j]);

  for (int i = 0; i < N; ++i)
  for (int j = 0; j < N; ++j) {
  int node1 = i * N + j;
  node1 *= 4;
  int node2 = node1 + 1;
  int node3 = node1 + 2;
  int node4 = node1 + 3;
  net->addEdge(node1, node2, 1, -data[i][j]);
  net->addEdge(node2, node4, 1, 0);
  net->addEdge(node1, node3, 99999999, 0);
  net->addEdge(node3, node4, 99999999, 0);
  int node5 = (i + 1) * N + j;
  int node6 = i * N + j + 1;
  if (i + 1 < N) {
  node5 *= 4;
  net->addEdge(node4, node5, K, 0);
  }
  if (j + 1 < N) {
  node6 *= 4;
  net->addEdge(node4, node6, K, 0);
  }
  }

  net->addEdge(sourceNode, 0, K, 0);
  net->addEdge(N*N*4 - 1, targetNode, K, 0);

  int maxFlow, minCost;
  net->maxFlowMinimalCost(maxFlow, minCost);

  printf("%d\n", -minCost);
  }
  */

/**
// PKU PIGS
int main()
{
MaxFlowMinimalCost * net = new MaxFlowMinimalCost();

int M, N;
scanf("%d%d", &M, &N);
net->reset(N + 2, N, N + 1);

vector<int> pigs(M);
for (int i = 0; i < M; ++i) 
scanf("%d", &pigs[i]);
vector<vector<int> >  pigsCustomer(M);
vector<int> buys(N);

for (int i = 0; i < N; ++i) {
int a, b;
scanf("%d", &a);
for (int j = 0; j < a; ++j) {
scanf("%d", &b);
pigsCustomer[b - 1].push_back(i);
}
scanf("%d", &b);
buys[i] = b;
}

for (int i = 0; i < pigsCustomer.size(); ++i) {
if (pigsCustomer[i].size() == 0) continue;
int firstCustomer = pigsCustomer[i][0];
net->addEdge(N, firstCustomer, pigs[i], 0);

for (int j = 1; j < pigsCustomer[i].size(); ++j) {
int first = pigsCustomer[i][j - 1];
int second = pigsCustomer[i][j];
net->addEdge(first, second, 99999999, 0);
}
}

for (int i = 0; i < N; ++i) 
net->addEdge(i, N + 1, buys[i], 0);

int maxFlow, minCost;
net->maxFlowMinimalCost(maxFlow, minCost);

printf("%d\n", maxFlow);
}
*/

/**
// PKU 1459
int main()
{
MaxFlowMinimalCost * net = new MaxFlowMinimalCost();
int N, np, nc, M;
while (scanf("%d%d%d%d", &N, &np, &nc, &M) == 4) {
net->reset(N + 2, 0, 1);

char temp[100];
int u, v, z;
for (int i = 0; i < M; ++i) {
scanf("%s", temp);
sscanf(temp, "(%d,%d)%d", &u, &v, &z);
net->addEdge(u + 2, v + 2, z, 0);
}
for (int i = 0; i < np; ++i) {
scanf("%s", temp);
sscanf(temp, "(%d)%d", &u, &z);
net->addEdge(0, u + 2, z, 0);
}
for (int i = 0; i < nc; ++i) {
scanf("%s", temp);
sscanf(temp, "(%d)%d", &u, &z);
net->addEdge(u + 2, 1, z, 0);
}

int maxFlow, minCost;
net->maxFlowMinimalCost(maxFlow, minCost);
printf("%d\n", maxFlow);
}
return 0;
}
*/



