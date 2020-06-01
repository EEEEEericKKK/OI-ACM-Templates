#include <bits/stdc++.h>

namespace BST
{

const int maxn = 1000111;
std::mt19937 rng;
int rnd(int l, int r) { return std::uniform_int_distribution<int>(l, r)(rng); }
struct treap_t { int ls, rs, val, sz; };
treap_t nd[maxn << 2];
int tot;
int copy(int t) { nd[++tot] = nd[t]; return tot; }
int merge(int u, int v)
{
	if(!u || !v) return u | v;
	if(rnd(1, nd[u].sz + nd[v].sz) <= nd[v].sz)
	{
		u = copy(u);
		nd[u].rs = merge(nd[u].rs, v);
		nd[u].sz = nd[nd[u].ls].sz + nd[nd[u].rs].sz + 1;
		return u;
	}
	else
	{
		v = copy(v);
		nd[v].ls = merge(u, nd[v].ls);
		nd[v].sz = nd[nd[v].ls].sz + nd[nd[v].rs].sz + 1;
		return v;
	}
}
void split(int o, int sz, int &k1, int &k2)
{
	if(!o)
	{
		k1 = k2 = 0;
		return;
	}
	o = copy(o);
	if(nd[nd[o].ls].sz >= sz)
	{
		k2 = o;
		split(nd[o].ls, sz, k1, nd[o].ls);
	}
	else
	{
		k1 = o;
		split(nd[o].rs, sz - nd[nd[o].ls].sz - 1, nd[o].rs, k2);
	}
	nd[o].sz = nd[nd[o].ls].sz + nd[nd[o].rs].sz + 1;
}

} // namespace BST

int main()
{
	return 0;
}