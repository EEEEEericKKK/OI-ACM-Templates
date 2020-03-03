#include <bits/stdc++.h>

const int maxn = 500111;
struct Suffix
{
	int S[maxn], n, m, c[maxn], rk[maxn], nrk[maxn], sa[maxn], h[maxn];
	void construct()
	{
		int *x = rk, *y = nrk;
		memset(c, 0, sizeof(int)*m);
		for(int i=0; i<n; i++) c[x[i] = S[i]]++;
		for(int i=1; i<m; i++) c[i] += c[i-1];
		for(int i=n-1; i>=0; i--) sa[--c[x[i]]] = i;
	}
};