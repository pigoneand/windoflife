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
#include <sstream>
using namespace std;

vector<string> split(const string & src, vector<char> & delimit)
{
	vector<string> ret;
	int last = 0;
	for (int i = 0; i < src.length(); ++i)
	{
		bool isDelimit = false;
		for (int j = 0; j < delimit.size(); ++j)
			if (src[i] == delimit[j])
				isDelimit = true;
		if (isDelimit)
		{
			ret.push_back(src.substr(last, i - last));
			last = i + 1;
		}
	}
	ret.push_back(src.substr(last, src.length() - last));
	return ret;
}

vector<string> split(const string & src, const string & delimit,
		const string &  null_subst = "")
{
	if(src.empty() || delimit.empty())
		return vector<string>();

	vector<string> v;
	size_t deli_len = delimit.size();
	long index = string::npos, last_search_position = 0;
	while((index = src.find(delimit, last_search_position)) != string::npos)
	{
		if(index == last_search_position)
			v.push_back(null_subst);
		else
			v.push_back(src.substr(last_search_position ,
						index - last_search_position));
		last_search_position = index + deli_len;
	}
	string last_one = src.substr(last_search_position);
	v.push_back(last_one.empty() ? null_subst : last_one);
	return v;
}

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
		Fraction(long long x) { init(x, 1); }
		Fraction(int x) { init(x, 1); }

		Fraction & operator = (long long x) { init(x, 1); return *this;}
		Fraction & operator = (int x) { init(x, 1); return *this; }

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

		Fraction operator - () const
		{
			Fraction ret;
			ret.son = -son;
			ret.mother = mother;
			return ret;
		}

		bool operator < (const Fraction & other) const
		{ return son * other.mother < mother * other.son; }

		bool operator > (const Fraction & other) const
		{ return son * other.mother > mother * other.son; }

		bool operator == (const Fraction & other) const
		{ return son == other.son && mother == other.mother; }

		bool operator != (const Fraction & other) const
		{ return son != other.son || mother != other.mother; }

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

struct OneItem
{
	map<char, int> powers;
	Fraction coff;
	int totalpower;

	OneItem()
	{
		totalpower = 0;
		coff = 0;
		powers.clear();
	}

	OneItem(Fraction x)
	{
		totalpower = 0;
		coff = x;
		powers.clear();
	}

	OneItem(string & str)
	{
		coff = 1;
		totalpower = 0;
		if (str[0] == '-') { coff = -1; str = str.substr(1); }
		if (str[0] == '+') { coff = 1; str = str.substr(1); }
		vector<string> s = split(str, "*");
		for (int i = 0; i < s.size(); ++i)
		{
			int co;
			if (sscanf(s[i].data(), "%d", &co) == 1)
				coff = coff * co;
			else
			{
				char c; int p = 1;
				sscanf(s[i].data(), "%c^%d", &c, &p);
				if (p > 0)
				{
					powers[c] += p;
					totalpower += p;
				}
			}
		}
		refine();
	}

	OneItem operator * (OneItem & other)
	{
		OneItem ret = (*this);
		ret.coff = ret.coff * other.coff;
		for (map<char, int>::iterator itr = other.powers.begin(); itr != other.powers.end(); ++itr)
			ret.powers[itr->first] += itr->second, ret.totalpower += itr->second;
		return ret;
	}

	OneItem operator - () const
	{
		OneItem ret = *this;
		ret.coff = -ret.coff;
		return ret;
	}

	bool match(OneItem & other)
	{
		if (totalpower != other.totalpower) return false;
		for (map<char, int>::iterator itr = other.powers.begin(); itr != other.powers.end(); ++itr)
		{
			if (powers.find(itr->first) == powers.end()) return false;
			if (powers[itr->first] != itr->second) return false;
		}
		return true;
	}

	void refine()
	{
		if (coff == 0)
		{
			powers.clear();
			totalpower = 0;
		}
	}

	bool operator < (const OneItem & other) const
	{
		if (totalpower > other.totalpower) return true;
		if (totalpower < other.totalpower) return false;
		for (char c = 'a'; c <= 'z'; ++c)
		{
			map<char, int>::const_iterator itr1 = powers.find(c);
			map<char, int>::const_iterator itr2 = other.powers.find(c);
			if (itr1 == powers.end() && itr2 == other.powers.end()) continue;
			if (itr1 != powers.end() && itr2 == other.powers.end()) return true;
			if (itr1 == powers.end() && itr2 != other.powers.end()) return false;
			if (itr1->second > itr2->second) return true;
			if (itr1->second < itr2->second) return false;
		}
		return false;
	}

	friend ostream & operator << (ostream & out, const OneItem & term)
	{
		if (term.coff == 0) { out << 0; return out; }
		bool leadCoff = false;
		if (term.coff > 0)
		{
			out << "+ ";
			if (term.coff != 1 || term.totalpower == 0) {out << term.coff; leadCoff = true; }
		}
		else
		{
			out << "- ";
			if (term.coff != -1 || term.totalpower == 0) {out << -term.coff; leadCoff = true; }
		}

		for (map<char, int>::const_iterator itr = term.powers.begin(); itr != term.powers.end(); ++itr)
		{
			if (itr != term.powers.begin() || leadCoff) out << "*";
			out << itr->first;
			if (itr->second > 1)
				out << "^" << itr->second;
		}
		return out;
	}
};

struct Polynomial
{
	vector<OneItem> terms;

	Polynomial operator * (Polynomial & other)
	{
		Polynomial ret;
		for (int i = 0; i < terms.size(); ++i)
			for (int j = 0; j < other.terms.size(); ++j)
				ret.terms.push_back(terms[i] * other.terms[j]);
		ret.refine();
		return ret;
	}

	Polynomial operator + (Polynomial & other)
	{
		Polynomial ret = (*this);
		for (int j = 0; j < other.terms.size(); ++j)
			ret.terms.push_back(other.terms[j]);
		ret.refine();
		return ret;
	}

	Polynomial operator - (Polynomial & other)
	{
		Polynomial ret = (*this);
		for (int j = 0; j < other.terms.size(); ++j)
			ret.terms.push_back(-(other.terms[j]));
		ret.refine();
		return ret;
	}

	Polynomial operator / (Fraction & x)
	{
		Polynomial ret = (*this);
		for (int j = 0; j < ret.terms.size(); ++j)
			ret.terms[j].coff = ret.terms[j].coff / x;
		ret.refine();
		return ret;
	}

	void refine()
	{
		for (int i = 0; i < terms.size(); ++i)
			terms[i].refine();

		vector<bool> valid(terms.size(), true);
		for (int i = 0; i < terms.size(); ++i)
			if (valid[i])
				for (int j = i + 1; j < terms.size(); ++j)
					if (terms[i].match(terms[j]) && valid[j])
						terms[i].coff = terms[i].coff + terms[j].coff, valid[j] = false;

		vector<OneItem> newterm;
		for (int i = 0; i < terms.size(); ++i)
			if (valid[i] && terms[i].coff != 0)
				newterm.push_back(terms[i]);
		sort(newterm.begin(), newterm.end());
		terms = newterm;
	}

	friend ostream & operator << (ostream & out, const Polynomial & poly)
	{
		if (poly.terms.size() == 0) { out << 0; return out; }
		for (int i = 0; i < poly.terms.size(); ++i)
			out << poly.terms[i] << " ";
		return out;
	}

	Polynomial(const string & str)
	{
		string now = "";
		for (int i = 0; i < str.length(); ++i)
		{
			if (str[i] == ' ') continue;
			if (str[i] == '+' || str[i] == '-')
			{
				if (now.length() > 0)
					terms.push_back(OneItem(now));
				now = string(1, str[i]);
			}
			else now.append(1, str[i]);
		}
		if (now.length() > 0)
			terms.push_back(OneItem(now));
	}

	Polynomial()
	{
	}
};

Polynomial xplus1[40];
Polynomial xp[40];
Polynomial ans[40];
void init()
{
	Polynomial one("1");

	xplus1[1] = Polynomial("x+1");
	xp[1] = Polynomial("x");
	for (int i = 2; i <= 31; ++i)
	{
		xplus1[i] = xplus1[i - 1] * xplus1[1];
		xp[i] = xp[i - 1] * xp[1];
	}

	ans[0] = Polynomial("x");
	for (int i = 1; i <= 30; ++i)
	{
		Polynomial now = xplus1[i + 1] - one;
		Polynomial expand = xplus1[i + 1] - xp[i + 1];

		for (int j = 1; j < expand.terms.size(); ++j)
		{
			int zhishu = expand.terms[j].powers['x'];
			Fraction coff = expand.terms[j].coff;
			Polynomial t;
			t.terms.push_back(coff);
			t = t * ans[zhishu];
			now = now - t;
		}

		Fraction coff = expand.terms[0].coff;
		now = now / coff;

		ans[i] = now;
	}

	int K;
	cin >> K;
	Fraction anscoff[40];
	for (int i = 0; i < 40; ++i)
		anscoff[i] = 0;
	for (int i = 0; i < ans[K].terms.size(); ++i)
	{
		int zhishu = ans[K].terms[i].powers['x'];
		anscoff[zhishu] = ans[K].terms[i].coff;
	}

	for (int i = K + 1; i >= 0; --i)
		cout << anscoff[i] << " ";
	cout << endl;
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
