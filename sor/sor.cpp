#include <cstdio>

const int MOD = 1e9;
const int MAX = 1e3 + 12;

int n;
int a[MAX];
int left_result[MAX][MAX];
int right_result[MAX][MAX];

void input() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
}

void solve() {
	for(int i = 0; i < n; i++)
		left_result[i][i] = right_result[i][i] = 1;
	for(int x = 1; x < n; x++) {
		for(int i = 0; i < n - x; i++) {
			right_result[i][i + x] =
				(
					left_result[i][i + x - 1] * (a[i] < a[i + x])
						+
					right_result[i][i + x - 1] * (a[i + x - 1] < a[i + x]) * (x - 1 != 0)
				) % MOD;
			left_result[i][i + x] =
				(
					left_result[i + 1][i + x] * (a[i] < a[i + 1])
				+
					right_result[i + 1][i + x] * (a[i] < a[i + x]) * (x != 1)
				) % MOD;
		}
	}
}

void debug(int result[][MAX]) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			printf("%d%c", result[i][j], (j == n - 1) ? '\n' : ' ');
	printf("\n");
}

void output() {
	if(n < 2) {
		printf("1\n");
		return;
	}
	printf("%d\n", (left_result[0][n - 1] + right_result[0][n - 1]) % MOD);
}

int main() {
	input();
	solve();
	//debug(left_result);
	//debug(right_result);
	output();
}
