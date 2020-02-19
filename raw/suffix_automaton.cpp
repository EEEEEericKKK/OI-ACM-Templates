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

struct node
{
	int ch[26],fa,val;
	node(int v=0)
	{
		memset(ch,0,sizeof(ch));
		fa=0;val=v;
	}
};
node a[200111];int tot,root,last;
int newnode(int v){a[++tot]=node(v);return tot;}
void append(int x)
{
	int p=last,np=newnode(a[p].val+1);
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
	last=np;
}

char s[200111];
int main()
{
	scanf("%s",s+1);
	
	root=last=newnode(0);
	for(int i=1;s[i];i++)append(s[i]-'a');
	for(int i=1;i<=tot;i++)for(int j=0;j<26;j++)if(a[i].ch[j])
		printf("%d %d %c\n",i,a[i].ch[j],j+'a');
	return 0;
}