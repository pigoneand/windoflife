//BEGIN CUT HERE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <string.h>
#include <sstream>
#include <numeric>
#include <functional>
#include <cmath>
using namespace std;
//END CUT HERE

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

class AllWoundUp
{
public:
    
    double getAngle(Point p, vector<Point>& pts)
    {
        double ans = 0;
        for (int i = 0; i < pts.size(); ++i)
        {
            Point pt1 = pts[i];
            Point pt2 = pts[(i + 1) % pts.size()];
            //debug4(p, pt1, pt2, segDegree(p, pt1, pt2) * sign(cross(p, pt1, pt2)));
            ans += segDegree(p, pt1, pt2) * sign(cross(p, pt1, pt2));
        }
        return ans;
    }
    
    int maxWind(vector <int> x, vector <int> y)
    {
        int N = (int) x.size();
        vector<Point> pts;
        for (int i = 0; i < N; ++i)
            pts.push_back(Point(x[i], y[i]));
        //cout << pts << endl;
        
        vector<Point> pointsOnX;
        Point x1(-10000, 0);
        Point x2(10000, 0);
        for (int i = 0; i < pts.size(); ++i)
        {
            Point pt1 = pts[i];
            Point pt2 = pts[(i + 1) % pts.size()];
            vector<Point> ips = interLine(x1, x2, pt1, pt2);
            for (int j = 0; j < ips.size(); ++j)
                if (onSeg(ips[j], pt1, pt2))
                    pointsOnX.push_back(ips[j]);
        }
        sort(pointsOnX.begin(), pointsOnX.end(), comPointByX);
        
        //cout << pointsOnX << endl;
        double ans = 0;
        for (int i = 0; i + 1 < pointsOnX.size(); ++i)
        {
            if (dist(pointsOnX[i], pointsOnX[i + 1]) < eps) continue;
            Point p = (pointsOnX[i] + pointsOnX[i + 1]) / 2;
            
            bool onEdge = false;
            for (int j = 0; j < pts.size(); ++j)
                if (onSeg(p, pts[j], pts[(j + 1) % pts.size()]))
                    onEdge = true;
            if (onEdge) continue;
            
            double deg = getAngle(p, pts);
            //cout << deg << endl;
            ans = max(ans, deg);
        }
        ans /= (2 * pi);
        return (ans + eps);
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, maxWind(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1,3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, maxWind(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0,1,1,0,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,-1,1,-1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(2, Arg2, maxWind(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {   0,1000, 500,   0,1000, 500, 500,1000,   0, 500,1000, 0}
        ; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] =  {-100,-100, 100,-100,-100, 100, 100,-100,-100, 100,-100,-100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(3, Arg2, maxWind(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    AllWoundUp ___test;
    ___test.run_test(-1);
}
// END CUT HERE
