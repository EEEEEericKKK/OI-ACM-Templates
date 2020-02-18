#include <bits/stdc++.h>

using std::vector;
using std::queue;

#define maxn 5111
//labels starting from one
template<typename Mat1,typename Mat2>
vector<int> Matroid_Intersection(Mat1 &M1, Mat2 &M2)
{
	static bool choose[maxn], X1[maxn], X2[maxn], vis[maxn];
	static int pre[maxn];
	static vector<int> g[maxn];
	if(!M1.check(vector<int>())||!M2.check(vector<int>()))return vector<int>();
	assert(M1.size()==M2.size());
	int SZ=M1.size();
	memset(choose,0,sizeof(choose[0])*(SZ+1));
	vector<int> base;
	for(int i=1;i<=SZ;i++)if(M1.test(i)&&M2.test(i))
	{
		base.push_back(i);
		choose[i]=1;
		M1.check(base);M2.check(base);
	}
	
	while(true)
	{
		memset(vis,0,sizeof(vis[0])*(SZ+1));
		memset(X1,0,sizeof(X1[0])*(SZ+1));
		memset(X2,0,sizeof(X2[0])*(SZ+1));
		for(int i=1;i<=SZ;i++)g[i].clear();
		vector<int> I;
		for(int i=1;i<=SZ;i++)if(choose[i])I.push_back(i);
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

struct Color_Matroid
{
	int col[maxn], lim[maxn], count[maxn], SZ, SZ_c;
	int size(){return SZ;}
	inline bool check(const vector<int> &v)
	{
		memset(count, 0, sizeof(int) * (SZ_c+1));
		for(int i=0; i<v.size(); i++)
		{
			int c = col[v[i]];
			count[c] ++;
			if(count[c] > lim[c]) return false;
		}
		return true;
	}
	inline bool test(int x){return count[col[x]] < lim[col[x]];}
};

#undef maxn

int main()
{
	return 0;
}