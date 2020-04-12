#include <bits/stdc++.h>

// #define RandMod
namespace HASH
{
const int maxn = 100111;
const int Base = 443;
#ifndef RandMod
const int Mod1 = 998244353, Mod2 = 1e9+7;
#else
int Mod1, Mod2;
#endif

bool isP(int x)
{
	if(x == 1) return false;
	for(int i=2; i*i<=x; i++) if(x % i == 0) return false;
	return true;
}

int P1[maxn], P2[maxn], pre1[maxn], pre2[maxn], n;
void prework()
{
#ifdef RandMod
	if(!Mod1)
	{
		static std::mt19937 rng(std::chrono::high_resolution_clock().now().time_since_epoch().count());
		do
		{
			Mod1 = std::uniform_int_distribution<int>(500000000, 1000000111);
		} while(!isP(Mod1));
		do
		{
			Mod2 = std::uniform_int_distribution<int>(500000000, 1000000111);
		} while(!isP(Mod2) || Mod1 == Mod2);
	}
#endif
	P1[0] = P2[0] = 1;
	for(int i=1; i<maxn; i++)
	{
		P1[i] = 1ll * P1[i-1] * Base % Mod1;
		P2[i] = 1ll * P2[i-1] * Base % Mod2;
	}
}
template<typename Tp>
void work(Tp *s, int N)
{
	if(!P1[0]) prework();
	n = N;
	for(int i=1; i<=n; i++)
	{
		int v = static_cast<int>(s[i]);
		pre1[i] = (1ll * pre1[i-1] * Base + v) % Mod1;
		pre2[i] = (1ll * pre2[i-1] * Base + v) % Mod2;
	}
}
inline unsigned long long calhash(int l, int r)
{
	if(l > r) return 0ull;
	int H1 = (pre1[r] - 1ll * pre1[l-1] * P1[r-l+1]) % Mod1; if(H1 < 0) H1 += Mod1;
	int H2 = (pre2[r] - 1ll * pre2[l-1] * P2[r-l+1]) % Mod2; if(H2 < 0) H2 += Mod2;
	return 1llu * H1 * Mod2 + H2 + 1;
}
bool same(int l, int r, int ll, int rr) { return calhash(l, r) == calhash(ll, rr); }
int lcp(int x, int y)
{
	if(x == y) return n - x + 1;
	int l = 0, r = n - std::max(x, y) + 2, mid;
	while(l < r-1)
	{
		int mid = (l + r) / 2;
		if(calhash(x, x+mid-1) == calhash(y, y+mid-1)) l = mid;
		else r = mid;
	}
	return l;
}
int lcs(int x, int y)
{
	if(x == y) return x;
	int l = 0, r = std::min(x, y) + 1, mid;
	while(l < r-1)
	{
		int mid = (l + r) / 2;
		if(calhash(x-mid+1, x) == calhash(y-mid+1, y)) l = mid;
		else r = mid;
	}
	return l;
}
} // namespace HASH

namespace Runs
{
const int maxn = 100111;
int n, sv[maxn], lcp[maxn];
std::unordered_map<unsigned long long, int> RUNS;
int timer;
bool cmp(int x, int y)
{
	int l = HASH::lcp(x, y);
	return sv[x+l] < sv[y+l];
}
void addRun(int lv, int rv, std::vector<std::pair<std::pair<int,int>,int>> &ret)
{
	if(sv[lv] != sv[rv]) return;
	int s = lv - HASH::lcs(lv, rv) + 1, t = rv + HASH::lcp(lv, rv) - 1, l = rv - lv;
	if(l + l <= t - s + 1)
	{
		unsigned long long now = 1ull * s * (n+1) * (n+1) + 1ll * t * (n+1) + l;
		if(RUNS[now] != timer) 
		{
			RUNS[now] = timer;
			ret.emplace_back(std::make_pair(s, t), l);
		}
	}
}
std::vector<std::pair<std::pair<int,int>,int>> work(char *s)
{
	n = strlen(s); for(int i=0; i<n; i++) sv[i+1] = s[i]-'a';
	sv[n+1] = -1;
	HASH::work(sv, n);
	timer++;
	std::vector<std::pair<std::pair<int,int>,int>> ret;
	for(int tp=0; tp<2; tp++)
	{
		static int stk[maxn], top;
		top = 0;
		for(int i=n; i>=1; i--)
		{
			while(top && cmp(i, stk[top]) == tp) top--;
			stk[++top] = i;
			if(top > 1) addRun(stk[top], stk[top-1], ret);
		}
	}
	return ret;
}
} // namespace Runs

const int maxn = 100111;
char s[maxn]; 
int main()
{
	scanf("%s", s);
	auto all = Runs::work(s);
	for(auto run : all) printf("s= %d t= %d l= %d\n", run.first.first, run.first.second, run.second);
	return 0;
}