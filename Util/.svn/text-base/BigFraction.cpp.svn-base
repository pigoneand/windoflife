#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

class BigInteger
{
public:
    static const int L = 3000 / 8;
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

    void print() const {
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

BigInteger gcd(BigInteger & a, BigInteger & b)
{
  if (b == 0) return a;
  BigInteger moder = a % b;
  return gcd(b, moder);
}

class Fraction
{
  public:
    BigInteger son;
    BigInteger mother;
    int sign;

    Fraction(int s, int m)
    {
      sign = 1;
      if (s < 0)
      {
        sign *= -1;
        s = -s;
      }
      if (m < 0)
      {
        sign *= -1;
        m = -m;
      }
      son = s;
      mother = m;
      //this->reduction();
    }

    Fraction()
    {
      son = 0;
      mother = 1;
      sign = 1;
    }

    void reduction()
    {
      BigInteger factor = gcd(son, mother);
      son = son / factor;
      mother = mother/ factor;
    }

    Fraction operator + (Fraction & other)
    {
      Fraction ret;
      BigInteger t1 = son * other.mother;
      BigInteger t2 = other.son * mother;
      ret.son = t1 + t2;
      ret.mother = mother * other.mother;
      ret.sign = sign * other.sign;
      //ret.reduction();
      return ret;
    }

    Fraction operator - (Fraction & other)
    {
      Fraction ret;  
      BigInteger t1 = son * other.mother;
      BigInteger t2 = other.son * mother;
      ret.son = t1 - t2;
      ret.mother = mother * other.mother;
      ret.sign = sign * other.sign;
      //ret.reduction();
      return ret;
    }

    Fraction operator * (Fraction & other)
    {
      Fraction ret;
      ret.son = son * other.son;
      ret.mother = mother * other.mother;
      ret.sign = sign * other.sign;
      //ret.reduction();
      return ret;
    }

    Fraction operator / (Fraction & other)
    {
      Fraction ret;
      ret.son = son * other.mother;
      ret.mother = mother * other.son;
      ret.sign = sign * other.sign;
      //ret.reduction();
      return ret;
    }

    int compare(Fraction & other) 
    {
      if (sign < other.sign) return -1;
      if (sign > other.sign) return 1;
      BigInteger t1 = son * other.mother;
      BigInteger t2 = mother * other.son;
      if (sign == 1)
        return t1.cmp(t2);
      else
        return t2.cmp(t1);
    }

    bool operator < (Fraction & other) 
    { return compare(other) < 0; }

    bool operator > (Fraction & other) 
    { return compare(other) > 0; }

    bool operator == (Fraction & other) 
    { return compare(other) == 0; }

    friend ostream & operator << (ostream & out, const Fraction & other)
    {
      if (other.sign == -1) 
        out << "-";
	  other.son.print();
	  out << "/";
	  other.mother.print();
      return out;
    }
};

int main()
{
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
}
