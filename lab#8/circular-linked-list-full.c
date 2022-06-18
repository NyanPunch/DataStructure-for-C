/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *  2019038054 ����
 */

#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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
			printf("[\t\t2019038054\t����\t\t]\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}

int initialize(listNode** h) {
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);
	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){
	/* ����Ʈ�� ������ ��� */
	if(h->rlink == h) {
		free(h);
		return 1;
	}
	listNode* p = h->rlink;
	listNode* prev = NULL;
	/* p�� ���̰� ����带 ���� �� ����*/
	while(p != NULL && p != h) {
		prev = p;
		p = p->rlink;
		free(prev); //������� �Ҵ�����
	}
	free(h); //��������� �Ҵ�����
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");
	/* ���� �˻� */
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;
	/* ������ ������ �ݺ� */
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //�� ĭ�� �̵�
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

/* list�� key�� ���� ����ϳ��� �߰� */
int insertLast(listNode* h, int key) {
	/* ������ ��� */
	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) { /* ù ���� ���� */
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else { /* ù ����� ���� ��� = ������ ��� */
		h->llink->rlink = node; //���ʳ���� �����ʸ�ũ�� ����
		node->llink = h->llink; //���ʸ�ũ�� ���ʳ�� ����
		h->llink = node;	//����� ���ʸ�ũ�� ����
		node->rlink = h;	//�����ʸ�ũ�� ��忬��
	}
	return 1;
}

/* list�� ������ ��� ���� */
int deleteLast(listNode* h) {
	/* ����Ʈ ���� Ȯ�� */
	if (h->llink == h || h == NULL)	{
		printf("nothing to delete.\n");
		return 1;
	}
	listNode* remove = h->llink; //h ���ʳ�尡 ������ ���
	/* link ���� */
	remove->llink->rlink = h; //rlink to h leftnode of lastnode
	h->llink = remove->llink; //leftnode of lastnode�� ��������弳��
	free(remove);

	return 1;
}

/* list ó���� key�� ���� ����ϳ��� �߰� */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	/* �� ��带 ������ ���� */
	node->rlink = h->rlink; //ó����带 �����ʸ�ũ�� ����
	h->rlink->llink = node; //ó������� ���ʸ�ũ�� ��� ����
	node->llink = h; //�����ʸ�ũ ��� ����
	h->rlink = node; //ù��°���� ����
	return 1;
}

/* list�� ù��° ��� ���� */
int deleteFirst(listNode* h) {
	/* ����Ʈ ���� �˻� */
	if (h == NULL || h->rlink == h)	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* remove = h->rlink; //h ������ ��尡 ù��° ���
	/* link ���� */
	remove->rlink->llink = h; //�ι�° ����� ���ʸ�ũ�� h�� ����
	h->rlink = remove->rlink; //������ �ι�° ��� ����
	free(remove);
	return 1;
}

/* ����Ʈ�� ��ũ�� �������� �� ��ġ */
int invertList(listNode* h) {
	/* ����Ʈ ���� �˻� */
	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *middle = h;
	listNode *trail = h;
	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink; //ù��° ��带 ������ ���� ����

	while(n != NULL && n != h){ /* �� ��徿 ������ �̵� */
		trail = middle; 
		middle = n;
		n = n->rlink;
		middle->rlink = trail; /* �߰������ �¿층ũ ���� */
		middle->llink = n;
	}
	h->rlink = middle; //������ ��带 ù��° ���� ����
	return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {
	/* �ʱ�ȭ���� ���� ��� */
	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;
	/* ����Ʈ�� ������ ��� */
	if (h->rlink == h) {
		insertFirst(h, key);
		return 1;
	}
	listNode* n = h->rlink;
	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;	//n ��� ���� ����
				node->llink = n->llink; //n��� ������� ��ũ����
				n->llink->rlink = node; //n��� �������� �����ʸ�ũ ��忬��
				n->llink = node; //n��� ����ũ�� ��� ����
			}
			return 0;
		}
		n = n->rlink;
	}
	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}

/* list���� key�� ���� ��� ���� */
int deleteNode(listNode* h, int key) {
	/* ����Ʈ ���� �˻� */
	if (h->rlink == h || h == NULL)	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->rlink;
	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h); 
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; //������� ������ �����ʰ� ����
				n->rlink->llink = n->llink; //������� �������� ���ʰ� ����
				free(n);
			}
			return 0;
		}
		n = n->rlink; //���� ���� �̵�
	}
	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}