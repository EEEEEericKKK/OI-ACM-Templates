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

const int hash_mod=233333;
const int hash_maxn=2333333;
struct hash_table
{
	int head[hash_mod],nxt[hash_maxn],a[hash_maxn],val[hash_maxn],tot;
	void clear(){memset(head,0,sizeof(head));tot=0;}
	hash_table(){clear();}
	int&operator[](const LL&x)
	{
		int tx=x%hash_mod;
		for(int i=head[tx];i;i=nxt[i])if(val[i]==x)return a[i];
		nxt[++tot]=head[tx];head[tx]=tot;val[tot]=x;a[tot]=0;
		return a[tot];
	}
	int find(const LL&x)
	{
		int tx=x%hash_mod;
		for(int i=head[tx];i;i=nxt[i])if(val[i]==x)return a[i];
		return 0;
	}
};

int main()
{
	return 0;
}
