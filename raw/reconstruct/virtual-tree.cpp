#include <bits/stdc++.h>

namespace Tree
{
constexpr int maxn = 200111;
std::vector<int> g[maxn], l[maxn];
void addedge(int u, int v, int w=1)
{
	g[u].push_back(v); l[u].push_back(w);
	g[v].push_back(u); l[v].push_back(w);
}
int dist[maxn];
int dfn[maxn], edfn[maxn], dep[maxn], timer, fa[20][maxn], seq[maxn];
void dfs(int x, int f = 0)
{
	fa[0][x] = f;
	for(int i=1; i<20; i++) fa[i][x] = fa[i-1][fa[i-1][x]];
	dfn[x] = ++timer;
	seq[timer] = x;
	for(int i=0; i<(int)g[x].size(); i++) if(g[x][i] != f)
	{
		dep[g[x][i]] = dep[x] + 1;
		dist[g[x][i]] = dist[x] + l[x][i];
		dfs(g[x][i], x);
	}
	edfn[x] = timer;
}
void prework(int n)
{
	memset(dfn, 0, sizeof(int)*(n+10));
	timer = 0;
	for(int i=1; i<=n; i++) if(!dfn[i])
		dfs(i);
}
int getlca(int u, int v)
{
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i=19; i>=0; i--) if((dep[u]-dep[v])>>i) u = fa[i][u];
	if(u == v) return u;
	for(int i=19; i>=0; i--) if(fa[i][u] != fa[i][v]) u = fa[i][u], v=fa[i][v];
	return fa[0][u];
}
int getdist(int u, int v)
{
	if(dfn[u] > dfn[v]) std::swap(u, v);
	if(edfn[u] >= dfn[v]) return dist[v] - dist[u];
	else return dist[u] + dist[v] - 2*dist[getlca(u, v)];
}
std::vector<std::pair<std::pair<int,int>,int>> extract(std::vector<int> &vs)
{
	std::sort(vs.begin(), vs.end(), [](int x, int y){return dfn[x] < dfn[y];});
	vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
	for(int i=vs.size()-1; i>=1; i--)
	{
		int lca = getlca(vs[i], vs[i-1]);
		if(lca) vs.push_back(getlca(vs[i], vs[i-1]));
	}
	std::sort(vs.begin(), vs.end(), [](int x, int y){return dfn[x] < dfn[y];});
	vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
	
	static int stk[maxn], top;
	top = 0;
	std::vector<std::pair<std::pair<int,int>,int>> ret;
	for(auto x:vs)
	{
		while(top && edfn[stk[top]] < dfn[x]) top--;
		if(top) ret.emplace_back(std::make_pair(x, stk[top]), dist[x] - dist[stk[top]]);
		stk[++top] = x;
	}
	assert(vs.size() == ret.size() + 1);
	return ret;
}
} // namespace Tree

int main()
{
	return 0;
}