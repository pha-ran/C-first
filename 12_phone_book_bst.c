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
		int id;				// ��ȭ�� id
		char *item;			// ��ȭ�� item
		struct plist *next;
	} *pb;
	struct tnode *left;
	struct tnode *right;
};

/* ��ȭ�� ID */
enum PID { MOBILE = 1, HOME, OFFICE, FAX, ETC, EMAIL, ADDR, MEMO };

char *sItem[] = {
	"�޴���", "����ȭ", "�繫����ȭ", "�ѽ�", "��Ÿ", "�̸���", "�ּ�", "�޸�"
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
		printf("\n\t===��ȭ��ȣ��====\n\n"
			"\t1. �߰�\n"
			"\t2. ��ü����\n"
			"\t3. �̸����� �˻��ϱ�\n"
			"\t4. ����\n");
		while ((m = getmnum()) <= 0 || 4 < m);
		switch (m) {
		case 1:
			pn = createNode();                //����ü�� �޸� �Ҵ�
			printf("\n�̸��� �Է��ϼ���: ");
			scanf(" %[^\n]", word);		// get line (after skipping white space)
			pn->name = strdupl(word);		// alloc and copy name, �Է��� �̸����� ��ȭ��ȣ�� ������ ����ü 1�� ����
			pn->pb = NULL;
			pstart = &pn->pb;				// list start
			do {
				printf("\n�����ϼ���\n(0:���� 1:�޴��� 2:����ȭ 3:�繫����ȭ "
					"4:�ѽ� 5:��Ÿ 6:�̸��� 7:�ּ� 8:�޸�): ");
				scanf_s(" %d", &n);
				if (n < 0 || 8 < n) continue;
				if (!n) break;
				pi = createList();
				pi->id = n;
				printf("\n%s ������ �Է��ϼ���: ", sItem[n - 1]);
				scanf(" %[^\n]", word);
				pi->item = strdupl(word);
				addList(pstart, pi);
			} while (n);
			root = addTree(root, pn);
			break;
		case 2:	// ��ü����
			treeprint(root);
			printf("\n");
			break;
		case 3: //�˻��ϱ�
			printf("\n\t�˻��� �̸��� �Է��ϼ���: ");
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
	printf("\n\t���ϴ� �޴��� �����ϼ���: ");
	scanf_s(" %d", &m);
	return m;
}

/* addTree: add a node at or below p
			print error message if there is same name */
struct tnode *addTree(struct tnode *p, struct tnode *r) {
	if (p == NULL)
	{
		return r; //p(root) = r �� ����
	}
	else
	{
		struct tnode *current = p;
		int LR;

		do {
			LR = strcmp(r->name, current->name); //r�� ���� Ž������ ����� �̸����� ū�� ������ �Ǻ�

			if (LR == 0) //�� ����� �̸��� ���� �̸��� ��尡 ����
			{
				printf("\n���� �̸��� �����մϴ�.\n");
				break;
			}
			else if (LR < 0) //���� �̸��� ��尡 ���� r�� �� ������
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
			else //���� �̸��� ��尡 ���� r�� �� Ŭ��
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
	if (*pstart == NULL) //����Ʈ(pb�� ����Ű�� ������)�� ���������
	{
		*pstart = pj;
	}
	else
	{
		struct plist *current = *pstart;

		do {
			if (current->id < pj->id) //���� �߰��� ������ ID�� ù ����Ʈ��� ID���� Ŭ��
			{
				if (current->next == NULL)
				{
					current->next = pj;
					break;
				}
				else
				{
		        	if (current->next->id > pj->id) //����Ʈ�� ���� ��庸�ٴ� ������ (�����϶�)
					{
						pj->next = current->next;
						current->next = pj;
						break;
					}
					else //���� ��带 �Ѱ� �Ѿ
					{
						current = current->next;
					}
				}
			}
			else if (current->id > pj->id) //���� �߰��� ������ ID�� ù ����Ʈ��� ID���� ������
			{
				pj->next = current;
				*pstart = pj;
				break;
			}
			else //���� �߰��� ������ ID�� �̹� �����Ҷ�
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

	printf("\n\t�̸� : %s", p->name);

	while (displist != NULL)
	{
		printf("\n\t    %s : %s(id : %d)", sItem[(displist->id) - 1], displist->item, displist->id);
		displist = displist->next;
		noi += 1;
	}

	return noi;
}

struct tnode *search(struct tnode *root, char *key) //�̸�(key)�� ����ó �˻��ϱ�
{
	if (root == NULL)
	{
		printf("\n\t�߰��� ����ó�� �����ϴ�.\n");

		return root;
	}

	struct tnode *searchn = root;
	struct plist *searchl = root->pb;
	int LR;

	do {
		LR = strcmp(key, searchn->name); //key�� ���� Ž������ ����� �̸����� ū�� ������ �Ǻ�

		if (LR == 0) //�� ����� �̸��� ���� �̸��� ��尡 ����
		{
			printf("\n\t�˻� �Ϸ�: %s", searchn->name);

			searchl = searchn->pb;

			while (searchl != NULL)
			{
				printf("\n\t    %s : %s(id : %d)", sItem[(searchl->id) - 1], searchl->item, searchl->id);
				searchl = searchl->next;
			}
		}
		else if (LR < 0) //���� �̸��� ��尡 ���� key�� �� ������
		{
			if (searchn->left == NULL)
			{
				printf("\n\t�ش� ����ó�� �������� �ʽ��ϴ�.\n");
				LR = 0;
			}
			else
			{
				searchn = searchn->left;
			}
		}
		else //���� �̸��� ��尡 ���� key�� �� Ŭ��
		{
			if (searchn->right == NULL)
			{
				printf("\n\t�ش� ����ó�� �������� �ʽ��ϴ�.\n");
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