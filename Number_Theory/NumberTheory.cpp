#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cmath>
#include <climits>
#include <set>
using namespace std;


#define DEBUG 1
#define debug1(x) if (DEBUG) cout << #x" = " << x << endl;
#define debug2(x, y) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

template <class T>
ostream & operator << (ostream & out, const vector<T> & data)
{ out << "["; for (int i = 0; i < data.size(); ++i) out << data[i] << (i == data.size() - 1 ? "" : ","); out << "]"; return out; }

template <class T>
ostream & operator << (ostream & out, const set<T> & s)
{ out << "{"; for (typename set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

template <class T>
ostream & operator << (ostream & out, const multiset<T> & s)
{ out << "{"; for (typename multiset<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

template <class T1, class T2>
ostream & operator << (ostream & out, const pair<T1, T2> & p)
{ out << "(" << p.first << "," << p.second << ")"; return out; }

template <class T1, class T2>
ostream & operator << (ostream & out, const map<T1, T2> & m)
{ 
  for (typename map<T1, T2>::const_iterator itr = m.begin(); itr != m.end(); ++itr)
    out << itr->first << "->" << itr->second << " ";
  return out;
}


////////////////////////////////////////////////////
// BASIC OPERATIONS
////////////////////////////////////////////////////
// a ^ b mod c , c >= 1, b >= 0, a >= 0
inline long long getmod(long long a, unsigned int b, long long c)
{
  if (a == 0) return 0;
  if (c == 1) return 0;
  if (b == 0) return 1;
  if (b == 1) return a % c;

  long long ret = 1;
  for (int i = 31; i >= 0; --i)
    if ((b & (1U << i)) > 0)
    {
      ret = (ret * ret) % c;
      ret = (ret * a) % c;
    }
    else
      ret = (ret * ret) % c;
  return ret;
}

/** 
* @warning gcd(2, -3) = -1
*/
int gcd(int x, int y)
{
  if (!x || !y) return x > y ? x : y;
  for (int t; (t = x % y); x = y, y = t);
  return y;
}

/** 
* ax + by = gcd(a, b)
* x, y may be negative 
*/
int extgcd(int a, int b, int & x, int & y)
{
  if (b == 0) { x = 1; y = 0; return a; }
  int d = extgcd(b, a % b, x, y);
  int t = x; x = y; y = t - a / b * y;
  return d;
}

/** 
* a * x mod p = 1 , (a,p) = 1
*/
int getReverse(int a, int p)
{
  if (a == 1) return 1;
  int x, y;
  extgcd(a, p, x, y);
  return (x % p + p) % p;
}

long long getModInRange(long long begin, long long end, long long moder)
{
  if (moder == 1) return end - begin + 1;
  long long ans = (end - begin + 1) / moder;
  long long remain = (end - begin + 1) % moder;
  long long start = begin % moder;
  long long stop = start + remain - 1;
  if (start == 0 || stop >= moder) ans++;
  return ans;
}

//////////////////////////////////////////////////////////////////////
// Algorithm about primes 
//////////////////////////////////////////////////////////////////////
class Prime 
{
public:
  /** The Primes */
  vector<int> primes;

  Prime()
  {
    genPrime(1000000);
  }

  /** Generate the primes from [2,N] */
  int genPrime(int N) {
    bool * mk = new bool[N + 2];
    memset(mk , 0 , N + 1);
    for (int i = 2 , k = 4 ; i <= N ; i++ , k += i + i - 1) {
      if (!mk[i]) 
      {
        primes.push_back(i);
        if (k <= N) for (int j = i + i ; j <= N ; j += i) mk[j] = 1;
      }
    }
    delete [] mk;
    return (int) primes.size();
  }

  /** Return the factors of the given long long number 
  *  Remember to call GenPrime first 
  */
  map<long long ,int> getFactors(long long N) 
  { 
    map<long long ,int> factors;
    long long root = ((long long) sqrt((double)N)) + 1;
    for(unsigned int i = 0 ; N > 1 && i < primes.size() && primes[i] <= root ; ++i) {
      if (N % primes[i] == 0) {
        factors[ primes[i] ] = 0;
        while (N % primes[i] == 0)
          N /= primes[i] , factors[ primes[i] ]++ ; 
      }
    }
    if (N > 1) factors[N] = 1; 
    return factors; 
  }

  map<int, int> getFactorsInt(int N)
  {
    map<int ,int> factors;
    int root = ((int) sqrt((double)N)) + 1;
    for(unsigned int i = 0 ; N > 1 && i < primes.size() && primes[i] <= root ; ++i) {
      if (N % primes[i] == 0) {
        factors[ primes[i] ] = 0;
        while (N % primes[i] == 0)
          N /= primes[i] , factors[ primes[i] ]++ ; 
      }
    }
    if (N > 1) factors[N] = 1; 
    return factors; 
  }

  map<int, int> getJieFactors(int x)
  {
    map<int, int> ret;
    for (int i = 0; x >= Prime::prime.primes[i]; ++i)
    {
      int p = Prime::prime.primes[i];int t = x;
      while (t >= p)	{	ret[p] += t / p; 	t /= p;	}
    }
    return ret;
  }

  /** Return the divisiors of the given number, divisiors are not sorted !! */
  vector<long long> getDivisors(long long N)
  {
    if (N == 1)
    {
      vector<long long> ret(1, 1);
      return ret;
    }

    map<long long, int> factors = getFactors(N);
    vector<long long> p;
    vector<int> maxi;
    for (map<long long, int>::iterator itr = factors.begin(); itr != factors.end(); ++itr)
      p.push_back(itr->first), maxi.push_back(itr->second);

    vector<long long> ret;
    vector<int> nowi(p.size(), 0);
    int nowp = (int) p.size() - 1;

    while (true)
    {
      long long now = 1;
      for (int i = 0; i < p.size(); ++i)
        for (int j = 1; j <= nowi[i]; ++j)
          now = now * p[i];
      ret.push_back(now);

      nowp = (int) p.size() - 1;
      nowi[nowp]++;
      while (nowi[nowp] > maxi[nowp])
      {
        nowp--;
        if (nowp < 0) return ret;
        nowi[nowp]++;
      }

      for (int i = nowp + 1; i < p.size(); ++i)
        nowi[i] = 0;
    }
    return ret;
  }

  static Prime prime;
};

Prime Prime::prime;

class PrimeJudger
{
public:
  const static int bits = 19, mask = (1<<bits) - 1;
  static unsigned long long mul(unsigned long long x, unsigned long long y, unsigned long long M) 
  {
    if (x <= UINT_MAX && y <= UINT_MAX) return x * y % M;
    unsigned long long rslt = y * (x & mask) % M;
    while (x >>= bits) rslt = (rslt + (y = (y << bits) % M) * (x & mask)) % M;
    return rslt;
  }

  static int mtest(unsigned long long n, unsigned long long a) {
    unsigned long long s, t, nmin1 = n - 1;
    int r;
    for (s = nmin1, r = 0; !(s & 1); s >>= 1, r++) ;
    for(t = a; s >>= 1; ) 
    {
      a = mul(a, a, n);
      if (s & 1) t = mul(t, a, n);
    }
    if (t == 1 || t == nmin1) return 1;
    while (--r) if ((t = mul(t, t, n)) == nmin1) return 1;
    return 0;
  }

  static bool isPrime(unsigned long long n) {
    if(n<29) return n==2 || n==3 || n==5 || n==7 || n==11 || n==13 || n==17 || n==19 || n==23;
    if(!(n&1 && n%3 && n%5 && n%7 && n%11 && n%13 && n%17 && n%19 && n%23)) return 0;
    return mtest(n, 2) && mtest(n, 1215) &&
      (n==17431 || mtest(n, 34862) && (n==3281359 || mtest(n, 574237825)));
  }
};



/** 
* C mn mod p , p may not be prime
*/
inline void addFactor(map<int, int> & cnt1, map<int, int> & cnt2)
{	for (map<int, int>::iterator itr = cnt2.begin(); itr != cnt2.end(); ++itr)		cnt1[itr->first] += itr->second;}

inline void minusFactor(map<int, int> & cnt1, map<int, int> & cnt2)
{	for (map<int, int>::iterator itr = cnt2.begin(); itr != cnt2.end(); ++itr)		cnt1[itr->first] -= itr->second;}

inline void addFactor(vector<int> & t1, vector<int> & t2)
{ for (int i = 0; i < t1.size(); ++i) t1[i] += t2[i]; }

inline void minusFactor(vector<int> & t1, vector<int> & t2)
{ for (int i = 0; i < t1.size(); ++i) t1[i] -= t2[i]; }

inline long long getFactorModer(map<int, int> & cnt, int p)
{
  long long ans = 1;
  for (map<int, int>::iterator itr = cnt.begin(); itr != cnt.end(); ++itr)
    if (itr->second > 0)
      ans = ans * getmod(itr->first, itr->second, p) % p;
  return ans;
}



/** 
* a * x = b mod n
* @warning : x could be negative
*/
vector<int> modeq(int a, int b, int n)
{
  vector<int> ret;
  int x, y;
  int d = extgcd(a, n, x, y);
  if (b % d > 0) return ret;
  else
  {
    int e = (x * (b / d)) % n;
    for (int i = 0; i < d; ++i)
      ret.push_back((e + i * (n / d)) % n);
    return ret;
  }
}

/** 
* Chinese Remainder Theorem
* mi 两两互质
*/
long long getModEquations(vector<long long> & b, vector<long long> & m)
{
  long long M = 1;
  for (long long i = 0; i < m.size(); ++i)
    M *= m[i];

  long long ret = 0;
  for (long long i = 0; i < b.size(); ++i)
  {
    long long Mi = M / m[i];
    long long yi = modeq(Mi, 1, m[i])[0];
    yi = (yi % m[i] + m[i]) % m[i];
    ret += b[i] * Mi * yi;
    ret %= M;
  }
  return ret;
}


// 判别二次剩余 , d 为 mod p 的二次剩余 当且仅当 
// d ^ ((p - 1) / 2) mod p == 1 (p > 2) 

// 寻找 p 的最大原根primitive_root， x ^ i 遍历整个 Zp* 
int primitive_root(int p) {
  vector<int> fact;
  int phi = p-1,  n = phi;
  for (int i=2; i*i<=n; ++i)
    if (n % i == 0) {
      fact.push_back (i);
      while (n % i == 0)
        n /= i;
    }
    if (n > 1)
      fact.push_back (n);

    for (int res = p - 1; res >= 2; --res) {
      bool ok = true;
      for (unsigned i=0; i < fact.size() && ok; ++i)
        ok &= getmod (res, phi / fact[i], p) != 1;
      if (ok)  return res;
    }
    return -1;
}

// For each N you should output the power of the Nth by order Mersenne prime.
map<int, int> getMersennePrimes()
{
  map<int, int> ret;
  ret[1] = 2;	ret[2] = 3;	ret[3] = 5;	ret[4] = 7;	ret[5] = 13;
  ret[6] = 17;	ret[7] = 19;	ret[8] = 31;	ret[9] = 61;	ret[10] = 89;
  ret[11] = 107;	ret[12] = 127;	ret[13] = 521;	ret[14] = 607;	ret[15] = 1279;
  ret[16] = 2203;	ret[17] = 2281;	ret[18] = 3217;	ret[19] = 4253;	ret[20] = 4423;
  ret[21] = 9689;	ret[22] = 9941;	ret[23] = 11213;	ret[24] = 19937;	ret[25] = 21701;
  ret[26] = 23209;	ret[27] = 44497;	ret[28] = 86243;	ret[29] = 110503;	ret[30] = 132049;
  ret[31] = 216091;	ret[32] = 756839;	ret[33] = 859433;	ret[34] = 1257787;	ret[35] = 1398269;
  ret[36] = 2976221;	ret[37] = 3021377;	ret[38] = 6972593;
  return ret;
}

// N >= 2, AC URAL 1356, find minimum primes that sum equal to N
vector<int> getPrimeSum(int N)
{
  vector<int> ret;
  if (PrimeJudger::isPrime(N)) 
  {
    ret.push_back(N);
    return ret;
  }

  if (N == 4) {	ret.push_back(2);	ret.push_back(2);	return ret;	}
  if (N == 6) {	ret.push_back(3);	ret.push_back(3);	return ret;	}
  if (N == 8) {ret.push_back(3);ret.push_back(5); return ret;}
  if (N == 9) {ret.push_back(2); ret.push_back(7); return ret;}

  if (N % 2 == 0)
  {
    for (int i = 0; i < Prime::prime.primes.size(); ++i)
      if (PrimeJudger::isPrime(N - Prime::prime.primes[i]))
      {
        ret.push_back(Prime::prime.primes[i]);
        ret.push_back(N - Prime::prime.primes[i]);
        return ret;
      }
  }
  else
  {
    if (PrimeJudger::isPrime(N - 2))
    {
      ret.push_back(2);
      ret.push_back(N - 2);
      return ret;
    }
    ret = getPrimeSum(N - 3);
    ret.push_back(3);
    return ret;
  }
  return ret;
}

// Euler function
int getPhi(int x)
{
  map<int, int> factors = Prime::prime.getFactorsInt(x);
  for (map<int, int>::iterator itr = factors.begin(); itr != factors.end(); ++itr)
    x = x / (itr->first) * (itr->first - 1);
  return x;
}

// Factor Sum
long long getFactorSum(int x)
{
  map<int, int> factors = Prime::prime.getFactorsInt(x);
  long long ret = 1;
  for (map<int, int>::iterator itr = factors.begin(); itr != factors.end(); ++itr)
  {
    long long now = 1;
    for (int i = 1; i <= itr->second + 1; ++i)
      now = now * itr->first;
    ret *= (now - 1) / (itr->first - 1);
  }
  return ret - x;
}

// 求欧拉函数的反函数，最小的X使得Phi(X) = K，如果不存在返回0
vector<int> phirev_cand;
long long phirev_ans;

void phirev_search(int remain, int off, long long now)
{
  if (remain == 1)
  {
    phirev_ans = min(phirev_ans, now);
    return;
  }

  if (now >= phirev_ans) return;

  for (int i = off; i < phirev_cand.size(); ++i)
    if (remain % phirev_cand[i] == 0) 
    {
      phirev_search(remain / phirev_cand[i], i + 1, now * (phirev_cand[i] + 1));
      int t = remain / phirev_cand[i];
      long long n = now * (phirev_cand[i] + 1);
      while (t % (phirev_cand[i] + 1) == 0)
      {
        phirev_search(t / (phirev_cand[i] + 1), i + 1, n * (phirev_cand[i] + 1));
        t /= (phirev_cand[i] + 1);
        n *= (phirev_cand[i] + 1);
      }
    }
    return;
}

long long getMinX_PhiXEqualK(int K)
{
  if (K == 1) return 1;
  if (PrimeJudger::isPrime(K + 1)) return K + 1;
  if (PrimeJudger::isPrime(K)) return 0;
  phirev_cand.clear();

  vector<long long> divs = Prime::prime.getDivisors(K);
  sort(divs.begin(), divs.end());

  for (int i = 0; i < divs.size(); ++i)
  {
    if (PrimeJudger::isPrime(divs[i] + 1))
      phirev_cand.push_back(divs[i]);
  }

  phirev_ans = 1000000000LL * 1000000000LL;
  phirev_search(K, 0, 1);

  if (phirev_ans == 1000000000LL * 1000000000LL) return 0;
  else return phirev_ans;
}


// 求离散对数
// a ^ x = 1 mod N
// return 0 non log
// AC URAL 1456
int getLog(int a, int N)
{
  if (gcd(a, N) > 1) return 0;
  int phi = getPhi(N);

  vector<long long> divs = Prime::prime.getDivisors(phi);
  sort(divs.begin(), divs.end());

  for (int i = 0; i < divs.size(); ++i)
    if (getmod(a, divs[i], N) == 1) 
      return divs[i];
  return 0;
}

// m > 1
pair<string, string> get1_M(int m)
{
  pair<string, string> ret;
  int now = 1;
  map<int, int> app;

  while (true)
  {
    now *= 10;

    if (now == 0) break;
    if (app.find(now) != app.end()) 
    {
      ret.second = ret.first.substr(app[now]);
      ret.first = ret.first.substr(0, app[now]);
      break;
    }

    app[now] = (int) ret.first.length();
    ret.first.push_back('0' + now / m);
    now %= m;
  }

  //debug2(ret.first, ret.second);
  return ret;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void init()
{
  int T;
  scanf("%d", &T);
  while (T--)
  {
    int N, P;
    scanf("%d%d", &N, &P);
    
    long long ans = 0;
    vector<long long> factors = Prime::prime.getDivisors(N);
    for (int i = 0; i < factors.size(); ++i)
    {
      int n = (int) factors[i];
      int phi = getPhi(N / n);
      long long temp = getmod(N, n - 1, P) * phi % P;
      ans += temp;
    }
    ans %= P;
    int ians = (int) ans;
    printf("%d\n", ians);
  }
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
