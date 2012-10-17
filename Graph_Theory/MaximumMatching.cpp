#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
using namespace std;

const int N = 300;

int n;
bool g[N][N];
int Match[N];
int start, finish;
int que[N], q1, q2;
int fa[N], Base[N], NewBase;
bool inque[N], inpath[N], inflower[N];

void CreateGraph() {
  scanf("%d", &n);
  int u, v;
  while (scanf("%d%d", &u, &v) != EOF) g[u][v] = g[v][u] = true;
}
inline void Push(int u) {
  que[q2++] = u;
  inque[u] = true;
}
int FindCommonAncestor(int u, int v) {
  memset(inpath, 0, sizeof inpath);
  while (1) {
    u = Base[u];
    inpath[u] = true;
    if (u == start) break;
    u = fa[Match[u]];
  }
  while (1) {
    v = Base[v];
    if (inpath[v]) break;
    v = fa[Match[v]];
  }
  return v;
}
void ResetTrace(int u) {
  while (Base[u] != NewBase) {
    int &v = Match[u];
    inflower[Base[u]] = true;
    inflower[Base[v]] = true;
    u = fa[v];
    if (Base[u] != NewBase) fa[u] = v;
  }
}
void BlossomContract(int u, int v) {
  NewBase = FindCommonAncestor(u, v);
  memset(inflower, 0, sizeof inflower);
  ResetTrace(u);
  ResetTrace(v);
  if (Base[u] != NewBase) fa[u] = v;
  if (Base[v] != NewBase) fa[v] = u;
  for (int u = 1; u <= n; u++)
    if (inflower[Base[u]]) {
      Base[u] = NewBase;
      if (!inque[u]) Push(u);
    }
}
void FindAugmentingPath() {
  int u, v;
  memset(inque, 0, sizeof inque);
  memset(fa, 0, sizeof fa);
  for (int u = 1; u <= n; u++) Base[u] = u;
  q1 = 0;
  q2 = 0;
  Push(start);
  finish = 0;

  while (q1 < q2) {
    u = que[q1++];
    for (int v = 1; v <= n; v++)
      if (g[u][v] && Base[u] != Base[v] && Match[u] != v) {
        if (v == start || Match[v] > 0 && fa[Match[v]] > 0) BlossomContract(u, v);
        else if (fa[v] == 0) {
          fa[v] = u;
          if (Match[v] > 0) Push(Match[v]);
          else { finish = v; return; }
        }
      }
  }
}
void AugmentPath() {
  int u = finish, v, w;
  while (u > 0) {
    v = fa[u];
    w = Match[v];
    Match[v] = u;
    Match[u] = v;
    u = w;
  }
}
void Edmonds() {
  for (int u = 1; u <= n; u++)
    if (Match[u] == 0) {
      start = u;
      FindAugmentingPath();
      if (finish > 0) AugmentPath();
    }
}
void PrintMatch() {
  int cnt = 0;
  for (int u = 1; u <= n; u++) if (Match[u] > 0) cnt++;
  printf("%d\n", cnt);
  for (int u = 1; u <= n; u++) if (u < Match[u]) printf("%d %d\n", u, Match[u]);
}
int main() {
  CreateGraph();
  Edmonds();
  PrintMatch();
  return 0;
}
