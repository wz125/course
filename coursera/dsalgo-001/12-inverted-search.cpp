/*=============================================================================
#     FileName: inverted_search.cpp
#         Desc: 
#       Author: zhuting
#        Email: cnjs.zhuting@gmail.com
#     HomePage: my.oschina.net/locusxt
#      Version: 0.0.1
#    CreatTime: 2013-12-17 18:38:37
#   LastChange: 2013-12-17 18:38:37
#      History:
=============================================================================*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
#define maxn 1000005/*文件数目最大为1000005, 编号大小为int范围需要hash一下*/
using namespace std;

typedef map <int, int> hmap;/*前面是hash后的值*/
map <int, int> rehmap;/*前面是hash前的值*/
hmap mymap;

bitset <maxn> mybs[1005];/*每个单词对应出现过的文件*/
int id_sum = 0;/*文件总数*/
bitset <maxn> bs_tmp;

int main()
{
	int n = 0;
	int doc_sum = 0, id = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &doc_sum);
		for (int j = 0; j < doc_sum; ++j)
		{
			scanf("%d", &id);
			int tmp = rehmap[id];
			if (tmp == 0)/*如果当前还没有加入这个文件*/
			{
				++id_sum;
				mymap[id_sum] = id;
				rehmap[id] = id_sum;
				tmp = id_sum;
			}
			
			mybs[i + 1][tmp] = 1;
		}
	}

	int m = 0;
	int state = 0;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i)
	{
		bool is_first = 1, is_find = 0;
		for (int j = 0; j < n; ++j)
		{
			scanf("%d", &state);
			if (state == 1)/*该单词需要存在*/
			{
				if (is_first)
				{
					bs_tmp = mybs[j + 1];
					is_first = 0;
				}
				else bs_tmp &= mybs[j + 1];
			}
			else if (state == -1)/*该单词不存在*/
			{
				if (is_first)
				{
					bs_tmp = ~mybs[j + 1];
					is_first = 0;
				}
				else bs_tmp &= ~mybs[j + 1];
			}
		}


		if (bs_tmp.none())/*不存在符合条件的文件*/
		{
			printf("NOT FOUND\n");
			continue;
		}

		is_first = 1;
		set <int> set_tmp;/*用set对文件编号排序*/
		for (int j = 1; j <= id_sum; ++j)
		{
			if (bs_tmp[j])
				set_tmp.insert(mymap[j]);
		}
		set <int> :: iterator setp = set_tmp.begin();
		while (setp != set_tmp.end())
		{
			if (!is_first)
				printf(" ");
			is_first = 0;
			printf("%d", *setp);
			setp++;
		}
		printf("\n");
	}
	return 0;
}
