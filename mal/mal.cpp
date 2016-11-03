#include <cstdio>
#include <vector>

#define scanf(args...) scanf(args) ? 0 : 0

class Tree {
private:
	int x;
	enum SubTreeState {
		BlackSubTree,
		WhiteSubTree,
		UnknownSubTree
	};

	class Node : std::pair<int, SubTreeState> {
	public:
		int &whites() {
			return first;
		}

		SubTreeState &state() {
			return second;
		}

		void set(const int sum) {
			whites() = sum;
			state() = sum ? WhiteSubTree : BlackSubTree;
		}
	};

	std::vector <Node> nodes;

	int a, b;

	bool intersection(int A, int B) {
		int L = std::max(A, a);
		int R = std::min(B, b);
		return L <= R;
	}

	void update(const int index, const int begin, const int end, const bool white) {
		if (begin == end) {
			nodes[index].set(white);
			return;
		}
		const int length = (end - begin + 1);
		if (nodes[index].state() != UnknownSubTree) {
			bool nodeState = nodes[index].state();
			nodes[2 * index].set(nodeState * length / 2);
			nodes[2 * index + 1].set(nodeState * length / 2);
		}
		if (a <= begin && end <= b) {
			nodes[index].set(white * length);
			return;
		}
		const int middle = begin + length / 2;
		if (intersection(begin, middle - 1)) {
			update(2 * index, begin, middle - 1, white);
		}
		if (intersection(middle, end)) {
			update(2 * index + 1, middle, end, white);
		}
		nodes[index].whites() = nodes[2 * index].whites() + nodes[2 * index + 1].whites();
		if (nodes[2 * index].state() == nodes[2 * index + 1].state()) {
			nodes[index].state() = nodes[2 * index].state();
		}
		else {
			nodes[index].state() = UnknownSubTree;
		}
	}

public:
	Tree(const int N) {
		x = 1;
		while (x < N) {
			x *= 2;
		}
		nodes.resize(2 * x);
		x--;
	}

	void insert(const int A, const int B, const bool white) {
		a = A;
		b = B;
		update(1, 1, x + 1, white);
	}

	int root() {
		return nodes[1].whites();
	}
};

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int a, b;
	char c;
	Tree tree(n);
	while (m--) {
		scanf("%d %d %c\n", &a, &b, &c);
		tree.insert(a, b, c == 'B');
		printf("%d\n", tree.root());
	}
}