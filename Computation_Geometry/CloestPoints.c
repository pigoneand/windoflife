#define sqr(z) ((z)*(z))
struct point {int x,y,id;} pt[100001];
int n,o[100002],on;

bool cmp(const point &a,const point &b) { return a.x < b.x;}
bool cmp2(const int &a,const int &b) { return pt[a].y < pt[b].y; }
int dis(const point & a, const point & b) { return (sqr(a.x-b.x)+sqr(a.y-b.y));}

const int INFI = 2000000000;
int mindis = INFI;
int ansi, ansj;

void search(int s,int t)
{
  int mid=(s+t)/2,i,j;
  if (s>=t) return;
  
  for (i=mid;i>=s && pt[i].x == pt[mid].x;--i); 
  search(s,i);
  for (i=mid;i<=t && pt[i].x == pt[mid].x;i++); 
  search(i,t); 
  
  int nowdistant = sqrt(mindis * 1.0) + 1;
  on=0;
  for (i=mid;i>=s && (pt[mid].x-pt[i].x) <= nowdistant; i--) o[on++]=i;
  for (i=mid+1;i<=t && (pt[i].x-pt[mid].x) <= nowdistant; ++i) o[on++]=i;
  sort(o,o+on,cmp2);
  
  for (i=0;i<on;++i) for (j=1;j<=8;j++) if (i+j<on)
    if (dis(pt[o[i]], pt[o[i + j]]) < mindis)
    {
      mindis = dis(pt[o[i]],pt[o[i+j]]);
      ansi = pt[o[i]].id;
      ansj = pt[o[i + j]].id;
    }
}


////////////////3xian
#include <cstdio>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

struct Point {
  double x, y;
  int i, q;
  bool operator <(const Point& e) const {
    return x < e.x || x == e.x && y < e.y;
  }
};

struct cmp_y {
  bool operator () (Point *a, Point *b) const {
    return a->y < b->y;
  }
};

double dis(const Point& a, const Point& b) {
  return hypot(a.x - b.x, a.y - b.y);
}

double york(Point* p, int n, Point& pa, Point& pb) {
  multiset<Point*, cmp_y> s;
  Point t;
  double d = 1e50;
  sort(p, p + n);
  for (int i = 0, lf = 0; i < n; i++) {
    t.y = p[i].y - d;
    for (; lf < i && p[i].x - p[lf].x >= d; lf++) s.erase(s.find(p + lf));
    for (set<Point*, cmp_y>::iterator it = s.upper_bound(&t); it != s.end() && p[i].y + d > (*it)->y; ++it) {
      double k = dis(p[i], **it);
      if (k < d) {
        d = k;
        pa = p[i];
        pb = **it;
      }
    }
    s.insert(p + i);
  }
  return d;
}