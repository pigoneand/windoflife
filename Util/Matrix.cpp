#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

const double eps = 1e-8;
const long long moder = 1000000007;

/** 
 * @warning gcd(2, -3) = -1
 */
long long gcd(long long x, long long y)
{
  if (!x || !y) return x > y ? x : y;
  for (long long t; t = x % y; x = y, y = t);
  return y;
}

/** 
 * ax + by = gcd(a, b)
 * x, y may be negative 
 */
long long extgcd(long long a, long long b, long long & x, long long & y)
{
  if (b == 0) { x = 1; y = 0; return a; }
  long long d = extgcd(b, a % b, x, y);
  long long t = x; x = y; y = t - a / b * y;
  return d;
}

/** 
 * a * x mod p = 1 , (a,p) = 1
 */
long long getReverse(long long a, long long p)
{
	if (a == 1) return 1;
	long long x, y;
	extgcd(a, p, x, y);
	return (x % p + p) % p;
}

struct Unit
{
	long long x;
	Unit(long long _x) { x = ((_x) % moder + moder) % moder; }
	Unit() { x = 0; }

	Unit operator + (Unit & other) { return Unit(x + other.x); }
	Unit operator - (Unit & other) { return Unit(x - other.x); }
	Unit operator * (Unit & other) { return Unit(x * other.x); }
	Unit operator / (Unit & other) { return Unit(x * getReverse(other.x, moder)); }
	Unit & operator += (Unit & other) { *this = *this + other; return *this; }
	Unit & operator -= (Unit & other) { *this = *this - other; return *this; }

	friend ostream & operator << (ostream & out, const Unit & unit)
	{ out << unit.x; return out; }
};

template <class T>
struct Matrix
{
	static Matrix<T> getNormal(int R) {
		Matrix<T> ret(R,R);
		for (int i = 0; i < R; ++i)
			ret.data[i][i] = 1;
		return ret;
	}

	int R, C;
	vector<vector<T> > data;

	Matrix(int r,int c) 
	{
		R = r;
		C = c;
		data = vector<vector<T> >(R, vector<T>(C, 0));
	}

	Matrix(const Matrix & x) 
	{
		R = x.R;
		C = x.C;
		data = x.data;
	}

	Matrix()
	{
	}

	/** swap two row in this matrix */
	void swapRow(int r1, int r2)
	{
		if (r1 == r2 || r1 >= R || r2 >= R) return;
		for (int j = 0; j < C; ++j)
			swap(data[r1][j], data[r2][j]);
	}

	/** swap two column in this matrix */
	void swapCol(int c1, int c2)
	{
		if (c1 == c2 || c1 >= C || c2 >= C) return;
		for (int i = 0; i < R; ++i)
			swap(data[i][c1], data[i][c2]);
	}

	/** subtract row2 = row2 - k * row1 */
	void subtractRowIFromRowJ(int r1, int r2, T k)
	{
		if (r1 == r2 || r1 >= R || r2 >= R) return;
		for (int j = 0; j < C; ++j)
			data[r2][j] -= data[r1][j] * k;
	}

	bool isZero()
	{
		for (int i = 0; i < R; ++i)
			for (int j = 0; j < C; ++j)
				if (fabs(data[i][j]) > eps)
					return false;
		return true;
	}

	bool isZeroRow(int r)
	{
		for (int j = 0; j < C; ++j)
			if (fabs(data[r][j]) > eps)
				return false;
		return true;
	}

	/** merge this matrix with matrix right */
	Matrix<T> rightMergeMatrix(Matrix<T> & right)
	{
		if (right.R != R) 
			return (*this);

		Matrix<T> newMatrix(R, C + right.C);
		for (int i = 0; i < R; ++i)
			for (int j = 0; j < newMatrix.C; ++j)
				if (j < C)
					newMatrix.data[i][j] = data[i][j];
				else
					newMatrix.data[i][j] = right.data[i][j - C];
		return newMatrix;
	}

	/** do Gaussian Elimination on this matrix 
	* As explained above, Gaussian elimination writes a given m × n matrix A 
	* uniquely as a product of an invertible m × m matrix S and a row-echelon matrix T. 
	* Here, S is the product of the matrices corresponding to the row operations performed.
	* The formal algorithm to compute T from A follows. We write A[i,j] for the entry in row i, 
	* column j in matrix A. 
	* The transformation is performed in place, 
	* meaning that the original matrix A is lost and successively replaced by T.
	* @side effect matrix will change 
	*/
	void gaussianElimination()
	{
		int i = 0;
		int j = 0;
		while (i < R && j < C)
		{
			int maxi = i;
			for (int k = i + 1; k < R; ++k)
				if (fabs(data[k][j]) > fabs(data[maxi][j]))
					maxi = k;

			if (fabs(data[maxi][j]) > eps)
			{
				/** swap rows i and maxi, but do not change the value of i 
				* Now A[i,j] will contain the old value of A[maxi,j]. 
				* divide each entry in row i by A[i,j] 
				* Now A[i,j] will have the value 1.  
				*/
				swapRow(i, maxi);
				T divide = data[i][j];
				for (int v = 0; v < C; ++v)
					data[i][v] /= divide;

				/** subtract A[u,j] * row i from row u 
				* Now A[u,j] will be 0, since A[u,j] - A[i,j] * A[u,j] = A[u,j] - 1 * A[u,j] = 0.
				*/
				for (int u = 0; u < R; ++u)
					subtractRowIFromRowJ(i, u, data[u][j]);

				i++;
			}
			j++;
		}
	}

	/** Return the rank of this matrix 
	* @side effect the matrix will change
	*/
	int rank()
	{
		gaussianElimination();
		int ret = 0;
		for (int i = 0; i < R; ++i)
			if (!isZeroRow(i))
				ret++;
		return ret;
	}
};

template <class T>
ostream & operator << (ostream & out , Matrix<T> & a)
{
	for (int i = 0; i < a.R; ++i) {
		for (int j = 0; j < a.C; ++j)
			out << a.data[i][j] << "\t";
		out << endl;
	}
	return out;
}

template <class T>
Matrix<T> operator + (Matrix<T> & a , Matrix<T> & b)
{
	assert(a.R == b.R);
	assert(a.C == b.C);

	Matrix<T> ret(a.R , a.C);
	for (int i = 0; i < ret.R; ++i)
		for (int j = 0; j < ret.C; ++j)
			ret.data[i][j] = a.data[i][j] + b.data[i][j];
	return ret;
}

template <class T>
Matrix<T> operator - (Matrix<T> & a , Matrix<T> & b)
{
	assert(a.R == b.R);
	assert(a.C == b.C);

	Matrix<T> ret(a.R , a.C);
	for (int i = 0; i < ret.R; ++i)
		for (int j = 0; j < ret.C; ++j)
			ret.data[i][j] = a.data[i][j] - b.data[i][j];
	return ret;
}

template <class T>
Matrix<T> operator * (Matrix<T> & a , double x)
{
	Matrix<T> ret(a.R , a.C);
	for (int i = 0; i < ret.R; ++i)
		for (int j = 0; j < ret.C; ++j)
			ret.data[i][j] = a.data[i][j] * x;
	return ret;
}

template <class T>
Matrix<T> operator * (Matrix<T> & a , Matrix<T> & b)
{
	assert(a.C == b.R);
	Matrix<T> ret(a.R , b.C);

	for (int i = 0; i < a.R; ++i)
		for (int j = 0; j < b.C; ++j)
			for (int k = 0; k < a.C; ++k)
				ret.data[i][j] = ret.data[i][j] + a.data[i][k] * b.data[k][j];
	return ret;
}

template <class T>
Matrix<T> operator ^ (Matrix<T> & a , int deg)
{
	if (deg == 0)
		return Matrix<T>::getNormal(a.R);
	if (deg == 1) 
		return a;

	int half = deg / 2;
	int remain = deg - half * 2;
	Matrix<T> tmp = a ^ half;
	if (remain) 
		return tmp * tmp * a;
	else
		return tmp * tmp;
}

template <class T>
Matrix<T> power(Matrix<T> & a , unsigned long long deg)
{
	if (deg == 0) return Matrix<T>::getNormal(a.R);
	if (deg == 1) return a;

	Matrix<T> ret = Matrix<T>::getNormal(a.R);
	for (int i = 60; i >= 0; --i)
	{
		ret = ret * ret;
		if (deg & (1ULL << i))
			ret = ret * a;
		//normal(ret);
	}
	return ret;
}

template <class T>
/** N <= 10^9 */
Matrix<T> miji(Matrix<T> & A, int N)
{
	static vector<Matrix<T> > powers;
	static bool first = true;
	if (first)
	{
		first = false;
		powers.resize(32);
		powers[0] = A;
		for (int i = 1; i < 32; ++i)
			powers[i] = powers[i - 1] * powers[i - 1];
	}

	Matrix<T> E = Matrix<T>::getNormal(A.R);
	Matrix<T> Zero = Matrix<T>(A.R, A.R);
	if (N < 0) return Zero;
	if (N == 0) return E;
	if (N == 1) return E + A;
	int upper = 1;
	for (int i = 1; i < 31; ++i)
		if (N >= ((1 << i) - 1))
			upper = i;

	Matrix<T> ret = E;
	for (int i = 0; i < upper; ++i)
		ret = ret * (E + powers[i]);
	ret = ret + powers[upper] * miji(A, N - (1 << upper));
	return ret;
}

/** 
* Return the inverse of this matrix
*/
template <class T>
bool inverseMatrix(Matrix<T> & a)
{
	vector<int> is(a.R, 0);
	vector<int> js(a.R, 0);
	T t;
	if (a.R != a.C) 
		return false;

	for (int k = 0; k < a.R; k++) 
	{
		t = 0;
		for (int i = k; i < a.R; i++)
			for (int j = k; j < a.R; j++)
				if (fabs(a.data[i][j]) > t)
					t = fabs(a.data[is[k] = i][js[k] = j]);

		if (fabs(t) < eps) return false;

		if (is[k] != k) a.swapRow(k, is[k]);
		if (js[k] != k) a.swapCol(k, js[k]);

		a.data[k][k] = 1 / a.data[k][k];
		for (int j = 0; j < a.R; j++)
			if (j != k) a.data[k][j] *= a.data[k][k];

		for (int i = 0; i < a.R; i++) if (i != k)
			for (int j = 0; j < a.R; j++) if (j != k)
				a.data[i][j] -= a.data[i][k] * a.data[k][j];

		for (int i = 0; i < a.R; i++)
			if (i != k) a.data[i][k] *= -a.data[k][k];
	}

	for (int k = a.R - 1; k >= 0; k--){
		for (int j = 0; j < a.R; j++)
			if (js[k] != k)
				t = a.data[k][j], a.data[k][j] = a.data[js[k]][j], a.data[js[k]][j] = t;
		for (int i = 0; i < a.R; i++)
			if (is[k] != k)
				t = a.data[i][k], a.data[i][k] = a.data[i][is[k]], a.data[i][is[k]] = t;
	}
	return true;
}

/** Solve linear equation
* A m * n matrix 
* b m * 1 vector
* @return n * 1 solution
*/
template <class T>
Matrix<T> solveEquation(Matrix<T> & A, Matrix<T> & b, int & solutions)
{
	Matrix<T> nA = A;
	Matrix<T> zA = A.rightMergeMatrix(b);
	Matrix<T> ret(A.C, 1);

	int rank1 = nA.rank();
	int rank2 = zA.rank();

	if (rank1 != rank2)
	{
		solutions = 0;
		return ret;
	}

	if (rank1 < A.R)
		solutions = 2;
	else
		solutions = 1;

	/** cal the solution */
	for (int i = zA.R - 1; i >= 0; --i)
	{
		if (zA.isZeroRow(i)) continue;
		T nowB = zA.data[i][zA.C - 1];
		for (int j = 0; j < zA.C - 1; ++j)
			if (fabs(zA.data[i][j]) > 0)
			{
				ret.data[j][0] = nowB / zA.data[i][j];
				break;
			}
	}

	return ret;
}

/** 
* Return the det of this matrix, 
* ensure that the this is a square matrix
* @see side effect matrix will change
*/
template <class T>
T det(Matrix<T> & a)
{
	T ret = 1;
	int sign = 0;

	int i, j, k;
	T t;
	for (i = 0; i < a.R; i++)
	{
		if (a.data[i][i] == 0)
		{
			for (j = i + 1; j < a.R; j++)
				if (a.data[j][i] != 0)
					break;
			if (j == a.R)
				return 0;
			for (k = i; k < a.R; k++)
				t = a.data[i][k], a.data[i][k] = a.data[j][k], a.data[j][k] = t;
			sign++;
		}

		/** if we could find leading one or negative one in this colume, swap */
		for (j = i + 1; j < a.R; ++j)
			if (a.data[j][i] == 1 || a.data[j][i] == -1)
			{
				for (k = i; k < a.R; ++k)
					t = a.data[i][k], a.data[i][k] = a.data[j][k], a.data[j][k] = t;
				sign++;
				break;
			}

			ret = ret * a.data[i][i];
			for (k = i + 1; k < a.R; k++)
				a.data[i][k] = a.data[i][k] / a.data[i][i];

			for (j = i + 1; j < a.R; j++)
			{
				for (k = i + 1; k < a.R; k++)
					a.data[j][k] = a.data[j][k] - a.data[j][i] * a.data[i][k];
				a.data[j][i] = 0;
			}
	}
	if (sign & 1)
		ret = -ret;
	return ret;
}

/**
* In numerical linear algebra, the tridiagonal matrix algorithm (TDMA), 
* also known as the Thomas algorithm (named after Llewellyn Thomas), 
* is a simplified form of Gaussian elimination that can be used to solve tridiagonal systems of equations. 
* A tridiagonal system for n unknowns may be written as
* a_i x_{i - 1} + b_i x_i + c_i x_{i + 1} = d_i , \,\!
* b0 c0
* a1 b1 c1
* 0   a2 b2 c2
* .........................
*          an-2 bn-2 cn-2
*                  an-1 bn-1
*/
vector<double> solveTriDiagonal(vector<double> a, vector<double> b, vector<double> c, vector<double> d)
{
	int N = a.size();
	vector<double> x(N, 0);

	c[0] /= b[0];
	d[0] /= b[0];
	for (int i = 1; i < N; ++i)
	{
		b[i] -= c[i - 1] * a[i];
		d[i] -= d[i - 1] * a[i];
		c[i] /= b[i];
		d[i] /= b[i];
	}

	x[N - 1] = d[N - 1];
	for (int i = N - 2; i >= 0; --i)
		x[i] = d[i] - c[i] * x[i + 1];
	return x;
}

/** 
*  Given a set of vectors, 
*  return the maximum independent subsets size
*  return the rank of the matrix
*  URAL 1041 AC
*/
void swapRow(vector<vector<long long> > & data, int row1, int row2)
{
	int cols = data[0].size();
	for (int i = 0; i < cols; ++i)
		swap(data[row1][i], data[row2][i]);
}

int getRank(vector<vector<long long> > & data)
{
	int Rows = data.size();
	int Cols = data[0].size();

	for (int i = 0; i < Rows; ++i)
		for (int j = 0; j < Cols; ++j)
			data[i][j] = (data[i][j] + moder) % moder;

	int row = 0;
	int col = 0;
	while (row < Rows && col < Cols)
	{
		int nonzero = -1;
		for (int i = row; i < Rows; ++i)
			if (data[i][col] != 0)
			{
				nonzero = i;
				break;
			}

			if (nonzero != -1)
			{
				if (nonzero != row) swapRow(data, nonzero, row);
				for (int i = row + 1; i < Rows; ++i)
				{
					if (data[i][col] != 0)
					{
						long long lcd = data[row][col] * data[i][col] / gcd(data[row][col], data[i][col]);
						long long a = lcd / data[row][col];
						long long b = lcd / data[i][col];
						for (int j = 0; j < Cols; ++j)
							data[i][j] = ((data[i][j] * b - data[row][j] * a) % moder + moder) % moder;
					}
				}
				row++;
			}
			col++;
	}

	int rank = 0;
	for (int i = 0; i < Rows; ++i)
		for (int j = 0; j < Cols; ++j)
			if (data[i][j] != 0) 
			{
				rank++;
				break;
			}
			return rank;
}

/** 最小二乘法 */
void linearLeastSquare(vector<double> & x, vector<double> & y, double & a, double & b)
{
	double A = 0.0, B = 0.0, C = 0.0, D = 0.0, delta;
	int N = x.size();
	for (int i = 0; i < N; ++i)
	{
		A += x[i] * x[i];
		B += x[i];
		C += x[i] * y[i];
		D += y[i];
	}
	delta=A * N - B * B;
	if (fabs(delta) < 1e-10)
		cerr<<"Error!Divide by zero"<<endl;
	else
	{
		a = ((C * N - B * D) / delta);
		b = ((A * D - C * B) / delta);
	}
}


/** ECNU 1032 */
/**
int main()
{
int N;
while (scanf("%d", &N) == 1)
{
Matrix<double> matrix(N, 26);
Matrix<double> b(N, 1);

vector<bool> app(26, false);
string line;
getline(cin, line);
for (int i = 0; i < N; ++i)
{
getline(cin, line);
string nowStr = "";
for (int j = 0; j < line.size(); ++j)
{
if (line[j] == '=') break;
if (line[j] >= 'A' && line[j] <= 'Z')
{
int varID = line[j] - 'A';
int coff = 1;
if (nowStr != "")
{
if (nowStr == "+")
coff = 1;
else
{
if (nowStr == "-")
coff = -1;
else
sscanf(nowStr.data(), "%d", &coff);
}
}
matrix.data[i][varID] = coff;
nowStr = "";
app[varID] = true;
}
else 
nowStr += string(1, line[j]);
}
int equalChar = line.find("=");
line = line.substr(equalChar + 1);
int nowB = 0;
sscanf(line.data(), "%d", &nowB);
b.data[i][0] = nowB;
}

int ans;
Matrix<double> solution = solveEquation(matrix, b, ans);
if (ans == 1)
{
for (int i = 0; i < 26; ++i)
if (app[i])
printf("%c=%.2lf\n", 'A' + i, solution.data[i][0]);
}
else
cout << "No solution" << endl;

}
return 0;
}
*/

#include <map>
#include <string>
int L, R;
map<string, int> idmap;
char c[4] = {'B', 'R', 'W', 'Y'};
Matrix<Unit> A;
Matrix<Unit> x;
Matrix<Unit> sumM;

void addStr(string pattern)
{
	idmap[pattern] = idmap.size();
}

long long getSum2N(int n)
{
	if (n < 2) return 0;
	Matrix<Unit> ret = miji(A, n - 2);
	Matrix<Unit> s = x * ret;
	Matrix<Unit> sum = s * sumM;
	return sum.data[0][0].x;
}

long long getS(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 4;
	long long ret = 0;
	ret += getSum2N(n);
	if (n % 2 == 0) 
		ret += getSum2N(n / 2);
	else 
		ret += getSum2N((n + 1) / 2);
	ret = ret * getReverse(2, moder) + 4;
	ret %= moder;
	return ret;
}

void init()
{
	cin >> L >> R;
	addStr("BW");
	addStr("BY");
	addStr("RW");
	addStr("RY");
	addStr("WB");
	addStr("WR");
	addStr("YR");
	addStr("YB");
	A = Matrix<Unit>(8, 8);

	for (map<string, int>::iterator itr = idmap.begin(); itr != idmap.end(); ++itr)
	{
		string s = itr->first;
		int id = itr->second;
		for (int i = 0; i < 4; ++i)
		{
			string ss = s + string(1, c[i]);
			if (ss == "BWR" || ss == "BRW" || ss == "WRB" || ss == "WBR" || ss == "RWB" || ss == "RBW") continue;
			string ns = ss.substr(1);
			if (idmap.find(ns) == idmap.end()) continue;
			A.data[id][idmap[ns]] = 1;
			//cout << ss << endl;
		}
	}

	x = Matrix<Unit>(1, 8);
	for (int i = 0; i < 8; ++i)
		x.data[0][i] = 1;

	sumM = Matrix<Unit>(8, 1);
	for (int i = 0; i < 8; ++i)
		sumM.data[i][0] = 1;

	//Matrix<Unit> ans = x * (A ^ 1);
	//cout << ans << endl;
}

void york()
{
	long long r = getS(R);
	long long l = getS(L - 1);
	long long ans = r - l;
	ans = (ans + moder) % moder;
	cout << ans << endl;
}

int main()
{
	init();
	york();

	/**
	Matrix<double> matrix(4, 4);
	int r1[] = {2, -1, 0, 0};
	int r2[] = {-1, 3, 0, -1};
	int r3[] = {0, 0, 2, -1};
	int r4[] = {0, -1, -1, 2};

	matrix.data[0] = vector<double>(r1, r1 + 4);
	matrix.data[1] = vector<double>(r2, r2 + 4);
	matrix.data[2] = vector<double>(r3, r3 + 4);
	matrix.data[3] = vector<double>(r4, r4 + 4);

	cout << matrix << endl;
	Matrix<double> sum(4, 4);
	

	for (int i = 0; i <= 16; ++i)
	{
		sum = sum + (matrix ^ i);
	}
	cout << sum << endl;

	cout << miji(matrix, 16) << endl;
	*/
	return 0;
}
