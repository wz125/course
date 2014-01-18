/*=============================================================================
#     FileName: catch.cpp
#         Desc: poj 1703
#       Author: zhuting
#        Email: cnjs.zhuting@gmail.com
#     HomePage: my.oschina.net/locusxt
#      Version: 0.0.1
#    CreatTime: 2013-12-04 19:28:15
#   LastChange: 2013-12-04 19:32:44
#      History:
=============================================================================*/
#include <cstdio>
#include <cstdlib>
#define maxn 100005


class node/*节点类*/
{
	public:
	int fa;/*父节点下标*/
	int re;/*与父节点的关系*/
};

node n[maxn];

int getfa(int x)/*获取父节点下标,顺带更新父节点和与父节点的关系*/
{
	if (n[x].fa == x) 
		return x;
	int tmp = n[x].fa;
	n[x].fa = getfa(tmp);
	if(n[x].re == 1)
		n[x].re = n[tmp].re;
	else 
		n[x].re = !n[tmp].re;
	return n[x].fa;
}

void ask(int x, int y, int num)/*询问x,y的关系*/
{
	if (num == 2 && x != y)/*只有两个案件且不一样,一定different*/
	{
		printf("In different gangs.\n");
		return;
	}
	if (getfa(x) == getfa(y))/*父节点相同时,比较与父节点的关系是否一样*/
	{
		if (n[x].re == n[y].re)
		{
			printf("In the same gang.\n");
			return;
		}
		else 
		{
			printf("In different gangs.\n");
			return;
		}
	}
	printf("Not sure yet.\n");/*否则不确定*/
	return;
}

void diff(int x, int y)/*连接x,y点,且两者关系不同*/
{
	int xf = getfa(x);
	int yf = getfa(y);

	if (xf == yf) return;/*父节点一样,不需要连接,否则会出问题*/
	n[xf].fa = yf;
	if ((n[xf].re == n[x].re) == (n[yf].re == n[y].re))/*更新关系*/
	{
		n[xf].re = 0;
	}
	else
		n[xf].re = 1;
	return;
}

int main()
{
	int t = 0;
	int m = 0, num = 0;
	
	char msg;
	int a = 0, b = 0;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i)
	{

		scanf ("%d%d", &num, &m);
		for (int j = 1; j <= num; ++j)/*init,特别注意范围是1-N,不是0-N-1*/
		{
			n[j].fa = j;
			n[j].re = 1;
		}
		
		for (int j = 0; j < m; ++j)
		{
			scanf ("\n%[AD]%d%d", &msg, &a, &b);
			if (msg == 'A')
				ask(a, b, num);
			else if (msg == 'D')
				diff(a, b);
		}
	}
	return 0;
}
