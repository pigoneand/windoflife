#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps=1e-8;
const double PI=acos(-1.0);

inline int dcmp(double x)
{ return x<eps ? -1 : x>eps; }

inline double sqr(double x)
{ return x*x; }

struct Point
{
	double x,y;
	Point(){}
	Point (double nx,double ny) {x=nx;y=ny;}
};

inline Point operator+(const Point &a,const Point &b)
{ return Point(a.x+b.x,a.y+b.y); }

inline Point operator-(const Point &a,const Point &b)
{ return Point(a.x-b.x,a.y-b.y); }

inline double det(const Point &a,const Point &b)
{ return a.x*b.y-a.y*b.x; }

inline double det(const Point &p,const Point &a,const Point &b)
{ return det(a-p,b-p); }

inline bool smaller(const Point &a,const Point &b)
{ return dcmp(a.y-b.y)<0 || dcmp(a.y-b.y)==0 && dcmp(a.x-b.x)<0 ; }

inline double Distant(const Point &a,const Point &b)
{ return sqrt( sqr(a.x-b.x) + sqr(a.y-b.y) ); }

inline void swap( Point &a, Point &b)
{ Point temp;temp=a;a=b;b=temp; }

Point ori;
inline bool com(const Point &a,const Point &b)
{
	double r=det(ori,a,b);
	return dcmp(r)>0 || dcmp(r)==0 && dcmp(Distant(ori,a)-Distant(ori,b))<0;
}

int N;
Point pt[40000];
Point npt[40000];
int Ns;
double ans;

void convexHull(Point *p,Point *poly)
{
	int i,j,k;
	Ns=0;

	int ms=0;
	for (i=1;i<N;++i) if (smaller(p[i],p[ms])==true) ms=i;
	if (ms) swap(p[0],p[ms]);

	ori=p[0];
	sort(p+1,p+N,com);

	for (i=0;i<N;++i)
	{
		if (Ns>2)
		{
			while (Ns>2 && dcmp( det(poly[Ns-2],poly[Ns-1],p[i]) )<=0) Ns--;
		}
		poly[Ns++]=p[i];
	}           
}

void solve()
{
	int i,j;
	double t,x;
	for (ans=i=j=0;i<m;++i)
	{
		for (t=dist(ch[i],ch[j]);;)
		{
			x=dist(ch[i],ch[j+1]);
			if (x>t)
			{
				t=x;
				j=(j+1)%m;
			}
			else break;
		}
		ans=max(ans,t);
	}
	printf("%.2lf\n",ans);
}