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

class CirclesOfDestruction
{
public:
    
    double getMinDis(Point o, Point a, Point b, vector<Point>& pts)
    {
        double minY = min(a.y, b.y);
        double maxY = max(a.y, b.y);
        
        for (int i = 0; i < pts.size(); ++i)
        {
            if (fabs(pts[i].y - o.y) < eps)
            {
                if (pts[i].x > o.x) return INF;
                else continue;
            }
            
            pair<Point, Point> vseg = getVerticalEquallySegment(o, pts[i]);
            vector<Point> interPoint = interLine(vseg.first, vseg.second, a, b);
            if (pts[i].y > o.y)
                maxY = min(maxY, interPoint[0].y);
            else
                minY = max(minY, interPoint[0].y);
        }
        
        if (minY > maxY + 2 * eps) return INF;
        if (o.y >= minY && o.y <= maxY) return dist(o, Point(a.x, o.y));
        return min(dist(o, Point(a.x, minY)), dist(o, Point(a.x, maxY)));
    }
    
    Point rotateAcc(Point a, Point tar)
    {
        Point delta = tar - a;
        return Point(delta.y, -delta.x);
    }
    
    void rotate(Point& o, Point& a, Point& b, vector<Point>& pts)
    {
        Point c = Point(0, b.y);
        Point nc = rotateAcc(a, c);
        o = rotateAcc(a, o);
        Point nb = rotateAcc(a, b);
        for (int i = 0; i < pts.size(); ++i)
            pts[i] = rotateAcc(a, pts[i]);

        a = nb;
        b = nc;
        return;
    }
    
    double exitTime(int xSize, int ySize, int px, int py, vector <int> x, vector <int> y)
    {
        Point a(xSize, 0);
        Point b(xSize, ySize);
        Point o(px, py);
        vector<Point> pts;
        int N = (int) x.size();
        for (int i = 0; i < N; ++i) pts.push_back(Point(x[i], y[i]));
        
        double ans = INF;
        
        ans = min(ans, getMinDis(o, a, b, pts));
        rotate(o, a, b, pts);
        ans = min(ans, getMinDis(o, a, b, pts));
        rotate(o, a, b, pts);
        ans = min(ans, getMinDis(o, a, b, pts));
        rotate(o, a, b, pts);
        ans = min(ans, getMinDis(o, a, b, pts));
        
        if (ans == INF) return -1; else return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 5; int Arg3 = 5; int Arr4[] = {1, 5, 5}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {5, 1, 9}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); double Arg6 = 5.0; verify_case(0, Arg6, exitTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 101; int Arg1 = 10; int Arg2 = 5; int Arg3 = 5; int Arr4[] = {1, 5, 5, 9}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {5, 1, 9, 5}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); double Arg6 = -1.0; verify_case(1, Arg6, exitTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 3; int Arg2 = 0; int Arg3 = 2; int Arr4[] = {0, 0, 1, 1, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1, 3, 1, 2, 3}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); double Arg6 = 0.0; verify_case(2, Arg6, exitTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 5; int Arg1 = 6; int Arg2 = 4; int Arg3 = 2; int Arr4[] = {0, 4, 5}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {6, 0, 2}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); double Arg6 = 4.0; verify_case(3, Arg6, exitTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 50; int Arg3 = 50; int Arr4[] = {10, 30, 70, 90, 10, 30, 70, 90}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {90, 70, 30, 10, 10, 30, 70, 90}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); double Arg6 = -1.0; verify_case(4, Arg6, exitTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_5() { int Arg0 = 1000; int Arg1 = 1000; int Arg2 = 800; int Arg3 = 800; int Arr4[] = {1000, 800, 600}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {800, 1000, 750}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); double Arg6 = 805.4744331758768; verify_case(5, Arg6, exitTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    CirclesOfDestruction ___test;
    ___test.run_test(-1);
}
// END CUT HERE
