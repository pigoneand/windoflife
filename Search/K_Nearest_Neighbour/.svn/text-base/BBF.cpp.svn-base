#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <ctime>
#include <map>
using namespace std;

/** Quick find a k-smallest data */
int quickfind(vector<int> & data, int l, int r, int K)
{
  if (l >= r) return data[l];
  int midPosi = l;
  if (data.size() >= 3) {
    int left = l;
    int right = r;
    int mid = (l + r) >> 1;
    vector<pair<int, int> > chooseMid;
    chooseMid.push_back(make_pair(data[left], left));
    chooseMid.push_back(make_pair(data[mid], mid));
    chooseMid.push_back(make_pair(data[right], right));
    sort(chooseMid.begin(), chooseMid.end());
    midPosi = chooseMid[1].second;
  }

  swap(data[l], data[midPosi]);
  int i = l, j = r, k = data[l];
  while (i < j) {
    while (i < j && data[j] >= k) j--;
    if (i < j) { data[i] = data[j]; i++; }
    while (i < j && data[i] <= k) i++;
    if (i < j) { data[j] = data[i]; j--;}
  }
  data[i] = k;

  int leftpart = i - l;
  if (K <= leftpart) return quickfind(data, l, i - 1, K);
  if (K == leftpart + 1) 
    return data[i];
  else 
    return quickfind(data, i + 1, r, K - leftpart - 1);
}

class KDTreeNode
{
  public:
    static const int INF = (1 << 30);

    /** The depth of this node, root = 0 */
    int depth;

    /** The split dimension */
    int splitDim;

    /** The split value */
    int splitValue;

    /** Left right son, for left son, value <= splitvalue 
     * for right son, value > splitvalue
     */
    KDTreeNode * left;
    KDTreeNode * right;

    /** If this node is internal node, save its superbox range 
     * in order to save the superbox storage space, 
     * we use map<dimID, pair<start, stop> > to represent the superbox 
     * if one dimension doesn't appear in the map, that means its range 
     * is [-INF, INF]
     */
    map<int, pair<int, int> > rangeBox;

    /** records pointer */
    vector<vector<int> > * records;

    /** the vector offset in the records */
    int ID;

    /** recs : the data which contain the records */
    KDTreeNode(vector<vector<int> > * recs)
    {
      depth = 0;
      left = right = NULL;
      rangeBox.clear();
      ID = -1;
      records = recs;
    }

    /** Construct by a father node, inherite its property */
    KDTreeNode(KDTreeNode * father)
    {
      depth = father->depth + 1;
      left = right = NULL;
      records = father->records;
      ID = -1;
      rangeBox = father->rangeBox;
    }

    void output(ostream & out, int depth = 0)
    {
      for (int i = 0; i < depth; ++i) cout << " ";
      if (left == NULL) {
        cout << "LEAF " << ID << endl;
      }
      else {
        cout << "[" << splitDim << "]" << "(" << splitValue << ")";
        cout << "\t(";
        map<int, pair<int, int> >::iterator itr;
        for (itr = rangeBox.begin(); itr != rangeBox.end(); ++itr)
          cout << itr->first << "[" << itr->second.first << "->" << itr->second.second << "] ";
        cout << ")";
        cout << endl;
      }
      if (left != NULL) left->output(out, depth + 1);
      if (right != NULL) right->output(out, depth + 1);
    }

    static void buildTree(KDTreeNode * node, vector<vector<int> > & records, vector<int> & needToBuildIDs)
    {
      if (records.size() == 0) return;
      if (needToBuildIDs.size() == 0) return;
      if (needToBuildIDs.size() == 1) {
        node->ID = needToBuildIDs[0];
        return;
      }

      /** Decide the split dimension, calculate each dimension's Variance */
      int N = needToBuildIDs.size();
      int Dims = records[0].size();
      vector<int> dimData(N);
      double maxVar = -1.0;
      int maxVarDim = -1;
      for (int i = 0; i < Dims; ++i) {
        double average = 0;
        for (int j = 0; j < N; ++j) {
          dimData[j] = records[needToBuildIDs[j]][i];
          average += dimData[j];
        }
        average /= N;
        double var = 0;
        for (int j = 0; j < N; ++j) 
          var += (dimData[j] - average) * (dimData[j] - average);
        if (var > maxVar) {
          maxVar = var;
          maxVarDim = i;
        }
      }

      /** Split the data based on the chosen dimension */
      vector<int> left;
      vector<int> right;
      for (int i = 0; i < N; ++i) 
        dimData[i] = records[needToBuildIDs[i]][maxVarDim];
      node->splitValue = quickfind(dimData, 0, dimData.size() - 1, N / 2 + 1);
      node->splitDim = maxVarDim;

      for (int i = 0; i < N; ++i) 
        dimData[i] = records[needToBuildIDs[i]][node->splitDim];
      for (int i = 0; i < N; ++i) 
        if (dimData[i] <= node->splitValue) 
          left.push_back(needToBuildIDs[i]);
        else
          right.push_back(needToBuildIDs[i]);

      /** If the left part or right part 's size = 0 */
      if (left.size() == 0 || right.size() == 0) {
        node->ID = needToBuildIDs[0];
        return;
      }
      node->left = new KDTreeNode(node);
      node->right = new KDTreeNode(node);
      
      /** Maintain the superbox range information */
      if (node->left->rangeBox.find(node->splitDim) == node->left->rangeBox.end())
        node->left->rangeBox[node->splitDim] = make_pair(-INF, INF);
      if (node->right->rangeBox.find(node->splitDim) == node->right->rangeBox.end())
        node->right->rangeBox[node->splitDim] = make_pair(-INF, INF);

      node->left->rangeBox[node->splitDim].second = node->splitValue;
      node->right->rangeBox[node->splitDim].first = node->splitValue + 1;

      /** Recursive build the tree */
      buildTree(node->left, records, left);
      buildTree(node->right, records, right);
      return;
    }

};

/** An extension of K-D tree, a approximiate algorithm for finding k-nearest neighbours
 * with high dimensional feature space and limited time 
 */
class BestBinFirst
{
  public:
    static const int EXPAND = 40;

    KDTreeNode * root;

    /** Construct by given the records pointer */
    BestBinFirst(vector<vector<int> > * records)
    {
      root = new KDTreeNode(records);
    }

    /** Given some records, build the tree */
    void buildTree()
    {
      vector<vector<int> > & records = *(root->records);
      vector<int> needToBuild;
      for (int i = 0; i < records.size(); ++i)
        needToBuild.push_back(i);
      KDTreeNode::buildTree(root, records, needToBuild);
    }

    static inline double distance(vector<int> & p1, vector<int> & p2)
    {
      double dist = 0.0;
      for (int i = 0; i < p1.size(); ++i) 
        dist += (p1[i] - p2[i]) * (p1[i] - p2[i]);
      return sqrt(dist);
    }

    static inline double distance(KDTreeNode * node, vector<int> & point)
    {
      if (node->left == NULL) {
        return distance((*(node->records))[node->ID], point);
      }
      else
        return distance(node->rangeBox, point);
    }

    /** Given a point , and a hyperrectangle, return their distance */
    static inline double distance(map<int, pair<int, int> > & superBox, 
        vector<int> & point)
    {
      int dim = point.size();
      vector<int> p(dim);

      for (int i = 0; i < dim; ++i) 
        p[i] = point[i];

      map<int, pair<int, int> >::iterator itr;
      for (itr = superBox.begin(); itr != superBox.end(); ++itr) {
        int dim = itr->first;
        if (point[dim] <= itr->second.first)
          p[dim] = itr->second.first;
        if (point[dim] >= itr->second.second)
          p[dim] = itr->second.second;
      }
      return distance(point, p);
    }

    /** Given a point , and a hyperrectangle, return their distance */
    static inline double distance(vector<int> & minRect, vector<int> & maxRect, 
        vector<int> & point)
    {
      int dim = minRect.size();
      vector<int> p(dim);

      for (int i = 0; i < dim; ++i) {
        if (point[i] <= minRect[i])
          p[i] = minRect[i];
        else {
          if (point[i] >= maxRect[i])
            p[i] = maxRect[i];
          else 
            p[i] = point[i];
        }
      }
      return distance(point, p);
    }

    /** 判断一个超立方体是否与一个超球体相交 */
    static inline bool intersect(vector<int> & minRect, vector<int> & maxRect,
        vector<int> & cirPoint, double radius)
    {
      double dis = distance(minRect, maxRect, cirPoint);
      return dis <= radius;
    }

    static inline bool intersect(map<int, pair<int, int> > & superBox, 
        vector<int> & cirPoint, double radius)
    {
      double dis = distance(superBox, cirPoint);
      return dis <= radius;
    }

    int bestK;
    priority_queue<double, vector<double> > nowBestK;
    priority_queue<pair<double, KDTreeNode *>, 
      vector<pair<double, KDTreeNode * > >, greater<pair<double, KDTreeNode *> > > queue;
    vector<pair<double, KDTreeNode * > > answers;

    void freshNowBest(double dis)
    {
      if (nowBestK.size() < bestK) 
        nowBestK.push(dis);
      else {
        if (nowBestK.top() > dis) 
          nowBestK.push(dis);
      }
      while (nowBestK.size() > bestK) 
        nowBestK.pop();
    }

    inline double getMaxAcceptDis()
    {
      if (nowBestK.size() < bestK) 
        return 1e20;
      else
        return nowBestK.top();
    }

    /** From a node, trace to a leaf, maintain the best bin heap */
    void search(KDTreeNode * node, vector<int> & searchVector)
    {
      while (node->left != NULL) {
        if (searchVector[node->splitDim] <= node->splitValue) {
          double dis = distance(node->right, searchVector);
          if (dis <= getMaxAcceptDis()) queue.push(make_pair(dis, node->right));
          node = node->left;
        }
        else {
          double dis = distance(node->left, searchVector);
          if (dis <= getMaxAcceptDis()) queue.push(make_pair(dis, node->left));
          node = node->right;
        }
      }
      double dis = distance(node, searchVector);
      freshNowBest(dis);
      answers.push_back(make_pair(dis, node));
      return;
    }

    /** Given a vector, search the tree, return the apprixomiate K-nearest vector ID */
    vector<int> searchKNearest(vector<int> & searchVector, int K)
    {
      /** Clear the previous data */
      while (!queue.empty())
        queue.pop();
      while (!nowBestK.empty())
        nowBestK.pop();
      bestK = K;
      answers.clear();

      /** search */
      search(root, searchVector);
      while (!queue.empty() && answers.size() <= K * EXPAND) {
        KDTreeNode * node = queue.top().second;
        queue.pop();
        search(node, searchVector);
      }

      /** output answer */
      sort(answers.begin(), answers.end());
      int select = min(K, (int)answers.size());
      vector<int> ret;
      double total = 0.0;
      for (int i = 0; i < select; ++i) {
        total += answers[i].first;
        ret.push_back(answers[i].second->ID);
      }

      double totalbest = 0.0;
      while (!nowBestK.empty()) {
        totalbest += nowBestK.top();
        nowBestK.pop();
      }

      return ret;
    }
};


int main()
{
  /** Read data */
  vector<vector<int> > * precords = new vector<vector<int> >();
  vector<vector<int> > & records = *precords;
  int temp;
  while (scanf("%d", &temp) == 1) {
    vector<int> single;
    single.push_back(temp);
    for (int i = 0; i < 959; ++i) {
      scanf("%d", &temp);
      single.push_back(temp);
    }
    records.push_back(single);
  } 

  /** Remove duplicated */
  sort(records.begin(), records.end());
  records.resize(unique(records.begin(), records.end()) - records.begin());
  cout << records.size() << endl;

  /** Construct the tree */
  BestBinFirst search(precords);
  search.buildTree();
  cout << "Tree Constructed " << endl;

  /** Test performance */
  clock_t start = clock();
  double averageErr = 0;
  double total1 = 0;
  double total2 = 0;
  for (int i = 0; i < 100; ++i) {
    clock_t s1 = clock();
    vector<int> result = search.searchKNearest(records[i], 10);
    clock_t t1 = clock();

    double answer1 = 0;
    for (int j = 0; j < result.size(); ++j) {
      answer1 += BestBinFirst::distance(records[i], records[result[j]]);
    }

    clock_t s2 = clock();
    vector<double> dists;
    for (int j = 0; j < records.size(); ++j)
      dists.push_back(BestBinFirst::distance(records[i], records[j]));
    sort(dists.begin(), dists.end());
    clock_t t2 = clock();
    double answer2 = 0;
    for (int j = 0; j < result.size(); ++j)
      answer2 += dists[j];

    double wucha = fabs(answer1 - answer2) / answer2 * 100;
    averageErr += wucha;
    total1 += (t1 - s1);
    total2 += (t2 - s2);
  }
  clock_t stop = clock();
  cout << "total spent = " << (double)(stop - start) / CLOCKS_PER_SEC << endl;
  cout << "BBF spent = " << (double) total1 / CLOCKS_PER_SEC << endl;
  cout << "Brute Force = " << (double) total2 / CLOCKS_PER_SEC << endl;
  averageErr /= 100;
  cout << "average Err = " << averageErr << "%" << endl;
  
  return 0;
}








