/* 11주차 과제
*  2019038054 김경민
*  2022 05 23 ~ 2022 05 28
*  Graph Search
*/

#include <stdio.h>
#include <stdlib.h>

/* 그래프 노드 */
typedef struct node{
	int vertex;			//정점을 나타냄
	struct node* link; 	//다음 노드와 연결
}GraphNode;
#define MAX_VERTEX 10

/* 방문확인용 배열 */
short int visited[MAX_VERTEX];
/* 방문 초기화함수 */
void clearvisit(){
	for(int i=0;i<MAX_VERTEX;i++){
		visited[i]=0;
	}
}

/* for queue */
#define MAX_QUEUE_SIZE 10
GraphNode* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

GraphNode* deQueue();	//큐 삭제
void enQueue(GraphNode* aNode); //큐 삽입

/* 함수 선언 */
int initializeGraph(GraphNode** h); /* 그래프 생성 */
int insertVertex(GraphNode* h, int v);	/* vertex 삽입 */
int insertEdge(GraphNode*h, int u,int v);	/* edge 삽입 */
void DFS(GraphNode* h, int v);	/* 깊이 우선 탐색 */
void BFS(GraphNode* h, int v);	/* 너비 우선 탐색 */
void printGraph(GraphNode* h);	/* 그래프 출력 */
int freeGraph(GraphNode* h);	/* 그래프할당해제 */
int freeVertex(GraphNode* ptr);	/* 정점할당해제 */

int main()
{
	char command;
	GraphNode* head = NULL;	//헤드노드 생성
	int u, v; //정점을 입력받을 변수 생성

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                          Graph Search                          \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeGraph(&head);
			break;
		case 'q': case 'Q':
			freeGraph(head);
			printf("----------------------------------------------------------------\n");
			printf("                    2019038054       김경민                     \n");
			printf("----------------------------------------------------------------\n");
			break;
        case 'v': case 'V':
            printf("Your Key(0~9) = ");
            scanf("%d", &u);
			insertVertex(head, u);
			break;
        case 'e': case 'E':
            printf("Your Key(u) = ");
            scanf("%d", &u);
            printf("Your Key(v) = ");
            scanf("%d", &v);
			insertEdge(head, u, v);
			break;
        case 'd': case 'D':
			clearvisit();	//방문 초기화
			printf("Your Key = ");
            scanf("%d", &u);
			DFS(head, u);
			break;
        case 'b': case 'B':
			printf("Your Key = ");
            scanf("%d", &u);
			BFS(head, u);
			break;
        case 'p': case 'P':
			printGraph(head);
			break;			
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeGraph(GraphNode** h){
	if(*h != NULL ) freeGraph(*h);
	/* MAX VERTEX SIZE = 10 */
	*h = (GraphNode*)malloc(sizeof(GraphNode)*MAX_VERTEX);
	for(int i=0;i<MAX_VERTEX;i++){
		(*h+i)->link = NULL;		/* 초기화 */ 
		(*h+i)->vertex = -1;		
	}
	front = rear = -1;
	return 0;
}

int freeGraph(GraphNode* h){
	/* 포인터 배열 내부 할당 해제 */
	for(int i=0; i<MAX_VERTEX; i++){
		if((h+i)->link) freeVertex((h+i)->link);
	}
	/* 헤드 해제 */
	free(h);
	return 0;
}
/* recursive */
int freeVertex(GraphNode* ptr){
	/* 연결된 인접리스트가 있으면 이동 */
	if(ptr){
		freeVertex(ptr->link);
		free(ptr);
	}
	return 0;
}
/* 정점 생성 */
int insertVertex(GraphNode* h, int v){
	/* 0~9 범위 밖에서 입력 시 */
	if(0 > v || v > 9){
		printf(" Vertex number is get out range!\n");
		return 0;
	}
	/* 정점이 존재하는 경우 */
	if((h+v)->vertex == v){
		printf(" Vertex is already exists!\n");
		return 0;
	}
	/* 정점은 0~9값이 부여되므로 해당 배열값에 생성 */
	(h+v)->vertex = v;
	return 1;
}
/* 간선 생성 */
int insertEdge(GraphNode* h, int u,int v){
	/* 두 정점이 존재하지 않은경우 */
	if((h+u)->vertex==-1||(h+v)->vertex==-1){
		printf(" Vertex is not exists!\n");
		return 0;
	}

	/* vertex u 간선 생성 */
	GraphNode* Edge1 = (GraphNode*)malloc(sizeof(GraphNode));
	Edge1->vertex = u;
	Edge1->link = NULL;
	/* vertex v 간선 생성*/
	GraphNode* Edge2 = (GraphNode*)malloc(sizeof(GraphNode));
	Edge2->vertex = v;
	Edge2->link = NULL;

	/* 헤드노드가 되는 정점에 연결 */
	GraphNode* p = (h+u);
	while(1){ // v간선 연결
		/* 간선이 존재하는 경우 */
		if(p->vertex == v){
			printf("\n Edge is already exists!\n");
			return 0;
		}
		/* 연결된 인접리스트가 없는경우 */
		if(p->link==NULL){
			p->link = Edge2;
			break;
		}
		/* 연결된 인접리스트의 정점이 더 큰 경우 */
		if(p->link->vertex > v){
			Edge2->link = p->link;
			p->link = Edge2;
			break;
		}
		/* 정점이 더 작은 경우 이동 */
		else p = p->link;
	}
	/* v 입장에서 연결 */
	p = (h+v);
	while(1){
		/* 연결된 정점이 없는 경우 */
		if(p->link==NULL){
			p->link = Edge1;
			break;
		} /* 연결된 정점이 더 큰 경우 */
		if(p->link->vertex > u){
			Edge1->link = p->link;
			p->link = Edge1;
			break;
		}
		else p = p->link; //연결된 정점이 작은 경우 이동
	}
	return 0;
}
/* recursive */
void DFS(GraphNode* h,int v){
	/* v 부터 시작하는 DFS */
	if((h+v)->vertex != v){ /* 정점이 없는 경우 */ 
		printf("\n Vertex is not exists!\n");
		return;
	}
	GraphNode* ptr = (h+v); //포인터변수 생성
	visited[v] = 1; //vertex v = TRUE 방문
	printf(" [%d] ", v);
	//다음 링크가 있을 경우
	for(;ptr;ptr = ptr->link){ //방문 1이면 다음 정점으로 이동
		/* visited[0] 일 경우 DFS실행 */
		if(!visited[ptr->vertex])
			DFS(h, ptr->vertex);
	}
	return;
} 
/* Queue 이용 */
void BFS(GraphNode* h, int v){
	if((h+v)->vertex != v){ /* 정점이 없는 경우 */
		printf("\n Vertex is not exists!\n");
		return;
	}
	/* 방문 배열 초기화 */
	clearvisit();
	rear=front=-1;

	printf(" [%d] ", v);
	visited[v] = 1;

	GraphNode* p =(h+v);
	enQueue(p); //큐 삽입
	while(1){
		p = deQueue(); 
		for(;p;p = p->link){ 
			v = p->vertex;
			if(!visited[v]){ //방문하지않은경우 출력후큐삽입
				printf(" [%d] ", p->vertex);
				enQueue(h+v);
				visited[v] = 1;
			}
		}
		/* isEmpty */
		if(rear == front) break;
	}
	return;
}
/* AdjList */
void printGraph(GraphNode* h){
	if(h == NULL){
		printf("\nGraph is not exists!\n");
		return;
	}

	GraphNode* p = h;
	for(int i=0; i<MAX_VERTEX; i++){
		p =(h+i);
		for(int j=0;j<MAX_VERTEX;j++){
			/* 정점이 할당된 경우 */
			if(p->vertex != -1){
				printf(" [%d] ->", p->vertex);
			}
			/* 인접리스트가 있는 경우 */
			if(p->link != NULL) p = p->link;
			else break;
		}
		printf("\n");
	}
	return;
}

/* front를 증가시켜 삭제 */
GraphNode* deQueue()
{
	if(front == rear){
		printf("\n Queue is empty!");
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
/* rear를 증가시켜 삽입 */
void enQueue(GraphNode* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if(front == rear){
		printf("\n Queue is FULL!\n");
		return;
	}
	queue[rear] = aNode;
}
