#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <utility>
using namespace std;

#define APRIORI_DATASTRUCT T

template <class T> class Apriori
{
    private:
        set<T> set_union(const set<T> &a, const set<T> &b)
        {
            set<T> ret;
            ret.clear();
            for (typename set<T>::iterator itr = a.begin();itr!=a.end();++itr)
                ret.insert(*itr);
            for (typename set<T>::iterator itr = b.begin();itr!=b.end();++itr)
                ret.insert(*itr);
            return ret;
        }

        set<T> set_intersect(const set<T> &a, const set<T> &b)
        {
            set<T> ret;
            ret.clear();
            for (typename set<T>::iterator itr = a.begin(); itr!=a.end(); ++itr)
                if (b.find((*itr)) != b.end()) ret.insert(*itr);
            return ret;
        }

        bool containSet(const set<T> &a, const set<T> &b)
        {
            for (typename set<T>::iterator itr = b.begin(); itr!=b.end(); ++itr)
                if (a.find(*itr) == a.end()) return false;
            return true;
        }

    public:
        /** Use apriori algorithm to mining frequent itemset,
         * vector[0] .. vector[N-1] stands for i+1-occurance frequent set 'set
         * set<T> stands for a frequent item subset
         * set<set<T> > stands for the frequent item subset's set
         */
        vector<set<set<T > > > miningFrequentPattern(
               vector<set<T> > itemList,
               double supportRadio, 
               int maxFrequentSetSize,
               int maxFrequentSetCountSize = 100) 
        {
            int lists = itemList.size();
            int support = (int)((double)lists * supportRadio);

            /** First Mining one-occurance frequent pattern */
            set<T> allitems;
            for (int i = 0; i < itemList.size(); ++i) {
                for (typename set<T>::iterator itr = itemList[i].begin(); 
                        itr != itemList[i].end(); ++itr)
                    allitems.insert(*itr);
            }

            set<set<T> > onefrequent;
            for(typename set<T>::iterator itr = allitems.begin(); 
                    itr != allitems.end(); ++itr) {
                int count = 0;
                for (int i = 0; i < itemList.size(); ++i)
                    if (itemList[i].find(*itr) != itemList[i].end())
                        count++;
                if (count >= support) {
                    set<T> subset;
                    subset.insert(*itr);
                    onefrequent.insert(subset);
                }
            }
            
            vector<set<set<T> > > result;
            result.push_back(onefrequent);

            /** Then we mining i-occurance frequent subset step by step */
            for (int i = 2; i <= maxFrequentSetSize; ++i) {
                typename set<set<T> >::iterator itr1;
                typename set<set<T> >::iterator itr2;
                set<set<T> > & last = result[i-2];
                set<set<T> > next;
                for (itr1 = last.begin(); itr1 != last.end(); ++itr1)
                    for (itr2 = itr1; itr2 != last.end(); ++itr2) {
                        if (itr2 != itr1) {
                            set<T> unionset = set_union(*itr1 , *itr2);
                            if (unionset.size() == (*itr1).size() + 1) {
                                set<T> interset = set_intersect(*itr1 , *itr2);
                                int count = 0;
                                for (int k = 0; k < itemList.size(); ++k)
                                    if (containSet(itemList[k] , unionset))
                                        count++;
                                if (count >= support)
                                    next.insert(unionset);
                            }
                        }
                    }
                if (next.size() == 0) break;
                result.push_back(next);
                if (next.size() > maxFrequentSetCountSize) break;
            }
            return result;
        }
};

int main()
{
    
    long long data1[4] = {1,2,3,4};
    long long data2[3] = {2,3,4};
    long long data3[2] = {2,3};
    long long data4[3] = {1,2,4};
    long long data5[4] = {1,2,3,4};
    long long data6[2] = {2,4};
    set<long long> set1(data1, data1 + 4);
    set<long long> set2(data2, data2 + 3);
    set<long long> set3(data3, data3 + 2);
    set<long long> set4(data4, data4 + 3);
    set<long long> set5(data5, data5 + 4);
    set<long long> set6(data6, data6 + 4);

    vector<set<long long> > itemList;
    itemList.push_back(set1);
    itemList.push_back(set2);
    itemList.push_back(set3);
    itemList.push_back(set4);
    itemList.push_back(set5);
    itemList.push_back(set6);


    Apriori<long long> apriori;
    vector<set<set<long long> > > answer = apriori.miningFrequentPattern(
            itemList , 0.5 , 5 , 100);

    for (int i = 0; i < answer.size(); ++i) {
        cout << "#####" << i << "#####" << endl;
        set<set<long long> >::iterator itr;
        for (itr = answer[i].begin(); itr != answer[i].end(); ++itr) {
            for (set<long long>::iterator itr2 = (*itr).begin();
                    itr2 != (*itr).end(); ++itr2)
                cout << (*itr2) << " ";
            cout << endl;
        }
    }

    return 0;
}
                
            

