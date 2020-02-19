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

struct sparse_table
{
	int lg[100111],v[20][100111],n;
	void construct(int n,int *a)
	{
		this->n=n;
		for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;i++)v[0][i]=a[i];
		for(int i=1;i<20;i++)for(int j=1;j<=n;j++)
		{
			int nxt=j+(1<<i-1);
			if(nxt>n)v[i][j]=v[i-1][j];
			else v[i][j]=min(v[i-1][j],v[i-1][nxt]);
		}
	}
	int query(int l,int r)
	{
		int len=lg[r-l+1];
		return min(v[len][l],v[len][r-(1<<len)+1]);
	}
};

int main()
{
	return 0;
}
