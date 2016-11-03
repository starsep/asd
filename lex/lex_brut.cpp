//brut
#include <cstdio>
#include <algorithm>

const int MAX = 3e5 + 16;

int n, m;
char s[MAX];

void input() {
	scanf("%d%d%s", &n, &m, s);
}

char query(int a, int b, int c, int d) {
	int size1 = b - a + 1;
	int size2 = d - c + 1;
	int size = std::min(size1, size2);
	int best;
	for (best = 0; best <= size;) {
		if (s[a + best] == s[c + best]) {
			best++;
		}
		else {
			break;
		}
	}
	if (best == size) {
		if (size1 == size2) {
			return '=';
		}
		return "><"[size1 < size2];
	}
	return "><"[s[a + best] < s[c + best]];
}

void solve() {
	int a, b, c, d;
	while (m--) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		a--, b--, c--, d--;
		printf("%c\n", query(a, b, c, d));
	}
}

int main() {
	input();
	solve();
}