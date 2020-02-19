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

const int maxn=200111;
int lg[maxn];
struct arithseq
{
	int st,ed,diff;
	arithseq(){}
	arithseq(int a,int b,int c){st=a;ed=b;diff=c;}
	arithseq shift(const int&x)const{return arithseq(st+x,ed+x,diff);}
	arithseq neg()const{return arithseq(-ed,-st,diff);}
	bool have(const int&x)const{return (x>=st&&x<=ed&&(st-x)%diff==0);}
};
arithseq un(const arithseq&a,const arithseq&b)
{
	if(a.diff!=b.diff)
	{
		int k1=-1,k2=-1;
		if((a.ed-a.st)<=(a.diff<<1))
		{
			for(int i=a.st;i<=a.ed;i+=a.diff)
				if(b.have(i))
				{
					if(k1==-1)k1=i;
					else k2=i;
				}
		}
		else if((b.ed-b.st)<=(b.diff<<1))
		{
			for(int i=b.st;i<=b.ed;i+=b.diff)
				if(a.have(i))
				{
					if(k1==-1)k1=i;
					else k2=i;
				}
		}
		else
		{
			
		}
		if(k1==-1)return arithseq(-1,-1,-1);
		else if(k2==-1)return arithseq(k1,k1,1);
		else return arithseq(k1,k2,k2-k1);
	}
	else if((b.st-a.st)%a.diff)return arithseq(-1,-1,-1);
	else if(a.ed<b.st||b.ed<a.st)return arithseq(-1,-1,-1);
	else return arithseq(max(a.st,b.st),min(a.ed,b.ed),a.diff);
}

struct IPM
{
	int sa[maxn],rk[maxn],nrk[maxn],c[maxn],n;
	int v[20][maxn];
	
	int id[20][maxn],mxl;
	vector<int> sq[20*maxn];
	void construct(char*s)
	{
		n=strlen(s)+1;int m=256;
		for(int i=2;i<maxn;i++)lg[i]=lg[i>>1]+1;
		
		int*x=rk,*y=nrk;
		for(int i=0;i<m;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]=s[i]]++;
		for(int i=1;i<m;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
		
		int tot=0;mxl=0;
		for(int k=1;k<=n;k<<=1)
		{
			for(int i=0,nxt=0;i<n;i=nxt)
			{
				for(;nxt<n&&x[sa[i]]==x[sa[nxt]];nxt++);
				
				tot++;sq[tot].clear();
				for(int j=i;j<nxt;j++)
				{
					sq[tot].pb(sa[j]);
					id[lg[k]][sa[j]]=tot;
				}
				sort(sq[tot].begin(),sq[tot].end());
			}
			mxl=k;
			
			int p=0;
			for(int i=n-k;i<n;i++)y[p++]=i;
			for(int i=0;i<n;i++)if(sa[i]>=k)y[p++]=sa[i]-k;
			for(int i=0;i<m;i++)c[i]=0;
			for(int i=0;i<n;i++)c[x[y[i]]]++;
			for(int i=1;i<m;i++)c[i]+=c[i-1];
			for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
			swap(x,y);
			x[sa[0]]=0;p=1;
			for(int i=1;i<n;i++)x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
			if(p>=n)break;
			m=p;
		}
		
		int k=0;
		for(int i=0;i<n;i++)rk[sa[i]]=i;
		for(int i=0;i<n-1;i++)
		{
			if(k)k--;
			int j=sa[rk[i]-1];
			while(s[i+k]==s[j+k])k++;
			v[0][rk[i]]=k;
		}
		
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
		if(l==r)return n-l;
		l=rk[l];
		r=rk[r];
		if(l>r)swap(l,r);l++;
		int t=lg[r-l+1];
		return min(v[t][l],v[t][r-(1<<t)+1]);
	}
	
	int pred(int l,int k,int pos)
	{
		if(k>mxl)
		{
			if(pos>=l)return l;
			else return -1;
		}
		vector<int>&v=sq[id[lg[k]][l]];
		int id=upper_bound(v.begin(),v.end(),pos)-v.begin();
		if(id)return v[id-1];
		else return -1;
	}
	int succ(int l,int k,int pos)
	{
		if(k>mxl)
		{
			if(pos<=l)return l;
			else return -1;
		}
		vector<int>&v=sq[id[lg[k]][l]];
		int id=lower_bound(v.begin(),v.end(),pos)-v.begin();
		if(id<(int)v.size())return v[id];
		else return -1;
	}
	
	vector<arithseq> get_border(int l,int r)
	{
		int len=r-l+1,l1,l2,l3,r1,r2,r3;
		vector<arithseq> ret;
		for(int k=1;k<len;k<<=1)
		{
			int tl=l,tr=r-k+1;
			l1=succ(tr,k,tl);if(l1==-1||l1>=l+k||l1>=r)continue;
			r1=pred(tl,k,tr);if(r1==-1||r1<=tr-k||r1<=l)continue;
			l2=succ(tr,k,l1+1);l3=pred(tr,k,l+k-1);
			r2=pred(tl,k,r1-1);r3=succ(tl,k,max(l+1,tr-k+1));
			arithseq k1,k2;
			if(l2!=-1)k1=arithseq(l1-l+k,l3-l+k,l2-l1);else k1=arithseq(l1-l+k,l1-l+k,1);
			if(r2!=-1)k2=arithseq(tr-r1+k,tr-r3+k,r1-r2);else k2=arithseq(tr-r1+k,tr-r1+k,1);
			arithseq now=un(k1,k2);if(now.diff!=-1)ret.pb(now);
		}
		return ret;
	}
}thor;

char s[maxn];
int n,q,l,r;
int main()
{
	scanf("%s",s);
	thor.construct(s);
	get1(q);
	while(q--)
	{
		get2(l,r);
		vector<arithseq> ans=thor.get_border(l,r);
	}
	return 0;
}
