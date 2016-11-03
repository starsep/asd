#include <cstdio>
#include <algorithm>

using LL = long long;

const int MAX = 3e5 + 16;
const LL P = 37;
const LL MOD = 1e9 + 7;

int n, m;
char s[MAX];
LL hash[MAX];
LL pot[MAX];

void input() {
	scanf("%d%d%s", &n, &m, s);
}

void preprocess() {
	for (int i = 0; i < n; i++) {
		s[i] -= ('a' - 1);
	}
	pot[0] = 1;
	for (int i = 1; i < n; i++) {
		pot[i] = pot[i - 1] * P % MOD;
	}
	hash[0] = s[0];
	for (int i = 1; i < n; i++) {
		hash[i] = (hash[i - 1] * P + s[i]) % MOD;
	}
}

int hash_p(int begin, int end) {
	if (begin == 0) {
		return hash[end];
	}
	return (MOD + (hash[end] - hash[begin - 1] * pot[end - begin + 1]) % MOD) % MOD;
}


char query(int a, int b, int c, int d) {
	int size1 = b - a + 1;
	int size2 = d - c + 1;
	int size = std::min(size1, size2);
	int begin = 0, end = size - 1, best = 0;
	while (begin <= end) {
		int med = (begin + end) / 2;
		int hash1 = hash_p(a, a + med);
		int hash2 = hash_p(c, c + med);
		if (hash1 == hash2) {
			begin = med + 1;
			best = med + 1;
		}
		else {
			end = med - 1;
		}
	}
	if (best == size) {
		if (size1 == size2) {
			return '=';
		}
		return size1 < size2 ? '<' : '>';
	}
	return s[a + best] < s[c + best] ? '<' : '>';
}

void solve() {
	int a, b, c, d;
	while (m--) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		a--; b--; c--; d--;
		printf("%c\n", query(a, b, c, d));
	}
}

int main() {
	input();
	preprocess();
	solve();
}