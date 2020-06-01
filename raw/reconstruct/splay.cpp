#include <bits/stdc++.h>

namespace Splay
{

const int maxn = 100111;
struct node
{
	int ch[2], fa, sz, val;
	void clear() { ch[0] = ch[1] = fa = sz = 0; }
	node() { clear(); }
	node(int v) { ch[0] = ch[1] = fa = 0; sz = 1; val = v; }
};

node a[maxn];
#define ls a[o].ch[0]
#define rs a[o].ch[1]

int tot = 0;
int newnode(int v) { tot++; a[tot] = node(v); return tot; }
inline int gettp(int o)
{
	const int &f = a[o].fa;
	if(a[f].ch[0] == o) return 0;
	else if(a[f].ch[1] == o) return 1;
	else return -1;
}
void pushdown(int o) {}
void pushup(int o) { if(gettp(o) != -1) pushup(a[o].fa); pushdown(o); }
void pull(int o) { a[o].sz = a[ls].sz + a[rs].sz + 1; }
void rotate(int o, int d)
{
	int k1 = a[o].ch[d], k2 = a[k1].ch[d ^ 1];
	if(gettp(o) != -1) a[a[o].fa].ch[gettp(o)] = k1;
	a[o].ch[d] = k2;
	a[k1].ch[d ^ 1] = o;
	a[k1].fa = a[o].fa; a[o].fa = k1; a[k2].fa = o;
	pull(o); pull(k1);
}
void splay(int o)
{
	pushup(o);
	while(gettp(o) != -1)
	{
		int f1 = a[o].fa, f2 = a[f1].fa, t1 = gettp(o), t2 = gettp(f1);
		if(t2 == -1) rotate(f1, t1);
		else if(t1 == t2) { rotate(f2, t2); rotate(f1, t1); }
		else { rotate(f1, t1); rotate(f2, t2); }
	}
	pull(o);
}
int leftmost(int o)
{
	pushdown(o);
	while(ls)
	{
		o = ls;
		pushdown(o);
	}
	splay(o);
	return o;
}
int rightmost(int o)
{
	pushdown(o);
	while(rs)
	{
		o = rs;
		pushdown(o);
	}
	splay(o);
	return o;
}
int succ(int o)
{
	splay(o);
	if(rs) return leftmost(rs);
	else return 0;
}
int pred(int o)
{
	splay(o);
	if(ls) return rightmost(ls);
	else return 0;
}

} // namespace Splay


int main()
{
	return 0;
}
