#include <bits/stdc++.h>

#define V 100111
#define E 100111
typedef int val_t;
const val_t INF = 0x3f3f3f3f;

namespace MincostFlow
{

struct edge
{
	int to,cap;
	val_t cost;
	edge(){}
	edge(int k1, int k2, val_t k3)
	{
		to = k1;
		cap = k2;
		cost = k3;
	}
};

int head[V], nxt[E<<1], etot = 1, MX = 0;
edge e[E<<1];
void clear()
{
	std::memset(head, 0, sizeof(head));
	etot = 1;
	MX = 0;
}

void addedge(int u, int v, int cap, val_t cost)
{
	if(u > MX) MX = u;
	if(v > MX) MX = v;
	nxt[++etot] = head[u];
	head[u] = etot;
	e[etot] = edge(v, cap, cost);
	nxt[++etot] = head[v];
	head[v] = etot;
	e[etot] = edge(u, 0, -cost);
}

val_t dist[V];
int pre[V];
void spfa(int s)
{
	static bool inq[V];
	static int q[V];
	
	std::fill(dist, dist + MX + 1, INF);
	int fr = 0, rr = 0;
	dist[s] = 0;
	q[rr++] = s;
	
	while(fr != rr)
	{
		int x = q[fr++];
		if(fr == V) fr = 0;
		inq[x] = 0;
		for(int i=head[x]; i; i=nxt[i]) if(e[i].cap && dist[e[i].to] > dist[x] + e[i].cost)
		{
			dist[e[i].to] = dist[x] + e[i].cost;
			pre[e[i].to] = i;
			if(!inq[e[i].to])
			{
				inq[e[i].to] = 1;
				if(fr==rr || dist[q[fr]] <= dist[e[i].to])
				{
					q[rr++] = e[i].to;
					if(rr == V) rr = 0;
				}
				else
				{
					if(fr == 0) fr = V;
					q[--fr] = e[i].to;
				}
				
			}
		}
	}
}
val_t augment(int t, int s, int&f)
{
	int d = f, cur;
	for(cur=t; cur!=s; cur=e[pre[cur]^1].to) d = std::min(d, e[pre[cur]].cap);
	f -= d;
	for(cur=t; cur!=s; cur=e[pre[cur]^1].to)
	{
		e[pre[cur]].cap -= d;
		e[pre[cur]^1].cap += d;
	}
	return dist[t] * d;
}
val_t work(int s, int t, int f)
{
	val_t ret = 0;
	while(f)
	{
		spfa(s);
		if(dist[t] == INF) return -1;
		ret += augment(t, s, f);
	}
	return ret;
}

} // namespace MincostFlow
#undef V
#undef E

int main()
{
	return 0;
}