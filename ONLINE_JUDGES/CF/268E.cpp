#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

const double eps = 1e-6;
int N;
vector<double> l;
vector<double> p;

void ReadProblem()
{
    scanf("%d", &N);
    l.resize(N);
    p.resize(N);
    
    for (int i = 0; i < N; ++i)
    {
        scanf("%lf%lf", &l[i], &p[i]);
        p[i] /= 100;
    }
}

void SolveProblem()
{
    vector<pair<double, int> > rank;
    for (int i = 0; i < N; ++i)
    {
        if (p[i] >= 1.0 - eps)
            rank.push_back(make_pair(1e10, i));
        else
            rank.push_back(make_pair(p[i] / (1 - p[i]) * l[i], i));
    }
    sort(rank.begin(), rank.end(), greater<pair<double, int> >());
    
    double ans = 0;
    double El = 0;
    for (int offset = 0; offset < rank.size(); ++offset)
    {
        int i = rank[offset].second;
        double Ei = p[i] * l[i] + (1 - p[i]) * (l[i] + El);
        ans += Ei;
        El += p[i] * l[i];
    }
    printf("%.10f\n", ans);
}

int main()
{
    ReadProblem();
    SolveProblem();
    return 0;
}