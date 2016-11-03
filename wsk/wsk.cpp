#include <cstdio>
#include <algorithm>
#include <vector>

#define scanf(args...) scanf(args) ? : 0

template<typename T>
class SegmentTree {
private:
	int x;
	std::vector <T> nodes;
public:
	SegmentTree(const int N) {
		x = 1;
		while (x < N) {
			x *= 2;
		}
		nodes.resize(2 * x);
		x--;
	}

	void setLeaf(const int n, const T &value) {
		nodes[n + x] = value;
	}

	void insert(const int n, const T &value) {
		setLeaf(n, value);
		int index = n + x;
		while (index > 0) {
			index /= 2;
			nodes[index] = nodes[2 * index] + nodes[2 * index + 1];
		}
	}

	void build() {
		for (int i = x; i >= 1; i--) {
			nodes[i] = nodes[2 * i] + nodes[2 * i + 1];
		}
	}

	T query(int a, int b) const {
		a += x;
		b += x;
		T leftResult = nodes[a];
		if (a == b) {
			return leftResult;
		}
		T rightResult = nodes[b];
		while (a / 2 != b / 2) {
			if (a % 2 == 0) {
				leftResult += nodes[a + 1];
			}
			if (b % 2 == 1) {
				rightResult = nodes[b - 1] + rightResult;
			}
			a /= 2;
			b /= 2;
		}
		return leftResult + rightResult;
	}

	int statisticOrder(int k) const {
		int index = 1;
		if (nodes[index] < k) {
			return x + 1;
		}
		while (index <= x) {
			index *= 2;
			if (nodes[index] >= k) {
				continue;
			}
			k -= nodes[index];
			index++;
		}
		return index - x;
	}

	void clear() {
		nodes.clear();
	}
};

enum class Rotation : int8_t {
	NoRotation,
	Right,
	Backwards,
	Left
};

Rotation rotFromChar(char c) {
	switch (c) {
		case 'L':
			return Rotation::Left;
		case 'R':
			return Rotation::Right;
		case 'U':
			return Rotation::Backwards;
		default:
			return Rotation::NoRotation;
	}
}

Rotation rotationComposition(Rotation first, Rotation second) {
	return static_cast<Rotation>((static_cast<int>(first) + static_cast<int>(second)) % 4);
}

class Hint {
private:
	int dx;
	int dy;
	Rotation rotation;

	void makeMove(const Hint &hint) {
		switch (rotation) {
			case Rotation::NoRotation:
				dx += hint.dx;
				dy += hint.dy;
				break;
			case Rotation::Backwards:
				dx -= hint.dx;
				dy -= hint.dy;
				break;
			case Rotation::Left:
				dx -= hint.dy;
				dy += hint.dx;
				break;
			case Rotation::Right:
				dx += hint.dy;
				dy -= hint.dx;
				break;
		}
	}

public:
	Hint() : Hint(0, 0, Rotation::NoRotation) {
	}

	Hint(const int DX, const int DY, const Rotation R) :
		dx(DX), dy(DY), rotation(R) {
	}

	Hint(const Hint &hint) :
		Hint(hint.dx, hint.dy, hint.rotation) {
	}

	void setHint(const Rotation R, const int DX, const int DY) {
		rotation = R;
		dx = DX;
		dy = DY;
	}

	const Hint &operator+=(const Hint &hint) {
		makeMove(hint);
		rotation = rotationComposition(rotation, hint.rotation);
		return *this;
	}

	const Hint operator+(const Hint &hint) const {
		return Hint(*this) += hint;
	}

	std::pair<int, int> getDs() const {
		return std::make_pair(dx, dy);
	}

	static const Hint &empty() {
		static Hint singleton;
		return singleton;
	}
};

int n;
std::vector <std::pair<int, Hint>> data;

void input() {
	scanf("%d", &n);
	data.resize(n);
	int d;
	char c;
	for (auto &x : data) {
		scanf("%d %c %d", &x.first, &c, &d);
		Rotation r = rotFromChar(c);
		int dx = 0, dy = 0;
		switch (r) {
			case Rotation::Left:
				dx = -d;
				break;
			case Rotation::Right:
				dx = d;
				break;
			case Rotation::Backwards:
				dy = -d;
				break;
			case Rotation::NoRotation:
				exit(1);
				break;
		}
		x.second.setHint(r, dx, dy);
	}
}

void solve() {
	SegmentTree<int> countTree(n);
	for (int i = 1; i <= n; i++) {
		countTree.setLeaf(i, 1);
	}
	countTree.build();

	std::vector<int> endOrder(n);
	std::vector<int> inverseEndOrder(n);
	for (int i = n - 1; i >= 0; i--) {
		int index = countTree.statisticOrder(data[i].first);
		countTree.insert(index, 0);
		endOrder[i] = index - 1;
		inverseEndOrder[index - 1] = i;
	}
	countTree.clear();

	SegmentTree<Hint> hintTree(n);
	for (int i = 0; i < n; i++) {
		hintTree.setLeaf(i + 1, data[inverseEndOrder[i]].second);
	}
	hintTree.build();

	std::vector <std::pair<int, int>> results(n);

	for (int i = n - 1; i >= 0; i--) {
		int index = endOrder[i] + 1;
		Hint pref = hintTree.query(1, index);
		results[i] = pref.getDs();
		hintTree.insert(index, Hint::empty());
	}
	for (auto &x : results) {
		printf("%d %d\n", x.first, x.second);
	}

}

int main() {
	input();
	solve();
}
