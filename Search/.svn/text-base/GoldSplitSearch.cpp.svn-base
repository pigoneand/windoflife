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
#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;
using namespace std;
 
const double eps = 1e-7;
const double pi = acos(-1.0);
const double INF = 1e20;

/** Return a float number's sign */
inline int sign(double d) {
  return d < -eps ? -1 : d > eps;
}

inline double sqr(double x) {
  return x * x;
}

struct Point {
  double x, y;
  Point() { x = 0.0; y = 0.0; }
  Point(double nx, double ny) : x(nx), y(ny) {}
  Point turnLeft() const {
    return Point(-y, x);
  }
  Point turnRight() const {
    return Point(y, -x);
  } 
  Point rotate(double ang) const {
    return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
  }

  inline double length() {
    return sqrt(x * x + y * y);
  }

  void normalize() {
    double r = length();
    if (sign(r) != 0)
      x /= r,y /= r;
  }

  bool operator < (const Point & other) const {
    return y < other.y || y == other.y == 0 && x < other.x;
  }

  bool operator == (const Point & other) const {
    return x == other.x && y == other.y;
  }

  /** Consider the float precision to judge whether two points are the same */
  inline bool equal(const Point & other) const {
    return sign(x - other.x) == 0 && sign(y - other.y) == 0;
  }

  friend ostream & operator << (ostream & out , const Point & point)
  {
    out << "(" << point.x << "," << point.y << ")";
    return out;
  }

};

inline Point operator + (const Point & a, const Point & b) {
  return Point(a.x + b.x, a.y + b.y);
}

inline Point operator - (const Point & a , const Point & b) {
  return Point(a.x - b.x, a.y - b.y);
}

inline Point operator * (const Point & a , double d) {
  return Point(a.x * d, a.y * d);
}

inline Point operator / (const Point & a , double d) {
  if (sign(d) == 0) return Point();
  return Point(a.x / d, a.y / d);
}

inline bool operator == (const Point & a , const Point & b) {
  return a.x == b.x && a.y == b.y;
}

inline bool operator != (const Point & a , const Point & b) {
  return a.x != b.x || a.y != b.y;
}

inline double dist(const Point & a , const Point & b) {
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

inline double sqrdist(const Point & a , const Point & b)
{
  return sqr(a.x - b.x) + sqr(a.y - b.y);
}

/** Cross Product */
inline double operator ^ (const Point & a , const Point & b) {
  return a.x * b.y - a.y * b.x;
}

inline double cross(const Point & p , const Point & a , const Point & b) {
  return (a - p) ^ (b - p);
}

/** Dot product */
inline double operator * (const Point & a , const Point & b) {
  return a.x * b.x + a.y * b.y;
}

inline double dot(const Point & p , const Point & a , const Point & b) {
  return (a - p) * (b - p);
}

/** Whether Point p is on the segment [a, b] or not */
inline bool onSeg(const Point & p , const Point & a , const Point & b) {
  return ( sign(cross(p, a, b)) == 0 && sign(dot(p, a, b)) <= 0) ;
}

/** Whether Point p is on the ray from a to b */
inline bool onRay(const Point & p , const Point & a , const Point & b) {
  return ( sign(cross(p, a, b)) == 0 && sign(dot(a, p, b)) >= 0) ;
}

/** Whether Point p is on the straight line a-b or not */
inline bool onLine(const Point & p , const Point & a , const Point & b) {
  return sign(cross(p,a,b))==0;
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

/**
 * Given two points just on the circle, return their shortest length along the circle 
 */
double distOnCircle(const Point & a, const Point & b, const Point & o, double r)
{
	double costheta = (a - o) * (b - o) / r / r;
	double theta = acos(costheta);
	return r * theta;
}

/////////////////////////////////////

class State
{
public:
	double x, y, z;

	State operator + (const State & other)
	{ State ret; ret.x = x + other.x;	ret.y = y + other.y;	ret.z = z + other.z; return ret; }

	State operator - (const State & other)
	{ State ret; ret.x = x - other.x; ret.y = y - other.y; ret.z = z - other.z; return ret; }

	State operator * (double k)
	{ State ret; ret.x = x * k; ret.y = y * k; ret.z = z * k; return ret; }

	friend ostream & operator << (ostream & out, const State & state)
	{ out << state.x << " " << state.y << " " << state.z; return out; }
};

/** Find global minimum func state */
class GoldSplitSearch
{
public:
	static State findMinimum(State & begin, State & end, double (*func)(const State & s))
	{
		const double tou = (sqrt(5.0) - 1) / 2;
		State a = begin;
		State b = end;

		for (int k = 0; k < 200; ++k)
		{
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

double dist(const State & a, const State & b)
{ return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z)); }

double distSphere(const State & a, const State & b, const State & center, double R)
{ 
	double costheta = (a.x - center.x) * (b.x - center.x) + 
		(a.y - center.y) * (b.y - center.y) + (a.z - center.z) * (b.z - center.z);
	costheta /= R;
	costheta /= R;
	double theta = acos(costheta);
	return R * theta;
}

double R;
State A, B, C;

double func1(const State & s)
{ return dist(s, C); }

double func2(const State & s)
{ return fabs(dist(s, C) - R); }

void york()
{
	State cloest = GoldSplitSearch::findMinimum(A, B, func1);
	//debug4(cloest.x, cloest.y, cloest.z, func1(cloest));

	if (dist(cloest, C) >= R) 
	{
		double ans = dist(A, B);
		printf("%.2f\n", ans);
		return;
	}
	else
	{
		Point O(dist(cloest, C), 0);
		Point A2(0, dist(A, cloest));
		Point B2(0, -dist(B, cloest));

		vector<Point> t1s = tangentCirPoint(O, R, A2);
		vector<Point> t2s = tangentCirPoint(O, R, B2);
		double ans = 1e20;
		for (int i = 0; i < t1s.size(); ++i)
			for (int j = 0; j < t2s.size(); ++j)
				ans = min(ans, dist(A2, t1s[i]) + dist(t2s[j], B2) + distOnCircle(t1s[i], t2s[j], O, R));
		printf("%.2f\n", ans);
		return;
	}
}

void init()
{
	cin >> A.x >> A.y >> A.z;
	cin >> B.x >> B.y >> B.z;
	cin >> C.x >> C.y >> C.z;
	cin >> R;
}

int main()
{
	init();
	york();

	return 0;
}