#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <map>
#include <set>
#include <utility>

using namespace std;


struct SegmentNode
{
    int l, r;
    int delta;
    int sum;
    
    SegmentNode* ls, *rs;
  
    SegmentNode(int nowl, int nowr)
    {
        l = nowl;
        r = nowr;
        delta = 0;
        sum = 0;
        ls = rs = NULL;
        
        if (l == r) return;
        int mid = (l + r) / 2;
        ls = new SegmentNode(l, mid);
        rs = new SegmentNode(mid + 1, r);
    }
    
    void update(int nowl, int nowr, int d)
    {
        if (nowl <= l && r <= nowr)
            delta += d;
        else
        {
            int mid = (l + r) / 2;
            if (nowl <= mid) ls->update(nowl, nowr, d);
            if (nowr >= mid + 1) rs->update(nowl, nowr, d);
        }
        if (delta > 0)
            sum = r - l + 1;
        else
        {
            sum = 0;
            if (ls != NULL) sum += ls->sum;
            if (rs != NULL) sum += rs->sum;
        }
    }
};

/**
 x[0] = X
 y[0] = Y
 x[i] = (x[i - 1] * a + y[i - 1] * b + 1) % W (for 0 < i < N)
 y[i] = (x[i - 1] * c + y[i - 1] * d + 1) % H (for 0 < i < N)
 Peter connects his monitor to his computer and opens an image with dimension P (width) * Q (height). How many unique positions can the image be placed so that it can be displayed perfectly (i.e. all pixels of the picture are shown on the monitor)? The image cannot be rotated.
 
 Input
 The first line contains an integer T, which is the number of test cases. Then T test cases follow. 
 Each test case contains 11 integers W, H, P, Q, N, X, Y, a, b, c, d.
 */

int W, H, P, Q, N, X, Y;
int a, b, c, d;
vector<int> x;
vector<int> y;
void readProblem()
{
    cin >> W >> H >> P >> Q >> N >> X >> Y;
    cin >> a >> b >> c >> d;
    x.resize(N);
    y.resize(N);
    x[0] = X;
    y[0] = Y;
    for (int i = 1; i < N; ++i)
    {
        x[i] = (x[i - 1] * a + y[i - 1] * b + 1) % W;
        y[i] = (x[i - 1] * c + y[i - 1] * d + 1) % H;
    }
}

struct Segment
{
    int y;
    int x1, x2;
    bool isOpen;
    Segment(int _y, int _x1, int _x2, bool open)
    {
        y = _y;
        x1 = _x1;
        x2 = _x2;
        isOpen = open;
    }
    
    bool operator < (const Segment& seg) const
    {
        return y < seg.y;
    }
    
    friend ostream& operator << (ostream& out, const Segment& seg)
    {
        out << seg.y << " [" << seg.x1 << ", " << seg.x2 << "] " << (seg.isOpen ? "(" : ")");
        return out;
    }
};

inline void checkrange(int& nowx, int& nowy, int minx, int miny, int maxx, int maxy)
{
    if (nowx < minx) nowx = minx;
    if (nowy < miny) nowy = miny;
    if (nowx > maxx) nowx = maxx;
    if (nowy > maxy) nowy = maxy;
}

vector<Segment> segs;
int solveProblem()
{
    int ans = (W - P + 1) * (H - Q + 1);
    
    // get rects
    int minx = 0;
    int miny = 0;
    int maxx = W - P;
    int maxy = H - Q;
    segs.clear();
    for (int i = 0; i < N; ++i)
    {
        int rbx = x[i];
        int rby = y[i];
        int lux = rbx - P + 1;
        int luy = rby - Q + 1;
        checkrange(rbx, rby, minx, miny, maxx, maxy);
        checkrange(lux, luy, minx, miny, maxx, maxy);
        
        rby++;
        segs.push_back(Segment(luy, lux, rbx, true));
        segs.push_back(Segment(rby, lux, rbx, false));
    }
    
    // calculate its cover area
    sort(segs.begin(), segs.end());
    
    int coverage = 0;
    SegmentNode* tree = new SegmentNode(1, W + 1);
    for (int i = 0; i < segs.size();)
    {
        int nowy = segs[i].y;
        int j = i;
        while (j < segs.size() && segs[j].y == nowy)
        {
            int sx = segs[j].x1 + 1;
            int ex = segs[j].x2 + 1;
            if (segs[j].isOpen)
                tree->update(sx, ex, 1);
            else
                tree->update(sx, ex, -1);
            j++;
        }
        if (j == segs.size()) break;
        int endy = segs[j].y;
        
        coverage += (endy - nowy) * tree->sum;
        i = j;
    }
    
    // return ans
    return ans - coverage;
}


int main()
{
    freopen("/Users/pigoneand/Desktop/dead_pixels.txt", "r", stdin);
    freopen("/Users/pigoneand/Desktop/dead_pixels.out", "w", stdout);
    
    int tests;
    cin >> tests;
    string line;
    getline(cin, line);
    
    for (int i = 1; i <= tests; ++i)
    {
        cerr << "Running Case: " << i << endl;
        readProblem();
        int ans = solveProblem();
        printf("Case #%d: %d\n", i, ans);
    }
}
