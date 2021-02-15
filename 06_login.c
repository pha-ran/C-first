#include <stdio.h>
#include <time.h>

int user_id = 12345;
int user_pwd = 98760;
int admin_id = 56789;
int admin_pwd = 87654;
int d = 10;  //딜레이 변수, 기본 딜레이시간 10초 설정
int dr = 10;  //딜레이 리셋 변수 (관리자 메뉴에서 리셋값을 설정한 뒤에는 설정된 리셋값으로 리셋)
int id_list[3];  //계정들의 아이디를 저장
int pwd_list[3];  //계정들의 비밀번호를 저장
int NoU = 0;  //계정을 만든 유저 수

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
	printf("로그인 프로그램입니다.\n");

	login();

	return 0;
}

void login()  //로그인 메뉴
{
	int login_input_id, login_input_pwd;

	printf("\n-로그인 메뉴- \n아이디와 비밀번호를 입력하세요. \n");
	printf("사용자 ID : ");
	scanf_s("%d", &login_input_id);
	printf("비밀번호 : ");
	scanf_s("%d", &login_input_pwd);

	if (verify(login_input_id, login_input_pwd) != 0)  //로그인에 실패하면, 로그인 메뉴를 다시 실행
	{
		login();
	}
}

int verify(int uid, int pwd)  //아이디와 비번을 확인
{
	static int trial = 0;
	int i;

	if ((uid == admin_id) && (pwd == admin_pwd))
	{
		printf("\n관리자 메뉴를 실행합니다. \n");
		trial = 0;      //실패횟수 초기화
		d = dr;         //딜레이 리셋
		admin_menu();
		return 0;
	}

	for (i = 1; i <= NoU; i++)   //생성된 아이디로 로그인 성공시
	{
		if (uid == id_list[i - 1] && pwd == pwd_list[i - 1])
		{
			printf("\n성공적으로 로그인 되었습니다. %d 님. \n", id_list[i - 1]);

			return 0;
		}
	}

	if ((uid == user_id) && (pwd == user_pwd))  //기본 아이디로 로그인 성공시
	{
		printf("성공적으로 로그인 되었습니다. \n");
		trial = 0;       //실패횟수 초기화
		d = dr;          //딜레이 리셋
		return 0;
	}

	else  //아이디 또는 비번이 틀렸을 경우
	{
		trial += 1;

		if (trial < 5)
		{
			printf("사용자 ID 또는 비밀번호 오류 (%d회) \n", trial);
			return trial;  //실패 횟수를 리턴
		}
		else
		{
			printf("5회 오류로 인하여 %d 초간 정지합니다. \n", d);
			wait1s();
			d *= 2;  //딜레이를 두배로 설정
			trial = 0;  //실패 횟수를 초기화
			login();  //로그인 메뉴를 재실행 (로그인 함수에서 다시 verify함수를 실행하게 되어 있으므로, 리턴값을 넣지 않음)
		}
	}
}

void wait1s()  //설정된 딜레이만큼 대기
{
	clock_t start = clock();
	while (clock() - start < ((CLOCKS_PER_SEC)* d))
		;
}

void addUser()
{
	int i, add_input_id, add_input_pwd, repwd;

	printf("\n[현재 계정 목록] \n");

	for (i = 1; i <= NoU; i++) //유저 수만큼 아이디 목록을 출력
	{
		printf("%d. %d \n", i, id_list[i - 1]);
	}
	if (NoU == 0)  //생성된 계정이 없을 경우
	{
		printf("계정이 없습니다. \n");
	}

	if (NoU == 3)  //유저가 3명으로 꽉 찼을 경우
	{
		printf("\n[!] 사용자를 추가할 수 없습니다. \n");
	}
	else
	{
		printf("\n추가할 사용자 ID를 입력하세요. : ");
		scanf_s("%d", &add_input_id);
		id_list[NoU] = add_input_id;

		do
		{
			printf("비밀번호를 입력하세요. : ");
			scanf_s("%d", &add_input_pwd);
			printf("비밀번호를 확인합니다. 틀릴 경우, 비밀번호를 다시 설정해야 합니다. \n다시 한번 입력하세요. : ");
			scanf_s("%d", &repwd);
		} while (add_input_pwd != repwd);  //입력한 비밀번호와 재입력 비밀번호가 같을때까지 반복

		pwd_list[NoU] = add_input_pwd;

		printf("\n가입 완료! \n");

		NoU += 1;  //전체 유저 수를 1 증가시킴
	}
	
	admin_menu();  //관리자 메뉴로 돌아가기
}

void delUser()
{
	int i, input_del;

	printf("\n[현재 계정 목록] \n");

	for (i = 1; i <= NoU; i++) //유저 수만큼 아이디 목록을 출력
	{
		printf("%d. %d \n", i, id_list[i - 1]);
	}
	
	if (NoU == 0)  //생성된 계정이 없을 경우
	{
		printf("계정이 없습니다. \n");
	}
	else
	{
		do
		{
			printf("\n삭제할 사용자 번호를 입력하세요. : ");
			scanf_s("%d", &input_del);
		}   while ((input_del <= 0) || (input_del > NoU));  //존재하는 유저의 번호를 누를때까지 반복

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

	admin_menu();  //관리자 메뉴로 돌아가기
}

void setDelay()
{
	int input_d;
	printf("\n대기시간 입력 (현재 %d초) : ", d);
	scanf_s("%d", &input_d);
	dr = input_d;                         //리셋 딜레이를 입력한 수만큼 설정
	d = dr;                             //딜레이 리셋
	printf("\n설정되었습니다.\n");

	admin_menu();  //관리자 메뉴로 돌아가기
}

void back()
{
	login();
}

void admin_menu()
{
	int input_menu;

	printf("\n**** 관리자 메뉴 ****\n1. 사용자 추가 \n2. 사용자 삭제 \n3. 대기시간 설정 \n4. 종료 \n\n원하는 메뉴를 입력하세요 : ");
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
		back(); // 종료시 로그인 화면으로 이동
	}
	else
	{
		printf("\n잘못 누르셨습니다. \n");

		admin_menu();  //다른 숫자를 누를 경우 관리자 메뉴를 재실행
	}
}