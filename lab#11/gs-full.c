/*
 * graph-search.c
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>


/* for graph */
typedef struct graph {
	int vertex;
	struct graph *link;
} Graph;

/* for stack */
#define MAX_STACK_SIZE		10	//max vertex size = 10
Graph* stack[MAX_STACK_SIZE];
int top = -1;

Graph* pop();
void push(Graph* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		10 //max vertex size = 10
Graph* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Graph* deQueue();
void enQueue(Graph* aNode);

/* functions that you have to implement */
int initializeGraph(Graph** h);
int freeGraph(Graph* h);
int InsertVertex(Graph* h,int);
int InsertEdge(Graph* h,int, int);
void DFS(Graph* h, int);
void BFS(Graph* h, int);
void PrintGraph(Graph* h);
void freeVertex(Graph *ptr);


int main()
{
	char command;
	int v1,v2;
    Graph* head=NULL;
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph search                           \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                     \n");
		printf(" Insert Vertex          = v      Insert Edge                = e \n");
		printf(" Depth First Search     = d      Breath First Search        = b \n");
		printf(" Print Graph            = p      Quit                       = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeGraph(&head);
			break;

        case 'q': case 'Q':
			freeGraph(head);
			break;
        
        case 'v': case 'V':
            printf("Your Key = ");
            scanf("%d",&v1);
			InsertVertex(head,v1);
			break;

        case 'e': case 'E':
            printf("Your Key (v1) = ");
            scanf("%d",&v1);
            printf("Your Key (v2) = ");
            scanf("%d",&v2);
			InsertEdge(head,v1,v2);
			break;

        case 'd': case 'D':
			printf("Your Key = ");
            scanf("%d",&v1);
			DFS(head, v1);
			break;

        case 'b': case 'B':
			printf("Your Key = ");
            scanf("%d",&v1);
			BFS(head, v1);
			break;

        case 'p': case 'P':
			PrintGraph(head);
			break;
		
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;
}

int initializeGraph(Graph** h){	
    if(*h!=NULL)	
        freeGraph(*h);
    *h=(Graph*)malloc(sizeof(Graph)*10);	//10???? ?????? ????? ?�� ????
    for(int i=0;i<10;i++){
        (*h+i)->link=NULL;
        (*h+i)->vertex=-1;	//?? ???????? vertex?? -1???? ????
    }
    top=-1;
    front = rear = -1;

    return 1;
}

void freeVertex(Graph *ptr){	
    if(ptr){
        freeVertex(ptr->link);
        free(ptr);
    }
}

int freeGraph(Graph* h){
    for(int i=0;i<10;i++){
        if((h+i)->link){	
           freeVertex((h+i)->link);
        }
    }
    free(h);	
    return 0;
}

int InsertVertex(Graph* h,int v1){	//?????? vertex ???? ??? vertex ?????? ????
   if((h+v1)->vertex==v1){	//??? vertex?? ??? ???????? ?????? ??? ?? ????
	   printf("\n key is already in graph\n");
	   return 0;
   }
   (h+v1)->vertex = v1;

   return 1;
}

int InsertEdge(Graph* h,int v1, int v2){
	if((h+v1)->vertex==-1||(h+v2)->vertex==-1){	//??? vertex?? ???????? ??��?? ?????? ???
		printf("\n key is not in graph \n");
		return 0;
	}


	Graph* temp1 =(Graph*)malloc(sizeof(Graph));		//???��? ???? ??? ???? ????
	Graph* temp2 =(Graph*)malloc(sizeof(Graph));		//???��? ???? ??? ???? ????
	Graph* p=(h+v1);	//??????? ????? ?��????? ????.

	temp1->vertex=v1;
	temp1->link=NULL;
	temp2->vertex=v2;
	temp2->link=NULL;

	while(1){
		if(p->vertex==v2){// ??? ??????????
			printf("\n Edge already exist \n");
			return 0;
		}

		if(!p->link){	//??????? ??? ????? ????
			p->link=temp2;	//v1 ?? v2 ?? ?????
			break;
		}

		if(p->link->vertex > v2){	//??????????? vertex ??? ?????? ????
			temp2->link=p->link;
			p->link=temp2;
			break;
		}

		else p=p->link;		// ???? ??? ???????? ???
	}

	p=(h+v2);
	while(1){
		if(!p->link){ 
			p->link=temp1;	//v2 ?? v1?? ?????
			break;
		}
		if(p->link->vertex > v1){ //??????????? vertex ??? ?????? ????
			temp1->link=p->link;
			p->link=temp1;
			break;
		}
		else p=p->link;
	}

	return 0;
}

/*Depth First Search (iteratvie)*/
void DFS(Graph* h,int v){
	if((h+v)->vertex==-1){
		printf("\n key is not in graph \n");
		return ;
	}
	Graph* p = h+v;	//??????? ??????? ??????
	Graph* ptr = NULL;	//stack ?? pop?? ???? ptr

	int visited[10]; 
	for(int i=0;i<10;i++){
		visited[i]=0;
	}	//visit flag  0???? ????
	top = -1;	//stack top ????

	//visited[v]=1;	//?�� ??? 1 ???
	//push(h+v);

	while(1){
		
		v=p->vertex;	//???????? vertex?? ??��?.

		if(!visited[v]){	//??? vertex?? ?��???? ?????
			printf("  [%d]  ",v);	//???? ???
			visited[v]=1;			//?�� flag
			push(h+v);				//stack ?? push
			p=h+v;					//??? ???? ???? ??????? ???
		}
		else {			//??? vertex?? ?��?? ????
			if(p->link==NULL){	//???? ??? ???????? ??��??
				ptr=pop();		//stack ?? pop ?????.
				//printf(" [%d] ", ptr->vertex);
				p=h+(p->vertex);	//?????? ???
			}
			p=p->link;	//??? ???
		}

		if(top==-1)	break;	//stack?? ??????? ????? ???
	}

}
/*Breath First Search */
void BFS(Graph* h, int v){
	Graph* p=h+v;		//??????? ????? ??????
	
	if((h+v)->vertex==-1){
		printf("\n key is not in graph \n");
		return ;
	}

	int visited[10]; 
	for(int i=0;i<10;i++){visited[i]=0;}	//visit flag  0???? ????
	rear=front=-1;

	printf("  [%d]  ",v);
	visited[v]=1;
	enQueue(p);

	while(1){
		p=deQueue();
		for(;;p=p->link){
			v=p->vertex;
			if(!visited[v]){
				printf("  [%d]  ",p->vertex);
				enQueue(h+v);
				visited[v]=1;
			}
		}
		if(rear==front) break;
	}
}
/*Graph ?? ???????? ???. Graph ????? ???��? ???? ????, ??????????? ?????????? ????? ?? ??? ????? ?????????.*/
void PrintGraph(Graph* h){
	Graph* p=h;

	for(int i=0;i<10;i++){
		p=h+i;
		for(int j=0;j<10;j++){	//link?? ???? ?????? ??????? vertex?? ???, link?? ????? ???? ??????? ???
			if(p->vertex!=-1){	//p->vertex?? -1 ???? ?????? vertex?? insert ???? ???? ???????? ??????? ??��?.
				printf(" [%d] ",(p->vertex));
			}
			if(p->link){
				p=p->link;
			}
			else
				break;
		}
		printf("\n");
	}
}

Graph* pop()	//stack pop
{
	if(top==-1)	return NULL;	
	else return stack[top--];
}

void push(Graph* aNode)	//stack push 
{	if(top==MAX_STACK_SIZE-1) printf("stack is full\n");	
	else stack[++top]=aNode;	
}

Graph* deQueue()	//deQueue
{
	if(front==rear)	return 0;	
	else return queue[++front];	
}

void enQueue(Graph* aNode)	//enQueue
{
	if(rear==MAX_QUEUE_SIZE-1)	printf("queue is full\n");	
	else queue[++rear]=aNode;
}