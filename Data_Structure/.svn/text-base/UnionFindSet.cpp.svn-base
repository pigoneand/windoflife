
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>

using namespace std;

/** Union Find Set 
 * O(1) to merge two set
 * O(1) to find which set the given element belong to 
 */
class UnionFindSet
{
    private:
        vector<int> belongTo;

        /** How many different sets exist now */
        int setCount;

    public:
        UnionFindSet(int size)
        {
            belongTo = vector<int>(size);
            clear();
        }

        /** Reset the union find set data */
        void clear()
        {
            for (int i = 0; i < belongTo.size(); ++i) 
                belongTo[i] = -1;
            setCount = belongTo.size();
        }

        /** Return element i's set's representive element */
        int find(int elementID)
        {
            if (belongTo[elementID] < 0)
                return elementID;
            else 
                return belongTo[elementID] = find(belongTo[elementID]);
        }

        /** Return the element i's set's size */
        int getSize(int elementID)
        { 
            int representiveElement = find(elementID);
            return -belongTo[representiveElement];
        }

        /** merge two element */
        void Union(int elementID1, int elementID2)
        {
            int representiveElement1 = find(elementID1);
            int representiveElement2 = find(elementID2);
            if (representiveElement1 == representiveElement2) 
                return;

            setCount--;
            int size1 = -belongTo[representiveElement1];
            int size2 = -belongTo[representiveElement2];

            if (size1 <= size2) {
                belongTo[representiveElement1] = representiveElement2;
                belongTo[representiveElement2] -= size1;
            }
            else {
                belongTo[representiveElement2] = representiveElement1;
                belongTo[representiveElement1] -= size2;
            }
        }

        /** Return different set count */
        inline int getSetCount() 
        {
            return setCount;
        }

        void output(ostream & out)
        {
            out << setCount << endl;
            for (int i = 0; i < belongTo.size(); ++i)
                out << find(i) << "\t";
            out << endl;
        }

        vector<vector<int> > getAllSets() 
        {
            map<int, vector<int> > sets;
            for (int i = 0; i < belongTo.size(); ++i) 
                sets[find(i)].push_back(i);

            vector<vector<int> > ret;
            for (map<int, vector<int> >::iterator itr = sets.begin(); itr != sets.end(); ++itr) 
                ret.push_back(vector<int>(itr->second.begin(), itr->second.end()));
            return ret;
        }
};


int main()
{
    UnionFindSet unionFindSet(10);
    unionFindSet.Union(0,1);
    unionFindSet.Union(2,3);
    unionFindSet.Union(1,3);

    unionFindSet.output(cout);

    vector<vector<int> > sets = unionFindSet.getAllSets();
    for (int i = 0; i < sets.size(); ++i) {
        for (int j = 0; j < sets[i].size(); ++j) 
            cout << sets[i][j] << " ";
        cout << endl;
    }

    return 0;
}
