#include <stdio.h>
#include <time.h>

int user_id = 12345;
int user_pwd = 98760;
int admin_id = 56789;
int admin_pwd = 87654;
int d = 10;  //������ ����, �⺻ �����̽ð� 10�� ����
int dr = 10;  //������ ���� ���� (������ �޴����� ���°��� ������ �ڿ��� ������ ���°����� ����)
int id_list[3];  //�������� ���̵� ����
int pwd_list[3];  //�������� ��й�ȣ�� ����
int NoU = 0;  //������ ���� ���� ��

void login();
int  verify(int uid, int pwd);
void wait1s();
void addUser();
void delUser();
void setDelay();
void back();
void admin_menu();

int main()
{
	printf("�α��� ���α׷��Դϴ�.\n");

	login();

	return 0;
}

void login()  //�α��� �޴�
{
	int login_input_id, login_input_pwd;

	printf("\n-�α��� �޴�- \n���̵�� ��й�ȣ�� �Է��ϼ���. \n");
	printf("����� ID : ");
	scanf_s("%d", &login_input_id);
	printf("��й�ȣ : ");
	scanf_s("%d", &login_input_pwd);

	if (verify(login_input_id, login_input_pwd) != 0)  //�α��ο� �����ϸ�, �α��� �޴��� �ٽ� ����
	{
		login();
	}
}

int verify(int uid, int pwd)  //���̵�� ����� Ȯ��
{
	static int trial = 0;
	int i;

	if ((uid == admin_id) && (pwd == admin_pwd))
	{
		printf("\n������ �޴��� �����մϴ�. \n");
		trial = 0;      //����Ƚ�� �ʱ�ȭ
		d = dr;         //������ ����
		admin_menu();
		return 0;
	}

	for (i = 1; i <= NoU; i++)   //������ ���̵�� �α��� ������
	{
		if (uid == id_list[i - 1] && pwd == pwd_list[i - 1])
		{
			printf("\n���������� �α��� �Ǿ����ϴ�. %d ��. \n", id_list[i - 1]);

			return 0;
		}
	}

	if ((uid == user_id) && (pwd == user_pwd))  //�⺻ ���̵�� �α��� ������
	{
		printf("���������� �α��� �Ǿ����ϴ�. \n");
		trial = 0;       //����Ƚ�� �ʱ�ȭ
		d = dr;          //������ ����
		return 0;
	}

	else  //���̵� �Ǵ� ����� Ʋ���� ���
	{
		trial += 1;

		if (trial < 5)
		{
			printf("����� ID �Ǵ� ��й�ȣ ���� (%dȸ) \n", trial);
			return trial;  //���� Ƚ���� ����
		}
		else
		{
			printf("5ȸ ������ ���Ͽ� %d �ʰ� �����մϴ�. \n", d);
			wait1s();
			d *= 2;  //�����̸� �ι�� ����
			trial = 0;  //���� Ƚ���� �ʱ�ȭ
			login();  //�α��� �޴��� ����� (�α��� �Լ����� �ٽ� verify�Լ��� �����ϰ� �Ǿ� �����Ƿ�, ���ϰ��� ���� ����)
		}
	}
}

void wait1s()  //������ �����̸�ŭ ���
{
	clock_t start = clock();
	while (clock() - start < ((CLOCKS_PER_SEC)* d))
		;
}

void addUser()
{
	int i, add_input_id, add_input_pwd, repwd;

	printf("\n[���� ���� ���] \n");

	for (i = 1; i <= NoU; i++) //���� ����ŭ ���̵� ����� ���
	{
		printf("%d. %d \n", i, id_list[i - 1]);
	}
	if (NoU == 0)  //������ ������ ���� ���
	{
		printf("������ �����ϴ�. \n");
	}

	if (NoU == 3)  //������ 3������ �� á�� ���
	{
		printf("\n[!] ����ڸ� �߰��� �� �����ϴ�. \n");
	}
	else
	{
		printf("\n�߰��� ����� ID�� �Է��ϼ���. : ");
		scanf_s("%d", &add_input_id);
		id_list[NoU] = add_input_id;

		do
		{
			printf("��й�ȣ�� �Է��ϼ���. : ");
			scanf_s("%d", &add_input_pwd);
			printf("��й�ȣ�� Ȯ���մϴ�. Ʋ�� ���, ��й�ȣ�� �ٽ� �����ؾ� �մϴ�. \n�ٽ� �ѹ� �Է��ϼ���. : ");
			scanf_s("%d", &repwd);
		} while (add_input_pwd != repwd);  //�Է��� ��й�ȣ�� ���Է� ��й�ȣ�� ���������� �ݺ�

		pwd_list[NoU] = add_input_pwd;

		printf("\n���� �Ϸ�! \n");

		NoU += 1;  //��ü ���� ���� 1 ������Ŵ
	}
	
	admin_menu();  //������ �޴��� ���ư���
}

void delUser()
{
	int i, input_del;

	printf("\n[���� ���� ���] \n");

	for (i = 1; i <= NoU; i++) //���� ����ŭ ���̵� ����� ���
	{
		printf("%d. %d \n", i, id_list[i - 1]);
	}
	
	if (NoU == 0)  //������ ������ ���� ���
	{
		printf("������ �����ϴ�. \n");
	}
	else
	{
		do
		{
			printf("\n������ ����� ��ȣ�� �Է��ϼ���. : ");
			scanf_s("%d", &input_del);
		}   while ((input_del <= 0) || (input_del > NoU));  //�����ϴ� ������ ��ȣ�� ���������� �ݺ�

		if (input_del == 1)
		{
			id_list[0] = -1;
			pwd_list[0] = -1;
			NoU -= 1;

			if (NoU == 1)
			{
				id_list[0] = id_list[1];
				pwd_list[0] = pwd_list[1];
			}
			else if (NoU == 2)
			{
				id_list[0] = id_list[1];
				pwd_list[0] = pwd_list[1];
				id_list[1] = id_list[2];
				pwd_list[1] = pwd_list[2];
			}
		}
		else if (input_del == 2)
		{
			id_list[1] = -1;
			pwd_list[1] = -1;
			NoU -= 1;

			if (NoU == 2)
			{
				id_list[1] = id_list[2];
				pwd_list[1] = pwd_list[2];
			}
		}
		else if (input_del == 3)
		{
			id_list[2] = -1;
			pwd_list[2] = -1;
			NoU -= 1;
		}
	}

	admin_menu();  //������ �޴��� ���ư���
}

void setDelay()
{
	int input_d;
	printf("\n���ð� �Է� (���� %d��) : ", d);
	scanf_s("%d", &input_d);
	dr = input_d;                         //���� �����̸� �Է��� ����ŭ ����
	d = dr;                             //������ ����
	printf("\n�����Ǿ����ϴ�.\n");

	admin_menu();  //������ �޴��� ���ư���
}

void back()
{
	login();
}

void admin_menu()
{
	int input_menu;

	printf("\n**** ������ �޴� ****\n1. ����� �߰� \n2. ����� ���� \n3. ���ð� ���� \n4. ���� \n\n���ϴ� �޴��� �Է��ϼ��� : ");
	scanf_s("%d", &input_menu);
	if (input_menu == 1)
	{
		addUser();
	}
	else if (input_menu == 2)
	{
		delUser();
	}
	else if (input_menu == 3)
	{
		setDelay();
	}
	else if (input_menu == 4)
	{
		back(); // ����� �α��� ȭ������ �̵�
	}
	else
	{
		printf("\n�߸� �����̽��ϴ�. \n");

		admin_menu();  //�ٸ� ���ڸ� ���� ��� ������ �޴��� �����
	}
}