#include <vector>
#include <iostream>
#include <map>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

long long Comb[100][100];

map<int, vector<vector<int> > > revColor;
struct State
{
  int off;
  vector<int> remainCnt;
  
  bool operator < (const State & other) const
  {
    return off < other.off || (off == other.off && remainCnt < other.remainCnt);
  }
};

map<State, long long> gf;

long long getGF(State s, vector<int> & colors)
{
  if (s.off >= colors.size()) return 1;
  if (gf.find(s) != gf.end()) return gf[s];
  long long & ret = gf[s];
  
  ret = 0;
  int c = colors[s.off];
  const vector<vector<int> > & v = revColor[c];
  for (int k = 0; k < v.size(); ++k)
  {
    bool ok = true;
    long long coff = 1;
    for (int i = 0; i < s.remainCnt.size(); ++i)
    {
      if (s.remainCnt[i] < v[k][i]) ok = false;
      coff *= Comb[s.remainCnt[i]][v[k][i]];
    }
    
    if (ok)
    {
      State news;
      news.off = s.off + 1;
      news.remainCnt = s.remainCnt;
      for (int i = 0; i < s.remainCnt.size(); ++i)
        news.remainCnt[i] -= v[k][i];
      ret += coff * getGF(news, colors);
    }
  }
  return ret;
}

long long getPolyaGroupBy(vector<int> colors, vector<int> groupSize, vector<int> groupCnt)
{
  static bool first = true;
  if (first)
  {
    first = false;
    memset(Comb, 0, sizeof(Comb));
    Comb[0][0] = 1;
    Comb[1][0] = 1;
    Comb[1][1] = 1;
    for (int i = 2; i <= 50; ++i)
    {
      Comb[i][0] = Comb[i][i] = 1;
      for (int j = 1; j < i; ++j)
        Comb[i][j] = Comb[i - 1][j - 1] + Comb[i - 1][j];
    }
  }
  
  revColor.clear();
  
  for (int i = 0; i < colors.size(); ++i)
    revColor[colors[i]] = vector<vector<int> > ();
  
  while (groupSize.size() < 3)
  {
    groupSize.push_back(0);
    groupCnt.push_back(0);
  }
  
  for (int i = 0; i <= groupCnt[0]; ++i)
    for (int j = 0; j <= groupCnt[1]; ++j)
      for (int k = 0; k <= groupCnt[2]; ++k)
      {
        int s = i * groupSize[0] + j * groupSize[1] + k * groupSize[2];
        if (revColor.find(s) == revColor.end()) continue;
        vector<int> v;
        v.push_back(i); v.push_back(j); v.push_back(k);
        revColor[s].push_back(v);
      }
  
  gf.clear();
  State init;
  init.off = 0;
  init.remainCnt = groupCnt;
  
  return getGF(init, colors);
}

/////////////////////////////////////
// sum (colors) = sum (groups) 
/////////////////////////////////////
long long getPolyaGroupBy(vector<int> colors, vector<int> groups)
{
  int G = (int) groups.size();
  int C = (int) colors.size();
  if (C > G) return 0;
  
  map<int, int> cnt;
  for (int i = 0; i < groups.size(); ++i)
    cnt[groups[i]]++;
  
  if (cnt.size() <= 3)
  {
    vector<int> groupSize;
    vector<int> groupCnt;
    for (map<int, int>::iterator itr = cnt.begin(); itr != cnt.end(); ++itr)
    {
      groupSize.push_back(itr->first);
      groupCnt.push_back(itr->second);
    }
    return getPolyaGroupBy(colors, groupSize, groupCnt);
  }
  
  vector<vector<int> > cByG(C);
  for (int s = 1; s < (1 << G); ++s)
  {
    int now = 0;
    for (int j = 0; j < G; ++j)
      if (s & (1 << j))
        now += groups[j];

    for (int j = 0; j < C; ++j)
      if (colors[j] == now) 
        cByG[j].push_back(s);
  }

  vector<vector<long long> > f;
  f.resize(C + 1);
  for (int i = 0; i <= C; ++i)
    f[i].resize(1 << G);
  f[0][0] = 1;

  for (int i = 0; i < C; ++i)
  {
    for (int j = 0; j < (1 << G); ++j)
      if (f[i][j] > 0)
        for (int k = 0; k < cByG[i].size(); ++k)
          if ((j & cByG[i][k]) == 0)
            f[i + 1][j | cByG[i][k]] += f[i][j];
  }

  //debug3(colors, groups, f[C][(1 << G) - 1]);
  return f[C][(1 << G) - 1];  
}

long long ans[41][41][41];
int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

void init()
{  
  for (int a = 0; a <= 40; ++a)
    for (int b = a; b <= 40; ++b)
      for (int c = b; c <= 40; ++c)
        if (a + b + c >= 3 && a + b + c <= 40)
        {
          int N = a + b + c;
          vector<int> colors;
          if (a > 0) colors.push_back(a);
          if (b > 0) colors.push_back(b);
          if (c > 0) colors.push_back(c);
          
          ans[a][b][c] = 0;
          for (int i = 0; i < N; ++i)
          {
            int lun = gcd(i, N);
            vector<int> group(lun, N / lun);
            ans[a][b][c] += getPolyaGroupBy(colors, group);
          }
          
          if (N % 2 == 0)
          {
            vector<int> g1(N / 2, 2);
            ans[a][b][c] += getPolyaGroupBy(colors, g1) * N / 2;
            vector<int> g2(N / 2 - 1, 2);
            g2.push_back(1);
            g2.push_back(1);
            ans[a][b][c] += getPolyaGroupBy(colors, g2) * N / 2;
          }
          else
          {
            vector<int> g1(N / 2, 2);
            g1.push_back(1);
            ans[a][b][c] += getPolyaGroupBy(colors, g1) * N;
          }
          
          ans[a][b][c] /= (N * 2);
          
          //cout << a << " " << b << " " << c << " " << ans[a][b][c] << endl;
        }
  
  int T;
  scanf("%d", &T);
  while (T--)
  {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    vector<int> v;
    v.push_back(a); v.push_back(b); v.push_back(c);
    sort(v.begin(), v.end());
    cout << ans[v[0]][v[1]][v[2]] << endl;
  }
}

void york()
{
  
}

int main()
{
  init();
  return 0;
}