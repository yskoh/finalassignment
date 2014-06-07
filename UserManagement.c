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
	printf("1.ȸ�� ��ܺ��� \n");
	printf("2.ȸ�� �˻� \n");
	printf("3.ȸ�� ��� \n");
	printf("4.ȸ�� ����\n");
	printf("5.ȸ�� ���� \n");
	printf("6.���Ϸ� �����ϱ� \n");
	printf("0. ����\n");
}

int input_order(void){
	int order;
	printf("������ �޴� ��ȣ�� �Է��ϼ��� \n");
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
		printf("�����ϱ� �� �����Ͻðڽ��ϱ�?\n1.yes 2.no\n");
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
			printf("�߸��� �Է��Դϴ�. �ٽ� 1�ƴϸ� 2�� �Է��Ͽ� �ּ���\n");
			n = 1;
		}
	}
		
	}
	else if (order == 1){
		printf("��� ���\n");
		view_list(perArr, perNum);
	}
	else if (order == 2){
		printf("ȸ�� �˻�\n");
		find_person(perArr,perNum);
	}
	else if (order == 3){
		printf("��� \n");
		register_person(perArr,perNum);
	}
	else if (order == 4){
		printf("���� \n");
		revise_person(perArr, perNum);
	}
	else if (order == 5){
		printf("���� \n");
		delete_person(perArr, perNum);
	}
	else if (order == 6){
		save_file(perArr, perNum);
	}
	else
	{
		printf("���Է��ϼ��� \n");
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
	fprintf(writeFile, "%s\n", "ȸ�� ���̵�\tȸ���̸�\tȸ���ּ�\t�ڵ��� ��ȣ");
	for (i = 0; i<*perNum; i++) {
			fprintf(writeFile, "%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
	}
	fclose(writeFile);
}

void register_person(Person * perArr, int * perNum) {

	// ���ο� Person ����
	Person new_person = { 0, };
	
	//printf("perNum: %d\n", *perNum);

	// id ����
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
	
	// Person�� �� �Է�
	puts("�Է��� �̸�");
	scanf("%s", new_person.name);
	getchar();

	puts("�Է��� �ּ�");
	fgets(new_person.address, 100, stdin);
	// ���������
	for (i = 0; i < 100; i++){
		if (new_person.address[i] == '\n') {
			new_person.address[i] = '\0';
			break;
		}
	}

	printf("�Է��� ��ȭ��ȣ");
	scanf("%s", new_person.phone);

	while (strlen(new_person.phone) != 13){
		printf("***-****-***** ���·� �ٽ� �Է����ּ��� \n");
		scanf("%s", new_person.phone);
	}

	while ((new_person.phone[3] != '-') && (new_person.phone[9] != '-')){
			printf("***-****-***** ���·� �ٽ� �Է����ּ��� \n");
			scanf("%s", new_person.phone);
		}
	
	while ((new_person.phone[i]<48) && (new_person.phone[i]>57)){
					printf("***-****-***** ���·� �ٽ� �Է����ּ��� \n");
					scanf("%s", new_person.phone);
				}

	// perArr[������ index]�� Person ����
	perArr[*perNum] = new_person;


	// ���� ������ index ���ϱ�
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

	printf("� ������ �˻��Ͻðڽ��ϱ�? \n");
	printf("1. �й�\n2. �̸�\n3. �ּ�\n4.�� ��ȣ\n");
	scanf("%d", &opt);

	switch (opt){
	case 1:
		printf("�й��� �Է��ϼ���\n");
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
		printf("�̸��� �Է��ϼ���\n");
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
		printf("�ּҸ� �Է��ϼ���\n");
		getchar();
		fgets(search_address,100,stdin);
		//printf("input: %d\n" + (search_address));
		
		search_address[strlen(search_address) - 1] = '\0';


		/*for (i = 0; search_address[i] != '\0'; i++) {
			printf("%d: %c %d \n", i, search_address[i], search_address[i]);
		}*/


		//�ϳ��ϳ� ���ϱ�
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
		printf("�� ��ȣ�� �Է��ϼ���\n");
		scanf("%s", search_phone); 
		while (strlen(search_phone) != 13){
			printf("***-****-***** ���·� �ٽ� �Է����ּ��� \n");
			scanf("%s", search_phone);
		}

		while ((search_phone[3] != '-') && (search_phone[8] != '-')){
			printf("***-****-***** ���·� �ٽ� �Է����ּ��� \n");
			scanf("%s", search_phone);
		}

		while ((search_phone[i]<=48) && (search_phone[i]>57)){
			printf("***-****-***** ���·� �ٽ� �Է����ּ��� \n");
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
		//�ش� �̸��� ���ٸ�???, �й�, �ּ�, �� ��ȣ
		default:
		printf("�߸��� �Է��Դϴ� 1~4�� �Է����ּ���\n");
		}
	if (flag == 0) {
		printf("�Է��Ͻ� ������ �����ϴ� \n");
	}
}

void revise_person(Person *perArr, int*perNum){
	int opt = 0;
	int i = 0;
	char search_name[10];
	char search_address[100];
	char search_phone[30];
	int search_id;

	printf("������ ������? \n");
	printf("1. �й�\n2. �̸�\n3. �ּ�\n4.�� ��ȣ\n");
	scanf("%d", &opt);

	switch (opt){
	case 1:
		printf("�й��� �Է��ϼ���\n");
		scanf("%d", &search_id);
		for (i = 0; i < *perNum; i++){
			if (perArr[i].id == search_id)
			{
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
				printf("�����ϰ��� �й��� �Է��Ͽ� �ּ���\n");
				scanf("%d", &perArr[i].id);
			}
		}
		break;
	case 2:
		printf("�̸��� �Է��ϼ���\n");
		scanf("%s", search_name);
		for (i = 0; i < *perNum; i++){
			if (strcmp(perArr[i].name, search_name) == 0)
			{
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
				printf("�����ϰ��� �̸��� �Է��Ͽ� �ּ���\n");
				scanf("%s", perArr[i].name);
			}
		}
		break;
	case 3:
		printf("�ּҸ� �Է��ϼ���\n");
		getchar();
		fgets(search_address, 100, stdin);
		//printf("input: %d\n" + (search_address));

		search_address[strlen(search_address) - 1] = '\0';


		/*for (i = 0; search_address[i] != '\0'; i++) {
		printf("%d: %c %d \n", i, search_address[i], search_address[i]);
		}*/


		//�ϳ��ϳ� ���ϱ�
		for (i = 0; i < *perNum; i++){
			//printf("---in: %s[size: %d], per[%d]: %s[size: %d]\n", search_address, strlen(search_address), i, perArr[i].address, strlen(perArr[i].address));

			if (strcmp(perArr[i].address, search_address) == 0)
			{
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
				printf("�����ϰ��� �ּҷ� �Է��Ͽ� �ּ���\n");
				fgets(perArr[i].address, 100, stdin);
			}
		}
		break;
	case 4:
		printf("�� ��ȣ�� �Է��ϼ���\n");
		scanf("%s", search_phone);
		getchar();
		for (i = 0; i < *perNum; i++){
			if (strcmp(perArr[i].phone, search_phone) == 0)
			{
				printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
				printf("�ٲٰ��� ��ȣ�� �Է��Ͽ� �ּ���\n");
				scanf("%s", perArr[i].phone);
				getchar();
				while (strlen(perArr[i].phone) != 13){
					printf("***-****-***** ���·� �ٽ� �Է����ּ��� \n");
					scanf("%s", perArr[i].phone);
				}

				while ((perArr[i].phone[3] != '-') && (perArr[i].phone[8] != '-')){
					printf("***-****-***** ���·� �ٽ� �Է����ּ��� \n");
					scanf("%s", perArr[i].phone);
				}

				while ((perArr[i].phone[i]<=48) && (perArr[i].phone[i]>57)){
					printf("***-****-***** ���·� �ٽ� �Է����ּ��� \n");
					scanf("%s", perArr[i].phone);
				}
			}
		}
		break;
	default:
		printf("�߸��� �Է��Դϴ� 1~4�� �Է����ּ���\n");
	}
		//printf("�Է��Ͻ� ������ �����ϴ�\n");
}


void delete_person(Person *perArr, int *perNum){
	int i = 0, c = 0;
	int search_id;

	printf("������ ������ �й��� �Է��ϼ���\n");
	scanf("%d", &search_id);
	for (i = 0; i < *perNum; i++){
		if (perArr[i].id == search_id)
		{

			printf("%d\t%s\t%s\t%s\n", perArr[i].id, perArr[i].name, perArr[i].address, perArr[i].phone);
			printf("�� ������ �����Ǿ����ϴ�\n");
				//���� �Լ�
			for (c = i; c < *perNum - 1; c++)
				perArr[c] = perArr[c + 1];
			//printf("Resultant array is\n");
			//for (c = 0; c < *perNum - 1; c++)
				//printf("%d\n",perArr[c]);
		}
	}
}
