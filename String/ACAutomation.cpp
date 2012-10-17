#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <string.h>
#include <queue>
#include <utility>
using namespace std;

/** timus 1269
 * @see http://www.cs.uku.fi/~kilpelai/BSA05/lectures/slides04.pdf
 */

struct TrieNode
{
  vector<pair<char, TrieNode*> > gt;
  TrieNode * fail;
  short int wordLen;

  static TrieNode * pool;
  static int nowUsed;

  static TrieNode * getNewNode()
  {
    nowUsed++;
    return &pool[nowUsed - 1];
  }

  //string debug;

  TrieNode()
  {
    gt.clear();
    fail = NULL;
    wordLen = -1;
  }

  inline TrieNode * find(char c)
  {
    for (int i = 0; i < gt.size(); ++i)
      if (gt[i].first == c) 
        return gt[i].second;
    return NULL;
  }

  void addString(char * str)
  {
    TrieNode * nowNode = this;
    int len = strlen(str);
    for (int i = 0; i < len; ++i)
    {
      char nowChar = str[i];
      TrieNode * next = nowNode->find(nowChar);
      if (next == NULL)
      {
        next = getNewNode();
        nowNode->gt.push_back(make_pair(nowChar, next));
      }
      nowNode = next;
    }
    nowNode->wordLen = len;
  }

  /**
  void output(ostream & out, int depth = 0)
  {
    for (int i = 0; i < depth; ++i)
      out << " ";
    //out << debug << "\t";
    if (word != NULL)
      out << (*word);
    else
      out << "NULL";
    out << endl;

    for (vector<pair<char, TrieNode*> >::iterator itr = gt.begin(); itr != gt.end(); ++itr)
    {
      for (int i = 0; i < depth; ++i)
        out << " ";
      out << itr->first << endl;
      itr->second->output(out, depth + 1);
    }
  }
  */
};

int TrieNode::nowUsed = 0;
TrieNode tpool[100010];
TrieNode * TrieNode::pool = tpool;

vector<string> words;
int N;
TrieNode * root;

void calFail()
{
  queue<TrieNode * > q;
  bool caled[256];
  for (int i = 0; i < 256; ++i)
    caled[i] = false;
  for (vector<pair<char, TrieNode*> >::iterator itr = root->gt.begin(); itr != root->gt.end(); ++itr)
  {
    caled[(int)(itr->first) + 128] = true;
    itr->second->fail = root;
    q.push(itr->second);
  }
  for (char c = -128; ; ++c)
  {
    if (c != 0 && c != 10 && c != 13 && !caled[c + 128])
      root->gt.push_back(make_pair(c, root));
    if (c == 127) break;
  }

  while (!q.empty())
  {
    TrieNode * r = q.front();
    q.pop();
    for (vector<pair<char, TrieNode*> >::iterator itr = r->gt.begin(); itr != r->gt.end(); ++itr)
    {
      char a = itr->first;
      TrieNode * u = itr->second;
      q.push(u);
      TrieNode * v = r->fail;
      while (v->find(a) == NULL)
        v = v->fail;
      u->fail = v->find(a);
      if (u->fail->wordLen != -1)
      {
        if (u->wordLen == -1)
          u->wordLen = u->fail->wordLen;
        else
        {
          if (u->fail->wordLen > u->wordLen)
            u->wordLen = u->fail->wordLen;
        }
      }
    }
  }
}

int ACAutomation(char * str)
{
  TrieNode * now = root;
  int L = strlen(str);
  int firstApp = 99999999;
  for (int i = 0; i < L; ++i) 
  {
    char c = str[i];
    while (now->find(c) == NULL) {
      now = now->fail;
    }
    now = now->find(c);
    if (now->wordLen != -1)
      firstApp = min(firstApp, i - (int)now->wordLen + 1);
  }
  if (firstApp < 99999999) 
    return firstApp;
  else
    return -1;
}

char wordbuffer[10002];
char buffer[910001];

void init()
{
  scanf("%d", &N);
  words = vector<string>(N);
  gets(wordbuffer);
  root = new TrieNode();
  for (int i = 0; i < N; ++i)
  {
    gets(wordbuffer);
    root->addString(wordbuffer);
  }

  calFail();

  int M;
  scanf("%d", &M);
  gets(buffer);
  for (int i = 0; i < M; ++i)
  {
    gets(buffer);
    int ret = ACAutomation(buffer);

    if (ret >= 0)
    {
      cout << i + 1 << " " << ret + 1 << endl;
      return;
    }
  }
  cout << "Passed" << endl;
}

int main()
{
  init();
  return 0;
}
