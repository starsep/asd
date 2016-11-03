#include <cstdio>
#include <bits/stdc++.h>

#define scanf(args...) scanf(args) ? : 0

const int MAXN = 5000;
const int NO_NODE = -2;

void usage(char **argv) {
	printf("Bad usage!\n");
	printf("Use: %s n m\n", argv[0]);
	exit(1);
}

int main(int argc, char **argv) {
	if (argc != 3) {
		usage(argv);
	}

	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	if (n <= 0 || m <= 0 || n > MAXN) {
		usage(argv);
	}

	srand(time(nullptr));

	int left[MAXN], right[MAXN], parent[MAXN], f[MAXN];

	std::fill(left, left + n, NO_NODE);
	std::fill(right, right + n, NO_NODE);
	std::fill(parent, parent + n, NO_NODE);
	for (int i = 0; i < n; i++) {
		f[i] = i;
	}
	std::random_shuffle(f, f + n);

	int currentNode = 0;
	for (int i = 1; i < n; i++) {
		int p = rand() % n;
		while (p--) {
			std::vector<int> options;
			options.push_back(currentNode);
			int tmp[3] = {left[currentNode], right[currentNode], parent[currentNode]};
			for (int x = 0; x < 3; x++) {
				if (tmp[x] != NO_NODE) {
					options.push_back(tmp[x]);
				}
			}
			currentNode = options[rand() % options.size()];
		}
		while (left[currentNode] != NO_NODE && right[currentNode] != NO_NODE) {
			currentNode = rand() % 2 ? left[currentNode] : right[currentNode];
		}
		parent[i] = currentNode;
		if (left[currentNode] == NO_NODE) {
			left[currentNode] = i;
		}
		else {
			right[currentNode] = i;
		}
	}

	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d %d\n", left[i] + 1, right[i] + 1);
	}

	printf("%d\n", m);
	while (m--) {
		printf("%d %d\n", rand() % n + 1, static_cast<int>(sqrt(n))); //static_cast<int>(sqrt(n))
	}
	return 0;
}