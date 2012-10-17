#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <fstream>
#include <utility>
#include <iomanip>
#include <string.h>
#include <cassert>
using namespace std;

class TreapNode
{
public:
	int value;
	int priority;
	int size;
	TreapNode * left;
	TreapNode * right;
	TreapNode * father;

	TreapNode(int _value, TreapNode * _father)
	{
		value = _value;
		priority = rand();
		size = 1;
		left = NULL;
		right = NULL;
		father = _father;
	}

	~TreapNode()
	{
		if (left != NULL) delete left;
		if (right != NULL) delete right;
	}

	void setLeftSon(TreapNode * son)
	{
		this->left = son;
		if (son != NULL) son->father = this;
	}

	void setRightSon(TreapNode * son)
	{
		this->right = son;
		if (son != NULL) son->father = this;
	}

	int getLeftSize()
	{
		return left == NULL ? 0 : left->size;
	}

	int getRightSize()
	{
		return right == NULL ? 0 : right->size;
	}

	void output(ostream & out, int indent = 0) const
	{
		for (int i = 0; i < abs(indent); ++i)
			out << "  ";
		if (indent == 0) out << "D";
		if (indent < 0) out << "L";
		if (indent > 0) out << "R";

		out << "(" << this->value << ")[" << this->priority << "]" << "|" << size << "|" << endl;
		if (this->left != NULL) 
		{
			this->left->output(out, -(abs(indent) + 1));
		}
		if (this->right != NULL)
		{
			this->right->output(out, abs(indent) + 1);
		}
	}

	bool check()
	{
		if (left != NULL) 
		{
			assert(left->value < value);
			assert(left->priority <= priority);
			left->check();
		}
		if (right != NULL)
		{
			assert(right->value > value);
			assert(right->priority <= priority);
			right->check();
		}

		int leftSize = 0;
		int rightSize = 0;
		if (left != NULL) leftSize = left->size;
		if (right != NULL) rightSize = right->size;
		assert(size == leftSize + rightSize + 1);
		return true;
	}
};

class Treap
{
public:
	TreapNode * root;

	Treap()
	{
		root = NULL;
	}

	~Treap()
	{
		delete root;
	}

	friend ostream & operator << (ostream & out, const Treap & treap)
	{
		treap.root->output(out);
		return out;
	}

	int getSize(TreapNode * node)
	{
		if (node == NULL) 
			return 0;
		else
			return node->size;
	}
	
	int size()
	{
		return getSize(root);
	}

	/** right twist 
	             D                           D
							 |                            |
	             Y                            X
						 /   \                        /   \
					  X     C       -->            A     Y
          /   \                              /   \
         A     B                            B     C
	*/
	bool rotateRight(TreapNode * node)
	{	
		TreapNode * Y = node;
		TreapNode * D = Y->father;
		TreapNode * X = Y->left;
		if (X == NULL) return false;

		TreapNode * C = Y->right;
		TreapNode * A = X->left;
		TreapNode * B = X->right;

		Y->setLeftSon(B);
		X->setRightSon(Y);
		/** maintain size */
		int ny = getSize(Y) - getSize(A) - 1;
		int nx = getSize(X) + 1 + getSize(C);
		Y->size = ny;
		X->size = nx;

		if (D != NULL) 
		{
			if (D->left == Y) 
				D->setLeftSon(X);
			else
				D->setRightSon(X);
		}
		else
		{
			X->father = NULL;
			root = X;
		}

		return true;
	}

	/** left twist 
	             D                            D
							 |                             |
	             Y                             X
						 /     \                       /    \
					   X      C       <--           A      Y
           /   \                               /   \
          A     B                             B     C
	*/
	bool rotateLeft(TreapNode * node)
	{
		TreapNode * X = node;
		TreapNode * D = X->father;
		TreapNode * Y = X->right;
		if (Y == NULL) return false;

		TreapNode * A = X->left;
		TreapNode * B = Y->left;
		TreapNode * C = Y->right;

		X->setRightSon(B);
		Y->setLeftSon(X);

		/** maintain size */
		int nx = X->size - 1 - getSize(C);
		int ny = Y->size + getSize(A) + 1;
		X->size = nx;
		Y->size = ny;

		if (D != NULL)
		{
			if (D->left == X)
				D->setLeftSon(Y);
			else
				D->setRightSon(Y);
		}
		else
		{
			Y->father = NULL;
			root = Y;
		}
		return true;
	}

	/** maintain the maximum heap property */
	void maintain(TreapNode * node)
	{
		TreapNode * now = node;
		while (now != NULL)
		{
			TreapNode * father = now->father;
			if (father == NULL) break;
			if (now->priority > father->priority)
			{
				if (father->left == now)
					rotateRight(father);
				else
					rotateLeft(father);
			}
			else
				break;
		}
	}

	/** assert doesn't contain this value */
	TreapNode * insert(int value)
	{
		if (root == NULL)
		{
			root = new TreapNode(value, NULL);
			return root;
		}

		TreapNode * now = root;
		while (true)
		{
			now->size++;
			if (value < now->value) 
			{
				if (now->left == NULL) 
				{
					now->left = new TreapNode(value, now);
					maintain(now->left);
					return now->left;
				}
				else
					now = now->left;
			}
			else
			{
				if (now->right == NULL)
				{
					now->right = new TreapNode(value, now);
					maintain(now->right);
					return now->right;
				}
				else
					now = now->right;
			}
		}
	}

	// erase given node in the treap
	void erase(TreapNode * node)
	{
		while (true)
		{
			// if this node is leaf now, erase this node
			// notice to update the size information and father information
			if (node->left == NULL && node->right == NULL)
			{
				if (node == root)
				{
					delete node;
					root = NULL;
				}
				else
				{
					if (node->father->left == node)
						node->father->left = NULL;
					if (node->father->right == node)
						node->father->right = NULL;

					// update size
					TreapNode * father = node->father;
					while (father != NULL)
					{
						father->size--;
						father = father->father;
					}
					delete node;
				}
				break;
			}
			else
			{
				if (node->left == NULL) 
					rotateLeft(node);
				else
				{
					if (node->right == NULL)
						rotateRight(node);
					else
					{
						if (node->left->priority > node->right->priority)
							rotateRight(node);
						else
							rotateLeft(node);
					}
				}
			}
		}
	}

	void erase(int value)
	{
		TreapNode * node = search(value);
		if (node != NULL)
			erase(node);
	}

	// search a node with given value, save its rank
	// if none, return NULL
	TreapNode * search(int value, int & rank)
	{
		rank = 1;
		TreapNode * now = root;
		while (now != NULL)
		{
			if (value == now->value) 
			{
				rank += now->getLeftSize();
				return now;
			}
			if (value < now->value) 
				now = now->left;
			else
			{
				rank += 1 + now->getLeftSize();
				now = now->right;
			}
		}
		return NULL;
	}

	TreapNode * search(int value)
	{
		int rank;
		return search(value, rank);
	}

	// search the kth bigger value in the treap
	TreapNode * searchByRank(int rank)
	{
		TreapNode * now = root;
		while (rank > 0)
		{
			if (now == NULL) return NULL;
			if (rank > getSize(now)) return NULL;
			int leftSize = now->getLeftSize();
			if (leftSize >= rank)
				now = now->left;
			else
			{
				if (leftSize + 1 == rank)
					return now;
				else
				{
					rank -= leftSize + 1;
					now = now->right;
				}
			}
		}
		return NULL;
	}

	/** check the consistency of the treap */
	bool check()
	{
		return root->check();
	}
};

class TimeUtil
{
  public:
    time_t start;
    time_t stop;

    void startCount()
    {
      start = clock();
    }

    double stopCount()
    {
      stop = clock();
      return (stop - start) / 1000.0;
    }
};

void testTreap()
{
	Treap treap;
	vector<int> nums;
	for (int k = 0; k < 10000; ++k)
		nums.push_back(rand() * rand() % 1000000);

	sort(nums.begin(), nums.end());
	nums.resize(unique(nums.begin(), nums.end()) - nums.begin());

	TimeUtil util;
	util.startCount();
	for (int k = 0; k < nums.size(); ++k)
	{
		int value = nums[k];
		treap.insert(value);
	}
	cout << util.stopCount() << endl;

	if (!treap.check())
	{
		cout << "ERROR" << endl;
		return;
	}

	cout << "OK" << endl;


	for (int i = 0; i < nums.size(); ++i)
	{
		int ansRank = i + 1;
		int myRank;
		treap.search(nums[i], myRank);
		assert(ansRank == myRank);
	}

	for (int i = 0; i < nums.size(); ++i)
	{
		int nowRank = i + 1;
		int ans = nums[i];
		TreapNode * rankNode = treap.searchByRank(nowRank);
		assert(ans == rankNode->value);
	}

	cout << "Rank OK" << endl;

	// test erase
	set<int> sets;
	for (int i = 0; i < nums.size(); ++i)
		if (rand() % 2 == 0)
			treap.erase(nums[i]);
		else
			sets.insert(nums[i]);

	for (int i = 0; i < nums.size(); ++i)
	{
		bool foundInSets = sets.find(nums[i]) != sets.end();
		bool foundInTreap = treap.search(nums[i]) != NULL;
		assert(foundInSets == foundInTreap);
	}

	cout << "Erase OK" << endl;

	cout << treap.check() << endl;
}

/////////////////////////////////////////////////////
// Test Treap Finished
/////////////////////////////////////////////////////

int N, K;
void init()
{
	scanf("%d%d", &N, &K);
}

Treap treap;
void york()
{
	for (int i = 1; i <= N; ++i)
		treap.insert(i);

	int nowRank = N - 1;
	int nowSize = N;
	for (int iter = 0; iter < N; ++iter)
	{
		int newRank = (nowRank + K) % nowSize;
		TreapNode * sel = treap.searchByRank(newRank + 1);
		printf("%d\n", sel->value);
		treap.erase(sel);

		if (iter == (N - 1)) break;
		nowSize--;
		nowRank = (newRank - 1 + nowSize) % nowSize;
	}
}

int main()
{
	testTreap();
	init();
	york();

	return 0;
}  
