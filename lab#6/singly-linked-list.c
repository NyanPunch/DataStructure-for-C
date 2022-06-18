/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h> //굳이?

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
}listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
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
			printf("-----------[김경민]----------------------[2019038054]-----------\n");
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
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode *temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
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
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;
	
	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	/* 리스트 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if(h->first == NULL) { 
		h->first = node;
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;

	/* 마지막 리스트까지 반복 */
	while(n->link != NULL){
		/* key보다 작으면 계속 넘어감 */
		/* n번째 key가 key보다 클 경우 */
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
 * list에서 key에 대한 노드 삭제
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
	//하나인경우
	if (n->link == NULL){
		h->first = NULL;
		free(n);
		return 0;
	}
	//마지막 이동
	while (n->link != NULL){
		prev = n;
		n = n->link;
	}
	prev->link = NULL;
	free(n);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
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