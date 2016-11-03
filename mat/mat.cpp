#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAX = 1e6 + 15;
const char STAR = '*';

int n;
char s[MAX];

int main() {
	scanf("%s", s);
	n = strlen(s);
	int result = 1;
	char last = STAR;
	int lastN = 0;
	for(int i = 0; i < n; i++) {
		if(s[i] != STAR) {
			if(last != STAR && last != s[i])
				result = std::max(result, n - (i - lastN - 1));
			last = s[i];
			lastN = i;
		}
	}
	printf("%d\n", result);
}
