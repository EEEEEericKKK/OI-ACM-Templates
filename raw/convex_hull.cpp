#include <bits/stdc++.h>
using std::vector;
typedef double db;

struct point
{
	db x, y;
	point(db _x = 0, db _y = 0) { x = _x; y = _y; }
	bool operator < (const point &rhs) const{ return std::make_pair(x, y) < std::make_pair(rhs.x, rhs.y); }
	db operator *(const point &rhs) const { return x * rhs.y - y * rhs.x; }
	point operator -(const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
};

vector<point> convex_hull(vector<point> points)
{
	if ((int)points.size() == 1)
	{
		return points;
	}
	vector<point> hull;
	for (int rot = 0; rot < 2; ++rot)
	{
		int limit = hull.size();
		for (auto p : points)
		{
			while ((int)hull.size() > limit + 1 && (hull[hull.size() - 1] - hull[hull.size() - 2]) * (p - hull[hull.size() - 2]) <= 0)
			{
				hull.pop_back();
			}
			hull.push_back(p);
		}
		hull.pop_back();
		reverse(points.begin(), points.end());
	}
	return hull;
}

int main()
{
	return 0;
}