#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
using namespace std;

long long gcd(long long a, long long b)
{  if (a % b == 0) return b;  else return gcd(b, a % b); }

inline int getsign(long long x) { return x >= 0 ? 1 : -1; }

// Ensure mother > 0
class Fraction
{
public:
	long long son;
	long long mother;

	void init(long long s, long long m) { son = s;	mother = m; reduction(); }
	Fraction(long long s, long long m) { init(s, m); }
	Fraction() { init(0, 1); }

	/** Format: intpart (space) son/mother */
	Fraction(const string & line)
	{
		int t, s, m;
		if (line.find(' ') == string::npos)
		{
			if (line.find('/') != string::npos)
			{		
				sscanf(line.data(), "%d/%d", &s, &m);
				init(s, m);
				return;
			}
			else
			{
				sscanf(line.data(), "%d", &s);
				init(s, 1);
				return;
			}
		}
		else
		{
			sscanf(line.data(), "%d %d/%d", &t, &s, &m);
			init(getsign(t) * (long long)s + (long long) t * (long long) m, m);
			return;
		}
	}

	void reduction()
	{
		if (mother < 0)
		{
			son = -son;
			mother = -mother;
		}

		long long factor = gcd(abs(son), mother);
		son /= factor;
		mother /= factor;
	}

	Fraction operator + (const Fraction & other)
	{
		Fraction ret;
		ret.son = son * other.mother + other.son * mother;
		ret.mother = mother * other.mother;
		ret.reduction();
		return ret;
	}

	Fraction operator - (const Fraction & other)
	{
		Fraction ret;
		ret.son = son * other.mother - other.son * mother;
		ret.mother = mother * other.mother;
		ret.reduction();
		return ret;
	}

	Fraction operator * (const Fraction & other)
	{
		Fraction ret;
		ret.son = son * other.son;
		ret.mother = mother * other.mother;
		ret.reduction();
		return ret;
	}

	Fraction operator / (const Fraction & other)
	{
		Fraction ret;
		ret.son = son * other.mother;
		ret.mother = mother * other.son;
		ret.reduction();
		return ret;
	}

	bool operator < (const Fraction & other) const
	{ return son * other.mother < mother * other.son; }

	bool operator > (const Fraction & other) const
	{ return son * other.mother > mother * other.son; }

	bool operator == (const Fraction & other) const
	{ return son == other.son && mother == other.mother; }

	friend ostream & operator << (ostream & out, const Fraction & other)
	{
		out << other.son << "/" << other.mother;
		return out;
	}

	string toIntPartString()
	{
		ostringstream ostr;
		if (son == 0) return "0";
		if (mother == 1) 	{ ostr << son;	return ostr.str(); }
		if (abs(son) < mother) 	{	ostr << son << "/" << mother;	return ostr.str(); }
		ostr << son / mother << " " << abs(son) % mother << "/" << mother;
		return ostr.str();
	}
};

void init()
{
	string line1, line2, line3;
	getline(cin, line1);
	getline(cin, line2);
	getline(cin, line3);

	Fraction f1(line1);
	Fraction f2(line3);
	Fraction ans;

	if (line2 == "+") ans = f1 + f2;
	if (line2 == "-") ans = f1 - f2;
	if (line2 == "*") ans = f1 * f2;
	if (line2 == "/") ans = f1 / f2;

	//cout << f1 << " " << f2 << endl;
	//cout << ans << endl;
	cout << ans.toIntPartString() << endl;
}

void york()
{
}

int main()
{
	/**
	Fraction f1(1, 2);
	Fraction f2(1, 3);
	Fraction f3(1, 6);
	cout << f1 << endl;
	cout << f2 << endl;
	cout << f3 << endl;

	cout << "+ " << f1 + f2 + f3 << endl;
	cout << "- " << f1 - f2 - f3 << endl;
	cout << "* " << f1 * f2 * f3 << endl;
	cout << "/ " << f1 / f2 << endl;
	*/

	init();
	york();
	return 0;
}
