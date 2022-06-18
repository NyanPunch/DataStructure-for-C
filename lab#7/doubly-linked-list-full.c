/*  doubly-linked-list.c
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */
/*******************************
���α׷���: ���� ���Ḯ��Ʈ
�� �� ��: 2019038054 ����
�� �� ��: 2022 04 23
���α׷� ����: ���������Ϳ� �̱��������� ���̸� �����ϰ� ���߿��Ḯ��Ʈ �Լ� ����
********************************/ 


#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
			printf("[-----------------����-------------2019038054-----------------]\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(headNode** h) {
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

/* h�� ����� listNode �޸� ����
 * headNode�� �����Ǿ�� ��.
 */
int freeList(headNode* h){
	listNode* p = h->first; //ù ��忡 ����
	listNode* prev = NULL; //p ��� ��(����)�� prev��� ����
	/* p�� ������ ��忡 ��ġ�Ҷ����� */
	while(p != NULL) {
		prev = p; 	 //prev��带 p��� ��ġ�� �̵�
		p = p->rlink;//p��带 ��(����)���� �̵�
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	/* �� ��� ���� */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;
	/* ����Ʈ�� ������ ��� */
	if (h->first == NULL){
		h->first = node;
		return 0;
	}
	/* ����Ʈ�� ��������ġ �̵� */
	listNode* n = h->first;
	while(n->rlink != NULL) {
		n = n->rlink;
	}
	n->rlink = node; //����Ʈ�� ��������� ����(��)�� �� ��� ����
	node->llink = n; //�� ����� ������ n���� ����
	return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	/* ����Ʈ�� ������ ��� */
	if (h->first == NULL){
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //�����
	listNode* trail = NULL;	//�������

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}
	/* ������ ������ �̵� */
	while(n->rlink != NULL) {
		trail = n;   //������带 ������ �̵�
		n = n->rlink;//����带 ����(��)���� �̵�
	}
	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL;
	free(n); //������ ��� ����

	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	/* �� ��� ����*/
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;
	/* ����Ʈ�� ������ ��� ������ ����*/
	if(h->first == NULL){
		h->first = node;
		return 1;
	}
	/* ������ �ƴ� ��� */
	node->rlink = h->first; //������ ����� ����Ʈ�� ������ ����
	node->llink = NULL;	//������� ����

	listNode *p = h->first; 
	p->llink = node; //���� ù ����� ������ ��� ����
	h->first = node; //������ �� ��� ����

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	/* ����Ʈ�� ������ ��� */
	if (h->first == NULL){
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //������� ����
	h->first = n->rlink;	//����带 ù��° ����� ��(������) ��忬��

	free(n); //ù��° ��� ����
	return 0;
}

/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //�����
	listNode *trail = NULL; //�������
	listNode *middle = NULL;//�߰����
	/* ���, �߰�, ���� ������ �� ĭ�� �̵� */
	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail; //�߰������ �޳�尡 ����
		middle->llink = n;	   //�߰������ �ճ�尡 ���
	}
	/* ��������ġ�� ���� ����� ���� */
	h->first = middle;
	return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;
	/* ����Ʈ�� ������ ��� ù��° ��忡 ���� */
	if (h->first == NULL){
		h->first = node;
		return 0;
	}
	listNode* n = h->first;
	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				insertFirst(h, key);
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n; //������ key���� ū n��� ����
				node->llink = n->llink; //������ n��尡 ����Ű�� ������� ����
				n->llink->rlink = node; //���� n��� ������ �ִ� ���� �� ��� ����
			}
			return 0;
		}
		n = n->rlink; //��(������) ���� �̵�
	}
	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	/* ����Ʈ�� ������ ��� */
	if (h->first == NULL){
		printf("nothing to delete.\n");
		return 1;
	}
	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; //n��� ������ ��尡 n��� �������� ����
				n->rlink->llink = n->llink; //n��� ������ ��带 n��� �������� ����
				free(n);
			}
			return 1;
		}
		n = n->rlink;
	}
	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}