#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
using namespace std;

#define maxn 305

int cur = 0;

class node
{
public:
	char name[maxn];
	int lchild;//the most left child
	int fa;//father
	int bro;//right brother
	node ():lchild(-1), fa (-1), bro (-1){};
};

int find_end (vector < node > vn_temp, int beg)//find the most right brother of beg
{
	while (vn_temp[beg].bro != -1)
	{
		beg = vn_temp[beg].bro;
	}
	return beg;
}


//insert a node, its father is i_fa, its string is ch_p
void insert_node (vector < node > &vn_temp, int i_fa, char *ch_p)
{
	node n_temp;

	n_temp.fa = i_fa;
	strcpy (n_temp.name, ch_p);
	vn_temp.push_back (n_temp);
	if (vn_temp[i_fa].lchild == -1)
	{
		vn_temp[i_fa].lchild = ++cur;
		return;
	}
	int lbro = find_end (vn_temp, vn_temp[i_fa].lchild);
	vn_temp[lbro].bro = ++cur;
	return;
}

void print_bro (vector < node > vn_temp, char *ch_p)//find ch_p, print its right brothers
{
	int vs = vn_temp.size (), i_temp = 0;
	bool isfind = 0;

	for (int i = 1; i < vs; ++i)//find ch_p
	{
		if (!strcmp(vn_temp[i].name, ch_p))
		{
			isfind = 1;
			i_temp = i;
			break;
		}
	}
	if (!isfind)//can't find ch_p
	{
		cout << "No" << endl;//never use cin/cout together with scanf/printf
		//printf ("No\n");
		return;
	}
	if (vn_temp[i_temp].bro == -1)//no right brothers
	{
		cout << " " << endl;
		//printf (" \n");
		return;
	}
	while (vn_temp[i_temp].bro != -1)
	{
		int i_bro = vn_temp[i_temp].bro;
		cout << vn_temp[i_bro].name;
		//printf ("%s", vn_temp[i_bro].name);
		i_temp = i_bro;
	}
	cout << endl;
	//printf ("\n");
	return;
}

int main ()
{
	int n = 0;
	char line[maxn];
	cin >> n;
	//scanf ("%d", &n);
	cin.get();
	++n;
	while (--n)
	{
		vector < node > n_ve;//record all nodes
		stack < int > i_stk;//record fathers

		cur = 0;//init
		node n_temp;

		n_ve.push_back (n_temp);//pushback root
		i_stk.push (0);

		while (true)
		{
			cin.getline (line, maxn);
			int len = strlen (line);

			if (!len)
				break;
			if (line[0] == '{')
				i_stk.push(cur);
			else if (line[0] == '}')
				i_stk.pop();
			else
			{
				insert_node(n_ve, i_stk.top(), line);
			}
		}


		cin.getline (line, maxn);
		print_bro(n_ve, line);
		cin.get ();
		cin.get ();
	}
}
