#include <cstdio>
#include <algorithm>
#include <vector>
const int MAX = 2e5 + 16;

int n;
int p[MAX];
std::vector<int> G[MAX];
std::vector<int> inv[MAX];
bool visited[MAX];

int P;
int post[MAX];

int SS;
int SSS[MAX];
int sum[MAX];
int result[MAX];
std::vector<int> SSG[MAX];
int in_deg[MAX];

std::vector<int> queue;

void input() {
	int a, b, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
	}
	while (m--) {
		scanf("%d%d", &a, &b);
		a--, b--;
		G[a].push_back(b);
		inv[b].push_back(a);
	}
}


void dfs1(int v) {
	visited[v] = true;
	for (int x : G[v]) {
		if (!visited[x]) {
			dfs1(x);
		}
	}
	post[P++] = v;
}

void dfs2(int v) {
	visited[v] = true;
	SSS[v] = SS;
	sum[SS] += p[v];
	for (int x : inv[v]) {
		if (!visited[x]) {
			dfs2(x);
		}
	}
}

void solve() {
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			dfs1(i);
		}
	}
	for (int i = 0; i < n; i++) {
		visited[i] = false;
	}
	for (int i = n - 1; i >= 0; i--) {
		if (!visited[post[i]]) {
			dfs2(post[i]);
			SS++;
		}
	}
	for (int v = 0; v < n; v++) {
		for (int u : G[v]) {
			if (SSS[u] != SSS[v]) {
				SSG[SSS[u]].push_back(SSS[v]);
			}
		} 
	}
	for (int i = 0; i < SS; i++) {
		result[i] = sum[i];
		std::sort(SSG[i].begin(), SSG[i].end());
		auto it = std::unique(SSG[i].begin(), SSG[i].end());
		SSG[i].resize(std::distance(SSG[i].begin(), it));
		for (int x : SSG[i]) {
			in_deg[x]++;
			//printf("%d -> %d\n", i, x);
		}
	}
	for (int i = 0; i < SS; i++) {
		if (in_deg[i] == 0) {
			queue.push_back(i);
		}
	}
	while (!queue.empty()) {
		int v = queue.back();
		queue.pop_back();
		for (int u : SSG[v]) {
			result[u] = std::max(sum[u] + result[v], result[u]);
			in_deg[u]--;
			if (in_deg[u] == 0) {
				queue.push_back(u);
			}
		}
	}
	int res = 0;
	for (int i = 0; i < SS; i++) {
		res = std::max(res, result[i]);
	}
	printf("%d\n", res);
}

int main() {
	input();
	solve();
	return 0;
}