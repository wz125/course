/*=============================================================================
#     FileName: phone_number.cpp
#         Desc: poj_1002
#       Author: zhuting
#        Email: cnjs.zhuting@gmail.com
#     HomePage: my.oschina.net/u/1053833
#      Version: 0.0.1
#    CreatTime: 2013-11-25
#   LastChange: 2013-11-25 23:30:45
#      History:
=============================================================================*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#define maxn 100005/*最大字符串个数*/
#define str_maxn 205/*最大字符串长*/
using namespace std;


int main()
{
	/*
	 * num为字母数字映射数组
	 * n为字符串个数
	 * phone为每个号码的整数表示
	 * str_tmp为临时字符串
	 */
	int num[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};
	int n = 0;
	int phone[maxn] = {0};
	char str_tmp[str_maxn];

	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", str_tmp);
		int len = strlen(str_tmp);
		int cur = 7;/*cur为当前读入整形的第几位*/
		for (int j = 0; j < len; ++j)
		{
			if (str_tmp[j] >= '0' && str_tmp[j] <= '9')
			{
				phone[i] += (str_tmp[j] - '0') * ((int)pow(10.0, --cur));/*字符串转整形*/
				if (cur == 0) break;
			}

			else if (str_tmp[j] >= 'A' && str_tmp[j] <= 'Z')
			{
				phone[i] += num[str_tmp[j] - 'A'] * ((int)pow(10.0, --cur));
				if (cur == 0) break;
			}
		}
	}

	sort(phone, phone + n);/*排序*/

	/*for test*/
	/*for (int i = 0; i < n; ++i)
		printf ("%d\n", phone[i]);*/

	/*
	 * is_exist记录是否存在,存在则为1
	 * cur_num当前值
	 * times当前值出现的次数
	 */
	bool is_exist = 0;
	int cur_num = phone[0];
	int times = 1;
	for (int i = 1; i < n; ++i)
	{
		if (phone[i] == cur_num)
		{
			++times;
		}
		else
		{
			if (times >= 2)
			{
				is_exist = 1;
				int front = cur_num / 10000;/*前3位*/
				int back = cur_num % 10000;/*后4位*/
				printf ("%03d-%04d %d\n", front, back, times);
			}
			times = 1;
			cur_num = phone[i];
		}
	}
	if (times >= 2)/*收尾检查!!!*/
	{
		is_exist = 1;
		int front = cur_num / 10000;
		int back = cur_num % 10000;
		printf ("%03d-%04d %d\n", front, back, times);
	}
	if (!is_exist) printf("No duplicates.\n");
	return 0;

}
