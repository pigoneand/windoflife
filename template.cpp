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
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <string.h>
#include <sstream>
#include <numeric>
#include <functional>

class Solution {
public:
    
    bool couldTransform(const string& a, const string& b)
    {
        int diff = 0;
        for (unsigned int i = 0; i < a.length(); ++i)
            if (a[i] != b[i]) diff++;
        return diff == 1;
    }
    
    vector<vector<int> > ansPaths;
    vector<int> curPath;
    
    void dfs(int now, int offset, vector<vector<bool> >& p)
    {
        curPath[offset] = now;
        if (offset == 0)
        {
            ansPaths.push_back(curPath);
            return;
        }
        for (int i = 0; i < p[now].size(); ++i)
            if (p[now][i])
                dfs(i, offset - 1, p);
    }
    
    vector<vector<string>> findLadders(string start, string end, set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        /// get all words in dicts, sort and unique it
        dict.insert(start);
        dict.insert(end);
        vector<string> words(dict.begin(), dict.end());
        map<string, int> dictMap;
        for (unsigned int i = 0; i < words.size(); ++i) dictMap[words[i]] = i;
        
        /// get start string and end string offset in dicts
        int N = (int) words.size();
        int startOffset, endOffset;
        for (unsigned int i = 0; i < words.size(); ++i)
        {
            if (words[i] == start) startOffset = i;
            if (words[i] == end) endOffset = i;
        }
        
        /// pre calculate the transform matrix
        vector<vector<int> > adjLinked(N);
        for (int i = 0; i < N; ++i)
        {
            string nowWord = words[i];
            for (int l = 0; l < nowWord.size(); ++l)
            {
                for (char c = 'a'; c <= 'z'; ++c)
                {
                    if (c == words[i][l]) continue;
                    nowWord[l] = c;
                    if (dict.find(nowWord) != dict.end()) adjLinked[i].push_back(dictMap[nowWord]);
                }
                nowWord[l] = words[i][l];
            }
        }
        
        /// previous
        vector<vector<bool> > previous(N, vector<bool>(N, false));
        vector<int> minDis(N, 9999);
        minDis[startOffset] = 1;
        queue<int> q;
        q.push(startOffset);
        
        while (q.size() > 0)
        {
            int now = q.front();
            q.pop();
            
            for (int i = 0; i < adjLinked[now].size(); ++i)
            {
                int adj = adjLinked[now][i];
                if (minDis[now] + 1 < minDis[adj])
                {
                    minDis[adj] = minDis[now] + 1;
                    q.push(adj);
                }
                if (minDis[now] + 1 == minDis[adj])
                    previous[adj][now] = true;
            }
        }
        
        vector<vector<string> > ans;
        if (minDis[endOffset] == 9999) return ans;
        
        ansPaths.clear();
        curPath.assign(minDis[endOffset], 0);
        dfs(endOffset, minDis[endOffset] - 1, previous);
        
        
        for (int i = 0; i < ansPaths.size(); ++i)
        {
            vector<string> s;
            for (int j = 0; j < ansPaths[i].size(); ++j)
                s.push_back(words[ansPaths[i][j]]);
            ans.push_back(s);
        }
        return ans;
    }
};

int main()
{
  return 0;
}
