#include <cstdio>
#include <cstdlib>
#include <map>
#include <stdio.h>
using namespace std;

const long long INFI = 1LL << 60;

struct QueryResult
{
	long long maxSum;
	int maxSumBegin;
	int maxSumLen;

	long long maxLeftSum;
	int maxLeftLen;

	long long maxRightSum;
	int maxRightLen;

	QueryResult()
	{
		maxSum = maxLeftSum = maxRightSum = -INFI;
		maxSumBegin = -1;
		maxSumLen = maxLeftLen = maxRightLen = -1;
	}
};

struct Node
{
	Node * left;
	Node * right;
	int begin, end, mid;

	long long sum;

	long long maxSum;
	int maxSumBegin;
	int maxSumLen;

	long long maxLeftSum;
	int maxLeftLen;

	long long maxRightSum;
	int maxRightLen;

	int nodes;

	void updateInfo()
	{
		sum = left->sum + right->sum;
		nodes = left->nodes + right->nodes;

		maxSum = left->maxSum;
		maxSumBegin = left->maxSumBegin;
		maxSumLen = left->maxSumLen;

		if (right->maxSum > maxSum)
		{
			maxSum = right->maxSum;
			maxSumBegin = right->maxSumBegin;
			maxSumLen = right->maxSumLen;
		}

		if (left->maxRightSum + right->maxLeftSum > maxSum)
		{
			maxSum = left->maxRightSum + right->maxLeftSum;
			maxSumBegin = left->end - left->maxRightLen + 1;
			maxSumLen = left->maxRightLen + right->maxLeftLen;
		}

		maxLeftSum = left->maxLeftSum;
		maxLeftLen = left->maxLeftLen;
		if (left->sum + right->maxLeftSum > maxLeftSum)
		{
			maxLeftSum = left->sum + right->maxLeftSum;
			maxLeftLen = left->end - left->begin + 1 + right->maxLeftLen;
		}

		maxRightSum = right->maxRightSum;
		maxRightLen = right->maxRightLen;
		if (right->sum + left->maxRightSum > maxRightSum)
		{
			maxRightSum = right->sum + left->maxRightSum;
			maxRightLen = right->end - right->begin + 1 + left->maxRightLen;
		}
	}

	void initLeaf(int x)
	{
		sum = x;
		maxSum = x;
		maxSumLen = 1;
		maxSumBegin = begin;
		maxLeftSum = x;
		maxLeftLen = 1;
		maxRightSum = x;
		maxRightLen = 1;
	}

	Node(int l, int r, int * a)
	{
		begin = l;
		end = r;
		left = NULL;
		right = NULL;
		nodes = 0;

		if (l == r)
		{
			initLeaf(a[l]);
			return;
		}

		mid = (l + r) >> 1;
		left = new Node(l, mid, a);
		right = new Node(mid + 1, r, a);

		updateInfo();
	}

	QueryResult query(int l, int r) const 
	{
		QueryResult ret;
		if (r < begin || l > end) 
			return ret;
		if (l <= begin && end <= r)
		{
			ret.maxSum = maxSum;
			ret.maxSumBegin = maxSumBegin;
			ret.maxSumLen = maxSumLen;
			
			ret.maxLeftSum = maxLeftSum;			
			ret.maxLeftLen = maxLeftLen;

			ret.maxRightSum = maxRightSum;
			ret.maxRightLen = maxRightLen;

			return ret;
		}
		
		if (l <= mid && r <= mid)
			return left->query(l, r);
		if (l > mid && r > mid)
			return right->query(l, r);

		const QueryResult & ll = left->query(l, r);
		const QueryResult & rr = right->query(l, r);

		if (l <= begin)
		{
			ret.maxLeftSum = ll.maxLeftSum;
			ret.maxLeftLen = ll.maxLeftLen;
			if (left->sum + rr.maxLeftSum > ret.maxLeftSum)
			{
				ret.maxLeftSum = left->sum + rr.maxLeftSum;
				ret.maxLeftLen = left->end - left->begin + 1 + rr.maxLeftLen;
			}
		}

		if (r >= end)
		{
			ret.maxRightSum = rr.maxRightSum;
			ret.maxRightLen = rr.maxRightLen;
			if (right->sum + ll.maxRightSum > ret.maxRightSum)
			{
				ret.maxRightSum = right->sum + ll.maxRightSum;
				ret.maxRightLen = right->end - right->begin + 1 + ll.maxRightLen;
			}
		}

		ret.maxSum = ll.maxSum;
		ret.maxSumBegin = ll.maxSumBegin;
		ret.maxSumLen = ll.maxSumLen;

		if (rr.maxSum > ret.maxSum)
		{
			ret.maxSum = rr.maxSum;
			ret.maxSumBegin = rr.maxSumBegin;
			ret.maxSumLen = rr.maxSumLen;
		}

		if (ll.maxRightSum + rr.maxLeftSum > ret.maxSum)
		{
			ret.maxSum = ll.maxRightSum + rr.maxLeftSum;
			ret.maxSumBegin = left->end - ll.maxRightLen + 1;
			ret.maxSumLen = ll.maxRightLen + rr.maxLeftLen;
		}

		return ret;
	}

	void modify(int l, int x)
	{
		if (l < begin || l > end) return;
		if (begin == end)
		{
			initLeaf(x);
			return;
		}

		if (l <= mid) 
			left->modify(l, x);
		if (l > mid)
			right->modify(l, x);

		updateInfo();
	}
};

int A[50001];
int N, M;
Node * root;
void init()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);

	root = new Node(1, N, A);
}

void york()
{
	scanf("%d", &M);
	for (int i = 0; i < M; ++i)
	{
		int op, s, e;
		scanf("%d%d%d", &op, &s, &e);
		if (op == 0)
			root->modify(s, e);
		else
		{
			QueryResult ret = root->query(s, e);
			printf("%lld\n", ret.maxSum);
		}
	}
}

int main()
{
	init();
	york();

	return 0;
}
