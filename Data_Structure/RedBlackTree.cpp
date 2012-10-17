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

int twists;
class RedBlackNode
{
    public:
        static const int BLACK = 0;
        static const int RED = 1;
        int data;
        int value;
        int color;
        RedBlackNode * L;
        RedBlackNode * R;

        RedBlackNode(int _value)
        {
            L = R = NULL;
            color = RED;
            value = _value;
        }

        RedBlackNode(int _value, int _data)
        {
            L = R = NULL;
            color = RED;
            value = _value;
            data = _data;
        }

        static RedBlackNode * twist(RedBlackNode * x, RedBlackNode * y,
                RedBlackNode * z,
                RedBlackNode * T1, RedBlackNode * T2,
                RedBlackNode * T3, RedBlackNode * T4) 
        {
            twists++;
            y->color = RED;
            x->color = BLACK;
            z->color = BLACK;
            x->L = T1;
            x->R = T2;
            z->L = T3;
            z->R = T4;
            y->L = x;
            y->R = z;
            return y;
        }

        static RedBlackNode * insert(RedBlackNode * node, int value)
        {
            if (node == NULL)
                return new RedBlackNode(value);

            if (value < node->value) 
                node->L = insert(node->L, value);
            else
                node->R = insert(node->R, value);

            if (node->color == BLACK) {
                RedBlackNode *& L = node->L;
                RedBlackNode *& R = node->R;
                if (L != NULL && L->color == RED && L->L != NULL && L->L->color == RED) 
                    return twist(L->L, L, node, L->L->L, L->L->R, L->R, R);
                if (L != NULL && L->color == RED && L->R != NULL && L->R->color == RED)
                    return twist(L, L->R, node, L->L, L->R->L, L->R->R, R);
                if (R != NULL && R->color == RED && R->L != NULL && R->L->color == RED)
                    return twist(node, R->L, R, L, R->L->L, R->L->R, R->R);
                if (R != NULL && R->color == RED && R->R != NULL && R->R->color == RED) 
                    return twist(node, R, R->R, L, R->L, R->R->L, R->R->R);
            }
            return node;
        }

        static RedBlackNode * find(RedBlackNode * node, int value)
        {
            if (node == NULL)
                return NULL;
            if (value == node->value)
                return node;
            if (value < node->value)
                return find(node->L, value);
            else
                return find(node->R, value);
        }
};


class RedBlackTree
{
    public:
        RedBlackNode * root;
        
        RedBlackTree()
        {
            root = NULL;
        }

        void insert(int value)
        {
            root = RedBlackNode::insert(root, value);
            root->color = RedBlackNode::BLACK;
        }

        int find(int value) {
            return RedBlackNode::find(root, value)->data;
        }
};


class RedBlack
{
	public:
		int numTwists(vector <int> keys)
		{
            RedBlackTree tree;
            twists = 0;
            for (int i = 0; i < keys.size(); ++i) {
                tree.insert(keys[i]);
            }
            return twists;
		}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 1,2,3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, numTwists(Arg0)); }
	void test_case_1() { int Arr0[] = { 1,2,3,4,5,6,7 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, numTwists(Arg0)); }
	void test_case_2() { int Arr0[] = { 7,1,4,6,3,5,2 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, numTwists(Arg0)); }
	void test_case_3() { int Arr0[] = { 5,10,15,14,3,4,11,2,1,12,6,9,7,13,8 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 11; verify_case(3, Arg1, numTwists(Arg0)); }
	void test_case_4() { int Arr0[] = { 6,8,10,12,4,2,18,14,16,19,7,15,9,17,13,5,11,3,1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, numTwists(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	RedBlack ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
