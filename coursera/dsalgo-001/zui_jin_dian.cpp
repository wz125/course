/*=============================================================================
#     FileName: min_dist.cpp
#         Desc: poj 3714
#       Author: zhuting
#        Email: cnjs.zhuting@gmail.com
#     HomePage: my.oschina.net/locusxt
#      Version: 0.0.1
#    CreatTime: 2013-12-02 19:01:32
#   LastChange: 2013-12-02 21:06:34
#      History: 补注释
=============================================================================*/

/*
 * 据说直接用int记点是过不了的
 * 所以用double或者long long
 */
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#define maxn 200005
using namespace std;

const double inf = 1e100;

class point
{
	public:
		double x;
		double y;
		bool flag;/*标志阵营*/
};
point poi[maxn];

int ordy[maxn] = {0};/*按y的顺序排序,一开始数组开在里面,一直re= =*/

bool cmpx(point a, point b)/*点按x排序*/
{
	return a.x < b.x;
}

bool cmpy(int a, int b)
{
	return poi[a].y < poi[b].y;
}

double dist(int a, int b)/*计算两点距离,当属于同阵营则距离无限大*/
{
	if (poi[a].flag == poi[b].flag)
		return inf;

	double ax = poi[a].x;
	double ay = poi[a].y;
	double bx = poi[b].x;
	double by = poi[b].y;
	return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

/*
 * 二分的思想
 * 区域按x从大到小等分成两块s1,s2
 * 最小距离点对的两个点有三种情况,都在s1;都在s2;一个在s1,一个在s2
 * 都在同一区域的则递归地找
 * 当左边界等于右边界,即只有一个点,返回inf
 * 只有两个点,直接返回距离
 * 比较两区域最小值大小,取小者为md
 * 
 * 不在同一区域,则将距分界线x向距离md以内的点找出
 * 并按y大小排序
 * 对这些点,依次与其后6个点求距离,更新md(至于这里为什么是对其后6个点求距离就够了,需要额外证明,这里略去,这里对y向距离小于md的求距离也一样的)
 * 
 * 最后返回md
 */

double min_dist(point* p, int left, int right)
{
	double md = inf;
	if (left == right) 
		return md;
	if (left + 1 == right)
		return dist(left, right);
	int mid = (left + right) >> 1;
	double l_md = min_dist(p, left, mid);
	double r_md = min_dist(p, mid + 1, right);
	if (l_md < r_md) md = l_md;
	else md = r_md;

	int cur = 0;
	
	
	for (int i = mid; i >= left; --i)
	{
		if (p[mid].x - p[i].x <= md)
			ordy[cur++] = i;
		else break;
	}
	for (int i = mid + 1; i <= right; ++i)
	{
		if (p[i].x - p[mid].x <= md)
			ordy[cur++] = i;
		else break;
	}

	sort(ordy, ordy + cur, cmpy);
	for (int i = 0; i < cur; ++i)
		for (int j = i + 1; j <= i + 6; ++j)
		{
			if (j >= cur) break;
			if (p[ordy[j]].y - p[ordy[i]].y >= md)
				break;
			double tmp = dist(ordy[i], ordy[j]);
			if (tmp < md)
				md =tmp;
		}
	return md;
}

int main()
{
	int t = 0, n = 0;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
		{
			scanf ("%lf%lf", &poi[i].x, &poi[i].y);
			poi[i].flag = 1;
		}
		for (int i = n; i < 2 * n ; ++i)
		{
			scanf ("%lf%lf", &poi[i].x, &poi[i].y);
			poi[i].flag = 0;
		}
		
		sort(poi, poi + 2 * n, cmpx);
		double ans = min_dist(poi, 0, 2 * n - 1);

		printf("%.3lf\n", ans);

	}
	return 0;
}
