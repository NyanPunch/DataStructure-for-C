/*  doubly-linked-list.c
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */
/*******************************
프로그램명: 이중 연결리스트
작 성 자: 2019038054 김경민
작 성 일: 2022 04 23
프로그램 설명: 이중포인터와 싱글포인터의 차이를 이해하고 이중연결리스트 함수 구현
********************************/ 


#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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
			freeList(headnode);
			printf("[-----------------김경민-------------2019038054-----------------]\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(headNode** h) {
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

/* h와 연결된 listNode 메모리 해제
 * headNode도 해제되어야 함.
 */
int freeList(headNode* h){
	listNode* p = h->first; //첫 노드에 연결
	listNode* prev = NULL; //p 노드 앞(좌측)에 prev노드 생성
	/* p가 마지막 노드에 위치할때까지 */
	while(p != NULL) {
		prev = p; 	 //prev노드를 p노드 위치로 이동
		p = p->rlink;//p노드를 뒤(우측)노드로 이동
		free(prev);
	}
	free(h);
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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	/* 새 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;
	/* 리스트가 공백인 경우 */
	if (h->first == NULL){
		h->first = node;
		return 0;
	}
	/* 리스트의 마지막위치 이동 */
	listNode* n = h->first;
	while(n->rlink != NULL) {
		n = n->rlink;
	}
	n->rlink = node; //리스트의 마지막노드 우측(뒤)에 새 노드 연결
	node->llink = n; //새 노드의 좌측을 n노드와 연결
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	/* 리스트가 공백인 경우 */
	if (h->first == NULL){
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //헤드노드
	listNode* trail = NULL;	//꼬리노드

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}
	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {
		trail = n;   //꼬리노드를 헤드노드로 이동
		n = n->rlink;//헤드노드를 우측(뒤)노드로 이동
	}
	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;
	free(n); //마지막 노드 삭제

	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	/* 새 노드 생성*/
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;
	/* 리스트가 공백인 경우 헤드노드와 연결*/
	if(h->first == NULL){
		h->first = node;
		return 1;
	}
	/* 공백이 아닌 경우 */
	node->rlink = h->first; //헤드노드와 연결된 리스트를 우측에 연결
	node->llink = NULL;	//좌측노드 공백

	listNode *p = h->first; 
	p->llink = node; //기존 첫 노드의 좌측이 노드 연결
	h->first = node; //헤드노드와 새 노드 연결

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	/* 리스트가 공백인 경우 */
	if (h->first == NULL){
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //삭제노드 선언
	h->first = n->rlink;	//헤드노드를 첫번째 노드의 뒤(오른쪽) 노드연결

	free(n); //첫번째 노드 삭제
	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //헤드노드
	listNode *trail = NULL; //꼬리노드
	listNode *middle = NULL;//중간노드
	/* 헤드, 중간, 꼬리 순서로 한 칸씩 이동 */
	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail; //중간노드의 뒷노드가 꼬리
		middle->llink = n;	   //중간노드의 앞노드가 헤드
	}
	/* 마지막위치에 노드와 헤드노드 연결 */
	h->first = middle;
	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;
	/* 리스트가 공백인 경우 첫번째 노드에 삽입 */
	if (h->first == NULL){
		h->first = node;
		return 0;
	}
	listNode* n = h->first;
	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //우측을 key값이 큰 n노드 연결
				node->llink = n->llink; //좌측을 n노드가 가리키는 좌측노드 연결
				n->llink->rlink = node; //기존 n노드 좌측에 있던 노드와 새 노드 연결
			}
			return 0;
		}
		n = n->rlink; //뒤(오른쪽) 노드로 이동
	}
	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	/* 리스트가 공백인 경우 */
	if (h->first == NULL){
		printf("nothing to delete.\n");
		return 1;
	}
	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n노드 좌측에 노드가 n노드 우측노드와 연결
				n->rlink->llink = n->llink; //n노드 우측에 노드를 n노드 좌측노드와 연결
				free(n);
			}
			return 1;
		}
		n = n->rlink;
	}
	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}