#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

int N, M;
int INFI = 99999999;
int w[501][501];
vector<vector<int> > tree;
int minCost;

void minTree()
{
	tree.resize(N + 1);
	vector<bool> visited(N + 1, false);
	vector<int> dist(N + 1, INFI);
	vector<int> last(N + 1, -1);
	dist[1] = 0;
	minCost = 0;

	for (int k = 0; k < N; ++k)
	{
		int minDis = INFI;
		int minTar = -1;
		for (int i = 1; i <= N; ++i)
			if (dist[i] < minDis && !visited[i])
			{
				minDis = dist[i];
				minTar = i;
			}
		if (minTar == -1) break;
		visited[minTar] = true;
		minCost += dist[minTar];
		if (last[minTar] != -1)
		{
			tree[minTar].push_back(last[minTar]);
			tree[last[minTar]].push_back(minTar);
		}

		for (int i = 1; i <= N; ++i)
			if (w[minTar][i] < dist[i])
			{
				dist[i] = w[minTar][i];
				last[i] = minTar;
			}
	}
	cout << "Cost: " << minCost << endl;
}

bool inMinTree[501][501];
int maxPass[501];
bool visited[501];

void dfs(int now)
{
	visited[now] = true;
	for (int i = 0; i < tree[now].size(); ++i)
	{
		int nextID = tree[now][i];
		if (!visited[nextID])
		{
			maxPass[nextID] = max(maxPass[now], w[now][nextID]);
			dfs(nextID);
		}
	}
}

void deal()
{
	minTree();

	memset(inMinTree, false, sizeof(inMinTree));
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 0; j < tree[i].size(); ++j)
			inMinTree[i][tree[i][j]] = true;
	}

	int secondCost = INFI;
	for (int i = 1; i <= N; ++i)
	{
		memset(visited, false, sizeof(visited));
		memset(maxPass, 0, sizeof(maxPass));
		dfs(i);

		for (int j = 1; j <= N; ++j)
			if (j != i && w[i][j] != INFI && !inMinTree[i][j])
			{
				int nowCost = minCost - maxPass[j] + w[i][j];
				secondCost = min(secondCost, nowCost);
			}
	}

	if (secondCost == INFI)
		secondCost = -1;
	cout << "Cost: " << secondCost << endl;
}

void init()
{
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			w[i][j] = INFI;

	for (int k = 0; k < M; ++k)
	{
		int t1, t2, weight;
		scanf("%d%d%d", &t1, &t2, &weight);
		w[t1][t2] = weight;
		w[t2][t1] = weight;
	}
}


int main()
{
	init();
	deal();

#ifndef ONLINE_JUDGE
	system("pause");
#endif
}