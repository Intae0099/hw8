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
    
    listNode* p = h->rlink; //임시노드인 p를 h의 rlink를 통해 첫 노드로 이동

	listNode* prev = NULL; //전노드를 NULL로 설정
	while(p != h) { //p가 h가 아닐경우 반복
		prev = p; //전노드로 p를로 설정
		p = p->rlink; //p를 다음노드로 이동
		free(prev); //전노드를 동적할당 해제를 통해 삭제
	}
	free(h); //헤드노드를 동적할당을 통해 삭제

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

    listNode* p = h->rlink; //h의 rlink를 통해 첫번째 노드를 p로 설정
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); //newNode를 새노드를 동적할당한다
    newNode->key = key; //새노드의 값을 key로 설정

    if(p == h) //h의 rlink가 h자신을 가르킬때
    {
        h->rlink = newNode; //첫번째 노드를 newNode로 설정
        h->llink = newNode; //헤드노드의 전 노들로 newNode로 설정
        newNode->rlink = h; //newNode의 rlink를 h로 설정
        newNode->llink = h; //newNode의 llink를 h로 설정
        return 1;
    }
    else //그렇지 않을 경우
    {
        while(p->rlink != h) //p의 rlink가 h가 아닐경우 반복
        {
            p = p->rlink; //p를 rlink를 통해 다음노드로 이동
        }
        p->rlink = newNode; //p의 rlink를 newNode로 설정
        newNode->llink = p; //newNode의 llink를 p로 설정
        newNode->rlink = h; //마지막 노드의 다음노드는 h로 가르켜야 하므로 newNode의 rlink를 h로 설정
        h->llink = newNode; //h노드의 llink를 newNode로 설정
    }
    
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

    listNode* p = h->rlink; //h노드의 rlink를 통해 첫노드를 p로 설정
    if(p->rlink == h && p->llink == h) //p의 rlink와 p의 llink가 h노드인 경우 즉 첫번째 노드일 경우
    {
        h->rlink = h; //h의 rlink를 h로 지정
        h->llink = h; //h의 llink를 h로 지정
        free(p); //p노드를 동적할당 해제를 통해 삭제
        return 1;
    }
    else //그렇지 않을 경우
    {
        while(p->rlink != h) //p의rlink가 h노드가 아닐경우 반복한다
        {
            p = p->rlink; //p를 p의 rlink로 설정함으로서 다음노드로 이동
        }
        if(p->rlink == h) //p의 rlink가 h일 경우 즉 마지막 노드일 경우
        {
            p->llink->rlink = h; //p의 rlink의 rlink를 h로 설정 즉 마지막 노드의 전노드의 rlink를 h로 설정
            h->llink = p->llink; //h노드의 llink를 p의 전노드로 설정
            free(p); //p노드 동적할당 해제를 통해 삭제
            return 1;
        }
    }
   
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

    listNode* p = h->rlink; //h노드의 rlink를 통해 첫노드를 p로 설정
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); //newNode를 새노드를 동적할당한다
    newNode->key = key; //새노드의 값을 key로 설정


    if(p == h) //p노드가 h일 경우 즉 첫번째 노드일 경우
    {
        h->rlink = newNode; //h의 rlink를 newNode로 설정
        h->llink = newNode; //h의 rlink를 newNode로 설정
        newNode->rlink = h; //newNode의 rlink를 h로 설정
        newNode->llink = h; //newNode의 llink를 h로 설정
        return 1;
    }
    else //그렇지 않을 경우
    {
        newNode->rlink = p; //newNode의 rlink를 p로 설정
        newNode->llink = h; //newNode의 llink를 h로 설정
        p->llink = newNode; //p의 llink를 newNode로 설정
        h->rlink = newNode; //h의 rlink를 newNode로 설정
    }
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

    listNode* p = h->rlink; //h노드의 rlink를 통해 첫노드를 p로 설정

    if(p->rlink == h) //p의 rlink가 h일 경우 즉 첫 노드일 경우
    {
        h->rlink = h; //h의 rlink를 h로 설정
        h->llink = h; //h의 llink를 h로 설정
        free(p); //p노드 동적할당 해제를 통해 첫번째 노드 삭제
        return 1; //1리턴을 통해 함수종료
    }
    else //그렇지 않을 경우
    {
        p->rlink->llink = p->llink; //p의 다음노드의 llink를 p의 전노드로 설정
        p->llink->rlink = p->rlink; //p의 전노드의 rlink를 p의 다음노드로 설정
        free(p); //p노드 동적할당 해제를 통해 첫번째 노드 삭제
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

    listNode* p = h->rlink; //h노드의 rlink를 통해 첫노드를 p로 설정
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); //newNode를 새노드를 동적할당한다
    newNode->key = key; //새노드의 값을 key로 설정

    if(p->key > key) //p노드안의 값이 key보다 클경우
    {
        newNode->rlink = p; //newNode의 rlink를 p로 설정
        newNode->llink = p->llink; //newNode의 llink를 p의 전노드로 설정
        p->llink->rlink = newNode; //p의 전노드의 rllink를 newNode로 설정
        p->llink = newNode; //p의 llink를 newNode로 설정
        return 0; //0리턴을 통해 함수 종료
    }
    else //그렇지 않을경우
    {
        while(p->rlink != h && p->key < key) //p의 rlink가 h가 아닐경우와 p노드안의 값이 key보다 작을 경우
        {
            p = p->rlink; //p를 다음노드로 이동
        }
        if(p->rlink == h) //p의 rlink가 h일 경우 즉 마지막 노드일 경우
        {
            newNode->llink = p; //newNode의 llink를 p로 설정
            newNode->rlink = h; //newNode의 rlink를 h로 설정
            p->rlink = newNode; //p의 rlink를 newNode로 설정
            h->llink = newNode; //h의 llink를 newNode로 설정
            return 0;
        }
        else //그렇지 않을 경우
        {
            newNode->rlink = p; //newNode의 rlink를 p로 설정
            newNode->llink = p->llink; //newNode의 llink를 p의 전노드로 설정
            p->llink->rlink = newNode; //p의 전노드의 rlink를 newNode로 설정
            p->llink = newNode; //p의 llink를 newNode로 설정
            return 0; //0을 리턴해줌으로서 함수 종료
        }
    }

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

    listNode* p = h->rlink; //h노드의 rlink를 통해 첫노드를 p로 설정

    if(p->key == key) //p안에 값이 key일 경우 즉 첫번째 노드가 삭제할 노드일 경우
    {
        p->rlink->llink = p->llink; //p의 다음노드의 llink를 p의 전노드로 설정
        p->llink->rlink = p->rlink; //p의 전노드의 rlink를 p의 다음노드로 설정
        free(p); //p노드 동적할당 해제를 통해 첫번째 노드 삭제
        return 0;
    }
    else //그렇지 않을 경우
    {  
        while(p->rlink != h&& p->key != key) //p의 rlink가 h가 아닐경우와 p노드 안의 값이 key가 아닌경우
        {
            p = p->rlink; //p를 다음노드로 이동
        }
        if(p->key !=key && p->rlink == h) //p노드안의 값이 key가 아닐경우와 p의 rlink가 h일 경우 즉 오류
        {
            return 0; //0을 리턴해줌으로서 함수 종료
        }
        else if(p->key == key) //p노드안의 값이 key일경우
        {
            p->rlink->llink = p->llink; //p의 다음노드의 llink를 p의 전노드로 설정
            p->llink->rlink = p->rlink; //p의 전노드의 rlink를 p의 다음노드로 설정
        }
        free(p);//p노드 동적할당 해제를 통해 첫번째 노드 삭제
    }
	return 0;
}


