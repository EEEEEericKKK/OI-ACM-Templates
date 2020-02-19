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

#define ls a[o].ch[0]
#define rs a[o].ch[1]
struct node
{
	int ch[2],fa;
	bool rev;
	
	unsigned sum,vsum,v;
	void clear(){ch[0]=ch[1]=rev=v=sum=vsum=0;}
	
	node(){clear();}
}a[200111];

inline int gettp(const int&o){int&f=a[o].fa;return a[f].ch[0]==o?0:(a[f].ch[1]==o?1:-1);}
void reverse(const int&o){if(!o)return;swap(ls,rs);a[o].rev^=1;}
void pushdown(const int&o)
{
	if(a[o].rev)
	{
		reverse(ls);reverse(rs);
		a[o].rev=0;
	}
}
void pushup(int o){if(gettp(o)!=-1)pushup(a[o].fa);pushdown(o);}

void pull(int o){a[o].sum=a[ls].sum^a[rs].sum^a[o].vsum^a[o].v;}
void modify_pref(int o,int k)
{
	a[o].vsum^=a[rs].sum^a[k].sum;
	rs=k;pull(o);
}
void rotate(int o,int d)
{
	int k1=a[o].ch[d],k2=a[k1].ch[d^1];
	if(gettp(o)!=-1)a[a[o].fa].ch[gettp(o)]=k1;
	a[o].ch[d]=k2;a[k1].ch[d^1]=o;
	a[k1].fa=a[o].fa;a[o].fa=k1;a[k2].fa=o;
	pull(o);
}
void splay(int o)
{
	pushup(o);
	while(gettp(o)!=-1)
	{
		int f1=a[o].fa,f2=a[f1].fa,t1=gettp(o),t2=gettp(f1);
		if(t2==-1||f2==0)rotate(f1,t1);
		else if(t1==t2){rotate(f2,t2);rotate(f1,t1);}
		else{rotate(f1,t1);rotate(f2,t2);}
	}
	pull(o);
}
int access(int o)
{
	int k=0;
	while(o)
	{
		splay(o);
		modify_pref(o,k);
		k=o;o=a[o].fa;
	}
	return k;
}
void makeroot(int o){reverse(access(o));splay(o);}
void link(int u,int v)
{
	makeroot(u);makeroot(v);
	a[v].fa=u;a[u].vsum^=a[v].sum;
	pull(u);
}
void cut(int u,int v)
{
	makeroot(u);access(v);splay(u);
	a[v].fa=a[u].ch[1]=0;
	pull(u);
}
unsigned query(int u,int v)
{
	makeroot(u);access(v);
	return a[u].sum^a[v].sum;
}
void modify(int o,unsigned v)
{
	makeroot(o);
	a[o].v^=v;
	pull(o);
}

unsigned rnd()
{
	return rand()<<10|rand();
}
int n,q,tot,ex[300111],ey[300111];
unsigned all,w[300111];
int main()
{
	get3(n,n,q);
	for(int i=1,u,v;i<n;i++)
	{
		get2(u,v);
		link(u,v);
	}
	
	int op,x,y,xx,yy;
	while(q--)
	{
		get1(op);
		if(op==1)
		{
			get2(x,y);get2(xx,yy);
			cut(x,y);
			link(xx,yy);
		}
		else if(op==2)
		{
			get2(x,y);tot++;ex[tot]=x;ey[tot]=y;
			w[tot]=rnd();all^=w[tot];
			modify(x,w[tot]);modify(y,w[tot]);
		}
		else if(op==3)
		{
			get1(x);
			all^=w[x];modify(ex[x],w[x]);modify(ey[x],w[x]);
		}
		else
		{
			get2(x,y);
			puts(query(x,y)==all?"YES":"NO");
		}
	}
	return 0;
}
