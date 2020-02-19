// This amazing code is by Eric Sunli Chen.
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

const int maxn=100111;
const int maxp=100111;

//(almost)online two dimensional counting with BIT
//call addp() to add points and prework() before queries
struct twod_query_v1
{
	int head[maxn],nxt[maxp*20],tot;
	LL bit[maxp*20];
	int v[maxp*20],sz[maxn];
	void clear()
	{
		memset(head,0,sizeof(head));
		tot=0;
	}
	twod_query_v1(){clear();}
	void addp(int x,int p)
	{
		for(;x<maxn;x+=x&-x)
		{
			nxt[++tot]=head[x];head[x]=tot;
			bit[tot]=p;sz[x]++;
		}
	}
	void prework()
	{
		tot=0;
		for(int i=0;i<maxn;i++)
		{
			for(int j=head[i];j;j=nxt[j])
				v[++tot]=bit[j];
			head[i]=tot-sz[i]+1;
			sort(v+head[i],v+head[i]+sz[i]);
		}
		for(int i=1;i<=tot;i++)bit[i]=0;
	}
	void add(int x,int p,int vv)
	{
		for(;x<maxn;x+=x&-x)
		{
			int pos=lower_bound(v+head[x],v+head[x]+sz[x],p)-v-head[x]+1;
			for(;pos<=sz[x];pos+=pos&-pos)
				bit[pos+head[x]-1]+=vv;
		}
	}
	LL query(int x,int p)
	{
		LL ret=0;
		for(;x;x-=x&-x)
		{
			int pos=upper_bound(v+head[x],v+head[x]+sz[x],p)-v-head[x];
			for(;pos;pos-=pos&-pos)
				ret+=bit[pos+head[x]-1];
		}
		return ret;
	}
};
//offline two dimensional counting with divide-and-conquer+BIT
namespace BIT
{
	int bit[200111],timer,mark[200111];
	void add(int x,int v){for(;x<200111;x+=x&-x){if(mark[x]!=timer){mark[x]=timer;bit[x]=0;}bit[x]+=v;}}
	int query(int x){int ret=0;for(;x;x-=x&-x)if(mark[x]==timer)ret+=bit[x];return ret;}
};
struct twod_query_v2
{
	struct query//tp=0: (l,r)+=tx   tp<0: ans[-tp]-=[0,tx][l,r]  tp>0:ans[tp]+=[0,tx][l,r]
	{
		int tp,l,r,tx;
		bool operator <(const query&b)
		{
			int ida,idb;
			if(tp)ida=tx;else ida=l;
			if(b.tp)idb=b.tx;else idb=b.l;
			if(ida!=idb)return ida<idb;
			return (!tp&&b.tp);
		}
	};
	query q[1000111],tq[1000111];
	int tot,ans[200111];
	twod_query_v2(){tot=0;memset(ans,0,sizeof(ans));}
	void addpoint(int x,int y,int v){q[++tot]=query{0,x,y,v};}
	void addquery(int x,int y,int xx,int yy,int id){q[++tot]=query{-id,y,yy,x-1};q[++tot]=query{id,y,yy,xx};}
	
	void solve(int l,int r)
	{
		while(l<=r&&q[l].tp!=0)l++;
		while(l<=r&&q[r].tp==0)r--;
		if(l>r)return;
		int mid=(l+r)>>1;solve(l,mid);solve(mid+1,r);
		int ctot=0;
		for(int i=l;i<=mid;i++)if(!q[i].tp)tq[++ctot]=q[i];
		for(int i=mid+1;i<=r;i++)if(q[i].tp)tq[++ctot]=q[i];
		sort(tq+1,tq+ctot+1);
		BIT::timer++;
		for(int i=1;i<=ctot;i++)
		{
			if(tq[i].tp)
			{
				int v=BIT::query(tq[i].r)-BIT::query(tq[i].l-1);
				if(tq[i].tp<0)ans[-tq[i].tp]-=v;
				else ans[tq[i].tp]+=v;
			}
			else BIT::add(tq[i].r,tq[i].tx);
		}
	}
	void go()
	{
		memset(ans,0,sizeof(ans));
		solve(1,tot);
	}
};

int main()
{
	return 0;
}
