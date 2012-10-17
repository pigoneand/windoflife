//pku2195 go home
//最大权完美匹配问题
//参考文献《网络算法与复杂性理论》 P212-P213
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;

/** The Node ID START FROM 1 !!!! 
 */
class BipartiteGraphMaxScoreMatch
{
    public:
        static const int INF = 0x1fffffff;
        static const int MAXN = 1000;
        int pCost[MAXN][MAXN];//p->h
        int nCount;
        int xVal[MAXN];
        int yVal[MAXN];
        int Mx[MAXN];//M中x的对应节点，0说明x未饱和
        int My[MAXN];//M中y的对应节点，0说明y未饱和
        int yslack[MAXN];
        int xmark[MAXN];//标号，-1说明没标号
        int ymark[MAXN];

    private:
        void ClearMark()
        {
            //清空标记
            for (int i = 1; i <= nCount; i++)
            {
                yslack[i] = INF;
                xmark[i] = -1;
                ymark[i] = -1;
            }
        }

        bool refresh_xyval(queue<int>& notCheck,int& yIndex)
        {//返回true说明成功找到未饱和y，yIndex当找到未饱和y时保存其下标
            int i,minVal=INF;
            vector<int> yslack_zero;//保存更新之后yslack为零的y下标
            for (i=1;i<=nCount;i++)if(yslack[i]>0)
                minVal=min(minVal,yslack[i]);//在所有未能与已标记x匹配的y的松弛向量中（yslack[i]>0）查找最小的
            for(i=1;i<=nCount;i++)
            {//刷新xVal,yVal
                if (xmark[i]!=-1)
                    xVal[i]-=minVal;
                if (ymark[i]!=-1)
                    yVal[i]+=minVal;
                else
                {//在刷新xVal之后，看看是否有新的可连接的y（更新yslack）
                    yslack[i]-=minVal;
                    if (yslack[i]==0)
                        yslack_zero.push_back(i);
                }
            }
            for (i=0;i<yslack_zero.size();i++)
            {//对每个可连接的y进行处理
                int curIndex=yslack_zero[i];
                for (int j=1;j<=nCount;j++)
                {//查找修正xVal后与y匹配的有标号的x
                    if (xmark[j]!=-1&&xVal[j]+yVal[curIndex]==pCost[j][curIndex])
                    {
                        ymark[curIndex]=j;
                        break;
                    }
                }
                if(My[curIndex])
                {//饱和,标记yj在M中对应的x为j，并将其标为未检查。此处不改变yVal的值
                    xmark[My[curIndex]]=curIndex;
                    notCheck.push(My[curIndex]);
                }
                else
                {//未饱和，记录y的下标，成功返回
                    yIndex=curIndex;
                    return true;
                }
            }
            return false;
        }

        void zengguang(int yIndex)
        {//逆向搜索增广路径（交叉链），沿途更新M
            int xIndex;
            do
            {//从未饱和的y到未饱和的x（未饱和）
                xIndex=ymark[yIndex];
                My[yIndex]=xIndex;
                Mx[xIndex]=yIndex;
            }while(yIndex=xmark[xIndex]);
        }

    public:
        int km(vector<int> & leftMatch)
        {//km算法
            ready();
            int yIndex,i,j;//yIndex搜索到的要加入M的未饱和y
            for (i=1;i<=nCount;i++)
            {//nCount次，每次加入一个y
                ClearMark();//在新一轮检查前，清空所有标记
                queue<int> notCheck;//检查队列
                for (j=1;j<=nCount;j++)
                {//对于每个非饱和点标记为0，并加入为检查队列
                    if(!Mx[j])
                    {//非饱和点
                        xmark[j]=0;
                        notCheck.push(j);
                    }
                }
                while (1)
                {//寻找未饱和的y
                    bool ok=false;
                    while (!notCheck.empty())
                    {//检查所有未检查的x
                        int xIndex=notCheck.front();notCheck.pop();
                        for (j=1;j<=nCount;j++)
                        {//处理未被标记的y ，说明此轮检查尚没有边与该y相连，但该y可能在M中（是饱和点）
                            if(ymark[j]==-1)
                            {
                                yslack[j]=min(yslack[j],xVal[xIndex]+yVal[j]-pCost[xIndex][j]);
                                if (!yslack[j])
                                {//可连线
                                    ymark[j]=xIndex;
                                    if (!My[j])
                                    {//成功找到非饱和y
                                        yIndex=j;
                                        ok=true;break;
                                    }
                                    else
                                    {//标记yj在M中对应的x为j，并将其标为未检查。
                                        xmark[My[j]]=j;
                                        notCheck.push(My[j]);
                                    }
                                }
                            }
                        }
                        if (ok)break;
                    }
                    if (ok||refresh_xyval(notCheck,yIndex)) break;//若ok==false,则更新xVal，yVal
                }
                zengguang(yIndex);//更新M
            }
            int ans=0;
            for (i = 1; i <= nCount; i++)
                ans += xVal[i] + yVal[i];
            leftMatch = vector<int>(nCount);
            for (int i = 1; i <= nCount; ++i)
                leftMatch[i-1] = Mx[i];
            return ans;
        }

        void ready()
        {
            memset(yVal,0,sizeof(yVal));
            ClearMark();
            memset(Mx,0,sizeof(Mx));
            memset(My,0,sizeof(My));
        }

};

BipartiteGraphMaxScoreMatch graph;

int main()
{
    int N, M;
    vector<pair<int, int> > Hs;
    vector<pair<int, int> > Ms;
    while (scanf("%d%d",&N,&M) == 2)
    {
        if (N == 0 && M == 0) break;
        Hs.clear();
        Ms.clear();
        for (int i=1;i<=N;i++)
        {
            for (int j=1;j<=M;j++)
            {
                char tmp;
                while (tmp=getchar(),tmp!='.'&&tmp!='H'&&tmp!='m');
                if(tmp=='H')
                    Hs.push_back(make_pair(i, j));
                else if (tmp=='m')
                    Ms.push_back(make_pair(i, j));
            }
        }
        int i,j,maxVal=0;
        memset(graph.pCost,0,sizeof(graph.pCost));
        int nCount = Hs.size();
        graph.nCount = Hs.size();
        for (i=1;i<=nCount;i++)
        {
            maxVal=0;
            for (j=1;j<=nCount;j++)
            {//用 2*nCount去减，将问题转化为最大权完美匹配问题
                graph.pCost[i][j]=
                    2*nCount-abs(Hs[i-1].first-Ms[j-1].first)-abs(Hs[i-1].second-Ms[j-1].second);
                maxVal=max(graph.pCost[i][j],maxVal);
            }
            graph.xVal[i]=maxVal;
        }
        vector<int> leftMatch;
        printf("%d\n", 2 * nCount * nCount - graph.km(leftMatch));
    }
    return 0;
}
