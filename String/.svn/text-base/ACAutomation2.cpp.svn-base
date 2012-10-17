#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <vector>
#include <queue>
#include <utility>
#include <string.h>
#include <string>
using namespace std;

class BigInteger
{
  public:
    const static int BASE = 10;

    vector<int> digits;

    /** The Big Integer's digits */
    inline int size() const { return digits.size(); }

    /** Constructors */
    BigInteger() { (*this) = 0; }
    BigInteger(int init) { (*this) = init; }
    BigInteger(const string & str) { (*this) = str; }
    BigInteger(const BigInteger & other) { digits = other.digits; }

    /** IO operation */
    friend ostream & operator << (ostream & out, const BigInteger &x);
    friend istream & operator >> (istream & in, BigInteger & x);

    /** Assignment operatoion */
    BigInteger & operator = (int init);
    BigInteger & operator = (const string & str);
    BigInteger & operator = (const BigInteger & other);

    /** Calculate operation */
    BigInteger operator * (const BigInteger & other);
    BigInteger operator + (const BigInteger & other);
    BigInteger operator / (const BigInteger & other);
    BigInteger operator - (const BigInteger & other);
    BigInteger operator % (const BigInteger & other);
    BigInteger operator * (int other);
    BigInteger operator / (int other);
    BigInteger operator % (int other);

    /** Additional calculate operation */
    /** power(x,y) */
    BigInteger operator ^ (int other);

    bool operator < (const BigInteger & other) const { return compare(other) < 0; }
    bool operator > (const BigInteger & other) const { return compare(other) > 0; }
    bool operator <= (const BigInteger & other) const { return compare(other) <= 0; }
    bool operator >= (const BigInteger & other) const { return compare(other) >= 0; }
    bool operator == (const BigInteger & other) const { return compare(other) == 0; }
    bool operator != (const BigInteger & other) const { return compare(other) != 0; }
    int compare(const BigInteger & y) const;

    /** Convert operation */
    string toString()
    {
      int len = size();
      string ret(len, '0');
      for (int i = 0; i < len; ++i) 
        ret[i] = getNumChar(digits[len - i - 1]);
      return ret;
    }

    int toInt()
    {
      string str = toString();
      int ret;
      sscanf(str.data(), "%d", &ret);
      return ret;
    }
    
    static inline char getNumChar(int x) { return x < 10 ? '0' + x : 'A' - 10 + x; }
};

/** IO operation */
ostream & operator << (ostream & out, const BigInteger & x)
{
  for (int i = x.digits.size() - 1; i >= 0; i--) 
    out << x.digits[i]; 
  return out; 
}

istream & operator >> (istream & in, BigInteger & x)
{
  string line;
  in >> line;
  x = line;
  return in;
}

/** Assignment operation */
BigInteger & BigInteger::operator = (const string & str)
{
  int len = str.length();
  digits = vector<int>(len);
  for (int i = 0; i < len; ++i) 
    digits[i] = str[len - i - 1] - '0';
  return (*this);
}

BigInteger & BigInteger::operator = (int init)
{
  if (init == 0) {
    digits = vector<int>(1);
    digits[0] = 0;
    return (*this);
  }
  digits.clear();
  while (init > 0) {
    digits.push_back(init % BASE);
    init /= BASE;
  }
  return (*this);
}

BigInteger & BigInteger::operator = (const BigInteger & other)
{
  if (&other != this) digits = other.digits;
  return (*this);
}

/** Calculation operations */
BigInteger BigInteger::operator * (const BigInteger & other)
{
  BigInteger ret;
  int lena = size();
  int lenb = other.size();
  int len = lena + lenb;
  ret.digits = vector<int>(len, 0);

  for (int i = 0; i < lena; ++i) 
    for (int j = 0; j < lenb; ++j) 
      ret.digits[i + j] += digits[i] * other.digits[j];

  for (int i = 0; i < len - 1; ++i) { 
    if (ret.digits[i] >= BASE) {
      ret.digits[i + 1] += ret.digits[i] / BASE; 
      ret.digits[i] %= BASE; 
    }
  }

  while (ret.digits[ret.size() - 1] >= BASE) { 
    ret.digits.push_back(ret.digits[ret.size() - 1] / BASE);
    ret.digits[ret.size() - 2] %= BASE;
  }
  while (ret.size() > 1 && ret.digits[ret.size() - 1] == 0) 
    ret.digits.pop_back();
  return ret;
}

/** Multiply int, assume other * BASE < maxint */
BigInteger BigInteger::operator * (int other)
{
  BigInteger ret;
  const static int MAX_INC_LEN = 10;
  ret.digits = vector<int>(size() + MAX_INC_LEN);

  int nowLen = size();
  int len = size() + MAX_INC_LEN;
  for (int i = 0; i < nowLen; ++i) 
    ret.digits[i] = digits[i] * other;
  for (int i = 0; i < len - 1; ++i) 
    if (ret.digits[i] >= BASE) {
      ret.digits[i + 1] += ret.digits[i] / BASE;
      ret.digits[i] %= BASE;
    }
  while (ret.size() > 1 && ret.digits[ret.size() - 1] == 0) 
    ret.digits.pop_back();
  return ret;
}

/** operator plus */
BigInteger BigInteger::operator + (const BigInteger & other)
{
  BigInteger ret; 
  int lena = size();
  int lenb = other.size();
  int len = max(lena, lenb) + 1;
  ret.digits = vector<int>(len, 0);
  int i;
  for (i = 0; i < lena || i < lenb || i < len && ret.digits[i]; i++) {
    if (i < lena) ret.digits[i] += digits[i];
    if (i < lenb) ret.digits[i] += other.digits[i];
    if (ret.digits[i] >= BASE) {
      ret.digits[i + 1] = ret.digits[i] / BASE;
      ret.digits[i] %= BASE;
    }
  }
  if (ret.digits[ret.size() - 1] == 0) 
    ret.digits.pop_back();
  return ret;
}


using namespace std;

struct TrieNode
{
  /** original nexts */
  map<char, TrieNode*> nexts;

  /** extended nexts */
  map<char, TrieNode*> gos;
  TrieNode * fail;
  bool legal;
  BigInteger ways;
  BigInteger newways;

  string debug;

  TrieNode()
  {
    fail = NULL;
    legal = true;
    ways = 0;

    debug = "";
  }

  void addWord(const string & word)
  {
    TrieNode * now = this;
    for (int i = 0; i < word.length(); ++i)
    {
      char nowC = word[i];
      if (now->nexts.find(nowC) == now->nexts.end())
        now->nexts[nowC] = new TrieNode();
      now = now->nexts[nowC];
      now->debug = word.substr(0, i + 1);
    }
    now->legal = false;
  }
};

TrieNode * root;
vector<TrieNode *> nodes;
void initAutomation(vector<string> & words)
{
  root = new TrieNode(); 
  for (int i = 0; i < words.size(); ++i)
    root->addWord(words[i]);

  queue<TrieNode*> q;
  nodes.push_back(root);
  root->fail = root;
  for (char c = -128; ; c++)
  {
    if (root->nexts.find(c) != root->nexts.end())
    {
      root->nexts[c]->fail = root;
      root->gos[c] = root->nexts[c];
      q.push(root->nexts[c]);
    }
    else
    {
      root->gos[c] = root;
    }
    if (c == 127) break;
  }

  while (q.size() > 0)
  {
    TrieNode * u = q.front();
    q.pop();
    nodes.push_back(u);

    for (map<char, TrieNode*>::iterator itr = u->nexts.begin(); itr != u->nexts.end(); ++itr)
    {
      TrieNode * v = itr->second;
      char nowC = itr->first;

      TrieNode * f = u->fail;
      while (f != root && f->nexts.find(nowC) == f->nexts.end())
        f = f->fail;
      if (f == root && f->nexts.find(nowC) == f->nexts.end())
          f = root;
      else
          f = f->nexts[nowC];

      v->fail = f;
      if (v->fail->legal == false) v->legal = false;
      q.push(v);
    }

    /** update goes */
    for (char c = -128; ; ++c)
    {
      if (u->nexts.find(c) == u->nexts.end())
        u->gos[c] = u->fail->gos[c];
      else
        u->gos[c] = u->nexts[c];
      if (c == 127) break;
    }
  }
}

int N;
int M;
int P;
string chars;
void init()
{
  scanf("%d%d%d", &N, &M, &P);
  vector<string> words;
  string line;
  getline(cin, line);
  getline(cin, chars);
  for (int i = 0; i < P; ++i)
  {
    getline(cin, line);
    words.push_back(line);
  }

  initAutomation(words);
}

void deal()
{
  root->ways = 1;
  for (int k = 0; k < M; ++k)
  {
    for (int i = 0; i < nodes.size(); ++i)
      nodes[i]->newways = 0;

    for (int i = 0; i < nodes.size(); ++i)
    {
      TrieNode * now = nodes[i];
      for (int c = 0; c < chars.length(); ++c)
      {
        char nowC = chars[c];
        TrieNode * next = now->gos[nowC];

//        if (k == 0) cout << "(" << now->debug << "," << next->debug << ")" << endl;
        if (now->legal && next->legal)
          next->newways = next->newways + now->ways;
      }
    }

    for (int i = 0; i < nodes.size(); ++i)
      nodes[i]->ways = nodes[i]->newways;
  }

  BigInteger ans = 0;
  for (int i = 0; i < nodes.size(); ++i)
    if (nodes[i]->legal) 
      ans = ans + nodes[i]->ways;

  cout << ans << endl;
}


int main()
{
  init();
  deal();
  return 0;
}


