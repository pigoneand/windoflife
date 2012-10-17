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
#include <cassert>
#include <fstream>
#include <sstream>
#include <bitset>
#include <stack>
#include <list>
using namespace std;
#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

template <class T>
ostream & operator << (ostream & out, const vector<T> & t)
{	out << t.size() << " {";	for (int i = 0; i < t.size(); ++i) 		out << t[i] << " ";	out << "}";	return out;}

template <class T>
ostream & operator << (ostream & out, const set<T> & t)
{	out << "{";	for (set<T>::iterator itr = t.begin(); itr != t.end(); ++itr)		out << *itr << " ";	out << "}";	return out;}

/////////////////////////
// template finished
/////////////////////////
class State
{
public:
	double x, y;

	State operator + (const State & other)
	{ State ret; ret.x = x + other.x;	ret.y = y + other.y; return ret; }

	State operator - (const State & other)
	{ State ret; ret.x = x - other.x; ret.y = y - other.y; return ret; }

	State operator * (double k)
	{ State ret; ret.x = x * k; ret.y = y * k; return ret; }

	friend ostream & operator << (ostream & out, const State & state)
	{ out << state.x << " " << state.y; return out; }

	State()
	{
	}

	State(double len)
	{
		double theda = rand() % 65537;
		x = cos(theda) * len;
		y = sin(theda) * len;
	}
};

/** Find global minimum func state */
class FireSearch
{
public:
	static State findMinimum(State & begin, double (*func)(const State & s), double initlen)
	{
		double nowbest = func(begin);
		double len = initlen;
		State now = begin;
		for (int iter = 0; iter < 200; ++iter)
		{
			for (int i = 0; i < 200; ++i)
			{
				State news = now + State(len);
				double nowf = func(news);
				if (nowf < nowbest)
				{
					nowbest = nowf;
					now = news;
				}
			}
			len *= 0.618;
		}
		return now;
	}
};

double X1, Y1, X2, Y2, X3, Y3;
inline double sqr(double x) { return x * x; }
double dist(double xx1, double yy1, double xx2, double yy2)
{ return sqrt(sqr(xx1 - xx2) + sqr(yy1 - yy2)); }

double func1(const State & s)
{ return dist(s.x, s.y, X1, Y1) + dist(s.x, s.y, X2, Y2) + dist(s.x, s.y, X3, Y3); }

void init()
{
	cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3;
	State init;
	init.x = (X1 + X2 + X3) / 3;
	init.y = (Y1 + Y2 + Y3) / 3;

	State ans = FireSearch::findMinimum(init, func1, 10000.0);
	printf("%.10f %.10f\n", ans.x, ans.y);
}

void york()
{
}

int main()
{
	init();
	york();
	return 0;
}