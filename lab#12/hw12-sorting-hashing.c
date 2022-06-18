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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
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
			printf("                    2019038054       ����                     \n");
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

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
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

/* ���� ���� */
int selectionSort(int *a)
{
	int min; //�ּҰ�
	int minindex; //������ġ(�ּҹ迭)
	int i, j;
	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	for (i = 0; i < MAX_ARRAY_SIZE; i++) {
		minindex = i;
		min = a[i]; //�ּҰ��� �˻��� �迭�� ����
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) {
			if (min > a[j])	{ //a[j]�� �� ������� ��ü
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i]; //���� ���� ��ȯ
		a[i] = min; //min == a[j]
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* ���� ���� */
int insertionSort(int *a)
{
	int i, j, t;
	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	for(i = 1; i < MAX_ARRAY_SIZE; i++)	{ //i = 1�� ���� a[0] = ���� ����
		t = a[i]; //������������ ù ���Ҹ� ����
		j = i; //������ �ε��� i ����
		/* �������տ��� �ݺ� */
		while (a[j-1] > t && j > 0)	{ // 0 < j < a[j-1]
			a[j] = a[j-1]; 
			j--;
		}
		a[j] = t; //������ ���� ���� t == a[i]
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* �������� �ڿ� �ִ� �迭�� ���Ͽ� ���� */
int bubbleSort(int *a)
{
	int i, j, t; //t = temp
	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	for(i = 0; i < MAX_ARRAY_SIZE; i++)	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) {
			if (a[j-1] > a[j]) { // j-1 ���� j�� �� ū ��� Swap
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
/* �� ���� */
int shellSort(int *a)
{
	int i, j, k, h, v; //h = ����
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) { //���ݼ��� ���ݾ� ����
		for (i = 0; i < h; i++) {
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) { //h��ŭ ���ݻ���
				v = a[j]; //���Ե� ��
				k = j;
				while (k > h-1 && a[k-h] > v) { //������ �ʿ��� ��
					a[k] = a[k-h]; //h �������� �̵�
					k -= h;
				}
				a[k] = v; //����
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* �� ���� */
int quickSort(int *a, int n) //n = MAX_ARRAY_SIZE
{
	int v, t; //v = pivot t = temp
	int i, j; //i = left, j = right
	if (n > 1) {
		v = a[n-1];
		i = -1;
		j = n - 1;
		while(1) {
			while(a[++i] < v); //i��°�� v���� ������ stop
			while(a[--j] > v); //j��°�� v���� ũ�� stop
			/* ������ �����ʺ��� ũ�ų� ���� ��� break */
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
		quickSort(a, i); //���� �κ����� quicksort
		quickSort(a+i+1, n-i-1); //������ �κ����� quicksort
	}
	return 0;
}
/* �ؽ��ڵ带 ��ȯ */
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}
/* �ؽ� �Լ� linear probing ������� overflow ó�� */
int hashing(int *a, int **ht)
{
	int *hashtable = NULL;
	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else { /* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
		hashtable = *ht; 
	}
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; //�ؽ����̺� �ʱ�ȭ
	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // Check hashtable
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/
	int key = -1; 
	int hashcode = -1; 
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) {
		key = a[i]; //array�� �� ������ �ؽ��ڵ��� Ű�� ��ȯ
		hashcode = hashCode(key); //�ؽ��ڵ� ���� 
		//printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]); //Check hashcode
		if (hashtable[hashcode] == -1) { //�ؽ����̺��� ��������� �� ����
			hashtable[hashcode] = key; 
		} else { /* linear probing */
			index = hashcode;
			while(hashtable[index] != -1) { //�ؽ����̺��� �� ��
				index = (++index) % MAX_HASH_TABLE_SIZE; //�� ĭ�� ����
				//printf("index = %d\n", index); //Check index
			}
			hashtable[index] = key; //�� �ڸ��� key ����
		}
	}
	return 0;
}
/* �ؽ����̺� �ִ� ���� �ּҸ� ��ȯ */
int search(int *ht, int key)
{
	int index = hashCode(key); //��ȯ�� �ؽ��ڵ带 ����
	if(ht[index] == key) //�ؽ����̺��� �ؽ��ڵ�� Ű�� �����ϸ� hashcode return
		return index;
	while(ht[++index] != key) //���������� �ݺ�
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; //ht[index] == key
}