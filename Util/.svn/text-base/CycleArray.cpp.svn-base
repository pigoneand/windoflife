#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

/** A class for cycle array, use fixed space step by step to 
 * calculate a large position data 
 */
template <class T> 
class CycleArray
{
  public:
    vector<T> * currentData;
    vector<T> * previousData;
    int preRangeStart;
    int preRangeStop;
    int nowRangeStart;
    int nowRangeStop;
    int capacity;

    CycleArray(int cap)
    {
      capacity = cap;
      currentData = new vector<T>(capacity);
      previousData = new vector<T>(capacity);
      nowRangeStart = 1;
      nowRangeStop = capacity;
      preRangeStop = 0;
      preRangeStart = -capacity + 1;
    }

    T & operator [] (int offset)
    {
      if (offset >= nowRangeStart && offset <= nowRangeStop) 
        return (*currentData)[offset - nowRangeStart];
      if (offset >= preRangeStart && offset <= preRangeStop)
        return (*previousData)[offset - preRangeStart];
      if (offset < preRangeStart) {
        cerr << "offset too small fatal error" << endl;
        exit(0);
      }
      if (offset > nowRangeStop + capacity) {
        cerr << "offset too large fatal error" << endl;
        exit(0);
      }
      preRangeStart = nowRangeStart;
      preRangeStop = nowRangeStop;
      nowRangeStart += capacity;
      nowRangeStop += capacity;
      vector<T> * temp;
      temp = previousData;
      previousData = currentData;
      currentData = temp;
      return (*currentData)[offset - nowRangeStart];
    }
};

int main()
{
  CycleArray<int> f(10);
  f[0] = 1;
  f[1] = 1;
  for (int i = 2; i < 40; ++i) {
    f[i] = f[i - 1] + f[i - 2];
    cout << i << "\t" << f[i] << endl;
  }

  return 0;
}
          

