// made by Emil Hotkowski
#include <iostream>
#include <cstdlib>
#include <time.h>
#define FOR(i,p,k) for(int i = (p);i<(k);i++)
typedef long long int LL;
using namespace std;

int main() {
	srand( time( NULL ) );

	int n;
	n = 7;
	
	int maxi = 1;
	cout<<n<<"\n";
	FOR(i,0,n) {
		int numer = rand() % maxi + 1;
		int znak = rand() % 3;
		int odl = rand()% 30 + 10;
		
		char z;
		if(znak == 1)
			z = 'R';
		else if (znak == 0)
			z = 'L';
		else 
			z = 'U';
		
		cout<<numer<<" "<<z<<" "<<odl<<'\n';
		maxi++;
	}
}
