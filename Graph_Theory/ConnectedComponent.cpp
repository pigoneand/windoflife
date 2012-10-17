#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class ConnectedComponent
{
  public:

    vector<vector<int> > getComponent(vector<vector<int> > & graph)
    {
      int N = graph.size();
      vector<bool> visited(N, false);
      vector<vector<int> > ret;

      for (int i = 0; i < N; ++i)
      {
        if (!visited[i])
        {
          stack<int> nodes;
          vector<int> com;
          nodes.push(i);
          visited[i] = true;
          com.push_back(i);

          while (nodes.size() > 0)
          {
            int nowID = nodes.top();
            nodes.pop();
            for (int j = 0; j < graph[nowID].size(); ++j)
            {
              int otherID = graph[nowID][j];
              if (!visited[otherID])
              {
                visited[otherID] = true;
                nodes.push(otherID);
                com.push_back(otherID);
              }
            }
          }
          ret.push_back(com);
        }
      }
      return ret;
    }
};

int main()
{
  vector<vector<int> > graph;
  return 0;
}
