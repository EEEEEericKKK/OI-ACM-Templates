#include <cstdio>
#include <cassert>

#include <vector>

using namespace std;

using i64 = long long;

int mod_inv(int a, int mod)
{
	int b = mod, s = 1, t = 0, old_a = a;
	while (b)
	{
		int q = a / b;
		swap(a %= b, b);
		swap(s -= t * q, t);
	}
	if (a != 1)
	{
		fprintf(stderr,
				"Error: %d^{-1} mod %d does not exist.\n\n", old_a, mod);
		assert(0);
	}
	return s < 0 ? s + mod : s;
}

vector<int> extended(int n,
					 const vector<vector<int>> &coeffs, const vector<int> &terms, int mod)
{

	vector<int> ret(max<int>(n + 1, terms.size()));
	copy(terms.begin(), terms.end(), ret.begin());
	const int order = coeffs.size() - 1;
	const int deg = coeffs[0].size() - 1;
	assert((int)terms.size() >= order);
	for (int m = terms.size(); m <= n; ++m)
	{
		int s = 0;
		for (int i = 1; i <= order; ++i)
		{
			int k = m - i, t = ret[k];
			for (int d = 0; d <= deg; ++d)
			{
				s = (s + i64(t) * coeffs[i][d]) % mod;
				t = i64(t) * k % mod;
			}
		}
		int denom = 0, mpow = 1;
		for (int d = 0; d <= deg; ++d)
		{
			denom = (denom + i64(mpow) * coeffs[0][d]) % mod;
			mpow = i64(mpow) * m % mod;
		}
		ret[m] = i64(mod - s) * mod_inv(denom, mod) % mod;
	}
	return ret;
}

vector<vector<int>> find_recurrence_relation(
	const vector<int> &terms, const int deg, const int mod, bool verify = true)
{

	const int n = terms.size();
	const int B = (n + 2) / (deg + 2); // number of blocks
	const int C = B * (deg + 1);	   // number of columns
	const int R = n - (B - 1);		   // number of rows
	assert(B >= 2);
	assert(R >= C - 1);

	auto mul = [mod](int a, int b) { return i64(a) * b % mod; };
	auto fixed = [mod](int a) { return (a %= mod) < 0 ? a + mod : a; };
	auto error = [](int order, int deg) {
		fprintf(stderr,
				"Error: Could not find a recurrence relation "
				"of order <= %d and degree <= %d.\n\n",
				order, deg);
		assert(0);
	};

	vector<vector<int>> mat(R, vector<int>(C));
	for (int y = 0; y < R; ++y)
	{
		for (int b = 0; b < B; ++b)
		{
			for (int d = 0, v = fixed(terms[y + b]); d <= deg; ++d)
			{
				mat[y][b * (deg + 1) + d] = v;
				v = mul(v, y + b);
			}
		}
	}

	int rank = 0;
	for (int x = 0; x < C; ++x)
	{
		int pivot = -1;
		for (int y = rank; y < R; ++y)
			if (mat[y][x] != 0)
			{
				pivot = y;
				break;
			}
		if (pivot < 0)
			break;
		if (pivot != rank)
			swap(mat[rank], mat[pivot]);
		int inv = mod_inv(mat[rank][x], mod);
		for (int x2 = x; x2 < C; ++x2)
			mat[rank][x2] = mul(mat[rank][x2], inv);
		for (int y = rank + 1; y < R; ++y)
			if (mat[y][x])
			{
				int c = mod - mat[y][x];
				for (int x2 = x; x2 < C; ++x2)
				{
					mat[y][x2] = (i64(mat[y][x2]) + i64(c) * mat[rank][x2]) % mod;
				}
			}
		++rank;
	}

	if (rank == C)
		error(B - 1, deg);

	for (int y = rank - 1; y >= 0; --y)
		if (mat[y][rank])
		{
			assert(mat[y][y] == 1);
			int c = mod - mat[y][rank];
			for (int y2 = 0; y2 < y; ++y2)
			{
				mat[y2][rank] = (mat[y2][rank] + i64(c) * mat[y2][y]) % mod;
			}
		}

	int order = rank / (deg + 1);
	vector<vector<int>> ret(order + 1, vector<int>(deg + 1));
	ret[0][rank % (deg + 1)] = 1;
	for (int y = rank - 1; y >= 0; --y)
	{
		int k = order - y / (deg + 1), d = y % (deg + 1);
		ret[k][d] = (mod - mat[y][rank]) % mod;
	}

	if (verify)
	{
		auto extended_terms = extended(n - 1, ret,
									   vector<int>(terms.begin(), terms.begin() + order), mod);
		for (int i = 0; i < (int)terms.size(); ++i)
		{
			if (fixed(terms[i] - extended_terms[i]) != 0)
				error(B - 1, deg);
		}
	}

	auto verbose = [&] {
		int last = verify ? n - 1 : order + R - 1;
		fprintf(stderr,
				"[ Found a recurrence relation ]\n"
				"- order %d\n"
				"- degree %d\n"
				"- verified up to a(%d) (number of non-trivial terms: %d)\n",
				order, deg, last, (last + 1) - ((deg + 2) * (order + 1) - 2));
		fprintf(stderr, "{\n");
		for (int k = 0; k <= order; ++k)
		{
			fprintf(stderr, "  {");
			for (int d = 0; d <= deg; ++d)
			{
				if (d)
					fprintf(stderr, ", ");
				fprintf(stderr, "%d", ret[k][d] <= mod / 2 ? ret[k][d] : ret[k][d] - mod);
			}
			fprintf(stderr, "}%s\n", k == order ? "" : ",");
		}
		fprintf(stderr, "}\n\n");
	};
	verbose();

	return ret;
}

vector<int> show_extended_sequence(int n, const vector<int> &terms, int degree, int mod)
{
	auto coeffs = find_recurrence_relation(terms, degree, mod);
	auto extended_terms = extended(n, coeffs, terms, mod);
	return extended_terms;
}

int main()
{
	const int mod = 998244353;
	auto g = show_extended_sequence(20000001, {1,9,114,2490,80190,3586590,212418360,114039112,432182346,878606070,852166888,576962735,
401992636,698176559,974800456,348564441,812128772,904445927,869858393,344087871,
707457170,870835070,209999881,113952781,75931335,115339459,497962577,806293965,
280865767,733253431,396583851,464638671,534169032,589251856,585293565,893620072,
894854912,401194812,962118800,941769335,607236264,725467846,713625950,729362819,
119750436,706727495,688739359,605839506,790309880,890869339}, 3, mod);
	g.insert(g.begin(), 0);
	int tp,x,y;
	scanf("%d%d",&tp,&x);
	if(tp==0)printf("%d\n",g[x]);
	else
	{
		scanf("%d",&y);
		int ans=0,p=1;
		for(int i=x;i<=y;i++)
		{
			ans=(ans+1ll*p*g[i])%mod;
			p=233ll*p%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
