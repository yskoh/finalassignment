#include"UserManagement.h"


void load_file(Person*perArr, int*perNum);
int input_order(void);
int execute_order(int order, Person*perArr, int*perNum);
void print_ui(void);
void view_list(Person * perArr, int * perNum);
void save_file(Person *perArr, int*perNum);
void register_person(Person * perArr, int * perNum);

int main(void){
	int flag = 1;
	int order = 0;
	Person perArr[100];
	int perNum = 0;

	load_file(perArr, &perNum);
	
	while (flag){
		print_ui();
		order = input_order();
		flag = execute_order(order, perArr, &perNum);
	}

	return 0;
}

void print_ui(void){
	printf("1.회원 명단보기 \n");
	printf("2.회원 검색 \n");
	printf("3.회원 등록 \n");
	printf("4.회원 수정\n");
	printf("5.회원 삭제 \n");
	printf("6.파일로 저장하기 \n");
	printf("0. 종료\n");
}

int input_order(void){
	int order;
	printf("수행할 메뉴 번호를 입력하세요 \n");
	scanf_s("%d", &order);
	return order;
}

void view_list(Person * perArr, int * perNum) {
	printf("%-11s %-13s %-28s %s\n", "ID","NAME","ADDRESS","PHONE");
	for (int i = 0; i < *perNum; i++){
		printf("%-11d %-13s %-28s %s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
	}
}


int execute_order(int order, Person*perArr, int*perNum){
	int i;

	if (order == 0){
		return 0;
	}
	else if (order == 1){
		printf("명단 출력\n");
		view_list(perArr, perNum);
	}
	else if (order == 2){
		printf("회원 검색\n");
	}
	else if (order == 3){
		printf("등록 \n");
		register_person(perArr,perNum);
	}
	else if (order == 4){
		printf("수정 \n");
	}
	else if (order == 5){
		printf("삭제 \n");
	}
	else if (order == 6){
		save_file(perArr, perNum);
	}
	else
	{
		printf("재입력하세요 \n");
	}
	return 1;

}

void load_file(Person*perArr, int*perNum){
	char str[256];

	FILE* readFile = fopen("data.txt", "rt");
	fgets(str, sizeof(str), readFile);

	while (fgets(str, sizeof(str), readFile) != NULL)
	{
		perArr[*perNum].id = atoi(strtok(str, "\t"));
		strcpy(perArr[*perNum].name, strtok(NULL, "\t"));
		strcpy(perArr[*perNum].address, strtok(NULL, "\t"));
		strcpy(perArr[*perNum].phone, strtok(NULL, "\n"));
		(*perNum)++;
	}
	fclose(readFile);
}

void save_file(Person *perArr, int*perNum){
	int i;

	FILE* writeFile = fopen("data.txt", "wt");
	fprintf(writeFile, "%s\n", "회원 아이디\t회원이름\t회원주소\t핸드폰 번호");
	for (i = 0; i<*perNum; i++) {
			fprintf(writeFile, "%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
	}
	fclose(writeFile);
}

void register_person(Person * perArr, int * perNum) {

	// 새로운 Person 선언
	Person new_person = { 0, };
	
	//printf("perNum: %d\n", *perNum);

	// id 저장
	int i=0;
	int maxid=0;
	for (i = 0; i < *perNum; i++){
		if (maxid>perArr[i].id){
			maxid = maxid;
		}
		else
		{
			maxid = perArr[i].id;
		}
	}
	new_person.id = maxid + 1;
	
	// Person에 값 입력
	puts("입력할 이름");
	scanf("%s", new_person.name);
	/*
	예외처리용 코드
	while (strlen(new_person.name) == 0)
	{
		printf("다시 입력해주세요\n");
		scanf("%s", new_person.name);
		
	}
	*/
	puts("입력할 주소");
	scanf("%s", new_person.address);
	puts("입력할 전화번호");
	scanf("%s", new_person.phone);
	while (strlen(new_person.phone) != 13){
		printf("***-****-***** 형태로 다시 입력해주세요 \n");
		scanf("%s", new_person.phone);
	}

	while ((new_person.phone[3] != '-') && (new_person.phone[9] != '-')){
			printf("***-****-***** 형태로 다시 입력해주세요 \n");
			scanf("%s", new_person.phone);
		}
	
	while ((new_person.phone[i]<48) && (new_person.phone[i]>57)){
					printf("***-****-***** 형태로 다시 입력해주세요 \n");
					scanf("%s", new_person.phone);
				}

	// perArr[저장할 index]에 Person 저장
	perArr[*perNum] = new_person;


	// 다음 저장할 index 구하기
	(*perNum)++;
}