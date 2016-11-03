#include <cstdio>
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> G;
std::vector<int> data;
std::vector<std::vector<int>> result;
std::vector<bool> visited;

void dfs(int v) {
	visited[v] = true;
	result.back().push_back(v);
	for (int x : G[v]) {
		if (!visited[x]) {
			dfs(x);
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	G.resize(n);
	data.resize(n);
	visited.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &data[i]);
		data[i]--;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (data[j] < data[i]) {
				G[data[i]].push_back(data[j]);
				G[data[j]].push_back(data[i]);
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			result.push_back(std::vector<int>());
			dfs(i);
		}
	}
	
	printf("%d\n", int(result.size()));
	for (auto &v : result) {
		printf("%d ", int(v.size()));
		std::sort(v.begin(), v.end());
		for (int p : v) {
			printf("%d ", p + 1);
		}
		printf("\n");
	}
	return 0;
}