/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

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
			headnode = initialize(headnode); //중요
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
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}
/* h와 연결된 listNode 메모리 해제 headNode도 해제되어야 함. */
int freeList(headNode* h){
	listNode* p = h->first;
	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

/* list 처음에 key에 대한 노드하나를 추가 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //새 노드의 데이터에 key 저장

	node->link = h->first; //헤드노드가 가리키던곳 연결
	h->first = node; //헤드노드는 새 노드 연결

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	//리스트가 공백인 경우
	if (h->first == NULL) {
		h->first = node;	//새 노드를 리스트의 시작노드로 연결
		return 0;
	}

	listNode* n = h->first; //key 비교노드
	listNode* trail = h->first; //이전 비교노드

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) { //n번째 key가 입력한 key보다 크거나 같을때
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				insertFirst(h,key);
			} 
			else { /* 중간이거나 마지막인 경우 */
				node->link = n; 		//새노드를 n번노드 앞에 연결
				trail->link = node; 	//이전노드를 새노드에 연결
			}
			return 0;
		}
		/* 비교가 끝난 n 노드에 trail이 오고 n 노드는 한칸이동 */
		trail = n;
		n = n->link;
	}
	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/* list에 key에 대한 노드하나를 추가 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	//리스트가 공백인 경우
	if (h->first == NULL) {
		h->first = node;
		return 0;
	}
	//리스트가 공백이 아닌경우
	listNode* n = h->first;
	while(n->link != NULL) n = n->link; //현재 리스트의 마지막노드를 찾는다
	n->link = node;	//새 노드를 마지막 노드의 다음 노드로 연결
	return 0;
}

/* list에서 key에 대한 노드 삭제 */
int deleteNode(headNode* h, int key) {
	//리스트가 공백인 경우
	if (h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //삭제노드
	listNode* trail = NULL; //삭제노드 이전위치 노드

	/* key를 기준으로 삭제할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드를 삭제해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}
		//한 칸씩 뒤로 이동
		trail = n;
		n = n->link;
	}
	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}

/* list의 마지막 노드 삭제 */
int deleteLast(headNode* h) {
	//리스트가 공백인 경우
	if (h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //삭제노드
	listNode* trail = NULL;	//n노드 뒤 꼬리노드

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}
	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}
	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n);

	return 0;
}

/* list의 첫번째 노드 삭제 */
int deleteFirst(headNode* h) {
	//리스트가 공백인 경우
	if (h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}
	//삭제노드 할당
	listNode* n = h->first;
	h->first = n->link;
	free(n); //삭제노드 메모리 해제

	return 0;
}

/* 리스트의 링크를 역순으로 재 배치 */
int invertList(headNode* h) {
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //헤드노드
	listNode *trail = NULL; //꼬리노드
	listNode *middle = NULL;//중간노드
	/* n, middle, trail 노드를 순서대로 한 칸씩 이동 */
	while(n != NULL){
		trail = middle; 
		middle = n;		
		n = n->link;	
		middle->link = trail; 
	}	//중간노드 링크가 꼬리노드와 연결하여 앞 뒤를 바꾼다
	/* 마지막 위치에 노드를 헤드노드 연결 */
	h->first = middle;

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");
	//헤드노드가 공백인 경우
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;
	//마지막 리스트를 통과할때까지
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}