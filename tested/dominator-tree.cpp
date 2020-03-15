#include <bits/stdc++.h>

namespace Dominator
{
constexpr int maxn = 300111;
constexpr int maxm = 400111;
int G[maxn], rG[maxn], nxt[maxm<<1], to[maxm<<1], etot = 1;
void clear()
{
	memset(G, 0, sizeof(G));
	memset(rG, 0, sizeof(rG));
	etot = 1;
}
void addedge(int u, int v)
{
	nxt[++etot] = G[u];
	G[u] = etot;
	to[etot] = v;
	nxt[++etot] = rG[v];
	rG[v] = etot;
	to[etot] = u;
}
int dfn[maxn], tot, pa[maxn], seq[maxn], f[maxn], fmn[maxn], sdom[maxn], idom[maxn];
void dfs(int x, int f)
{
	dfn[x] = ++tot; seq[tot] = x; pa[x] = f;
	for(int i=G[x]; i; i=nxt[i]) if(!dfn[to[i]]) dfs(to[i], x);
}
void gf(int x)
{
	if(x == f[x]) return;
	gf(f[x]);
	if(dfn[sdom[fmn[f[x]]]] < dfn[sdom[fmn[x]]]) fmn[x] = fmn[f[x]];
	f[x] = f[f[x]];
}
std::vector<int> buc[maxn];
void work(int rt)
{
	for(int i=1; i<=tot; i++) dfn[seq[i]] = 0; tot = 0;
	dfs(rt, 0);
	for(int i=1; i<=tot; i++)
	{
		f[seq[i]] = fmn[seq[i]] = sdom[seq[i]] = seq[i];
		buc[seq[i]].clear();
	}
	for(int t=tot; t>1; t--)
	{
		int x = seq[t];
		for(int i=rG[x]; i; i=nxt[i]) if(dfn[to[i]])
		{
			gf(to[i]);
			if(dfn[sdom[fmn[to[i]]]] < dfn[sdom[x]]) sdom[x] = sdom[fmn[to[i]]];
		}
		f[x] = pa[x];
		buc[sdom[x]].push_back(x);
		
		x = seq[t-1];
		for(int i=0; i<buc[x].size(); i++)
		{
			gf(buc[x][i]);
			if(sdom[fmn[buc[x][i]]] == x) idom[buc[x][i]] = x;
			else idom[buc[x][i]] = fmn[buc[x][i]];
		}
	}
	idom[rt] = 0;
}
} // namespace Dominator

int main()
{
	return 0;
}