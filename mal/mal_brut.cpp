//brucik, aby sprawdzić czy rozumiem treść :P

#include <cstdio>
#include <vector>
#include <cassert>

#define scanf(args...) scanf(args) ? : 0

const int MAX = 1e6 + 15;

int n;

class Tree {
	private:
		int x;
		std::vector<int> t;
	public:
		Tree() : Tree(n) {
		}
		Tree(const int N) {
			x = 1;
			while(x < N) {
				x *= 2;
			}
			t.resize(2 * x);
			x--;
		}
		void insert(int a, const int w) {
			a += x;
			t[a] = w;
			while(a > 0) {
				a /= 2;
				t[a] = t[2 * a] + t[2 * a + 1]; 
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
				result = result + t[b];
			}
			while(a / 2 != b / 2) {
				if(a % 2 == 0) {
					result = result + t[a + 1];
				}
				if(b % 2 == 1) {
					result = result + t[b - 1];
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
	int m;
	scanf("%d%d", &n, &m);
	int a, b;
	char c;
	Tree tree;
	while(m--) {
		scanf("%d %d %c\n", &a, &b, &c);
		switch(c) {
			case 'B':
				for(int i = a; i <= b; i++) {
					tree.insert(i, 1);
				}
				break;
			case 'C':
				for(int i = a; i <= b; i++) {
					tree.insert(i, 0);
				}
				break;
			default:
				assert(false);
				break;
		}
		printf("%d\n", tree.root());
	}
}
