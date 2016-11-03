#include <cstdio>
#include <bits/stdc++.h>

#define scanf(args...) scanf(args) ? : 0

const int MAXN = 5000;
const int NO_NODE = -2;
int left[MAXN], right[MAXN], parent[MAXN], dist[MAXN][MAXN], maxDist[MAXN];

void bfs(const int K) {
	std::queue<int> q;
	q.push(K);
	dist[K][K] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		auto check = [K, v](std::queue<int> &qq, int *arr) {
			if (arr[v] != NO_NODE) {
				if (dist[K][v] + 1 < dist[K][arr[v]]) {
					dist[K][arr[v]] = dist[K][v] + 1;
					qq.push(arr[v]);
				}
			}
		};
		check(q, left);
		check(q, right);
		check(q, parent);
	}
}

int main() {
	int n, a, b;
	scanf("%d", &n);
	std::fill(left, left + n, NO_NODE);
	std::fill(right, right + n, NO_NODE);
	std::fill(parent, parent + n, NO_NODE);
	std::fill(maxDist, maxDist + n, 0);
	for (int i = 0; i < n; i++) {
		std::fill(dist[i], dist[i] + n, MAXN);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		a--;
		b--;
		left[i] = a;
		right[i] = b;
		if (a != NO_NODE) {
			parent[a] = i;
		}
		if (b != NO_NODE) {
			parent[b] = i;
		}
	}
	for (int i = 0; i < n; i++) {
		bfs(i);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//printf("%d%c", dist[i][j], j == n - 1 ? '\n' : ' ');
			maxDist[i] = std::max(maxDist[i], dist[i][j]);
		}
	}
	int m;
	scanf("%d", &m);
	std::vector <std::pair<int, int>> queries;
	while (m--) {
		scanf("%d%d", &a, &b);
		queries.push_back(std::make_pair(a, b));
	}
	for (int i = 0; i < (int) queries.size(); i++) {
		a = queries[i].first;
		a--;
		b = queries[i].second;
		int ans;
		scanf("%d", &ans);
		ans--;
		if (ans != NO_NODE) {
			if (!(ans >= 0 && ans < n)) {
				fprintf(stderr, "Blad w linii %d, zapytanie: %d %d\n", i + 1, a + 1, b);
				fprintf(stderr, "Bledna liczba %d\n", ans + 1);
				exit(1);
			}
			if (dist[a][ans] != b) {
				fprintf(stderr, "Blad w linii %d, zapytanie: %d %d\n", i + 1, a + 1, b);
				fprintf(stderr, "Bledna odleglosc: pomiedzy %d i %d odleglosc wynosi %d, szukano %d\n", a + 1, ans + 1,
						dist[a][ans], b);
				exit(2);
			}
		}
		else if (maxDist[a] >= b) {
			fprintf(stderr, "Blad w linii %d, zapytanie: %d %d\n", i + 1, a + 1, b);
			fprintf(stderr, "Wypisano -1 kiedy istniala odpowiedz: maxDist[%d] = %d, szukano %d\n", a + 1, maxDist[a],
					b);
			exit(3);
		}
	}
	return 0;
}