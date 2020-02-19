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
typedef vector<int> vi;
const int inf=0x3f3f3f3f;
const LL Linf=1ll<<61;
const double pi=acos(-1.0);
 
const int maxn=5111;
//labels starting from one
template<typename Mat1,typename Mat2>
vector<int> Matroid_Intersection(Mat1&M1,Mat2&M2)
{
	static bool choose[maxn],X1[maxn],X2[maxn],vis[maxn];
	static int pre[maxn];
	static vector<int> g[maxn];
	
	if(!M1.check(vector<int>())||!M2.check(vector<int>()))return vector<int>();
	
	assert(M1.size()==M2.size());int SZ=M1.size();
	memset(choose,0,sizeof(choose[0])*(SZ+10));
	
	vector<int> base;
	for(int i=1;i<=SZ;i++)if(M1.test(i)&&M2.test(i))
	{
		base.pb(i);
		choose[i]=1;
		M1.check(base);M2.check(base);
	}
	
	while(true)
	{
		memset(vis,0,sizeof(vis[0])*(SZ+10));
		memset(X1,0,sizeof(X1[0])*(SZ+10));
		memset(X2,0,sizeof(X2[0])*(SZ+10));
		for(int i=1;i<=SZ;i++)g[i].clear();
		
		vector<int> I;
		for(int i=1;i<=SZ;i++)if(choose[i])I.pb(i);
		
		assert(M1.check(I));
		assert(M2.check(I));
		
		bool update=0;
		for(int i=1;i<=SZ;i++)if(!choose[i])
		{
			X1[i]=M1.test(i);
			X2[i]=M2.test(i);
			if(X1[i]&&X2[i])
			{
				choose[i]=1;
				update=1;
				break;
			}
		}
		
		for(auto x:I)
		{
			vector<int>nI;
			for(auto v:I)if(v!=x)nI.push_back(v);
			M1.check(nI);
			M2.check(nI);
			
			for(int i=1;i<=SZ;i++)if(!choose[i])
			{
				if(M2.test(i))g[i].push_back(x);
				if(M1.test(i))g[x].push_back(i);
			}
		}
		
		if(update)continue;
		queue<int> q;
		for(int i=1;i<=SZ;i++)if(X1[i])
		{
			vis[i]=1;
			pre[i]=0;
			q.push(i);
		}
		
		while(!q.empty())
		{
			int x=q.front();q.pop();
			if(X2[x])
			{
				update=1;
				int cur=x;
				while(cur)
				{
					choose[cur]^=1;
					cur=pre[cur];
				}
				break;
			}
			
			for(int i=0;i<(int)g[x].size();i++)if(!vis[g[x][i]])
			{
				vis[g[x][i]]=1;
				q.push(g[x][i]);
				pre[g[x][i]]=x;
			}
		}
		if(!update)return I;
	}
}
 
/*
struct Matroid
{
	int SZ;
	int size();
	bool check(vector<int> v);
	bool test(int x);
};
*/
 
int n,m,tot;
struct Color_Matroid
{
	int col[maxn],lim[maxn],SZ;
	int count[66];
	inline int size(){return SZ;}
	inline bool check(const vector<int>&v)
	{
		memset(count,0,sizeof(int)*m);
		for(int i=0;i<(int)v.size();i++)
		{
			assert(1<=v[i]&&v[i]<=SZ);
			int c=col[v[i]];
			count[c]++;
			if(count[c]>lim[c])return false;
		}
		return true;
	}
	inline bool test(int x){return count[col[x]]<lim[col[x]];}
}M1;
uLL val[65],val2[5111];
 
struct Linear_Matroid
{
	int SZ;uLL b[65];int cnt;
	inline int size(){return SZ;}
	inline bool check(const vector<int>&v)
	{
		cnt=0;
		for(int i=0;i<n;i++)
		{
			uLL nv=val[i];
			for(int j=0;j<cnt&&nv;j++)if(nv&b[j]&-b[j])nv^=b[j];
			if(!nv)return false;
			for(int j=0;j<cnt;j++)if(nv&-nv&b[j])b[j]^=nv;
			b[cnt++]=nv;
		}
		for(int i=0;i<(int)v.size();i++)
		{
			uLL nv=val2[v[i]];
			for(int j=0;j<cnt&&nv;j++)if(nv&b[j]&-b[j])nv^=b[j];
			if(!nv)return false;
			for(int j=0;j<cnt;j++)if(nv&-nv&b[j])b[j]^=nv;
			b[cnt++]=nv;
		}
		return true;
	}
	inline bool test(int x)
	{
		uLL nv=val2[x];
		for(int j=0;j<cnt&&nv;j++)if(nv&b[j]&-b[j])nv^=b[j];
		return (nv!=0);
	}
}M2;
 
int main()
{
	get1(n);for(int i=0;i<n;i++)get1(val[i]);get1(m);
	for(int i=0,sz;i<m;i++)
	{
		M1.lim[i]=1;
		get1(sz);
		while(sz--)
		{
			tot++;
			get1(val2[tot]);
			M1.col[tot]=i;
		}
	}
	
	M1.SZ=M2.SZ=tot;
	vector<int> ans=Matroid_Intersection(M1,M2);
	if((int)ans.size()<m)
	{
		puts("-1");
		return 0;
	}
	sort(ans.begin(),ans.end());
	for(int i=0;i<m;i++)printf("%llu\n",val2[ans[i]]);
	return 0;
}