/*=============================================================================
#     FileName: dna_sorting.cpp
#         Desc: 
#       Author: zhuting
#        Email: cnjs.zhuting@gmail.com
#     HomePage: my.oschina.net/u/1053833
#      Version: 0.0.1
#   LastChange: 2013-11-22 00:25:49
#      History:
=============================================================================*/
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#define maxn 55
#define dna_maxn 105

/*dna结构, id其实是没用的,最后也没有使用.
 * rev是逆序对的个数.*/
struct dna
{
	int id, rev;
	char code[maxn];
};
dna d[dna_maxn];


void swap(dna &x, dna &y)
{
	int tmp = x.rev;
	x.rev = y.rev;
	y.rev = tmp;
	char chp_tmp[maxn];
	strcpy (chp_tmp, x.code);
	strcpy (x.code, y.code);
	strcpy (y.code, chp_tmp);
	return;
}


int main()
{
	int n = 0, m = 0;
	scanf ("%d%d", &n, &m);

	for (int i = 0; i < m; ++i)
	{
		scanf ("%s", d[i].code);

		/* 对于本题的特殊性,求逆序对可以实现O(n).
		 * x_count等记录的是以x为较大元素的逆序对的个数.
		 * 由于本题的元素仅仅只有4种,所以可以这样做.
		 * 从后向前扫一遍字符串,统计x_count的个数*/
		int a_count = 0, c_count = 0, g_count = 0, t_count = 0;
		int rev_sum = 0;
		for (int j = n - 1; j >= 0; --j)
		{
			switch(d[i].code[j])
			{
				case 'A':
					  ++c_count;
					  ++g_count;
					  ++t_count;
					  break;
				case 'C':
					  ++g_count;
					  ++t_count;
					  rev_sum += c_count;
					  break;
				case 'G':
					  ++t_count;
					  rev_sum += g_count;
					  break;
				case 'T':
					  rev_sum += t_count;
					  break;
				default:
					  break;
			}
		}
		d[i].rev = rev_sum;
	}
	
	/*鉴于本题的数据不够大,直接用冒泡.*/
	for (int i = 0; i < m; ++i)
	{
		for (int j = i; j < m; ++j)
		{
			if (d[i].rev > d[j].rev)
			{
				swap(d[i], d[j]);
			}
		}
	}

	for (int i = 0; i < m; ++i)
	{
		printf ("%s\n", d[i].code);
	}
	return 0;
}
