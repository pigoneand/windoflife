/** SGU 199 AC */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;

/** 
 * This class solve the longest increasing subsequence problem 
 * in n lon g 
 */
class LIS
{
  public:
    const static int INFINITE = 2147483647;

    /** 
     * @return the longest increasing subsequence indexes 
     */
    vector<int> getLIS(vector<int> & a)
    {
      int N = a.size();

      /** d[i]表示要得到长度为i的增序列，序列中的最大数(最后一个数）的最小值 */
      vector<int> d(N + 1, 0);
      /** posi[i] 表示得到d[i]所表示的那个数在a中的位置 */
      vector<int> posi(N + 1, -1);
      /** father[i] 表示以a[i]结束的最大序列的前一个数的位置 */
      vector<int> father(N, -1);

      d[0] = -INFINITE;
      posi[0] = -1;

      /** len 最大上升序列的长度 */
      int len = 0;
      for (int i = 0; i < N; ++i)
      {
        /** 如果a[i] >= d[len], 那么可以得到更长的增子序列 */
        if (a[i] > d[len]) 
        {
          d[++len] = a[i];
          posi[len] = i;
          father[i] = posi[len - 1];
        }
        else
        {
          /** 寻找比a[i]小的最大的d[l] */
          int l = 0; 
          int r = len;
          while (r > l + 1)
          {
            int mid = (l + r) >> 1;
            if (d[mid] >= a[i])
              r = mid - 1;
            else
              l = mid;
          }
          if (d[l + 1] < a[i]) l++;

          father[i] = posi[l];
          d[l + 1] = a[i];  
          posi[l + 1] = i;
        }
      }
      
      /** 注意到d[i]并不是最长递增序列，因为d[i]的值会因为之后更小的值而发生变化 */
      vector<int> ret;
      ret.clear();
      int nowPosi = posi[len]; 
      do 
      {
        ret.push_back(nowPosi);
        nowPosi = father[nowPosi];
      } while (nowPosi >= 0);

      vector<int> realRet;
      for (int i = ret.size() - 1; i >= 0; --i)
        realRet.push_back(ret[i]);
      return realRet;;
    }
};

struct node
{
  int first;
  int second;
  int offset;
};


struct classcomp {
  bool operator() (const node & t1, const node & t2) const
  {
    if (t1.first != t2.first)
      return t1.first < t2.first;
    else
      return t1.second > t2.second;
  }
};


int main()
{
  LIS lis;

  int N;
  set<node, classcomp > pairs;
  scanf("%d", &N);
  for (int i = 0; i < N; ++i)
  {
    node newPair;
    scanf("%d%d", &newPair.first, &newPair.second);
    newPair.offset = i + 1;
    pairs.insert(newPair);
  }

  vector<node> final;
  vector<int> p;
  for (set<node>::iterator itr = pairs.begin(); itr != pairs.end(); ++itr)
  {
    final.push_back(*itr);
    p.push_back(itr->second);
  }

  vector<int> ans = lis.getLIS(p);
  printf("%d\n", ans.size());
  for (int i = 0; i < ans.size() - 1; ++i)
    printf("%d ", final[ans[i]].offset);
  printf("%d\n", final[ans[ans.size() - 1]].offset);
  return 0;
}
