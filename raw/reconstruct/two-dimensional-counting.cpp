#include <bits/stdc++.h>

template<typename T,const int MAXN>
struct bit_t
{
	int timer, mark[MAXN];
	T bit[MAXN];
	bit_t(){timer = 0; memset(mark,0,sizeof(mark));}
	void add(int x,T v)
	{
		for(;x<MAXN;x+=x&-x)
		{
			if(mark[x]!=timer)
			{
				mark[x]=timer;
				bit[x]=0;
			}
			bit[x]+=v;
		}
	}
	T query(int x)
	{
		T ret=0;
		for(;x;x-=x&-x)if(mark[x]==timer)ret+=bit[x];
		return ret;
	}
};

#define maxn 100111
template<typename T>
struct twod_query
{
	struct query
	{
		int tp, time, q1, q2, q3;
		T qval;
		bool operator <(const query&b)
		{
			if(time!=b.time) return time < b.time;
			else return tp > b.tp;
		}
	};
	query q[maxn*2];
	T ans[maxn];
	int tot;
	twod_query()
	{
		tot=0;
		memset(ans,0,sizeof(ans));
	}
	
	void addpoint(int x,int y,T v){q[++tot] = query{2,x,y,0,0,v};}
	void addquery(int x,int y,int xx,int yy,int id)
	{
		q[++tot] = query{0, x-1, y, yy, id, 0};
		q[++tot] = query{1, xx, y, yy, id, 0};
	}
	
	void solve(int l,int r)
	{
		while(l<=r&&q[l].tp!=2)l++;
		while(l<=r&&q[r].tp==2)r--;
		if(l>r)return;
		
		int mid=(l+r)>>1;solve(l,mid);solve(mid+1,r);
		static query tq[maxn*2];static bit_t<T,maxn> bit;
		int ctot=0;
		for(int i=l;i<=mid;i++)if(q[i].tp==2)tq[++ctot]=q[i];
		for(int i=mid+1;i<=r;i++)if(q[i].tp!=2)tq[++ctot]=q[i];
		
		bit.timer++;
		for(int i=1;i<=ctot;i++)
		{
			if(tq[i].tp==2)bit.add(tq[i].q1,tq[i].qval);
			else
			{
				T v=bit.query(tq[i].q2)-bit.query(tq[i].q1-1);
				if(tq[i].tp==0)v=-v;
				ans[tq[i].q3]+=v;
			}
		}
	}
	void work()
	{
		memset(ans,0,sizeof(ans));
		solve(1,tot);
	}
};
#undef maxn

int main()
{
	return 0;
}