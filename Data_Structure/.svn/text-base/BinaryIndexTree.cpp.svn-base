/** 
 * id range from 1 to maxX 
 * http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees
 */
const int maxX = 128;
struct Cube3D
{
	long long sum[maxX + 1][maxX + 1][maxX + 1];

	Cube3D()
	{
		memset(sum, 0, sizeof(sum));
	}

	long long queryXYZ(int x, int y, int z)
	{
		if (x <= 0 || y <= 0 || z <= 0) return 0;
		long long ret = 0;
		while (x > 0)
		{
			ret += queryYZ(x, y, z);
			x -= x & (-x);
		}
		return ret;
	}

	long long queryYZ(int x, int y, int z)
	{
		long long ret = 0;
		while (y > 0)
		{
			ret += queryZ(x, y, z);
			y -= y & (-y);
		}
		return ret;
	}

	long long queryZ(int x, int y, int z)
	{
		long long ret = 0;
		while (z > 0)
		{
			ret += sum[x][y][z];
			z -= z & (-z);
		}
		return ret;
	}

	void updateXYZ(int x, int y, int z, int delta)
	{
		while (x <= maxX)
		{
			updateYZ(x, y, z, delta);
			x += x & (-x);
		}
	}

	void updateYZ(int x, int y, int z, int delta)
	{
		while (y <= maxX)
		{
			updateZ(x, y, z, delta);
			y += y & (-y);
		}
	}

	void updateZ(int x, int y, int z, int delta)
	{
		while (z <= maxX)
		{
			sum[x][y][z] += delta;
			z += z & (-z);
		}
	}

	long long getRange(int x1, int y1, int z1, int x2, int y2, int z2)
	{
		long long xyz = queryXYZ(x2, y2, z2);
		long long xx1 = queryXYZ(x1 - 1, y2, z2);
		long long yy1 = queryXYZ(x2, y1 - 1, z2);
		long long zz1 = queryXYZ(x2, y2, z1 - 1);
		long long xy1 = queryXYZ(x1 - 1, y1 - 1, z2);
		long long yz1 = queryXYZ(x2, y1 - 1, z1 - 1);
		long long xz1 = queryXYZ(x1 - 1, y2, z1 - 1);
		long long xxyyzz = queryXYZ(x1 - 1, y1 - 1, z1 - 1);
		return xyz - xx1 - yy1 - zz1 + xy1 + yz1 + xz1 - xxyyzz;
	}
};