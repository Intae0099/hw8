/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
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



int main()
{
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

/* 메모리 해제 */
int freeList(listNode* h){
    
    listNode* p = h->rlink;

	listNode* prev = NULL;
	while(p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
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



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

    listNode* p = h->rlink;
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key;

    if(p == h)
    {
        h->rlink = newNode;
        h->llink = newNode;
        newNode->rlink = h;
        newNode->llink = h;
        return 1;
    }
    else
    {
        while(p->rlink != h)
        {
            p = p->rlink;
        }
        p->rlink = newNode;
        newNode->llink = p;
        newNode->rlink = h;
        h->llink = newNode;
    }
    
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

    listNode* p = h->rlink;
    if(p->rlink == h)
    {
        h->rlink = h;
        h->llink = h;
        free(p);
        return 1;
    }
    else
    {
        while(p->rlink != h)
        {
            p = p->rlink;
        }
        if(p->rlink == h)
        {
            p->llink->rlink = h;
            h->llink = p->llink;
            free(p);
            return 1;
        }
    }
   

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

    listNode* p = h->rlink;
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key;

    if(p == h)
    {
        h->rlink = newNode;
        h->llink = newNode;
        newNode->rlink = h;
        newNode->llink = h;
        return 1;
    }
    else
    {
        newNode->rlink = p;
        newNode->llink = h;
        p->llink = newNode;
        h->rlink = newNode;
    }
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

    listNode* p = h->rlink;

    if(p->rlink == h)
    {
        h->rlink = h;
        h->llink = h;
        free(p);
        return 1;
    }
    else
    {
        p->rlink->llink = p->llink;
        p->llink->rlink = p->rlink;
        free(p);
    }

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

    listNode *middle; //중간 노드
	listNode *trail; //뒤 노드
	listNode *lead; //앞 노드

	lead = h->rlink; //h의first를 lead에 불러온다
	middle = lead->llink; //middle를 NULL로 설정한다

	while(lead != h) //lead가 NULL일때 반복문 탈출
	{
		trail = middle; //trail을 중간노드로 둔다
		middle = lead; //중간 노드는 앞의 노드로 바꾼다
		lead = lead->rlink; //앞 노드는 앞노드의 rlink를 타고 다음노드로 간다
		middle->rlink = trail; //중간노드의 rlink는 trail로 바꿈으로서 rlink를 역순으로 설정
		middle->llink = lead; //중간노드의 llink는 lead로 바꿈으로서 llink를 역순으로 설정
	}

	h->rlink = middle; //lead는 NULL로 바뀌었기 때문에 첫번째 노드는 lead의 이전 노드인 middle로 설정한다.

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {

    listNode* p = h->rlink;
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key;

    if(p->key > key)
    {
        newNode->rlink = p;
        newNode->llink = p->llink;
        p->llink->rlink = newNode;
        p->llink = newNode;
        h = newNode;
        return 0;
    }
    else
    {
        while(p->rlink != h && p->key < key)
        {
            p = p->rlink;
        }
        if(p->rlink == h)
        {
            newNode->llink = p;
            newNode->rlink = h;
            p->rlink = newNode;
            h->llink = newNode;
            return 0;
        }
        else
        {
            newNode->rlink = p;
            newNode->llink = p->llink;
            p->llink->rlink = newNode;
            p->llink = newNode;
            return 0;
        }
    }

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

    listNode* p = h->rlink;

    if(p->key == key)
    {
        p->rlink->llink = p->llink;
        p->llink->rlink = p->rlink;
        free(h);
        return 0;
    }
    else
    {  
        while(p->rlink != h&& p->key != key)
        {
            p = p->rlink;
        }
        if(p->key !=key && p->rlink == h)
        {
            return 0;
        }
        else if(p->key == key)
        {
            p->rlink->llink = p->llink;
            p->llink->rlink = p->rlink;
        }
        free(p);
    }

	return 0;
}


