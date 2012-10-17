string trim(string & str)
{
	int t1 = str.find_first_not_of(" ");
	if (t1 == string::npos) return "";
	int t2 = str.find_last_not_of(" ");
	return str.substr(t1, t2 - t1 + 1);
}

string Replace( const string& orignStr, const 
	string& oldStr, const string& newStr )   
{   
	size_t pos = 0;   
	string tempStr = orignStr;   
	string::size_type newStrLen = newStr.length();   
	string::size_type oldStrLen = oldStr.length();   
	while(true)   
	{   
		pos = tempStr.find(oldStr, pos);   
		if (pos == wstring::npos) break;
		tempStr.replace(pos, oldStrLen, newStr);   
		pos += newStrLen;  
	}   
	return tempStr;   
} 

struct Exp
{
	bool isValid;
	bool isConst;
	bool isVar;
	int constValue;
	char var;
	Exp * left, * right;

	bool isLeftAss(char c)
	{ return c == '*' || c == '/' || c == '+' || c == '-' || c == '&' || c == '|'; }

	int getOpRank(char c)
	{
		if (c == '!') return 3;
		if (c == '*') return 2;
		if (c == '/') return 2;
		if (c == '&') return 2;
		if (c == '+') return 1;
		if (c == '-') return 1;
		if (c == '|') return 1;
		return -1;
	}

	Exp(string str)
	{
		isVar = false;
		isConst = false;
		isValid = true;

		// remove meanless brack () match
		while (true)
		{
			str = trim(str);
			bool remove = false;
			if (str.length() >= 2 && str[0] == '(' && str[str.length() - 1] == ')')
			{
				vector<int> bMatch(str.length());
				stack<int> s;
				for (int i = 0; i < str.length(); ++i)
				{
					if (str[i] == '(') s.push(i);
					if (str[i] == ')') 
					{
						bMatch[i] = s.top();
						s.pop();
					}
				}
				if (bMatch[str.length() - 1] == 0)
				{
					remove = true;
					str = str.substr(1, str.length() - 2);
				}
			}
			if (!remove) break;
		}

		// find the lowest op 
		int lowPos = -1;
		int lowRank = 9999;
		int baseRank = 0;
		for (int i = 0; i < str.length(); ++i)
		{
			int rank = getOpRank(str[i]);
			if (rank >= 0 && (baseRank + rank < lowRank) || (baseRank + rank <= lowRank && isLeftAss(str[i])))
			{
				lowRank = baseRank + rank;
				lowPos = i;
			}
			if (str[i] == '(') baseRank += 10;
			if (str[i] == ')') baseRank -= 10;
		}

		// detect const or variable
		if (lowPos == -1)
		{
			if (str.length() == 0)
			{
				isValid = false;
				return;
			}
			if (str[0] >= 'A' && str[0] <= 'Z' && str.length() == 1)
			{
				isVar = true;
				var = str[0];
			}
			else
			{
				isConst = true;
				sscanf(str.data(), "%d", &constValue);
			}
			return;
		}

		// is op
		var = str[lowPos];
		left = new Exp(str.substr(0, lowPos));
		right = new Exp(str.substr(lowPos + 1));
	}

	friend ostream & operator << (ostream & out, const Exp & e)
	{
		if (!e.isValid) { out << "[]"; return out; }
		if (e.isConst) { 
			out << "[" << e.constValue << "]"; return out; }
		if (e.isVar) { out << "[" << e.var << "]"; return out; }
		out << e.var << "(";
		out << (*e.left) << ",";
		out << (*e.right) << ")";
		return out;
	}

	int calExp(map<char, int> & vartable)
	{	
		if (!isValid) return 0;
		if (isConst) return constValue;
		if (isVar) return vartable[var];
		char op = var;
		int l = left->calExp(vartable);
		int r = right->calExp(vartable);
		if (op == '*') return l * r;
		if (op == '/') return l / r;
		if (op == '&') return (l != 0) && (r != 0);
		if (op == '+') return l + r;
		if (op == '-') return l - r;
		if (op == '|') return (l != 0) || (r != 0);
		if (op == '!') 
			return r == 0 ? 1 : 0;
	}
};
