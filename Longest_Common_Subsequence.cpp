#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
void DPLCS(char* X, char* Y, int m, int n)
{
	int L[m + 2][n + 2];

	/* Following steps build L[m+1][n+1] in bottom up
	fashion. Note that L[i][j] contains length of LCS of
	X[0..i-1] and Y[0..j-1] */
	for (int i = 0; i <= m+1; i++) {
		for (int j = 0; j <= n+1; j++) {
			if (i == 0 || j == 0)
				L[i][j] = 0;
			else if (X[i - 1] == Y[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;
			else
				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}
		
	printf("\n\nDynamic Programming: \n");
	for (int i = 0; i <= m+1; i++){
		for (int j = 0; j <= n; j++){
			cout<<L[i][j]<<" ";
		}
			cout<<"\n";
	}
		
	int index = L[m+1][n+1];
	char lcs[index];

	// Start from the right-most-bottom-most corner and
	// one by one store characters in lcs[]
	int i = m+1, j = n+1;
	while (i > 0 && j > 0) {
		// If current character in X[] and Y are same, then
		// current character is part of LCS
		if (X[i - 1] == Y[j - 1]) {
			lcs[index - 1]
				= X[i - 1]; // Put current character in result
			i--;
			j--;
			index--; // reduce values of i, j and index
		}

		// If not same, then find the larger of two and
		// go in the direction of larger value
		else if (L[i - 1][j] > L[i][j - 1])
			i--;
		else
			j--;
	}
	cout<<"\n";
	
	// Print the lcs
	cout << "LCS of " << X << " and " << Y << " is " << lcs;
}

//用 Greedy會有誤 
void greedyLCS(char* X, char* Y,int m,int n){
		char ans[max(m,n)];
		int start = 0;
		int index = 0;
		int j;
		//陣列 X[0]開始找 Y 中有沒有相符合的，有符合即選取 
		for (int i=0; i<m; i++){
			if(start==n) break;//當 Y已經選到最後一個元素(最後一個元素為Y[n-1]) 
			j=start;
			while(X[i]!=Y[j]){
				j++;
				if(X[i]==Y[j]) {
					ans[index]=X[i];	
					start=j+1;//Y從選取的下一格繼續往下找 
					index++;
				}
			}
		}
		printf("Greedy: \n");
		for(int i=0;i<index;i++){
			printf("%c ",ans[i]);
		}
}
	
/* Driver program to test above function */
int main()
{
	char X[] = "CAACABCACA";
	char Y[] = "ACACACBAACCAA";
	int m = strlen(X)-1;
	int n = strlen(Y)-1;
	greedyLCS(X, Y, m, n);
	DPLCS(X, Y, m, n);
	return 0;
}

