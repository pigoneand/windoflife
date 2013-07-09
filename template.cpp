
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

const double eps = 1e-6;
const int MAXN = 18;
double prob[1 << MAXN][MAXN][MAXN];
bool caled[1 << MAXN][MAXN][MAXN];
vector<int> ts[1 << MAXN][MAXN];
bool couldAtt[MAXN][MAXN];

double rates[MAXN];
int IQLevel[MAXN];
int N;

inline double beatProb(double r1, double r2)
{
    return r1 / (r1 + r2);
}

/**
 * Current people that still alived is state (binary representation)
 * Current fighter is fighter
 * the probability of people watchID 's survive probability
 */
double getProb(int state, int fighter, int watchID)
{
    /// memorzation 
    if (caled[state][fighter][watchID]) return prob[state][fighter][watchID];
    caled[state][fighter][watchID] = true;
    
    /// simple cases
    double& ret = prob[state][fighter][watchID];
    int nextFighter = (fighter + 1) % N;
    if (state == (1 << watchID)) return ret = 1.0;
    if ((state & (1 << watchID)) == 0) return ret = 0;
    if ((state & (1 << fighter)) == 0) return ret = getProb(state, nextFighter, watchID);
    
    /// calculate reasonable targets for current fighter
    vector<bool> couldAttack(N, false);
    for (int i = 0; i < N; ++i)
        if (state & (1 << i))
            if (couldAtt[fighter][i])
                couldAttack[i] = true;
    
    /// if all the potential enemy is friend, then we have to face them
    int couldCnt = (int) count(couldAttack.begin(), couldAttack.end(), true);
    if (couldCnt == 0)
    {
        for (int i = 0; i < N; ++i)
            if (state & (1 << i))
                couldAttack[i] = true;
    }
    
    /// for each possible enemy, calculte the winning prob
    double maxSurviveProb = -1;
    vector<int>& targets = ts[state][fighter];
    vector<double> winProb(N, -1);
    targets.clear();
    
    for (int i = 0; i < N; ++i)
        if (couldAttack[i])
            {
                double p = beatProb(rates[fighter], rates[i]);
                double nowSurvive = p * getProb(state ^ (1 << i), nextFighter, fighter);
                winProb[i] = nowSurvive;
                if (nowSurvive > maxSurviveProb + eps)
                {
                    maxSurviveProb = nowSurvive;
                    targets.clear();
                }
                
                if (fabs(nowSurvive - maxSurviveProb) < eps)
                    targets.push_back(i);
            }
    
    /// if current fighter has no intelligence, wow
    if (IQLevel[fighter] == 0)
    {
        maxSurviveProb = 0;
        targets.clear();
        for (int i = 0; i < N; ++i)
            if (couldAttack[i])
            {
                targets.push_back(i);
                maxSurviveProb += winProb[i];
            }
        maxSurviveProb /= targets.size();
    }
    
    /// basic greedy strategy
    if (IQLevel[fighter] == 1)
    {
        int minRating = 100000;
        maxSurviveProb = -1;
        targets.clear();
        for (int i = 0; i < N; ++i)
            if (couldAttack[i])
                if (rates[i] < minRating)
                {
                    minRating = rates[i];
                    maxSurviveProb = winProb[i];
                    targets = vector<int>(1, i);
                }
    }
    
    /// calculate current watchID's survive probability
    if (fighter == watchID) return ret = maxSurviveProb;

    ret = 0;
    for (int i = 0; i < targets.size(); ++i)
    {
        int target = targets[i];
        {
            double p = beatProb(rates[fighter], rates[target]);
            if (target == watchID)
                ret += 1.0 / targets.size() * (1 - p) * getProb(state ^ (1 << fighter), nextFighter, watchID);
            else
            {
                ret += 1.0 / targets.size() * p * getProb(state ^ (1 << target), nextFighter, watchID);
                ret += 1.0 / targets.size() * (1 - p) * getProb(state ^ (1 << fighter), nextFighter, watchID);
            }
        }
    }
    
    return ret;
}

vector<double> getWinningProb(vector<double>& ratings, vector<int>& color, vector<int>& IQs)
{
    N = (int) ratings.size();
    
    /// init attack matrix
    memset(couldAtt, false, sizeof(couldAtt));
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            if (color[i] != color[j])
                couldAtt[i][j] = couldAtt[j][i] = true;
    
    /// clear memorzation
    memset(caled, false, sizeof(caled));
    
    memset(IQLevel, 0, sizeof(IQLevel));
    for (int i = 0; i < N; ++i) IQLevel[i] = IQs[i];

    for (int i = 0; i < N; ++i) rates[i] = ratings[i];
    vector<double> ret(N);
    for (int i = 0; i < N; ++i) ret[i] = getProb((1 << N) - 1, 0, i);
    return ret;
}

int main()
{
    N = 10;
    /// init ratings
    vector<double> ratings(N, 100);
    for (int i = 1; i < N; ++i) ratings[i] = 100 + rand() % 41 - 20;
    ratings[3] = 83;
    ratings[8] = 101;
    
    /// init groups
    vector<int> color(N, 1);
    for (int i = 0; i < N; ++i) color[i] = i;
    //color[1] = color[2] = color[3] = color[4] = color[5] = color[6] = color[7];// = color[8]; //; = color[3];
    //color[9] = color[0] = color[8];
    //color[1] = color[2] = color[3] = color[4] = color[5] = color[6] = color[7] = color[8] = color[9];
    //debug1(color);
    
    vector<int> IQ(N, 0);
    IQ[0] = 1;
    
    int watch = 0;
    //for (ratings[watch] = 104; ratings[watch] <= 104; )
    //{
        vector<double> ret = getWinningProb(ratings, color, IQ);
        //cout << ratings[watch] << "\t" << ret[watch] << "\t" << ts[(1 << N) - 1][0] << endl;
        debug1(ratings);
        debug1(IQ);
        cout << setprecision(3);
        debug1(ret);
        debug1(ts[(1 << N) - 1][0]);
        //if (ratings[watch] > 200) ratings[watch] += 5;
        //if (ratings[watch] > 500) ratings[watch] += 5;
        //if (ratings[watch] > 1000) ratings[watch] += 5;
        ratings[watch] += 0.1;
    //}
    
    return 0;
}