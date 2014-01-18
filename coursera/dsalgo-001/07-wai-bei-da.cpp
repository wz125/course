/*
在点的字符串与数字对应方面,做得不好
*/

#include <cstdio>
#include <cstdlib>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
#define maxn 37655

class poi//其实直接开一个数组就行了
{
public:
	char addr[105];
};

poi po[35];
//len[i][j]记录i,j两点间最短路长
//rout[i][j]表示i,j两点间最短路的一个中间点,便于输出路径
int len[35][35] = {0}, rout[35][35] = {0};
int p = 0, q = 0, r = 0;

//用长为length的路径连接a,b
//需考虑重复边
void join(int a, int b, int length)
{
	if (len[a][b] < length)//无需使用新路
	{
		return;
	}
	len[a][b] = length;
	len[b][a] = length;
	return;
}

void prout(int a, int b)//输出ab两点间的路径(递归)
{
	int i_temp = rout[a][b];
	if (i_temp == -1) printf("->(%d)->%s", len[a][b], po[b].addr);
	else
	{
		prout(a, i_temp);
		prout(i_temp, b);
	}
	return;
}

int main()
{
	//init
	for (int i = 0 ; i < 35; ++i)
		for (int j = 0 ; j < 35; ++j)
		{
			rout[i][j] = -1;
			if (i == j)
			{
				len[i][i] = 0;
				continue;
			}
			len[i][j] = maxn;
		}
	
	//输入点
	char ch_temp[105];
	scanf("%d", &p);
	for (int i = 0; i < p; ++i)
	{
		scanf ("%s", ch_temp);
		strcpy(po[i].addr, ch_temp);
	}
	
	//输入路径
	scanf ("%d", &q);
	char cha[105], chb[105];
	int leng = 0, ia = 0, ib = 0;
	for (int i = 0 ; i < q; ++i)
	{
		scanf ("%s%s%d", cha, chb, &leng);
		for (int j = 0 ; j  < p; ++j)
		{
			if (!strcmp(po[j].addr, cha))
			{
				ia = j;
				break;
			}
		}
		for (int j = 0 ; j  < p; ++j)
		{
			if (!strcmp(po[j].addr, chb)) 
			{
				ib = j;
				break;
			}
		}
		join(ia, ib, leng);//连接
	}
	/*test
	for (int i = 0 ; i < p; ++i)
	{
		for (int j = 0; j < p; ++j)
		printf ("%d ", len[i][j]);
		printf ("\n");
	}
	*/
	//floyd
	for (int k = 0; k < p; ++k)
	for (int i = 0; i < p; ++i)
		for (int j = 0; j < p; ++j)
			{
				if (i == j) continue;
				int i_temp = len[i][k] + len[k][j];
				if (len[i][j] > i_temp)
				{
					len[i][j] = i_temp;
					len[j][i] = i_temp;
					rout[i][j] = k;
					rout[j][i] = k;
				}
			}

	//ask and ans
	scanf("%d", &r);
	for (int i = 0; i < r; ++i)
	{
		scanf ("%s%s", cha, chb);
		for (int j = 0 ; j  < p; ++j)
		{
			if (!strcmp(po[j].addr, cha))
			{
				ia = j;
				break;
			}
		}
		for (int j = 0 ; j  < p; ++j)
		{
			if (!strcmp(po[j].addr, chb)) 
			{
				ib = j;
				break;
			}
		}
		printf("%s", po[ia].addr);
		prout(ia, ib);
		printf("\n");
	}
	return 0;
}
