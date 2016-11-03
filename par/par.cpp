#pragma GCC optimize ("O3")
#include <cstdio>
#include <bits/stdc++.h>

#define scanf(args...) scanf(args) ? : 0

typedef std::pair<int, int> DistNode;

struct Node {
	constexpr static const DistNode NO_DIST_NODE = std::make_pair(-1, 0);
	static const int NO_NODE = -2;
	static const int LOG2_MAXN = 20;
	int left;
	int right;
	int height;
	int up[LOG2_MAXN];
	DistNode leftDist;
	DistNode rightDist;
	DistNode upDist;
	DistNode maxDist;

	Node() {
		left = right = NO_NODE;
		leftDist = rightDist = upDist = maxDist = NO_DIST_NODE;
		std::fill(up, up + LOG2_MAXN, NO_NODE);
	}

};

class Tree {
private:
	int n;
	std::vector <Node> nodes;

	int findRoot() {
		auto rootIt = std::find_if(nodes.begin(), nodes.end(), [](const Node &node) {
			return node.up[0] == Node::NO_NODE;
		});
		assert(rootIt != nodes.end());
		return static_cast<int>(rootIt - nodes.begin());
	}

	void setHeight(int v, int h) {
		if (v < 0) {
			return;
		}
		nodes[v].height = h;
		if (nodes[v].left != Node::NO_NODE) {
			setHeight(nodes[v].left, h + 1);
		}
		if (nodes[v].right != Node::NO_NODE) {
			setHeight(nodes[v].right, h + 1);
		}
	}

	void setUp(int v, int index) {
		if (v < 0) {
			return;
		}
		if (nodes[v].up[index - 1] != Node::NO_NODE) {
			nodes[v].up[index] = nodes[nodes[v].up[index - 1]].up[index - 1];
		}
		if (nodes[v].left != Node::NO_NODE) {
			setUp(nodes[v].left, index);
		}
		if (nodes[v].right != Node::NO_NODE) {
			setUp(nodes[v].right, index);
		}
	}

	void setLeftRightDistNodes(int v) {
		if (v < 0) {
			return;
		}
		int leftSon = nodes[v].left;
		if (leftSon != Node::NO_NODE) {
			setLeftRightDistNodes(leftSon);
			nodes[v].leftDist = nodes[leftSon].maxDist;
			nodes[v].leftDist.first++;
		}
		else {
			nodes[v].leftDist = {0, v};
		}
		int rightSon = nodes[v].right;
		if (rightSon != Node::NO_NODE) {
			setLeftRightDistNodes(rightSon);
			nodes[v].rightDist = nodes[rightSon].maxDist;
			nodes[v].rightDist.first++;
		}
		else {
			nodes[v].rightDist = {0, v};
		}
		nodes[v].maxDist = std::max(nodes[v].leftDist, nodes[v].rightDist);
		/*printf("Setting left/rightDistNodes for %d\n", v + 1);
		printf("Left: %d (dist = %d) Right: %d (dist = %d) Max: %d (dist = %d)\n",
			   nodes[v].leftDist.second, nodes[v].leftDist.first,
			   nodes[v].rightDist.second, nodes[v].rightDist.first,
			   nodes[v].maxDist.second, nodes[v].maxDist.first);*/
	}

	void setUpDistNodes(int v) {
		if (v < 0) {
			return;
		}
		int parent = nodes[v].up[0];
		if (parent != Node::NO_NODE) {
			nodes[v].upDist = nodes[parent].upDist;
			nodes[v].upDist.first++;
			if (nodes[parent].left == v) {
				DistNode upRightPath = nodes[parent].rightDist;
				upRightPath.first++;
				nodes[v].upDist = std::max(nodes[v].upDist, upRightPath);
			}
			else {
				DistNode upLeftPath = nodes[parent].leftDist;
				upLeftPath.first++;
				nodes[v].upDist = std::max(nodes[v].upDist, upLeftPath);
			}
		}
		else {
			nodes[v].upDist = {0, v};
		}
		nodes[v].maxDist = std::max(nodes[v].maxDist, nodes[v].upDist);
		if (nodes[v].left != Node::NO_NODE) {
			setUpDistNodes(nodes[v].left);
		}
		if (nodes[v].right != Node::NO_NODE) {
			setUpDistNodes(nodes[v].right);
		}
	}

	void setDistNodes(int v) {
		if (v < 0) {
			return;
		}
		setLeftRightDistNodes(v);
		setUpDistNodes(v);
	}

	int goUp(int x, int dist) {
		if (dist == 0) {
			return x;
		}
		int magic = dist & (-dist);
		dist -= magic;
		magic--;
		return goUp(nodes[x].up[__builtin_popcount(magic)], dist);
	}

	int query(int x, int dist) {
		//printf("Max from %d is %d (dst = %d)\n", x, nodes[x].maxDist.second, nodes[x].maxDist.first);
		if (dist > nodes[x].maxDist.first) {
			return Node::NO_NODE;
		}
		//printf("Height %d is %d\n", x, nodes[x].height);
		if (nodes[x].height >= dist) {
			return goUp(x, dist);
		}
		//printf("QUERY: %d %d\n", dist, nodes[x].maxDist.first);
		return goUp(nodes[x].maxDist.second, nodes[x].maxDist.first - dist);
	}

public:
	Tree() = default;

	void input() {
		scanf("%d", &n);
		nodes.resize(n);
		int a, b;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &a, &b);
			a--;
			b--;
			nodes[i].left = a;
			nodes[i].right = b;
			if (a != Node::NO_NODE) {
				nodes[a].up[0] = i;
			}
			if (b != Node::NO_NODE) {
				nodes[b].up[0] = i;
			}
		}
	}

	void preprocess() {
		int root = findRoot();
		setHeight(root, 0);
		for (int i = 1; i < Node::LOG2_MAXN; i++) {
			setUp(root, i);
		}
		setDistNodes(root);
	}

	void queries() {
		int m, x, dist;
		scanf("%d", &m);
		while (m--) {
			scanf("%d%d", &x, &dist);
			x--;
			printf("%d\n", query(x, dist) + 1);
		}
	}
};


int main() {
	Tree tree;
	tree.input();
	tree.preprocess();
	tree.queries();
	return 0;
}
