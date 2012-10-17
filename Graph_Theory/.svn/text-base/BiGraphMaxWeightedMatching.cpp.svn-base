#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string.h>
using namespace std;

/** id from 0, AC by TC */
const int BM_MAXN = 2000;
const int BM_INFI = 99999999;
struct BipartiteMaxMatch
{
	/** 
	@see http://en.wikipedia.org/wiki/Hungarian_algorithm
	*/
	int N;
	int w[BM_MAXN][BM_MAXN];
	int label[BM_MAXN];
	bool g[BM_MAXN][BM_MAXN];
	int match[BM_MAXN];
	int nowMatch;

	BipartiteMaxMatch()
	{
		nowMatch = 0;
	}

	// 返回最佳匹配，对于左边的每个点 first 匹配id, second 匹配的边权
	vector<pair<int, int> > getMatch(int _N, int _M, vector<vector<int> > _w)
	{
		int i,j;
		N = max(_N, _M);
		memset(w, 0, sizeof(w));
		for (i = 0; i < _N; ++i)
			for (j = 0; j < _M; ++j)
			{
				w[i][j + N] = _w[i][j];
				w[j + N][i] = _w[i][j];
			}

			initMatch();
			startMatch();

			vector<pair<int, int> > ret(_N);
			for (i = 0; i < _N; ++i)
			{
				ret[i].first = match[i] - N;
				if (ret[i].first < 0 || ret[i].first >= _M) ret[i].first = -1;
				if (ret[i].first >= 0)
					ret[i].second = w[i][match[i]];
			}
			return ret;
	}

	void initMatch()
	{
		int i, j;
		for (j = N; j < 2 * N; ++j)
			label[j] = 0;
		for (i = 0; i < N; ++i)
		{
			label[i] = 0;
			for (j = N; j < 2 * N; ++j)
				label[i] = max(label[i], w[i][j]);
		}
		memset(g, false, sizeof(g));
		for (i = 0; i < N; ++i)
			for (j = N; j < 2 * N; ++j)
				g[i][j] = true;

		memset(match, -1, sizeof(match));
	}

	bool visited[BM_MAXN];
	int last[BM_MAXN];

	void dfs(int now, int father)
	{
		visited[now] = true;
		last[now] = father;
		for (int i = 0; i < N * 2; ++i)
			if (g[now][i] && label[now] + label[i] == w[now][i] && !visited[i])
				dfs(i, now);
	}

	void update(int now)
	{
		while (true)
		{
			int prev = last[now];
			g[prev][now] = false;
			g[now][prev] = true;
			match[prev] = now;
			match[now] = prev;
			now = last[prev];
			g[prev][now] = true;
			g[now][prev] = false;
			if (now == -1) break;
		}
	}

	void startMatch()
	{
		int i, j;
		int nowMatch = 0;
		while (true)
		{
			if (nowMatch == N) break;

			memset(visited, false, sizeof(visited));
			memset(last, -1, sizeof(last));
			for (i = 0; i < N; ++i)
				if (match[i] == -1)
					dfs(i, -1);

			int tar = -1;
			for (j = N; j < 2 * N; ++j)
				if (match[j] == -1 && visited[j])
				{
					tar = j;
					break;
				}

				if (tar != -1)
				{
					update(tar);
					nowMatch++;
				}
				else
				{
					int minDelta = BM_INFI;
					for (i = 0; i < N; ++i)
						if (visited[i])
							for (j = N; j < 2 * N; ++j)
								if (!visited[j])
									minDelta = min(minDelta, label[i] + label[j] - w[i][j]);
					for (i = 0; i < N; ++i)
						if (visited[i])
							label[i] -= minDelta;
					for (j = N; j < 2 * N; ++j)
						if (visited[j])
							label[j] += minDelta;
				}
		}
	}
};

}
void init()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		for (int j = N; j < 2 * N; ++j)
		{
			scanf("%d", &w[i][j]);
			w[j][i] = w[i][j];
		}
}


int main()
{
	init();
	initMatch();
	startMatch();

	for (int i = 0; i < N; ++i)
		cout << label[i] << " ";
	cout << endl;
	for (int j = N; j < 2 * N; ++j)
		cout << label[j] << " ";
	cout << endl;
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
}
