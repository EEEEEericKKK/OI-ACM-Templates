#include <bits/stdc++.h>

namespace SCC
{
constexpr int maxn = 100111;
constexpr int maxm = 300111;
int G[maxn], nxt[maxm], to[maxm], etot = 1;
void addedge(int u, int v)
{
	nxt[++etot] = G[u];
	G[u] = etot;
	to[etot] = v;
}
void clear()
{
	memset(G, 0, sizeof(G));
	etot = 1;
}
int dfn[maxn], low[maxn], timer, stk[maxn], top, scc[maxn], scnt;
void dfs(int x)
{
	dfn[x] = low[x] = ++timer;
	stk[++top] = x;
	for(int i=G[x]; i; i=nxt[i])
	{
		if(!dfn[to[i]])
		{
			dfs(to[i]);
			low[x] = std::min(low[x], low[to[i]]);
		}
		else if(!scc[to[i]]) low[x] = std::min(low[x], dfn[to[i]]);
	}
	if(low[x] == dfn[x])
	{
		scc[x] = ++scnt;
		while(stk[top] != x)
		{
			scc[stk[top]] = scnt;
			top--;
		}
		top--;
	}
}
void work(int n)
{
	std::memset(dfn, 0, sizeof(int) * (n+1));
	std::memset(scc, 0, sizeof(int) * (n+1));
	timer = scnt = top = 0;
	for(int i=1; i<=n; i++) if(!dfn[i]) dfs(i);
}
} // namespace SCC

int main()
{
	return 0;
}