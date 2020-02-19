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

const int poly_bits=17;
const int poly_max=1<<poly_bits;
const int mod=998244353;
const int root=3;

#define COMB
int qpow(LL x,int y,const int&mod=::mod)
{
	LL ret=1;
	while(y)
	{
		if(y&1)ret=ret*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ret;
}
int up_pw2(const int&x){int ret=1;while(ret<x)ret<<=1;return ret;}
inline void copy(int*a,int n,int*b,int m)
{
	if(n>=m)memcpy(b,a,sizeof(int)*m);
	else
	{
		if(a!=b)memcpy(b,a,sizeof(int)*n);
		memset(b+n,0,sizeof(int)*(m-n));
	}
}
#ifdef COMB
int fac[poly_max+1],inv[poly_max+1],invf[poly_max+1];
int comb(int x,int y){if(y<0||x<y)return 0;return (LL)fac[x]*invf[y]%mod*invf[x-y]%mod;}
#endif

void poly_dotmul(int*a,int*b,int*c,int n){for(int i=0;i<n;i++)c[i]=(LL)a[i]*b[i]%mod;}
void poly_add(int*a,int*b,int*c,int n){for(int i=0;i<n;i++)if((c[i]=a[i]+b[i])>=mod)c[i]-=mod;}
void poly_sub(int*a,int*b,int*c,int n){for(int i=0;i<n;i++)if((c[i]=a[i]-b[i])<0)c[i]+=mod;}

void dft(int* a, int n, bool inv = 0)
{
	static int w[2][poly_max]; static bool fb = 0;
	if(!fb)
	{
		fb = 1;
		int wn0 = qpow(root, (mod-1) >> poly_bits), wn1 = qpow(wn0, mod - 2);
		w[0][0] = w[1][0] = 1;
		for(int i=1; i<poly_max; i++)
		{
			w[0][i] = 1ll * w[0][i-1] * wn0 % mod;
			w[1][i] = 1ll * w[1][i-1] * wn1 % mod;
		}
	}
	const int *W = w[inv];
	const uLL md2 = static_cast<uLL>(mod) * mod;
	for(int i=0, j=0; i<n; i++)
	{
		if(i<j) std::swap(a[i], a[j]);
		for(int t = n>>1; (j ^= t) < t; t >>= 1);
	}
	static uLL ca[poly_max];
	for(int i=0; i<n; i++) ca[i] = a[i];
	for(int l = 1, d = poly_bits - 1; l<n; l <<= 1, d--)
	{
		int l2 = l << 1;
		static int cw[poly_max];
		for(int j=0; j<l; j++) cw[j] = W[j<<d];
		for(int i=0, j; i<n; i+=l2)
		{
			uLL *x1 = ca+i, *x2 = ca+i+l, tmp;
			for(j=0; j+8 <= l; j+=8)
			{
				tmp=(*x2%mod)*cw[j];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+1];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+2];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+3];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+4];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+5];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+6];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+7];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
			}
			for(; j<l; j++)
			{
				tmp=(*x2%mod)*cw[j];
				*x2=*x1-tmp+md2;
				*x1+=tmp;
				x1++; x2++;
			}
		}
		if(l == 65536) for(int i=0; i<n; i++) ca[i] %= mod;
	}
	for(int i=0; i<n; i++) a[i] = ca[i] % mod;
	if(inv)
	{
		int inv = qpow(n, mod-2);
		for(int i=0; i<n; i++) a[i] = 1ll * a[i] * inv % mod;
	}
}


void poly_mult(int*a,int n,int*b,int m,int*c,int k=-1)
{
	static int tA[poly_max],tB[poly_max];
	if(k==-1)k=n+m-1;if(n>k)n=k;if(m>k)m=k;
	if(n<=50&&m<=50)
	{
		copy(tA,0,tA,k);
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)tA[i+j]=(tA[i+j]+(LL)a[i]*b[j])%mod;
		copy(tA,k,c,k);
		return;
	}
	int len=up_pw2(n+m-1);
	copy(a,n,tA,len);copy(b,m,tB,len);
	dft(tA,len);dft(tB,len);
	poly_dotmul(tA,tB,tA,len);
	dft(tA,len,1);
	copy(tA,k,c,k);
}

void poly_inv_do(int*a,int n,int*b,int m)
{
	if(m==1)
	{
		if(a[0]==1)b[0]=1;
		else b[0]=qpow(a[0],mod-2);
		return;
	}
	if(n>m)n=m;
	
	int nl=m+1>>1,l=up_pw2(n+nl+nl-2);
	poly_inv_do(a,n,b,nl);
	static int tA[poly_max];
	copy(a,n,tA,l);copy(b,nl,b,l);
	dft(tA,l);dft(b,l);
	for(int i=0;i<l;i++)b[i]=(mod+2-(LL)tA[i]*b[i]%mod)*b[i]%mod;
	dft(b,l,1);
}
// n + m <= poly_max
void poly_inv(int*a,int n,int*b,int m)
{
	assert(a[0]>0);
	static int tA[poly_max];
	poly_inv_do(a,n,tA,m);
	copy(tA,m,b,m);
}

void poly_div(int*a,int n,int*b,int m,int*c)
{
	assert(n>=m&&m>0);assert(a[n-1]>0&&b[m-1]>0);
	static int tA[poly_max];
	reverse(b,b+m);poly_inv(b,m,tA,n-m+1);reverse(b,b+m);
	reverse(a,a+n);poly_mult(a,n-m+1,tA,n-m+1,tA,n-m+1);reverse(a,a+n);
	copy(tA,n-m+1,c,n-m+1);reverse(c,c+n-m+1);
}

void poly_mod(int*a,int n,int*b,int m,int*c)
{
	while(n&&!a[n-1])n--;while(m&&!b[m-1])m--;
	assert(m>1);
	if(n<m)
	{
		copy(a,n,c,m-1);
		return;
	}
	static int tA[poly_max];
	poly_div(a,n,b,m,tA);
	poly_mult(b,m,tA,n-m+1,tA);
	poly_sub(a,tA,c,m-1);
}

void poly_sqrt_do(int*a,int n,int*b,int m)
{
	if(m==1)
	{
		b[0]=1;
		return;
	}
	if(n>m)n=m;
	
	int nl=(m+1)>>1,l=up_pw2(n+m-1);
	poly_sqrt_do(a,n,b,nl);
	
	static int tA[poly_max];
	poly_inv_do(b,nl,tA,m);
	poly_mult(tA,m,a,n,tA,m);
	for(int i=nl;i<m;i++)
	{
		if(tA[i]&1)b[i]=tA[i]+mod>>1;
		else b[i]=tA[i]>>1;
	}
}
void poly_sqrt(int*a,int n,int*b,int m)
{
	assert(a[0]==1);
	static int tA[poly_max];
	poly_sqrt_do(a,n,tA,m);
	copy(tA,m,b,m);
}

void poly_derive(int*a,int*b,int n)
{
	for(int i=1;i<n;i++)b[i-1]=(LL)a[i]*i%mod;
	b[n-1]=0;
}

#ifdef COMB
void poly_integral(int*a,int*b,int n)
{
	for(int i=n-2;i>=0;i--)b[i+1]=(LL)a[i]*inv[i+1]%mod;
	b[0]=0;
}

// 2 * m <= poly_max
void poly_ln(int*a,int n,int*b,int m)
{
	assert(a[0]==1);
	static int tA[poly_max],tB[poly_max];
	poly_inv(a,n,tB,m);
	if(n<m)
	{
		poly_derive(a,tA,n);
		copy(tA,n,tA,m);
	}
	else poly_derive(a,tA,m);
	poly_mult(tA,m-1,tB,m-1,tB,m-1);
	poly_integral(tB,b,m);
}

void poly_exp_do(int*a,int n,int*b,int m)
{
	if(m==1)
	{
		b[0]=1;
		return;
	}
	if(n>m)n=m;
	
	int nl=(m+1)>>1;
	poly_exp_do(a,n,b,nl);
	
	static int tA[poly_max];
	
	poly_ln(b,nl,tA,m);
	for(int i=0;i<m;i++)
	{
		tA[i]=(i<n?a[i]:0)-tA[i];
		if(tA[i]<0)tA[i]+=mod;
	}
	tA[0]=(tA[0]==mod-1?0:tA[0]+1);
	
	poly_mult(b,m,tA,m,b,m);
}
// 4 * m <= poly_max
void poly_exp(int*a,int n,int*b,int m)
{
	assert(a[0]==0);
	static int tA[poly_max];
	poly_exp_do(a,n,tA,m);
	copy(tA,m,b,m);
}

// 4 * m <= poly_max
void poly_pow(int*a,int n,int*b,int m,int k)
{
	int fir=0;while(fir<n&&a[fir]==0)fir++;
	if(fir==n||(LL)k*fir>=m)
	{
		copy(a,0,b,m);
		return;
	}
	static int tA[poly_max];
	n-=fir;m-=fir*k;
	copy(a+fir,n,tA,n);
	int coef=qpow(tA[0],k),rcoef=qpow(tA[0],mod-2);
	for(int i=0;i<n;i++)tA[i]=(LL)tA[i]*rcoef%mod;
	
	poly_ln(tA,n,tA,m);
	for(int i=0;i<m;i++)tA[i]=(LL)tA[i]*k%mod;
	poly_exp(tA,m,tA,m);
	for(int i=0;i<fir*k;i++)b[i]=0;
	for(int i=0;i<m;i++)b[i+fir*k]=(LL)tA[i]*coef%mod;
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
	poly_mult(mcoef[lvl+1]+(l<<1),mid-l+2,mcoef[lvl+1]+(mid+1<<1),r-mid+1,mcoef[lvl]+(l<<1),r-l+2);
}
void eval_work(int*a,int*ans,int n,int l,int r,int lvl)
{
	poly_mod(a,n,mcoef[lvl]+(l<<1),r-l+2,ncoef[lvl]+l);
	if(l==r)
	{
		ans[l]=ncoef[lvl][l];
		return;
	}
	int mid=(l+r)>>1;
	eval_work(ncoef[lvl]+l,ans,r-l+1,l,mid,lvl+1);
	eval_work(ncoef[lvl]+l,ans,r-l+1,mid+1,r,lvl+1);
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
	poly_mult(ncoef[lvl+1]+l,mid-l+1,mcoef[lvl+1]+(mid+1<<1),r-mid+1,ncoef[lvl]+l);
	poly_mult(ncoef[lvl+1]+mid+1,r-mid,mcoef[lvl+1]+(l<<1),mid-l+2,tA);
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
	poly_derive(mcoef[0],ta,n+1);
	eval_work(ta,tb,n,0,n-1,0);
	for(int i=0;i<n;i++)tb[i]=(LL)b[i]*qpow(tb[i],mod-2)%mod;
	intp_work(tb,c,0,n-1,0,tb);
	copy(ncoef[0],n,c,n);
}

int n,a[poly_max],b[poly_max];
int main()
{
	n=100;
	for(int i=0;i<n;i++)a[i]=1;
	poly_ln(a,n,b,n);
	for(int i=0;i<n;i++)printf("%d ",b[i]*1ll*i%mod);
	return 0;
}
