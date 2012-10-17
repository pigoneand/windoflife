#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <limits.h>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Algorithm about primes 
//////////////////////////////////////////////////////////////////////
class Prime 
{
    public:
        /** The Primes */
        vector<int> primes;

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
            return primes.size();
        }
        
        /** Return the factors of the given long long number 
         *  Remember to call GenPrime first 
         */
        map<long long ,int> getFactors(long long N) { 
            map<long long ,int> factors;
            long long root = (long long) sqrt((double)N);
            for(int i = 0 ; N > 1 && i < primes.size() && primes[i] <= root ; ++i) {
                if (N % primes[i] == 0) {
                    factors[ primes[i] ] = 0;
                    while (N % primes[i] == 0)
                       N /= primes[i] , factors[ primes[i] ]++ ; 
                }
            }
            if (N > 1) factors[N] = 1; 
            return factors; 
        }
};

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

int main()
{
    Prime primeAlgo;
    primeAlgo.genPrime(13);
    map<long long , int> factors = primeAlgo.getFactors(100);
    for (int i = 0 ; i < primeAlgo.primes.size() ; ++i)
        cout << primeAlgo.primes[i] << endl;
    for (map<long long , int>::iterator itr = factors.begin() ; 
            itr != factors.end() ; ++itr)
        cout << itr->first << " " << itr->second <<endl;
    return 0;
}
