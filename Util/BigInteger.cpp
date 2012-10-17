#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
using namespace std;

class BigInteger
{
public:
	const static int BASE = 10;

	vector<int> digits;

	/** The Big Integer's digits */
	inline int size() const { return digits.size(); }

	/** Constructors */
	BigInteger() { (*this) = 0; }
	BigInteger(int init) { (*this) = init; }
	BigInteger(const string & str) { (*this) = str; }
	BigInteger(const BigInteger & other) { digits = other.digits; }

	/** IO operation */
	friend ostream & operator << (ostream & out, const BigInteger &x);
	friend istream & operator >> (istream & in, BigInteger & x);

	/** Assignment operatoion */
	BigInteger & operator = (int init);
	BigInteger & operator = (const string & str);
	BigInteger & operator = (const BigInteger & other);

	/** Calculate operation */
	BigInteger operator * (const BigInteger & other);
	BigInteger operator + (const BigInteger & other);
	BigInteger operator / (const BigInteger & other);
	BigInteger operator - (const BigInteger & other);
	BigInteger operator % (const BigInteger & other);
	BigInteger operator * (int other);
	BigInteger operator / (int other);
	BigInteger operator % (int other);

	/** Additional calculate operation */
	/** power(x,y) */
	BigInteger operator ^ (int other);

	bool operator < (const BigInteger & other) const { return compare(other) < 0; }
	bool operator > (const BigInteger & other) const { return compare(other) > 0; }
	bool operator <= (const BigInteger & other) const { return compare(other) <= 0; }
	bool operator >= (const BigInteger & other) const { return compare(other) >= 0; }
	bool operator == (const BigInteger & other) const { return compare(other) == 0; }
	bool operator != (const BigInteger & other) const { return compare(other) != 0; }
	int compare(const BigInteger & y) const;

	/** Convert operation */
	string toString()
	{
		int len = size();
		string ret(len, '0');
		for (int i = 0; i < len; ++i) 
			ret[i] = getNumChar(digits[len - i - 1]);
		return ret;
	}

	int toInt()
	{
		string str = toString();
		int ret;
		sscanf(str.data(), "%d", &ret);
		return ret;
	}

	static inline char getNumChar(int x) { return x < 10 ? '0' + x : 'A' - 10 + x; }
};

/** IO operation */
ostream & operator << (ostream & out, const BigInteger & x)
{
	for (int i = x.digits.size() - 1; i >= 0; i--) 
		out << x.digits[i]; 
	return out; 
}

istream & operator >> (istream & in, BigInteger & x)
{
	string line;
	in >> line;
	x = line;
	return in;
}

/** Assignment operation */
BigInteger & BigInteger::operator = (const string & str)
{
	int len = str.length();
	digits = vector<int>(len);
	for (int i = 0; i < len; ++i) 
		digits[i] = str[len - i - 1] - '0';
	return (*this);
}

BigInteger & BigInteger::operator = (int init)
{
	if (init == 0) {
		digits = vector<int>(1);
		digits[0] = 0;
		return (*this);
	}
	digits.clear();
	while (init > 0) {
		digits.push_back(init % BASE);
		init /= BASE;
	}
	return (*this);
}

BigInteger & BigInteger::operator = (const BigInteger & other)
{
	if (&other != this) digits = other.digits;
	return (*this);
}

/** Calculation operations */
BigInteger BigInteger::operator * (const BigInteger & other)
{
	BigInteger ret;
	int lena = size();
	int lenb = other.size();
	int len = lena + lenb;
	ret.digits = vector<int>(len, 0);

	for (int i = 0; i < lena; ++i) 
		for (int j = 0; j < lenb; ++j) 
			ret.digits[i + j] += digits[i] * other.digits[j];

	for (int i = 0; i < len - 1; ++i) { 
		if (ret.digits[i] >= BASE) {
			ret.digits[i + 1] += ret.digits[i] / BASE; 
			ret.digits[i] %= BASE; 
		}
	}

	while (ret.digits[ret.size() - 1] >= BASE) { 
		ret.digits.push_back(ret.digits[ret.size() - 1] / BASE);
		ret.digits[ret.size() - 2] %= BASE;
	}
	while (ret.size() > 1 && ret.digits[ret.size() - 1] == 0) 
		ret.digits.pop_back();
	return ret;
}

/** Multiply int, assume other * BASE < maxint */
BigInteger BigInteger::operator * (int other)
{
	BigInteger ret;
	const static int MAX_INC_LEN = 10;
	ret.digits = vector<int>(size() + MAX_INC_LEN);

	int nowLen = size();
	int len = size() + MAX_INC_LEN;
	for (int i = 0; i < nowLen; ++i) 
		ret.digits[i] = digits[i] * other;
	for (int i = 0; i < len - 1; ++i) 
		if (ret.digits[i] >= BASE) {
			ret.digits[i + 1] += ret.digits[i] / BASE;
			ret.digits[i] %= BASE;
		}
		while (ret.size() > 1 && ret.digits[ret.size() - 1] == 0) 
			ret.digits.pop_back();
		return ret;
}

/** operator plus */
BigInteger BigInteger::operator + (const BigInteger & other)
{
	BigInteger ret; 
	int lena = size();
	int lenb = other.size();
	int len = max(lena, lenb) + 1;
	ret.digits = vector<int>(len, 0);
	int i;
	for (i = 0; i < lena || i < lenb || i < len && ret.digits[i]; i++) {
		if (i < lena) ret.digits[i] += digits[i];
		if (i < lenb) ret.digits[i] += other.digits[i];
		if (ret.digits[i] >= BASE) {
			ret.digits[i + 1] = ret.digits[i] / BASE;
			ret.digits[i] %= BASE;
		}
	}
	if (ret.digits[ret.size() - 1] == 0) 
		ret.digits.pop_back();
	return ret;
}

/** Assume this >= other */
BigInteger BigInteger::operator - (const BigInteger & other)
{
	BigInteger ret;
	int lena = this->size();
	int lenb = other.size();
	int len = lena;
	ret.digits = vector<int>(len, 0);

	for (int i = 0, jiewei = 0; i < lena; i++) {
		ret.digits[i] = digits[i] - jiewei;
		if (i < lenb) ret.digits[i] -= other.digits[i];
		jiewei = 0;
		if (ret.digits[i] < 0) { 
			jiewei = 1;
			ret.digits[i] += BASE;
		} 
	}

	while (ret.size() > 1 && ret.digits[ret.size() - 1] == 0) 
		ret.digits.pop_back();
	return ret;
}

BigInteger BigInteger::operator / (const BigInteger & other)
{
	if (other == 0) cerr << "divide zero" << endl;

	BigInteger d(0), ret;
	int lena = size();
	int lenb = other.size();
	int len = lena;
	ret.digits = vector<int>(len, 0);

	for (int i = lena - 1; i >= 0; i--) {
		/** if d != 0, d *= 10 */
		if (d != 0) {
			d.digits.push_back(0);
			for (int j = d.size() - 1; j > 0; --j) 
				d.digits[j] = d.digits[j - 1];
			d.digits[0] = 0;
		}
		d.digits[0] = digits[i]; 
		ret.digits[i] = 0;
		while (int j = d.compare(other) >= 0) {
			d = d - other;
			ret.digits[i]++;
			if (j == 0) break;
		}
	}

	/** Remove leading zero */
	while (ret.size() > 1 && ret.digits[ret.size() - 1] == 0)
		ret.digits.pop_back();
	return ret;
}

BigInteger BigInteger::operator / (int other)
{
	if (other == 0) cerr << "divide zero" << endl;

	int d = 0;
	BigInteger ret;
	int lena = size();
	int len = lena;
	ret.digits = vector<int>(len, 0);

	for (int i = lena - 1; i >= 0; i--) {
		if (d != 0) d *= 10;
		d += digits[i];
		ret.digits[i] = d / other;
		d %= other;
	}

	/** Remove leading zero */
	while (ret.size() > 1 && ret.digits[ret.size() - 1] == 0)
		ret.digits.pop_back();
	return ret;
}

BigInteger BigInteger::operator % (const BigInteger & other) 
{
	if (other == 0) cerr << "divide zero" << endl;
	BigInteger div = (*this) / other;
	return (*this) - div * other;
}

BigInteger BigInteger::operator % (int other)
{
	if (other == 0) cerr << "divide zero" << endl;

	int d = 0;
	int lena = size();
	int len = lena;

	for (int i = lena - 1; i >= 0; i--) {
		if (d != 0) d *= 10;
		d += digits[i];
		d %= other;
	}
	return d;
}

BigInteger BigInteger::operator ^ (int other)
{
	if (other < 0) cerr << "power negative" << endl;
	if (other == 0) return 1;
	if (other == 1) return (*this);

	int mid = other / 2;
	BigInteger midResult = (*this) ^ mid;
	return other % 2 == 0 ? midResult * midResult : (midResult * midResult) * (*this);
}

/** Compare two bigInteger
* Actually , return sign(this - other)
*/
int BigInteger::compare(const BigInteger & other) const
{
	if (size() > other.size()) return 1;
	if (size() < other.size()) return -1;
	int i = size() - 1;
	while (i > 0 && digits[i] == other.digits[i]) 
		i--;
	return digits[i] - other.digits[i];
}

class BigFloat
{
public:
	static const int fprec = 150;

	void setZero();
	bool isZero();
	void normalize();

	BigFloat();
	BigFloat(int inte) {(*this) = inte;}
	BigFloat(const char * s) {(*this) = s;}
	
	// exponential notation 
	BigFloat(string & str, bool exp) 
	{
		for (int i = 0; i < str.length(); ++i)
			if (str[i] == 'e' || str[i] == 'E') str[i] = ' ';

		string d; int e = 0;
		istringstream sin(str);
		sin >> d >> e;
		BigFloat ret(d.data());
		BigFloat div(1);
		BigFloat ten(10);
		for (int i = 0; i < abs(e); ++i) div = div * ten;
		if (e > 0) 
			*this = ret * div; 
		else 
			*this = ret / div;
	}

	BigFloat & operator = (const char * s);
	BigFloat & operator = (int inte);
	BigFloat & operator = (string & str);
	BigFloat operator + (BigFloat & b);
	BigFloat operator - (BigFloat & b);
	BigFloat operator * (BigFloat & b);
	BigFloat operator / (BigFloat & b);
	BigFloat operator += (BigFloat & b)
	{ (*this) = (*this) + b; }
	BigFloat operator -= (BigFloat & b)
	{ (*this) = (*this) - b; }
	BigFloat operator *= (BigFloat & b)
	{ (*this) = (*this) * b; }
	BigFloat operator /= (BigFloat & b)
	{ (*this) = (*this) / b; }

	bool operator < (BigFloat & other) { return compare(other) < 0; }
	bool operator > (BigFloat & other) { return compare(other) > 0; }
	bool operator <= (BigFloat & other) { return compare(other) <= 0; }
	bool operator >= (BigFloat & other) { return compare(other) >= 0; }
	bool operator == (BigFloat & other) { return compare(other) == 0; }
	bool operator != (BigFloat & other) { return compare(other) != 0; }
	int compare(BigFloat & y);

	void LShift(int s);
	void RShift(int s);
	void multi10(int s);

	friend ostream & operator << (ostream & out, BigFloat & x);
	string toString(int outputPrec = -1);
	string toExpString(int outputPrec);

	int sign;
	int prec;
	BigInteger num;
};

int BigFloat::compare(BigFloat & b) 
{
	if (prec > b.prec) b.LShift(prec - b.prec);
	else if (prec < b.prec) LShift(b.prec - prec);
	bool aZero = isZero();
	bool bZero = b.isZero();
	if (aZero && bZero) return 0;
	if (aZero) 
		return b.sign > 0 ? -1 : 1;
	if (bZero)
		return sign > 0 ? 1 : -1;

	if (sign > 0 && b.sign < 0) return 1;
	if (sign < 0 && b.sign > 0) return -1;
	if (sign > 0)
		return num.compare(b.num); 
	else
		return b.num.compare(num);
}

void BigFloat::multi10(int s)
{
	if (prec >= s)
	{
		prec -= s;
		return;
	}
	else
	{
		int remain = s - prec;
		int oldSize = num.digits.size();
		prec = 0;
		num.digits.resize(num.digits.size() + remain);
		for (int i = num.digits.size() - 1; i >= remain; --i)
			num.digits[i] = num.digits[i - oldSize];
		for (int i = remain - 1; i >= 0; --i)
			num.digits[i] = 0;
		return;
	}
}

void BigFloat::LShift(int s)
{
	prec += s; 
	num.digits.resize(num.digits.size() + s);
	for (int i = num.digits.size() - 1; i >= s; --i) 
		num.digits[i] = num.digits[i - s];
	for (int i = s - 1; i >= 0; --i)
		num.digits[i] = 0;
}

void BigFloat::RShift(int s)
{
	prec -= s;
	num.digits = vector<int>(num.digits.begin() + s, num.digits.end());
}

void BigFloat::setZero() { sign = 1; num = 0; prec = 0; }
bool BigFloat::isZero() 
{
	for (int i = 0; i < num.digits.size(); ++i)
		if (num.digits[i] != 0) 
			return false;
	return true;
}

void BigFloat::normalize()
{
	if (prec > BigFloat::fprec)
		RShift(prec - BigFloat::fprec);

	int i;
	for (i = 0; i < prec; ++i)
		if (num.digits[i] != 0)
			break;

	RShift(i);
}

BigFloat::BigFloat() { setZero(); }

ostream & operator << (ostream & out, BigFloat & x)
{
	if (x.sign < 0) out << "-";
	int i;
	for (i = x.num.digits.size(); i > x.prec; --i)
		out << x.num.digits[i - 1];
	if (x.prec >= x.num.digits.size())
		out << "0";
	if (x.num == 0) 
	{
		out << ".0";
		return out;
	}

	int k = i;
	while (k > 0 && x.num.digits[k - 1] == 0) k--;
	if (k == 0) 
	{
		out << ".0";
		return out;
	}
	out << ".";
	if (x.num.digits.size() < x.prec) 
		for (int j = 0; j < x.prec - x.num.digits.size(); ++j)
			out << "0";
	int low = 1;
	while (x.num.digits[low - 1] == 0) low++;
	while (i >= low) 
		out << x.num.digits[--i];
	return out;
}

string BigFloat::toString(int outputPrec)
{
	if (outputPrec == -1)
	{
		ostringstream os;
		os << (*this);
		return os.str();
	}
	else
	{
		ostringstream os;
		os << (*this);
		string ret = os.str();
		int prec = 0;
		if (ret.find(".") != string::npos)
			prec = ret.length() - 1 - ret.find(".");
		if (prec < outputPrec)
		{
			ret += string(outputPrec - prec, '0');
			return ret;
		}
		if (prec > outputPrec)
		{
			int last = ret[ret.length() - (prec - outputPrec)] - '0';
			ret = ret.substr(0, ret.length() - (prec - outputPrec));
			return ret;
		}
	}
}

string BigFloat::toExpString(int outputPrec)
{
	int e = 0;
	BigFloat one(1);
	BigFloat ten(10);
	BigFloat zero(0);
	BigFloat f = *this;
	while (f < one && f > zero)
	{
		f = f * ten;
		e--;
	}
	while (f >= ten)
	{
		f = f / ten;
		e++;
	}

	string d = f.toString(outputPrec + 10);
	int digits = 0;
	for (int i = 0; i < d.length(); ++i)
		if (d[i] != '.') digits++;
	if (digits > outputPrec) 
		d = d.substr(0, d.length() - (digits - outputPrec));
	char ans[200];
	sprintf(ans, "%se%d", d.data(), e);
	return string(ans);
}

BigFloat & BigFloat::operator = (int inte)
{
	prec = 0;
	if (inte >= 0) { sign = 1; num = inte; }
	else { sign = -1; num = -inte; }
	return (*this);
}

BigFloat & BigFloat::operator = (const char * s)
{
	if (strlen(s) == 1 && s[0] == '0')
		return (*this) = 0;

	int p, i, l;
	setZero();
	num.digits.clear();
	int offset = 0;
	if (s[0] == '-') { sign = -1; offset++; }
	if (s[0] == '+') { sign = 1; offset++; }
	l = strlen(s + offset);
	for (p = 0; p < l; ++p)
		if (s[p + offset] == '.') break;

	if (p == l)
		prec = 0;
	else
		prec = l - 1 - p;

	for (i = l - 1; i >= 0; --i) 
		if (s[i + offset] != '.') 
			num.digits.push_back(s[i + offset] - '0');

	normalize();
	return (*this);
}

BigFloat & BigFloat::operator = (string & str)
{
	(*this) = str.data();
	return (*this);
}

BigFloat BigFloat::operator + (BigFloat & b)
{
	BigFloat c;
	if (prec > b.prec) b.LShift(prec - b.prec); else
		if (prec < b.prec) LShift(b.prec - prec);
	if (sign == b.sign)
	{
		c.sign = sign;
		c.prec = prec;
		c.num = num + b.num;
		if (c.num == 0) c.setZero();
	}
	else
	{
		c.prec = prec;
		if (num == b.num) c.setZero();
		else if (num > b.num) { c.sign = sign; c.num = num - b.num; }
		else if (num < b.num) { c.sign = b.sign; c.num = b.num - num; }
		if (c.num == 0) c.setZero();
	}
	c.normalize();
	return c;
}

BigFloat BigFloat::operator - (BigFloat & b)
{
	b.sign = -b.sign;
	BigFloat c = (*this) + b;
	b.sign = -b.sign;
	return c;
}

BigFloat BigFloat::operator * (BigFloat & b)
{
	BigFloat c;
	c.sign = sign * b.sign;
	c.num = num * b.num;
	c.prec = prec + b.prec;
	if (c.num == 0) c.setZero();
	c.normalize();
	return c;
}

BigFloat BigFloat::operator / (BigFloat & b)
{
	BigFloat ret, c, d;

	c = (*this);
	if (c.isZero()) 
	{
		c.setZero();
		return c;
	}
	c.LShift(BigFloat::fprec);
	c.multi10(b.prec);

	d = b;
	int i;
	for (i = d.num.digits.size() - 1; i >= 0; --i)
		if (d.num.digits[i] != 0)
			break;
	d.num.digits.resize(i + 1);

	ret.prec = c.prec;
	ret.sign = c.sign * d.sign;
	ret.num = c.num / d.num;
	ret.normalize();

	return ret;
}


inline bool equal(BigFloat a, double b)
{
	string sa = a.toString(8);
	char temp[100];
	sprintf(temp, "%.8lf", b);
	string sb(temp);

	double a1; double a2;
	sscanf(sa.data(), "%lf", &a1);
	sscanf(sb.data(), "%lf", &a2);

	if (fabs(a1 - a2) > 1e-7)
	{
		cout << "error\t" << a << "\t" << b << endl;
		cout << "convert\t" << sa << "\t" << sb << endl;
		return false;
	}
	return true;
}

////////////////////////////////////////////
// TEST 
/////////////////////////////////////////////


#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

int main()
{
	int N;
	scanf("%d", &N);
	string line;
	getline(cin, line);

	BigFloat ans = 0;
	for (int i = 0; i < N; ++i)
	{
		getline(cin, line);
		BigFloat now(line, true);
		ans = ans + now;
	}
	//cout << ans << endl;
	cout << ans.toExpString(19) << endl;
	return 0;
}

/** Unit test for BigInteger's correctness */
int _main()
{
	bool error = false;
	for (int a = 0; a <= 100; ++a) {
		for (int b = 0; b <= 100; ++b) {
			BigInteger aa = a;
			BigInteger bb = b;

			int plusAnswer = a + b;
			if (aa + bb != BigInteger(plusAnswer)) {
				cout << "plus error" << endl;
				error = true;
			}

			if (a > b != aa > bb) {
				cout << "> error" << endl;
				error = true;
			}

			if (a >= b) {
				if ((aa - bb) != BigInteger(a - b)) {
					cout << "minus error" << endl;
					error = true;
				}
			}

			if ((aa * bb) != BigInteger(a * b)) {
				cout << a << "\t" << b << endl << "\t" << aa * bb << endl;
				cout << "multi error" << endl;
				error = true;
			}

			if (b != 0) {
				if (BigInteger(a / b) != (aa / bb)) {
					cout << a << "\t" << b << "\t" << a / b << endl;
					cout << aa / bb << endl;
					cout << "divide error" << endl;
					error = true;
				}
				if (BigInteger(a / b) != (aa / b)) {
					cout << "divide int error" << endl;
					error = true;
				}
			}

			if (b != 0) {
				if (BigInteger(a % b) != (aa % bb)) {
					cout << "mod error" << endl;
					error = true;
				}
				if (BigInteger(a % b) != (aa % b)) {
					cout << "mod error" << endl;
					error = true;
				}
			}

			if (b < 5 && a < 50) {
				if (BigInteger((int)pow((double)a, (double)b)) != (aa ^ b)) {
					cout << "power error" << endl;
					error = true;
				}
			}

			if (aa.toInt() != a) {
				cout << "convert error" << endl;
				error = true;
			}

			if (BigInteger(a * b) != aa * b) {
				cout << "multi with int error" << endl;
				error = true;
			}
		}
	}
	cout << "big integer errors" << endl;
	cout << error << endl;

	for (int t = 0; t < 1000; ++t)
	{
		double x = (double)(rand() % 1000) / 100;
		double y = (double)(rand() % 1000) / 100;
		if (rand() % 2 == 0) x = -x;
		if (rand() % 2 == 0) y = -y;
		if (y == 0.0) y += 0.1;

		char sx[100];
		char sy[100];
		sprintf(sx, "%lf", x);
		sprintf(sy, "%lf", y);
		BigFloat xx(sx);
		BigFloat yy(sy);

		double plusAns = x + y;
		double minAns = x - y;
		double multiAns = x * y;
		double divideAns = x / y;

		BigFloat plus = xx + yy;
		BigFloat minus = xx - yy;
		BigFloat multi = xx * yy;
		BigFloat divide = xx / yy;

		if (!equal(plus, plusAns))
		{
			error = true;
		}
		if (!equal(minus, minAns))
		{
			error = true;
		}
		if (!equal(multi, multiAns))
		{
			error = true;
		}
		if (!equal(divide, divideAns))
		{
			cout << x << "\t" << y << endl;
			cout << divide << "\t" << divideAns << endl;
			error = true;
		}

		bool c1 = x > y;
		bool c11 = xx > yy;
		if (c1 != c11)
		{
			error = true;
			cout << x << "\t" << y << endl;
		}
	}


	if (error) cout << "has error" << endl;
	else cout << "no error" << endl;

	while (true)
	{
		BigFloat aa;
		BigFloat bb;
		string line;
		getline(cin, line);
		aa = line;
		getline(cin, line);
		bb = line;

		cout << aa << "\t" << bb << endl;
		BigFloat cc = aa + bb;
		cout << "+\t" << cc << endl;
		cc = aa * bb;
		cout << "*\t" << cc << endl;

		if (!bb.isZero()) 
		{
			cc = aa / bb;
			cout << "/\t" << cc << endl;
		}

		cout << "a < b" << (aa < bb) << endl;
		cout << "a = b" << (aa == bb) << endl;
	}

	return 0;
}


