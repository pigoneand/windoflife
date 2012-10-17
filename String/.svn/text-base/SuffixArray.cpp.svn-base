#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <algorithm>
#include <queue>
#include <utility>
#include <sstream>
#include <bitset>
#include <stdio.h>
#include <stack>

using namespace std;

#define DEBUG 0
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
/////// BEGIN CODE //////////////////
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstdlib>
#include <map>
#include <set>
#include <utility>
#include <cassert>
using namespace std;

const int MAXSTRLEN = 1001000;

/**
 * RMQ Sparse Table approach
 * Init: O(N log N)
 * Query: O(1)
 */
class RMQ_ST
{
private:
  const static int RMQ_LOGMAX = 21;
  const static int RMQ_MAXN = MAXSTRLEN + 10;
  
  /** the binary len for each int */
  vector<int> intLen;
  
  /** the sparse table */
  int M[RMQ_MAXN][RMQ_LOGMAX];
  
public:
  /** the source value */
  vector<int> value;
  
private:
  int N;
  
  /** return the len of given integer by binary representation */
  inline int getIntLen(int key)
  {
    int len = 0;
    while (key>0)
    {
      len++;
      key >>= 1;
    }
    return len;
  }
  
public:
  RMQ_ST(int n)
  {
    N = n;
    intLen = vector<int>(N);
    value = vector<int>(N);
    
    for (int i = 0; i < N; ++i)
      intLen[i] = getIntLen(i);
  }
  
  inline void setValue(int posi , int value)
  { this->value[posi] = value; }
  
  /** Pre calculate the RMQ array for further query */
  void initRMQ()
  {
    for (int i = 0; i < N; ++i)
      M[i][0] = i;
    for (int j = 1; (1 << j) <= N; ++j)
    {
      int upper = N + 1 - (1 << j);
      int step = 1 << (j - 1);
      for (int i = 0; i < upper; ++i)
      {
        if (value[M[i][j-1]] < value[M[i+step][j-1]])
          M[i][j] = M[i][j-1];
        else
          M[i][j] = M[i+step][j-1];
      }
    }
  }
  
  /** return the min value in the query range */
  int RMQ_value(int start,int stop)
  {
    int k = (stop - start +1);
    k = intLen[k] - 1;
    return min(value[M[start][k]] , value[M[stop-(1<<k)+1][k]]);
  }
  
  /** return the min value position in the query range */
  int RMQ_posi(int start,int stop)
  {
    int k = (stop - start + 1);
    k = intLen[k] - 1;
    if (value[M[start][k]] <= value[M[stop-(1<<k)+1][k]]) 
      return M[start][k];
    else 
      return M[stop-(1<<k)+1][k];
  }
};


// SPOJ 705
class SuffixArray
{
public:
  int rankToID[MAXSTRLEN + 10];
  int IDtoRank[MAXSTRLEN + 10];
  int IDtoRank2[MAXSTRLEN + 10];
  
  int sortData[MAXSTRLEN + 10];
  int sortID[MAXSTRLEN + 10];
  int sortRet[MAXSTRLEN + 10];
  int height[MAXSTRLEN + 10];

  int bucketSize[MAXSTRLEN + 10];
  int bucketID[MAXSTRLEN + 10];
  int sumSize[MAXSTRLEN + 10];
  
  RMQ_ST * rmq;
  
  int L;
  string str;
  vector<int> strData;
  
  // ret[i] = i'th rank
  inline void sorting(int * ret)
  {
    int maxKey = 0;

    for (int i = 0; i < L; ++i)
    {
      int key = sortData[i];
      bucketSize[key]++;
      if (key > maxKey) maxKey = key;
    }
    
    int bids = 0;
    for (int i = 0; i <= maxKey; ++i) 
      if (bucketSize[i] > 0)
      {
        bucketID[i] = bids++;
        bucketSize[i] = 0;
      }
    
    for (int i = 0; i < L; ++i)
    {
      int key = sortData[i];
      ret[i] = bucketID[key];
    }
  }

  // ret[i] = rank i ' id
  inline void sorting2(int * ret)
  {
    int maxKey = 0;

    for (int i = 0; i < L; ++i)
    {
      int key = sortData[i];
      bucketSize[key]++;
      if (key > maxKey) maxKey = key;
    }

    sumSize[0] = bucketSize[0];
    for (int i = 1; i <= maxKey; ++i)
      sumSize[i] = sumSize[i - 1] + bucketSize[i];
    
    for (int i = 0; i < L; ++i)
    {
      int key = sortData[i];
      ret[sumSize[key] - bucketSize[key]] = sortID[i];
      bucketSize[key]--;
    }
  }


  /** 
   * rank from 0 to L - 1
   * id from 0 to L - 1
   * @see make sure that the last character in the str is the smallest character 
   */
  void Construct(const string & _str, bool RMQ = true)
  {
    L = (int) _str.length();
    str = _str;
    strData.resize(L);
    for (int i = 0; i < L; ++i) 
      strData[i] = (int) str[i];
    
    memset(rankToID, 0, sizeof(rankToID));
    memset(IDtoRank, 0, sizeof(IDtoRank));
    memset(IDtoRank2, 0, sizeof(IDtoRank2));
    memset(sortRet, 0, sizeof(sortRet));
    memset(height, 0, sizeof(height));
    memset(sortID, 0, sizeof(sortID));
    memset(bucketSize, 0, sizeof(bucketSize));

    sortSuffix();
    calHeight();
    
    if (RMQ)
    {
      rmq = new RMQ_ST(L);
      for (int i = 0; i < L; ++i)
        rmq->setValue(i, height[i]);
      rmq->initRMQ();
    }
  }
  
  void Construct(vector<int> & data, bool RMQ)
  {
    L = (int) data.size();
    str == "";
    strData.resize(L);
    for (int i = 0; i < L; ++i) 
      strData[i] = data[i];
    
    memset(rankToID, 0, sizeof(rankToID));
    memset(IDtoRank, 0, sizeof(IDtoRank));
    memset(IDtoRank2, 0, sizeof(IDtoRank2));
    memset(sortRet, 0, sizeof(sortRet));
    memset(height, 0, sizeof(height));
    memset(sortID, 0, sizeof(sortID));
    
    sortSuffix();
    calHeight();
    
    if (RMQ)
    {
      rmq = new RMQ_ST(L);
      for (int i = 0; i < L; ++i)
        rmq->setValue(i, height[i]);
      rmq->initRMQ();
    }
  }
  
  int getLCS(int l, int r)
  {
    if (l == r) return L - l;
    int rank1 = IDtoRank[l];
    int rank2 = IDtoRank[r];
    if (rank1 > rank2) swap(rank1, rank2);
    return rmq->RMQ_value(rank1 + 1, rank2);
  }
  
  void calHeight()
  {
    int j = 0;
    height[0] = 0;
    for (int i = 0; i < L; ++i)
    {
      int nowID = i;
      int nowRank = IDtoRank[i];
      if (nowRank == 0) continue;
      int lastRank = nowRank - 1;
      int lastID = rankToID[lastRank];
      while (true)
      {
        if (strData[nowID + j] == strData[lastID + j]) 
          j++;
        else 
          break;
      }
      height[nowRank] = j;
      if (j > 0) j--;
    }
  }
  
  void sortSuffix()
  {
    /** init sort each character */
    int k = 1;
    for (int i = 0; i < L; ++i)
      sortData[i]= (int) strData[i];
    sorting(IDtoRank);
    
    /** each step , from k to 2 * k */
    while (true)
    {
      for (int i = 0; i < L; ++i) 
      {
        sortData[i] = IDtoRank[i + k];
        sortID[i] = i;
      }
      sorting2(sortRet);
      
      for (int i = 0; i < L; ++i) {
        int nowID = sortRet[i];
        sortData[i] = IDtoRank[nowID];
        sortID[i] = nowID;
      }
      sorting2(sortRet);
      
      int nowR = 0;
      IDtoRank2[sortRet[0]] = nowR;
      for (int i = 1; i < L; ++i) {
        int nowID = sortRet[i];
        int lastID = sortRet[i - 1];
        if (!(IDtoRank[nowID] == IDtoRank[lastID] && IDtoRank[nowID + k] == IDtoRank[lastID + k]))
          nowR++;
        IDtoRank2[nowID] = nowR;
      }
      
      for (int i = 0; i < L; ++i)
        IDtoRank[i] = IDtoRank2[i];
      
      //debug1(IDtoRank);
      k = k << 1;
      if (k >= L) break;
      if (nowR == L - 1) break;
    }
    
    /** Reverse the id to rank table to get the rank to ID */
    for (int i = 0; i < L; ++i)
      rankToID[IDtoRank[i]] = i;
  }
  
  bool check()
  {
    for (int i = 0; i < L; ++i)
    {
      int nowID  = rankToID[i];
      if (i < L - 1)
      {
        int nextID = rankToID[i + 1];
        string now = str.substr(nowID);
        string next = str.substr(nextID);
        if (now >= next)
          return false;
      }
    }
    
    for (int i = 1; i < L; ++i)
    {
      int nowID = rankToID[i];
      int lastID = rankToID[i - 1];
      string now = str.substr(nowID);
      string last = str.substr(lastID);
      
      int same = 0;
      for (int k = 0; k < now.length() && k < last.length(); ++k)
        if (now[k] == last[k]) 
          same++;
        else
          break;
      
      if (same != height[i]) return false;
    }
    if (height[0] != 0) return false;
    return true;
  }
  
  /** Output the suffix array, also check the correctness */
  friend ostream & operator << (ostream & out, SuffixArray & array)
  {
    cout << "#####Suffix#####" << endl;
    if (array.str.length() > 0)
    {
      for (int i = 0; i < array.L; ++i)
        out << array.str.substr(i) << endl;
    }
    else
    {
      for (int i = 0; i < array.L; ++i)
      {
        for (int j = i; j < array.L; ++j) 
          out << array.strData[j] << " ";
        out << endl;
      }
    }
      
    
    cout << "#####Sorted#####" << endl;
    if (array.str.length() > 0)
    {
      for (int i = 0; i < array.L; ++i)
        out << array.str.substr(array.rankToID[i]) << endl;
    }
    else
    {
      for (int i = 0; i < array.L; ++i)
      {
        for (int j = array.rankToID[i]; j < array.L; ++j)
          out << array.strData[j] << " ";
        out << endl;
      }
    }
    
    return out;
  }
  
  /** Only for debug */
  void outputNowRank(int k)
  {
    vector<vector<string> > ranks(L);
    for (int i = 0; i < L; ++i) {
      cout << IDtoRank[i] << " " << str.substr(i, k) << " ";
      ranks[IDtoRank[i]].push_back(str.substr(i, k));
    }
    cout << endl;
    
    for (int i = 0; i < L; ++i) {
      cout << i << " ";
      for (int j = 0; j < ranks[i].size(); ++j)
        cout << ranks[i][j] << " ";
    }
    cout << endl;
  }
  
};

string getRandomString()
{
  string ret(1000000, 'a');
  for (int i = 0; i < ret.length(); ++i)
    ret[i] = 'a' + rand() % 26;
  return ret;
}


/////////////////////////////////////////////////////
// Rabin - Karp
/////////////////////////////////////////////////////

vector<pair<unsigned long long, unsigned long long> > rabinKarp(vector<int> & v, int L)
{
  vector<pair<unsigned long long, unsigned long long> > ret;
  int N = v.size();
  if (L > N) return ret;

  static vector<unsigned long long> pow1;
  static vector<unsigned long long> pow2;
  static bool first = true;
  if (first)
  {
    first= false;
    pow1.resize(MAXSTRLEN + 10);
    pow2.resize(MAXSTRLEN + 10);
    pow1[0] = 1; pow2[0] = 1;
    for (int i = 1; i <= MAXSTRLEN; ++i)
    {
      pow1[i] = (pow1[i - 1] << 8) + pow1[i - 1];
      pow2[i] = (pow2[i - 1] << 16) + pow2[i - 1];
    }
  }

  unsigned long long h1 = 0;
  unsigned long long h2 = 0;
  for (int i = 0; i < L; ++i)
  {
    h1 += pow1[L - i - 1] * v[i];
    h2 += pow2[L - i - 1] * v[i];
  }
  ret.push_back(make_pair(h1, h2));

  for (int i = L; i < N; ++i)
  {
    h1 = (h1 - pow1[L - 1] * v[i - L]);
    h1 = (h1 << 8) + h1 + v[i];
    h2 = (h2 - pow2[L - 1] * v[i - L]);
    h2 = (h2 << 16) + h2 + v[i];
    ret.push_back(make_pair(h1, h2));
  }
  return ret;
}

vector<pair<unsigned long long, unsigned long long> > rabinKarp(const string & s, int L)
{
  vector<int> v;
  for (int i = 0; i < s.size(); ++i)
    v.push_back(s[i] + 127);

  return rabinKarp(v, L);
}

inline bool isHashMatch(const pair<unsigned long long, unsigned long long> & a,  
  const pair<unsigned long long, unsigned long long> & b)
{
  return a.first == b.first && a.second == b.second;
}

/////////////////////////////////////////////
// Z-algorithm
// Given a string S of length n, the Z Algorithm produces an array Z
// where Z[i] is the length of the longest substring starting from S[i]
// which is also a prefix of S
/////////////////////////////////////////////
vector<int> getZ(vector<int> & v)
{
  int n = (int) v.size();
  vector<int> z(n, 0);

  int L = 0, R = 0;
  for (int i = 1; i < n; i++) {
    if (i > R) {
      L = R = i;
      while (R < n && v[R-L] == v[R]) R++;
      z[i] = R-L; R--;
    } else {
      int k = i-L;
      if (z[k] < R-i+1) z[i] = z[k];
      else {
        L = i;
        while (R < n && v[R-L] == v[R]) R++;
        z[i] = R-L; R--;
      }
    }
  }
  return z;
}

vector<int> getZ(const string & str)
{
  vector<int> v;
  for (int i = 0; i < str.length(); ++i)
    v.push_back(str[i] + 127);
  return getZ(v);
}

/////////////////////////////////////////////////////
// CODE
/////////////////////////////////////////////////////
string s;
vector<int> firstAt;
vector<bool> isFirstOK;
vector<int> lastAt;
vector<int> lastDotCnt;
vector<bool> isLastOK;

void calLastAt()
{
  int N = (int) s.length();
  lastAt.resize(N, -1);
  lastDotCnt.resize(N, 0);
  isLastOK.resize(N, false);
  
  lastAt[N - 1] = N - 1;
  isLastOK[N - 1] = true;
  
  for (int i = N - 2; i >= 0; --i)
  {
    if ((s[i] >= 'a' && s[i] <= 'z') || s[i] == '.')
    {
      lastAt[i] = lastAt[i + 1];
      isLastOK[i] = isLastOK[i + 1];
      lastDotCnt[i] = lastDotCnt[i + 1];
      if (s[i] == '.') lastDotCnt[i]++;
      if (s[i] == '.' && s[i + 1] == '.') 
      {
        isLastOK[i] = true;
        lastAt[i] = i;
        lastDotCnt[i] = 0;
      }
    }
    else
    {
      lastAt[i] = i;
      isLastOK[i] = true;
      lastDotCnt[i] = 0;
    }
  }
  
  debug1(lastAt);
  debug1(isLastOK);
  //cout << lastAt << endl;
  //cout << isLastOK << endl;
}

void calFirstAt()
{
  int N = (int) s.length();
  firstAt.resize(N, -1);
  isFirstOK.resize(N, false);
  
  if (s[N - 1] == '@') { firstAt[N - 1] = N - 1; isFirstOK[N - 1] = true; }
  for (int i = N - 2; i >= 0; --i)
  {
    if (s[i] == '@') 
    {
      firstAt[i] = i;
      isFirstOK[i] = true;
    }
    else
    {
      firstAt[i] = firstAt[i + 1];
      isFirstOK[i] = isFirstOK[i + 1];
      if ((s[i] >= 'a' && s[i] <= 'z') || s[i] == '.')
      {
        if (s[i] == '.' && s[i + 1] == '.') isFirstOK[i] = false;
      }
      else
        isFirstOK[i] = false;
    }
  }
  
  //cout << firstAt << endl;
  //cout << isFirstOK << endl;
}

void init()
{
  s = "";
  string line;
  while (getline(cin, line))
  {
    if (line == "\t") break;
    s.append(line);
    s.append(1, ' ');
  }
 
  for (int i = 0; i < s.length(); ++i)
    if (s[i] >= 'a' && s[i] <= 'z' || s[i] == '.' || s[i] == '@')
      ;
    else
      s[i] = ' ';

  string news = "";
  string now = "";
  bool ok = false;
  for (int i = 0; i < s.length(); ++i)
  {
    if (s[i] == ' ')
    {
      if (now.length() > 0 && ok) { news.append(now); news.append(1, ' '); }
      now = "";
      ok = false;
    }
    else
    {
      now.append(1, s[i]);
      if (s[i] == '@') ok = true;
    }
  }

  s = news;
  s.append(1, '\t');
  debug1(s);
  //cout << s << endl;
}

inline int getDiffSuffix(int posi)
{
  if (!isLastOK[posi]) return 0;
  int lastposi = lastAt[posi];
  int len = lastposi - posi;
  int dots = lastDotCnt[posi];
  return len - dots;
}

void york()
{
  //if (s.length() > MAXSTRLEN) while(1);

  if (s.length() == 0) 
  {
    cout << 0 << endl;
    return;
  }
  
  calFirstAt();
  calLastAt();
  
  SuffixArray * sa = new SuffixArray();
  sa->Construct(s, false);
  
  //cout << *sa << endl;
  
  long long ans = 0;
  int lastSuffixLen = 0;
  int lastPrefixLen = 0;
  for (int i = 1; i < sa->L; ++i)
  {
    int posi = sa->rankToID[i];
    //debug1(s.substr(posi));
    if (s[posi] >= 'a' && s[posi] <= 'z' && isFirstOK[posi])
    {
      int prefixEnd = firstAt[posi] - 1;
      int suffixStart = firstAt[posi] + 1;
      int nowPrefixLen = suffixStart - posi;
      //debug2(nowPrefixLen, lastPrefixLen);
      if (s[suffixStart] >= 'a' && s[suffixStart] <= 'z' && isLastOK[suffixStart] && s[prefixEnd] != '.')
      {
        int suffixEnd = lastAt[suffixStart] - 1;
        int nowSuffixLen = suffixEnd - suffixStart + 1;
        int lcs = sa->height[i];
        if (lcs > nowSuffixLen + nowPrefixLen) lcs = nowSuffixLen + nowPrefixLen;
        if (lcs > lastSuffixLen + lastPrefixLen) lcs = lastSuffixLen + lastPrefixLen;
        
        // common prefix aaa@
        //debug4(nowSuffixLen, lastSuffixLen, lcs, suffixStart);
        if (nowPrefixLen == lastPrefixLen && lcs >= nowPrefixLen)
        {
          int lastsame = posi + lcs - 1;
          if (s[lastsame] == '.') ans += getDiffSuffix(lastsame); else ans += getDiffSuffix(lastsame + 1);
        }
        else
          ans += getDiffSuffix(suffixStart);
        
        lastPrefixLen = nowPrefixLen;
        lastSuffixLen = nowSuffixLen;
        //debug3(posi, s.substr(posi), ans);

        //debug1("-------------");
        //cout << endl;
        continue;
      }
    }
    
    lastSuffixLen = 9999999;
    lastPrefixLen = 0;
  }
  
  cout << ans << endl;
}

int main()
{
  init();
  york();
  return 0;
}