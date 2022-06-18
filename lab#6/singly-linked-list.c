/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h> //����?

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
}listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			printf("-----------[����]----------------------[2019038054]-----------\n");
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode *temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode *p = h->first;
	listNode *prev = NULL;

	while(p != NULL){
		prev = p;
		p = p->link;
		free(prev);
	}
	free(p);
	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;
	
	return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	/* ����Ʈ ���� */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if(h->first == NULL) { 
		h->first = node;
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;

	/* ������ ����Ʈ���� �ݺ� */
	while(n->link != NULL){
		/* key���� ������ ��� �Ѿ */
		/* n��° key�� key���� Ŭ ��� */
		if(n->key >= key){
			if(n == h->first){
				h->first = node;
				node->link = n;
			}
			else {
				node->link = n;
				trail->link = node;
			}
			return 0;
		}
		trail = n;
		n = n->link;
	}
	return 0;
}

	// complete
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL){
		h->first = node;
		return 0;
	}

	listNode *n = h->first;

	while(n->link != NULL)	n = n->link;
	n->link = node;

	return 0;
}

		//complete
int deleteFirst(headNode* h) {
	if (h->first == NULL) {
		printf("Nothing to delete Node\n");
		return 0;
	}
	listNode *n = h->first;
	h->first = n->link;
	free(n);

	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	if(h->first == NULL){
		printf("nothing to delete\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *prev = NULL;
	while (n->key == key){
		prev = n;
		n = n->link;
	}
	prev->link = n->link;
	free(n);
	return 0;
}

	//complete
int deleteLast(headNode* h) {
	if(h->first == NULL){
		printf("nothing to delete");
		return 0;
	}
	listNode *n = h->first;
	listNode *prev = NULL;
	//�ϳ��ΰ��
	if (n->link == NULL){
		h->first = NULL;
		free(n);
		return 0;
	}
	//������ �̵�
	while (n->link != NULL){
		prev = n;
		n = n->link;
	}
	prev->link = NULL;
	free(n);

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	if (h->first == NULL){
		printf("list is empty\n");
		return 0;
	}
	listNode *p = h->first;
	listNode *mid = NULL;
	listNode *trail = NULL;

	while(p != NULL){
		trail = mid;
		mid = p;
		p = p->link;
		mid->link = trail;
	}
	h->first = mid;
	
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}