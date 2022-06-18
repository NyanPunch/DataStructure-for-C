/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			printf("----------------------------------------------------------------\n");
			printf("                    2019038054       김경민                     \n");
			printf("----------------------------------------------------------------\n");
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		case 'l': case 'L':
			levelOrder(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {
	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);
	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	top = -1;
	front = rear = -1;
	return 1;
}

void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);	//왼쪽순회
		printf(" [%d] ", ptr->key);		//출력
		recursiveInorder(ptr->right);	//오른쪽순회
	}
}

/* Stack */
void iterativeInorder(Node* node)
{
	for(;;){ //무한루프
		//왼쪽 자식노드 순회
		for(; node; node = node->left) //node != NULL 반복
			push(node); //스택에 삽입
		node = pop();	//스택에서 삭제

		if(!node) break; //공백 스택

		printf(" [%d] ", node->key); //출력
		node = node->right;	//오른쪽순회
	}
}

/* Queue */
void levelOrder(Node* ptr)
{
	if (!ptr) return; // Node is empty

	enQueue(ptr); //큐 삽입
	for(;;){
		ptr = deQueue();
		if(ptr){
			printf(" [%d] ", ptr->key); /* V */
			if(ptr->left)
			    enQueue(ptr->left);		/* L */
			if(ptr->right)
			    enQueue(ptr->right);	/* R */
		}
		else break;
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;
	Node* parentNode = NULL;
	while(ptr != NULL) {
		/* 삽입할 key와 동일한 노드가 존재하면 삽입 불가하므로 리턴 */
		if(ptr->key == key) return 1;
		/* 동일한 노드가 없다면 부모노드 위치 조정 */
		parentNode = ptr;
		/* 삽입할 key 값이 큰 경우 오른쪽 노드로 이동하고 
		 * 삽입할 key 값이 작은 경우 왼쪽 노드로 이동한다 */
		if(ptr->key < key) ptr = ptr->right;
		else ptr = ptr->left;
	}

	/* 새로 삽입한 노드를 부모노드와 연결 */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{	
	/* Check empty */
	if(head == NULL){
		printf("\n Nothing to delete!\n");
		return 0;
	}
	if(head->left == NULL){
		printf("\n Nothing to delete!\n");
		return 0;
	}

	Node *root = head->left; 
	Node *parent = NULL;
	Node *p = root;

	/* 동일 값이 나올때까지 노드 순회 */
	while((p != NULL)&&(p->key != key)){ 
		if(p->key != key){
			/* 노드 이동 */
			parent = p;
			/* 찾는 키가 더 작으면 왼쪽 크면 오른쪽 */
			if(p->key > key) p = p->left; 
			else p = p->right;
		}
	}	
	/* p->key == key OR p == NULL 상태로 반복문 탈출 */

	if(p == NULL){
		printf("No node for the key [%d]\n",key);
		return 0;
	}

	/* case 1: 리프 원소 삭제 */
	if(p->left == NULL && p->right == NULL){
		/* 자식노드의 위치 확인 후 삭제 */
		if(parent != NULL){
			if(parent->left == p) parent->left = NULL;
			else parent->right = NULL;
		}
		else { /* parent == NULL */
			head->left = NULL;
		}
		free(p);
		return 0;
	}
	/* case 2: 하나의 자식을 가진 비리프 노드 삭제 */
	if(p->left == NULL || p->right == NULL){
		Node *child;
		/* 자식노드 위치 초기화 */
		if(p->left != NULL) child = p->left;
		else child = p->right;

		if(parent != NULL){
			if(parent->left == p) parent->left = child;
			else parent->right = child;
		}
		else{ /* parent == NULL */
			root = child;
		}
		free(p);
		return 0;
	}
	/* case 3: 두 자식을 가진 비리프 노드 삭제 */
	/* 오른쪽 자식 중 가장 작은 값을 찾아 대체 */
	Node *candiate; //작은 값 탐색 노드 선언
	parent = p; 	//삭제 노드 = 부모 노드
	candiate = p->right;
	/* 왼쪽 자식이 작은 값 이므로 왼쪽 마지막 노드 이동 */
	while(candiate->left != NULL){
		parent = candiate;
		candiate = candiate->left;
	}
	/* 노드 이동을 안한 경우 */
	if (parent->right == candiate) parent->right = candiate->right;
	else /* parent->left == candiate */
		parent->left = candiate->right;

	/* 삭제 노드 위치에 candiate가 삽입 */
	p->key = candiate->key;
	free(candiate); 
	return 1;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	if(head->left == head)
	{
		free(head);
		return 1;
	}
	Node* p = head->left;
	freeNode(p);
	free(head);
	return 1;
}
/* 스택의 탑 감소 */
Node* pop() {
	if(top < 0) return NULL;
	return stack[top--];
}
/* 스택의 탑을 증가시키고 삽입 */
void push(Node* aNode) {
	stack[++top] = aNode; 
}
/* front를 증가시켜 삭제 */
Node* deQueue()
{
	if(front == rear){
		printf("\n Queue is empty!");
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
/* rear를 증가시켜 삽입 */
void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if(front == rear){
		printf("\n Queue is FULL!\n");
		return;
	}
	queue[rear] = aNode;
}
