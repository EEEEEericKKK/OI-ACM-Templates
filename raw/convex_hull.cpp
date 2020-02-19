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
