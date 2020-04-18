namespace Matching
{
	const int maxn=511;
	int n,m;
	vector<int> con[maxn];
	int mt[maxn];
	void init(int N)
	{
		n=N;m=0;
		for(int i=1;i<=n;i++)con[i].clear();
		memset(mt,0,sizeof(mt));
	}
	void adde(int x,int y)
	{
		con[x].PB(y);
		con[y].PB(x);
	}
	int q[maxn],qn;
	int f[maxn],pre[maxn],mk[maxn];
	pair<int,int> cr[maxn];
	int gf(int x){return f[x]==x?x:f[x]=gf(f[x]);}
	void match(int x,int y){mt[x]=y;mt[y]=x;}
	void flip(int x,int y)
	{
		if(x==y)return;
		if(mk[y]==0)
		{
			flip(x,pre[pre[y]]);
			match(pre[y],pre[pre[y]]);
		}
		else
		{	
			flip(mt[y],cr[y].FF);
			flip(x,cr[y].SS);
			match(cr[y].FF,cr[y].SS);
		}
	}
	int tmp[maxn],ti;
	int getlca(int x,int y)
	{
		for(ti++,x=gf(x),y=gf(y);;x=gf(pre[x]),y=gf(pre[y]))
		{
			if(x&&tmp[x]==ti)return x;
			tmp[x]=ti;
			if(y&&tmp[y]==ti)return y;
			tmp[y]=ti;
		}
	}
	void blossom(int x,int p,pair<int,int> c)
	{
		for(x=gf(x);x!=p;x=gf(pre[x]))
		{
			f[x]=p;
			if(mk[x]==1)cr[x]=c,q[qn++]=x;
		}
	}
	bool bfs(int S)
	{
		for(int i=1;i<=n;i++)
		{
			mk[i]=-1;
			f[i]=i;
			pre[i]=0;
		}
		qn=0;
		q[qn++]=S;
		mk[S]=0;
		for(int i=0;i<qn;i++)
		{
			int x=q[i];
			for(int j=0;j<con[x].size();j++)
			{
				int u=con[x][j];
				if(gf(u)==gf(x))continue;
				if(mk[u]==-1)
				{
					if(!mt[u])
					{
						flip(S,x);
						match(x,u);
						return true;
					}
					else
					{
						int v=mt[u];
						pre[u]=x;pre[v]=u;
						mk[u]=1;mk[v]=0;
						q[qn++]=v;
					}
				}
				else
				{
					if(mk[gf(u)]==0)
					{
						int p=getlca(x,u);
						blossom(x,p,MP(x,u));
						blossom(u,p,MP(u,x));
					}
				}
			}
		}
		return false;
	}
	int solve()
	{
		for(int i=1;i<=n;i++)mt[i]=0;
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(mt[i])continue;
			ans+=bfs(i);
		}
		return ans;
	}
};
//Example
int main()
{
	int n,m;
	getii(n,m);
	Matching::init(n);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		getii(x,y);
		Matching::adde(x,y);
	}
	int ans=Matching::solve();
	putsi(ans);
	for(int i=1;i<=n;i++)puti(Matching::mt[i]);
	return 0;
}

