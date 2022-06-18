/* 11���� ����
*  2019038054 ����
*  2022 05 23 ~ 2022 05 28
*  Graph Search
*/

#include <stdio.h>
#include <stdlib.h>

/* �׷��� ��� */
typedef struct node{
	int vertex;			//������ ��Ÿ��
	struct node* link; 	//���� ���� ����
}GraphNode;
#define MAX_VERTEX 10

/* �湮Ȯ�ο� �迭 */
short int visited[MAX_VERTEX];
/* �湮 �ʱ�ȭ�Լ� */
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

GraphNode* deQueue();	//ť ����
void enQueue(GraphNode* aNode); //ť ����

/* �Լ� ���� */
int initializeGraph(GraphNode** h); /* �׷��� ���� */
int insertVertex(GraphNode* h, int v);	/* vertex ���� */
int insertEdge(GraphNode*h, int u,int v);	/* edge ���� */
void DFS(GraphNode* h, int v);	/* ���� �켱 Ž�� */
void BFS(GraphNode* h, int v);	/* �ʺ� �켱 Ž�� */
void printGraph(GraphNode* h);	/* �׷��� ��� */
int freeGraph(GraphNode* h);	/* �׷����Ҵ����� */
int freeVertex(GraphNode* ptr);	/* �����Ҵ����� */

int main()
{
	char command;
	GraphNode* head = NULL;	//����� ����
	int u, v; //������ �Է¹��� ���� ����

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
			printf("                    2019038054       ����                     \n");
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
			clearvisit();	//�湮 �ʱ�ȭ
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
		(*h+i)->link = NULL;		/* �ʱ�ȭ */ 
		(*h+i)->vertex = -1;		
	}
	front = rear = -1;
	return 0;
}

int freeGraph(GraphNode* h){
	/* ������ �迭 ���� �Ҵ� ���� */
	for(int i=0; i<MAX_VERTEX; i++){
		if((h+i)->link) freeVertex((h+i)->link);
	}
	/* ��� ���� */
	free(h);
	return 0;
}
/* recursive */
int freeVertex(GraphNode* ptr){
	/* ����� ��������Ʈ�� ������ �̵� */
	if(ptr){
		freeVertex(ptr->link);
		free(ptr);
	}
	return 0;
}
/* ���� ���� */
int insertVertex(GraphNode* h, int v){
	/* 0~9 ���� �ۿ��� �Է� �� */
	if(0 > v || v > 9){
		printf(" Vertex number is get out range!\n");
		return 0;
	}
	/* ������ �����ϴ� ��� */
	if((h+v)->vertex == v){
		printf(" Vertex is already exists!\n");
		return 0;
	}
	/* ������ 0~9���� �ο��ǹǷ� �ش� �迭���� ���� */
	(h+v)->vertex = v;
	return 1;
}
/* ���� ���� */
int insertEdge(GraphNode* h, int u,int v){
	/* �� ������ �������� ������� */
	if((h+u)->vertex==-1||(h+v)->vertex==-1){
		printf(" Vertex is not exists!\n");
		return 0;
	}

	/* vertex u ���� ���� */
	GraphNode* Edge1 = (GraphNode*)malloc(sizeof(GraphNode));
	Edge1->vertex = u;
	Edge1->link = NULL;
	/* vertex v ���� ����*/
	GraphNode* Edge2 = (GraphNode*)malloc(sizeof(GraphNode));
	Edge2->vertex = v;
	Edge2->link = NULL;

	/* ����尡 �Ǵ� ������ ���� */
	GraphNode* p = (h+u);
	while(1){ // v���� ����
		/* ������ �����ϴ� ��� */
		if(p->vertex == v){
			printf("\n Edge is already exists!\n");
			return 0;
		}
		/* ����� ��������Ʈ�� ���°�� */
		if(p->link==NULL){
			p->link = Edge2;
			break;
		}
		/* ����� ��������Ʈ�� ������ �� ū ��� */
		if(p->link->vertex > v){
			Edge2->link = p->link;
			p->link = Edge2;
			break;
		}
		/* ������ �� ���� ��� �̵� */
		else p = p->link;
	}
	/* v ���忡�� ���� */
	p = (h+v);
	while(1){
		/* ����� ������ ���� ��� */
		if(p->link==NULL){
			p->link = Edge1;
			break;
		} /* ����� ������ �� ū ��� */
		if(p->link->vertex > u){
			Edge1->link = p->link;
			p->link = Edge1;
			break;
		}
		else p = p->link; //����� ������ ���� ��� �̵�
	}
	return 0;
}
/* recursive */
void DFS(GraphNode* h,int v){
	/* v ���� �����ϴ� DFS */
	if((h+v)->vertex != v){ /* ������ ���� ��� */ 
		printf("\n Vertex is not exists!\n");
		return;
	}
	GraphNode* ptr = (h+v); //�����ͺ��� ����
	visited[v] = 1; //vertex v = TRUE �湮
	printf(" [%d] ", v);
	//���� ��ũ�� ���� ���
	for(;ptr;ptr = ptr->link){ //�湮 1�̸� ���� �������� �̵�
		/* visited[0] �� ��� DFS���� */
		if(!visited[ptr->vertex])
			DFS(h, ptr->vertex);
	}
	return;
} 
/* Queue �̿� */
void BFS(GraphNode* h, int v){
	if((h+v)->vertex != v){ /* ������ ���� ��� */
		printf("\n Vertex is not exists!\n");
		return;
	}
	/* �湮 �迭 �ʱ�ȭ */
	clearvisit();
	rear=front=-1;

	printf(" [%d] ", v);
	visited[v] = 1;

	GraphNode* p =(h+v);
	enQueue(p); //ť ����
	while(1){
		p = deQueue(); 
		for(;p;p = p->link){ 
			v = p->vertex;
			if(!visited[v]){ //�湮����������� �����ť����
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
			/* ������ �Ҵ�� ��� */
			if(p->vertex != -1){
				printf(" [%d] ->", p->vertex);
			}
			/* ��������Ʈ�� �ִ� ��� */
			if(p->link != NULL) p = p->link;
			else break;
		}
		printf("\n");
	}
	return;
}

/* front�� �������� ���� */
GraphNode* deQueue()
{
	if(front == rear){
		printf("\n Queue is empty!");
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
/* rear�� �������� ���� */
void enQueue(GraphNode* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if(front == rear){
		printf("\n Queue is FULL!\n");
		return;
	}
	queue[rear] = aNode;
}
