//made by Emil Hotkowski
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <climits>
#include <cstring>
#include <stack>
#define FOR(i,p,k) for(int i = (p);i<(k);i++)
typedef long long int LL;
using namespace std;

int Index[100007];
int Numer[100007];
char Ruch[100007];
int Dystans[100007];

int n;

void licz(int d) {
	int nowy = Numer[d];
	
	FOR(i,0,n) {
		if(Index[i] >= nowy) {
			Index[i]++;
		}
	}
	Index[d] = nowy;
	int gT = 2, gX = 0, gY = 0;
	FOR(kto,1,nowy+1) {
		FOR(i,0,n) {
			if(Index[i] != kto)
				continue;
			//cout<<"ide w " <<Ruch[i]<<" "<<Dystans[i]<<"\n";
			if(gT == 2 && Ruch[i] == 'L') {
				gT = 1;
				gX -= Dystans[i];
			} else if (gT == 2 && Ruch[i] == 'R') {
				gT = 3;
				gX += Dystans[i];
			} else if (gT == 2 && Ruch[i] == 'U') {
				gT = 4;
				gY -= Dystans[i];
			} 

			else if (gT == 4 && Ruch[i] == 'R') {
				gT = 1;
				gX -= Dystans[i];
			} else if (gT == 4 && Ruch[i] == 'L') {
				gT = 3;
				gX += Dystans[i];
			} else if (gT == 4 && Ruch[i] == 'U') {
				gT = 2;
				gY += Dystans[i];
			} 

			else if(gT == 3 && Ruch[i] == 'L') {
				gT = 2;
				gY += Dystans[i];
			} else if (gT == 3 && Ruch[i] == 'R') {
				gT = 4;
				gY -= Dystans[i];
			} else if (gT == 3 && Ruch[i] == 'U') {
				gT = 1;
				gX -= Dystans[i];
			} 

			else if (gT == 1 && Ruch[i] == 'R') {
				gT = 2;
				gY += Dystans[i];
			} else if (gT == 1 && Ruch[i] == 'L') {
				gT = 4;
				gY -= Dystans[i];
			} else if (gT == 1 && Ruch[i] == 'U') {
				gT = 3;
				gX += Dystans[i];
			} 
		}
	}
	//cout<<"Zwrot : "<<gT<<"\n";
	cout<<gX<<" "<<gY<<"\n";
}	

void dane() {
	cin>>n;
	FOR(i,0,n) {
		Index[i] = 1000000;
	}	
	FOR(i,0,n) {
		cin>>Numer[i]>>Ruch[i]>>Dystans[i];
		licz(i);
	}
}

int main() {
	dane();
	return 0;
}
