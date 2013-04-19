#include <vector>
#include <string>
using namespace std;

class TheDevice
{
public:
	int minimumAdditional(vector<string> plates)
	{
		if (plates.size() == 1) return 2;
		if (plates.size() == 2) return 1;
		int N = plates.size();
		int M = plates[0].size();
		for (int m = 0; m < M; ++m)
		{
			int zeroCnt = 0;
			int oneCnt = 0;
			for (int i = 0; i < N; ++i)
			{
				if (plates[i][m] == '0') zeroCnt++;
				if (plates[i][m] == '1') oneCnt++;
			}
			if (oneCnt >= 2 && zeroCnt >= 1) continue;
			return 1;
		}
		return 0;
	}
};
