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

const int maxn=100111;
const int sigma=26;
const int lg=20;

struct SAM
{
	struct node
	{
		int ch[sigma],fa,val;
		node(int v=0)
		{
			memset(ch,0,sizeof(ch));
			fa=0;val=v;
		}
	};
	int p,tot,root;
	SAM_node a[maxn<<1];
	int newnode(int v){a[++tot]=node(v);return tot;}
	void clear(){tot=0;p=root=newnode(0);}
	SAM(){clear();}
	
	void append(int x)
	{
		while(p&&!a[p].ch[x])
		{
			a[p].ch[x]=np;
			p=a[p].fa;
		}
		if(!p)a[np].fa=root;
		else
		{
			int q=a[p].ch[x];
			if(a[p].val+1==a[q].val)
				a[np].fa=q;
			else
			{
				int nq=newnode(a[p].val+1);
				memcpy(a[nq].ch,a[q].ch,sizeof(a[q].ch));
				a[nq].fa=a[q].fa;
				a[q].fa=nq;
				a[np].fa=nq;
				while(p&&a[p].ch[x]==q)
				{
					a[p].ch[x]=nq;
					p=a[p].fa;
				}
			}
		}
		p=np;
	}
};

namespace suffix_array
{
	int sa[maxn],rk[maxn],nrk[maxn],c[maxn];
	void construct_sa(char*s,int n)
	{
		this->n=n;
		int m=256;
		int*x=rk,*y=nrk;
		for(int i=0;i<m;i++)c[i]=0;
		for(int i=1;i<=n;i++)c[x[i]=s[i]]++;
		for(int i=1;i<m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa[--c[x[i]]]=i;
		
		for(int k=1;k<=n;k<<=1)
		{
			int p=0;
			for(int i=n-k+1;i<=n;i++)y[++p]=i;
			for(int i=1;i<=n;i++)if(sa[i]>k)y[p++]=sa[i]-k;
			for(int i=0;i<m;i++)c[i]=0;
			for(int i=1;i<=n;i++)c[x[y[i]]]++;
			for(int i=1;i<m;i++)c[i]+=c[i-1];
			for(int i=n;i>=1;i--)sa[--c[x[y[i]]]]=y[i];
			swap(x,y);
			x[sa[1]]=1;p=1;
			for(int i=2;i<=n;i++)x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?p:++p);
			if(p>=n)break;
			m=p;
		}
	}
	
	void construct_lcp(char*s)
	{
		int k=0;
		for(int i=0;i<n;i++)rk[sa[i]]=i;
		for(int i=0;i<n-1;i++)
		{
			if(k)k--;
			int j=sa[rk[i]-1];
			while(s[i+k]==s[j+k])k++;
			v[0][rk[i]]=k;
		}
		for(int i=2;i<n;i++)lg[i]=lg[i>>1]+1;
		for(int i=1;i<20;i++)
		{
			for(int j=2;j<n;j++)
			{
				int nxt=j+(1<<i-1);
				if(nxt>=n)v[i][j]=v[i-1][j];
				else v[i][j]=min(v[i-1][j],v[i-1][nxt]);
			}
		}
	}
	int qlcp(int l,int r)
	{
		if(l>r)swap(l,r);l++;
		int t=lg[r-l+1];
		return min(v[t][l],v[t][r-(1<<t)+1]);
	}
};

int main()
{
	return 0;
}
