#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;

//路径类
class rot
{
  public:
	int sr;
	int de;
	int len;
	  rot (int s, int d, int l):sr (s), de (d), len (l)
	{
	};
};

//重载小于号 便于priority_queue按照路径长度排序
bool operator< (rot a, rot b)
{
	return a.len > b.len;
}

//节点类 用于并查集查是否连通
class node
{
  public:
	node * father;
	node ():father (NULL)
	{
	};
};

//并查集获取祖先
node *getori (node * a)
{
	if (a->father == NULL)
		return a;
	else
	{
		a->father = getori (a->father);	//顺带直接将a的父节点置为祖先
		return a->father;
	}
}

bool isconnect (node * a, node * b)	//判断两节点是否连通
{
	return getori (a) == getori (b);
}

void connect (node * a, node * b)	//连接 相当于并查集的并
{
	if (a->father == NULL)
		a->father = b;
	else
		a->father->father = b;	//一开始在这里WA了= =
	return;
}

int main ()
{
	int poisum = 0, roadsum = 0;
	char c_src, c_dest;
	int i_src = 0, i_dest = 0, consum = 0, length = 0;

	priority_queue < rot > pq;

	scanf ("%d", &poisum);
	node *poi = new node[poisum + 2];
	for (int i = 0; i < poisum - 1; ++i)
	{
		while(true)
		{
			c_src = getchar();
			if (c_src >= 'A' && c_src <= 'Z') break;
		}
		scanf ("%d", &consum);
		i_src = c_src - 'A';
		for (int j = 0; j < consum; ++j)
		{
			while(true)
			{
				c_dest = getchar();
				if (c_dest >= 'A' && c_dest <= 'Z') break;
			}
			scanf ("%d", &length);
			i_dest = c_dest - 'A';
			pq.push (rot (i_src, i_dest, length));
			++roadsum;
		}
	}

	int usedrot = 0, totallen = 0;

	while (usedrot < poisum - 1)	//由最小生成树 边数一定为点数减一
	{
		rot r_temp = pq.top ();	//优先队列top的一定为最短的路径

		if (!isconnect (&poi[r_temp.sr], &poi[r_temp.de]))	//判是否已经连通
		{
			totallen += r_temp.len;
			++usedrot;
			connect (&poi[r_temp.sr], &poi[r_temp.de]);
		}
		pq.pop ();
	}
	printf ("%d\n", totallen);
	delete poi;

	return 0;
}
