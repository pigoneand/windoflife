#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <algorithm>
#include <queue>
#include <utility>
#include <sstream>
#include <bitset>
#include <stdio.h>
using namespace std;

#define DEBUG 0
#define debug1(x) if (DEBUG) cout << #x" = " << x << endl;
#define debug2(x, y) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << endl;
#define debug3(x, y, z) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl;
#define debug4(x, y, z, w) if (DEBUG) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl;

template <class T>
ostream & operator << (ostream & out, const vector<T> & data)
{ out << "["; for (int i = 0; i < data.size(); ++i) out << data[i] << (i == data.size() - 1 ? "" : ","); out << "]"; return out; }

template <class T>
ostream & operator << (ostream & out, const set<T> & s)
{ out << "{"; for (typename set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

template <class T>
ostream & operator << (ostream & out, const multiset<T> & s)
{ out << "{"; for (typename multiset<T>::iterator itr = s.begin(); itr != s.end(); ++itr) out << *itr << " "; out << "}"; return out; }

template <class T1, class T2>
ostream & operator << (ostream & out, const pair<T1, T2> & p)
{ out << "(" << p.first << "," << p.second << ")"; return out; }

template <class T1, class T2>
ostream & operator << (ostream & out, const map<T1, T2> & m)
{ 
  for (typename map<T1, T2>::const_iterator itr = m.begin(); itr != m.end(); ++itr)
    out << itr->first << "->" << itr->second << " ";
  return out;
}
/////// BEGIN CODE //////////////////

struct TokenParseResult
{
  int begin; 
  int end;
  string element;
  
  TokenParseResult(int _begin, int _end, const string & _element)
  {
    begin = _begin;
    end = _end;
    element = _element;
  }
  
  bool operator < (const TokenParseResult & other) const 
  {
    if (begin < other.begin) return true;
    if (begin > other.begin) return false;
    if (end < other.end) return true;
    if (end > other.end) return false;
    if (element < other.element) return true;
    return false;
  }
};

struct RuleParseResult
{
  int begin; 
  int end;
  int ruleID;
  int depth;
  
  bool operator < (const RuleParseResult & other) const
  {
    if (begin < other.begin) return true;
    if (begin > other.begin) return false;
    if (end < other.end) return true;
    if (end > other.end) return false;
    if (ruleID < other.ruleID) return true;
    if (ruleID > other.ruleID) return false;
    if (depth < other.depth) return true;
    return false;
  }
  
  RuleParseResult(int _begin, int _end, int _ruleID, int _depth)
  {
    begin = _begin;
    end = _end;
    ruleID = _ruleID;
    depth = _depth;
  }
};

struct Parser
{
public:
  // rules id start from 1;
  vector<vector<string> > rules;
  map<string, vector<int> > expandrules;
  map<string, string> elements;
  
  Parser() { rules.resize(1); }
  
  void addRule(string  & line)
  {
    for (int i = 0; i < line.length(); ++i)
    {
      if (line[i] == ' ' || line[i] == '\t') line[i] = '_';
      if (line[i] == '<') line[i] = ' ';
      if (line[i] == '>') line[i] = ' ';
      if (line[i] == ':') line[i] = ' ';
    }
    
    string newline = "";
    for (int i = 0; i < line.length(); ++i)
      if (line[i] == '|')
        newline += " | ";
      else
        newline.append(1, line[i]);
    line = newline;
    
    istringstream sin(line);
    string firstword;
    sin >> firstword;
    
    vector<string> now;
    string word;
    while (sin >> word)
    {
      if (word == "|")
      {
        if (now.size() > 0) 
        {
          rules.push_back(now);
          expandrules[firstword].push_back((int)rules.size() - 1);
        }
        now.clear();
        continue;
      }
      now.push_back(word);
    }
    if (now.size() > 0)
    {
      rules.push_back(now);
      expandrules[firstword].push_back((int)rules.size() - 1);
    }
  }
  
  void finishRules()
  {
    vector<vector<string> > & s = rules;
    for (int i = 0; i < s.size(); ++i)
      for (int j = 0; j < s[i].size(); ++j)
        if (expandrules.find(s[i][j]) == expandrules.end())
          elements[s[i][j]] = s[i][j];
  }
  
  map<TokenParseResult, int> token_result;
  map<RuleParseResult, int> rule_result;
  
  int parseRule(string & nowstr, int begin, int end, int ruleID, int depth)
  {
    RuleParseResult rpr(begin, end, ruleID, depth);
    if (rule_result.find(rpr) != rule_result.end()) return rule_result[rpr];
    int & ret = rule_result[rpr];
    
    int nowlen = end - begin;
    if (depth == rules[ruleID].size()) return ret = (nowlen == 0 ? 0 : -1);
    if (nowlen == 0) return ret = -1;
    
    for (int i = begin; i <= end; ++i)
    {
      if (parseToken(nowstr, begin, i, rules[ruleID][depth]) >= 0) 
      {
        if (parseRule(nowstr, i, end, ruleID, depth + 1) >= 0) 
          return ret = i;
      }
    }
    return ret = -1;
  }
  
  int parseToken(string & nowstr, int begin, int end, const string & nowele)
  {
    TokenParseResult tpr(begin, end, nowele);
    if (token_result.find(tpr) != token_result.end()) return token_result[tpr];
    int & ret = token_result[tpr];
    
    if (elements.find(nowele) != elements.end())
      return ret = (nowstr.substr(begin).substr(0, end - begin) == elements[nowele] ? 0 : -1);
    
    vector<int> & erules = expandrules[nowele];
    for (int i = 0; i < erules.size(); ++i)
      if (parseRule(nowstr, begin, end, erules[i], 0) >= 0) return ret = erules[i];
    
    return ret = -1;
  }
  
  void clearParse()
  {
    token_result.clear();
    rule_result.clear();
    result_tokennames.clear();
    result_tokendatas.clear();
  }
  
  vector<string> result_tokennames;
  vector<string> result_tokendatas;
  void printParseTree(string & nowstr, int begin, int end, const string & token, set<string> & stoptokens)
  {
    string nowsub = nowstr.substr(begin, end - begin);
    if (stoptokens.find(token) != stoptokens.end()) 
    {
      result_tokendatas.push_back(nowsub);
      result_tokennames.push_back(token);
      return;
    }
    
    if (elements.find(token) != elements.end())
    {
      result_tokendatas.push_back(nowsub);
      result_tokennames.push_back(token);
      return;
    }
    
    TokenParseResult tpr(begin, end, token);
    int ruleid = token_result[tpr];
    int depth = 0;
    while (depth < rules[ruleid].size())
    {
      RuleParseResult rpr(begin, end, ruleid, depth);
      int i = rule_result[rpr];
      printParseTree(nowstr, begin, i, rules[ruleid][depth], stoptokens);
      begin = i;
      depth++;
    }
  }
};

string rules[10] = {
  string("<digit>:0|1|2|3|4|5|6|7|8|9"), 
  string("<unsigned integer number>:<digit>|<digit><unsigned integer number>"), 
  string("<sign>:+|-"), 
  string("<integer number>:<unsigned integer number>|<sign><unsigned integer number>"), 
  string("<exponent symbol>:e|E"), 
  string("<exponent>:<exponent symbol><integer number>"), 
  string("<simple unsigned real number>:<unsigned integer number>|.<unsigned integer number>|<unsigned integer number>.<unsigned integer number>"), 
  string("<simple real number>:<simple unsigned real number>|<sign><simple unsigned real number>"), 
  string("<real number>:<simple real number>|<simple real number><exponent>") };

map<string, string> nownummap;

string getNorm(string & s)
{
  nownummap.clear();
  string ret = "";
  char c = '0';
  
  for (int i = 0; i < s.length(); ++i)
    if (s[i] >= '0' && s[i] <= '9')
    {
      int j = i;
      while (j < s.length() && s[j] >= '0' && s[j] <= '9') j++;
      string nownum = s.substr(i, j - i);
      nownummap[string(1, c)] = nownum;
      ret.append(1, c);
      c++;
      i = j - 1;
      if (c >= '5') return "";
    }
    else
      ret.append(1, s[i]);
  return ret;
}

void init()
{
  Parser parser;
  for (int i = 0; i < 10; ++i)
    parser.addRule(rules[i]);
  debug1(parser.rules);
  debug1(parser.expandrules);
  parser.finishRules();
  
  string line;
  while (getline(cin, line))
  {
    if (line == "#") break;
    string N;
    getline(cin, N);
    
    debug1(line);
    
    line = getNorm(line);
    debug1(nownummap);
    
    if (line == "") 
    {
      cout << "Not a floating point number" << endl;
      continue;
    }
    
    parser.clearParse();
    int result = parser.parseToken(line, 0, (int)line.length(), "real_number");
    debug2(line, result);
    
    if (result == -1)
    {
      cout << "Not a floating point number" << endl;
      continue;
    }
    
    set<string> stoptokens;
    stoptokens.insert("unsigned_integer_number");
    parser.printParseTree(line, 0, (int)line.length(), "real_number", stoptokens);
    //debug1(parser.result_tokennames);
    debug1(parser.result_tokendatas);
    
    vector<string> ret = parser.result_tokendatas;
    bool sign = false;
    if (ret[0] == "-") { sign = true; ret.erase(ret.begin()); }
    if (ret[0] == "+") { sign = false; ret.erase(ret.begin()); }
    
    int exp = 0;
    bool expsign = false;
    string expstr = "";
    for (int i = 0; i < ret.size(); ++i)
      if (ret[i] == "e" || ret[i] == "E")
      {
        for (int j = i + 1; j < ret.size(); ++j)
          if (ret[j] == "-" || ret[j] == "+")
            expsign = (ret[j] == "-" ? true : false);
          else
            expstr += nownummap[ret[j]];
        ret.resize(i);
        break;
      }
    
    string intpart = "";
    string floatpart = "";
    bool isIntPart = true;
    for (int i = 0; i < ret.size(); ++i)
    {
      if (ret[i] == ".") isIntPart = false;
      else
      {
        if (isIntPart) intpart += nownummap[ret[i]]; 
        else floatpart += nownummap[ret[i]];
      }
    }
    
    string expnumstr = "";
    for (int i = 0; i < expstr.length(); ++i)
      if (expstr[i] != '0')
      {
        for (int j = i; j < expstr.length(); ++j)
          expnumstr.append(1, expstr[j]);
        break;
      }
    
    debug2(expstr, expnumstr);
    if (expnumstr.length() >= 4 && expsign)
    {
      intpart = "";
      floatpart = "";
    }
    else
    {
      sscanf(expnumstr.data(), "%d", &exp);
      if (expsign) exp = -exp;
    }
    
    if (exp > 0)
    {
      for (int i = 0; i < exp; ++i)
        if (floatpart.length() > 0) 
        {
          intpart.append(1, floatpart[0]);
          floatpart = floatpart.substr(1);
        }
        else
          intpart.append(1, '0');
    }
    else
    {
      for (int i = 0; i < abs(exp); ++i)
        if (intpart.length() > 0)
        {
          floatpart = string(1, intpart[intpart.length() - 1]) + floatpart;
          intpart.resize(intpart.length() - 1);
        }
        else
          floatpart = string(1, '0') + floatpart;
    }
    
    while (intpart.length() > 0 && intpart[0] == '0') 
      intpart = intpart.substr(1);
    
    if (intpart == "") intpart = "0";
    if (floatpart == "") floatpart = "0";
    
    debug2(sign, exp);
    debug2(intpart, floatpart);
    
    int NN;
    sscanf(N.data(), "%d", &NN);
    floatpart.resize(NN, '0');
      
    if (intpart == "0" && floatpart == string(floatpart.length(), '0')) 
      sign = false;
    
    if (sign) cout << "-";
    cout << intpart;
    if (floatpart.length() > 0) 
      cout << "." << floatpart;
    cout << endl;
    
    //cout << endl;
  }
}

void york()
{
  
}

int main()
{
  init();
  york();
  return 0;
}
