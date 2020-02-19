// This amazing code is by Eric Sunli Chen.
#include<bits/stdc++.h>
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
#define get3(a,b,cur) (get1(a)&&get2(b,cur))
#define printendl(a) print_int(a),puts("")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const LL Linf=1ll<<61;
const double pi=acos(-1.0);

const int maxn=500111;

struct palindromic_tree
{
	int tot,ch[maxn][26],len[maxn],fail[maxn],sv[maxn],pos[maxn],now,clen;
	int diff[maxn],slink[maxn];
	
	void prework()
	{
		tot=1;fail[1]=0;len[0]=-1;len[1]=0;diff[0]=diff[1]=-inf;
		sv[0]=-inf;now=1;clen=0;
	}
	palindromic_tree(){prework();}
	
	void append(int c)
	{
		sv[++clen]=c;
		int cur=now;
		while(sv[clen-len[cur]-1]!=c)cur=fail[cur];
		if(!ch[cur][c])
		{
			ch[cur][c]=now=++tot;len[now]=len[cur]+2;
			if(len[cur]==-1)fail[now]=1;
			else
			{
				cur=fail[cur];
				while(sv[clen-len[cur]-1]!=c)cur=fail[cur];
				fail[now]=ch[cur][c];
			}
			diff[now]=len[now]-len[fail[now]];
			if(diff[now]==diff[fail[now]])slink[now]=slink[fail[now]];
			else slink[now]=fail[now];
		}
		else now=ch[cur][c];
		pos[clen]=now;
	}
};

int main()
{
	return 0;
}
