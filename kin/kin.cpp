#include <cstdio>
#include <vector>

#define scanf(args...) scanf(args) ? : 0

const int MOD = 1e9;
const int MAX = 2e4 + 15;

int n;

class tree {
	private:
		int x;
		std::vector<int> t;
	public:
		tree() : tree(n) {
		}
		tree(const int N) {
			x = 1;
			while(x < N) {
				x *= 2;
			}
			t.resize(2 * x);
			x--;
		}
		void insert(int a, const int w) {
			a += x;
			t[a] = (t[a] + w) % MOD;
			while(a > 0) {
				a /= 2;
				t[a] = (t[2 * a] + t[2 * a + 1]) % MOD; 
			}
		}
		int sum(int a, int b) {
			if(b < a) {
				return 0;
			}
			a += x;
			b += x;
			int result = t[a];
			if(a != b) {
				result = (result + t[b]) % MOD;
			}
			while(a / 2 != b / 2) {
				if(a % 2 == 0) {
					result = (result + t[a + 1]) % MOD;
				}
				if(b % 2 == 1) {
					result = (result + t[b - 1]) % MOD;
				}
				a /= 2;
				b /= 2;
			}
			return result;
		}
		int root() {
			return t[1];
		}
};

int main() {
	int a, k;
	scanf("%d%d", &n, &k);
	tree trees[k];
	for(int i = 0; i < n; i++) {
		scanf("%d", &a);
		trees[0].insert(a, 1);
		for(int j = 0; j < k - 1; j++) {
			trees[j + 1].insert(a, trees[j].sum(a + 1, n));
		}
	}
	printf("%d\n", trees[k - 1].root());
}
