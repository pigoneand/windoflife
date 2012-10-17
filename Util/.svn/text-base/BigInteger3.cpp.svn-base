#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class BigInteger
{
public:
    static const int L = 300 / 8;
    static const int CPS = 100000000;

	bool operator < (const BigInteger & other) const { return cmp(other) < 0; }
    bool operator > (const BigInteger & other) const { return cmp(other) > 0; }
    bool operator <= (const BigInteger & other) const { return cmp(other) <= 0; }
    bool operator >= (const BigInteger & other) const { return cmp(other) >= 0; }
    bool operator == (const BigInteger & other) const { return cmp(other) == 0; }
    bool operator != (const BigInteger & other) const { return cmp(other) != 0; }

    int len, d[L];
    void fix() {
        while (len > 0 && d[len] == 0) len--;
    }

    BigInteger(int x = 0) {
        for (d[len = 0] = 0; x; x /= CPS) d[++len] = x % CPS;
    }
    BigInteger(const char *s) {
        d[len = 0] = 0;
        for (int i = strlen(s) - 1, e = CPS; i >= 0; i--)
            if (e == CPS) d[++len] = s[i] - '0', e = 10;
            else d[len] += (s[i] - '0') * e, e *= 10;
        fix();
    }
    BigInteger(const BigInteger &rhs) {
        len = rhs.len;
        memcpy(d, rhs.d, sizeof d[0] * (len + 1));
    }

    int cmp(const BigInteger &b) const {
        if (len != b.len) return len - b.len;
        int i = len; while (i > 1 && d[i] == b.d[i]) i--;
        return d[i] - b.d[i];
    }

    void print() {
        printf("%d", d[len]);
        for (int i = len - 1; i > 0; i--) printf("%08d", d[i]);
    }

	friend ostream & operator << (ostream & out, BigInteger & a)
	{
		a.print();
		return out;
	}

    BigInteger& operator += (const BigInteger &b) {
        for (int i = 1, t = 0; i <= b.len || t; t = (d[i] += t) / CPS, d[i++] %= CPS) {
            if (i > len) d[++len] = 0;
            if (i <= b.len) t += b.d[i];
        }
        return *this;
    }

    BigInteger operator + (const BigInteger &b) const {
        return BigInteger(*this) += b;
    }

    BigInteger operator - (const BigInteger &b) const {
        BigInteger c(*this);
        for (int i = 1, j = 0; i <= len; i++) {
            c.d[i] -= j;
            if (i <= b.len) c.d[i] -= b.d[i];
            if (c.d[i] < 0) j = 1, c.d[i] += CPS;
            else j = 0;
        }
        c.fix();
        return c;
    }

    BigInteger& operator *= (const int &b) {
        if (b == 0) len = 0;
        long long t = 0;
        for (int i = 1; i <= len; i++)
            d[i] = (t += d[i] * (long long) b) % CPS, t /= CPS;
        while (t) d[++len] = t % CPS, t /= CPS;
        return *this;
    }

    BigInteger operator * (const BigInteger &b) const {
        if (len == 0 || b.len == 0) return 0;
        long long sum, t = 0;
        BigInteger c; c.len = len + b.len - 1;
        for (int i = 1; i <= c.len; i++) {
            sum = t;
            int b1 = len < i ? len : i;
            int b2 = i - b.len > 0 ? i - b.len : 0;
            for (int j = b2; j < b1 && j < i; j++) {
                if (i - j > b.len) j = i - b.len - 1;
                else sum += (long long) d[j + 1] * b.d[i - j] ;
            }
            if (sum >= CPS) t = sum / CPS, c.d[i] = sum % CPS;
            else t = 0, c.d[i] = sum;
        }
        if (t) c.d[++c.len] = t;
        return c;
    }

    BigInteger operator / (const int &b) const {
        BigInteger c;
        long long t = 0;
        for (int i = len; i > 0; i--)
            t = t * CPS + d[i], c.d[i] = t / b, t %= b;
        c.len = len;
        c.fix();
        return c;
    }

    BigInteger operator / (const BigInteger &b) const {
        BigInteger c, f;
        for (int i=len; i>0; i--) {
            !f.len ? (f=d[i]) : (f=f*CPS, f.d[1]=d[i]);
            if (f.cmp(b)<0) {c.d[i]=0; continue;}
            int lf=1, rt=CPS-1;
            while (lf<=rt) {
                int mid=lf+rt>>1;
                (f.cmp(b*mid)<0) ? (rt=mid-1) : (lf=mid+1);
            }
            f=f-b*rt; c.d[i]=rt; if (i>c.len) c.len=i;
        }
        return c;
    }

    int operator % (const int &b) const {
        long long t = 0;
        for (int i = len; i > 0; i--) t = (t * CPS + d[i]) % b;
        return t;
    }

    BigInteger operator % (const BigInteger &b) const {
        BigInteger f;
        for (int i=len; i>0; i--) {
            !f.len ? (f=d[i]) : (f=f*CPS, f.d[1]=d[i]);
            if (f.cmp(b)<0) continue;
            int lf=1, rt=CPS-1;
            while (lf<=rt) {
                int mid=lf+rt>>1;
                (f.cmp(b*mid)<0) ? (rt=mid-1) : (lf=mid+1);
            }
            f=f-b*rt;
        }
        return f;
    }

    void shiftRight() {
        for (int i = len, t = 0; i > 0; i--)
            t = t * CPS + d[i], d[i] = t >> 1, t &= 1;
        fix();
    }

    BigInteger sqrt() {
        if (len == 0) return 0;
        BigInteger x, y(*this);
        y.d[y.len = y.len / 2 + 1] = CPS - 1;
        do x = y, y = (*this) / x + x, y.shiftRight(); while (x.cmp(y) > 0);
        return x;
    }

};

class SignBigInteger
{
public:
	BigInteger num;
	int sign;

	SignBigInteger(int x = 0)
	{
		sign = 1;
		if (x < 0) 
		{
			sign = -1;
			x = -x;
		}
		num = x;
	}

	void refine()
	{
		if (num == 0) 
			sign = 1;
	}

	bool operator == (const SignBigInteger & other) const 
	{ return sign == other.sign && num == other.num; }

	friend ostream & operator << (ostream & out, SignBigInteger & other)
	{
		if (other.sign < 0 && other.num != 0) out << "-";
		out << other.num;
		return out;
	}

	SignBigInteger operator + (const SignBigInteger & b)
	{
		if (sign == b.sign)
		{
			SignBigInteger ret;
			ret.sign = sign;
			ret.num = num + b.num;
			ret.refine();
			return ret;
		}
		else
		{
			SignBigInteger ret;
			if (num >= b.num) 
			{
				ret.sign = sign;
				ret.num = num - b.num;
				ret.refine();
			}
			else
			{
				ret = sign = b.sign;
				ret.num = b.num - num;
				ret.refine();
			}
			return ret;
		}
	}

	SignBigInteger operator - (const SignBigInteger & b)
	{
		SignBigInteger tmp = b;
		tmp.sign = -tmp.sign;
		tmp.refine();
		return (*this) + tmp;
	}

	SignBigInteger operator * (const SignBigInteger & b)
	{
		SignBigInteger ret;
		ret.num = num * b.num;
		ret.sign = sign * b.sign;
		ret.refine();
		return ret;
	}

	SignBigInteger operator / (const SignBigInteger & b)
	{
		SignBigInteger ret;
		ret.num = num / b.num;
		ret.sign = sign * b.sign;
		ret.refine();
		return ret;
	}

	SignBigInteger operator % (const SignBigInteger & b)
	{
		if (b.sign < 0 || b.num == 0) 
		{
			cerr << "mod error" << endl;
			system("pause");
			exit(0);
		}

		SignBigInteger ret;
		ret.sign = sign;
		ret.num = num % b.num;
		ret.refine();
		return ret;
	}

	SignBigInteger & operator *= (const int & b)
	{
		num *= b;
		refine();
		return (*this);
	}
};


BigInteger f[101][60];
bool caled[101][60];
int L, M, K;
BigInteger N;

inline int getMod(int x)
{ return (x + K * 100) % K; }

void deal()
{
	for (int i = 0; i < K; ++i)
		f[0][i] = 0;
	f[0][0] = 1;

	for (int i = 1; i < L; ++i)
	{
		for (int j = 0; j < K; ++j)
		{
			f[i][j] = 0;
			for (int num = 1; num <= M; ++num)
				f[i][j] += f[i - 1][getMod(j - num)];
		}
	}
	
	int nowSum = 0;
	for (int i = 1; i <= L; ++i)
	{
		int num;
		for (num = 1; num <= M; ++num)
		{
			BigInteger nowWays = f[L - i][getMod(K - num - nowSum)];
			if (N > nowWays)
				N = N - nowWays;
			else
				break;
		}
		nowSum += num;
		nowSum %= K;
		cout << num << " ";
	}
	cout << endl;
}

void init()
{
	cin >> L >> M >> K;
	string line;
	getline(cin, line);
	getline(cin, line);
	N = BigInteger(line.data());
	N = N + 1;
}


int main()
{
	init();
	deal();

#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}