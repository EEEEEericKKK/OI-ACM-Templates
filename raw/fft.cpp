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

const double eps=1e-10;
const int poly_bits=18;
const int poly_max=1<<poly_bits;//poly_max=2^poly_bits

int up_pw2(const int&x){int ret=1;while(ret<x)ret<<=1;return ret;}
inline int dcmp(const double&x){if(fabs(x)<eps)return 0;else if(x<0)return -1;else return 1;}
struct cpx
{
	double x,y;
	cpx(double _x=0,double _y=0){x=_x;y=_y;}
	bool operator ==(const cpx&b)const{return dcmp(b.x-x)==0&&dcmp(b.y-y)==0;}
	cpx operator+(const cpx &t){return cpx(x+t.x,y+t.y);}
	cpx operator-(const cpx &t){return cpx(x-t.x,y-t.y);}
	cpx operator*(const cpx &t){return cpx(x*t.x-y*t.y,x*t.y+y*t.x);}
	cpx operator*(const double &t){return cpx(x*t,y*t);}
	cpx conj()const{return cpx(x,-y);}
	cpx inv()const{return cpx(x/(x*x+y*y),-y/(x*x+y*y));}
};
cpx w[poly_max+1];
inline void dft(cpx*a,int n,bool rev=0)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(i<j)swap(a[i],a[j]);
		for(int t=n>>1;(j^=t)<t;t>>=1);
	}
	for(int l=1,d=poly_bits-1;l<n;l<<=1,d--)
	{
		int l2=l<<1;
		static cpx cw[poly_max];
		for(int j=0;j<l;j++)cw[j]=w[rev?poly_max-(j<<d):(j<<d)];
		for(int i=0;i<n;i+=l2)for(int j=0;j<l;j++)
		{
			cpx tmp=a[i|l|j]*cw[j];
			a[i|l|j]=a[i|j]-tmp;
			a[i|j]=a[i|j]+tmp;
		}
	}
	if(rev)for(int i=0;i<n;i++)a[i]=a[i]*(1.0/n);
}

cpx tA[poly_max],tB[poly_max];
double tC[poly_max];
void poly_mult(double*a,int n,double*b,int m,double*c,int k=-1)
{
	if(k==-1)k=n+m-1;if(n>k)n=k;if(m>k)m=k;
	if(n<=50&&m<=50)
	{
		memset(tC,0,sizeof(double)*k);
		for(int i=0;i<n;i++)for(int j=0;j<m&&j<k-i;j++)tC[i+j]+=a[i]*b[j];
		for(int i=0;i<k;i++)c[i]=tC[i];
		return;
	}
	int l=up_pw2(n+m-1);
	for(int i=0;i<l;i++)tA[i]=cpx(i<n?a[i]:0,0);
	for(int i=0;i<l;i++)tB[i]=cpx(i<m?b[i]:0,0);
	dft(tA,l);dft(tB,l);
	for(int i=0;i<l;i++)tA[i]=tA[i]*tB[i];
	dft(tA,l,1);
	for(int i=0;i<k;i++)c[i]=tA[i].x;
}

struct init_t
{
	init_t()
	{
		for(int i=0;i<=poly_max;i++)w[i]=cpx(cos(2*pi/poly_max*i),sin(2*pi/poly_max*i));
	}
} initializer;

double a[100111],b[100111];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);n++;m++;
	for(int i=0;i<n;i++)scanf("%lf",a+i);
	for(int i=0;i<m;i++)scanf("%lf",b+i);
	poly_mult(a,n,b,m,a);
	for(int i=0;i<n+m-1;i++)printf("%d ",int(a[i]+0.5));
	return 0;
}