#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 Description:
 
 Magician Gandalf unfortunate enough to be surrounded by a group of monsters. 
 In order to resist the attack of the monster, he decided to use the four magic rock around him to form a magic square. 
 In order to form a valid magic square, first of all, the four magic rock must form a square, 
 and secondly, Gandalfthe must stand on the geometric center of the square, which imply the distance from him to any magic rock is equal.
 Given the location of the four ancient rocks, and Gandalf the position, 
 you need to tell Gandalf whether he would be able to resist the attack of the monster or not.
 */

inline int sqr(int x) { return x * x; }

bool isSquare(vector<int>& x, vector<int>& y)
{
    vector<int> dists;
    for (int i = 0; i < 4; ++i)
        for (int j = i + 1; j < 4; ++j)
            dists.push_back(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
    sort(dists.begin(), dists.end());
    return (dists[4] == dists[5]) && (dists[0] == dists[3]) && (dists[4] == 2 * dists[0]);
}

int main()
{
    vector<int> x(4), y(4);
    for (int i = 0; i < 4; ++i)
        cin >> x[i] >> y[i];
    int cx, cy;
    cin >> cx >> cy;
    
    if (isSquare(x, y))
    {
        if ((x[0] + x[1] + x[2] + x[3]) == (4 * cx) && (y[0] + y[1] + y[2] + y[3]) == (4 * cy))
        {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}