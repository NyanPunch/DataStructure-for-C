/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

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
			headnode = initialize(headnode); //�߿�
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
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}
/* h�� ����� listNode �޸� ���� headNode�� �����Ǿ�� ��. */
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

/* list ó���� key�� ���� ����ϳ��� �߰� */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //�� ����� �����Ϳ� key ����

	node->link = h->first; //����尡 ����Ű���� ����
	h->first = node; //������ �� ��� ����

	return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	//����Ʈ�� ������ ���
	if (h->first == NULL) {
		h->first = node;	//�� ��带 ����Ʈ�� ���۳��� ����
		return 0;
	}

	listNode* n = h->first; //key �񱳳��
	listNode* trail = h->first; //���� �񱳳��

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) { //n��° key�� �Է��� key���� ũ�ų� ������
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				insertFirst(h,key);
			} 
			else { /* �߰��̰ų� �������� ��� */
				node->link = n; 		//����带 n����� �տ� ����
				trail->link = node; 	//������带 ����忡 ����
			}
			return 0;
		}
		/* �񱳰� ���� n ��忡 trail�� ���� n ���� ��ĭ�̵� */
		trail = n;
		n = n->link;
	}
	/* ������ ������ ã�� ���� ��� , �������� ���� */
	trail->link = node;
	return 0;
}

/* list�� key�� ���� ����ϳ��� �߰� */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	//����Ʈ�� ������ ���
	if (h->first == NULL) {
		h->first = node;
		return 0;
	}
	//����Ʈ�� ������ �ƴѰ��
	listNode* n = h->first;
	while(n->link != NULL) n = n->link; //���� ����Ʈ�� ��������带 ã�´�
	n->link = node;	//�� ��带 ������ ����� ���� ���� ����
	return 0;
}

/* list���� key�� ���� ��� ���� */
int deleteNode(headNode* h, int key) {
	//����Ʈ�� ������ ���
	if (h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //�������
	listNode* trail = NULL; //������� ������ġ ���

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key == key) {
			/* ù ��带 �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				h->first = n->link;
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}
		//�� ĭ�� �ڷ� �̵�
		trail = n;
		n = n->link;
	}
	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}

/* list�� ������ ��� ���� */
int deleteLast(headNode* h) {
	//����Ʈ�� ������ ���
	if (h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //�������
	listNode* trail = NULL;	//n��� �� �������

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}
	/* ������ ������ �̵� */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}
	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->link = NULL;
	free(n);

	return 0;
}

/* list�� ù��° ��� ���� */
int deleteFirst(headNode* h) {
	//����Ʈ�� ������ ���
	if (h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}
	//������� �Ҵ�
	listNode* n = h->first;
	h->first = n->link;
	free(n); //������� �޸� ����

	return 0;
}

/* ����Ʈ�� ��ũ�� �������� �� ��ġ */
int invertList(headNode* h) {
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //�����
	listNode *trail = NULL; //�������
	listNode *middle = NULL;//�߰����
	/* n, middle, trail ��带 ������� �� ĭ�� �̵� */
	while(n != NULL){
		trail = middle; 
		middle = n;		
		n = n->link;	
		middle->link = trail; 
	}	//�߰���� ��ũ�� �������� �����Ͽ� �� �ڸ� �ٲ۴�
	/* ������ ��ġ�� ��带 ����� ���� */
	h->first = middle;

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");
	//����尡 ������ ���
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;
	//������ ����Ʈ�� ����Ҷ�����
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}