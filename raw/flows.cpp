// This amazing code is by Eric Sunli Chen.
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
template<typename T> bool get_int(T &x)
{
	char t=getchar();
	bool neg=false;
	x=0;
	for(; (t>'9'||t<'0')&&t!='-'&&t!=EOF; t=getchar());
	if(t=='-')neg=true,t=getchar();if(t==EOF)return false;
	for(; t<='9'&&t>='0'; t=getchar())x=x*10+t-'0';
	if(neg)x=-x;return true;
}
template<typename T> void print_int(T x)
{
	if(x<0)putchar('-'),x=-x;
	short a[20]= {},sz=0;
	while(x>0)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1; i>=0; i--)putchar('0'+a[i]);
}
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define get1(a) get_int(a)
#define get2(a,b) (get1(a)&&get1(b))
#define get3(a,b,c) (get1(a)&&get2(b,c))
#define printendl(a) print_int(a),puts("")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const LL Linf=1ll<<61;
const double pi=acos(-1.0);

const int maxn=1111;
const int maxm=100111;

struct max_flow
{
	struct edge{int to,cap;};
	int head[maxn],nxt[maxm<<1],iter[maxn],tot;
	edge e[maxm<<1];
	void clear()
	{
		memset(head,0,sizeof(head));
		tot=1;
	}
	max_flow(){clear();}
	void addedge(int u,int v,int cap)
	{
		nxt[++tot]=head[u];
		head[u]=tot;
		e[tot]=edge{v,cap};
		nxt[++tot]=head[v];
		head[v]=tot;
		e[tot]=edge{u,0};
	}
	
	int lvl[maxn],q[maxn];
	bool bfs(int s,int t)
	{
		memset(lvl,-1,sizeof(lvl));
		lvl[s]=0;int rr=0;q[rr++]=s;
		for(int fr=0;fr<rr;fr++)
		{
			int x=q[fr];if(x==t)return true;
			for(int i=head[x];i;i=nxt[i])if(e[i].cap&&lvl[e[i].to]==-1)
			{
				lvl[e[i].to]=lvl[x]+1;
				q[rr++]=e[i].to;
			}
		}
		return false;
	}
	int dfs(int x,int t,int f)
	{
		if(x==t||f==0)return f;
		int ret=0;
		for(int&i=iter[x];i;i=nxt[i])if(e[i].cap&&lvl[e[i].to]==lvl[x]+1)
		{
			int d=dfs(e[i].to,t,min(f,e[i].cap));
			e[i].cap-=d;e[i^1].cap+=d;
			f-=d;ret+=d;
			if(!f)break;
		}
		return ret;
	}
	int maxflow(int s,int t)
	{
		int flow=0;
		while(bfs(s,t))
		{
			memcpy(iter,head,sizeof(head));
			flow+=dfs(s,t,inf);
		}
		return flow;
	}
};
struct mincost_flow
{
	struct edge{int to,cap,cost;};
	int head[maxn],nxt[maxm<<1],iter[maxn],tot=1;
	edge e[maxm<<1];
	void addedge(int u,int v,int cap,int cost)
	{
		nxt[++tot]=head[u];
		head[u]=tot;
		e[tot]=edge{v,cap,cost};
		nxt[++tot]=head[v];
		head[v]=tot;
		e[tot]=edge{u,0,-cost};
	}
	bool inq[maxn];int q[maxn],dist[maxn],pre[maxn];
	void spfa(int s)
	{
		memset(dist,63,sizeof(dist));
		dist[s]=0;int fr=0,rr=0;q[rr++]=s;
		while(fr!=rr)
		{
			int x=q[fr++];if(fr==maxn)fr=0;
			inq[x]=0;
			for(int i=head[x];i;i=nxt[i])if(e[i].cap&&dist[e[i].to]>dist[x]+e[i].cost)
			{
				dist[e[i].to]=dist[x]+e[i].cost;
				pre[e[i].to]=i;
				if(!inq[e[i].to])
				{
					inq[e[i].to]=1;
					if(fr==rr||dist[q[fr]]<=dist[e[i].to])
					{
						q[rr++]=e[i].to;
						if(rr==maxn)rr=0;
					}
					else
					{
						if(fr==0)fr=maxn;
						q[--fr]=e[i].to;
					}
				}
			}
		}
	}
	int augment(int t,int s,int&f)
	{
		int d=f,cur;
		for(cur=t;cur!=s;cur=e[pre[cur]^1].to)d=min(d,e[pre[cur]].cap);
		f-=d;
		for(cur=t;cur!=s;cur=e[pre[cur]^1].to)
		{
			e[pre[cur]].cap-=d;
			e[pre[cur]^1].cap+=d;
		}
		return dist[t]*d;
	}
	int mincostflow(int s,int t,int f)
	{
		int ret=0;
		while(f)
		{
			spfa(s);
			if(dist[t]==inf)return -1;
			ret+=augment(t,s,f);
		}
		return ret;
	}
};

int main()
{
	return 0;
}
