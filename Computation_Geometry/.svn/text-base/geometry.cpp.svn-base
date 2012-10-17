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

//#define OPENCV

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

const double eps = 1e-6;
const double eps_arc = 1e-10;
const double pi = acos(-1.0);
const double INF = 1e20;

/** Return a float number's sign */
inline int sign(double d) { return d < -eps ? -1 : d > eps; }
inline double sqr(double x) { return x * x; }

struct Point 
{
  int id;
  double x, y;
  Point() { x = 0.0; y = 0.0; }
  Point(double nx, double ny) : x(nx), y(ny) {}
  Point(double nx, double ny, int nid) : x(nx), y(ny), id(nid) {} 
  Point turnLeft() const { return Point(-y, x); }
  Point turnRight() const { return Point(y, -x); } 
  Point rotate(double ang) const { return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang)); }

  inline double length() { return sqrt(x * x + y * y); }
  void normalize() { double r = length(); if (sign(r) != 0)  x /= r,y /= r; }

  /** Consider the float precision to judge whether two points are the same */
  inline bool equal(const Point & other) const {
    return sign(x - other.x) == 0 && sign(y - other.y) == 0;
  }

  friend ostream & operator << (ostream & out , const Point & point)
  {
    out << "(" << point.x << "," << point.y << ")";
    return out;
  }

  friend istream & operator >> (istream & in, Point & point)
  {
    in >> point.x >> point.y;
    return in;
  }
};

#ifdef OPENCV
#include "opencvdebug.h"
using namespace Drawing;
#endif

bool comPointByX(const Point & a, const Point & b) { return a.x < b.x; }
bool comPointEqual(const Point & a, const Point & b) { return a.equal(b); }

//////////////////////////////////////////////////////////////////////
// BASIC OPERATIONS
//////////////////////////////////////////////////////////////////////
inline Point operator + (const Point & a, const Point & b) { return Point(a.x + b.x, a.y + b.y); }
inline Point operator - (const Point & a , const Point & b) { return Point(a.x - b.x, a.y - b.y); }
inline Point operator * (const Point & a , double d) { return Point(a.x * d, a.y * d); }
inline Point operator / (const Point & a , double d) { if (sign(d) == 0) return Point(); 	return Point(a.x / d, a.y / d); }
inline bool operator == (const Point & a , const Point & b) { return a.x == b.x && a.y == b.y; }
inline bool operator != (const Point & a , const Point & b) { 	return a.x != b.x || a.y != b.y; }
inline double dist(const Point & a , const Point & b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); }
inline double sqrdist(const Point & a , const Point & b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }

/** Cross Product */
inline double operator ^ (const Point & a , const Point & b) { return a.x * b.y - a.y * b.x; }
inline double cross(const Point & p , const Point & a , const Point & b) { return (a - p) ^ (b - p); }

/** Dot product */
inline double operator * (const Point & a , const Point & b) { return a.x * b.x + a.y * b.y; }
inline double dot(const Point & p , const Point & a , const Point & b) {	return (a - p) * (b - p); }

/** return degree of two segment span */
inline double segDegree(const Point & p, const Point & a, const Point & b)
{
  double d = dot(p, a, b);
  double cosd =  d / dist(a, p) / dist(b, p);
  if (cosd > 1.0) cosd = 1.0;
  if (cosd < -1.0) cosd = -1.0;
  return acos(cosd);
}

/** cos theory */
inline double segDegree(double a, double b, double c)
{
  double ret = a * a + b * b - c * c;
  ret = ret / a / b / 2;
  if (ret > 1.0) ret = 1.0;
  if (ret < -1.0) ret = -1.0;
  return acos(ret);
}

inline double triangleArea(double a, double b, double c)
{
  double p = (a + b + c) / 2;
  return sqrt(p * (p - a) * (p - b) * (p - c));
}

///////////////////////////////////////////////////////////////////////////
// OPERATION ABOUT segment line
///////////////////////////////////////////////////////////////////////////
/** Whether Point p is on the segment [a, b] or not */
inline bool onSeg(const Point & p , const Point & a , const Point & b) { return ( sign(cross(p, a, b)) == 0 && sign(dot(p, a, b)) <= 0) ; }

/** Whether Point p is on the ray from a to b */
inline bool onRay(const Point & p , const Point & a , const Point & b) { return ( sign(cross(p, a, b)) == 0 && sign(dot(a, p, b)) >= 0) ;}

/** Whether Point p is on the straight line a-b or not */
inline bool onLine(const Point & p , const Point & a , const Point & b) { return sign(cross(p,a,b))==0; }

/** Given a line equation Ax + By + C = 0, return two diff points on it, A^2 +B^2 <> 0 */
pair<Point, Point> onLine(double A, double B, double C)
{
  if (sign(A) == 0)
    return make_pair(Point(0, -C / B), Point(1, -C / B));
  if (sign(B) == 0)
    return make_pair(Point(-C / A, 0), Point(-C / A, 1));
  if (fabs(A + B + C) < eps)
    return make_pair(Point(-(C + B) / A, 1), Point(2, -(C + A * 2) / B));
  return make_pair(Point(-(C + B) / A, 1), Point(1, -(C + A) / B));
}

/** Find the intersection point of two strait lines a-b and c-d, 
storing the result in p */
vector<Point> interLine(const Point & a , const Point & b , const Point & c , const Point & d) 
{
  vector<Point> inters;
  double u = cross(a, c, b), v = cross(a, b, d);
  if (sign(u + v) == 0) return inters;
  Point p = (c * v + d * u) / (u + v);
  inters.push_back(p);
  return inters;
}

/** Find the intersection point of two segment a-b and c-d,
storing the result in p */
vector<Point> interSeg(const Point & a , const Point & b , const Point & c , const Point & d)
{
  vector<Point> inters = interLine(a, b, c, d);
  if (inters.size() == 0) return inters;
  const Point & p = inters[0];
  if (onSeg(p, a, b) && onSeg(p, c, d)) 
    return inters;
  else {
    inters.clear();
    return inters;
  }       
}

/** Given a segment, return its vertical equally segment */
pair<Point, Point> getVerticalEquallySegment(const Point & a, const Point & b)
{
  Point mid = (a + b) / 2;
  Point dir = mid - a;
  dir = dir.turnLeft();
  Point begin = mid - dir;
  Point end = mid + dir;
  return make_pair(begin, end);
}

/** Given a line and a point p, return the point on the line which has the minimum distance to the point */
Point getMinimumDistPointOnLine(const Point & a, const Point & b, const Point & p)
{
  if (onLine(p, a, b)) return p;
  pair<Point, Point> vertical = getVerticalEquallySegment(a, b);
  const Point & q = p + (vertical.second - vertical.first);
  vector<Point> inter = interLine(a, b, p, q);
  return inter[0];
}

/** Given a segment and a point p, return the point on the segment which has the minimum distance to the point */
Point getMinimumDistPointOnSeg(const Point & a, const Point & b, const Point & p)
{
  Point q = getMinimumDistPointOnLine(a, b, p);
  if (onSeg(q, a, b)) return q;
  if (dist(a, p) < dist(b, p)) return a; else return b;
}


/** Given a segment and a point p, return the point on the ray which has the minimum distance to the point */
Point getMinimumDistPointOnRay(const Point & a, const Point & b, const Point & p)
{
  Point q = getMinimumDistPointOnLine(a, b, p);
  if (onRay(q, a, b)) return q;
  if (dist(a, p) < dist(b, p)) return a; else return b;
}

/** Given a line a-b, return the reflection point of point p by this line */
Point getReflectionPointByLine(const Point & a, const Point & b, const Point & p)
{
  Point q = getMinimumDistPointOnLine(a, b, p);
  return q * 2 - p;
}

//////////////////////////////////////////////////////////////
// OPERATION ABOUT circle 
//////////////////////////////////////////////////////////////

/** Given three points, return a circle */
void formCircle(const Point & a, const Point & b, const Point & c, 
  Point & o, double & r)
{
  pair<Point, Point> l1 = getVerticalEquallySegment(a, b);
  pair<Point, Point> l2 = getVerticalEquallySegment(b, c);
  o = interLine(l1.first, l1.second, l2.first, l2.second)[0];
  r = dist(o, a);
}

/** Intersection of two circles, 
whose centers are a and b, radius are r1 and r2, respectively
Return the number of intersections, storing the result to array p */
vector<Point> interCir(const Point & a , const Point & b , double r1 , double r2) {
  vector<Point> ret;
  double d = dist(a, b), d1 = ((sqr(r1) - sqr(r2)) / d + d) / 2;
  if (sign(r1 + r2 - d) < 0 || sign(abs(r1 - r2) - d) > 0) return ret;
  Point mid = a + ((b - a) / d) * d1;
  if (sign(r1 + r2 - d) == 0) {
    ret.push_back(mid);
    return ret;
  }
  Point incr = (b - a).turnLeft() / d * sqrt(sqr(r1) - sqr(d1));
  ret.push_back(mid - incr);
  ret.push_back(mid + incr);
  return ret;
}

/** Intersection of two circles, 
return the intersect area */
double interCirArea(Point a, Point b, double ra, double rb)
{
  double d, dA, dB;
  d = dist(a, b);
  if ((d < eps) || (d + ra <= rb) || (d + rb <= ra)) 
    return sqr((rb < ra) ? rb : ra) * pi;
  if (d >= ra + rb) 
    return 0;

  dA = (sqr(d) + sqr(ra) - sqr(rb)) / d / 2;
  dB = d - dA;

  return sqr(ra) * acos(dA/ra) - dA * sqrt(sqr(ra)-sqr(dA))
    + sqr(rb) * acos(dB/rb) - dB * sqrt(sqr(rb)-sqr(dB));
}

/** Intersection of a line and a circle. The circle's center is o, radius is r, 
while the straight line is a-b
Return the number of intersections, storing the result to array p
*/
vector<Point> interLineCir(const Point & o , double r , const Point & a , 
  const Point & b) {
    vector<Point> ret;
    double d = dist(a, b), h = fabs(cross(a, b, o)) / d;
    if (sign(r - h) < 0) return ret;
    double d1 = ((sqr(dist(o, a)) - sqr(dist(o, b))) / d + d) / 2;
    Point mid = a + (b - a) / d * d1;
    if (sign(r - h) == 0) {
      ret.push_back(mid);
      return ret;
    }
    Point incr = (b - a) / d * sqrt(sqr(r) - sqr(h));
    ret.push_back(mid - incr);
    ret.push_back(mid + incr);
    return ret;
}

vector<Point> interSegCir(const Point & o, double r, const Point & a, const Point & b)
{
  vector<Point> temp = interLineCir(o, r, a, b);
  vector<Point> ret;
  for (int i = 0; i < (int) temp.size(); ++i)
    if (onSeg(temp[i], a, b))
      ret.push_back(temp[i]);
  return ret;
}

/** Tangent from Point a, to circle whose center is o, radius is r
Return the number of intersections, storing the result to array p
*/
vector<Point> tangentCirPoint(const Point & o , double r , const Point & a) {
  vector<Point> ret;
  double d = dist(a, o);
  if (sign(d - r) < 0) return ret;
  if (sign(r - d) == 0) {
    ret.push_back(a);
    return ret;
  }
  return interCir(o, a, r, sqrt(sqr(d) - sqr(r)));
}

inline bool inCircle(const Point & p, const pair<Point, double> & circle) {
  double dis = dist(p, circle.first);
  return sign(dis - circle.second) <= 0;
}

inline bool inCircle2(const Point & p, const pair<Point, double> & circle) {
  double dis = dist(p, circle.first);
  return sign(dis - circle.second) < 0;
}

/**
* Given two points just on the circle, return their shortest length along the circle 
*/
double distOnCircle(const Point & a, const Point & b, const Point & o, double r)
{
  double costheta = (a - o) * (b - o) / r / r;
  double theta = acos(costheta);
  return r * theta;
}

/** Given three points, find a circle that cover these three points which has
* minimal ares
*/
pair<Point, double> minCoverCircle(const Point & a, const Point & b, const
  Point & c) 
{
  if (a.equal(b)) 
    return make_pair((b + c) / 2, dist(b, c) / 2);
  if (b.equal(c)) 
    return make_pair((c + a) / 2, dist(c, a) / 2);
  if (c.equal(a))
    return make_pair((a + b) / 2, dist(a, b) / 2);

  if (onLine(a, b, c)) {
    if (onSeg(a, b, c)) 
      return make_pair((b + c) / 2, dist(b, c) / 2);
    if (onSeg(b, a, c))
      return make_pair((a + c) / 2, dist(a, c) / 2);
    return make_pair((a + b) / 2, dist(a, b) / 2);
  }

  pair<Point, double> minCircle;
  minCircle.second = INF;

  pair<Point, double> cir1 = make_pair((a + b) / 2, dist(a, b) / 2);
  pair<Point, double> cir2 = make_pair((b + c) / 2, dist(b, c) / 2);
  pair<Point, double> cir3 = make_pair((a + c) / 2, dist(a, c) / 2);

  if (inCircle(c, cir1) && cir1.second < minCircle.second)
    minCircle = cir1;
  if (inCircle(a, cir2) && cir2.second < minCircle.second)
    minCircle = cir2;
  if (inCircle(b, cir3) && cir3.second < minCircle.second)
    minCircle = cir3;

  Point mid1 = (a + b) / 2;
  Point mid2 = (b + c) / 2;
  Point turn1 = (b - a).turnLeft();
  Point turn2 = (c - b).turnLeft();
  turn1 = mid1 + turn1;
  turn2 = mid2 + turn2;

  vector<Point> inters = interLine(mid1, turn1, mid2, turn2);
  pair<Point, double> cir4 = make_pair(inters[0], dist(inters[0], a));
  if (cir4.second < minCircle.second)
    minCircle = cir4;

  return minCircle;
}

/** Given a circle and a triangle, one of the triangle vertex is as same as the center of the circle
return their intersect area , AC by PKU 2986, 3675, URAL 
*/
double getCircleTriangleInterArea(const Point & o, double r, const Point & a, const Point & b)
{
  vector<Point> abcir = interSegCir(o, r, a, b);
  if (abcir.size() == 2 && dist(a, abcir[0]) > dist(a, abcir[1])) swap(abcir[0], abcir[1]);

  abcir.insert(abcir.begin(), a);
  abcir.push_back(b);

  double ret = 0;
  for (int i = 0; i < (int) abcir.size() - 1; ++i)
  {
    Point & t1 = abcir[i];
    Point & t2 = abcir[i + 1];
    if (inCircle((t1 + t2) / 2, make_pair(o, r)))
      ret += fabs(cross(o, t1, t2) / 2);
    else
      ret += segDegree(o, t1, t2) * r * r * 0.5;
  }
  return ret;
}


////////////////////////////////////////////////////////////
// OPERATION ABOUT polygon
////////////////////////////////////////////////////////////

/** A Convex ploygon */
class MyPolygon 
{
public:
  /** Points, points in polygon is counter-clockwise */
  vector<Point> pt;

  inline void clear() { pt.clear(); }
  inline int size() const { return (int)pt.size(); }
  inline void addPoint(Point a) { pt.push_back(a); }
  inline void removePoint() { pt.pop_back(); }
  inline Point & operator [] (int offset) { return pt[offset]; }
  inline void getSeg(int offset, Point & a, Point & b) { a = pt[offset]; b = pt[(offset + 1) >= (int) pt.size() ? 0 : (offset + 1)]; }
  inline int nextnode(int i) { int ret = i + 1; if (ret == pt.size()) ret = 0; return ret; }
  inline int lastnode(int i) { int ret = i - 1; if (ret < 0) ret = (int) pt.size() - 1; return ret; }
  
  /** Whether a Point is inside a polygon, 
  * 1 : inside, 
  * -1 : outside, 
  *  0 : on the edge
  */
  int inside(const Point & p) 
  {
    int N = (int) pt.size();
    bool positiveSign = false;
    bool negativeSign = false;

    for (int i = 0; i < N; ++i)
    {
      Point & now = pt[i];
      Point & next = pt[(i + 1) % N];
      Point t1 = next - now;
      Point t2 = p - next;
      int s = sign(t1 ^ t2);
      if (s == 0) 
      {
        if (onSeg(p, now, next))
          return 0;
        else 
          return -1;
      }
      if (s > 0) positiveSign = true;
      if (s < 0) negativeSign = true;
    }

    if (positiveSign && negativeSign) 
      return -1;
    else
      return 1;
  }

  /** return the area intersection with a circle, AC by PKU 3675 */
  double interCirArea(const Point & o, double r)
  {
    int N = (int) pt.size();
    double ret = 0;

    for (int i = 0; i < N; ++i)
    {
      Point & now = pt[i];
      Point & next = pt[(i + 1) % N];
      double area = getCircleTriangleInterArea(o, r, now, next);
      if (cross(now, next, o) >= 0) 
        ret += area;
      else
        ret -= area;
    }
    return ret;
  }

  /** return the intersection situation with a circle
  * 1 contained in the circle
  * 2 circle contained in the polygon 
  * 3 intersect 
  * 4 outside 
  */
  int interCircle(const Point & o, double r, vector<Point> & inters)
  {
    inters.clear();

    bool ok = true;
    for (int i = 0; i < (int) pt.size(); ++i)
      if (!inCircle2(pt[i], make_pair(o, r))) ok = false;
    if (ok) return 1;

    if (inside(o) == 1)
    {
      double mindis = 1e20;
      for (int i = 0; i < (int) pt.size(); ++i)
      {
        Point a = pt[i];
        Point b = pt[(i + 1) % pt.size()];
        Point p = getMinimumDistPointOnSeg(a, b, o);
        mindis = min(mindis, dist(p, o));
      }
      if (mindis > r + eps) return 2;
    }

    for (int i = 0; i < (int) pt.size(); ++i)
    {
      Point a = pt[i];
      Point b = pt[(i + 1) % pt.size()];
      vector<Point> ps = interSegCir(o, r, a, b);
      inters.insert(inters.end(), ps.begin(), ps.end());
    }
    return inters.size() > 0 ? 3 : 4;
  }

  /** return the point in or on the polygon which has the minimum distance to the given point p, 
  AC URAL 1215 */
  Point getMinDistPointInPolygon(const Point & p)
  {
    if (inside(p) >= 0) return p;
    int N = (int) pt.size();

    double minDis = INF;
    Point ret;
    for (int i = 0; i < N; ++i)
    {
      Point & a = pt[i];
      Point & b = pt[(i + 1) % N];
      Point nowMin = getMinimumDistPointOnSeg(a, b, p);
      double nowDis = dist(nowMin, p);
      if (nowDis < minDis) minDis = nowDis, ret = nowMin;
    }
    return ret;
  }

  /** Cut the polygon by the strait line a-b, 
  preserving the right side of the straight line
  Provided that the polygon is convex
  */
  MyPolygon cut(const Point & a, const Point & b) {
    MyPolygon newPoly;
    Point temp;
    for (int i = 0; i < (int) pt.size(); i++) 
    {
      Point & nowP = pt[i];
      Point & nextP = pt[(i + 1) >= (int) pt.size() ? 0 : i + 1];
      if (sign(cross(a, b, nowP)) <= 0) newPoly.addPoint(nowP);
      if (sign(cross(a, b, nowP)) * sign(cross(a, b, nextP)) < 0) 
      {
        vector<Point> inters = interLine(nowP, nextP, a, b);
        if (inters.size() > 0) 	newPoly.addPoint(inters[0]);
      }
    }
    return newPoly;
  }

  /** intersect two polygon, return their intersection polygon */
  MyPolygon inter(MyPolygon & b)
  {
    MyPolygon ret = *this;
    for (int i = 0; i < b.size(); ++i)
    {
      Point s, t;
      b.getSeg(i, s, t);
      ret = ret.cut(t, s);
    }
    return ret;
  }
  
  /**
  * Intersect a line with this polygon
  * return the intersect points 
  */
  vector<Point> polyInterLine(const Point & a, const Point & b)
  {
    int N = (int) pt.size();
    vector<Point> ret;
    Point temp;
    for (int i = 0; i < N; ++i)
    {
      Point & now = pt[i];
      Point & next = pt[(i + 1) % N];
      if (sign(cross(a, b, now)) * sign(cross(a, b, next)) <= 0)
      {
        vector<Point> inters = interLine(a, b, now, next);
        if (inters.size() > 0)
          ret.push_back(inters[0]);
      }
    }
    return ret;
  }

  /** return the area of this polygon */
  double area()
  {
    int size = this->size();
    if (size <= 2) return 0.0;

    addPoint(this->pt[0]);
    double ans = 0;
    for (int i = 0; i < size; ++i) ans += (pt[i] ^ pt[i+1]);
    removePoint();

    return fabs(ans / 2);
  }

  /** return the length of this polygon */
  double length()
  {
    int size = this->size();
    addPoint(pt[0]);
    double ans = 0;
    for (int i = 0; i < size; ++i) ans += dist(pt[i], pt[i+1]);
    removePoint();
    return ans;
  }

  /** Get the Diameter of this polygon */
  pair<Point, Point>  getDiameter()
  {
    if (this->size() == 0) 
      return make_pair(Point(0,0), Point(0,0));
    if (this->size() == 1)
      return make_pair(pt[0], pt[0]);
    if (this->size() == 2)
      return make_pair(pt[0], pt[1]);

    pair<Point, Point> ret;
    double diameter = 0.0;
    
    int N = (int) pt.size();
    int j = 1;
    int nj = j + 1;
    if (nj >= N) nj = 0;
    for (int i = 0; i < N; ++i)
    {
      Point a, b;
      getSeg(i, a, b);
      while (cross(a, b, pt[nj]) > cross(a, b, pt[j]))
      {
        j++;
        if (j >= N) j = 0;
        nj = j + 1;
        if (nj >= N) nj = 0;
      }
      if (dist(pt[i], pt[j]) > diameter)
      {
        diameter = dist(pt[i], pt[j]);
        ret = make_pair(pt[i], pt[j]);
      }
    }
    return ret;
  }

  /** Find a circle that cover the polygon with minimal area 
  */
  pair<Point, double> getMinCoverCircle()
  {
    vector<Point> & points = pt;

    if (points.size() == 0)
      return make_pair(Point(0, 0), 0);
    if (points.size() == 1)
      return make_pair(points[0], 0);
    if (points.size() == 2)
      return make_pair((points[0] + points[1]) / 2, dist(points[0], points[1]) / 2);

    Point a = points[0];
    Point b = points[1];
    Point c = points[2];
    pair<Point, double> nowCircle = minCoverCircle(a, b, c);

    while (true) {
      bool found = false;
      double maxDis = nowCircle.second;
      Point maxDisPoint;
      for (unsigned int i = 0; i < points.size(); ++i) {
        double dis = dist(points[i], nowCircle.first);
        if (sign(dis - maxDis) > 0) {
          maxDis = dis;
          maxDisPoint = points[i];
          found = true;
        }
      }

      if (!found) break;
      Point d = maxDisPoint;

      Point newa, newb, newc;
      pair<Point, double> cir1 = minCoverCircle(a, b, d);
      pair<Point, double> cir2 = minCoverCircle(a, c, d);
      pair<Point, double> cir3 = minCoverCircle(b, c, d);
      pair<Point, double> minCircle;
      minCircle.second = INF;
      if (inCircle(c, cir1) && cir1.second < minCircle.second) {
        minCircle = cir1;
        c = d;
      }
      else {
        if (inCircle(b, cir2) && cir2.second < minCircle.second) {
          minCircle = cir2;
          b = d;
        }
        else {
          if (inCircle(a, cir3) && cir3.second < minCircle.second) {
            minCircle = cir3;
            a = d;
          }
        }
      }
      nowCircle = minCircle;
    }
    return nowCircle;
  }

  friend ostream & operator << (ostream & out, const MyPolygon & poly) 
  {
    int size = poly.size();
    for (int i = 0; i < size; ++i) 
      out << poly.pt[i] << "\t";
    return out;
  }

#ifdef OPENCV
  void drawPolygon(const CvScalar & segc = CV_RGB(0, 255, 0))
  {
    vector<pair<Point, Point> > lines;
    lines.resize(this->size());
    for (int i = 0; i < (int) lines.size(); ++i)
      this->getSeg(i, lines[i].first, lines[i].second);
    drawPoints(this->pt, CV_RGB(0, 0, 255));
    drawSegs(lines, segc);
  }
#endif
};


bool comPs(const pair<Point, int> & a, const pair<Point, int> & b)
{
  int s = sign(a.first.x - b.first.x);
  if (s < 0) return true;
  if (s > 0) return false;
  return a.second < b.second;
}

// Return the union area of a set of polygons 
double unionArea(vector<MyPolygon> & polys)
{
  double ans = 0;
  int N = (int) polys.size();
  if (N == 0) return ans;

  vector<pair<double, double> > lines;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < polys[i].size(); ++j)
    {
      Point a, b;
      polys[i].getSeg(j, a, b);
      if (fabs(a.x - b.x) < eps) continue;
      double deg = atan2(b.y - a.y, b.x - a.x);
      double bb = a.y - (b.y - a.y) * a.x / (b.x - a.x);

      bool close = false;
      for (int k = 0; k < (int) lines.size(); ++k)
        //if (fabs(lines[k].first - deg) < eps && fabs(lines[k].second - bb) < eps) close = true;
        if (fabs(lines[k].first - deg) < eps_arc && fabs(lines[k].second - bb) < eps) close = true;
      if (close) continue;

      lines.push_back(make_pair(deg, bb));

      vector<pair<Point, int> > ps;
      for (int k = 0; k < N; ++k)
      {
        bool isPar = false;
        for (int l = 0; l < polys[k].size(); ++l)
        {
          Point c, d;
          polys[k].getSeg(l, c, d);
          if (fabs(c.x - d.x) < eps) continue;

          if (onLine(c, a, b) && onLine(d, a, b))
          {
            int dir = (c.x < d.x) ? 2 : 1;
            if (c.x > d.x) swap(c, d);
            ps.push_back(make_pair(c, dir * 2));
            ps.push_back(make_pair(d, dir * 2 + 1));
            isPar = true; 
            break;
          }
        }
        if (isPar) continue;

        vector<Point> inters;
        for (int l = 0; l < polys[k].size(); ++l)
        {
          Point c, d;
          polys[k].getSeg(l, c, d);
          vector<Point> t = interLine(a, b, c, d);
          for (int z = 0; z < (int) t.size(); ++z) if (onSeg(t[z], c, d)) inters.push_back(t[z]);
        }
        sort(inters.begin(), inters.end(), comPointByX);
        inters.resize(unique(inters.begin(), inters.end(), comPointEqual) - inters.begin());

        if (inters.size() >= 2)
        {
          ps.push_back(make_pair(inters.front(), 0));
          ps.push_back(make_pair(inters.back(), 1));
        }
      }

      sort(ps.begin(), ps.end(), comPs);

      int cntPosi = 0, cntNega = 0;
      int cntIn = 0;
      for (int k = 0; k < (int) ps.size(); ++k)
      {
        double x2 = ps[k].first.x;
        double y2 = ps[k].first.y;
        double x1 = 0, y1 = 0;
        if (k > 0) { x1 = ps[k - 1].first.x; y1 = ps[k - 1].first.y; }
        double area = (x2 - x1) * (y2 + y1) / 2;
        if (cntPosi > 0 && cntNega == 0 && x2 - x1 > eps && cntIn == 0)
          ans += area;
        if (cntPosi == 0 && cntNega > 0 && x2 - x1 > eps && cntIn == 0) 
          ans -= area;

        int id = ps[k].second;
        if (id == 2) cntPosi++; 
        if (id == 4) cntNega++;
        if (id == 0) cntIn++; 
        if (id == 3) cntPosi--;
        if (id == 5) cntNega--;
        if (id == 1) cntIn--;
      }
    }

    return ans;
}

///////////////////////////////////////////////
// ADVANCED ALGORITHM
///////////////////////////////////////////////
struct ConvexHull
{
  static inline bool cmp(const Point &a, const Point &b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
  }

  /** Calculate the convex hull represented by array p, points in polygon is counter-clockwise */
  static MyPolygon convexHull(const vector<Point> & points, bool needInnerEdgePoint = false) 
  {
    vector<Point> p(points.begin(), points.end());
    vector<int> stack(p.size() + 1);
    MyPolygon poly;
    poly.clear();
    if (p.size() == 0) 
      return poly;
    if (p.size() == 1) {
      poly.addPoint(points[0]);
      return poly;
    }

    sort(p.begin(), p.end(), ConvexHull::cmp); 

    int threshold = 0;
    if (needInnerEdgePoint) 
      threshold = 1;

    int N = (int)p.size();
    int top = -1;
    stack[++top] = 0; stack[++top] = 1;
    for (int i = 2; i < N; i++)
    {
      while (top >= 1 && 
        sign(cross(p[stack[top - 1]], p[i], p[stack[top]])) >= threshold) top--; 
      stack[++top] = i;
    }
    int temp_top = top; 
    stack[++top] = N - 2;
    for (int i = N - 3; i >= 0; i--)
    {
      while (top >= temp_top + 1 && 
        sign(cross(p[stack[top - 1]], p[i], p[stack[top]])) >= threshold) top--; 
      stack[++top] = i;
    }

    for (int i = 0; i < top; ++i) 
      poly.addPoint(p[stack[i]]);
    return poly;
  }
};


////////////////////////////////////////////////////////////////
// HALF-PLANE INTERSECTION
////////////////////////////////////////////////////////////////

/////////// ORZ zhuzeyuan //////////////////////
struct Cvector {
  Point s, e;
  double ang, d;
};

void setline(double x1, double y1, double x2, double y2, Cvector &v) {
  v.s.x = x1; v.s.y = y1;
  v.e.x = x2; v.e.y = y2;
  v.ang = atan2(y2 - y1, x2 - x1);
  if (sign(x1 - x2))    v.d = (x1 * y2 - x2 * y1) / fabs(x1 - x2);
  else                v.d = (x1 * y2 - x2 * y1) / fabs(y1 - y2);
}

//判向量平行
bool parallel(const Cvector &a, const Cvector &b) {
  double u = (a.e.x - a.s.x) * (b.e.y - b.s.y) 
    - (a.e.y - a.s.y) * (b.e.x - b.s.x);
  return sign(u) == 0;
}

//求两向量(直线)交点 (两向量不能平行或重合)
Point CrossPoint(const Cvector &a, const Cvector &b) {
  Point res;
  double u = cross(a.s, a.e, b.s), v = cross(a.e, a.s, b.e);
  res.x = (b.s.x * v + b.e.x * u) / (u + v);
  res.y = (b.s.y * v + b.e.y * u) / (u + v);
  return res;
}

//半平面交排序函数[优先顺序: 1.极角 2.前面的直线在后面的左边]
static bool VecCmp(const Cvector &l, const Cvector &r) {
  if (sign(l.ang - r.ang)) return l.ang < r.ang;
  return l.d < r.d;
}

Cvector deq[100000]; //用于计算的双端队列

// 获取半平面交的多边形（多边形的核）
// 注意:1.半平面在向量左边, 2.函数会改变vec[]中的值
// 函数运行后如果n[即返回多边形的点数量]为0则
// 不存在半平面交的多边形（不存在区域或区域面积无穷大）
// @warning: vec will be changed
void HalfPanelCross(vector<Cvector> vec, vector<Point> & cp) 
{
  int i, tn; 
  cp.clear();
  int n = (int) vec.size();
  sort(vec.begin(), vec.end(), VecCmp);
  for(i = tn = 1; i < n; ++i) //平面在向量左边的筛选
    if(sign(vec[i].ang - vec[i - 1].ang) != 0)
      vec[tn++] = vec[i];
  n = tn;
  int bot = 0, top = 1;
  deq[0] = vec[0];
  deq[1] = vec[1]; // vec[]大小不可小于2
  for (i = 2; i < n; ++i) {
    if (parallel(deq[top], deq[top - 1]) ||
      parallel(deq[bot], deq[bot + 1]) ) return ;
    while ( bot < top && sign( cross(vec[i].s, vec[i].e,
      CrossPoint(deq[top], deq[top - 1])) ) < 0 ) top--;
    while ( bot < top && sign( cross(vec[i].s, vec[i].e, 
      CrossPoint(deq[bot], deq[bot + 1])) ) < 0 ) bot++;
    deq[++top] = vec[i];
  }
  while ( bot < top && sign( cross(deq[bot].s, deq[bot].e, 
    CrossPoint(deq[top], deq[top - 1])) ) < 0 ) top--;
  while ( bot < top && sign( cross(deq[top].s, deq[top].e, 
    CrossPoint(deq[bot], deq[bot + 1])) ) < 0 ) bot++;
  if (top <= bot + 1) return ; // 两条或两条以下的直线，面积无穷大
  for (i = bot; i < top; i ++)
    cp.push_back(CrossPoint(deq[i], deq[i + 1]));
  if (bot < top + 1)
    cp.push_back(CrossPoint(deq[bot], deq[top]));
  cp.resize(unique(cp.begin(), cp.end(), comPointEqual) - cp.begin());
  for (i = 0; i < (int) cp.size(); ++i) {
    if (sign(cp[i].x) == 0) cp[i].x = 0;
    if (sign(cp[i].y) == 0) cp[i].y = 0;
  }
}

class HalfPlanes
{
public:
  MyPolygon poly;
  HalfPlanes(double maxRange)
  {
    poly.addPoint(Point(-maxRange, -maxRange));
    poly.addPoint(Point(maxRange, -maxRange));
    poly.addPoint(Point(maxRange, maxRange));
    poly.addPoint(Point(-maxRange, maxRange));
  }

  HalfPlanes(Point & a, Point & b, Point & c, Point & d)
  {
    poly.addPoint(a);
    poly.addPoint(b);
    poly.addPoint(c);
    poly.addPoint(d);
  }
  
  static HalfPlanes construct(const vector<Point> & s, const vector<Point> & t, const vector<Point> & d = vector<Point>())
  {
    int N = (int) s.size();
    vector<Cvector> vs(N);
    bool hasdir = (d.size() > 0);

    for (int i = 0; i < N; ++i)
    {
      if (!hasdir || sign(cross(s[i], t[i], d[i])) >= 0)
        setline(s[i].x, s[i].y, t[i].x, t[i].y, vs[i]);
      else
        setline(t[i].x, t[i].y, s[i].x, s[i].y, vs[i]);
    }

    HalfPlanes plane(100);
    HalfPanelCross(vs, plane.poly.pt);
    return plane;
  }

  /** intersect with a new line, reserver the right part of this line */
  void intersect(const Point & a, const Point & b)
  {
    poly = poly.cut(a, b);
  }

  /** cut the halfplane ensure that Ax + By + C >= 0 */
  void intersect(double A, double B, double C)
  {
    pair<Point, Point> ab = onLine(A, B, C);
    pair<Point, Point> cd = getVerticalEquallySegment(ab.first, ab.second);
    Point a = ab.first, b = ab.second, c = cd.first, d = cd.second;
    double vc = A * c.x + B * c.y + C;
    if (vc > 0)
    {
      if (sign(cross(a, b, c)) > 0)
        swap(a, b);
    }
    else
    {
      if (sign(cross(a, b, d)) > 0)
        swap(a, b);
    }
    poly = poly.cut(a, b);
  }

  /** cut the halfplane by line a-b, and ensure c is remain */
  void intersect(const Point & a, const Point & b, const Point & c)
  {
    if (sign(cross(a, b, c)) <= 0) 
      poly = poly.cut(a, b); 
    else
      poly = poly.cut(b, a);
  }
  
  
};

//////////////////////////////////////////////////////////
// Trangulation
//////////////////////////////////////////////////////////
double triarea(const Point & a, const Point & b, const Point & c)
{
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool inCircle(const Point & a, const Point & b,
  const Point & c, const Point & d)
{
  if (&d == &a || &d == &b || &d == &c)
    return false;

  return (a.x*a.x + a.y*a.y) * triarea(b, c, d) -
    (b.x*b.x + b.y*b.y) * triarea(a, c, d) +
    (c.x*c.x + c.y*c.y) * triarea(a, b, d) -
    (d.x*d.x + d.y*d.y) * triarea(a, b, c) > 0;
}

struct MyTriangle
{
  bool visit;
  Point * ps[3];
  MyTriangle * neighbor[3];
  vector<MyTriangle*> sons;

  MyTriangle(Point * a, Point * b, Point * c)
  {
    ps[0] = a;
    ps[1] = b;
    ps[2] = c;

    neighbor[0] = neighbor[1] = neighbor[2] = NULL;
    sons.clear();
    if (sign(cross(*ps[0], *ps[1], *ps[2])) < 0) swap(ps[1], ps[2]);
    visit = false;
  }

  static inline bool edgeMatch(Point * a, Point * b, Point * c, Point * d)
  { return (a == c && b == d) || (a == d && b == c); }

  static inline void addLink(MyTriangle * ta, MyTriangle * tb, Point * a, Point * b)
  {
    if (ta == NULL || tb == NULL) return;
    int ai = -1; int bi = -1;
    for (int i = 0; i < 3; ++i)
    {
      int ni = i + 1;
      if (ni == 3) ni = 0;
      if (edgeMatch(ta->ps[i], ta->ps[ni], a, b)) ai = i;
      if (edgeMatch(tb->ps[i], tb->ps[ni], a, b)) bi = i;
    }
    if (ai >= 0 && bi >= 0)
    {
      ta->neighbor[ai] = tb;
      tb->neighbor[bi] = ta;
    }
  }

  static inline void reverse(MyTriangle * ta, MyTriangle * tb, Point * i, Point * j)
  {
    if (ta == NULL || tb == NULL) return;
    Point * a = ta->another(i, j);
    Point * b = tb->another(i, j);

    MyTriangle * abj = new MyTriangle(a, b, j);
    MyTriangle * abi = new MyTriangle(a, b, i);
    addLink(abi, abj, a, b);
    addLink(abj, ta->getnear(a, j), a, j);
    addLink(abj, tb->getnear(b, j), b, j);
    addLink(abi, ta->getnear(a, i), a, i);
    addLink(abi, tb->getnear(b, i), b, i);
    ta->sons.push_back(abi);
    ta->sons.push_back(abj);
    tb->sons.push_back(abi);
    tb->sons.push_back(abj);
  }

  bool inTri(Point * p)
  {
    return sign(cross(*ps[0], *ps[1], *p)) >= 0 && 
      sign(cross(*ps[1], *ps[2], *p)) >= 0 &&
      sign(cross(*ps[2], *ps[0], *p)) >= 0;
  }

  bool inside(Point * p)
  {
    return sign(cross(*ps[0], *ps[1], *p)) > 0 && 
      sign(cross(*ps[1], *ps[2], *p)) > 0 &&
      sign(cross(*ps[2], *ps[0], *p)) > 0;
  }

  Point * another(Point * a, Point * b)
  {
    for (int i = 0; i < 3; ++i)
      if (ps[i] != a && ps[i] != b)
        return ps[i];
    
    assert(false);
    return (Point*) NULL;
  }

  pair<Point *, Point *> another(Point * p)
  {
    for (int i = 0; i < 3; ++i) 
      if (ps[i] == p) 
        return make_pair(ps[i + 1 >= 3 ? i + 1 - 3 : i + 1], 
        ps[i + 2 >= 3 ? i + 2 - 3 : i + 2]);

    assert(false);
    return make_pair((Point*)NULL, (Point*)NULL);
  }

  MyTriangle * getnear(Point * a, Point * b)
  {
    for (int i = 0; i < 3; ++i)
      if (edgeMatch(a, b, ps[i], ps[i + 1 >= 3 ? i + 1 - 3 : i + 1]))
        return neighbor[i];

    assert(false);
    return (MyTriangle*)NULL;
  }

  void split3(Point * p)
  {
    sons.push_back(new MyTriangle(ps[0], ps[1], p));
    sons.push_back(new MyTriangle(ps[1], ps[2], p));
    sons.push_back(new MyTriangle(ps[2], ps[0], p));

    addLink(sons[0], sons[1], p, ps[1]);
    addLink(sons[1], sons[2], p, ps[2]);
    addLink(sons[2], sons[0], p, ps[0]);
    addLink(sons[0], neighbor[0], ps[0], ps[1]);
    addLink(sons[1], neighbor[1], ps[1], ps[2]);
    addLink(sons[2], neighbor[2], ps[2], ps[0]);
  }

  void split2(Point * p, Point * a)
  {
    int aid;
    for (int i = 0; i < 3; ++i)
      if (ps[i] == a) 
        aid = i;
    
    int bid = (aid + 1 >= 3 ? aid + 1 - 3 : aid + 1);
    int cid = (aid - 1 < 0 ? aid - 1 + 3 : aid - 1);
    Point * b = ps[bid];
    Point * c = ps[cid];
    
    sons.push_back(new MyTriangle(p, a, b));
    sons.push_back(new MyTriangle(p, a, c));
    
    addLink(sons[0], sons[1], a, p);
    addLink(sons[0], neighbor[aid], a, b);
    addLink(sons[1], neighbor[cid], a, c);  
  }

  static void split4(MyTriangle * ta, MyTriangle * tb, Point * a, Point * b, Point * p)
  {
    if (ta != NULL) ta->split2(p, ta->another(a, b));
    if (tb != NULL) tb->split2(p, tb->another(a, b));
    if (ta != NULL && tb != NULL)
    {
      for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
        {
          addLink(ta->sons[i], tb->sons[j], a, p);
          addLink(ta->sons[i], tb->sons[j], b, p);
        }
    }
  }

  bool isLegal(Point * k, Point * & l, Point * & i, Point * & j)
  {
    pair<Point *, Point *> ab = another(k);
    i = ab.first;
    j = ab.second;
    if (i == NULL || j == NULL) return true;
    if (i->id < 0 && j->id < 0) return true;

    MyTriangle * n = getnear(i, j);

    l = NULL;
    if (n != NULL) 
      l = n->another(i, j);

    if (l == NULL) return true;

    return !inCircle(*i, *j, *k, *l);
  }

  void findEdges(vector<pair<int, int> > & ret)
  {
    if (visit) return;
    visit = true;

    if (sons.size() > 0)
    {
      for (int i = 0; i < (int) sons.size(); ++i)
        sons[i]->findEdges(ret);
      return;
    }

    int a = ps[0]->id;
    int b = ps[1]->id;
    int c = ps[2]->id;
    if (a >= 0 && b >= 0) ret.push_back(make_pair(a, b));
    if (b >= 0 && c >= 0) ret.push_back(make_pair(b, c));
    if (c >= 0 && a >= 0) ret.push_back(make_pair(c, a));
  }

  void output(int depth)
  {
    for (int i = 0; i < depth; ++i)
      cout << " ";
    cout << sons.size() << " " << this << " " << *ps[0] << " " << *ps[1] << " " << *ps[2] << 
      " " << neighbor[0] << " " << neighbor[1] << " " << neighbor[2] << endl;

    if (sons.size() > 0)
    {
      for (int i = 0; i < (int) sons.size(); ++i)
        sons[i]->output(depth + 1);
    }
  }

  friend ostream & operator << (ostream & out, const MyTriangle & t)
  {
    out << *t.ps[0] << " " << *t.ps[1] << " " << *t.ps[2] << " " << t.sons.size();
    return out;
  }

#ifdef OPENCV
  void drawTri()
  {
    //if (visit) return;
    //visit = true;

    if (sons.size() > 0)
    {
      for (int i = 0; i < (int) sons.size(); ++i)
        sons[i]->drawTri();
      return;
    }
    drawTriangle(*ps[0], *ps[1], *ps[2]);
  }
#endif
};


class Triangulation
{
public:
  MyTriangle * root;
  vector<pair<int, int> > edges;

  /**
  void debugShow(Point * p, MyTriangle * tr)
  {
    debug2(*p, *tr);
    root->output(0);
    cout << endl;
    Drawing::clear();
    root->drawTri();
    Drawing::drawPoint(*p, CV_RGB(255, 255, 255));
    Drawing::showDrawing();
  }
  */

  Triangulation(vector<Point> ps)
  {
    double M = 0;
    for (int i = 0; i < (int) ps.size(); ++i)
    {
      M = max(M, fabs(ps[i].x));
      M = max(M, fabs(ps[i].y));
    }
    M = M * 2;

    Point * p1 = new Point(M * 3, 0, -1);
    Point * p2 = new Point(0, M * 3, -2);
    Point * p3 = new Point(-3 * M, -3 * M, -3);
    root = new MyTriangle(p1, p2, p3);

    random_shuffle(ps.begin(), ps.end());

    for (int k = 0; k < (int) ps.size(); ++k)
    {
      Point * p = new Point(ps[k].x, ps[k].y, k);
      MyTriangle * t = inwhich(p);
      //debug2(*pr, *t);
      //root->output(0);

      bool close = false;
      for (int i = 0; i < 3; ++i)
        if (dist(*t->ps[i], *p) < eps)
          close = true;
      if (close) continue;

      if (t->inside(p))
      {
        //debug1("split");
        t->split3(p);
        //debugShow(p, t);

        legalEdge(p, t->sons[0]);
        legalEdge(p, t->sons[1]);
        legalEdge(p, t->sons[2]);
      }
      else
      {
        for (int i = 0; i < 3; ++i)
        {
          Point * a = t->ps[i];
          Point * b = t->ps[i + 1 >= 3 ? i + 1 - 3 : i + 1];
          if (onSeg(*p, *a, *b))
          {
            MyTriangle * t2 = t->getnear(a, b);
            //debug2("begin split4", *p);
            //debug4(*t, *t2, *a, *b);
            
            MyTriangle::split4(t, t2, a, b, p);

            //debug1("split4");
            //debugShow(p, t);

            legalEdge(p, t->sons[0]);
            legalEdge(p, t->sons[1]);
            legalEdge(p, t2->sons[0]);
            legalEdge(p, t2->sons[1]);
            break;
          }
        }
      }

      //debugShow(p, t);
    }

    root->findEdges(edges);
    for (int i = 0; i < (int) edges.size(); ++i)
    {
      edges[i].first = ps[edges[i].first].id;
      edges[i].second = ps[edges[i].second].id;
    }
    
    MyPolygon poly = ConvexHull::convexHull(ps, false);
    for (int i = 0; i < poly.size(); ++i)
    {
      Point a, b;
      poly.getSeg(i, a, b);
      //debug4(a, b, a.id, b.id);
      //Drawing::drawSeg(a, b, CV_RGB(255, 255, 255));
      edges.push_back(make_pair(a.id, b.id));
    }
    
  }

  void legalEdge(Point * p, MyTriangle * tr)
  {
    Point * l = NULL;
    Point * a = NULL, * b = NULL;
    bool isLegal = tr->isLegal(p, l, a, b);

    if (!isLegal)
    {
      pair<Point *, Point *> ij = tr->another(p);
      Point * i = ij.first;
      Point * j = ij.second;
      MyTriangle * tk = tr->getnear(i, j);
      tr->reverse(tr, tk, i, j);

      //debug1("illegal");
      //debugShow(p, tr);

      legalEdge(p, tr->sons[0]);
      legalEdge(p, tr->sons[1]);
    }
  }

  MyTriangle * inwhich(Point * p)
  {
    MyTriangle * now = root;
    while (now->sons.size() > 0)
    {
      for (int i = 0; i < (int) now->sons.size(); ++i)
        if (now->sons[i]->inTri(p))
        {
          now = now->sons[i];
          break;
        }
    }
    return now;
  }
};

///////////////////////////////////////////////
// Vornori
///////////////////////////////////////////////
class Voronoy
{
public:
  vector<Point> ps;
  vector<HalfPlanes> planes;
  vector<vector<Point> > as;
  vector<vector<Point> > bs;
  vector<vector<Point> > cs;
  int N;

  void construct(vector<Point> & points, double maxRange)
  {
    Point a(-maxRange, -maxRange);
    Point b(maxRange, -maxRange);
    Point c(maxRange, maxRange);
    Point d(-maxRange, maxRange);
    construct(points, a, b, c, d);
  }

  void construct(vector<Point> & points, Point & a, Point & b, Point & c, Point & d)
  {
    ps = points;
    N = (int) ps.size();
    as.resize(N);
    bs.resize(N);
    cs.resize(N);
    
    for (int i = 0; i < N; ++i)
    {
      as[i].push_back(a); bs[i].push_back(b); cs[i].push_back(c);
      as[i].push_back(b); bs[i].push_back(c); cs[i].push_back(d);
      as[i].push_back(c); bs[i].push_back(d); cs[i].push_back(a);
      as[i].push_back(d); bs[i].push_back(a); cs[i].push_back(b);
    }

    if (N <= 1) 
    {
      planes.resize(N, HalfPlanes(a, b, c, d));
      return;
    }

    construct();
  }

  void construct()
  {
    for (int i = 0; i < N; ++i) ps[i].id = i;
    Triangulation tr(ps); 

    const vector<pair<int, int> > & segs = tr.edges;

    for (int i = 0; i < (int) segs.size(); ++i)
    {
      int id1 = segs[i].first;
      int id2 = segs[i].second;
      pair<Point, Point> v = getVerticalEquallySegment(ps[id1], ps[id2]);
      as[id1].push_back(v.first); bs[id1].push_back(v.second); cs[id1].push_back(ps[id1]);
      as[id2].push_back(v.first); bs[id2].push_back(v.second); cs[id2].push_back(ps[id2]);
    }

    planes.clear();
    for (int i = 0; i < N; ++i)
      planes.push_back(HalfPlanes::construct(as[i], bs[i], cs[i]));
  }

#ifdef OPENCV
  void drawVor()
  {
    drawPoints(ps);
    for (int i = 0; i < (int) planes.size(); ++i)
      planes[i].poly.drawPolygon();
  }
#endif
};


///////////////////////////////////////////////////
// 立体几何
///////////////////////////////////////////////////
struct Point3D
{
  double x, y, z;
  Point3D() {}
  Point3D(double xx, double yy, double zz) { x = xx; y = yy; z = zz; }
  double len() { return sqrt(x * x + y * y + z * z); }
};

Point3D operator + (const Point3D & a, const Point3D & b)
{ return Point3D(a.x + b.x, a.y + b.y, a.z + b.z); }

Point3D operator - (const Point3D & a, const Point3D & b)
{ return Point3D(a.x - b.x, a.y - b.y, a.z - b.z); }

double dist(const Point3D & a, const Point3D & b)
{ return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z)); }

double dot(const Point3D & a, const Point3D & b)
{ return a.x * b.x + a.y * b.y + a.z * b.z; }

Point3D cross(const Point3D & u, const Point3D & v)
{
  Point3D ret;
  ret.x = u.y * v.z - v.y * u.z;
  ret.y = u.z * v.x - u.x * v.z;
  ret.z = u.x * v.y - u.y * v.x;
  return ret;
}

Point3D planeVector(const Point3D & a, const Point3D & b, const Point3D & c)
{ return cross(a - b, b - c); }

// @warning : directed distance, may be negative
double distToPlane(const Point3D & p, const Point3D & s1, const Point3D & s2, const Point3D & s3)
{
  Point3D plane = planeVector(s1, s2, s3);
  return dot(plane, p - s1) / plane.len();
}

///////////////////////////////////////////////////
// SEARCH
///////////////////////////////////////////////////
class State
{
public:
  static const int DIM = 1;
  vector<double> s;

  State()
  {
    s.resize(DIM);
  }

  State operator + (const State & other)
  { State ret; for (int i = 0; i < DIM; ++i) ret.s[i] = s[i] + other.s[i]; return ret; }

  State operator - (const State & other)
  { State ret; for (int i = 0; i < DIM; ++i) ret.s[i] = s[i] - other.s[i]; return ret; }

  State operator * (double k)
  { State ret; for (int i = 0; i < DIM; ++i) ret.s[i] = s[i] * k; return ret; }

  friend ostream & operator << (ostream & out, const State & state)
  { out << state.s; return out; }
};

/** Find global minimum func state */
class GoldSplitSearch
{
public:
  static State findMinimum(State & begin, State & end, double (*func)(const State & s))
  {
    const double tou = 2.0 / 3;
    State a = begin;
    State b = end;

    for (int k = 0; k < 200; ++k)
    {
      //debug3(a, b, func(a));
      State x1 = a + (b - a) * (1 - tou);
      State x2 = a + (b - a) * tou;
      double f1 = func(x1);
      double f2 = func(x2);
      if (f1 > f2)
        a = x1;
      else 
        b = x2;
    }
    return a;
  }
};

/////////////////////////////////////
// MAIN
/////////////////////////////////////

double R;
int K;
vector<Point> ps;
vector<int> ww;

bool checkAns(Point & p, int ans)
{
  double mindis = 1e10;
  for (int i = 0; i < (int) ps.size(); ++i)
    if (dist(p, ps[i]) < mindis)
      mindis = dist(p, ps[i]);

  int maxans = 0;
  for (int i = 0; i < (int) ps.size(); ++i)
    if (fabs(dist(p, ps[i]) - mindis) < eps)
      maxans = max(maxans, ww[i]);
  return ans == maxans && fabs(p.length() - R) < eps;
}

void init()
{  
  //scanf("%lf %d", &R, &K);
  R = 100;
  K = 100;
  ps.resize(K);
  ww.resize(K);

  for (int i = 0; i < K; ++i)
  {
    //scanf("%lf %lf %d", &ps[i].x, &ps[i].y, &ww[i]);
    while (true)
    {
      ps[i].x = rand() % 200 - 100;
      ps[i].y = rand() % 200 - 100;
      if (ps[i].length() <= R) break;
    }
    ps[i].id = i;
  }
  //cout << "init" << endl;

  //sort(ps.begin(), ps.end(), ConvexHull::cmp);
  //ps.resize(unique(ps.begin(), ps.end(), comPointEqual) - ps.begin());
  vector<bool> valid(K, true);

  for (int i = 0; i < K; ++i)
    for (int j = 0; j < K; ++j)
      if (j != i && dist(ps[i], ps[j]) < 1e-4 && valid[j])
        valid[i] = false;

  vector<Point> nps;
  for (int i = 0; i < K; ++i)
    if (valid[i]) nps.push_back(ps[i]);

  //if (nps.size() < ps.size()) while(1);

  Voronoy * v = new Voronoy();
  v->construct(nps, 200);
#ifdef OPENCV
  Drawing::init(120);
  v->drawVor();
  Drawing::showDrawing();
#endif

  int ans = 0;
  Point ansp(R, 0);
  for (int i = 0; i < (int) nps.size(); ++i)
  {
    int w = ww[nps[i].id];

    if (fabs(dist(Point(0, 0), nps[i]) - R) < eps && w >= ans)
    {
      ans = w;
      ansp = nps[i];
      continue;
    }

    for (int j = 0; j < v->planes[i].poly.size(); ++j)
    {
      Point tmp = v->planes[i].poly[j];
      if (tmp.length() > R - eps && w > ans)
      {
        ans = w;
        vector<Point> inters = interLineCir(Point(0, 0), R, nps[i], tmp);
        if (inters.size() > 0) if (onRay(inters[0], nps[i], tmp))
          ansp = inters[0];
        if (inters.size() > 1) if (onRay(inters[1], nps[i], tmp))
          ansp = inters[1];
      }
    }
  }

  //debug1(ans);
  printf("%.7f %.7f\n", ansp.x, ansp.y);  
}

int main()
{
#ifdef OPENCV
  Drawing::init(3000);
#endif

  init();
  //york();
  //deal();
  
  return 0;
}