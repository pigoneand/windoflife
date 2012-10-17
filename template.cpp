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

int main()
{
  init();
  york();
  return 0;
}
