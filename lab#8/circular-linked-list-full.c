/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *  2019038054 김경민
 */

#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

int main() {
	char command;
	int key;
	listNode* headnode=NULL;
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			printf("[\t\t2019038054\t김경민\t\t]\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}

int initialize(listNode** h) {
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);
	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){
	/* 리스트가 공백인 경우 */
	if(h->rlink == h) {
		free(h);
		return 1;
	}
	listNode* p = h->rlink;
	listNode* prev = NULL;
	/* p가 널이고 헤드노드를 만날 때 까지*/
	while(p != NULL && p != h) {
		prev = p;
		p = p->rlink;
		free(prev); //이전노드 할당해제
	}
	free(h); //마지막노드 할당해제
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");
	/* 공백 검사 */
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;
	/* 마지막 노드까지 반복 */
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //한 칸씩 이동
		i++;
	}
	printf("  items = %d\n", i);

	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

/* list에 key에 대한 노드하나를 추가 */
int insertLast(listNode* h, int key) {
	/* 공백인 경우 */
	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) { /* 첫 노드로 삽입 */
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else { /* 첫 노드의 왼쪽 노드 = 마지막 노드 */
		h->llink->rlink = node; //왼쪽노드의 오른쪽링크와 연결
		node->llink = h->llink; //왼쪽링크와 왼쪽노드 연결
		h->llink = node;	//헤드의 왼쪽링크와 연결
		node->rlink = h;	//오른쪽링크와 헤드연결
	}
	return 1;
}

/* list의 마지막 노드 삭제 */
int deleteLast(listNode* h) {
	/* 리스트 공백 확인 */
	if (h->llink == h || h == NULL)	{
		printf("nothing to delete.\n");
		return 1;
	}
	listNode* remove = h->llink; //h 왼쪽노드가 마지막 노드
	/* link 정리 */
	remove->llink->rlink = h; //rlink to h leftnode of lastnode
	h->llink = remove->llink; //leftnode of lastnode를 마지막노드설정
	free(remove);

	return 1;
}

/* list 처음에 key에 대한 노드하나를 추가 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	/* 새 노드를 헤드노드와 연결 */
	node->rlink = h->rlink; //처음노드를 오른쪽링크와 연결
	h->rlink->llink = node; //처음노드의 왼쪽링크와 노드 연결
	node->llink = h; //노드왼쪽링크 헤드 연결
	h->rlink = node; //첫번째노드로 설정
	return 1;
}

/* list의 첫번째 노드 삭제 */
int deleteFirst(listNode* h) {
	/* 리스트 공백 검사 */
	if (h == NULL || h->rlink == h)	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* remove = h->rlink; //h 오른쪽 노드가 첫번째 노드
	/* link 정리 */
	remove->rlink->llink = h; //두번째 노드의 왼쪽링크를 h와 연결
	h->rlink = remove->rlink; //헤드노드와 두번째 노드 연결
	free(remove);
	return 1;
}

/* 리스트의 링크를 역순으로 재 배치 */
int invertList(listNode* h) {
	/* 리스트 공백 검사 */
	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *middle = h;
	listNode *trail = h;
	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; //첫번째 노드를 마지막 노드로 설정

	while(n != NULL && n != h){ /* 한 노드씩 앞으로 이동 */
		trail = middle; 
		middle = n;
		n = n->rlink;
		middle->rlink = trail; /* 중간노드의 좌우링크 변경 */
		middle->llink = n;
	}
	h->rlink = middle; //마지막 노드를 첫번째 노드로 설정
	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	/* 초기화되지 않은 경우 */
	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;
	/* 리스트가 공백인 경우 */
	if (h->rlink == h) {
		insertFirst(h, key);
		return 1;
	}
	listNode* n = h->rlink;
	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;	//n 노드 왼편에 삽입
				node->llink = n->llink; //n노드 왼편노드와 링크연결
				n->llink->rlink = node; //n노드 왼편노드의 오른쪽링크 노드연결
				n->llink = node; //n노드 왼편링크와 노드 연결
			}
			return 0;
		}
		n = n->rlink;
	}
	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}

/* list에서 key에 대한 노드 삭제 */
int deleteNode(listNode* h, int key) {
	/* 리스트 공백 검사 */
	if (h->rlink == h || h == NULL)	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->rlink;
	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); 
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //삭제노드 왼편노드 오른쪽과 연결
				n->rlink->llink = n->llink; //삭제노드 오른편노드 왼쪽과 연결
				free(n);
			}
			return 0;
		}
		n = n->rlink; //다음 노드로 이동
	}
	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}