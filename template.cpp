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

#define DEBUG 1
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

int A, B, N;
struct Seg
{
    int x1, x2, y;
    int order;
    
    Seg(int _x1, int _x2, int _y, int _order) : x1(_x1), x2(_x2), y(_y), order(_order) {}
    
    bool operator < (const Seg& s) const
    {
        return y < s.y;
    }
    
    friend ostream& operator << (ostream& out, const Seg& s)
    {
        out << s.x1 << " " << s.x2 << " " << s.y << " " << s.order;
        return out;
    }
};

vector<int> colors;
vector<Seg> segs;
vector<int> xs;

void init()
{
    cin >> A >> B >> N;
    colors.push_back(0);
    colors.push_back(1);
    segs.push_back(Seg(0, A, 0, 1));
    segs.push_back(Seg(0, A, B, -1));
    int rank = 1;
    
    while (N--)
    {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        rank++;
        colors.push_back(c);
        segs.push_back(Seg(x1, x2, y1, +rank));
        segs.push_back(Seg(x1, x2, y2, -rank));
        xs.push_back(x1);
        xs.push_back(x2);
    }
    xs.push_back(0);
    xs.push_back(A);
    
    sort(segs.begin(), segs.end());
    sort(xs.begin(), xs.end());
    xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
}

void york()
{
    vector<int> ans(2501, 0);
    
    for (int i = 0; i < (int) xs.size() - 1; ++i)
    {
        int x1 = xs[i];
        int x2 = xs[i + 1];
        multiset<int> orders;
        
        int lastY = 0;
        for (int j = 0; j < segs.size(); ++j)
        {
            if (segs[j].x1 <= x1 && x2 <= segs[j].x2)
            {
                int nowY = segs[j].y;
                int area = (nowY - lastY) * (x2 - x1);
                if (area > 0) ans[colors[*orders.rbegin()]] += area;
                if (segs[j].order > 0) orders.insert(segs[j].order);
                else orders.erase(orders.find(-segs[j].order));
                lastY = nowY;
                //debug3(x1, x2, segs[j]);
            }
        }
    }
    
    
    for (int i = 1; i <= 2500; ++i)
        if (ans[i] > 0)
            printf("%d %d\n", i, ans[i]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    init();
    york();
    
    return 0;
}