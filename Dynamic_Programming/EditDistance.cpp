#include <vector>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class EditDistance
{
    public:
        static const int LEFTMOVE = -1;
        static const int RIGHTMOVE = -2;
        static const int DOUBLEMOVE = -3;

        static const int INSERTCOST = 2;
        static const int REPLACECOST = 3;
        static const int INFINITECOST = 99999999;

        static const int MAXLEN = 100;
        
        static pair<string , string> getMinEditString(vector<string> & left , 
                vector<string> & right)
        {
            static int edit[MAXLEN][MAXLEN];
            static int come[MAXLEN][MAXLEN];
            edit[0][0] = 0;

            for (int i = 1; i <= left.size(); ++i) {
                edit[i][0] = edit[i-1][0] + INSERTCOST;
                come[i][0] = LEFTMOVE;
            }
            for (int j = 1; j <= right.size(); ++j) {
                edit[0][j] = edit[0][j-1] + INSERTCOST;
                come[0][j] = RIGHTMOVE;
            }

            for (int i = 1; i <= left.size(); ++i) {
                for (int j = 1; j <= right.size(); ++j) {
                    edit[i][j] = INFINITECOST;
                    if (edit[i-1][j] + 1 < edit[i][j]) {
                        edit[i][j] = edit[i-1][j] + INSERTCOST;
                        come[i][j] = LEFTMOVE;
                    }
                    if (edit[i][j-1] + 1 < edit[i][j]) {
                        edit[i][j] = edit[i][j-1] + INSERTCOST;
                        come[i][j] = RIGHTMOVE;
                    }
                    int cost = (left[i-1] != right[j-1]) ? REPLACECOST : 0;
                    if (edit[i-1][j-1] + cost < edit[i][j]) {
                        edit[i][j] = edit[i-1][j-1] + cost;
                        come[i][j] = DOUBLEMOVE;
                    }
                }
            }

            pair<string , string> ans;
            ans.first = "";
            ans.second = "";

            int leftPosi = left.size();
            int rightPosi = right.size();
            while (leftPosi >= 1 || rightPosi >= 1) {
                if (come[leftPosi][rightPosi] == LEFTMOVE) {
                    ans.first = left[leftPosi - 1] + ans.first;
                    leftPosi--;
                }
                else {
                    if (come[leftPosi][rightPosi] == RIGHTMOVE) {
                        ans.second = right[rightPosi - 1] + ans.second;
                        rightPosi--;
                    }
                    else {
                        if (left[leftPosi - 1] != right[rightPosi - 1]) {
                            ans.first = left[leftPosi - 1] + ans.first;
                            ans.second = right[rightPosi - 1] + ans.second;
                        }
                        leftPosi--;
                        rightPosi--;
                    }
                }
            }
            return ans;
        }
};


int main()
{
    vector<string> left;
    vector<string> right;
    left.push_back("a");
    left.push_back("b");
    left.push_back("c");
    left.push_back("d");

    right.push_back("a");
    right.push_back("c");
    right.push_back("d");
    right.push_back("d");

    pair<string , string> ans = EditDistance::getMinEditString(left , right);
    cout << ans.first << " " << ans.second << endl; 

    return 0;
}
