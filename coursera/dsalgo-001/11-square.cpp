/*=============================================================================
#     FileName: square.cpp
#         Desc: poj 2002
#       Author: zhuting
#        Email: cnjs.zhuting@gmail.com
#     HomePage: my.oschina.net/locusxt
#      Version: 0.0.1
#    CreatTime: 2013-12-04 18:27:36
#   LastChange: 2013-12-04 19:35:39
#      History:
=============================================================================*/
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <vector>
#define maxn 1005
#define maxl 40005
#define offset 20000/*偏移避免负数*/
using namespace std;

/*不hash会爆内存...*/

class point
{
	public:
		int x;
		int y;
		point()
		{
			x = 0;
			y = 0;
		}
};
point p[maxn];

class hash/*拉链法解决冲突的问题*/
{
	public:
		vector <int> vn;
};

hash h[maxl];



bool find(int x, int y)/*寻找是否有点(x,y)*/
{
	int len = h[x].vn.size();
	if (len == 0) return 0;
	for (int i = 0; i < len; ++i)
	{
		if (h[x].vn[i] == y)
			return 1;
	}
	return 0;
}

void add(int x, int y)/*加入点*/
{
	h[x].vn.push_back(y);
	return;
}

int main()
{
	int n = 0;
	int xtmp = 0, ytmp = 0;
	while(scanf("%d", &n) && n)
	{
		memset (p, 0, sizeof(p));
		memset (h, 0, sizeof(h));
		for (int i = 0; i < n; ++i)
		{
			scanf("%d%d", &xtmp, &ytmp);
			xtmp += offset;
			ytmp += offset;
			add(xtmp, ytmp);
			p[i].x = xtmp;
			p[i].y = ytmp;
		}
		/*没有必要排序*/
		//sort(p, p + n, cmpx);

		int square_num = 0;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
			{
				int pix = p[i].x;
				int piy = p[i].y;
				int pjx = p[j].x;
				int pjy = p[j].y;
				int dy = pjy - piy;
				int dx = pjx - pix;
				/*分直线上下找*/
				if (find(pix - dy, piy + dx) && find(pjx - dy, pjy + dx))
				{
					++square_num;
				}
				if (find(pix + dy, piy - dx) && find(pjx + dy, pjy - dx))
				{
					++square_num;
				}
			}
		printf("%d\n", square_num / 4);/*存在重复*/
	}
	return 0;
}
