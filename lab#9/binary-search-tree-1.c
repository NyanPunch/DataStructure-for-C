/* Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 * 
 * 2019038054 김경민
 * 
 * 모든 원소는 서로 상이한 키를 갖는다.
 * 왼쪽 서브트리의 키는 그 루트의 키보다 작다.
 * 오른쪽 서브트리의 키는 그 루트의 키보다 크다.
 * 왼쪽, 오른쪽 서브트리도 이원 탐색트리다.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	 		/* recursive inorder traversal */
void preorderTraversal(Node* ptr);    		/* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  		/* recursive postorder traversal */
int insert(Node* head, int key);  			/* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  	/* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key); /* search the node for the key */
int freeBST(Node* head); 					/* free all memories allocated to the tree */
void freeNode(Node* ptr);					/* free all memories allocated to the node */
/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f \n");
		printf(" Postorder Traversal  = t      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			printf("-------------------김경민----------2019038054-------------------\n");
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}

/* All Traversal maded recursive function */
/* 중위 순회 LVR */
void inorderTraversal(Node* ptr)
{
	if(ptr){
		inorderTraversal(ptr->left);
		printf(" [%d] ",ptr->key);
		inorderTraversal(ptr->right);
	}
}
/* 전위 순회 VLR */
void preorderTraversal(Node* ptr)
{
	if(ptr){
		printf(" [%d] ",ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}	
}
/* 후위 순회 LRV */
void postorderTraversal(Node* ptr)
{
	if(ptr){
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ",ptr->key);
	}	
}

/* 삽입 함수 */
int insert(Node* head, int key)
{	/* new node */
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	/* if tree is null */
	if(head->left == NULL){
		head->left = node;
		return 1;
	}
	/* head->left == root */
	Node* ptr = head->left; /* 삽입 자리 탐색 변수 */
	Node* parentnode = NULL; /* 삽입노드의 부모노드 */

	while( ptr != NULL){
		/* 삽입하는 키와 같을 경우 리턴, 삽입 불가 */
		if(ptr->key == key) return 1;

		parentnode = ptr; //부모노드 위치 조정

		/* 삽입하는 key가 위치한 key보다 클 경우 오른쪽 노드로 이동
		   작을 경우 왼쪽 노드로 이동 */
		if (ptr->key < key)
		    ptr = ptr->right;
		else ptr = ptr->left;
	}
	/* 부모노드가 클 경우 왼쪽 서브트리 */
	if(parentnode->key > key)
		parentnode->left = node;
	else /* 부모노드가 작을 경우 오른쪽 서브트리 */
		parentnode->right = node;
	return 1;
}
/* ONLY leafNode  */
int deleteLeafNode(Node* head, int key)
{
	/* 전처리 공백 검사 */
	if(head == NULL){
		printf("Nothing to delete node\n");
		return 0;
	}
	if(head->left == NULL){
		printf("Nothing to delete node\n");
		return 0;		
	}
	
	Node* ptr = head->left;
	Node* parentnode = head;
	/* leaf 노드 삭제 */
	while(ptr != NULL){
		if(ptr->key == key){
			if(ptr->left == NULL && ptr->right == NULL){
				/* 노드가 하나인 경우 */
				if(parentnode == head) head->left = NULL;
				/* 좌우 구분 후 노드 삭제 */
				if(parentnode->left == ptr)
					parentnode->left = NULL;
				else
					parentnode->right = NULL;
				free(ptr);
			}
			else /* 리프노드가 아닌경우 */
			printf("[%d] Node is not leaf Node!\n", ptr->key);
			return 1;
		}
		parentnode = ptr;
		/* 부모노드의 크기의 따라 이동 */
		if(ptr->key < key)
		    ptr = ptr->right;
		else ptr = ptr->left;
	}
	printf("Cannot find delete Node\n");
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) return NULL;
	
	if(ptr->key < key) { /* 찾는 key가 큰 경우 right */
		ptr = searchRecursive(ptr->right, key);
	}
	else if (ptr->key > key){ /* key가 더 작은 경우 left */
		ptr = searchRecursive(ptr->left, key);
	}
	/* ptr->key == key */
	return ptr;
}

Node* searchIterative(Node* head, int key)
{
	if(head == NULL) return NULL;

	Node* ptr = head->left;

	while(ptr != NULL){
		/* key 찾은 경우 */
		if (ptr->key == key) return ptr;
		/* key 크기의 따라 노드 이동 */
		if (ptr->key < key)
			ptr = ptr->right;
		else ptr = ptr->left;
	}

	return NULL;
}


int freeBST(Node* head)
{
	/* 노드가 하나인 경우 */
	if(head->left == head) {
		free(head);
		return 1;
	}
	/* 노드가 여러개인 경우 */
	Node* p = head->left;
	freeNode(p);
	free(head);
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