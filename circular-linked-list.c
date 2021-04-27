/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



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
         singly-linked-list의 initialize와 차이점을 이해 할것 */
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
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

    if(h != NULL) //h가 NULL이 아닐때
    {
		freeList(h); //h를 동적할당 해제한다.
    }
  	*h = (headNode*)malloc(sizeof(headNode)); //*h를 동적할당 해준다
	(*h)->first = NULL; //*h의 first를 NULL로 설정
	return 1; // 1로 리턴해줌으로서 함수 종료
}

int freeList(headNode* h){
	
    listNode* p = h->first; //첫번째 노드를 p 에 불러온다
   
    listNode* prev = NULL; //p의 전노드를 임시로 설정한다
	while(p != NULL) { //p가 NULL이 아닐때까지 반복한다
		prev = p; //prev를 p로 설정해 둠으로서 p의 전노드 설정
		p = p->rlink; //p를 다음 노드로 이동시킨 후
		free(prev); //prev의 노드를 할댕 해제를 통해 삭제
	}

    free(h); //h를 동적할당 해제해준다
    return 0; //0을 리턴해줌으로서 함수 종료
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

    listNode* p; //h를 불러올 p노드 선언
	listNode* newNode = (listNode*)malloc(sizeof(listNode)); //새노드 newNode 할당
    p = h->first; //p에 h->first를 불러들여 헤드파일로 설정
	newNode->key = key; //newNode의 key에 key값 대입

	if(h->first != NULL) //헤드노드가 NULL이 아닐시
	{
    	while(p !=NULL) //p가 NULL이 아닐때 반복한다
  	  {
			if(p->rlink == NULL) //p의 다음 노드가 NULL일때
			{
				p->rlink = newNode; //p의 다음노드를 새노드 newNode로 설정
				break;//반복문 종료
			}
   	     p = p->rlink; //p를 다음 노드로 이동
  	  }
	}
	else //헤드노드가 NULL일시
	{
		h->first = newNode; //헤드노드를 newNode로 설정
		newNode->llink = NULL; //전노드를 NULL로 설정
		newNode->rlink = NULL; //다음노드를 NULL로 설정
		return 0; //0리턴함으로서 함수 종료
	}
    
	newNode->llink = p; //newNode의 전 노드를 p로 설정
	newNode->rlink = NULL; //newNode의 다음 노드를 NULL로 설정
	return 0; //0리턴함으로서 함수 종료
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* p;//h를 불러올 p노드 선언
    p = h->first;//p에 h->first를 불러들여 헤드파일로 설정

	if(p->rlink == NULL) //p의 다음노드가 NULL일때, 즉 처음 노드가 마지막 노드일때
	{
		h->first = NULL; //처음 노드를 NULL로 설정
		free(p); //p 동적할당 해제를 통한 삭제
		return 0; //0리턴 해줌으로서 함수 종료
	}
	else //그렇지 않을 경우
	{	
 		while(p !=NULL) //p가 NULL이 아닐때 반복
  		{	
			if(p->rlink == NULL) //p의 다음노드가 NULL일때
			{
				p->llink->rlink = NULL; //p의 전노드의 다음노드를 NULL로 가르킨다
				free(p);//p 동적할당 해제를 통한 삭제
				return 0; //0리턴 해줌으로서 함수 종료
			}
    	    p = p->rlink;//p를 다음노드로 이동

  		}
	}
	
	return 0; //0리턴 해줌으로서 함수 종료
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* newNode = (listNode*)malloc(sizeof(listNode));//새노드 newNode 할당
	newNode -> key = key;//newNode의 key에 key값 대입
	newNode->llink = NULL;//전노드를 NULL로 설정
	newNode->rlink = NULL;//다음노드를 NULL로 설정

	if(h->first == NULL) //처음노드가 없을땨
	{
		h->first = newNode; //newNode를 처음노드로 설정
	}
	else //그렇지 않을경우
	{
		newNode->rlink = h->first; //newNode의 다음노드를 처음노드로 가르킨다
		h->first->llink = newNode; //처음노드의 전노드로 newNode를 가르킨다
		h->first = newNode; //처음노드를 newNode로 설정한다
	}
	return 0; //0리턴해줌으로서 함수종료
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* p;//h를 불러올 p노드 선언
	p = h->first;//p에 h->first를 불러들여 헤드파일로 설정

	if(h->first != NULL) //처음노드가 NULL이 아닐때
	{
		h->first = p->rlink; //처음노드를 다음노드로 설정
		p->llink = NULL; //처음노드의 전노드를 NULL로 가르킨다
	}
	free(p); //p를 동적할당 해제를 통해 삭제

	return 0; //0리턴 해줌으로서 함수 종료
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode *middle; //중간 노드
	listNode *trail; //뒤 노드
	listNode *lead; //앞 노드

	lead = h->first; //h의first를 lead에 불러온다
	middle = NULL; //middle를 NULL로 설정한다

	while(lead != NULL) //lead가 NULL일때 반복문 탈출
	{
		trail = middle; //trail을 중간노드로 둔다
		middle = lead; //중간 노드는 앞의 노드로 바꾼다
		lead = lead->rlink; //앞 노드는 앞노드의 rlink를 타고 다음노드로 간다
		middle->rlink = trail; //중간노드의 rlink는 trail로 바꿈으로서 rlink를 역순으로 설정
		middle->llink = lead; //중간노드의 llink는 lead로 바꿈으로서 llink를 역순으로 설정
	}

	h->first = middle; //lead는 NULL로 바뀌었기 때문에 첫번째 노드는 lead의 이전 노드인 middle로 설정한다.

	return 0; //0리턴을 통한 invertList함수 종료
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* p;//h를 불러올 p노드 선언
	listNode* newNode = (listNode*)malloc(sizeof(listNode));//새노드 newNode 할당
	p = h->first;//p에 h->first를 불러들여 헤드파일로 설정
	newNode->key = key;//newNode의 key에 key값 대입
	newNode->rlink = NULL;//전노드를 NULL로 설정
	newNode->llink = NULL;//다음노드를 NULL로 설정

	if(h->first == NULL) //처음노드가 없을때
	{
		h->first = newNode; //newNode를 처음노드로 설정
	}
	else //그렇지 않을경우
	{
		if(p->key > key) //p의 노드안에 값이 key보다 클 경우
		{
			h->first = newNode; //처음노드를 newNode로 설정
			newNode->rlink = p; //newNode의 다음노드로 p를 가르킨다
		}
		else //그렇지 않을 경우
		{
			while(p !=NULL && p->key < key) //p가 NULL이 아니고 p의 노드안에 값이 key보다 작을 경우 반복
			{
				if(p->rlink == NULL) //p의 다음노드가 NULL일때
				{
					p->rlink = newNode; //p의 다음노드로 newNode를 가르킨다
					newNode->llink = p; //newNode의 전노드로는 p를 가르킨다
					return 0; //0을 리턴해 줌으로서 함수 종료
				}
				p = p->rlink; //p를 다음노드로 이동
			}
			if(p != NULL) //p가 NULL이 아닐때
			{
				newNode->llink = p->llink; //newNode의 전노드를 p의 전노드로 가르킨다
				p->llink->rlink = newNode; //p의 전노드의 다음노드로는 newNode로 가르킨다
				p->llink = newNode; //p의 전노드는 newNode로 가르킨다
				newNode->rlink = p; //newNode의 다음노드로는 p를 가르킨다
			}
		}
	}



	return 0; //0을 리턴해 줌으로서 함수 종료
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* p;//h를 불러올 p노드 선언
	p = h->first;//p에 h->first를 불러들여 헤드파일로 설정

	if(p->key == key) //p의 노드안에 값이 key일경우
	{
		h->first = p->rlink; //첫번째 노드를 p의 다음노드로 설정
		free(p); //p의 동적할당 해제를 통한 삭제
		return 1; //1을 리턴해 줌으로서 함수 종료
	}
	else //그렇지 않을경우
	{
		p = p->rlink; //p를 다음노드로 이동
		while(p !=NULL && p->key != key) //p가 NULL이 아니고 p의 노드안에 값이 key가 아닌경우 반복
		{
			if(p->rlink == NULL && p->key !=key) //p의 다음노드가 NULL이 아니고 p의 노드안에 값이 key가 아닌경우
			{
				return 1; //1을 리턴해 줌으로서 함수 종료
			}
			p = p->rlink; //p를 다음노드로 이동
		}
		if(p->rlink == NULL) //p의 다음노드가 NULL일 경우
		{
			p->llink->rlink = p->rlink; //p의 전노드의 다음노드로 p의 다음노드를 가리킨다. 즉 NULL로 설정
		}
		else //그렇지 않은 경우
		{
			p->llink->rlink = p->rlink; //p의 전노드의 다음노드로 p의 다음노드를 가르킨다
			p->rlink->llink = p->llink; //p의 다음노드의 전노드로는 p의 전노드를 가르킨다
		}
		free(p); //p의 동적할당 해제를 통한 삭제
		return 1; //1을 리턴해 줌으로서 함수 종료
	}
	
	

	return 1; //1을 리턴해 줌으로서 함수 종료
}


