#include <iostream>
using namespace std;
class MaxFlow
{
    public:
        static const int INFINITE = 2147483647;
        static const int MAXNODES = 1000;
        int nodes;

        int capacity[MAXNODES][MAXNODES];
        int flow[MAXNODES][MAXNODES];
        int parent[MAXNODES];
        int path[MAXNODES];
        int delta[MAXNODES];
        bool mark[MAXNODES];

        MaxFlow(int _nodes)
        {
            if (_nodes > MAXNODES) {
                cout << "Too much nodes" << endl;
                return;
            }
            nodes = _nodes;
            clear();
        }

        void clear()
        {
            memset(capacity, 0, sizeof(capacity));
            memset(flow, 0, sizeof(flow));
        }


        int maxFlow(int startNode, int stopNode) 
        {
            int maxFlow = 0;
            memset(flow, 0, sizeof(flow));
            do {
                memset(mark, false, sizeof(mark));
                memset(delta, 0, sizeof(delta));
                path[0] = startNode;
                mark[startNode] = true; 
                delta[startNode] = INFINITE;
                parent[startNode] = -1;
                int open = 1;
                int closed = 0;
                while (closed < open && !mark[stopNode]) {
                    int nowNode = path[closed++];
                    for (int nextNode = 0; nextNode < nodes; ++nextNode) {
                        if (!mark[nextNode] && flow[nowNode][nextNode] < capacity[nowNode][nextNode]) {
                            mark[nextNode] = true;
                            path[open++] = nextNode;
                            parent[nextNode] = nowNode;
                            if (delta[nowNode] < capacity[nowNode][nextNode] - flow[nowNode][nextNode])
                                delta[nextNode] = delta[nowNode];
                            else
                                delta[nextNode] = capacity[nowNode][nextNode] - flow[nowNode][nextNode];
                        }
                    }
                }
                if (!mark[stopNode]) break; 
                maxFlow += delta[stopNode];
                for (int nowNode = stopNode; nowNode != startNode;) { 
                    int nextNode = nowNode;
                    nowNode = parent[nowNode]; 
                    flow[nowNode][nextNode] += delta[stopNode];
                    flow[nextNode][nowNode] = -flow[nowNode][nextNode]; 
                }
            } while (delta[stopNode] > 0);
            return maxFlow;
        }
};

int main()
{
    return 0;
}
