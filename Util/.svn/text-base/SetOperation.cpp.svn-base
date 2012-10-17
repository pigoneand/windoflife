#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;

#define pigoneand_Set__T__ int

set<pigoneand_Set__T__> operator +(const set<pigoneand_Set__T__> & a , const set<pigoneand_Set__T__> & b)
{
    set<pigoneand_Set__T__> ret;
    set<pigoneand_Set__T__>::iterator itr;
    for (itr = a.begin(); itr != a.end(); ++itr) 
        ret.insert(*itr);
    for (itr = b.begin(); itr != b.end(); ++itr)
        ret.insert(*itr);
    return ret;
}

set<pigoneand_Set__T__> operator ^ (const set<pigoneand_Set__T__> & a , const set<pigoneand_Set__T__> & b)
{
    set<pigoneand_Set__T__> ret;
    for (set<pigoneand_Set__T__>::iterator itr = a.begin(); itr != a.end(); ++itr)
        if (b.find(*itr) != b.end())
            ret.insert(*itr);
    return ret;
}

set<pigoneand_Set__T__> operator - (const set<pigoneand_Set__T__> & a , const set<pigoneand_Set__T__> & b) 
{
    set<pigoneand_Set__T__> ret;
    for (set<pigoneand_Set__T__>::iterator itr = a.begin(); itr != a.end(); ++itr)
        if (b.find(*itr) == b.end())
            ret.insert(*itr);
    return ret;
}

/** 
 * Combine two subset's set
 * For Example
 * A = { { 1, 2} , { 1, 3 } }
 * A combine A = { { 1 , 2 , 3} }
 * This function is degisned for apriori algorithm which generate the next
 * frequent subset's set
 */
set<set<pigoneand_Set__T__> > combine(set<set<pigoneand_Set__T__> > & a , set<set<pigoneand_Set__T__> > & b)
{
    set<set<pigoneand_Set__T__> > ret;
    set<set<pigoneand_Set__T__> >::iterator itr1;
    set<set<pigoneand_Set__T__> >::iterator itr2;
    for (itr1 = a.begin(); itr1 != a.end(); ++itr1)
        for (itr2 = b.begin(); itr2 != b.end(); ++itr2) {
            const set<pigoneand_Set__T__> & part1 = (*itr1);
            const set<pigoneand_Set__T__> & part2 = (*itr2);
            set<pigoneand_Set__T__> temp = part1 + part2;
            if ((*itr1).size() == (*itr2).size() && temp.size() == (*itr1).size() + 1)
                ret.insert(temp);
        }
    return ret;
}

/** 
 * Output the set 
 */
ostream & operator<< (ostream & out , const set<pigoneand_Set__T__> & a)
{
    for (set<pigoneand_Set__T__>::iterator itr = a.begin(); itr != a.end(); ++itr) 
        out << (*itr) << " ";
    return out;
}

int main()
{
    set<int> a; 
    a.insert(1);
    a.insert(2);
    set<int> b;
    b.insert(1);
    b.insert(3);

    set<int> c = a + b;
    cout << c << endl;

    c = a ^ b;
    cout << c << endl;

    c = a - b;
    cout << c << endl;

    return 0;
}
