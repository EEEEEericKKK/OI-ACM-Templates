// This amazing code is by Eric Sunli Chen.
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;

struct Splay_tree
{
	struct node
	{
		int ch[2],fa,sz,v;
		bool rev;
		void clear(){ch[0]=ch[1]=fa=sz=v=0;}
		node(){clear();}
		node(int v){clear();sz=1;this->v=v;}
	}a[200111];
#define ls a[o].ch[0]
#define rs a[o].ch[1]
	int tot=0;
	int newnode(int v){tot++;a[tot]=node(v);return tot;}
	inline int gettp(int o){int&f=a[o].fa;return a[f].ch[0]==o?0:(a[f].ch[1]==o?1:-1);}
	void pushdown(int o)
	{
		if(a[o].rev)
		{
			a[ls].rev^=1;a[rs].rev^=1;swap(ls,rs);
			a[o].rev=0;
		}
	}
	void pushup(int o){if(a[o].fa)pushup(a[o].fa);pushdown(o);}
	void maintain(int o){a[o].sz=a[ls].sz+a[rs].sz+(a[o].v>0);}
	void rotate(int o,int d)
	{
		int k1=a[o].ch[d],k2=a[k1].ch[d^1];
		if(gettp(o)!=-1)a[a[o].fa].ch[gettp(o)]=k1;
		a[o].ch[d]=k2;a[k1].ch[d^1]=o;
		a[k1].fa=a[o].fa;a[o].fa=k1;a[k2].fa=o;
		maintain(o);maintain(k1);
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
		maintain(o);
	}
	int findrank(int o,int k)
	{
		pushdown(o);
		if(a[ls].sz>=k)return findrank(ls,k);
		if(a[ls].sz+(a[o].v>0)<k)return findrank(rs,k-a[ls].sz-(a[o].v>0));
		splay(o);return o;
	}
	int findright(int o)
	{
		pushdown(o);
		while(rs){o=rs;pushdown(o);}
		splay(o);
		return o;
	}
	void split(int &o,int&r,int sz)
	{
		o=findrank(o,sz);
		r=rs;a[r].fa=0;rs=0;
		maintain(o);
	}
	void merge(int&o,int r)
	{
		o=findright(o);
		rs=r;a[r].fa=o;maintain(o);
	}
	void print(int o)
	{
		if(o==0)return;
		pushdown(o);
		print(ls);
		if(o!=1)printf("%d ",a[o].v);
		print(rs);
	}
	void reverse(int o){a[o].rev^=1;}
}splay;

int main()
{
	return 0;
}
