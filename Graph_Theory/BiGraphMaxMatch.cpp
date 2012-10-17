#include <iostream>
using namespace std;

class BipartiteMaxMatch
{
  public:
    /** Max Left or Right Nodes */
    static const int MaxN = 250;

    int leftNodes;
    int rightNodes;

    /** These is an edge between left node i and right node j */
    bool connect[MaxN][MaxN];

    /** Left i's current partener */
    int leftPart[MaxN];

    /** Right i's current partener */
    int rightPart[MaxN];

    /** Right Node Visited or not */
    bool visited[MaxN];

    BipartiteMaxMatch(int left, int right)
    {
      if (left > MaxN || right > MaxN) {
        cout << "Too much nodes" << endl;
        return;
      }
      leftNodes = left;
      rightNodes = right;
      memset(connect, false, sizeof(connect));
    }

    /** Start Match */
    int match()
    {
      int ans = 0;
      for (int i = 0; i < leftNodes; ++i) leftPart[i] = -1;
      for (int j = 0; j < rightNodes; ++j) rightPart[j] = -1;
      memset(visited, false, sizeof(visited));

      for (int i = 0; i < leftNodes; ++i) 
        if (leftPart[i] == -1) {
          memset(visited, false, sizeof(visited));
          ans += find(i);
        }
      return ans;
    }

    /** Find the augument path */
    int find(int start)
    {
      for (int i = 0; i < rightNodes; ++i) {
        if (!visited[i] && connect[start][i]) {
          visited[i] = true;
          if (rightPart[i] == -1 || find(rightPart[i])) {
            leftPart[start] = i;
            rightPart[i] = start;
            return 1;
          }    
        }
      }        
      return 0;
    }

	/** Find minimum vertex cover, after match() is called */
	bool leftMask[MaxN], rightMask[MaxN];
	bool leftV[MaxN];

	void covermask(int x)
	{
		if (leftV[x]) return;
		leftV[x] = true;
		leftMask[x] = true;
		int y = leftPart[x];
		rightMask[y] = true;
		for (int i = 0; i < leftNodes; ++i)
			if (connect[i][y]) 
				covermask(i);
	}

	/** get minimum vertex cover */
	vector<pair<int, int> > getVertexCover()
	{
		memset(leftMask, false, sizeof(leftMask));
		memset(rightMask, false, sizeof(rightMask));
		memset(leftV, false, sizeof(leftV));

		for (int j = 0; j < rightNodes; ++j)
			if (rightPart[j] == -1)
				for (int i = 0; i < leftNodes; ++i)
					if (connect[i][j]) 
						covermask(i);

		vector<pair<int, int> > ret;
		for (int i = 0; i < leftNodes; ++i)
			if (leftMask[i]) ret.push_back(make_pair(0, i));
		for (int j = 0; j < rightNodes; ++j)
			if (rightPart[j] != -1 && !rightMask[j]) ret.push_back(make_pair(1, j));
		return ret;
	}
};

int main()
{
  return 0;
}
