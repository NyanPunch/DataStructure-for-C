/* circularQ.c
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */
/*******************************
프로그램명: 원형 큐
작 성 자: 2019038054 김경민
작 성 일: 2022 04 06
프로그램 설명: 원형 큐의 동작들을 함수로 구현하고 실행
********************************/ 
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4	//큐의 최대 사이즈

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();	//동적메모리 큐 생성
int freeQueue(QueueType *cQ);	//동적메모리 큐 해제
int isEmpty(QueueType *cQ);	//공백상태검사
int isFull(QueueType *cQ);	//포화상태검사
void enQueue(QueueType *cQ, element item);	//큐 원소 삽입
void deQueue(QueueType *cQ, element* item);	//큐 원소 삭제
void printQ(QueueType *cQ);	//큐 출력
void debugQ(QueueType *cQ);	//큐 정보 출력
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;
	printf("\n---------------[김경민]----[2019038054]---------------\n");
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);	
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}
//큐 동적메모리 및 초기값 생성
QueueType *createQueue()
{
    QueueType* cQ = (QueueType*)malloc(sizeof(QueueType));
    cQ->front = NULL;
    cQ->rear = NULL;
    return cQ;
}
//큐 동적메모리 해제
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}
//원소 삽입
element getElement()
{
    element item;
    printf("input element = ");
    scanf(" %c",&item);
    return item;
}


//큐 공백상태 확인
int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear) {	//rear와 front가 동일 시 비어있는 상태
		printf("Queue is EMPTY!!");
		return 1;
	}
    else return 0;
}

//큐 포화상태 확인
int isFull(QueueType *cQ)
{
	if(((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front){	//rear의 다음위치가 front와 같을 시 포화상태
		printf("Queue is FULL!!");
		return 1;
	}
   	else return 0;
}


//큐 원소 삽입
void enQueue(QueueType *cQ, element item)
{	/* item = data */
	if(isFull(cQ))
		return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;	//rear의 다음위치 조정
		cQ->queue[cQ->rear] = item;
	}
}


//큐 원소 삭제
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ))
		return;
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front]; //설명
		return;
	}
}

//큐 출력 함수
void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;	//front의 뒤에 위치한 곳
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;	//rear의 

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

