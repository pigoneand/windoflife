#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class KMP
{
  public:
    /** 
     * s        :   ^  a  b  a  b  a  c  b
     * next     :   -1 0  0  1  2  3  0  0
     */
    vector<int> getNext(const char * const s, int N)
    {
      vector<int> next(N + 1, -1);
      for (int i = 0; i < N; ++i)
      {
        next[i + 1] = next[i] + 1;
        while (next[i + 1] > 0 && s[i] != s[next[i + 1] - 1])
          next[i + 1] = next[next[i + 1] - 1] + 1;
      }
      return next;
    }

    /** 
     * return the positions that substr appeared in str 
     */
    vector<int> kmp(const char * const str, const char * const substr, int L, int N)
    {
      vector<int> ret;
      vector<int> next = getNext(substr, N);
      int j = 0;
      for (int i = 0; i < L; i++)
        for (;;) 
        {      
          if (str[i] == substr[j]) 
          { 
            j++;        
            if (j == N) {   
              ret.push_back(i - N + 1);
              j = next[j];
            }
            break;
          } 
          else 
            if (j == 0) break;   
            else j = next[j];    
        }
      return ret;
    }
};

int N;
char S[600005];
char T[600005];
int LenS;
int LenT;

void init()
{
  scanf("%d", &N);
  gets(S);
  gets(S);
  gets(T);

  int DN = N + N;
  for (int i = N; i < DN; ++i)
    S[i] = S[i - N];
  S[N + N] = '\0';
}

void deal()
{
  KMP kmp;
  vector<int> posi = kmp.kmp(S, T, N + N, N);
  if (posi.size() > 0)
    cout << (N - posi[0]) % N << endl;
  else
    cout << -1 << endl;
}

int main()
{
  /**
  string str;
  string substr;
  getline(cin, str);
  getline(cin, substr);

  KMP kmp;
  vector<int> ret = kmp.kmp(str.data(), substr.data(), str.length(), substr.length());
  for (int i = 0; i < ret.size(); ++i)
    cout << ret[i] << " ";
  cout << endl;
  */

  init();
  deal();
  return 0;
}


    

