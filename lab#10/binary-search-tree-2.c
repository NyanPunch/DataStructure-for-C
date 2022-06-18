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
			printf("                    2019038054       ����                     \n");
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
		recursiveInorder(ptr->left);	//���ʼ�ȸ
		printf(" [%d] ", ptr->key);		//���
		recursiveInorder(ptr->right);	//�����ʼ�ȸ
	}
}

/* Stack */
void iterativeInorder(Node* node)
{
	for(;;){ //���ѷ���
		//���� �ڽĳ�� ��ȸ
		for(; node; node = node->left) //node != NULL �ݺ�
			push(node); //���ÿ� ����
		node = pop();	//���ÿ��� ����

		if(!node) break; //���� ����

		printf(" [%d] ", node->key); //���
		node = node->right;	//�����ʼ�ȸ
	}
}

/* Queue */
void levelOrder(Node* ptr)
{
	if (!ptr) return; // Node is empty

	enQueue(ptr); //ť ����
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
		/* ������ key�� ������ ��尡 �����ϸ� ���� �Ұ��ϹǷ� ���� */
		if(ptr->key == key) return 1;
		/* ������ ��尡 ���ٸ� �θ��� ��ġ ���� */
		parentNode = ptr;
		/* ������ key ���� ū ��� ������ ���� �̵��ϰ� 
		 * ������ key ���� ���� ��� ���� ���� �̵��Ѵ� */
		if(ptr->key < key) ptr = ptr->right;
		else ptr = ptr->left;
	}

	/* ���� ������ ��带 �θ���� ���� */
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

	/* ���� ���� ���ö����� ��� ��ȸ */
	while((p != NULL)&&(p->key != key)){ 
		if(p->key != key){
			/* ��� �̵� */
			parent = p;
			/* ã�� Ű�� �� ������ ���� ũ�� ������ */
			if(p->key > key) p = p->left; 
			else p = p->right;
		}
	}	
	/* p->key == key OR p == NULL ���·� �ݺ��� Ż�� */

	if(p == NULL){
		printf("No node for the key [%d]\n",key);
		return 0;
	}

	/* case 1: ���� ���� ���� */
	if(p->left == NULL && p->right == NULL){
		/* �ڽĳ���� ��ġ Ȯ�� �� ���� */
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
	/* case 2: �ϳ��� �ڽ��� ���� ���� ��� ���� */
	if(p->left == NULL || p->right == NULL){
		Node *child;
		/* �ڽĳ�� ��ġ �ʱ�ȭ */
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
	/* case 3: �� �ڽ��� ���� ���� ��� ���� */
	/* ������ �ڽ� �� ���� ���� ���� ã�� ��ü */
	Node *candiate; //���� �� Ž�� ��� ����
	parent = p; 	//���� ��� = �θ� ���
	candiate = p->right;
	/* ���� �ڽ��� ���� �� �̹Ƿ� ���� ������ ��� �̵� */
	while(candiate->left != NULL){
		parent = candiate;
		candiate = candiate->left;
	}
	/* ��� �̵��� ���� ��� */
	if (parent->right == candiate) parent->right = candiate->right;
	else /* parent->left == candiate */
		parent->left = candiate->right;

	/* ���� ��� ��ġ�� candiate�� ���� */
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
/* ������ ž ���� */
Node* pop() {
	if(top < 0) return NULL;
	return stack[top--];
}
/* ������ ž�� ������Ű�� ���� */
void push(Node* aNode) {
	stack[++top] = aNode; 
}
/* front�� �������� ���� */
Node* deQueue()
{
	if(front == rear){
		printf("\n Queue is empty!");
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
/* rear�� �������� ���� */
void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if(front == rear){
		printf("\n Queue is FULL!\n");
		return;
	}
	queue[rear] = aNode;
}
