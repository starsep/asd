#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAX = 1e5 + 15;
int n, m;
ll mask[MAX];
ll pot[MAX];

void solve() {
	scanf("%d%d", &n, &m);
	pot[0] = 1;
	for(int i = 1; i < m; i++) {
		pot[i] = pot[i - 1] * 2;
	}
	int q;
	for(int i = 0; i < m; i++) {
		for(int j = 1; j <= n; j++) {
			scanf("%d", &q);
			q--;
			if(j <= n / 2) {
				mask[q] |= pot[i];
			}
		}
	}
	std::sort(mask, mask + n);
	for(int i = 1; i < n; i++) {
		if(mask[i] == mask[i - 1]) {
			printf("NIE\n");
			return;
		}
	}
	printf("TAK\n");
}

int main() {
	solve();
}
