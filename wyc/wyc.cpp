//Moje rozwiązania tego zadania jakiś czas temu straciły czytelność
//W razie czytania kodu, proszę czytać http://szkopul.edu.pl/c/asdlab-2015/s/215875/
//Późniejsze edycje to już tylko brzydkie, brudne tricki

#include <cstdio>
#include <cstring>

#define scanf(args...) scanf(args) ? : 0

const int MAX = 1e3 + 15;
const int INF = 1e9 + 15;

int n, k;

int taxiCost[MAX],
	planeCost[MAX],
	trainCost[MAX];
	
int dp[2][MAX][2 * MAX];

int q = 0;
#define prev (dp[(q&1)])
#define next (dp[!(q&1)])

inline void input() {
	scanf("%d%d", &n, &k);
	scanf("%d", &taxiCost[0]);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d%d", &trainCost[i], &taxiCost[i], &planeCost[i]);
	}
	
}

inline void swapTablesAndSetInfinities() {
	q++;
	for(int i = 0; i <= n / 2; i++) {
		for(int j = 0; j <= k; j++) {
			memset((char *)(next[i] + 2 * j), 120, 8);
		}
	}
}

inline int min(int A, int B) {
	if(A < B) {
		return A;
	}
	return B;
}

//0 - lotnisko, 1 - dworzec kolejowy

inline void travelByPlane(const int T) {
	register int K = min(k, T + 1);
	register int N = min(n / 2, T + 1);
	
	for(int i = 0; i <= N; i++) {
		next[i][0] = prev[i][0] + planeCost[T];
		for(int j = 1; j <= K; j++) {
			next[i][2 * j] = min(
				//skończyliśmy w poprzednim mieście na lotnisku
				prev[i][2 * j] + planeCost[T],
				//skończyliśmy w poprzednim mieście na dworcu
				prev[i][2 * (j - 1) + 1] + taxiCost[T - 1] + planeCost[T]);
		}
	}
}

inline void travelByTrain(const int T) {
	register int K = min(k, T + 1);
	register int N = min(n / 2, T + 1);
	
	for(int i = 1; i <= N; i++) {
		next[i][1] = min(next[i][1], prev[i - 1][1] + trainCost[T]);
		for(int j = 1; j <= K; j++) {
			next[i][2 * j + 1] = min(
			//skończyliśmy w poprzednim mieście na lotnisku
				prev[i - 1][2 * (j - 1)] + taxiCost[T - 1] + trainCost[T],
				//skończyliśmy w poprzednim mieście na dworcu
				prev[i - 1][2 * j + 1] + trainCost[T]);
		}
	}
}

//teraz podróżujemy do miasta T
inline void travel(const int T) {
	travelByPlane(T);
	travelByTrain(T);
}

void debug() {
	return;
	for(int i = 0; i <= n / 2; i++) {
		for(int j = 0; j < i; j++) {
			printf("-");
		}
		for(int j = 0; j < n / 2 - i; j++) {
			printf(" ");
		}
		for(int j = 0; j <= k; j++) {
			printf("%d %d | ", prev[i][2 * j], prev[i][2 * j + 1]);  
		}
		printf("\n");
	}
	printf("\n");
}

void init() {
	for(int i = 0; i <= n / 2; i++) {
		for(int j = 0; j <= k; j++) {
			memset((char *)(next[i] + 2 * j), 120, 8);
		}
	}
	next[0][1] = 0;
}

void solve() {
	init();
	for(int i = 1; i <= n; i++) {
		swapTablesAndSetInfinities();
		debug();
		travel(i);
	}
	int result = INF;
	for(int i = 1; i <= k; i++) {
		result = min(result, next[n / 2][2 * i]);
		if(i < k) {
			result = min(result, next[n / 2][2 * i + 1] + taxiCost[n]);
		}
	}
	printf("%d\n", result);
	
}

int main() {
	input();
	solve();
}
