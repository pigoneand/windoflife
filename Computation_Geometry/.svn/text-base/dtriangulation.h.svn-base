#include <ctime>
#include <cassert>
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
#include <stack>
using namespace std;

/**
* The error tolerance used in global scope.
*/
const double TOLERANCE = 1e-6;

/**
* The max random number.
*/
const double INV_RAND_MAX = 1.0 / (RAND_MAX + 1.0);

/**
* Returns the absolute value of @c val.
*/
template<typename T>
inline T fabs(T val)
{
  if (val < 0)
    return -val;
  else
    return val;
}

/**
* Returns the max value of @c val.
*/
template<typename T>
inline T getMax(T a, T b)
{
  if (a > b)
    return a;
  else
    return b;
}

/**
* Returns the min value of @c val.
*/
template<typename T>
inline T getMin(T a, T b)
{
  if (a > b)
    return b;
  else
    return a;
}

/**
* Returns a random integer between @c start(inclusive) and @c end(exclusive).
*/
inline int random(int start, int end)
{
  assert(end > start);
  return start + rand() % (end - start);
}

/**
* Returns a random double double number between 0(inclusive) and 1(exclusive).
*/
inline double random(void)
{
  return  rand() * INV_RAND_MAX;
}



/////////////////////////////////////////////////
// VECTOR 2D
/////////////////////////////////////////////////
/**
* class for 2d vector.
*/
class Vector2d
{
  // public constructors & destructor
public:
  /**
  * Sets all coordinate values to 0.0 by default.
  */
  Vector2d(void);
  /**
  * Sets x, y coordinate values with @c tx and @c ty.
  */
  Vector2d(double tx, double ty);
  /**
  * Copy constructor.
  */
  Vector2d(const Vector2d& vect);

  // public member functions
public:
  /**
  * Gets the norm of vector.
  */
  double norm(void) const;
  /**
  * Returns the square norm of vector.
  */
  double squareNorm(void) const;
  /**
  * Normalizes self.
  * @return true if it is nonzero vector, or else @return false.
  */
  bool normalize(void);
  /**
  * Operator +.
  */
  Vector2d operator+(const Vector2d& vect) const;
  /**
  * Operator +=.
  */
  Vector2d& operator+=(const Vector2d& vect);
  /**
  * Operator -.
  */
  Vector2d operator-(const Vector2d& vect) const;
  /**
  * Operator -=.
  */
  Vector2d& operator-=(const Vector2d& vect);
  /**
  * Operator *.
  */
  Vector2d operator*(double c) const;
  /**
  * Operator *=.
  */
  Vector2d& operator*=(double c);
  /**
  * Returns the dot product of two <code>Vector2d</code>s.
  */
  double dot(const Vector2d& vect);

  // public data members
public:
  double x;
  double y;
};

Vector2d::Vector2d(void)
  :x(0), y(0)
{
}

Vector2d::Vector2d(double tx, double ty)
  :x(tx), y(ty)
{
}

Vector2d::Vector2d(const Vector2d& vect)
{
  x = vect.x;
  y = vect.y;
}

double Vector2d::norm(void) const
{
  return sqrt(x * x + y * y);
}

double Vector2d::squareNorm(void) const
{
  return x * x + y * y;
}

bool Vector2d::normalize(void)
{
  double len = this->norm();
  if (len == 0.0)
  {
    return false;
  }
  else
  {
    x /= len;
    y /= len;

    return true;
  }
}

double Vector2d::dot(const Vector2d& vect)
{
  return (x * vect.x + y * vect.y);
}

Vector2d Vector2d::operator*(double c) const
{
  return Vector2d(c * x, c * y);
}

Vector2d& Vector2d::operator*=(double c)
{
  x *= c;
  y *= c;

  return *this;
}

Vector2d Vector2d::operator+(const Vector2d& vect) const
{
  return Vector2d(x + vect.x, y + vect.y);
}

Vector2d& Vector2d::operator+=(const Vector2d& vect)
{
  x += vect.x;
  y += vect.y;

  return *this;
}

Vector2d Vector2d::operator-(const Vector2d& vect) const
{
  return Vector2d(x - vect.x, y - vect.y);
}

Vector2d& Vector2d::operator-=(const Vector2d& vect)
{
  x -= vect.x;
  y -= vect.y;

  return *this;
}



////////////////////////////////////////////
// Point 2D
/////////////////////////////////////////////
/**
* class for 2d point.
*/
class Point2d
{
  // public constructors & destructor
public:
  /**
  * Sets all coordinate values to 0.0 by default.
  */
  Point2d(void);
  /**
  * Sets x, y coordinate values with @c tx and @c ty.
  */
  Point2d(double tx, double ty);
  /**
  * Copy constructor.
  */
  Point2d(const Point2d& p);

  // public member functions
public:
  /**
  * Operator + for @c v.
  */
  Point2d operator+(const Vector2d& v) const;
  /**
  * Operator - for @c p.
  */
  Vector2d operator-(const Point2d& p) const;
  /**
  * Operator ==.
  */
  bool operator==(const Point2d& p) const;
  /**
  * Operator <
  */
  bool operator<(const Point2d& p) const;

  // public data members
public:
  double x;
  double y;
  int id;
};


Point2d::Point2d(void)
  : x(0), y(0)
{
}

Point2d::Point2d(double tx, double ty)
  : x(tx), y(ty)
{
}

Point2d::Point2d(const Point2d& p)
{
  x = p.x;
  y = p.y;
  id = p.id;
}

Point2d Point2d::operator+(const Vector2d& v) const
{
  return Point2d(x + v.x, y + v.y);
}

Vector2d Point2d::operator-(const Point2d& p) const
{
  return Vector2d(x - p.x, y - p.y);
}

bool Point2d::operator==(const Point2d& p) const
{
  if (fabs(x - p.x) >= TOLERANCE || fabs(y - p.y) >= TOLERANCE)
    return false;

  return true;
}

bool Point2d::operator<(const Point2d& p) const
{
  if(x < p.x)
  {
    return true;
  }
  else
  {
    if(x > p.x)
      return false;
    else
      return (y < p.y);
  }
}


///////////////////////////////////////////
// LINE 2D
///////////////////////////////////////////

/**
* The class for Line2d.
*/
class Line2d
{
  // public constructors & destructor
public:
  /**
  * Sets all the line parameters to 1.0 by default.
  */
  Line2d(void);
  /**
  * Line passes by two points, start point @c p1 and end point @c p2.
  */
  Line2d(const Point2d& p1, const Point2d& p2);

  // public member functions
public:
  /**
  * Returns the value of a * p.x + b * p.y + c.
  */
  double eval(const Point2d& p) const;
  /**
  * Classifies the point @c p is whether to the left, to the right,
  * or just on the line.
  * @return -1 when is to the left;
  * @return 1 when is to the right;
  * @return 0 when is on the line.
  */
  int classify(const Point2d& p) const;

  // public data members
public:
  /**
  * These line parameters meet the equation ax + by + c = 0;
  */
  double a, b, c;
};



Line2d::Line2d(void)
  :a(1.0), b(1.0), c(1.0)
{
}

Line2d::Line2d(const Point2d& p1, const Point2d& p2)
{
  a = p2.y - p1.y;
  b = p1.x - p2.x;
  c = p1.y * (p2.x - p1.x) - p1.x * (p2.y - p1.y);
}

double Line2d::eval(const Point2d& p) const
{
  return (a * p.x + b * p.y + c);
}

int Line2d::classify(const Point2d& p) const
{
  double d = eval(p);

  if (d < -TOLERANCE)
    return -1;
  else if (d > TOLERANCE)
    return 1;
  else
    return 0;
}


///////////////////////////////////////////////
// EDGE 2D
////////////////////////////////////////////////

/**
* The class for Edge.
*/
class Edge
{
  // public constructors & destructor
public:
  /**
  * Default constructor without data.
  */
  Edge(void);

  // public member functions
public:
  /**
  * Returns the twin edge.
  */
  Edge* twin(void);
  /**
  * Returns the next edge(CCW).
  */
  Edge* next(void);
  /**
  * Returns the previous edge(CCW).
  */
  Edge* prev(void);

  // public member functions
public:
  /**
  * Returns the edge from the destination to the origin of the current edge.
  */
  Edge* sym(void);
  /**
  * Returns the next ccw edge around (from) the origin of the current edge.
  */
  Edge* oNext(void);
  /**
  * Returns the next cw edge around (from) the origin of the current edge.
  */
  Edge* oPrev(void);
  /**
  * Returns the next ccw edge around (into) the destination of
  * the current edge.
  */
  Edge* dNext(void);
  /**
  * Returns the next cw edge around (into) the destination of
  * the current edge.
  */
  Edge* dPrev(void);
  /**
  * Returns the ccw edge around the left face following the current edge.
  */
  Edge* lNext(void);
  /**
  * Returns the ccw edge around the left face before the current edge.
  */
  Edge* lPrev(void);
  /**
  * Returns the edge around the right face ccw following the current edge.
  */
  Edge* rNext(void);
  /**
  * Returns the edge around the right face ccw before the current edge.
  */
  Edge* rPrev(void);
  /**
  * Returns the origin of the current edge.
  */
  Point2d* org(void);
  /**
  * Returns the destination of the current edge.
  */
  Point2d* dest(void);
  /**
  * Gets the pointer to the origin.
  */
  const Point2d& org2d(void) const;
  /**
  * Gets the pointer to the destination.
  */
  const Point2d& dest2d(void) const;
  /**
  * Sets the origin with @c org, and the destination with @c des.
  */
  void endPoints(Point2d* org, Point2d* des);
  /**
  * Returns the address of the starting edge.
  */
  void* qEdge(void);

  // public data members
public:
  int num;
  Edge* eNext;
  Edge* ePrev;
  Point2d* oData;
};



Edge::Edge(void)
  :oData(NULL), eNext(NULL), ePrev(NULL), num(-1)
{
}

Edge* Edge::twin(void)
{
  return (num > 0) ? this - 1 : this + 1;
}

Edge* Edge::next(void)
{
  return eNext;
}

Edge* Edge::prev(void)
{
  return ePrev;
}

Edge* Edge::sym(void)
{
  return (num > 0) ? this - 1 : this + 1;
}

Edge* Edge::oNext(void)
{
  return ePrev->twin();
}

Edge* Edge::oPrev(void)
{
  return twin()->next();
}

Edge* Edge::dNext(void)
{
  return twin()->prev();
}

Edge* Edge::dPrev(void)
{
  return eNext->twin();
}

Edge* Edge::lNext(void)
{
  return eNext;
}

Edge* Edge::lPrev(void)
{
  return ePrev;
}

Edge* Edge::rNext(void)
{
  return twin()->next()->twin();
}

Edge* Edge::rPrev(void)
{
  return twin()->prev()->twin();
}

Point2d* Edge::org(void)
{
  return oData;
}

Point2d* Edge::dest(void)
{
  return twin()->oData;
}

const Point2d& Edge::org2d(void) const
{
  return *oData;
}

const Point2d& Edge::dest2d(void) const
{
  return (num > 0) ? *((this - 1)->oData) : *((this + 1)->oData);
}

void Edge::endPoints(Point2d *org, Point2d *des)
{
  oData = org;
  twin()->oData = des;
}

void* Edge::qEdge(void)
{
  return (void*)(this - num);
}

/////////////////////////////////////
// DCEL
//////////////////////////////////////
/**
* The class for DCEL.
*/
class DCEL
{
  // public constructors & destructor
public:
  /**
  * Default constructor.
  */
  DCEL(void);

  // public data members
public:
  Edge e[2];
  bool visited;
};

DCEL::DCEL(void)
{
  e[0].num = 0;
  e[1].num = 1;

  e[0].ePrev = &(e[1]);
  e[0].eNext = &(e[1]);

  e[1].ePrev = &(e[0]);
  e[1].eNext = &(e[0]);

  visited = false;
}

//////////////////////////////////////////////
// UTILITY
//////////////////////////////////////////////
/**
* Makes a new edge.
*/
Edge* makeEdge(void);
/**
* This operator affects the two edge rings around the origins of a and b,
* and, independently, the two edge rings around the left faces of a and b.
* In each case, (i) if the two rings are distinct, Splice will combine
* them into one; (ii) if the two are the same ring, Splice will break it
* into two separate pieces.
* Thus, Splice can be used both to attach the two edges together, and
* to break them apart. See Guibas and Stolfi (1985) p.96 for more details
* and illustrations.
*/
void splice(Edge* a, Edge* b);
/**
* Deletes the edge @c e.
*/
void deleteEdge(Edge* e);
/**
* Adds a new edge e connecting the destination of a to the
* origin of b, in such a way that all three have the same
* left face after the connection is complete.
* Additionally, the data pointers of the new edge are set.
*/
Edge* connect(Edge* a, Edge* b);
/**
* Essentially turns edge e counterclockwise inside its enclosing
* quadrilateral. The data pointers are modified accordingly.
*/
void swap(Edge* e);
/**
* Returns twice the area of the oriented triangle (a, b, c), i.e., the
* area is positive if the triangle is oriented counterclockwise.
*/
double triarea(const Point2d& a, const Point2d& b, const Point2d& c);
/**
* Returns TRUE if the point d is inside the circle defined by the
* points a, b, c. See Guibas and Stolfi (1985) p.107.
*/
bool inCircle(const Point2d& a, const Point2d& b,
  const Point2d& c, const Point2d& d);
/**
* Returns TRUE if the points a, b, c are in a counterclockwise order.
*/
bool ccw(const Point2d& a, const Point2d& b, const Point2d& c);
/**
* @return true when the point @c x is to the right of the edge @c e.
*/
bool rightOf(const Point2d& x, Edge* e);
/**
* @return true when the point @c x is to the left of the edge @c e.
*/
bool leftOf(const Point2d& x, Edge* e);
/**
* A predicate that determines if the point x is on the edge e.
* The point is considered on if it is in the EPS-neighborhood
* of the edge.
*/
bool onEdge(const Point2d& x, Edge* e);
/**
* test whether the edge e is above edge basel
*/
bool valid(Edge* e, Edge* basel);
/**
* Returns an edge e either x is on e, or e is an edge of a triangle containing x.
*/
Edge* locate(const Point2d &x, Edge* startEdge);
/**
* Tests whether two lines intersected, line1 defined by p1, p2, line2 defined by p3, p4
*/
bool lineIntersected(const Point2d& p1, const Point2d& p2, const Point2d& p3, const Point2d& p4);
/**
* Returns edges which belongs to triangles which intersected by line defined by p1 and p2
*/
void intersectedTris(Point2d& p1, Point2d& p2, vector<Edge *>& edges, Edge* startEdge);
/**
* Tests whether the point x is inside the triangles.
*/
bool testInside(const Point2d& x, Edge* startEdge);
/**
* If point p1 is outside the triangles, search for the nearest intersect edge for p1.
*/
Edge* searchIntersectedEdge(Point2d& p1, Point2d& p2, Edge* startEdge);
/**
* Calculates the parameters of circum circle for a specified triangle.
*/
void circumCircle(const Point2d& p1, const Point2d& p2, const Point2d& p3,
  Point2d* pCenter, double* radius);


Edge* makeEdge(void)
{
  DCEL* dcel = new DCEL();
  return dcel->e;
}

void splice(Edge* a, Edge* b)
{
  a->prev()->eNext = b;
  b->prev()->eNext = a;
  Edge* t1 = a->prev();
  Edge* t2 = b->prev();
  a->ePrev = t2;
  b->ePrev = t1;
}

void deleteEdge(Edge* e)
{
  if (e != NULL)
  {
    splice(e, e->oPrev());
    splice(e->sym(), e->sym()->oPrev());
    delete e->qEdge();
    e = NULL;
  }
}

Edge* connect(Edge* a, Edge* b)
{
  Edge* e = makeEdge();
  splice(e, a->lNext());
  splice(e->sym(), b);
  e->endPoints(a->dest(), b->org());
  return e;
}

void swap(Edge* e)
{
  Edge* a = e->oPrev();
  Edge* b = e->sym()->oPrev();
  splice(e, a);
  splice(e->sym(), b);
  splice(e, a->lNext());
  splice(e->sym(), b->lNext());
  e->endPoints(a->dest(), b->dest());
}

double triarea(const Point2d& a, const Point2d& b, const Point2d& c)
{
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool inCircle(const Point2d& a, const Point2d& b,
  const Point2d& c, const Point2d& d)
{
  if (&d == &a || &d == &b || &d == &c)
    return false;

  return (a.x*a.x + a.y*a.y) * triarea(b, c, d) -
    (b.x*b.x + b.y*b.y) * triarea(a, c, d) +
    (c.x*c.x + c.y*c.y) * triarea(a, b, d) -
    (d.x*d.x + d.y*d.y) * triarea(a, b, c) > 0;
}

bool ccw(const Point2d& a, const Point2d& b, const Point2d& c)
{
  return (triarea(a, b, c) > 0);
}

bool rightOf(const Point2d& x, Edge* e)
{
  return ccw(x, e->dest2d(), e->org2d());
}

bool leftOf(const Point2d& x, Edge* e)
{
  return ccw(x, e->org2d(), e->dest2d());
}

bool onEdge(const Point2d& x, Edge* e)
{
  double t1, t2, t3;
  t1 = (x - e->org2d()).squareNorm();
  t2 = (x - e->dest2d()).squareNorm();

  if (t1 < TOLERANCE || t2 < TOLERANCE)
    return true;

  t3 = (e->org2d() - e->dest2d()).squareNorm();
  if (t1 > t3 || t2 > t3)
    return false;

  Line2d line(e->org2d(), e->dest2d());
  return (fabs(line.eval(x)) < TOLERANCE);
}

bool valid(Edge* e, Edge* basel)
{
  return rightOf(*(e->dest()), basel);
}

bool testInside(const Point2d &x, Edge* startEdge)
{
  Edge* e = startEdge->twin();
  do {
    if (leftOf(x, e))
      return false;
    e = e->lNext();
  } while (e != startEdge->twin());
  return true;
}

Edge* locate(const Point2d& x, Edge* startEdge)

{
  if (!testInside(x, startEdge))
    return NULL;
  Edge* e = startEdge;
  int lastState = 0;

  while (true) 
  {
    if (&x == e->org() || &x == e->dest())
      return e;
    else if (onEdge(x, e))
      return e;
    else if (!rightOf(x, e->oNext()))
    {
      if (lastState != 1)
      {
        lastState = 1;
        startEdge = e;
      }
      e = e->oNext();
      if (e == startEdge)
        return NULL;
    }
    else if (!rightOf(x, e->dPrev()))
    {
      if (lastState != 2)
      {
        lastState = 2;
        startEdge = e;
      }
      e = e->dPrev();
      if (e == startEdge)
        return NULL;
    }
    else
      return e;
  }
}

bool lineIntersected(const Point2d& p1, const Point2d& p2,
  const Point2d& p3, const Point2d& p4)
{
  if((ccw(p3, p4, p1) != ccw(p3, p4, p2)) &&
    ccw(p1, p2, p3) != ccw(p1, p2, p4))
    return true;
  else
    return false;
}

Edge* searchIntersectedEdge(Point2d& p1, Point2d& p2, Edge* startEdge)
{
  Edge *e = startEdge->twin()->lNext();
  bool isIntersect = false;
  while (e != startEdge->twin())
  {
    if (lineIntersected(p1, p2, e->org2d(), e->dest2d()) && leftOf(p1, e))
    {
      isIntersect = true;
      return e->twin();
    }
    e = e->lNext();
  }
  if (lineIntersected(p1, p2, e->org2d(), e->dest2d()) && leftOf(p1, e))
    return e->twin();
  else
    return NULL;
}

void intersectedTris(Point2d& p1, Point2d& p2,
  vector<Edge *>& edges, Edge* startEdge)
{
  // find the first intersected triangle
  Edge *initEdge = locate(p1, startEdge);
  bool outerCase1 = false;
  bool outerCase2 = false;
  if (initEdge == NULL)
  {
    outerCase1 = true;
    initEdge = searchIntersectedEdge(p1, p2, startEdge);  // search outer intersect edge.
    if (initEdge == NULL)  // no intersection.
      return;
  }
  if (locate(p2, startEdge) == NULL)
    outerCase2 = true;
  Edge *iterEdge;
  Edge *firstEdge = initEdge;
  bool isIntersected = false;
  bool isFirst = false;

  // decide whether p1 is on the initEdge
  if(!onEdge(p1, initEdge))
  {
    while(1)
    {
      isIntersected = false;
      iterEdge = initEdge->lNext();
      while(iterEdge != initEdge)
      {
        if (iterEdge == firstEdge || iterEdge == firstEdge->twin())
          return; //break
        if(lineIntersected(p1, p2, iterEdge->org2d(), iterEdge->dest2d()))
        {
          isIntersected = true;
          break;
        }
        iterEdge = iterEdge->lNext();
      }

      if(!isFirst && !isIntersected && !outerCase1)
      {
        if(lineIntersected(p1, p2, iterEdge->org2d(), iterEdge->dest2d()))
        {
          isIntersected = true;
        }
      }

      // p1, p2 is not surrounded by tri define by initEdge
      if(isIntersected)
      {
        if (!isFirst)
          isFirst = true;
        edges.push_back(iterEdge);
        initEdge = iterEdge->twin();
      }
      else
      {
        if(!isFirst)
        {
          edges.push_back(initEdge);
          return;
        }
        else if (isFirst && !outerCase2)
        {
          if (!outerCase2)
            edges.push_back(initEdge);
          return;
        }
        else
        {
          return;
        }
      }
    }
  }
  else
  {
  }
}

void circumCircle(const Point2d& p1, const Point2d& p2, const Point2d& p3,
  Point2d* pCenter, double* radius)
{
  double u1 = 0.5 * (pow(p2.x, 2.0) - pow(p1.x, 2.0) + pow(p2.y, 2.0) - pow(p1.y, 2.0));
  double u2 = 0.5 * (pow(p3.x, 2.0) - pow(p1.x, 2.0) + pow(p3.y, 2.0) - pow(p1.y, 2.0));
  double d11 = p2.x - p1.x;
  double d12 = p2.y - p1.y;
  double d21 = p3.x - p1.x;
  double d22 = p3.y - p1.y;
  pCenter->x = (u1 * d22 - u2 * d12) / (d11 * d22 - d21 * d12);
  pCenter->y = (u2 * d11 - u1 * d21) / (d11 * d22 - d21 * d12);
  *radius = sqrt((pCenter->x - p1.x) * (pCenter->x - p1.x)
    + (pCenter->y - p1.y) * (pCenter->y - p1.y));
}


//////////////////////////////////////////////
// TRIANGULATION
//////////////////////////////////////////////
/**
* Stores le and re which are the ccw CH edge out of the leftmost vertex
* and the cw CH edge out of the rightmost vertex, respectively.
*/
struct MaxEdge
{
  MaxEdge(void)
  {
    le = NULL;
    re = NULL;
  }

  Edge* le;
  Edge* re;
};

/**
* Class for delaunay triangulation.
*/
class DelaunayTriangulation
{
  // public constructors & destructor
public:
  DelaunayTriangulation(void);

  // public member functions
public:
  /**
  * Initials the point data.
  */
  void initial(int* count, Point2d* ps);
  void initial(vector<Point> & ps);

  /**
  * Destroys and resets the edge data.
  */
  void destroy(void);
  /**
  * Does delaunay triangulation operation.
  */
  void doDelaunayTriangulation(void);
  /**
  * Gets the @c pos point.
  */
  Point2d* point(int pos) const;

  /** Gets dt lines */
  vector<pair<Point, Point> > getDrawSegs();

  // private member functions
private:
  /**
  * Collects dcel for deleting.
  */
  void collectDcel(Edge* e, vector<DCEL*> &dcels);
  /**
  * DAC algorithm for delaunay triangulation.
  */
  MaxEdge delaunay(int begin, int end);

  // public data members
public:
  int nPoints;
  Point2d *points;
  MaxEdge maxEdge;
  bool isFinished;
};

vector<pair<Point, Point> > DelaunayTriangulation::getDrawSegs()
{
  vector<pair<Point, Point> > ret;

  Edge * e = this->maxEdge.le;
  DCEL *pDcel;
  Edge *edge;

  std::stack<Edge *>dcelStack;
  dcelStack.push(e);

  while(!dcelStack.empty())
  {
    edge = dcelStack.top();
    pDcel = (DCEL *)(edge->qEdge());
    dcelStack.pop();
    if(!pDcel->visited)
    {
      Point a(edge->org()->x, edge->org()->y, edge->org()->id);
      Point b(edge->dest()->x, edge->dest()->y, edge->dest()->id);
      ret.push_back(make_pair(a, b));
      pDcel->visited = true;
      dcelStack.push(edge->oNext());
      dcelStack.push(edge->oPrev());
      dcelStack.push(edge->dNext());
      dcelStack.push(edge->dPrev());
    }
  }

  e = this->maxEdge.re;
  
  dcelStack.push(e);

  while(!dcelStack.empty())
  {
    edge = dcelStack.top();
    pDcel = (DCEL *)(edge->qEdge());
    dcelStack.pop();
    if(!pDcel->visited)
    {
      Point a(edge->org()->x, edge->org()->y, edge->org()->id);
      Point b(edge->dest()->x, edge->dest()->y, edge->dest()->id);
      ret.push_back(make_pair(a, b));
      pDcel->visited = true;
      dcelStack.push(edge->oNext());
      dcelStack.push(edge->oPrev());
      dcelStack.push(edge->dNext());
      dcelStack.push(edge->dPrev());
    }
  }
  return ret;
}

DelaunayTriangulation::DelaunayTriangulation(void)
{
  isFinished = false;
  nPoints = 0;
  points = NULL;
}

Point2d* DelaunayTriangulation::point(int pos) const
{
  assert(pos >= 0 && pos < nPoints);
  return (points + pos);
}

void DelaunayTriangulation::initial(vector<Point> & ps)
{
  int count = ps.size();
  Point2d * p = new Point2d[count];
  for (int i = 0; i < count; ++i)
  {
    p[i].x = ps[i].x;
    p[i].y = ps[i].y;
    p[i].id = ps[i].id;
  }
  initial(&count, p);
}

void DelaunayTriangulation::initial(int* count, Point2d* ps)
{
  nPoints = *count;
  points = ps;
  std::sort(points, points + nPoints);

  // Deletes the repeated elements.
  int j = 1;
  for (int i = 1; i < nPoints; ++i)
  {
    if (points[i].x != points[i-1].x || points[i].y != points[i-1].y)
    {
      points[j++] = points[i];
    }
  }

  nPoints = *count = j;

  isFinished = false;
}

void DelaunayTriangulation::destroy(void)
{
  if(!maxEdge.le)
  {
    return;
  }

  // collect dcels
  vector<DCEL *>dcels;
  dcels.clear();
  collectDcel(maxEdge.le, dcels);
  collectDcel(maxEdge.re, dcels);

  // delete the DCEL.
  vector<DCEL *>::iterator iter;
  for(iter = dcels.begin(); iter != dcels.end(); iter++)
    delete (*iter);

  maxEdge.le = NULL;
  maxEdge.re = NULL;
  nPoints = 0;
  isFinished = false;
  points = NULL;
}

void DelaunayTriangulation::collectDcel(Edge* e, vector<DCEL*> &dcels)
{
  DCEL *pDcel;
  Edge *edge;

  std::stack<Edge *>dcelStack;
  dcelStack.push(e);
  while(!dcelStack.empty())
  {
    edge = dcelStack.top();
    pDcel = (DCEL *)(edge->qEdge());
    dcelStack.pop();
    if(!pDcel->visited)
    {
      dcels.push_back(pDcel);
      pDcel->visited = true;
      dcelStack.push(edge->oNext());
      dcelStack.push(edge->oPrev());
      dcelStack.push(edge->dNext());
      dcelStack.push(edge->dPrev());
    }
  }

}

void DelaunayTriangulation::doDelaunayTriangulation(void)
{
  if (nPoints >= 2)
  {
    maxEdge = delaunay(0, nPoints - 1);
    isFinished = true;
  }
}

MaxEdge DelaunayTriangulation::delaunay(int begin, int end)
{
  // the number of points
  int size = end - begin + 1;
  // max edge
  MaxEdge ret;

  // delaunay triangulation
  if(size == 2) // only two points
  {
    // let s1, s2 be two sites in sorted order.
    // create an edge a from s1 to s2
    Edge* a = makeEdge();
    a->endPoints(point(begin), point(end));

    ret.le = a;
    ret.re = a->twin();

    return ret;
  }
  else if(size == 3) // only three points
  {
    // let s1, s2, s3 be the three sites, in sorted order,
    // create edges a connecting s1 to s2 and b connecting s2 to s3
    Edge* a = makeEdge();
    Edge* b = makeEdge();
    splice(a->twin(), b);
    a->endPoints(point(begin), point(begin + 1));
    b->endPoints(point(begin + 1), point(end));

    // close the triangle
    Edge* c;
    if(ccw(*point(begin), *point(begin + 1), *point(end)))
    {
      c = connect(b, a);

      ret.le = a;
      ret.re = b->twin();

      return ret;
    }
    else if(ccw(*point(begin), *point(end), *point(begin + 1)))
    {
      c = connect(b, a);

      ret.le = c->twin();
      ret.re = c;

      return ret;
    }
    else  // the three points are collinear
    {
      ret.le = a;
      ret.re = b->twin();
      return ret;
    }
  }
  else // |sites| >= 4
  {
    Edge *ldo, *ldi; // left half result
    Edge *rdo, *rdi; // right half result

    // recursively delaunay triangulation L and R halves
    MaxEdge leftRet = delaunay(begin, begin + (size / 2) - 1);
    MaxEdge rightRet = delaunay(begin + (size / 2), end);
    ldo = leftRet.le;
    ldi = leftRet.re;
    rdi = rightRet.le;
    rdo = rightRet.re;

    // Compute the lower commom tangent of L and R
    while(1)
    {
      if(leftOf(*(rdi->org()), ldi))
      {
        ldi = ldi->lNext();
      }
      else if(rightOf(*(ldi->org()), rdi))
      {
        rdi = rdi->rPrev();
      }
      else
      {
        break;
      }
    }

    // create a first edge basel from rdi.org to ldi.org
    Edge* basel = connect(rdi->twin(), ldi);
    if((ldi->org()) == (ldo->org()))
    {
      ldo = basel->twin();
    }
    if((rdi->org()) == (rdo->org()))
    {
      rdo = basel;
    }

    // merge
    while(1)
    {
      // locate the first L point (lcand.Dest) to be encountered by the rising bubble
      // and delete L edges out of basel.Dest that fail the circle test
      Edge* lcand = basel->twin()->oNext();
      Edge* t;
      if(valid(lcand, basel))
      {
        while(inCircle(*(basel->dest()), *(basel->org()), *(lcand->dest()), 
          *(lcand->oNext()->dest())))
        {
          t = lcand->oNext();
          deleteEdge(lcand);
          lcand = t;
        }
      }

      // symmetrically, locate the first R point to be hit, and delete R edges
      Edge* rcand = basel->oPrev();
      if(valid(rcand, basel))
      {
        while(inCircle(*(basel->dest()), *(basel->org()), *(rcand->dest()), 
          *(rcand->oPrev()->dest())))
        {
          t = rcand->oPrev();
          deleteEdge(rcand);
          rcand = t;
        }
      }

      // if both lcand and rcand are invalid, then basel is the upper common tangent
      if((!valid(lcand, basel)) && (!valid(rcand, basel)))
      {
        break;
      }

      // the next cross edge is to be connected to either lcand.Dest or rcand.Dest
      // if both are valid, then choose the appropriate one using the inCircle test
      if((!valid(lcand, basel)) || (valid(rcand, basel)
        && inCircle(*(lcand->dest()), *(lcand->org()),
        *(rcand->org()), *(rcand->dest()))))
      {
        // add cross edge basel from rcand.Dest to basel.Dest
        basel = connect(rcand, basel->twin());
      }
      else
      {
        // add cross edge basel from basel.org to lcand.Dest
        basel = connect(basel->twin(), lcand->twin());
      }
    }
    ret.le = ldo;
    ret.re = rdo;
    return ret;
  }
}
