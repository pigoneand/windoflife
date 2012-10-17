#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define debug1(x) cout << #x" = " << x << endl;
#define debug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;

// eps to find a root
const long double smalleps = 1e-60;

// eps to test whether two root are equal
const long double bigeps = 1e-6;

class Polynomial
{
public:
	// coff[0] a0  coff[N] an * x ^ n
	vector<long double> coff;

	Polynomial(const vector<long double> & _coff)
	{ coff = _coff; }

	Polynomial(int coffs)
	{ coff.resize(coffs); }

	Polynomial()
	{ ; }

	void refine()
	{
		while (coff.size() > 0 && fabs(coff[coff.size() - 1]) < smalleps)
			coff.pop_back();
	}

	Polynomial qiudiao() const
	{
		if (coff.size() == 0) return Polynomial();
		Polynomial ret(coff.size() - 1);
		for (int i = 0; i < ret.coff.size(); ++i)
			ret.coff[i] = coff[i + 1] * (i + 1);
		ret.refine();
		return ret;
	}

	long double func(long double x) const
	{
		long double ret = 0;
		for (int i = coff.size() - 1; i >= 0; --i)
			ret = ret * x + coff[i];
		return ret;
	}

	// given f and its derivative f_, and a init x0, return its newton_iteration result to find a root 
	static bool newton_root(long double x0, const Polynomial & f, const Polynomial & f_, long double & root)
	{
		root = x0;
		long double nf, nf_;
		int iter = 0;
		while (fabs(nf = f.func(root)) > smalleps)
		{
			nf_ = f_.func(root);
			if (fabs(nf_) < smalleps) return false;
			root = root - nf / nf_;

			iter++;
			if (iter >= 128) return false;
		}
		return true;
	}

	// after we find a root of a polynomial, use this method to determine its multiple
	static int findRootMultiple(long double x, const Polynomial & f)
	{
		int ret = 1;
		Polynomial now = f;
		double zeroeps = 1e-6;
		while (true)
		{
			now = now.qiudiao();
			if (now.coff.size() == 0) break;
			long double nowf = now.func(x);
			if (fabs(nowf) < zeroeps) ret++;	else 	break;
			zeroeps *= 4;
		}
		return ret;
	}

	static vector<long double> findAllRoots(const Polynomial & f)
	{
		vector<long double> ret;
		Polynomial f_ = f.qiudiao();

		long double minRoot = -200.0;
		long double maxRoot = 200.0;
	
		for (int iter = 0; iter <= 1000; ++iter)
		{
			//cout << iter << endl;
			long double x0 = (long double) rand() / (long double) RAND_MAX;
			x0 = minRoot + (maxRoot - minRoot) * x0;
			long double root;
			bool findRoot = newton_root(x0, f, f_, root);

			if (findRoot)
			{
				bool newroot = true;
				for (int i = 0; i < ret.size(); ++i)
					if (fabs(ret[i] - root) < bigeps)
						newroot = false;

				if (newroot)
				{
					int multi = findRootMultiple(root, f);
					vector<long double> newroots(multi, root);
					ret.insert(ret.end(), newroots.begin(), newroots.end());
				}
			}
		}

		sort(ret.begin(), ret.end());
		return ret;
	}
};

Polynomial poly;
Polynomial poly_;
int N;

void york()
{
	vector<long double> roots = Polynomial::findAllRoots(poly);
	for (int i = 0; i < roots.size(); ++i)
		printf("%.8f\n", roots[i]);
}

void init()
{
	cin >> N;
	poly.coff.resize(N + 1);
	for (int i = N; i >= 0; --i)
		cin >> poly.coff[i];

	poly_ = poly.qiudiao();
}

int main()
{
	init();
	york();
	return 0;
}
