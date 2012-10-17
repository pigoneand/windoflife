#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

/** Partition the array[left, right] into two subarrays around a pivot x such that
 * elements in lower subarray <= x <= elements in the upper subarray
 * Loop Invariant: x      |  <= x  |  >= x  | ?
 *                 left   |  i     |   j    |    right
 */
template <class T>
inline int partition(vector<T> & data, int left, int right, int pivotIndex = -1)
{
  /** Random select the pivot */
  if (pivotIndex == -1)
    pivotIndex = left + rand() % (right - left + 1);
  swap(data[left], data[pivotIndex]);

  T pivot = data[left];
  int i = left;
  for (int j = left + 1; j <= right; ++j)
    if (data[j] <= pivot)
    {
      i++;
      swap(data[i], data[j]);
    }
  swap(data[left], data[i]);
  return i;
}

/** Select k-th smallest of array[rangeStart, rangeStop] 
 * Remember this procecure would change the array !!
 * k start count from 1
 * return: pair<T, int> 
 * T: the k-th data
 * int: the k-th data's offset in the array
 */
template <class T>
pair<T, int> select_k(vector<T> & data, int rangeStart, int rangeStop, int k)
{
  if (rangeStart == rangeStop) 
    return make_pair(data[rangeStart], rangeStart);

  int mid = partition(data, rangeStart, rangeStop);
  int numLeftPart = mid - rangeStart + 1;

  if (numLeftPart == k) 
    return make_pair(data[mid], mid);
  else
  {
    if (numLeftPart < k)
      return select_k(data, mid + 1, rangeStop, k - numLeftPart);
    else
      return select_k(data, rangeStart, mid - 1, k);
  }
}

inline double getSqrDistance(const vector<double> & d1, const vector<double> & d2)
{
	double dis = 0;
	for (unsigned int i = 0; i < d1.size(); ++i)
		dis += (d1[i] - d2[i]) * (d1[i] - d2[i]);
	return dis;
}

inline bool isInterSect(const vector<double> & lower, const vector<double> & upper, 
	const vector<double> & center, double sqrR)
{
	double sqrDis = 0;
	for (unsigned int i = 0; i < lower.size(); ++i)
	{
		double now = 0;
		if (center[i] > upper[i]) now = center[i] - upper[i];
		if (center[i] < lower[i]) now = lower[i] - center[i];
		sqrDis += now * now;
	}

	return sqrDis < sqrR + 1; //+ 2 * (fabs(center[0]) + fabs(center[1]) + fabs(lower[0])
		//+ fabs(lower[1]) + fabs(upper[0]) + fabs(upper[1]));
}

///
// @warning the data must alive 
//
class KDNode
{
public:
	const static int MAXLEAFSIZE = 16;

	vector<double> rectlower;
	vector<double> rectupper;
	KDNode * left, *right;

	short int dim;
	short int splitDim;
	short int depth;
	double splitValue;

	vector<int> leafDataIDs;
	const vector<vector<double> > * alldata;

	KDNode(const vector<vector<double> > * data, const vector<int> & ids, short int _depth = 0)
	{
		alldata = data;
		if (ids.size() == 0) return;

		left = right = NULL;
		splitDim = -1;
		depth = _depth;
		dim = (*alldata)[0].size();
		detectHyperRectangle(ids);

		if (ids.size() <= MAXLEAFSIZE)
		{
			leafDataIDs = ids;
			return;
		}
		else
		{
			vector<int> leftIDs;
			vector<int> rightIDs;

			pair<int, double> ret;
			if (depth <= 3)
				ret = chooseSplitDimAndValue1(ids);
			else 
				ret = chooseSplitDimAndValue2(ids);

			splitDim = ret.first;
			splitValue = ret.second;
			for (unsigned int i = 0; i < ids.size(); ++i)
			{
				if ((*alldata)[ids[i]][splitDim] < splitValue - 1e-6) 
					leftIDs.push_back(ids[i]);
				else
				{
					if ((*alldata)[ids[i]][splitDim] > splitValue + 1e-6)
						rightIDs.push_back(ids[i]);
					else 
					{
						if (leftIDs.size() < rightIDs.size()) 
							leftIDs.push_back(ids[i]);
						else
							rightIDs.push_back(ids[i]);
					}
				}
			}

			if (leftIDs.size() > 0) left = new KDNode(alldata, leftIDs, depth + 1);
			if (rightIDs.size() > 0) right = new KDNode(alldata, rightIDs, depth + 1);
		}
	}

	// detect the range of data 
	void detectHyperRectangle(const vector<int> & ids)
	{
		rectlower = vector<double>(dim, 1e50);
		rectupper = vector<double>(dim, -1e50);
		for (unsigned int i = 0; i < ids.size(); ++i)
			for (int d = 0; d < dim; ++d)
				rectlower[d] = min(rectlower[d], (*alldata)[ids[i]][d]), rectupper[d] = max(rectupper[d], (*alldata)[ids[i]][d]);
	}

	// choose the widest dimension, and choose value closest to the center
	pair<int, double> chooseSplitDimAndValue2(const vector<int> & ids)
	{
		int widestDim = 0;
		for (int i = 1; i < dim; ++i)
			if (rectupper[i] - rectlower[i] > rectupper[widestDim] - rectlower[widestDim])
				widestDim = i;

		double midValue = (rectlower[widestDim] + rectupper[widestDim]) / 2;
		int close = ids[0];
		for (unsigned int i = 1; i < ids.size(); ++i)
			if (fabs((*alldata)[ids[i]][widestDim] - midValue) < fabs((*alldata)[close][widestDim] - midValue))
				close = ids[i];

		return make_pair(widestDim, (*alldata)[close][widestDim]);
	}

	// choose the most spread dimension, and choose its median value
	pair<int, double> chooseSplitDimAndValue1(const vector<int> & ids)
	{
		// cal mean value
		vector<double> meanValue(dim, 0);
		for (unsigned int i = 0; i < ids.size(); ++i)
			for (int d = 0; d < dim; ++d)
				meanValue[d] += (*alldata)[ids[i]][d];

		for (int d = 0; d < dim; ++d)
			meanValue[d] /= ids.size();

		// cal tor value
		vector<double> torValue(dim, 0);
		for (unsigned int i = 0; i < ids.size(); ++i)
			for (int d = 0; d < dim; ++d)
				torValue[d] += ((*alldata)[ids[i]][d] - meanValue[d]) * ((*alldata)[ids[i]][d] - meanValue[d]);

		// choose dim that has maximum tor value
		int chooseDim = 0;
		for (int i = 1; i < dim; ++i)
			if (torValue[i] > torValue[chooseDim])
				chooseDim = i;

		// select the median value in this dim 
		vector<double> valueInChooseDim(ids.size());
		for (unsigned int i = 0; i < ids.size(); ++i)
			valueInChooseDim[i] = (*alldata)[ids[i]][chooseDim];

		pair<double, int> ret = select_k(valueInChooseDim, 0, ids.size() - 1, ids.size() / 2 + 1);
		return make_pair(chooseDim, ret.first);
	}

	friend ostream & operator << (ostream & out, const KDNode * node)
	{
		for (int i = 0; i < node->depth; ++i)
			out << "  ";
		out << node->leafDataIDs.size() << " ";
		out << "[";
		for (unsigned int i = 0; i < node->rectlower.size(); ++i)
			out << node->rectlower[i] << " ";
		out << "] -> ";

		out << "[";
		for (unsigned int i = 0; i < node->rectupper.size(); ++i)
			out << node->rectupper[i] << " ";
		out << "] ";

		out << "sD: " << node->splitDim << " ";
		out << "sV: " << node->splitValue << " ";
		out << endl;

		if (node->left != NULL) out << node->left;
		if (node->right != NULL) out << node->right;

		return out;
	}

	///////////////////////////////////////////////////////////////////
	// operation about search
	///////////////////////////////////////////////////////////////////
	void search(const vector<double> & query, vector<double> & nearest, double & dis, vector<int> & ids) const
	{
		if (!isInterSect(rectlower, rectupper, query, dis)) 
			return;

		// is leaf node
		if (left == NULL && right == NULL)
		{
			for (unsigned int i = 0; i < leafDataIDs.size(); ++i)
			{
				double nowSqrDis = getSqrDistance(query, (*alldata)[leafDataIDs[i]]);
				if (nowSqrDis < dis - 1e-8)
				{
					dis = nowSqrDis;
					nearest = (*alldata)[leafDataIDs[i]];
					ids.clear();
					ids.push_back(leafDataIDs[i]);
				}
				else
				{
					if (nowSqrDis < dis + 1e-8)
						ids.push_back(leafDataIDs[i]);
				}
			}
			return;
		}

		KDNode * first;
		KDNode * second;

		if (query[splitDim] <= splitValue) 
		{
			first = left;
			second = right;
		}
		else
		{
			first = right;
			second = left;
		}

		if (first != NULL)
			first->search(query, nearest, dis, ids);
		if (second != NULL)
			second->search(query, nearest, dis, ids);
	}
};

KDNode * root;
vector<vector<double> > inputData;
void init()
{
	int M;
	scanf("%d", &M);

	inputData = vector<vector<double> >(M, vector<double>(2));
	vector<int> ids(M);

	for (int i = 0; i < M; ++i)
	{
		scanf("%lf %lf", &inputData[i][0], &inputData[i][1]);
		ids[i] = i;
	}

	root = new KDNode(&inputData, ids);
}

void york()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i)
	{
		vector<double> query(2);
		scanf("%lf %lf", &query[0], &query[1]);

		vector<double> nearest(2, 0);
		double dis = 1e50;

		vector<int> ret;

		root->search(query, nearest, dis, ret);
		sort(ret.begin(), ret.end());
		for (unsigned int j = 0; j < ret.size(); ++j)
			printf("%d ", ret[j] + 1);
		printf("\n");
	}
}

int main()
{
	init();
	york();
}

int _main()
{
	time_t start = clock();

	vector<vector<double> > data;
	vector<int> ids;
	for (int i = 0; i < 100000; ++i)
	{
		vector<double> newdata;
		newdata.push_back(rand() * 0.618);
		newdata.push_back(rand() * 0.618);
		data.push_back(newdata);

		ids.push_back(i);
	}

	cout << "begin" << endl;
	KDNode * root = new KDNode(&data, ids);
	cout << "build success" << endl;

	ofstream fout("E:\\kdtree.txt");
	fout << root << endl;
	fout.close();


	for (int i = 0; i < 10000; ++i)
	{
		vector<double> query;
		query.push_back(rand() * 0.618);
		query.push_back(rand() * 0.618);

		vector<double> nearest;
		nearest.push_back(0);
		nearest.push_back(0);

		double dis = 1e20;

		vector<int> ids;

		//cout << query[0] << " " << query[1] << endl;
		root->search(query, nearest, dis, ids);

		
		//cout << dis << " " << ids.size() << " " << nearest[0] << " " << nearest[1] << " ";
		//cout << data[ids[0] - 1][0] << " " << data[ids[0] - 1][1] << endl;

		/**
		double minSqrDis = 1e20;
		int minTar = -1;
		for (unsigned int j = 0; j < data.size(); ++j)
		{
			double nowDis = getSqrDistance(query, data[j]);
			if (nowDis < minSqrDis)
			{
				minSqrDis = nowDis;
				minTar = j;
			}
		}

		//cout << minSqrDis << " " << minTar << " " << data[minTar][0] << " " << data[minTar][1] << " " << endl;

		if (fabs(minSqrDis - dis) > 1e-8)
		{
			system("pause");
		}
		*/
	}

	time_t stop = clock();
	cout << stop - start << endl;
	return 0;
}