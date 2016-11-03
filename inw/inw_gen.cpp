#include <cstdio>
#include <algorithm>
#include <vector>

int main() {
	int n;
	scanf("%d", &n);
	std::vector<int> v;
	for (int i = 1; i <= n; i++) {
		v.push_back(i);
	}
	srand(time(nullptr));
	int times = int(sqrt(n));
	for (int i = 0; i < times; i++) {
		int a = rand() % n;
		int b = rand() % n;
		std::swap(v[a], v[b]);
	}
	
	printf("%d\n", n);
	for (int x : v) {
		printf("%d ", x);
	}
	printf("\n");
	return 0;
}