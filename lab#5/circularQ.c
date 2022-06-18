/* circularQ.c
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */
/*******************************
???ес????: ???? ?
?? ?? ??: 2019038054 ????
?? ?? ??: 2022 04 06
???ес?? ????: ???? ??? ??????? ????? ??????? ????
********************************/ 
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4	//??? ??? ??????

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();	//??????? ? ????
int freeQueue(QueueType *cQ);	//??????? ? ????
int isEmpty(QueueType *cQ);	//??????б╞??
int isFull(QueueType *cQ);	//??????б╞??
void enQueue(QueueType *cQ, element item);	//? ???? ????
void deQueue(QueueType *cQ, element* item);	//? ???? ????
void printQ(QueueType *cQ);	//? ???
void debugQ(QueueType *cQ);	//? ???? ???
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;
	printf("\n---------------[????]----[2019038054]---------------\n");
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
//? ??????? ?? ??? ????
QueueType *createQueue()
{
	QueueType *cQ = (QueueType*)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}
//? ??????? ????
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}
//???? ????
element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

//? ???? ????
void enQueue(QueueType *cQ, element item)
{	/* item = data */
	if(isFull(cQ))
		return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;	//rear?? ??????? ????
		cQ->queue[cQ->rear] = item;
	}
}

//? ??????? ???
int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear) {	//rear?? front?? ???? ?? ?????? ????
		printf("Queue is EMPTY!!");
		return 1;
	}
    else return 0;
}

//? ??????? ???
int isFull(QueueType *cQ)
{
	if(((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front){	//rear?? ????????? front?? ???? ?? ???????
		printf("Queue is FULL!!");
		return 1;
	}
   	else return 0;
}

//? ???? ????
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ))
		return;
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front]; //????
		return;
	}
}

//? ??? ???
void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;	//front?? ??? ????? ??
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;	//rear?? 

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

