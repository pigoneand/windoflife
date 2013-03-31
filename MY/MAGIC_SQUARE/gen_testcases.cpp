#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <sstream>
using namespace std;

int randInt(int lower, int upper)
{
    return rand() % (upper - lower + 1) + lower;
}

double randDouble(double lower, double upper)
{
    return 1.0 * rand() / RAND_MAX * (upper - lower) + lower;
}

const int TESTCASES = 30;
const int MAXVALUE = 1000;

void generateTestCases(ostream& out)
{
    vector<int> xs(5, 0), ys(5, 0);
    xs[0] = randInt(0, MAXVALUE);
    ys[0] = randInt(0, MAXVALUE);
    xs[1] = randInt(0, MAXVALUE);
    xs[1] = randInt(0, MAXVALUE);
    
    if (rand() & 1)
    {
        int dx = xs[1] - xs[0];
        int dy = ys[1] - ys[0];
        xs[2] = xs[0] - dy;
        ys[2] = ys[0] + dx;
        xs[3] = xs[1] - dy;
        xs[3] = xs[1] + dx;
        
        xs[4] = (xs[0] + xs[1] + xs[2] + xs[3]) / 4;
        ys[4] = (ys[0] + ys[1] + ys[2] + ys[3]) / 4;
    }
    else
    {
        for (int i = 2; i < 5; ++i)
        {
            xs[i] = randInt(0, MAXVALUE);
            ys[i] = randInt(0, MAXVALUE);
        }
    }
    
    for (int i = 0; i < 5; ++i)
        for (int j = i + 1; j < 5; ++j)
            if (xs[i] == xs[j] && ys[i] == ys[j]) return generateTestCases(out);
    for (int i = 0; i < 5; ++i)
        out << xs[i] << " " << ys[i] << endl;
    return;
}


int main()
{
    for (int i = 1; i <= TESTCASES; ++i)
    {
        ostringstream ostr;
        ostr << i << ".in";
        string inputFileName = ostr.str();
        
        ofstream fout(inputFileName.data());
        generateTestCases(fout);
        fout.close();
    }
    return 0;
}