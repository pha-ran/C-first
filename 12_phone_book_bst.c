#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD	100

//#define MAXNUM	100		// maximum number of phonebook entries
//#define EOL		'.'		// define end of input

struct tnode {
	char *name;
	struct plist {
		int id;				// 전화부 id
		char *item;			// 전화부 item
		struct plist *next;
	} *pb;
	struct tnode *left;
	struct tnode *right;
};

/* 전화부 ID */
enum PID { MOBILE = 1, HOME, OFFICE, FAX, ETC, EMAIL, ADDR, MEMO };

char *sItem[] = {
	"휴대폰", "집전화", "사무실전화", "팩스", "기타", "이메일", "주소", "메모"
};

struct tnode *createNode();		// create node and initialize
struct plist *createList();		// create list and initialize
struct tnode *addTree(struct tnode *, struct tnode *);	// add a node into binary tree
void addList(struct plist **pstart, struct plist *pj);	// add a list in increasing order of id
void treeprint(struct tnode *);
int dispNode(struct tnode *p, int opt);
int getmnum();
char *strdupl(char *);
// Requirement #3
struct tnode *search(struct tnode *root, char *key);

int main()
{
	struct tnode *root, *pn;
	struct plist *pi, **pstart;
	char word[MAXWORD];
	int m, n;

	root = NULL;

	do {
		printf("\n\t===전화번호부====\n\n"
			"\t1. 추가\n"
			"\t2. 전체보기\n"
			"\t3. 이름으로 검색하기\n"
			"\t4. 종료\n");
		while ((m = getmnum()) <= 0 || 4 < m);
		switch (m) {
		case 1:
			pn = createNode();                //구조체의 메모리 할당
			printf("\n이름을 입력하세요: ");
			scanf(" %[^\n]", word);		// get line (after skipping white space)
			pn->name = strdupl(word);		// alloc and copy name, 입력한 이름으로 전화번호를 저장할 구조체 1개 생성
			pn->pb = NULL;
			pstart = &pn->pb;				// list start
			do {
				printf("\n선택하세요\n(0:종료 1:휴대폰 2:집전화 3:사무실전화 "
					"4:팩스 5:기타 6:이메일 7:주소 8:메모): ");
				scanf_s(" %d", &n);
				if (n < 0 || 8 < n) continue;
				if (!n) break;
				pi = createList();
				pi->id = n;
				printf("\n%s 내용을 입력하세요: ", sItem[n - 1]);
				scanf(" %[^\n]", word);
				pi->item = strdupl(word);
				addList(pstart, pi);
			} while (n);
			root = addTree(root, pn);
			break;
		case 2:	// 전체보기
			treeprint(root);
			printf("\n");
			break;
		case 3: //검색하기
			printf("\n\t검색할 이름을 입력하세요: ");
			scanf(" %[^\n]", word);
			root = search(root, word);
			break;
		default:
			return 0;
			break;
		}
	} while (m);

	return 0;
}

/* getmnum: get menu number */
int getmnum() {
	int m;
	printf("\n\t원하는 메뉴를 선택하세요: ");
	scanf_s(" %d", &m);
	return m;
}

/* addTree: add a node at or below p
			print error message if there is same name */
struct tnode *addTree(struct tnode *p, struct tnode *r) {
	if (p == NULL)
	{
		return r; //p(root) = r 로 시작
	}
	else
	{
		struct tnode *current = p;
		int LR;

		do {
			LR = strcmp(r->name, current->name); //r이 현재 탐색중인 노드의 이름보다 큰지 작은지 판별

			if (LR == 0) //새 노드의 이름과 같은 이름의 노드가 존재
			{
				printf("\n같은 이름이 존재합니다.\n");
				break;
			}
			else if (LR < 0) //같은 이름의 노드가 없고 r이 더 작을때
			{
				if (current->left == NULL)
				{
					current->left = r;
					LR = 0;
				}
				else
				{
					current = current->left;
				}
			}
			else //같은 이름의 노드가 없고 r이 더 클때
			{
				if (current->right == NULL)
				{
					current->right = r;
					LR = 0;
				}
				else
				{
					current = current->right;
				}
			}
		} while (LR != 0);
	}
	return p;
}

/* addList: add a list at or next pi in increasing order of id */
void addList(struct plist **pstart, struct plist *pj) {
	if (*pstart == NULL) //리스트(pb가 가리키는 포인터)가 비어있을때
	{
		*pstart = pj;
	}
	else
	{
		struct plist *current = *pstart;

		do {
			if (current->id < pj->id) //새로 추가한 정보의 ID가 첫 리스트노드 ID보다 클때
			{
				if (current->next == NULL)
				{
					current->next = pj;
					break;
				}
				else
				{
		        	if (current->next->id > pj->id) //리스트의 다음 노드보다는 작을때 (사이일때)
					{
						pj->next = current->next;
						current->next = pj;
						break;
					}
					else //기준 노드를 한개 넘어감
					{
						current = current->next;
					}
				}
			}
			else if (current->id > pj->id) //새로 추가한 정보의 ID가 첫 리스트노드 ID보다 작을때
			{
				pj->next = current;
				*pstart = pj;
				break;
			}
			else //새로 추가한 정보의 ID가 이미 존재할때
			{
				current = pj;
				break;
			}
		} while (1);
	}
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		dispNode(p, 0);
		treeprint(p->right);
	}
}

/* dispNode: display a node including list
			(opt=1) display with line number, return number of items */
int dispNode(struct tnode *p, int opt) {
	struct plist *displist = p->pb;
	int noi = 0;

	printf("\n\t이름 : %s", p->name);

	while (displist != NULL)
	{
		printf("\n\t    %s : %s(id : %d)", sItem[(displist->id) - 1], displist->item, displist->id);
		displist = displist->next;
		noi += 1;
	}

	return noi;
}

struct tnode *search(struct tnode *root, char *key) //이름(key)로 연락처 검색하기
{
	if (root == NULL)
	{
		printf("\n\t추가된 연락처가 없습니다.\n");

		return root;
	}

	struct tnode *searchn = root;
	struct plist *searchl = root->pb;
	int LR;

	do {
		LR = strcmp(key, searchn->name); //key가 현재 탐색중인 노드의 이름보다 큰지 작은지 판별

		if (LR == 0) //새 노드의 이름과 같은 이름의 노드가 존재
		{
			printf("\n\t검색 완료: %s", searchn->name);

			searchl = searchn->pb;

			while (searchl != NULL)
			{
				printf("\n\t    %s : %s(id : %d)", sItem[(searchl->id) - 1], searchl->item, searchl->id);
				searchl = searchl->next;
			}
		}
		else if (LR < 0) //같은 이름의 노드가 없고 key가 더 작을때
		{
			if (searchn->left == NULL)
			{
				printf("\n\t해당 연락처는 존재하지 않습니다.\n");
				LR = 0;
			}
			else
			{
				searchn = searchn->left;
			}
		}
		else //같은 이름의 노드가 없고 key가 더 클때
		{
			if (searchn->right == NULL)
			{
				printf("\n\t해당 연락처는 존재하지 않습니다.\n");
				LR = 0;
			}
			else
			{
				searchn = searchn->right;
			}
		}
	} while (LR != 0);

	return root;
}

/* createNode: make and initialize a tnode */
struct tnode *createNode() {
	struct tnode *p;
	p = (struct tnode *) malloc(sizeof(struct tnode));
	p->left = p->right = NULL;
	return p;
}

/* createList: make and initialize a list */
struct plist *createList() {
	struct plist *p;
	p = (struct plist *) malloc(sizeof(struct plist));
	p->next = NULL;
	return p;
}

/* strdupl: make a duplicate of a string */
char *strdupl(char *s) {
	char *p;
	p = (char *)malloc(strlen(s) + 1);		// +1 for '\0'
	if (p != NULL)
		strcpy(p, s);
	return p;
}