#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

#define X first
#define Y second


std::vector<int> P;
std::vector<int> input;
std::vector<int> rev;
std::vector<int> left;
std::vector<int> right;

std::vector<int> res;

std::vector<std::vector<int>> result;

int main() {
	int n;
	scanf("%d", &n);
	input.resize(n);
	rev.resize(n);
	left.resize(n);
	right.resize(n);
	P.resize(n);
	int x;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		x--;
		input[i] = x;
		rev[x] = i;
		left[i] = i;
	}
	
	int maxi = 0;
	for (int i = 0; i < n; i++) {
		maxi = std::max(maxi, rev[i]);
		right[rev[i]] = maxi;
	}
	
	auto intersection = [] (int a, int b, int c, int d) {
		int l = std::max(a, c);
		int r = std::min(b, d);
		return r - l + 1;
	};
	
	res.push_back(0);
	for (int i = 1; i < n; i++) {
		if (intersection(left[i - 1], right[i - 1], left[i], right[i]) > 0) {
			res.pop_back();
			left[i] = std::min(left[i - 1], left[i]);
			right[i] = std::max(right[i - 1], right[i]);
		}
		res.push_back(i);
	}
	
	int PP = 0;
	for (size_t i = 0; i < res.size(); i++) {
		int k = res[i];
		for (int j = left[k]; j <= right[k]; j++) {
			P[input[j]] = PP;
		}
		PP++;
	}
	
	result.resize(PP);
	for (int i = 0; i < n; i++) {
		result[P[i]].push_back(i + 1); 
	}
	
	printf("%d\n", int(result.size()));
	for (auto &v : result) {
		printf("%d ", int(v.size()));
		for (auto q : v) {
			printf("%d ", q);
		}
		printf("\n");
	}
}