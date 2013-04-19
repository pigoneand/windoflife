//BEGIN CUT HERE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <string.h>
#include <sstream>
using namespace std;
//END CUT HERE

// 0 1
// 2 3
struct State
{
    int link[4];
    int coms[4];
    int maxcom;
    
    State()
    {
        memset(link, 0, sizeof(link));
        memset(coms, 0, sizeof(coms));
        maxcom = 0;
        hashcode = 0;
    }
    
    void merge(int id[], int idsize[], int o1, int o2)
    {
        if (id[o1] == id[o2]) return;
        if (id[o1] == 0 || id[o2] == 0) return;
        
        int newid = min(id[o1], id[o2]);
        int newsize = idsize[o1] + idsize[o2];
        int id1 = id[o1];
        int id2 = id[o2];
        for (int i = 0; i < 8; ++i)
            if (id[i] == id1 || id[i] == id2) { id[i] = newid; idsize[i] = newsize; }
    }
    
    int refine()
    {
        map<int, int> idmap;
        for (int i = 0; i < 4; ++i)
            if (link[i] > 0)
            {
                if (idmap.count(link[i]) == 0)
                {
                    int newid = (int) idmap.size() + 1;
                    idmap[link[i]] = newid;
                }
                link[i] = idmap[link[i]];
            }
        return (int) idmap.size();
    }
    
    int getMaxComSize()
    {
        return maxcom;
    }
    
    vector<State> getNewStates()
    {
        vector<State> ret;
        for (int s = 0; s < 16; ++s)
        {
            State news = *this;
            
            int curID = *max_element(link, link + 4);
            
            int newlink[4];
            for (int i = 0; i < 4; ++i)
                if (s & (1 << i)) newlink[i] = ++curID; else newlink[i] = 0;
            
            int id[8];
            for (int i = 0; i < 4; ++i) id[i] = link[i];
            for (int i = 0; i < 4; ++i) id[i + 4] = newlink[i];
            
            int idsize[8];
            for (int i = 0; i < 4; ++i) idsize[i] = coms[i];
            for (int i = 0; i < 4; ++i) idsize[i + 4] = (newlink[i] == 0 ? 0 : 1);
            
            for (int i = 0; i < 4; ++i) merge(id, idsize, i, i + 4);
            merge(id, idsize, 0 + 4, 1 + 4);
            merge(id, idsize, 0 + 4, 2 + 4);
            merge(id, idsize, 2 + 4, 3 + 4);
            merge(id, idsize, 1 + 4, 3 + 4);
            
            
            for (int i = 0; i < 4; ++i) news.link[i] = id[i + 4];
            for (int i = 0; i < 4; ++i) news.coms[i] = idsize[i + 4];
            news.refine();
            for (int i = 0; i < 8; ++i) news.maxcom = max(news.maxcom, idsize[i]);
            news.gencode();
            ret.push_back(news);
            
        }
        return ret;
    }
    
    long long hashcode;
    int gencode()
    {
        hashcode = 0;
        for (int i = 0; i < 4; ++i)
        {
            hashcode = (hashcode << 4) + link[i];
            hashcode = (hashcode << 8) + coms[i];
        }
        hashcode = (hashcode << 8) + maxcom;
    }
    
    bool operator < (const State & s) const
    {
        return hashcode < s.hashcode;
    }
    
    friend ostream& operator << (ostream& out, const State& s)
    {
        for (int i = 0; i < 4; ++i) out << s.link[i];
        out << "\t";
        for (int i = 0; i < 4; ++i) out << s.coms[i];
        return out;
    }
};

class DynamiteBoxes
{
public:
    
    map<State, double> p[50];
    
    double getProbability(int height, int dangerousClusterSize)
    {
        for (int i = 0; i < 50; ++i) p[i].clear();
        
        State init;
        p[0][init] = 1.0;
        
        for (int h = 0; h < height; ++h)
        {
            for (map<State, double>::iterator itr = p[h].begin(); itr != p[h].end(); ++itr)
            {
                State now = itr->first;
                //cout << now << "\t" << itr->second << endl;
                vector<State> news = now.getNewStates();
                for (int i = 0; i < news.size(); ++i)
                {
                    p[h + 1][news[i]] += itr->second / 16.0;
                    //cout << news[i] << " # ";
                    //if (news[i].coms[0] == 5 && news[i].coms[1] == 5 && news[i].coms[2] == 5 && news[i].coms[3] == 0)
                    //    cout << now << endl;
                }
                //cout << endl;
            }
            cout << h << " " << p[h].size() << endl;
        }
        //cout << "----------" << endl;
        
        double ans = 0;
        for (map<State, double>::iterator itr = p[height].begin(); itr != p[height].end(); ++itr)
        {
            State now = itr->first;
            //cout << now << "\t" << itr->second << endl;
            if (now.getMaxComSize() >= dangerousClusterSize) ans += itr->second;
        }
        return ans;
    }
    
    // BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; double Arg2 = 0.9375; verify_case(0, Arg2, getProbability(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 2; double Arg2 = 0.5625; verify_case(1, Arg2, getProbability(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 4; double Arg2 = 0.51171875; verify_case(2, Arg2, getProbability(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 30; int Arg1 = 121; double Arg2 = 0.99609375; verify_case(3, Arg2, getProbability(Arg0, Arg1)); }
    
    // END CUT HERE
    
};

// BEGIN CUT HERE
int main()
{
    DynamiteBoxes ___test;
    ___test.run_test(-1);
}
// END CUT HERE
