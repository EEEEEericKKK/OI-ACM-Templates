#include <bits/stdc++.h>

#define V 100111
#define E 100111
typedef int val_t;
constexpr val_t INF = 0x3f3f3f3f;

namespace MaxFlow
{

struct edge
{
	int to;
	val_t cap;
	edge(){}
	edge(int k1, val_t k2)
	{
		to=k1;
		cap=k2;
	}
};

int head[V], nxt[E<<1], it[E<<1], etot = 1, MX = 0;
edge e[E<<1];

void clear()
{
	std::memset(head, 0, sizeof(head));
	etot = 1;
	MX = 0;
}

void addedge(int u, int v, val_t cap)
{
	if(u > MX) MX = u;
	if(v > MX) MX = v;
	nxt[++etot] = head[u];
	head[u] = etot;
	e[etot] = edge(v, cap);
	nxt[++etot] = head[v];
	head[v] = etot;
	e[etot] = edge(u, 0);
}

int lvl[V];
bool bfs(int s,int t)
{
	static int q[V];
	
	std::memset(lvl, 0, sizeof(bool) * (MX+1));
	lvl[s] = 0;
	int rr = 0;
	q[rr++] = s;
	
	for(int fr=0; fr<rr; fr++)
	{
		int x = q[fr];
		if(x==t) return true;
		for(int i=head[x]; i; i=nxt[i]) if(e[i].cap && lvl[e[i].to] == -1)
		{
			lvl[e[i].to] = lvl[x]+1;
			q[rr++] = e[i].to;
		}
	}
}
val_t dfs(int x, int t, val_t f)
{
	if(x==t || f==0) return f;
	val_t ret = 0;
	for(int &i = it[x]; i; i=nxt[i]) if(e[i].cap && lvl[e[i].to] == lvl[x]+1)
	{
		val_t d = dfs(e[i].to, t, std::min(f, e[i].cap));
		e[i].cap -= d;
		e[i^1].cap += d;
		f -= d;
		ret += d;
		if(!f) break;
	}
	return ret;
}
val_t work(int s, int t)
{
	if(s > MX) MX = s;
	if(t > MX) MX = t;
	int flow = 0;
	while(bfs(s,t))
	{
		std::memcpy(it, head, sizeof(int) * (MX+1));
		flow += dfs(s, t, INF);
	}
	return flow;
}

} // namespace MaxFlow
#undef V
#undef E

int main()
{
	return 0;
}