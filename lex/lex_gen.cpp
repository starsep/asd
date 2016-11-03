#include <cstdio>
#include <cstdlib>
#include <algorithm>

const int MAXN = 100;
const int MAXM = 100;
const int seed = 1337;
const int ALPHA = 2;

char s[MAXN + 1];

int main() {
	srand(seed);
	int n = rand() % MAXN;
	int m = rand() % MAXM;
	s[n] = '\0';
	for (int i = 0; i < n; i++) {
		s[i] = rand() % ALPHA + 'a';
	}
	printf("%d %d\n%s\n", n, m, s);
	while (m--) {
		int a = 1 + rand() % n;
		int b = 1 + rand() % n;
		if (a > b) {
			std::swap(a, b);
		}
		int c = 1 + rand() % n;
		int d = 1 + rand() % n;
		if (c > d) {
			std::swap(c, d);
		}
		printf("%d %d %d %d\n", a, b, c, d);
	}
}