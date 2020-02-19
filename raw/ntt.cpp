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

const int poly_bits=19;
const int poly_max=1<<poly_bits;//poly_max=2^poly_bits
const int mod=998244353;//a prime in the form of k*poly_max+1
const int root=3;//a primitive root of mod

//#define COMB
int power(int x,int y,const int&mod=::mod){int ret=1;do{if(y&1)ret=1ll*ret*x%mod;x=1ll*x*x%mod;}while(y>>=1);return ret;}
int up_pw2(const int&x){int ret=1;while(ret<x)ret<<=1;return ret;}
int inv[poly_max+1],fac[poly_max+1],invf[poly_max+1];

int w[poly_max+1];
template<typename tp>int simplify(tp*a,int n){while(n&&a[n-1]==tp(0))n--;return n;}
template<typename tp>void copy(tp*a,tp*b,int n,int m){for(int i=0;i<m;i++)b[i]=(i<n?a[i]:tp(0));}

#ifdef COMB
int comb(int x,int y){if(x<y||y<0)return 0;return 1ll*fac[x]*invf[y]%mod*invf[x-y]%mod;}
#endif

void prework()
{
	w[0]=1;w[1]=power(root,mod-1>>poly_bits);
	for(int i=2;i<=poly_max;i++)w[i]=1ll*w[i-1]*w[1]%mod;
#ifdef COMB
	fac[0]=inv[0]=invf[0]=1;
	for(int i=1;i<poly_max;i++)
	{
		fac[i]=1ll*i*fac[i-1]%mod;
		inv[i]=power(i,mod-2);
		invf[i]=1ll*inv[i]*invf[i-1]%mod;
	}
#endif
}
void dft(int*a,int n)
{
	for(int i=0,j=0;i<n;i++){if(i<j)swap(a[i],a[j]);for(int t=n>>1;(j^=t)<t;t>>=1);}
	for(int l=1,d=1;l<n;l<<=1,d++)
	{
		int l2=l<<1;
		for(int i=0;i<n;i+=l2)for(int j=0;j<l;j++)
		{
			int tmp=1ll*a[i|l|j]*w[j<<poly_bits-d]%mod;
			a[i|l|j]=a[i|j]-tmp+mod;if(a[i|l|j]>=mod)a[i|l|j]-=mod;
			a[i|j]+=tmp;if(a[i|j]>=mod)a[i|j]-=mod;
		}
	}
}
void idft(int*a,int n)
{
	for(int i=0,j=0;i<n;i++){if(i<j)swap(a[i],a[j]);for(int t=n>>1;(j^=t)<t;t>>=1);}
	for(int l=1,d=1;l<n;l<<=1,d++)
	{
		int l2=l<<1;
		for(int i=0;i<n;i+=l2)for(int j=0;j<l;j++)
		{
			int tmp=1ll*a[i|l|j]*w[poly_max-(j<<poly_bits-d)]%mod;
			a[i|l|j]=a[i|j]-tmp+mod;if(a[i|l|j]>=mod)a[i|l|j]-=mod;
			a[i|j]+=tmp;if(a[i|j]>=mod)a[i|j]-=mod;
		}
	}
	int inv=power(n,mod-2);for(int i=0;i<n;i++)a[i]=1ll*a[i]*inv%mod;
}

void poly_dotmul(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++)c[i]=(i<n&&i<m?1ll*a[i]*b[i]%mod:0);}

int ttA[poly_max],ttB[poly_max];
void poly_mult(int*a,int*b,int*c,int n,int m)
{
	int len=up_pw2(n+m-1);
	copy(a,ttA,n,len);
	copy(b,ttB,m,len);
	dft(ttA,len);dft(ttB,len);
	poly_dotmul(ttA,ttB,ttA,len,len);
	idft(ttA,len);
	copy(ttA,c,len,n+m-1);
}

static int tA[poly_max],tB[poly_max],tC[poly_max],tD[poly_max],tE[poly_max];
void poly_inv(int*a,int*b,int n,int m)
{
	assert(a[0]!=0);
	int tn=up_pw2(m);
	tB[0]=qpow(a[0],mod-2);
	for(int l=2;l<=tn;l<<=1)
	{
		int l2=l<<1;
		copy(a,tA,min(n,l),l2);
		copy(tB,tB,l>>1,l2);
		dft(tA,l2);dft(tB,l2);
		for(int i=0;i<l2;i++)tB[i]=(mod+2-(LL)tA[i]*tB[i]%mod)*tB[i]%mod;
		idft(tB,l2);
		copy(tB,tB,l,l2);
	}
	copy(tB,b,tn,m);
}


int main()
{
	prework();
	return 0;
}
