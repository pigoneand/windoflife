#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

template <class T>
class TrieNode
{
  public:
    static const char TRIE_NODE_START_CHAR = '0';
    static const int TRIE_NODE_BRANCHES = 2;

    /** The data saved on this node */
    T * data;

    /** The children */
    TrieNode * child[TRIE_NODE_BRANCHES];

    TrieNode()
    {
      for (int i = 0; i < TRIE_NODE_BRANCHES; ++i)
        child[i] = NULL;
      data = new T();
    }

    void release()
    {
      for (int i = 0; i < TRIE_NODE_BRANCHES; ++i)
        if (child[i] != NULL)
          child[i]->release();

      for (int i = 0; i < TRIE_NODE_BRANCHES; ++i)
        delete child[i];
    }
};

template<class T>
class TrieTree
{
  public:
    TrieNode<T> * root;
    TrieTree() { root = new TrieNode<T>(); }

    ~TrieTree()
    {
      root->release();
      delete root;
    }

    /** 
     * Insert new str in trie tree
     * @return the pointer to the data, so that the caller can do operation on date 
     */
    T * insert(const string & str)
    {
      TrieNode<T> * nowNode = root;
      for (int i = 0; i < str.length(); ++i)
      {
        int nowCharIndex = str[i] - TrieNode<T>::TRIE_NODE_START_CHAR;
        if (nowNode->child[nowCharIndex] == NULL)
          nowNode->child[nowCharIndex] = new TrieNode<T>();
        nowNode = nowNode->child[nowCharIndex];
      }
      return nowNode->data;
    }

    /** 
     * Search str in trie tree
     * @return NULL if not found
     *         else return the pointer to the data
     */
    T * search(const string & str)
    {
      TrieNode<T> * nowNode = root;
      for (int i = 0; i < str.length(); ++i)
      {
        int nowCharIndex = str[i] - TrieNode<T>::TRIE_NODE_START_CHAR;
        if (nowNode->child[nowCharIndex] == NULL)
          return NULL;
        nowNode = nowNode->child[nowCharIndex];
      }
      return nowNode->data;
    }

    /** 
     * Search cloest string in trie with respect to str
     */
    T * searchClosest(const string & str)
    {
      TrieNode<T> * nowNode = root;
      for (int i = 0; i < str.length(); ++i)
      {
        int nowCharIndex = str[i] - TrieNode<T>::TRIE_NODE_START_CHAR;
        int offset = 0;
        for (offset = 0; offset < TrieNode<T>::TRIE_NODE_BRANCHES; ++offset)
          if (nowNode->child[(nowCharIndex + offset) % TrieNode<T>::TRIE_NODE_BRANCHES] != NULL)
            break;
        int closeCharIndex = (nowCharIndex + offset) % TrieNode<T>::TRIE_NODE_BRANCHES;
        if (nowNode->child[closeCharIndex] != NULL)
          nowNode = nowNode->child[closeCharIndex];
        else
          return NULL;
      }
      return nowNode->data;
    }
};


class Node
{
  public:
    int number;
    Node() {}
};

string toTwo(int x)
{
  string ret(32, '0');

  int posi = 31;
  while (x > 0)
  {
    if (x & 1) 
      ret[posi] = '1';
    x >>= 1;
    posi--;
  }
  
  return ret;
}

int main()
{
  for (int k = 0; k < 100; ++k)
  {
    cout << k << endl;
    TrieTree<Node> tree;

    vector<unsigned int> num(rand() % 10000 + 1);
    for (int i = 0; i < num.size(); ++i)
      num[i] = rand();

    int p1, p2;
    unsigned int ans = 0;
    for (int i = 0; i < num.size(); ++i)
      for (int j = i + 1; j < num.size(); ++j)
      {
        if ((num[i] ^ num[j]) > ans)
        {
          ans = num[i] ^ num[j];
          p1 = i;
          p2 = j;
        }
      }

    for (int i = 0; i < num.size(); ++i)
      tree.insert(toTwo(num[i]))->number = num[i];

    unsigned int ans2 = 0;
    for (int i = 0; i < num.size(); ++i)
    {
      string query = toTwo(num[i]);
      for (int j = 0; j < query.size(); ++j)
        query[j] = 1 - (query[j] - '0') + '0';
      Node * node = tree.searchClosest(query);
      ans2 = max(ans2, node->number ^ num[i]);
    }

    if (ans != ans2)
    {
      cout << "error" << endl;
    }
  }
  return 0;
}





