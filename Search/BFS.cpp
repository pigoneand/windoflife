#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <list>
#include <queue>
using namespace std;

/** This class represent a BFS Search Node */
class BFSNode
{
  private:
    /** @Need change */
    inline int getHashCode()
    {
      int code = 0;
      for (int i = 0; i < nodeData.size(); ++i)
        code = (code << 1) + nodeData[i];
      return code;
    }

  public:
    /** The path length from the root node to this node, root node's depth is 0 */
    int depth;
    int hashcode;

    int father;

    /** How we generate this node from its father */
    int generateMethod;

    /** The inner node data */
    vector<bool> nodeData;

    string toString()
    {
      string ret = "";
      for (int i = 0; i < nodeData.size(); ++i)
        if (nodeData[i])
          ret += "1";
        else
          ret += "0";
      return ret;
    }

    BFSNode()
    {
      depth = 0;
      father = -1;
      nodeData = vector<bool>(13);
      hashcode = getHashCode();
      generateMethod = -1;
    }

    BFSNode(vector<bool> & data)
    {
      nodeData = data;
      depth = 0;
      father = -1;
      hashcode = getHashCode();
      generateMethod = -1;
    }

    BFSNode(const BFSNode & node)
    {
      nodeData = node.nodeData;
      depth = node.depth + 1;
      hashcode = getHashCode();
      father = -1;
      generateMethod = node.generateMethod;
    }

    /** In order to use set, overload this operator 
     * @Need Change
     */
    bool operator < (const BFSNode & other) const
    {
      return hashcode < other.hashcode;
    }

    /** Eqivalence relation 
     * @Need Change
     */
    bool operator == (const BFSNode & other) const
    {
      return hashcode == other.hashcode;
    }

    /** Expand this node, don't care about appeared or not 
     * @Need Change
     */
    vector<BFSNode> expandNode()
    {
      vector<BFSNode> nodes;

      static int r[6][6] = {
        {0, 3, 6, 8, 5, 2},
        {0, 2, 5, 8, 6, 3},
        {1, 4, 7, 9, 6, 3},
        {1, 3, 6, 9, 7, 4},
        {6, 9, 11, 12, 10, 8},
        {6, 8, 10, 12, 11, 9}
      };

      for (int i = 0; i < 6; ++i) 
      {
          BFSNode newNode(*this);
          newNode.generateMethod = i;
          bool temp = newNode.nodeData[r[i][0]];
          for (int j = 0; j < 5; ++j)
            newNode.nodeData[r[i][j]] = newNode.nodeData[r[i][j+1]]; 
          newNode.nodeData[r[i][5]] = temp;
          newNode.hashcode = newNode.getHashCode();
          nodes.push_back(newNode);
      }
      return nodes;
    }
};

class BFSSearcher
{
  public:
    int duplicatedDetectorMethod;
    static const int DUPLICATED_SET = 1;
    static const int DUPLICATED_CODE = 2;
    static const int CODESIZE = 200000;
    static const int NODESIZE = 200000;

    BFSSearcher()
    {
      duplicatedDetectorMethod = DUPLICATED_CODE;
      clear();
    }

    void clear()
    {
      for (int i = 0; i < CODESIZE; ++i)
        visitedCode[i] = false;
      visited.clear();
    }

    BFSNode startNode;
    BFSNode targetNode;
    BFSNode path[NODESIZE];

    /** The nodes which has been visited */
    set<BFSNode> visited;
    bool visitedCode[CODESIZE];

    inline bool isVisited(const BFSNode & node)
    {
      if (duplicatedDetectorMethod == DUPLICATED_SET)
        return visited.find(node) != visited.end();
      else
        return visitedCode[node.hashcode];
    }

    inline void setVisited(const BFSNode & node)
    {
      if (duplicatedDetectorMethod == DUPLICATED_SET)
        visited.insert(node);
      else
        visitedCode[node.hashcode] = true;
    }

    list<BFSNode> search()
    {
      clear();
      list<BFSNode> ret;

      if (targetNode == startNode) return ret;
      setVisited(startNode);

      int open = 1;  
      int closed = 0;
      bool found = false;
      path[0] = startNode;
      while (closed < open && !found)
      {
        vector<BFSNode> nexts = path[closed].expandNode();
        for (int i = 0; i < nexts.size(); ++i)
        {
          if (!isVisited(nexts[i]))
          {
            setVisited(nexts[i]);
            nexts[i].father = closed;
            path[open++] = nexts[i];
            if (nexts[i] == targetNode)
            {
              found = true;
              int temp = open - 1;
              ret.push_front(path[temp]);
              while (path[temp].father != -1)
              {
                temp = path[temp].father;
                ret.push_front(path[temp]);
              }
            }
          }
        }
        closed++;
      }
      return ret;
    }
};
    
int main()
{
  BFSSearcher bfs;
  vector<bool> stopData(13, false);
  stopData[3] = 1;
  stopData[6] = 1;
  stopData[8] = 1;
  stopData[9] = 1;
  BFSNode stop(stopData);

  int T;
  cin >> T;
  string temp;
  getline(cin, temp);
  while (T--)
  {
    getline(cin, temp);
    vector<bool> startData(13, false);
    for (int i = 0; i < 13; ++i) 
      startData[i] = temp[i] - '0';
    BFSNode start(startData);

    bfs.startNode = start;
    bfs.targetNode = stop;
    list<BFSNode> ans = bfs.search();

    cout << ans.size() - 1 << endl;
    for (list<BFSNode>::iterator itr = ans.begin(); itr != ans.end(); ++itr)
      if (itr->generateMethod >= 0) cout << itr->generateMethod / 2 << " " << itr->generateMethod % 2 << endl;
  }
  return 0;
}
    
    

