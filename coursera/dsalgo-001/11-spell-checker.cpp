/*=============================================================================
#     FileName: spell.cpp
#         Desc: poj 1035
#       Author: zhuting
#        Email: cnjs.zhuting@gmail.com
#     HomePage: my.oschina.net/locusxt
#      Version: 0.0.1
#    CreatTime: 2013-12-04 15:44:51
#   LastChange: 2013-12-04 19:35:52
#      History:
=============================================================================*/

/*
 * 数据在http://poj.org/showmessage?message_id=172686
 */
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#define max_len 16
#define maxn 10005
using namespace std;

class word
{
public:
	char c[max_len];
	int len;
};
word w[maxn];/*字典类*/


/*
 * 一开始以为要分情况讨论的.....
 * 找到一样的state置4
 * 找到修改的置3
 * 找到短的置2
 * 找到长的置1
 * 找不到置0
 */

void find(char tof[], int len, int dic_n, int &state)/*tof为要找的字符串,state为4时已经找到完全匹配的字符串*/
{
	char* cur = NULL;/*没用*/
	int cur_num = 0;
	vector <char*> vc;/*记录相似字符串的指针*/

	for (int i = 0; i < dic_n; ++i)
	{
		if (state == 4) break;
		int delta = w[i].len - len;
		switch (delta)
		{
		case 0:
		{
			if (state == 4) break;
			int error_num = 0;/*失配的次数*/
			for (int j = 0; j < len; ++j)
			{
				if (error_num >= 2) break;
				if (w[i].c[j] != tof[j]) ++error_num;
			}
			if (error_num == 0)
			{
				cur = w[i].c;
				state = 4;
			}
			else if (error_num == 1)
			{
				vc.push_back(w[i].c);
				state = 3;
			}
			break;
		}
		case 1:
		{
			if (state == 4) break;
			int j = 0, k = 0;
			bool is_add = 0;/*记录是否已经失配过*/
			while (j < len + 1 && k < len)
			{
				if (w[i].c[j] == tof[k])
				{
					++j;
					++k;
				}
				else
				{
					if (is_add) break;
					++j;
					is_add = 1;
				}
			}
			if (k == len)/*这里的边界条件很重要*/
			{
				vc.push_back(w[i].c);
				state = 1;
			}
			break;
		}
		case -1:
		{
			if (state == 4) break;
			int j = 0, k = 0;
			bool is_add = 0;
			while (j < len - 1 && k < len)
			{
				if (w[i].c[j] == tof[k])
				{
					++j;
					++k;
				}
				else
				{
					if (is_add) break;
					++k;
					is_add = 1;
				}
			}
			if (j == len - 1)/*重要*/
			{
				vc.push_back(w[i].c);
				state = 2;
			}
			break;
		}
		default:
			break;
		}
	}
	if (state == 4)
	{
		printf("%s is correct\n", tof);
		return;
	}
	printf("%s:", tof);
	for (int i = 0; i < vc.size(); ++i)
	{
		printf(" %s", vc[i]);
	}
	printf("\n");
	return;

}


int main()
{
	char ch_tmp[max_len];
	int dic_num = 0;

	while (true)
	{
		scanf("%s", ch_tmp);
		if (ch_tmp[0] != '#')
		{
			w[dic_num].len = strlen(ch_tmp);
			strcpy(w[dic_num++].c, ch_tmp);
		}
		else break;
	}

	while (true)
	{
		scanf("%s", ch_tmp);
		if (ch_tmp[0] == '#') break;
		int tmp_len = strlen(ch_tmp);
		int state = 0;
		find(ch_tmp, tmp_len, dic_num, state);
	}
	return 0;
}
