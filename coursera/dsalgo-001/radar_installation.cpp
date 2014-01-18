/*=============================================================================
#     FileName: radar.cpp
#         Desc: 
#       Author: zhuting
#        Email: cnjs.zhuting@gmail.com
#     HomePage: my.oschina.net/locusxt
#      Version: 0.0.1
#    CreatTime: 2013-12-03 00:12:22
#   LastChange: 2013-12-03 10:20:49
#      History:
=============================================================================*/
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define maxn 1005
using namespace std;

struct line/*区间结构*/
{
	double left;/*左右边界*/
	double right;
};
struct line li[maxn];


bool cmp (struct line a, struct line b)/*sort的比较函数*/
{
	if(a.left == b.left) return b.right < a.right;
	return a.left < b.left;
}

int main()
{
	int i;
	int case_num;
	int n;
	double d;/*尽量都用double,避免错误*/
	double x, y;
	double tmp, l, r;

	double pos;
	int num;
	bool is_possible;/*是否有解*/
	

	case_num = 0;
	while(1)
	{
		++case_num;
		scanf("%d%lf", &n, &d);
		if (!n && !d) break;
		is_possible = 1;
		if (d <= 0) is_possible = 0;/*半径得大于0*/
		for (i = 0; i < n; ++i)
		{
			scanf("%lf%lf", &x, &y);
			if (!is_possible) continue;
			tmp = (d*d - y*y);/*一定大于0*/
			if (tmp < 0 || y < 0)
			{
				is_possible = 0;
				continue;
			}
			tmp = sqrt(tmp);
			l = x - tmp;
			r = x + tmp;
			li[i].left = l;
			li[i].right = r;
		}
		if (!is_possible)
		{
			printf("Case %d: -1\n", case_num);
			continue;
		}

		sort(li, li + n, cmp);

		
		pos = li[0].right;/*一开始,第一个雷达位置为区间0的右边界*/
		num = 1;
		for (i = 1; i < n; ++i)
		{
			if (li[i].left > pos)/*区间左边界在当前雷达的右边,则一定得加一个雷达*/
			{
				++num;
				pos = li[i].right;/*新雷达在区间最右*/
			}
			else if (li[i].right < pos)/*区间右边界在当前雷达左侧,则新雷达移动至现区间右边界*/
				pos = li[i].right;
		}
		printf("Case %d: %d\n", case_num, num);
	}
	return 0;
}
