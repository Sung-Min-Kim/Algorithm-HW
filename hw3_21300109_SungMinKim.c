#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define CLOCKS_PER_SEC 1000

/*
Comment: my program works for greedy and DP solution only.
*/


/* Item Structure */
typedef struct{
	int weight;
	int value;
	double value_per_weight; // value / weight
	int bound;
}Item;

/* B & B Structure */
typedef struct _Node{
	int benefit;
	int weight;
	int bound; // upper bound on the benefit we could achieve by expanding beyond this node
	struct _Node * yes; // left child means choosing that node
	struct _Node * no; // right child means not choosing that node
}Node;



/* Function Lists */
void greedy(int num_of_item, FILE* fp, Item *item, Item *sorted_item);
void dynamic(int num_of_item, FILE* fp, Item *item);
//void branch_bound(int num_of_item, FILE* fp, Item* item, Item* sorted_item);

void init_item(Item* item, int num_of_item);
double rounding(double x, int num);
void merge(Item list[], Item* sorted_item, int left, int mid, int right);
void merge_sort(Item list[], Item* sorted_item, int left, int right);

/* main */
int main(void){
	srand(time(NULL));

	FILE *fp = fopen("output.txt", "w");
	int i;

	fprintf(fp, "\t\t\t  \t|\t   Processing time in miliseconds / Maximum benefit value\t\t\t\t\t\t \t\t\n");
	fprintf(fp, "Number of Item\t|\t\t   Greedy\t \t\t\t\t\t\t  D.P.\t\t\t\t\t\t \t\tB. & B.\n");
	Item *item;
	Item *sorted_item;
	
	///// Input = 10
	item = (Item *)malloc(sizeof(Item) * 10);
	sorted_item = (Item *)malloc(sizeof(Item) * 10);
	init_item(item, 10);
	merge_sort(item, sorted_item, 0, 10 -1);
	
	greedy(10, fp, item, sorted_item);
	dynamic(10, fp, item);
	//branch_bound(10, fp, item, sorted_item);
	
	free(item);
	free(sorted_item);
	

	///// Input = 100
	item = (Item *)malloc(sizeof(Item) * 100);
	sorted_item = (Item *)malloc(sizeof(Item) * 100);
	init_item(item, 100);
	merge_sort(item, sorted_item, 0, 100 -1);

	greedy(100, fp, item, sorted_item);
	dynamic(100, fp, item);
	//branch_bound(100, fp, item, sorted_item);

	free(item);
	free(sorted_item);
	/////


	///// Input = 500
	item = (Item *)malloc(sizeof(Item) * 500);
	sorted_item = (Item *)malloc(sizeof(Item) * 500);
	init_item(item, 500);
	merge_sort(item, sorted_item, 0, 500 -1);

	greedy(500, fp, item, sorted_item);
	dynamic(500, fp, item);
	//branch_bound(500, fp, item, sorted_item);

	free(item);
	free(sorted_item);
	/////


	///// Input = 1000
	item = (Item *)malloc(sizeof(Item) * 1000);
	sorted_item = (Item *)malloc(sizeof(Item) * 1000);
	init_item(item, 1000);
	merge_sort(item, sorted_item, 0, 1000 -1);

	greedy(1000, fp, item, sorted_item);
	dynamic(1000, fp, item);
	//branch_bound(1000, fp, item, sorted_item);

	free(item);
	free(sorted_item);
	/////


	


	///// Input = 5000
	item = (Item *)malloc(sizeof(Item) * 5000);
	sorted_item = (Item *)malloc(sizeof(Item) * 5000);
	init_item(item, 5000);
	merge_sort(item, sorted_item, 0, 5000 -1);

	greedy(5000, fp, item, sorted_item);
	dynamic(5000, fp, item);
	//branch_bound(5000, fp, item, sorted_item);

	free(item);
	free(sorted_item);
	/////


	///// Input = 7000
	item = (Item *)malloc(sizeof(Item) * 7000);
	sorted_item = (Item *)malloc(sizeof(Item) * 7000);
	init_item(item, 7000);
	merge_sort(item, sorted_item, 0, 7000 -1);

	greedy(7000, fp, item, sorted_item);
	dynamic(7000, fp, item);
	//branch_bound(7000, fp, item, sorted_item);

	free(item);
	free(sorted_item);
	/////


	///// Input = 9000
	item = (Item *)malloc(sizeof(Item) * 9000);
	sorted_item = (Item *)malloc(sizeof(Item) * 9000);
	init_item(item, 9000);
	merge_sort(item, sorted_item, 0, 9000 -1);

	greedy(9000, fp, item, sorted_item);
	dynamic(9000, fp, item);
	//branch_bound(9000, fp, item, sorted_item);

	free(item);
	free(sorted_item);
	/////


	///// Input = 10000
	item = (Item *)malloc(sizeof(Item) * 10000);
	sorted_item = (Item *)malloc(sizeof(Item) * 10000);
	init_item(item, 10000);
	merge_sort(item, sorted_item, 0, 10000 -1);

	greedy(10000, fp, item, sorted_item);
	dynamic(10000, fp, item);
	//branch_bound(10000, fp, item, sorted_item);

	free(item);
	free(sorted_item);
	/////
	
	
	fclose(fp);

	return 0;
}

/* MergeSort */
void merge(Item list[], Item* sorted_item, int left, int mid, int right){
  int i, j, k, l;
  i = left;
  j = mid+1;
  k = left;

  while(i<=mid && j<=right){
    if(list[i].value_per_weight > list[j].value_per_weight)
      sorted_item[k++] = list[i++];
    else{
			if(list[i].value_per_weight == list[j].value_per_weight && list[i].value > list[j].value)
				sorted_item[k++] = list[i++];
			else
				sorted_item[k++] = list[j++];
		}
      
  }

  if(i>mid){
    for(l=j; l<=right; l++)
      sorted_item[k++] = list[l];
  }
  else{
    for(l=i; l<=mid; l++)
      sorted_item[k++] = list[l];
  }

  for(l=left; l<=right; l++){
    list[l] = sorted_item[l];
  }
}

void merge_sort(Item list[], Item* sorted_item, int left, int right){
  int mid;

  if(left<right){
    mid = (left+right)/2; 
    merge_sort(list, sorted_item, left, mid); 
    merge_sort(list, sorted_item, mid+1, right); 
    merge(list, sorted_item, left, mid, right); 
  }
}



/* Rounding Function */
double rounding(double x, int num)
{
	return (floor((x) * pow((float)10, num) + 0.5f) / pow((float)10, num));
}

/* Initializing Items Function */
void init_item(Item* item, int num_of_item){
	int i;
	for(i = 0; i < num_of_item; i++){
		item[i].weight = rand() % 100 + 1;
		item[i].value = rand() % 300 + 1;
		item[i].value_per_weight = (double)item[i].value / item[i].weight;
		// printf("Item %d value = %d weight = %d value per weight: %lf\n", i + 1, item[i].value, item[i].weight, item[i].value_per_weight);
	}
}

/* Greedy Algorithm */
void greedy(int num_of_item, FILE* fp, Item *item, Item *sorted_item){
	clock_t start_time, end_time;
	start_time = clock(); //Start Process

	int max_capacity = num_of_item * 40;
	double result_benefit = 0;

	int i = 0;
	while(1){
		if(max_capacity <= 0)
			break;

		if(item[i].weight < max_capacity){
			result_benefit += item[i].value;
			max_capacity -= item[i].weight;
			i++;
		}else if(max_capacity > 0){
			result_benefit += item[i].value_per_weight;
			max_capacity -= 1;
		}

	}

	end_time = clock(); //End Process
	fprintf(fp, "%10d\t\t| %10.0lf ms / %-12d\t|\t", num_of_item, rounding((double)(end_time-start_time)/CLOCKS_PER_SEC,3)*1000, (int)result_benefit);

}


/* Dynamic Programming Algorithm */
void dynamic(int num_of_item, FILE* fp, Item *item){
	clock_t start_time, end_time;
	start_time = clock(); //Start Process
	
	//Variables
	int max_capacity = num_of_item * 40;
	int p, q;
	int **benefit;

	//Memory Allocation
	if(!(benefit = (int**)malloc(sizeof(int*) * (num_of_item + 1))))
		printf("First Malloc failed!");
	
	for(p = 0; p <= num_of_item; p++){
		if(!(benefit[p] = (int*)malloc(sizeof(int) * (max_capacity + 1))))
			printf("Second Malloc Failed!\n");
	}
	
	int w, i;
	for(w = 0; w <= max_capacity; w++){
		benefit[0][w] = 0;
	}
	for(i = 1; i <= num_of_item; i++){
		benefit[i][0] = 0;
		for(w = 1; w <= max_capacity; w++){
			if(item[i-1].weight <= w)
				if(item[i-1].value + benefit[i-1][w-item[i-1].weight] > benefit[i-1][w])
					benefit[i][w] = item[i-1].value + benefit[i-1][w-item[i-1].weight];
				else
					benefit[i][w] = benefit[i-1][w];
			else
				benefit[i][w] = benefit[i-1][w];
		}
	}

	end_time = clock(); //End Process
	fprintf(fp, "%10.0lf ms / %-12d\t|\t\n", rounding((double)(end_time-start_time)/CLOCKS_PER_SEC,3)*1000, benefit[num_of_item][max_capacity]);

	//Memory Deallocation
	for(p = 0; p <= num_of_item; p++){
		free(benefit[p]);
	}
	free(benefit);
}


/* Branch and Bound Algorithm */
// int max_benefit = 0; // A global variable that represents the maximum benefit

// void branch_bound(int num_of_item, FILE *fp, Item* item, Item* sorted_item){
// 	clock_t start_time, end_time;
// 	start_time = clock(); //Start Process

// 	//Variables
// 	int max_capacity = num_of_item * 40;
// 	int result_benefit = 0;


// 	end_time = clock(); //End Process
// 	fprintf(fp, " %10g ms / %-12d\n", rounding((double)(end_time-start_time)/CLOCKS_PER_SEC,3)*1000, max_benefit);
// }
