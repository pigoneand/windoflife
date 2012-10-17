
/****************************************************************
Problem: 1017
User: pigoneand
Language: C++
Result: Accepted
Time:2592 ms
Memory:34044 kb
****************************************************************/

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
using namespace std;
#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

/**
template <class T>
ostream & operator << (ostream & out, const vector<T> & t)
{	out << t.size() << " {";	for (int i = 0; i < t.size(); ++i) 		out << t[i] << " ";	out << "}";	return out;}

template <class T>
ostream & operator << (ostream & out, const set<T> & t)
{	out << "{";	for (set<T>::iterator itr = t.begin(); itr != t.end(); ++itr)		out << *itr << " ";	out << "}";	return out;}
*/

//////////////////////////////////////////////////////////////////////////
// template finished 
//////////////////////////////////////////////////////////////////////////
const int maxDancer = 2000000;
int nowDancers = 0;
int L[maxDancer], R[maxDancer], U[maxDancer], D[maxDancer];
int colH[maxDancer];
int row[maxDancer], col[maxDancer], cnt[maxDancer];

inline void removeCol(int c)
{
	L[R[c]] = L[c]; R[L[c]] = R[c];
	for (int i = D[c]; i != c; i = D[i])
		for (int j = R[i]; j != i; j = R[j])
		{ 
			D[U[j]] = D[j]; U[D[j]] = U[j];
			cnt[colH[j]]--;
		}
}

void recoverCol(int c)
{
	for (int i = U[c]; i != c; i = U[i])
		for (int j = L[i]; j != i; j = L[j])
		{ 
			D[U[j]] = j; U[D[j]] = j;
			cnt[colH[j]]++;
		}
		L[R[c]] = c; R[L[c]] = c;
}

int newDancer(int up, int down, int left, int right, int r, int c)
{
	U[nowDancers] = up;
	D[nowDancers] = down;
	L[nowDancers] = left;
	R[nowDancers] = right;
	D[up] = U[down] = R[left] = L[right] = nowDancers;
	row[nowDancers] = r;
	col[nowDancers] = c;
	cnt[nowDancers] = 0;
	return nowDancers++;
}

class DancingLink
{
public:
	int head;
	vector<int> colhead;
	int rows;
	int cols;

	bool foundAns;
	vector<int> selrows;
	vector<int> selrowsans;

	/** Each col should have at least one 1, @warning : singleton */
	DancingLink(vector<vector<bool> > & matrix)
	{
		nowDancers = 0;
		rows = matrix.size();
		cols = matrix[0].size();

		head = newDancer(0, 0, 0, 0, -1, -1); 
		colhead.resize(cols);
		for (int j = 0; j < cols; ++j)
			colhead[j] = newDancer(nowDancers, nowDancers, L[head], head, -1, j);

		for (int i = 0; i < rows; ++i)
		{
			int lastrow = -1;
			for (int j = 0; j < cols; ++j)
				if (matrix[i][j])
				{
					cnt[colhead[j]]++;
					if (lastrow >= 0) 
					{
						lastrow = newDancer(U[colhead[j]], colhead[j], lastrow, R[lastrow], i, j);
						colH[lastrow] = colhead[j];
					}
					else
					{
						lastrow = newDancer(U[colhead[j]], colhead[j], nowDancers, nowDancers, i, j);
						colH[lastrow] = colhead[j];
					}
				}
		}
	}

	void dance()
	{
		foundAns = false;
		selrows = vector<int>(rows, -1);
		search(0);
	}

	/** Dancing main procedure */
	void search(int depth)
	{
		if (R[head] == head) 
		{
			foundAns = true;
			selrowsans = vector<int>(depth);
			for (int i = 0; i < depth; ++i) 
				selrowsans[i] = selrows[i];
			return;
		}

		int selcol = 0;
		int minS = rows + 1;
		for (int i = R[head]; i != head; i = R[i])
		{
			if (cnt[i] < minS) { minS = cnt[i]; selcol = i; }
			if (cnt[i] == 0) return;
		}
		removeCol(selcol);
		for (int r = D[selcol]; r != selcol; r = D[r])
		{
			selrows[depth] = row[r];
			for (int j = R[r]; j != r; j = R[j])
				removeCol(colH[j]);

			search(depth + 1);

			for (int j = L[r]; j != r; j = L[j])
				recoverCol(colH[j]);

			if (foundAns) break;
		}
		recoverCol(selcol);
	}
};

// http://acm.hust.edu.cn/thanks/problem.php?id=1017 最原始问题 
int N, M;
void init1()
{
	while (scanf("%d%d", &N, &M) == 2)
	{
		vector<vector<bool> > m(N, vector<bool>(M, false));

		for (int i = 0; i < N; ++i)
		{
			int C;
			scanf("%d", &C);
			while (C--)
			{
				int j;
				scanf("%d", &j);
				m[i][j - 1] = true;
			}
		}

		DancingLink d(m);
		d.dance();
		if (d.foundAns)
		{
			printf("%d", d.selrowsans.size());
			for (int i = 0; i < d.selrowsans.size(); ++i)
				printf(" %d", d.selrowsans[i] + 1);
			printf("\n");
		}
		else
			printf("NO\n");
	}
}

/** soduku  http://poj.org/problem?id=3074 188MS */
vector<vector<bool> > m(9 * 9 * 9, vector<bool>(9 * 9 * 4, false));
bool coled[1000];

void init()
{
	string line;

	while (getline(cin, line))
	{
		if (line == "end") break;
		for (int i = 0; i < m.size(); ++i)
			for (int j = 0; j < m[0].size(); ++j)
				m[i][j] = false;
		memset(coled, false, sizeof(coled));

		for (int x = 0; x < 9;  ++x)
			for (int y = 0; y < 9; ++y)
			{
				if (line[x * 9 + y] != '.')
				{
					int d = line[x * 9 + y] - '1';
					int r = x * 81 + y * 9 + d;
					int c1 = x * 9 + y;
					int c2 = 81 + x * 9 + d;
					int c3 = 81 * 2 + y * 9 + d;
					int c4 = 81 * 3 + ((x / 3) * 3 + (y / 3)) * 9 + d;
					coled[c1] = coled[c2] = coled[c3] = coled[c4] = true;
					m[r][c1] = m[r][c2] = m[r][c3] = m[r][c4] = true;				
				}
			}

			for (int x = 0; x < 9;  ++x)
				for (int y = 0; y < 9; ++y)
				{
					if (line[x * 9 + y] == '.')
					{
						for (int d = 0; d < 9; ++d)
						{
							int r = x * 81 + y * 9 + d;
							int c1 = x * 9 + y;
							int c2 = 81 + x * 9 + d;
							int c3 = 81 * 2 + y * 9 + d;
							int c4 = 81 * 3 + ((x / 3) * 3 + (y / 3)) * 9 + d;
							if (!coled[c1] && !coled[c2] && !coled[c3] && !coled[c4])
								m[r][c1] = m[r][c2] = m[r][c3] = m[r][c4] = true;				
						}
					}
				}

				DancingLink dance(m);
				dance.dance();

				vector<int> sel = dance.selrowsans;
				for (int i = 0; i < sel.size(); ++i)
				{
					int t = sel[i];
					int x = t / 81;
					int y = t % 81 / 9;
					int d = t % 9;
					line[x * 9 + y] = '1' + d;
				}
				cout << line << endl;
	}
}

int main()
{
	init();

	return 0;
}


/** 求最小支配集，非精确覆盖 */
/**
const int maxDancer = 2000000;
int nowDancers = 0;
int L[maxDancer], R[maxDancer], U[maxDancer], D[maxDancer];
int colH[maxDancer];
int row[maxDancer], col[maxDancer], cnt[maxDancer];

inline void removeCol(int c)
{
    //L[R[c]] = L[c]; R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i])
    { 
        L[R[i]] = L[i]; R[L[i]] = R[i];
    }
}

void recoverCol(int c)
{
    for (int i = U[c]; i != c; i = U[i])
    { 
        L[R[i]] = i; R[L[i]] = i;
    }
    //L[R[c]] = c; R[L[c]] = c;
}

int newDancer(int up, int down, int left, int right, int r, int c)
{
    U[nowDancers] = up;
    D[nowDancers] = down;
    L[nowDancers] = left;
    R[nowDancers] = right;
    D[up] = U[down] = R[left] = L[right] = nowDancers;
    row[nowDancers] = r;
    col[nowDancers] = c;
    cnt[nowDancers] = 0;
    return nowDancers++;
}

class DancingLink
{
public:
    int head;
    vector<int> colhead;
    int rows;
    int cols;

    int minAns;
    bool foundAns;
    vector<int> selrows;
    vector<int> selrowsans;

    DancingLink(vector<vector<bool> > & matrix)
    {
        minAns = 9999;
        nowDancers = 0;
        rows = matrix.size();
        cols = matrix[0].size();

        head = newDancer(0, 0, 0, 0, -1, -1); 
        colhead.resize(cols);
        for (int j = 0; j < cols; ++j)
            colhead[j] = newDancer(nowDancers, nowDancers, L[head], head, -1, j);

        for (int i = 0; i < rows; ++i)
        {
            int lastrow = -1;
            for (int j = 0; j < cols; ++j)
                if (matrix[i][j])
                {
                    cnt[colhead[j]]++;
                    if (lastrow >= 0) 
                    {
                        lastrow = newDancer(U[colhead[j]], colhead[j], lastrow, R[lastrow], i, j);
                        colH[lastrow] = colhead[j];
                    }
                    else
                    {
                        lastrow = newDancer(U[colhead[j]], colhead[j], nowDancers, nowDancers, i, j);
                        colH[lastrow] = colhead[j];
                    }
                }
        }
    }

    void dance()
    {
        foundAns = false;
        selrows = vector<int>(rows, -1);
        search(0);
    }

    int estimate()
    {
        vector<bool> visit(cols, false);
        int ret = 0;
        for (int now = R[head]; now != head; now = R[now])
            if (cnt[now] > 0 && !visit[col[now]])
            {
                visit[col[now]] = true;
                ret++;
                for (int i = D[now]; i != now; i = D[i])
                    for (int j = R[i]; j != i; j = R[j])
                        visit[col[j]] = true;
            }
            return ret;
    }

    void search(int depth)
    {
        if (depth + estimate() >= minAns) 
            return;

        if (R[head] == head) 
        {
            minAns = min(minAns, depth);
            return;
        }

        int selcol = 0;
        int minS = rows + 1;
        for (int i = R[head]; i != head; i = R[i])
            if (cnt[i] < minS) { minS = cnt[i]; selcol = i; }

            //removeCol(selcol);
            for (int r = D[selcol]; r != selcol; r = D[r])
            {
                removeCol(r);
                for (int j = R[r]; j != r; j = R[j])
                    removeCol(j);

                search(depth + 1);

                for (int j = L[r]; j != r; j = L[j])
                    recoverCol(j);
                recoverCol(r);

                if (foundAns) break;
            }
            //recoverCol(selcol);
    }
};

int N, M;
string line;
int ditui[30][30];
void init()
{
    while (scanf("%d%d", &N, &M) == 2)
    {
        getline(cin, line);
        int empty = 0; int wall = 0;
        for (int i = 0; i < N; ++i)
        {
            getline(cin, line);
            for (int j = 0; j < M; ++j)
            {
                if (line[j] == '.') ditui[i][j] = -1;
                if (line[j] == '*') ditui[i][j] = -2;
                if (line[j] == '#') ditui[i][j] = wall++;
            }
        }    

        if (wall == 0)
        {
            cout << 0 << endl;
            continue;
        }

        vector<vector<bool> > matrix;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (ditui[i][j] == -1)
                {
                    vector<bool> now(wall, false);
                    int x = i; while (x < N && ditui[x][j] == -1) x++;
                    if (x < N && ditui[x][j] >= 0) now[ditui[x][j]] = true;
                    x = i; while (x >= 0 && ditui[x][j] == -1) x--;
                    if (x >= 0 && ditui[x][j] >= 0) now[ditui[x][j]] = true;

                    int y = j; while (y < M && ditui[i][y] == -1) y++;
                    if (y < M && ditui[i][y] >= 0) now[ditui[i][y]] = true;
                    y = j; while (y >= 0 && ditui[i][y] == -1) y--;
                    if (y >= 0 && ditui[i][y] >= 0) now[ditui[i][y]] = true;
                    matrix.push_back(now);

                    //debug3(i, j, now);
                }

                DancingLink dance(matrix);
                dance.dance();
                cout << dance.minAns << endl;
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
*/