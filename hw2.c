#include <stdio.h>

int combi_rec(int n, int k){
	if(k == 0 || k == n)
		return 1;
	else
		return combi_rec(n-1, k-1) + combi_rec(n-1, k);
}

int combi_dyn(int n, int j){
	int arr[n+1][j+1];
	for (int i = 0; i < n+1; i++){
		for (int k = 0; k < j+1; k++){
			if (i == k || k == 0)
				arr[i][k] = 1;
			else
				arr[i][k] = arr[i-1][k-1] + arr[i-1][k];
		}

	}


	return arr[n][j];
}

int main(void){
	int n, k;
	char choose;
	printf("Choose either Recursive manner or Dynamic Programming manner: ");
	scanf("%c", &choose);
	
	printf("Enter the value for n & k: ");
	scanf("%d %d", &n, &k);

	int result;
	if(choose == 'r')
		result = combi_rec(n, k);
	else if(choose == 'd')
		result = combi_dyn(n, k);
	else{
		printf("You entered wrong input! Exit the program.\n");
		return -1;
	}

	printf("result: %d\n", result);
	return 0;
}
