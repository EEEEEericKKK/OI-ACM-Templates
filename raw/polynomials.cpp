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

const double eps=1e-8;
const int poly_bits=19;
const int poly_max=1<<poly_bits;//poly_max=2^poly_bits
const int mod=998244353;//a prime in the form of k*poly_max+1 if NTT
const int root=3;//a primitive root of mod
#define COMB
int qpow(int x,int y,const int&mod=::mod){int ret=1;do{if(y&1)ret=(LL)ret*x%mod;x=(LL)x*x%mod;}while(y>>=1);return ret;}
inline int up_pw2(const int&x){int ret=1;while(ret<x)ret<<=1;return ret;}
int inv[poly_max+1],fac[poly_max+1],invf[poly_max+1],w[poly_max+1];

#ifdef COMB
	int comb(int x,int y){if(x<y||y<0)return 0;return (LL)fac[x]*invf[y]%mod*invf[x-y]%mod;}
#endif

int simplify(int*a,int n){while(n&&a[n-1]==0)n--;return n;}
inline void copy(int*a,int*b,int n,int m)
{
	if(n>=m)memcpy(b,a,sizeof(int)*m);
	else
	{
		memcpy(b,a,sizeof(int)*n);
		memset(b+n,0,sizeof(int)*(m-n));
	}
}

void prework()
{
	w[0]=1;w[1]=qpow(root,mod-1>>poly_bits);
	for(int i=2;i<=poly_max;i++)w[i]=(LL)w[i-1]*w[1]%mod;
#ifdef COMB
	fac[0]=inv[0]=invf[0]=1;
	for(int i=1;i<=poly_max;i++)
	{
		fac[i]=(LL)i*fac[i-1]%mod;
		inv[i]=qpow(i,mod-2);
		invf[i]=(LL)inv[i]*invf[i-1]%mod;
	}
#endif
}
void poly_dotmul(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++)c[i]=(i<n&&i<m?(LL)a[i]*b[i]%mod:0);}
void poly_add(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++){c[i]=(i<n?a[i]:0)+(i<m?b[i]:0);if(c[i]>=mod)c[i]-=mod;}}
void poly_sub(int*a,int*b,int*c,int n,int m){for(int i=0;i<n||i<m;i++){c[i]=(i<n?a[i]:0)-(i<m?b[i]:0);if(c[i]<0)c[i]+=mod;}}

inline void dft(int*a,int n,bool rev=0)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(i<j)swap(a[i],a[j]);
		for(int t=n>>1;(j^=t)<t;t>>=1);
	}
	static int cw[poly_max];static uLL ca[poly_max];uLL md2=(LL)mod*mod;
	for(int i=0;i<n;i++)ca[i]=a[i];
	for(int l=1,d=poly_bits-1;l<n;l<<=1,d--)
	{
		int l2=l<<1;
		for(int j=0;j<l;j++)cw[j]=w[rev?poly_max-(j<<d):(j<<d)];
		for(int i=0;i<n;i+=l2)for(int j=0;j<l;j++)
		{
			uLL tmp=LL(ca[i|l|j]%mod)*cw[j];
			ca[i|l|j]=ca[i|j]-tmp+md2;
			ca[i|j]+=tmp;
		}
		if(l==(1<<16))for(int i=0;i<n;i++)ca[i]%=mod;
	}
	for(int i=0;i<n;i++)a[i]=ca[i]%mod;
	if(rev)
	{
		LL inv=qpow(n,mod-2);
		for(int i=0;i<n;i++)a[i]=a[i]*inv%mod;
	}
}

inline void poly_mult(int*a,int*b,int*c,int n,int m,int k=-1)
{
	static int tA[poly_max],tB[poly_max];
	if(k==-1)k=n+m-1;if(n>k)n=k;if(m>k)m=k;
	if(n<=50&&m<=50)
	{
		for(int i=0;i<k;i++)tA[i]=0;
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)tA[i+j]=(tA[i+j]+(LL)a[i]*b[j])%mod;
		for(int i=0;i<k;i++)c[i]=tA[i];
		return;
	}
	int len=up_pw2(n+m-1);
	for(int i=0;i<len;i++)
	{
		tA[i]=i<n?a[i]:0;
		tB[i]=i<m?b[i]:0;
	}
	dft(tA,len);dft(tB,len);
	poly_dotmul(tA,tB,tA,len,len);
	dft(tA,len,1);
	for(int i=0;i<k;i++)c[i]=tA[i];
}

void poly_inv(int*a,int*b,int n,int m)
{
	static int tA[poly_max],tB[poly_max];
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
		dft(tB,l2,1);
		copy(tB,tB,l,l2);
	}
	copy(tB,b,tn,m);
}

void poly_rdiv(int*a,int*invb,int*c,int n,int m)
{
	static int tA[poly_max],tB[poly_max];
	assert(n>=m);
	int l=up_pw2(n+n-m-m+1);
	for(int i=0;i<l;i++)
	{
		tA[i]=(i<=n-m?a[n-i-1]:0);
		tB[i]=(i<=n-m?invb[i]:0);
	}
	dft(tA,l);dft(tB,l);
	poly_dotmul(tA,tB,tA,l,l);
	dft(tA,l,1);
	for(int i=0;i<=n-m;i++)c[i]=tA[n-m-i];
}
void poly_div(int*a,int*b,int*c,int n,int m)
{
	static int tC[poly_max];
	for(int i=0;i<m;i++)tC[i]=b[m-i-1];
	poly_inv(tC,tC,m,n-m+1);
	poly_rdiv(a,tC,c,n,m);
}
int poly_kdiv(int*a,int*b,int*c,int n,int m)
{
	n=simplify(a,n);m=simplify(b,m);
	if(n<m)return 0;
	assert(m>1);
	poly_div(a,b,c,n,m);
	return n-m+1;
}

void poly_rmod(int*a,int*b,int*invb,int*c,int n,int m)
{
	static int tC[poly_max];
	assert(m>1);
	poly_rdiv(a,invb,tC,n,m);
	poly_mult(b,tC,tC,m-1,min(n-m+1,m-1));
	poly_sub(a,tC,c,m-1,m-1);
}
void poly_mod(int*a,int*b,int*c,int n,int m)
{
	if(n<m)
	{
		copy(a,c,n,n);
		return;
	}
	static int tC[poly_max];
	assert(m>1);
	poly_div(a,b,tC,n,m);
	poly_mult(b,tC,tC,m-1,min(m-1,n-m+1));
	poly_sub(a,tC,c,m-1,m-1);
}
int poly_kmod(int*a,int*b,int*c,int n,int m)
{
	n=simplify(a,n);m=simplify(b,m);
	if(n<m)
	{
		copy(a,c,n,n);
		return n;
	}
	poly_mod(a,b,c,n,m);
	return m-1;
}


void poly_qpow(int*a,int*b,int n,int k,int m)
{
	static int tA[poly_max],tB[poly_max];
	copy(a,tA,n,m);copy(b,tB,0,m);tB[0]=1;
	while(k)
	{
		if(k&1)poly_mult(tB,tA,tB,m,m);
		k>>=1;
		if(k)poly_mult(tA,tA,tA,m,m);
	}
	copy(tB,b,m,m);
}

void poly_sqrt(int*a,int*b,int n,int m)
{
	static int tB[poly_max],tC[poly_max],tD[poly_max];
	assert(a[0]==1);
	int tn=up_pw2(m);
	tD[0]=1;
	for(int l=2;l<=tn;l<<=1)
	{
		int l2=l<<1;
		copy(a,tC,min(n,l),l2);
		poly_inv(tD,tB,l>>1,l);
		copy(tB,tB,l,l2);
		dft(tB,l2);dft(tC,l2);
		poly_dotmul(tB,tC,tB,l2,l2);
		dft(tB,l2,1);
		for(int i=l>>1;i<l;i++)
		{
			if(tB[i]&1)tD[i]=tB[i]+mod>>1;
			else tD[i]=tB[i]>>1;
		}
	}
	copy(tD,b,m,m);
}

void poly_derive(int*a,int*b,int n){for(int i=1;i<n;i++)b[i-1]=(LL)a[i]*i%mod;b[n-1]=0;}
#ifdef COMB
void poly_integral(int*a,int*b,int n){for(int i=n-2;i>=0;i--)b[i+1]=(LL)a[i]*inv[i+1]%mod;b[0]=0;}
#endif

#ifdef COMB
void poly_ln(int*a,int*b,int n,int m)
{
	assert(a[0]==1);
	static int tA[poly_max],tB[poly_max];
	poly_inv(a,tB,n,m);
	if(n<m)
	{
		poly_derive(a,tA,n);
		copy(tA,tA,n,m);
	}
	else poly_derive(a,tA,m);
	poly_mult(tA,tB,tA,m-1,m-1);
	poly_integral(tA,b,m);
}

void poly_exp(int*a,int*b,int n,int m)
{
	static int tB[poly_max],tC[poly_max],tD[poly_max];
	assert(a[0]==0);
	
	int tn=up_pw2(m);
	tD[0]=1;
	for(int l=2;l<=tn;l<<=1)
	{
		int l2=l<<1;
		copy(a,tC,min(n,l),l2);
		copy(tD,tD,l>>1,l2);
		poly_ln(tD,tB,l>>1,l);
		poly_sub(tC,tB,tC,l,l);tC[0]++;if(tC[0]==mod)tC[0]=0;
		
		dft(tC,l2);dft(tD,l2);
		poly_dotmul(tC,tD,tD,l2,l2);
		dft(tD,l2,1);
	}
	copy(tD,b,m,m);
}

void poly_pow(int*a,int*b,int n,int k,int m)
{
	int fir=0;while(fir<n&&a[fir]==0)fir++;
	if(fir==n||(LL)k*fir>=m)
	{
		copy(a,b,0,m);
		return;
	}
	static int tE[poly_max];
	n-=fir;m-=fir*k;
	copy(a+fir,tE,n,n);
	int coef=qpow(tE[0],k),rcoef=qpow(tE[0],mod-2);
	for(int i=0;i<n;i++)tE[i]=(LL)tE[i]*rcoef%mod;
	for(int i=0;i<m;i++)printf("%d ",tE[i]);puts("");
	poly_ln(tE,tE,n,m);
	for(int i=0;i<m;i++)printf("%d ",tE[i]);puts("");
	for(int i=0;i<m;i++)tE[i]=(LL)tE[i]*k%mod;
	poly_exp(tE,tE,m,m);
	
	for(int i=0;i<fir*k;i++)b[i]=0;
	for(int i=0;i<m;i++)b[i+fir*k]=(LL)tE[i]*coef%mod;
}
#endif

int mcoef[poly_bits][poly_max],ncoef[poly_bits][poly_max];
void eval_pre(int*b,int l,int r,int lvl)
{
	if(l==r)
	{
		mcoef[lvl][l<<1]=(b[l]==0?0:mod-b[l]);
		mcoef[lvl][l<<1|1]=1;
		return;
	}
	int mid=(l+r)>>1;
	eval_pre(b,l,mid,lvl+1);
	eval_pre(b,mid+1,r,lvl+1);
	poly_mult(mcoef[lvl+1]+(l<<1),mcoef[lvl+1]+(mid+1<<1),mcoef[lvl]+(l<<1),mid-l+2,r-mid+1,r-l+2);
}
void eval_work(int*a,int*ans,int n,int l,int r,int lvl)
{
	int sz=poly_kmod(a,mcoef[lvl]+(l<<1),ncoef[lvl]+l,n,r-l+2);
	if(l==r)
	{
		ans[l]=ncoef[lvl][l];
		return;
	}
	int mid=(l+r)>>1;
	eval_work(ncoef[lvl]+l,ans,sz,l,mid,lvl+1);
	eval_work(ncoef[lvl]+l,ans,sz,mid+1,r,lvl+1);
}
void poly_eval(int*a,int*b,int*c,int n,int m)//a: poly; b: eval_point; c: answer
{
	if(n==1)
	{
		for(int i=0;i<m;i++)c[i]=a[0];
		return;
	}
	eval_pre(b,0,m-1,0);
	eval_work(a,c,n,0,m-1,0);
}

void intp_work(int*a,int*ans,int l,int r,int lvl,int*v)
{
	if(l==r)
	{
		ncoef[lvl][l]=v[l];
		return;
	}
	int mid=(l+r)>>1;
	intp_work(a,ans,l,mid,lvl+1,v);
	intp_work(a,ans,mid+1,r,lvl+1,v);
	static int tA[poly_max];
	poly_mult(ncoef[lvl+1]+l,mcoef[lvl+1]+(mid+1<<1),ncoef[lvl]+l,mid-l+1,r-mid+1);
	poly_mult(ncoef[lvl+1]+mid+1,mcoef[lvl+1]+(l<<1),tA,r-mid,mid-l+2);
	for(int i=l;i<=r;i++)
	{
		ncoef[lvl][i]+=tA[i-l];
		if(ncoef[lvl][i]>=mod)ncoef[lvl][i]-=mod;
	}
}
void poly_intp(int*a,int*b,int*c,int n)//a: eval_point; b:val; c: poly
{
	static int ta[poly_max],tb[poly_max];
	eval_pre(a,0,n-1,0);
	//for(int i=0;i<=n;i++)printf("%d ",mcoef[0][i]);puts("");
	poly_derive(mcoef[0],ta,n+1);
	eval_work(ta,tb,n,0,n-1,0);
	for(int i=0;i<n;i++)tb[i]=(LL)b[i]*qpow(tb[i],mod-2)%mod;
	//for(int i=0;i<n;i++)printf("i= %d tb= %d\n",i,tb[i]);
	intp_work(tb,c,0,n-1,0,tb);
	copy(ncoef[0],c,n,n);
}

int a[200111],b[200111],n,m,c[200111],d[200111],e[200111];
int main()
{
	prework();
	get1(n);
	for(int i=0;i<n;i++)get2(a[i],b[i]);
	poly_intp(a,b,c,n);
	get1(m);
	for(int i=0;i<m;i++)get1(d[i]);
	poly_eval(c,d,e,n,m);
	for(int i=0;i<m;i++)printf("%d ",e[i]);
	return 0;
}
