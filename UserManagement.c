#include"UserManagement.h"


void load_file(Person*perArr, int*perNum);
int input_order(void);
int execute_order(int order, Person*perArr, int*perNum);
void print_ui(void);
void view_list(Person * perArr, int * perNum);
void save_file(Person *perArr, int*perNum);
void register_person(Person * perArr, int * perNum);
void find_person(Person *perArr, int*perNum);
void revise_person(Person *perArr, int*perNum);
void delete_person(Person *perArr, int *perNum);
int main(void){
	int flag = 1;
	int order = 0;
	Person perArr[100];
	int perNum = 0;

	load_file(perArr, &perNum);
	
	while (flag){
		print_ui();
		fflush(stdin);
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

	if (order == 0){
		int selection;
		int n=1;
		while(n==1){
		printf("종료하기 전 저장하시겠습니까?\n1.yes 2.no\n");
		scanf("%d", &selection);
		if (selection == 1){
			save_file(perArr,perNum);
			n = 0;
			return 0;
		}
		else if (selection == 2){
			n = 0;
			return 0;
		}
		else{
			printf("잘못된 입력입니다. 다시 1아니면 2를 입력하여 주세요\n");
			n = 1;
		}
	}
		
	}
	else if (order == 1){
		printf("명단 출력\n");
		view_list(perArr, perNum);
	}
	else if (order == 2){
		printf("회원 검색\n");
		find_person(perArr,perNum);
	}
	else if (order == 3){
		printf("등록 \n");
		register_person(perArr,perNum);
	}
	else if (order == 4){
		printf("수정 \n");
		revise_person(perArr, perNum);
	}
	else if (order == 5){
		printf("삭제 \n");
		delete_person(perArr, perNum);
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
	getchar();

	puts("입력할 주소");
	fgets(new_person.address, 100, stdin);
	// 개행지우기
	for (i = 0; i < 100; i++){
		if (new_person.address[i] == '\n') {
			new_person.address[i] = '\0';
			break;
		}
	}

	printf("입력할 전화번호");
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

void find_person(Person *perArr, int*perNum){
	int opt = 0;
	int i = 0;
	int flag = 0;
	char search_name[10];
	char search_address[100];
	char search_phone[30];
	int search_id;

	printf("어떤 정보로 검색하시겠습니까? \n");
	printf("1. 학번\n2. 이름\n3. 주소\n4.폰 번호\n");
	scanf("%d", &opt);

	switch (opt){
	case 1:
		printf("학번을 입력하세요\n");
		scanf("%d", &search_id);
		for (i = 0; i < *perNum; i++){
			if (perArr[i].id== search_id)
			{
				flag = 1;
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
			}
		}
		break;
	case 2:
		printf("이름을 입력하세요\n");
		scanf("%s", search_name);
		for (i = 0; i < *perNum; i++){
			if (strcmp(perArr[i].name, search_name) == 0)
			{
				flag = 1;
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
			}
		}
		break;
	case 3:
		printf("주소를 입력하세요\n");
		getchar();
		fgets(search_address,100,stdin);
		//printf("input: %d\n" + (search_address));
		
		search_address[strlen(search_address) - 1] = '\0';


		/*for (i = 0; search_address[i] != '\0'; i++) {
			printf("%d: %c %d \n", i, search_address[i], search_address[i]);
		}*/


		//하나하나 비교하기
		for (i = 0; i < *perNum; i++){
			//printf("---in: %s[size: %d], per[%d]: %s[size: %d]\n", search_address, strlen(search_address), i, perArr[i].address, strlen(perArr[i].address));
			
			if (strcmp(perArr[i].address, search_address) == 0)
			{
				flag = 1;
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
			}
		}
		break;
	case 4:
		printf("폰 번호를 입력하세요\n");
		scanf("%s", search_phone); 
		while (strlen(search_phone) != 13){
			printf("***-****-***** 형태로 다시 입력해주세요 \n");
			scanf("%s", search_phone);
		}

		while ((search_phone[3] != '-') && (search_phone[8] != '-')){
			printf("***-****-***** 형태로 다시 입력해주세요 \n");
			scanf("%s", search_phone);
		}

		while ((search_phone[i]<=48) && (search_phone[i]>57)){
			printf("***-****-***** 형태로 다시 입력해주세요 \n");
			scanf("%s", search_phone);
		}
		for (i = 0; i < *perNum; i++){
			if (strcmp(perArr[i].phone, search_phone) == 0)
			{
				flag = 1;
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
			}
		}
		break;
		//해당 이름이 없다면???, 학번, 주소, 폰 번호
		default:
		printf("잘못된 입력입니다 1~4를 입력해주세요\n");
		}
	if (flag == 0) {
		printf("입력하신 정보가 없습니다 \n");
	}
}

void revise_person(Person *perArr, int*perNum){
	int opt = 0;
	int i = 0;
	char search_name[10];
	char search_address[100];
	char search_phone[30];
	int search_id;

	printf("수정할 정보는? \n");
	printf("1. 학번\n2. 이름\n3. 주소\n4.폰 번호\n");
	scanf("%d", &opt);

	switch (opt){
	case 1:
		printf("학번을 입력하세요\n");
		scanf("%d", &search_id);
		for (i = 0; i < *perNum; i++){
			if (perArr[i].id == search_id)
			{
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
				printf("수정하고픈 학번을 입력하여 주세요\n");
				scanf("%d", &perArr[i].id);
			}
		}
		break;
	case 2:
		printf("이름을 입력하세요\n");
		scanf("%s", search_name);
		for (i = 0; i < *perNum; i++){
			if (strcmp(perArr[i].name, search_name) == 0)
			{
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
				printf("수정하고픈 이름을 입력하여 주세요\n");
				scanf("%s", perArr[i].name);
			}
		}
		break;
	case 3:
		printf("주소를 입력하세요\n");
		getchar();
		fgets(search_address, 100, stdin);
		//printf("input: %d\n" + (search_address));

		search_address[strlen(search_address) - 1] = '\0';


		/*for (i = 0; search_address[i] != '\0'; i++) {
		printf("%d: %c %d \n", i, search_address[i], search_address[i]);
		}*/


		//하나하나 비교하기
		for (i = 0; i < *perNum; i++){
			//printf("---in: %s[size: %d], per[%d]: %s[size: %d]\n", search_address, strlen(search_address), i, perArr[i].address, strlen(perArr[i].address));

			if (strcmp(perArr[i].address, search_address) == 0)
			{
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
				printf("수정하고픈 주소로 입력하여 주세요\n");
				fgets(perArr[i].address, 100, stdin);
			}
		}
		break;
	case 4:
		printf("폰 번호를 입력하세요\n");
		scanf("%s", search_phone);
		getchar();
		for (i = 0; i < *perNum; i++){
			if (strcmp(perArr[i].phone, search_phone) == 0)
			{
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
				printf("바꾸고픈 번호로 입력하여 주세요\n");
				scanf("%s", perArr[i].phone);
				getchar();
				while (strlen(perArr[i].phone) != 13){
					printf("***-****-***** 형태로 다시 입력해주세요 \n");
					scanf("%s", perArr[i].phone);
				}

				while ((perArr[i].phone[3] != '-') && (perArr[i].phone[8] != '-')){
					printf("***-****-***** 형태로 다시 입력해주세요 \n");
					scanf("%s", perArr[i].phone);
				}

				while ((perArr[i].phone[i]<=48) && (perArr[i].phone[i]>57)){
					printf("***-****-***** 형태로 다시 입력해주세요 \n");
					scanf("%s", perArr[i].phone);
				}
			}
		}
		break;
	default:
		printf("잘못된 입력입니다 1~4를 입력해주세요\n");
	}
		//printf("입력하신 정보가 없습니다\n");
}


void delete_person(Person *perArr, int *perNum){
	int i = 0, c = 0;
	int search_id;

	printf("삭제할 정보의 학번을 입력하세요\n");
	scanf("%d", &search_id);
	for (i = 0; i < *perNum; i++){
		if (perArr[i].id == search_id)
		{

			printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
			printf("위 정보가 삭제되었습니다\n");
				//삭제 함수
			for (c = i; c < *perNum - 1; c++)
				perArr[c] = perArr[c + 1];
			//printf("Resultant array is\n");
			//for (c = 0; c < *perNum - 1; c++)
				//printf("%d\n",perArr[c]);
		}
	}
}
