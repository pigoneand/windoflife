#include <utility>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
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

  int pivot = data[left];
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

/** Quicksort the array[rangeStart, rangeStop] order by data increment */
template <class T>
int quick_sort(vector<T> & data, int rangeStart, int rangeStop)
{
  if (rangeStart < rangeStop)
  {
    int mid = partition(data, rangeStart, rangeStop);
    quick_sort(data, rangeStart, mid - 1);
    quick_sort(data, mid + 1, rangeStop);
  }
}

/** Simple find the k-th smallest data in the array, return the data and the index */
template <class T> 
inline pair<T, int> getMedian(vector<T> & data, int rangeStart, int rangeStop, int k)
{
  sort(data.begin() + rangeStart, data.begin() + rangeStop + 1);
  return make_pair(data[rangeStart + k - 1], rangeStart + k - 1);
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

/** Select k-th smallest of array[rangeStart, rangeStop]
 * Using algorithm 5-median O(n) algorithm 
 * Remember this procedure would change the array 
 */
template <class T>
pair<T, int> select_k_5(vector<T> & data, int rangeStart, int rangeStop, int k)
{
  if (rangeStart > rangeStop - 5) 
    return getMedian(data, rangeStart, rangeStop, k);

  int groups = (rangeStop - rangeStart + 1) / 5;
  vector<T> medians;
  for (int i = 0; i < groups; ++i)
    medians.push_back(getMedian(data, rangeStart + i * 5, rangeStart + i * 5 + 4, 3).first);
  
  pair<T, int> mid = select_k_5(medians, 0, medians.size() - 1, medians.size() / 2 + 1);

  int midPartPosi = partition(data, rangeStart, rangeStop, mid.second * 5 + rangeStart + 2);
  int leftPartSize = midPartPosi - rangeStart + 1;
  if (leftPartSize == k)
    return make_pair(data[midPartPosi], midPartPosi);
  else
  {
    if (leftPartSize < k)
      return select_k_5(data, midPartPosi + 1, rangeStop, k - leftPartSize);
    else
      return select_k_5(data, rangeStart, midPartPosi - 1, k);
  }
}

int main()
{
  /** Test quicksort performance */
  double sort1Time = 0.0;
  double sort2Time = 0.0;
  double selectKTime = 0.0;
  double selectK2Time = 0.0;

  for (int j = 0; j < 100; ++j) {
    int N = j * 1000 + 1;

    vector<int> test;
    if (j % 10 == 0)
    {
      for (int i = 0; i < N; ++i)
        test.push_back(i);
    }
    else
    {
      for (int i = 0; i < N; ++i) 
        test.push_back(rand() % 100000);
    }

    vector<int> test1 = test;
    vector<int> test2 = test;
    vector<int> test3 = test;
    vector<int> test4 = test;
    cout << N << "\t"; 

    clock_t start = clock();
    sort(test1.begin(), test1.end());
    clock_t stop = clock();
    cout << (double)(stop - start) / CLOCKS_PER_SEC << "\t";
    sort1Time += (double)(stop - start) / CLOCKS_PER_SEC;

    start = clock();
    quick_sort(test2, 0, test2.size() - 1);
    stop = clock();
    cout << (double)(stop - start) / CLOCKS_PER_SEC << "\t";
    sort2Time += (double)(stop - start) / CLOCKS_PER_SEC;


    for (int k = 0; k < test1.size(); ++k)
      if (test1[k] != test2[k])
      {
        cerr << "sort error" << endl;
        exit(0);
      }

    int delta = test1.size() / 100 + 1;
    start = clock();
    for (int k = 0; k < test1.size(); k += delta)
    {
      if (test1[k] != select_k(test3, 0, test3.size() - 1, k + 1).first)
      {
        cerr << "error_k" << endl;
        exit(0);
      }
    }
    stop = clock();
    cout << (double)(stop - start) / CLOCKS_PER_SEC << "\t";
    selectKTime += (double)(stop - start) / CLOCKS_PER_SEC;

    start = clock();
    for (int k = 0; k < test1.size(); k += delta)
    {
      if (test1[k] != select_k_5(test4, 0, test4.size() - 1, k + 1).first)
      {
        cerr << "error_k" << endl;
        exit(0);
      }
    }
    stop = clock();
    cout << (double)(stop - start) / CLOCKS_PER_SEC << endl;
    selectK2Time += (double)(stop - start) / CLOCKS_PER_SEC;
  }
  cout << "ok" << endl;
  cout << sort1Time << "\t" << sort2Time << endl;
  cout << selectKTime << endl;
  cout << selectK2Time << endl;
  return 0;
}
