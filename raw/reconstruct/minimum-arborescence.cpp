#include <bits/stdc++.h>

const int maxn = 200111;
const int maxm = 400111;
typedef int val_t;
namespace MinArb
{
struct node
{
	int ls, rs, sz;
	val_t key, dlt;
	node() { ls = rs = sz = 0; key = dlt = val_t(0); }
	node(val_t key)
	{
		this -> key = key;
		dlt = val_t(0);
		sz = 1;
		ls = rs = 0;
	}
	void add(val_t v) { dlt += v; key += v; }
};

node a[maxn];
void push(int o)
{
	if(a[o].dlt)
	{
		if(a[o].ls) a[a[o].ls].add(a[o].dlt);
		if(a[o].rs) a[a[o].rs].add(a[o].dlt);
		a[o].dlt = val_t(0);
	}
}
int merge(int u, int v)
{
	if(!u || !v) return u | v;
	if(a[u].key > a[v].key) std::swap(u, v);
	push(u);
	a[u].rs = merge(a[u].rs, v);
	if(a[a[u].ls].sz < a[a[u].rs].sz) std::swap(a[u].ls, a[u].rs);
	a[u].sz = a[a[u].ls].sz + a[a[u].rs].sz + 1;
	return u;
}
int pop(int x)
{
	push(x);
	return merge(a[x].ls, a[x].rs);
}

struct edge
{
	int u, v;
	val_t w;
	edge() { u = v = 0; w = val_t(0); }
	edge(int k1, int k2, val_t k3) { u = k1; v = k2; w = k3; }
};
edge e[maxm];
int f[maxn], h[maxn];
int gf(int x) { return x == f[x] ? x : f[x] = gf(f[x]); }
long long ans;

int stk[maxn], top;
bool use[maxn], inst[maxn];

bool go(int x)
{
	stk[top = 1] = x;
	inst[x] = 1;
	while(true)
	{
		x = stk[top];
		while(h[x] && gf(e[h[x]].v) == x) h[x] = pop(h[x]);
		if(!h[x]) return false;
		
		int nxt = gf(e[h[x]].v);
		ans += a[h[x]].key;
		a[h[x]].add(-a[h[x]].key);
		if(use[nxt])
		{
			while(top) use[stk[top--]] = 1;
			break;
		}
		if(!inst[nxt])
		{
			stk[++top] = nxt;
			inst[nxt] = 1;
		}
		else
		{
			while(top && stk[top] != nxt)
			{
				f[gf(stk[top])] = gf(nxt);
				h[nxt] = merge(h[nxt], h[stk[top]]);
				use[stk[top]] = 1;
				top--;
			}
		}
	}
	return true;
}

int Minimum_Arborescence(int rt, int n, int m)
{
	ans = 0;
	for(int i=1; i<=n; i++)
	{
		f[i] = i;
		use[i] = h[i] = inst[i] = 0;
	}
	for(int i=1; i<=m; i++)
	{
		a[i] = node(e[i].w);
		h[e[i].u] = merge(h[e[i].u], i);
	}
	
	use[rt] = 1;
	for(int i=1; i<=n; i++) if(!use[i] && !go(i)) return -1;
	
	return ans;
}

} // namespace MinArb

int main()
{
	return 0;
}