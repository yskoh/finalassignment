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
	int i;

	if (order == 0){
		return 0;
	}
	else if (order == 1){
		printf("��� ���\n");
		view_list(perArr, perNum);
	}
	else if (order == 2){
		printf("ȸ�� �˻�\n");
	}
	else if (order == 3){
		printf("��� \n");
		register_person(perArr,perNum);
	}
	else if (order == 4){
		printf("���� \n");
	}
	else if (order == 5){
		printf("���� \n");
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
	/*
	����ó���� �ڵ�
	while (strlen(new_person.name) == 0)
	{
		printf("�ٽ� �Է����ּ���\n");
		scanf("%s", new_person.name);
		
	}
	*/
	puts("�Է��� �ּ�");
	scanf("%s", new_person.address);
	puts("�Է��� ��ȭ��ȣ");
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