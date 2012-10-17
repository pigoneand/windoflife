#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdio>

using namespace std;

const int INFI = 2000000000;

class ToySegmentTree
{
public:
	int N;
	vector<int> nums;

	ToySegmentTree(int l, int r)
	{
		N = r - l + 1;
		nums = vector<int>(N, 0);
	}

	void updateRange(int l, int r, int delta)
	{
		for (int i = l; i <= r; ++i)
			nums[i] += delta;
	}

	int queryMax(int l, int r)
	{
		int ret = -INFI;
		for (int i = l; i <= r; ++i)
			ret = max(ret, nums[i]);
		return ret;
	}

	int query(int x)
	{
		return nums[x];
	}
};

class Segment
{
private:
	Segment * left;
	Segment * right;
	int begin, end, mid;

	// delta on this segment
	int totalDelta;

	// maxValue on this segment, initially we assume all the value is zero oh 
	// remember the maxValue is not the actually max value, it just count the information contain 
	// by the subtree of this segment
	int maxValue;

public:
	Segment(int l, int r)
	{
		left = NULL;
		right = NULL;
		begin = l;
		end = r;
		totalDelta = 0;
		maxValue = 0;

		if (begin == end) return;

		mid = begin + (end - begin) / 2;
		left = new Segment(begin, mid);
		right = new Segment(mid + 1, end);
	}

	void updateRange(int l, int r, int delta)
	{
		// no change 
		if (delta == 0) 
			return updateSegment();

		// no intersect 
		if (r < begin || l > end) 
			return updateSegment();

		// totally contain
		if (l <= begin && end <= r) 
		{
			totalDelta += delta;
			return updateSegment();
		}

		// partial intersect
		if (totalDelta != 0)
		{
			left->updateRange(begin, mid, totalDelta);
			right->updateRange(mid + 1, end, totalDelta);
		}
		totalDelta = 0;

		if (l <= mid)
			left->updateRange(l, r, delta);
		if (r >= mid + 1)
			right->updateRange(l, r, delta);

		return updateSegment();
	}

	// update the maintained information of this segment 
	void updateSegment()
	{
		if (begin == end)
		{
			maxValue = totalDelta;
			return;
		}

		maxValue = max(left->maxValue, right->maxValue) + totalDelta;
	}

	// make sure x is in range lo ^_^
	int query(int x) const
	{
		int ret = 0;
		const Segment * now = this;
		while (now != NULL)
		{
			ret += now->totalDelta;
			if (x <= now->mid) 
				now = now->left;
			else
				now = now->right;
		}
		return ret;
	}

	// query the max value in this range 
	int queryMax(int l, int r) const
	{
		if (r < begin || l > end) 
			return -INFI;

		if (l <= begin && end <= r) 
			return maxValue;

		int ret = -INFI;
		if (l <= mid)
			ret = max(ret, left->queryMax(l, r));

		if (r >= mid + 1)
			ret = max(ret, right->queryMax(l, r));
		return ret + totalDelta;
	}

	int queryLastGeqPosi(int value) const
	{
		const Segment * now = this;
		while (now != NULL)
		{
			if (now->begin == now->end) 
				return queryMax(now->begin, now->end) < value ? -1 : now->begin; 

			if (queryMax(now->begin, now->end) < value) 
				return -1;

			if (queryMax(now->mid + 1, now->end) >= value) 
				now = now->right;
			else
				now = now->left;
		}
		return -1;
	}
};

int N;
Segment * root;
vector<int> a;
vector<int> b;

void init()
{
	root = new Segment(1, N);
	a.clear();
	a.resize(N + 1);
	b.clear();
	b.resize(N + 1);
	for (int i = 1; i <= N; ++i)
	{
		int ll, aa, bb;
		scanf("%d%d%d", &ll, &aa, &bb);
		root->updateRange(i, i, ll);
		a[i] = aa;
		b[i] = bb;
	}
}

void york()
{
	int M;
	scanf("%d", &M);
	while (M--)
	{
		//for (int i = 1; i <= N; ++i)
		//	cout << root->query(i) << " ";
		//cout << endl;

		int k;
		scanf("%d", &k);

		int target = root->queryLastGeqPosi(k);
		if (target == -1)
			root->updateRange(1, N, 1);
		else
		{
			int lastLife = root->query(target);
			int nowLife = 1;
			root->updateRange(target, target, 1 - lastLife);
			root->updateRange(a[target], b[target], 1);
		}

		//for (int i = 1; i <= N; ++i)
		//	cout << root->query(i) << " ";
		//cout << endl;
	}

	printf("%d\n", root->queryMax(1, N));
}

int main()
{
	while (scanf("%d", &N) == 1)
	{
		init();
		york();
	}

	return 0;
}