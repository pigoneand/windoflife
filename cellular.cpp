
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
#include <cassert>
#include <iomanip>
using namespace std;

#define DEBUG 1
#define debug1(x) if (DEBUG) cout << #x" = " << x << endl;
#define debug2(x, y) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

template <class T1, class T2>
ostream & operator << (ostream & out, const pair<T1, T2> & p)
{ out << "(" << p.first << "," << p.second << ")"; return out; }

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
ostream & operator << (ostream & out, const map<T1, T2> & m)
{ 
  for (typename map<T1, T2>::const_iterator itr = m.begin(); itr != m.end(); ++itr)
    out << itr->first << "->" << itr->second << " ";
  return out;
}
 
/////// BEGIN CODE //////////////////

int f[10001][2][2];
bool caled[10001][2][2];
int N, M, K;

int getF(int money, int player, int care)
{
    if (caled[money][player][care]) return f[money][player][care];
    caled[money][player][care] = true;
    int& ret = f[money][player][care];
    
    // no budget
    if (money == 0) return ret = 0;
    
    // calculate current grant value
    int maxEarn = 0;
    int enemyEarn = 999999999;
    
    for (int i = 1; i <= K; ++i)
    {
        int gain;
        int enemyGain;
        
        if (money >= i)
        {
            gain = getF(money - i, 1 - player, player) + i;
            enemyGain = getF(money - i, 1 - player, 1 - player);
        }
        else
        {
            gain = M;
            enemyGain = 0;
        }
        
        if (gain > maxEarn || (gain == maxEarn && enemyGain < enemyEarn))
        {
            maxEarn = gain;
            enemyEarn = enemyGain;
        }
    }
    
    if (care == player) return ret = maxEarn; else return ret = enemyEarn;
}

void init()
{
    cin >> N >> M >> K;
    memset(caled, false, sizeof(caled));
}

void york()
{
    cout << getF(N, 0, 0) << " " << getF(N, 0, 1) << endl;
}


int main()
{
    init();
    york();
    
    return 0;
}
