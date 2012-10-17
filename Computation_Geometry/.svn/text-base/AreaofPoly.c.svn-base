#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
 
const int MaxN=10000;
const double eps=1e-8;
const double PI=acos(-1.0);
 
inline int dcmp(double x)
{ return x<-eps ? -1 : x>eps; }
 
inline double sqr(double x)
{ return x*x; }
 
struct Point
{
	double x,y;
	Point(){}
	Point(double nx,double ny) {x=nx;y=ny;}

	Point turnLeft() const 
	{ return Point(-y, x); }

    Point turnRight() const 
	{ return Point(y, -x); } 

    Point rotate(double ang) const 
	{ return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang)); }
};

inline double Distant(const Point &a,const Point &b)
{ return sqrt( sqr(a.x-b.x) + sqr(a.y-b.y) ); }

inline Point operator+(const Point &a,const Point &b)
{ return Point(a.x+b.x,a.y+b.y); }
 
inline Point operator-(const Point &a,const Point &b)
{ return Point(a.x-b.x,a.y-b.y); }
 
inline Point operator*(const Point &a,double d)
{ return Point(a.x*d,a.y*d); }
 
inline Point operator/(const Point &a,double d)
{ return Point(a.x/d,a.y/d); }

inline Point operator*(double d,const Point &a)
{ return Point(a.x*d,a.y*d); }
 
inline Point operator/(double d,const Point &a)
{ return Point(a.x/d,a.y/d); }

 
inline double det(const Point &a,const Point &b)
{ return a.x*b.y-a.y*b.x; }
 
inline double det(const Point &p,const Point &a,const Point &b)
{ return det(a-p,b-p); }
 
inline double dot(const Point &a,const Point &b)
{ return a.x*b.x+a.y*b.y; }
 
inline double dot(const Point &p,const Point &a,const Point &b)
{ return dot(a-p,b-p); }
 
inline bool onSeg(const Point &p,const Point &a,const Point &b)
{ return dcmp(det(p,a,b))==0 && dcmp(dot(p,a,b)<=0); }
 
bool Intersection(const Point &a,const Point &b,const Point &c,const Point &d,Point &p)
{
	double u=det(a,c,b);
	double v=det(a,b,d);
	if (dcmp(u+v)==0) return false;
	p=(d*u+c*v)/(u+v);
	return true;
}
 
Point pn[MaxN];
 
struct Polygon
{
	Point pt[MaxN];
	int n;
 
	//判断一个点是否在多边形内部，边上，或者外部
	//1 内部 -1 外部 0 边上
	int Inside(const Point &x)
	{
		pt[n]=pt[0];
		int i;
		//首先判断是否在边上
		for (i=0;i<n;++i) if (onSeg(x,pt[i],pt[i+1])) return 0;
		
		double ans=0;
		for (i=0;i<n;++i) 
			ans+=atan2(det(x,pt[i],pt[i+1]),dot(x,pt[i],pt[i+1]));
 
		return dcmp(ans+PI)<0 || dcmp(ans-PI)>0 ? 1 : -1;
    }
 
	//返回一个多边形的面积
	double Area()
	{
		pt[n]=pt[0];
		int i;
		double ans=0;
 
		for (i=0;i<n;++i) ans+=det(pt[i],pt[i+1]);
		return fabs(ans/2);
	}
 
	void Cut(const Point &a,const Point &b)
	{
		pt[n] = pt[0];
		int i;
        int nl = 0;
        for (i = 0; i < n; i++) 
		{
			//如果点在ab一侧，那么包含
            if (dcmp(det(a, b, pt[i])) <= 0) pn[nl++] = pt[i];
			//如果线段的两端在两侧，那么切割中间点
            if (dcmp(det(a, b, pt[i])) * dcmp(det(a, b, pt[i + 1])) < 0) 
			{
                Intersection(pt[i], pt[i + 1], a, b, pn[nl]);
                nl++;
            }
        }
        n = nl;
        for (i = 0; i < n; i++) pt[i] = pn[i];
	}
};
 
Polygon p1,p2,p3;
double a1,a2,a3;
 
void init()
{
	int i,j,k;
	for (i=0;i<p1.n;++i) cin>>p1.pt[i].x>>p1.pt[i].y;
 
	scanf("%d",&p2.n);
	for (i=0;i<p2.n;++i) cin>>p2.pt[i].x>>p2.pt[i].y;
 
	a1=p1.Area();
	a2=p2.Area();
 
	//切割每一条边
	for (i=0;i<p2.n;++i)
	{
		p1.Cut(p2.pt[i],p2.pt[i+1]);
	}
	a3=p1.Area();
 
	double ans;
	ans=a1+a2-a3-a3;
 
	char temp[100];
	sprintf(temp,"%.2lf",ans);
	k=8-strlen(temp);
 
	for (i=0;i<k;++i) cout<<" ";
	cout<<temp;
}
 
 
int main()
{
	int i;
	while (true)
	{
		scanf("%d",&i);
		if (i==0) break;
		p1.n=i;
		init();
	}
	cout<<endl;
 
	return 0;
}