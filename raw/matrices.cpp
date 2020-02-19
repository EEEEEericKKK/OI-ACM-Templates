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
#define get3(a,b,c) (get1(a)&&get2(b,c))
#define printendl(a) print_int(a),puts("")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const LL Linf=1ll<<61;
const double pi=acos(-1.0);

const int sz=10;
const int mod=1e9+7;

struct matrix
{
	int a[sz][sz];
	void reset(){memset(a,0,sizeof(a));}
	void reset(int x){memset(a,0,sizeof(a));for(int i=0;i<sz;i++)a[i][i]=x;}
	matrix(){reset();}
	matrix(int x){reset(x);}
};

matrix operator *(const matrix&a,const matrix&b)
{
	matrix ret;
	for(int i=0;i<sz;i++)for(int k=0;k<sz;k++)if(a.a[i][k])
		for(int j=0;j<sz;j++)ret.a[i][j]=(ret.a[i][j]+(LL)a.a[i][k]*b.a[k][j])%mod;
	return ret;
}

matrix qpow(matrix x,int y)
{
	matrix ret(1);
	while(y)
	{
		if(y&1)ret=ret*x;
		x=x*x;
		y>>=1;
	}
	return ret;
}

int main()
{
	return 0;
}
