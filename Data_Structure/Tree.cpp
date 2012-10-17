#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
using namespace std;

const int INFI = 99999999;
const int TM = (1 << 17);
int maxvalue[TM * 3];

void update(int posi, int value)
{
  int now = posi + TM;
  maxvalue[now] = value;
  while (now > 1)
  {
    now = now >> 1;
    maxvalue[now] = max(maxvalue[now + now], maxvalue[now + now + 1]);
  }
}

int query(int l, int r)
{
  l--; r++;
  l += TM; r += TM;
  
  int ret = -INFI;
  while (true)
  {
    if ((l ^ r) == 1) break;
    if ((l & 1) == 0) ret = max(ret, maxvalue[l + 1]);
    if ((r & 1) == 1) ret = max(ret, maxvalue[r - 1]);
    l >>= 1; 
    r >>= 1;
  }
  return ret;
}

// Operation On Trees
// Latest Common Ancestor 
// Please make sure that the construction of LCA is a rooted tree 
// edge are inserted from the low degree to high degree
// AC URAL 1752
class Tree
{
public:
	const static int MAX_FATHERS = 20;
  
	// nodes in this tree
	int N;
  
	// root in the tree
	int root;
  
	// fathers of this node, note that -1 represent non this father
	// fathers[i][0] represent the direct father of this node
	// fathers[i][j] = fathers[fathers[i][j - 1]][j - 1];
	vector<vector<int> > fathers;
  vector<int> fatherDis;
  
	// sons of this node, not include its father
	vector<vector<int> > sons;
	vector<vector<int> > sonsDis;
  
	// depth of each node
	vector<int> depth;
  
	// distance between node and root, node 0 is root
	vector<int> distanceToRoot;
  
	// the size of this subtree
	vector<int> size;
  
	// the farthest son to the current node , measured by number of edges connect them
	vector<int> farSon1;
	vector<int> farSonDis1;
	vector<int> farSonNext1;
	vector<int> farSon2;
	vector<int> farSonDis2;
	vector<int> farSonNext2;
  
	vector<int> farNodeFromFather;
	vector<int> farNodeFromFatherDis;
  
	vector<int> farNode;
	vector<int> farNodeDis;
  
	// if we want to split the tree into different links, that's the information
  // for each nodes, which link id it belongs to
	vector<int> linkID;
  // in his link, remain length to the top of the link
	vector<int> linkOffset;
  // for each node, the map id in the segment tree
  vector<int> linkidmap;
  // for each node, the next start node of its link's end
  vector<int> linkNextStart;
  
	vector<vector<int> > links;
  
	Tree()
	{
	}
  
	// given a tree, constructor the lca
	// make sure that the root of the tree is node 0
	// weight : the distance between two node, usually it's all 1
	// sometimes it is not
	// tree is the linked list representation of the tree
	// weight is the corresponding weight 
	// @warning no multiple edge please
	// @warning no self loop please
	Tree(vector<vector<int> > & tree, vector<vector<int> > & dis, int _root = 0)
	{
		N = (int) tree.size();
		root = _root;
		fathers.resize(N);
		for (unsigned int i = 0; i < fathers.size(); ++i)
			fathers[i] = vector<int>(MAX_FATHERS, -1);
		depth = vector<int>(N, 0);
		distanceToRoot = vector<int>(N, 0);
		size = vector<int>(N, 0);
		sons.resize(N);
		sonsDis.resize(N);
    fatherDis.resize(N, 0);
    
		queue<int> q;
		q.push(root);
    
		vector<bool> visited(N, false);
		visited[root] = true;
    
		while (q.size() > 0)
		{
			int nowID = q.front();
			q.pop();
      
			for (unsigned int i = 0; i < tree[nowID].size(); ++i)
			{
				int nextID = tree[nowID][i];
				int nowDis = dis[nowID][i];
				if (!visited[nextID])
				{
					visited[nextID] = true;
					addEdge(nowID, nextID, nowDis);
					q.push(nextID);
				}
			}
		}
    
		calSize();
		splitIntoLinks();
    
		//calFarthestSon();
		//calFarthestNodeFromFather();
		//calFarthestNode();
	}
  
private:
  
	void calFarthestNodeFromFather()
	{
		farNodeFromFather = vector<int>(N, -1);
		farNodeFromFatherDis = vector<int>(N, -1);
    
		calFarthestNodeFromFather(root);
	}
  
	void calFarthestNodeFromFather(int now)
	{
		int father = fathers[now][0];
		
		if (father == -1)
		{
			farNodeFromFather[now] = now;
			farNodeFromFatherDis[now] = 0;
		}
		else
		{
			int distToFather = distanceToRoot[now] - distanceToRoot[father];
			farNodeFromFather[now] = farNodeFromFather[father];
			farNodeFromFatherDis[now] = farNodeFromFatherDis[father] + distToFather;
      
			if (farSonNext1[father] != now)
			{
				if (distToFather + farSonDis1[father] > farNodeFromFatherDis[now])
				{
					farNodeFromFatherDis[now] = distToFather + farSonDis1[father];
					farNodeFromFather[now] = farSon1[father];
				}
			}
      
			if (farSonNext2[father] != now)
			{
				if (distToFather + farSonDis2[father] > farNodeFromFatherDis[now])
				{
					farNodeFromFatherDis[now] = distToFather + farSonDis2[father];
					farNodeFromFather[now] = farSon2[father];
				}
			}
		}
    
		for (int i = 0; i < sons[now].size(); ++i)
		{
			int nextID = sons[now][i];
			calFarthestNodeFromFather(nextID);
		}
	}
  
	// cal the farthest node of each node 
	void calFarthestNode()
	{
		farNode = vector<int>(N, -1);
		farNodeDis = vector<int>(N, -1);
    
		calFarthestNode(root);
	}
  
	void calFarthestNode(int now)
	{
		farNode[now] = farSon1[now];
		farNodeDis[now] = farSonDis1[now];
    
		if (farNodeFromFatherDis[now] > farNodeDis[now])
		{
			farNodeDis[now] = farNodeFromFatherDis[now];
			farNode[now] = farNodeFromFather[now];
		}
    
		for (int i = 0; i < sons[now].size(); ++i)
		{
			int nextID = sons[now][i];
			calFarthestNode(nextID);
		}
	}
  
	// cal the farthest son 
	void calFarthestSon()
	{
		farSon1 = vector<int>(N, -1);
		farSonDis1 = vector<int>(N, -1);
		farSonNext1 = vector<int>(N, -1);
		farSon2 = vector<int>(N, -1);
		farSonDis2 = vector<int>(N, -1);
		farSonNext2 = vector<int>(N, -1);
    
		calFarthestSon(root);
	}
  
	void calFarthestSon(int now)
	{
		if (sons[now].size() == 0)
		{
			farSon1[now] = farSon2[now] = now;
			farSonDis1[now] = farSonDis2[now] = 0;
			farSonNext1[now] = farSonNext2[now] = now;
			return;
		}
    
		for (int i = 0; i < sons[now].size(); ++i)
		{
			int nextID = sons[now][i];
			calFarthestSon(nextID);
			int dis = sonsDis[now][i] + farSonDis1[nextID];
			if (dis > farSonDis1[now])
			{
				farSon2[now] = farSon1[now];
				farSonDis2[now] = farSonDis1[now];
				farSonNext2[now] = farSonNext1[now];
				farSon1[now] = farSon1[nextID];
				farSonDis1[now] = dis;
				farSonNext1[now] = nextID;
			}
			else
			{
				if (dis > farSonDis2[now])
				{
					farSonDis2[now] = dis;
					farSon2[now] = farSon1[nextID];
					farSonNext2[now] = nextID;
				}
			}
		}
	}
  
	// private
	void calSize()
	{
		stack<pair<int, bool> > s;
		s.push(make_pair(root, true));
		vector<bool> visited(N, false);
		visited[root] = true;
    
		while (s.size() > 0)
		{
			pair<int, bool> now = s.top();
      s.pop();
      int nowID = now.first;
      bool isfirst = now.second;
      if (isfirst)
      {
        s.push(make_pair(nowID, false));
        for (int i = 0; i < sons[nowID].size(); ++i)
        {
          int nextid = sons[nowID][i];
          if (!visited[nextid])
          {
            visited[nextid] = true;
            s.push(make_pair(nextid, true));
          }
        }
      }
      else
      {
        size[nowID] = 1;
        for (int i = 0; i < sons[nowID].size(); ++i)
          size[nowID] += size[sons[nowID][i]];
      }
		}
	}
  
	// split the tree into links
	void splitIntoLinks()
	{
		linkID = vector<int>(N, -1);
		linkOffset = vector<int>(N, -1);
    
		queue<int> q;
		q.push(root);
    
		while (q.size() > 0)
		{
			int nowID = q.front();
			q.pop();
      
			int maxSonSize = 0;
			int maxSon = -1;
			for (unsigned int i = 0; i < sons[nowID].size(); ++i)
			{
				int nextID = sons[nowID][i];
				q.push(nextID);
				if (size[nextID] > maxSonSize)
				{
					maxSonSize = size[nextID];
					maxSon = nextID;
				}
			}
      
			if (maxSon != -1)
			{
				if (linkID[nowID] != -1)
				{
					linkID[maxSon] = linkID[nowID];
					linkOffset[maxSon] = linkOffset[nowID] + 1;
					links[linkID[nowID]].push_back(maxSon);
				}
				else
				{
					links.push_back(vector<int>());
					linkID[nowID] = (int) links.size() - 1;
					linkID[maxSon] = (int) links.size() - 1;
					links[linkID[nowID]].push_back(nowID);
					links[linkID[nowID]].push_back(maxSon);
					linkOffset[nowID] = 0;
					linkOffset[maxSon] = 1;
				}
			}
			else
			{
				if (linkID[nowID] == -1)
				{
					links.push_back(vector<int>());
					linkID[nowID] = (int) links.size() - 1;
					links[linkID[nowID]].push_back(nowID);
					linkOffset[nowID] = 0;
				}
			}
		}
    
    linkidmap.resize(N, 0);
    int cnt = 1;
    for (int i = 0; i < links.size(); ++i)
      for (int j = (int) links[i].size() - 1; j >= 0; --j)
      {
        int id = links[i][j];
        linkidmap[id] = cnt;
        cnt++;
      }
    
    linkNextStart.resize(N);
    for (int i = 0; i < N; ++i)
      linkNextStart[i] = fathers[links[linkID[i]][0]][0];
	}
  
	// add an edge from t1 to t2, 
	// make sure that depth(t1) < depth(t2)
	// so t1 is the direct father of t2
	void addEdge(int t1, int t2, int dis)
	{
		fathers[t2][0] = t1;
		for (int i = 1; i < MAX_FATHERS; ++i)
		{
			int midFather = fathers[t2][i - 1];
			if (midFather != -1)
				fathers[t2][i] = fathers[midFather][i - 1];
			else
				break;
		}
		depth[t2] = depth[t1] + 1;
		distanceToRoot[t2] = distanceToRoot[t1] + dis;
    
		sons[t1].push_back(t2);
		sonsDis[t1].push_back(dis);
    fatherDis[t2] = dis;
	}
  
public:
  
	// return the latest common ancestor of this two nodes
	int getLCA(int t1, int t2)
	{
		if (t1 == t2) return t1;
    
		// make sure that depth[t1] >= depth[t2]
		if (depth[t1] < depth[t2])
			swap(t1, t2);
    
		// adjust t1's depth equal to t2's
		int deltaDepth = depth[t1] - depth[t2];
		for (int i = MAX_FATHERS - 1; i >= 0; --i)
		{
			if ((deltaDepth & (1 << i)) > 0)
				t1 = fathers[t1][i];
			if (depth[t1] == depth[t2]) break;
		}
    
		// adjust t1 and t2 to their latest common father
		for (int i = MAX_FATHERS - 1; i >= 0; --i)
		{
			if (fathers[t1][i] != fathers[t2][i])
			{
				t1 = fathers[t1][i];
				t2 = fathers[t2][i];
			}
		}
    
		if (t1 == t2) 
			return t1;
		else
			return fathers[t1][0];
	}
  
	int getEdgesBetweenNode(int t1, int t2)
	{
		if (t1 == t2) return 0;
		int lca = getLCA(t1, t2);
		return depth[t1] - depth[lca] + depth[t2] - depth[lca];
	}
  
	int getDistanceBetweenNode(int t1, int t2)
	{
		if (t1 == t2) return 0;
		int lca = getLCA(t1, t2);
		return distanceToRoot[t1] - distanceToRoot[lca] 
    + distanceToRoot[t2] - distanceToRoot[lca];
	}
  
	// get the f's father , f start from 1, f = 1 means direct father 
	int getFather(int t, int f)
	{
		int nowt = t;
		for (int i = MAX_FATHERS - 1; i >= 0; --i)
		{
			if (f >= (1 << i))
			{
				nowt = fathers[nowt][i];
				f -= (1 << i);
			}
			if (nowt == -1) return -1;
		}
		return nowt;
	}
};

int getMaxInPath(Tree * tree, int now, int remainnodes, int N)
{
  int ret = -INFI;
  while (remainnodes > 0)
  {
    int segid = tree->linkidmap[now];
    int remain = tree->linkOffset[now];
    if (remain + 1 >= remainnodes)
    {
      ret = max(ret, query(segid, segid + remainnodes - 1));
      break;
    }
    else
    {
      ret = max(ret, query(segid, segid + remain));
      remainnodes -= (remain + 1);
      now = tree->linkNextStart[now];
    }
  }
  return ret;
}

int T;
int N, Q;
int rad[200000];

void init()
{
  scanf("%d", &N);
  vector<vector<int> > g(N);
  vector<vector<int> > dis(N);
  for (int i = 1; i <= N - 1; ++i)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    g[a].push_back(b);
    dis[a].push_back(1);
    g[b].push_back(a);
    dis[b].push_back(1);
  }
  
  Tree tree(g, dis, 0);
  memset(maxvalue, 0, sizeof(maxvalue));
  memset(rad, 0, sizeof(rad));
  
  scanf("%d", &Q);
  char temp[20]; 
  int a, b;
  while (Q--)
  {
    scanf("%s", temp);
    if (temp[0] == 'G')
    {
      scanf("%d%d", &a, &b);
      a--; b--;
      
      int lca = tree.getLCA(a, b);
      int value1 = getMaxInPath(&tree, a, tree.depth[a] - tree.depth[lca] + 1, N);
      int value2 = getMaxInPath(&tree, b, tree.depth[b] - tree.depth[lca] + 1, N);
      printf("%d\n", max(value1, value2));
    }
    else
    {
      scanf("%d%d", &a, &b);
      a--;
      rad[a] += b;
      update(tree.linkidmap[a], rad[a]);
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