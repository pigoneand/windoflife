#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <cmath>
#include <cstdlib>
using namespace std;

inline int abs(int x)
{
  return x > 0 ? x : -x;
}

const int INF = 2147483647;

/** vector<int> & data : the input data which want to find a bipartition
 *  vector<int> & result : the bipartition result , 0, 1 two cluster ID
 *  return : the score of this bipartition
 */
double findBipartition(vector<int> & data, vector<int> & result)
{
  int N = data.size();
  result = vector<int>(N);

  double center1 = INF;
  double center2 = 0;
  for (int i = 0; i < N; ++i) {
    if (data[i] < center1) 
      center1 = data[i];
    if (data[i] > center2) 
      center2 = data[i];
  }

  double range = center2 - center1;

  const int iteration = 5;

  /** Start Iteration */
  for (int k = 0; k < iteration; ++k) {
    /** Cal new cluster ID for each data based on new center */
    for (int i = 0; i < N; ++i) 
      result[i] = (abs(data[i] - center1) < abs(data[i] - center2)) ? 0 : 1;
    /** Update new cluster center */
    center1 = 0;
    center2 = 0;
    int center1s = 0;
    int center2s = 0;
    for (int i = 0; i < N; ++i) {
      if (result[i] == 0) {
        center1s++;
        center1 += data[i];
      }
      else {
        center2s++;
        center2 += data[i];
      }
    }
    /** If only one cluster remained, just return */
    if (center1s == 0 || center2s == 0) return 0.0;
    center1 /= center1s;
    center2 /= center2s;
  }

  double nowrange = center2 - center1;
  if (range == 0.0) return 0.0;
  return nowrange / range * N;
}

pair<int, double> getBestSplitDim(vector<vector<int> > & records, vector<int> & cluster)
{
  pair<int, double> ret = make_pair(0, 0);
  if (records.size() == 0) 
    return ret;

  int Dims = records[0].size();
  int N = cluster.size();
  vector<int> data(N);
  vector<int> result;
  for (int k = 0; k < Dims; ++k) {
    for (int i = 0; i < N; ++i) 
      data[i] = records[cluster[i]][k];
    double score = findBipartition(data, result);

    if (score > ret.second) {
      ret.second = score;
      ret.first = k;
    }
  }
  return ret;
}

void GDS(vector<vector<int> > & records, int num, vector<vector<int> > & center, vector<int> & clusterID)
{
  if (records.size() == 0) return;

  int N = records.size();
  int Dims = records[0].size();
  vector<pair<vector<int>, pair<int, double> > >  nowClusters; 
  vector<int> cluster;
  vector<int> data;
  vector<int> result;
  for (int i = 0; i < N; ++i) 
    cluster.push_back(i);
  pair<int, double> bestSplitDimInfo = getBestSplitDim(records, cluster);
  nowClusters.push_back(make_pair(cluster, bestSplitDimInfo));

  cout << bestSplitDimInfo.first << "\t" << bestSplitDimInfo.second << endl;

  while (nowClusters.size() < num) {
    cout << "now clusters " << nowClusters.size() << endl;

    /** Find the best cluster to split */
    double bestScore = 0;
    int bestSplitClusterID = -1;
    int bestSplitDim = -1;
    for (int i = 0; i < nowClusters.size(); ++i) {
      if (nowClusters[i].second.second > bestScore) {
        bestScore = nowClusters[i].second.second;
        bestSplitDim = nowClusters[i].second.first;
        bestSplitClusterID = i;
      }
    }
    if (bestSplitClusterID == -1) break;

    cout << "bestSplitClusterID = " << bestSplitClusterID << "\tbestSplitDim = " << bestSplitDim << "\t";

    /** Split the best cluster, generate a new cluster */
    vector<int> & splitCluster = nowClusters[bestSplitClusterID].first;
    data.clear();
    data.resize(splitCluster.size());
    for (int i = 0; i < splitCluster.size(); ++i) 
      data[i] = records[splitCluster[i]][bestSplitDim];
    double score = findBipartition(data, result);

    cout << "score = " << score << endl;

    vector<int> oldCluster;
    vector<int> newCluster;
    for (int i = 0; i < splitCluster.size(); ++i) {
      if (result[i] == 0) 
        oldCluster.push_back(splitCluster[i]);
      else
        newCluster.push_back(splitCluster[i]);
    }
    pair<int, double> oldScore = getBestSplitDim(records, oldCluster);
    pair<int, double> newScore = getBestSplitDim(records, newCluster);
    nowClusters[bestSplitClusterID].first = oldCluster;
    nowClusters[bestSplitClusterID].second = oldScore;
    nowClusters.push_back(make_pair(newCluster, newScore));
  }

  int clusters = nowClusters.size();
  center = vector<vector<int> >(clusters);
  for (int i = 0; i < clusters; ++i) 
    center[i] = vector<int>(Dims, 0);
  clusterID = vector<int>(N);

  for (int k = 0; k < clusters; ++k) {
    for (int i = 0; i < nowClusters[k].first.size(); ++i) {
      clusterID[nowClusters[k].first[i]] = k;
      for (int j = 0; j < Dims; ++j) 
        center[k][j] += records[nowClusters[k].first[i]][j];
    }
    if (nowClusters[k].first.size() == 0) continue;
    for (int j = 0; j < Dims; ++j)
      center[k][j] /= nowClusters[k].first.size();
  }
  return;
}

ostream & operator << (ostream & out, vector<int> & data) 
{
  for (int i = 0; i < data.size(); ++i) 
    out << data[i] << "\t";
  return out;
}

int main()
{
  vector<vector<int> > records;
  for (int i = 0; i < 500000; ++i) {
     vector<int> singlePoint(45);
     for (int k = 0; k < 45; ++k) 
       singlePoint[k] = rand() % 10000;
     records.push_back(singlePoint);
  }
     
  vector<vector<int> > centers;
  vector<int> clusterID;
  cout << "records = " << records.size() << endl;
  GDS(records, 40000, centers, clusterID);

  cout << "Cluster ID for each record " << endl;
  for (int i = 0; i < clusterID.size(); ++i) 
    cout << clusterID[i] << "\t";
  cout << endl;
  cout << "Cluster center for each cluster " << endl;
  for (int i = 0; i < centers.size(); ++i) 
    cout << centers[i] << endl;
  cout << endl;
}

