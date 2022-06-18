/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			printf("----------------------------------------------------------------\n");
			printf("                    2019038054       김경민                     \n");
			printf("----------------------------------------------------------------\n");
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);
			break;
		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;
		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;
		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

/* 선택 정렬 */
int selectionSort(int *a)
{
	int min; //최소값
	int minindex; //기준위치(최소배열)
	int i, j;
	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	for (i = 0; i < MAX_ARRAY_SIZE; i++) {
		minindex = i;
		min = a[i]; //최소값을 검색할 배열로 설정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) {
			if (min > a[j])	{ //a[j]가 더 작을경우 교체
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i]; //값을 서로 교환
		a[i] = min; //min == a[j]
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* 삽입 정렬 */
int insertionSort(int *a)
{
	int i, j, t;
	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	for(i = 1; i < MAX_ARRAY_SIZE; i++)	{ //i = 1로 시작 a[0] = 정렬 집합
		t = a[i]; //정렬하지않은 첫 원소를 삽입
		j = i; //정렬할 인덱스 i 저장
		/* 정렬집합에서 반복 */
		while (a[j-1] > t && j > 0)	{ // 0 < j < a[j-1]
			a[j] = a[j-1]; 
			j--;
		}
		a[j] = t; //정렬할 원소 삽입 t == a[i]
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* 버블정렬 뒤에 있는 배열과 비교하여 스왑 */
int bubbleSort(int *a)
{
	int i, j, t; //t = temp
	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	for(i = 0; i < MAX_ARRAY_SIZE; i++)	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) {
			if (a[j-1] > a[j]) { // j-1 보다 j가 더 큰 경우 Swap
				t = a[j-1];	
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* 셸 정렬 */
int shellSort(int *a)
{
	int i, j, k, h, v; //h = 간격
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) { //간격설정 절반씩 감소
		for (i = 0; i < h; i++) {
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) { //h만큼 간격생성
				v = a[j]; //삽입될 값
				k = j;
				while (k > h-1 && a[k-h] > v) { //정렬이 필요할 시
					a[k] = a[k-h]; //h 간격으로 이동
					k -= h;
				}
				a[k] = v; //삽입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* 퀵 정렬 */
int quickSort(int *a, int n) //n = MAX_ARRAY_SIZE
{
	int v, t; //v = pivot t = temp
	int i, j; //i = left, j = right
	if (n > 1) {
		v = a[n-1];
		i = -1;
		j = n - 1;
		while(1) {
			while(a[++i] < v); //i번째가 v보다 작으면 stop
			while(a[--j] > v); //j번째가 v보다 크면 stop
			/* 왼쪽이 오른쪽보다 크거나 같은 경우 break */
			if (i >= j) break;
			/* swap */
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		/* swap */
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
		quickSort(a, i); //왼쪽 부분집합 quicksort
		quickSort(a+i+1, n-i-1); //오른쪽 부분집합 quicksort
	}
	return 0;
}
/* 해시코드를 반환 */
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}
/* 해시 함수 linear probing 방식으로 overflow 처리 */
int hashing(int *a, int **ht)
{
	int *hashtable = NULL;
	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else { /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
		hashtable = *ht; 
	}
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; //해시테이블 초기화
	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // Check hashtable
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/
	int key = -1; 
	int hashcode = -1; 
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) {
		key = a[i]; //array에 각 값들을 해시코드의 키로 변환
		hashcode = hashCode(key); //해시코드 삽입 
		//printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]); //Check hashcode
		if (hashtable[hashcode] == -1) { //해시테이블이 비어있으면 값 저장
			hashtable[hashcode] = key; 
		} else { /* linear probing */
			index = hashcode;
			while(hashtable[index] != -1) { //해시테이블이 빈 곳
				index = (++index) % MAX_HASH_TABLE_SIZE; //한 칸씩 증가
				//printf("index = %d\n", index); //Check index
			}
			hashtable[index] = key; //빈 자리에 key 저장
		}
	}
	return 0;
}
/* 해시테이블에 있는 값의 주소를 반환 */
int search(int *ht, int key)
{
	int index = hashCode(key); //반환된 해시코드를 받음
	if(ht[index] == key) //해시테이블의 해시코드와 키가 동일하면 hashcode return
		return index;
	while(ht[++index] != key) //같을때까지 반복
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; //ht[index] == key
}