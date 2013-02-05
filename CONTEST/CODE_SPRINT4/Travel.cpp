#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int N;
double C;
double D;
vector<double> prices;
vector<int> x, y;
vector<double> DD;

inline double sqr(double x) { return x * x; }

inline double dist(double x1, double y1, double x2, double y2)
{
    return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

void ReadProblem()
{
    cin >> N >> C >> D;
    prices.resize(N);
    x.resize(N);
    y.resize(N);
    
    for (int i = 0; i < N; ++i)
        cin >> x[i] >> y[i] >> prices[i];
    
    DD.resize(N + 1);
    DD[0] = 1;
    for (int i = 1; i <= N; ++i)
        DD[i] = DD[i - 1] * D;
}

double Evalute(vector<int>& path, int& maxOffset)
{
    double maxprofit = 0;
    int maxProfitOffset = -1;
    
    double profit = 0;
    double nowCarries = 0;
    double lastx = 0;
    double lasty = 0;
    int nowSold = 0;
    int lastCarriesOffset = -1;
    
    int current = 0;
    for (int i = 0; i < path.size(); ++i)
    {
        if (path[i] < 0) lastCarriesOffset = i;
        if (path[i] < 0) current -= path[i]; else current--;
        if (current < 0 && lastCarriesOffset >= 0)
        {
            path[lastCarriesOffset]--;
            current++;
        }
    }
    
    for (int i = 0; i < path.size(); ++i)
    {
        double nowx = 0;
        double nowy = 0;
        if (path[i] >= 0)
        {
            nowx = x[i];
            nowy = y[i];
        }
        
        double travelDist = dist(lastx, lasty, nowx, nowy);
        double travelCost = travelDist * 1.0;
        double carryCost = travelDist * nowCarries * C;
        
        profit -= travelCost;
        profit -= carryCost;
        
        //cout << path[i] << " " << travelCost << " " << carryCost << " ";
        
        if (path[i] < 0)
        {
            nowCarries -= path[i];
        }
        else
        {
            if (nowCarries > 0)
            {
                nowCarries--;
                double nowPrice = prices[path[i]];
                nowPrice *= DD[nowSold];
                //cout << nowPrice << " ";
                profit += nowPrice;
                nowSold++;
            }
            else
                profit -= 1e8;
        }
        
        //cout << profit << endl;
        
        if (profit > maxprofit)
        {
            maxprofit = profit;
            maxProfitOffset = i;
        }
        
        lastx = nowx;
        lasty = nowy;
    }
    maxOffset = maxProfitOffset;
    return maxprofit;
}


void OutputAnsPath(vector<int>& path)
{
    bool isLeavingBase = false;
    int carry = -1;
    
    for (int i = 0; i < path.size(); ++i)
    {
        int nowx = 0;
        int nowy = 0;
        if (path[i] >= 0)
        {
            nowx = x[path[i]];
            nowy = y[path[i]];
        }
        
        if (i > 0)
        {
            cout << nowx << " " << nowy;
            if (isLeavingBase)
            {
                cout << " " << carry << endl;
                isLeavingBase = false;
            }
            else
                cout << endl;
        }
        
        if (path[i] < 0)
        {
            isLeavingBase = true;
            carry = -path[i];
        }
    }
}


void SolveProblem()
{
    srand(time(0));
    
    vector<int> maxPath;
    double maxProfit = 0;
    
    vector<int> curPath;
    for (int i = 0; i < N; ++i)
        curPath.push_back(i);
    
    int SN = sqrt(min(N, 100));
    if (SN == 0) SN = 1;
    
    int valid = 0;
    for (int iter = 0; iter < 40000; ++iter)
    {
        if (iter % 100 == 0)
            random_shuffle(curPath.begin(), curPath.end());
        
        vector<int> nowPath = curPath;
        if (nowPath.size() > 100) nowPath.resize(100);
        
        if (iter < 20000)
        {
            for (int i = 0; i < SN; ++i)
                if (rand() & 1)
                    nowPath.push_back(-1);
            random_shuffle(nowPath.begin(), nowPath.end());
        }
        else
        {
            vector<pair<double, int> > estimateProfits;
            for (int i = 0; i < min(N, 100); ++i)
                estimateProfits.push_back(make_pair((prices[nowPath[i]] * DD[nowPath[i]] - dist(0, 0, x[nowPath[i]], y[nowPath[i]])) * (rand() % 100) / 50.0, nowPath[i]));
            sort(estimateProfits.begin(), estimateProfits.end());
            for (int i = 0; i < min(N, 100); ++i)
            {
                nowPath.push_back(estimateProfits[i].second);
                if (rand() & 1) if (rand() % SN == 0) nowPath.push_back(-1);
            }
        }
        
        nowPath.push_back(-1);
        reverse(nowPath.begin(), nowPath.end());
        
        int maxOffset;
        double nowProfit = Evalute(nowPath, maxOffset);
        if (nowProfit > 0) valid++;
        nowPath.resize(maxOffset + 1);
        if (nowProfit > maxProfit)
        {
            maxProfit = nowProfit;
            maxPath = nowPath;
        }
    }
    
    //cout << "valid = " << valid << endl;
    //cerr << maxProfit << endl;
    OutputAnsPath(maxPath);
}

int main()
{
    ReadProblem();
    SolveProblem();
    return 0;
}
