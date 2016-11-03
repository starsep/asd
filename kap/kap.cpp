#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

#define X first
#define Y second

using edge = std::pair<int, int>;
using point = std::pair<int, int>;

int n;
std::vector<std::vector<edge>> G;
std::vector<point> points;

void addEdges(std::vector<int> &v) {
	auto dist = [](const point &A, const point &B) {
		return std::min(std::abs(A.X - B.X), std::abs(A.Y - B.Y));
	};
	auto iterate = [&v, &dist]() {
		for (size_t i = 1; i < v.size(); i++) {
			int a = v[i];
			int b = v[i - 1];
			int d = dist(points[a], points[b]);
			G[a].push_back(std::make_pair(b, d));
			G[b].push_back(std::make_pair(a, d));
		}
	};
	iterate();
	std::reverse(v.begin(), v.end());
	iterate();
}

std::vector<int> result;
struct cmp {
	bool operator()(const int a, const int b) {
		if (result[a] != result[b]) {
			return result[a] < result[b];
		}
		return a < b;
	}
};

std::set<int, cmp> queue;

void dijkstra(int v) {
	const int INF = 1e9 + 16;
	for (int i = 0; i < n; i++) {
		result[i] = INF;
	}
	result[v] = 0;
	queue.insert(v);
	while (!queue.empty()) {
		v = *queue.begin();
		queue.erase(queue.begin());
		for (size_t i = 0; i < G[v].size(); i++) {
			int u = G[v][i].X;
			int cost = G[v][i].Y;
			if (result[v] + cost < result[u]) {
				result[u] = result[v] + cost;
				queue.insert(u);
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	G.resize(n);
	result.resize(n);
	points.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &points[i].X, &points[i].Y);
	}
	
	std::vector<int> order;
	for (int i = 0; i < n; i++) {
		order.push_back(i);
	}
	
	auto cmpByX = [](const int a, const int b) {
		if (points[a].X != points[b].X) {
			return points[a].X < points[b].X;
		}
		return points[a].Y < points[b].Y;
	};
	
	auto cmpByY = [](const int a, const int b) {
		if (points[a].Y != points[b].Y) {
			return points[a].Y < points[b].Y;
		}
		return points[a].X < points[b].X;
	};
	
	std::sort(order.begin(), order.end(), cmpByX);
	addEdges(order);
	std::sort(order.begin(), order.end(), cmpByY);
	addEdges(order);
	
	dijkstra(n - 1);
	printf("%d\n", result[0]);
	return 0;
}