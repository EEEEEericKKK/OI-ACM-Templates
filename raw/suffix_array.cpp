// This amazing code is by Eric Sunli Chen.
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;

const int maxn=500111;
struct suffix_array
{
	int sa[maxn],t[maxn],t2[maxn],c[maxn],n;
	int rk[maxn],v[20][maxn],lg[maxn];
	void construct_sa(char*s)
	{
		vector<int> all;for(int i=0;i<n;i++)all.pb(s[i]);
		sort(all.begin(),all.end());all.erase(unique(all.begin(),all.end()),all.end());
		
		int m=all.size();
		for(int i=0;i<n;i++)s[i]=lower_bound(all.begin(),all.end(),s[i])-all.begin();
		
		int *x=t,*y=t2;
		for(int i=0;i<m;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]=s[i]]++;
		for(int i=1;i<m;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
		
		for(int k=1;k<=n;k<<=1)
		{
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
	}
	void construct_lcp(char*s)
	{
		int k=0;
		for(int i=0;i<n;i++)rk[sa[i]]=i;
		for(int i=0;i<n-1;i++)
		{
			if(k)k--;
			int j=sa[rk[i]-1];
			while(s[i+k]==s[j+k])k++;
			v[0][rk[i]]=k;
		}
		for(int i=2;i<n;i++)lg[i]=lg[i>>1]+1;
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
	void get_bound(int v,int len,int &lb,int &ub)
	{
		v=rk[v];
		int l=0,r=v,mid;
		while(l<r-1)
		{
			mid=(l+r)>>1;
			if(qlcp(sa[mid],sa[v])>=len)r=mid;else l=mid;
		}
		lb=r;
		l=v;r=n;
		while(l<r-1)
		{
			mid=(l+r)>>1;
			if(qlcp(sa[mid],sa[v])>=len)l=mid;else r=mid;
		}
		ub=l;
	}
}sa;
char s[500111];
int main()
{
	scanf("%s",s);
	sa.n=strlen(s)+1;
	reverse(s,s+sa.n-1);
	sa.construct_sa(s);
	sa.construct_lcp(s);
	printf("sa 1 ");for(int i=1;i<sa.n;i++)printf("%d ",sa.n-sa.sa[i]);puts("");
	printf("h ");for(int i=1;i<sa.n;i++)printf("%d ",sa.v[0][i]);puts("");
	return 0;
}
