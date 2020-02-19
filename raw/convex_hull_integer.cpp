#include<bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;

const int maxn=500111;

LL det(const pii&a,const pii&b){return (LL)a.ff*b.ss-(LL)a.ss*b.ff;}
LL det(const pii&a,const pii&b,const pii&c){return det(mp(b.ff-a.ff,b.ss-a.ss),mp(c.ff-a.ff,c.ss-a.ss));}

int n;
pii p[maxn],offset,stk[maxn],q[maxn];

bool cmp(const pii&x,const pii&y)
{
	LL p=det(x,y);
	if(p!=0)return p>0;
	else return abs(x.ff)+abs(x.ss)<abs(y.ff)+abs(y.ss);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i].ff,&p[i].ss);
	
	sort(p+1,p+n+1);
	offset=p[1];
	for(int i=1;i<=n;i++)
	{
		p[i].ff-=offset.ff;
		p[i].ss-=offset.ss;
	}
	sort(p+2,p+n+1,cmp);
	int top=n;
//	if angles of degree 180 is allowed : add the following, change <= to <
//	while(top>=1&&det(p[top],p[n])==0)top--;
//	if(top>1)reverse(p+top+1,p+n+1);
	for(int i=1;i<=n;i++)
	{
		p[i].ff+=offset.ff;
		p[i].ss+=offset.ss;
	}
	
	top=0;
	for(int i=1;i<=n;i++)
	{
		while(top>1&&det(stk[top-1],stk[top],p[i])<=0)
		{
			q[++m]=stk[top];
			top--;
		}
		stk[++top]=p[i];
	}
	for(int i=1;i<=top;i++)p[i]=stk[i];
	n=top;
	
	return 0;
}
