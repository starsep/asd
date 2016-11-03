#include <cstdio>
#include <algorithm>

typedef long long LL;

const int MAX = 1e6 + 15;
const int INV = -1;

int n;
int a[MAX];
LL result[MAX];

void input() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
}

int find_next(bool odd, int start) {
	for(int j = start - 1; j >= 0; j--) {
		if(a[j] % 2 == odd) {
			return j;
		}
	}
	return INV;
}

void preprocess() {
	LL sum = 0;
	int ourOdd = INV;
	int ourEven = INV;
	int odd = INV;
	int even = INV;
	for(int i = 0; i < n; i++) {
		if(a[i] % 2 == 0) {
			even = i;
		}
		else {
			odd = i;
		}
	}
	for(int i = n - 1; i >= 0; i--) {
		sum += a[i];
		if(odd == i) {
			odd = find_next(true, odd);
		}
		if(even == i) {
			even = find_next(false, even);
		}
		if(a[i] % 2 == 1) {
			ourOdd = i;
		}
		else {
			ourEven = i;
		}
		//fprintf(stderr, "%d %d %d %d\n", ourEven, ourOdd, even, odd); 
		if(sum % 2 == 1) {
			result[n - i] = sum;
		}
		else {
			result[n - i] = INV;
			if(ourOdd != INV && even != INV) {
				result[n - i] = sum - a[ourOdd] + a[even];
			}
			if(ourEven != INV && odd != INV) {
				result[n - i] = std::max(result[n - i], sum - a[ourEven] + a[odd]);
			}
		}
	}
}

int main() {
	input();
	preprocess();
	int m, x;
	scanf("%d", &m);
	while(m--) {
		scanf("%d", &x);
		printf("%lld\n", result[x]);
	}
	return 0;
}
