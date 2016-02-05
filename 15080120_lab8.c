#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct student
{
	int id;
	char name[10];
	char gender;//�����ã��ǵøĻ������� ���Ѿ����� 
	int age;
	int entry;
	int gpa;
	char phone[50];
	char addr[50];
	struct student *self;//ָ���Լ���ָ�룬�ڱ�����ʹ�õ������㷨���õ���������û������
	struct student *next;//ָ����һ���ڵ��ָ�� 
};

struct student *head=NULL; 

int nullchk(struct student *head)//�쳣����������������û������ʱִ��>1�Ĺ��ܻ�FC
{
	if (head == NULL)
	{
		printf("û������.\n");
		system("pause");
		return 1;
	}
	else
		return 0;
}



struct student *release(struct student *head)
{
	struct student *p;
	for (; head != NULL; head = p) 
	{  
		p = head->next;  
		free(head);  
	}  
	return head;
}

struct student *create(struct student *head)
{
	int i,num;
	struct student *prev;
	struct student *current;
	printf("ѧ������:");
	scanf("%d",&num);

	head=NULL;//��ͷָ���ʼ��Ϊ��ָ��

	for (i=1;i<=num;i++)
	{
		printf("\n\nѧ��%d��",i); 
		current = (struct student *)malloc(sizeof (struct student));//Ϊ�����е�һ���ṹ�����ڴ棬�����ַ��ֵ��current��current��ָ��ǰ�ڵ��ָ�� �� 
		if (head == NULL)//���ͷָ��Ϊ����ǰΪ��һ���ṹ ����head��ֵΪcurrent��ָ��ǰ�ڵ��ָ�롣 
			head = current;
		else
			prev->next = current;//������ָ����һ���ṹ��nextָ��ָ��ǰ�ṹ�ĵ�ַ

		current->next = NULL;//��nextָ�������ʾ�������һ��Ԫ�� 
		current->self = current;//���Լ��ĵ�ַ��ֵ��current��self 
		printf("\n����ѧ��:\t"/*,current*/);
		scanf("%d",&current->id);
		printf("\n��������:\t");
		scanf("%s",&current->name);
		printf("\n�����Ա�M/F:\t");
		scanf(" %c",&current->gender);//%cǰ�ӿո񣬷�ֹ���뻺�����еĻس�
		printf("\n��������:\t");
		scanf("%d",&current->age);
		printf("\n������ѧʱ��:\t");
		scanf("%d",&current->entry);
		printf("\n����GPA:\t");
		scanf("%d",&current->gpa);
		printf("\n����绰:\t");
		scanf("%s",&current->phone);
		printf("\n�����ַ:\t");
		scanf("%s",&current->addr);
		prev = current;//������ɣ�ʹ��ǰ�Ľṹ��Ϊ��һ���� 
	}
	return head;
}

int display(struct student *head)
{
	struct student *current;
	int num=0;
	current = head;//��currentָ��ָ�������һ���ڵ�

	while(1)
	{
		printf("\nѧ�ţ�\t%d.\n������\t%s.\n�Ա�\t%c.\n���䣺\t%d.\n��ѧ��\t%d.\nGPA��\t%d.\n�绰��\t%s.\n��ַ��\t%s.\n",current->id,current->name,current->gender,current->age,current->entry,current->gpa,current->phone,current->addr); 
		num++;//ͳ�ƽڵ�����
		current = current->next;
		if (current == NULL)
			break;
	}
	return num;//���ؽڵ�����������������ļ���ʱ����õ���
}

int search(struct student *head)
{
	int sid;
	struct student *current;
	printf("����Ҫ������ѧ��id:\t\n");
	scanf("%d",&sid);
	current = head;
	while(1)
	{
		if (current->id == sid)
			break;
		current = current->next;
		if (current == NULL)
		{
			printf("δ�ҵ���ѧ��\n");
			system("pause");
			return 0;
		}
	}
	printf("\nѧ�ţ�\t%d.\n������\t%s.\n�Ա�\t%c.\n���䣺\t%d.\n��ѧ��\t%d.\nGPA��\t%d.\n�绰��\t%s.\n��ַ��\t%s.\n",current->id,current->name,current->gender,current->age,current->entry,current->gpa,current->phone,current->addr); 
	system("pause");
	return 0;
}

int out(struct student *head)//�ļ����
{
	struct student *current;
	FILE *fp;//����һ���ļ�����ָ��
	current = head;//��currentָ��ָ�������һ��Ԫ��
	fp=fopen("output.txt","w");//��output.txt
	if (fp == NULL)
	{
		printf("���ļ�ʧ��\n");
		return 1;
	}
	fprintf(fp,"%d\n",display(head));//����ļ��ĵ�һ��Ϊ�ڵ�����
	while(1)
	{
		fprintf(fp,"%d\n%s\n%c\n%d\n%d\n%d\n%s\n%s\n",current->id,current->name,current->gender,current->age,current->entry,current->gpa,current->phone,current->addr); 
		current = current->next;
		if (current == NULL)
			break;
	}
	fclose(fp);//�ر��ļ�
	system("cls");
	printf("�ļ�������output.txt\n");
	system("pause");
	return 0;
}

struct student *in(struct student *head)
{
	int i,j,num;
	struct student *prev;
	struct student *current;
	FILE *fp = fopen("output.txt", "r");
	char fstr[1000] = {0};
	int len = 0;	

	if (head != NULL)
	{
		printf("�Ѿ������ݴ��ڣ��Ƿ���գ�y/n\n");
		getchar();
		if (getchar() == 'n')
			return head;
	}
	
	memset(fstr, 0, sizeof(fstr));
	fgets(fstr, sizeof(fstr) - 1, fp); 
	num = atoi(fstr);//���ļ��ж�ȡ��һ�У���ʾ�����ж��ٸ��ڵ㣬�����ļ��ж������ַ���ת��Ϊ����
	head=NULL;//��ͷָ���ʼ��Ϊ��ָ��

	if(fp == NULL)
	{
		printf("failed to open file\n");
		return;
	}

	for (i=1;i<=num;i++)
	{
		printf("\n\nѧ��%d��",i); 
		current = (struct student *)malloc(sizeof (struct student));//Ϊ�����е�һ���ṹ�����ڴ棬�����ַ��ֵ��current��current��ָ��ṹ��ָ�� �� 
		if (head == NULL)//���ͷָ��Ϊ����ǰΪ��һ���ṹ ����head��ֵΪcurrent��ָ��ǰ�ṹ�ĵ�ַ��ָ�롣 
			head = current;
		else
			prev->next = current;//������ָ����һ���ṹ��nextָ��ָ��ǰ�ṹ�ĵ�ַ

		current->next = NULL;//��nextָ�������ʾ�������һ��Ԫ�� 
		current->self = current;//���Լ��ĵ�ַ��ֵ��current��self

		{
			//ÿ�δ��ļ��ж�ȡһ��
			memset(fstr, 0, sizeof(fstr));//��fstr��ǰ(fstr�ĳ���)���ֽ�ȫ����Ϊascii��0���ҷ���fstr�ĵ�ַ��
			fgets(fstr, sizeof(fstr) - 1, fp); //��fp�ж�ȡ(sizeof(fstr))���ȵ����ݣ���ֵ��fstr
			printf("%s", fstr);
			//id
			current->id = atoi(fstr);

			memset(fstr, 0, sizeof(fstr));
			fgets(fstr, sizeof(fstr) - 1, fp); 
			printf("%s", fstr);
			rmenter(fstr);//ȥ���ַ����е�\n
			//name
			strcpy(current->name, fstr);

			memset(fstr, 0, sizeof(fstr));
			fgets(fstr, sizeof(fstr) - 1, fp); 
			printf("%s", fstr);
			//gender
			current->gender = fstr[0];

			memset(fstr, 0, sizeof(fstr));
			fgets(fstr, sizeof(fstr) - 1, fp); 
			printf("%s", fstr);
			//age
			current->age = atoi(fstr);

			memset(fstr, 0, sizeof(fstr));
			fgets(fstr, sizeof(fstr) - 1, fp); 
			printf("%s", fstr);
			//entry
			current->entry = atoi(fstr);

			memset(fstr, 0, sizeof(fstr));
			fgets(fstr, sizeof(fstr) - 1, fp); 
			printf("%s", fstr);
			//gpa
			current->gpa = atoi(fstr);

			memset(fstr, 0, sizeof(fstr));
			fgets(fstr, sizeof(fstr) - 1, fp); 
			printf("%s", fstr);
			rmenter(fstr);
			//phone
			strcpy(current->phone, fstr);

			memset(fstr, 0, sizeof(fstr));
			fgets(fstr, sizeof(fstr) - 1, fp); 
			printf("%s", fstr);
			rmenter(fstr);
			//addr
			strcpy(current->addr, fstr);
		}
		prev = current;//������ɣ�ʹ��ǰ�Ľṹ��Ϊ��һ����
	}
	fclose(fp);//�ر��ļ�
	system("cls");
	printf("�Ѵ��ļ�����%d��ѧ�����ݡ�\n",num);
	system("pause");
	return head;
}

int rmenter(char *sz)
{
	int i=0;
	while(1)
	{
		if (*(sz+i) == '\n')
		{
			*(sz+i)=0;
			return 0;
		}
		i++;
	}
}

struct student *sort(struct student *head)
{
	//����һ�ѱ�����������������ʱ����ʱ����
	int swapper_id;
	char swapper_name[10];
	int swapper_gender;
	int swapper_age;
	int swapper_entry;
	int swapper_gpa;
	char swapper_phone[50];
	char swapper_addr[50];
	int flag=0;
	struct student *curr = NULL;
	curr=head;

	while (curr->next!=NULL)//ѭ��ֱ�����һ���ڵ�
	{
		if (curr->id>curr->next->id)//��������򽻻�
		{
			//����id
			swapper_id=curr->id;
			curr->id=curr->next->id;
			curr->next->id=swapper_id;
			//����name
			strcpy(swapper_name, curr->name);
			strcpy(curr->name, curr->next->name);
			strcpy(curr->next->name, swapper_name);
			//����gender
			swapper_gender=curr->gender;
			curr->gender=curr->next->gender;
			curr->next->gender=swapper_gender;
			//����age
			swapper_age=curr->age;
			curr->age=curr->next->age;
			curr->next->age=swapper_age;
			//����entry
			swapper_entry=curr->entry;
			curr->entry=curr->next->entry;
			curr->next->entry=swapper_entry;
			//����gpa
			swapper_gpa=curr->gpa;
			curr->gpa=curr->next->gpa;
			curr->next->gpa=swapper_gpa;
			//����phone
			strcpy(swapper_phone, curr->phone);
			strcpy(curr->phone, curr->next->phone);
			strcpy(curr->next->phone, swapper_phone);
			//����addr
			strcpy(swapper_addr, curr->addr);
			strcpy(curr->addr, curr->next->addr);
			strcpy(curr->next->addr, swapper_addr);
			flag=1;
		}
		curr=curr->next;//һ��ѭ������curr����һ��
	}
	if (flag)
	{
		sort(head);//�ݹ�
	}
	return head;

}

struct student *rm(struct student *head)
{
	int rmid;
	struct student *current;
	struct student *prev;
	prev = NULL;
	printf("����Ҫ�Ƴ���ѧ��id:\t\n");
	scanf("%d",&rmid);
	current = head;
	//�쳣�������ͷ�ڵ㱻�Ƴ�
	while(1)
	{
		if (current->id == rmid)
			break;
		prev = current;
		current = current->next;
		if (current == NULL)
		{
			printf("δ�ҵ���ѧ��\n");
			system("pause");
			return head;
		}
	}
	if(current == head)
		head = head->next;
	else
		prev->next=prev->next->next;
	return head;
}

int update(struct student *head)
{
	int modid;
	struct student *current;
	printf("����Ҫ�༭��ѧ��id:\t\n");
	scanf("%d",&modid);
	current = head;
	while(1)
	{
		if (current->id == modid)
			break;
		current = current->next;
		if (current == NULL)
		{
			printf("δ�ҵ���ѧ��\n");
			system("pause");
			return 0;
		}
	}
	printf("\n��ǰ״̬��\t\nѧ�ţ�\t%d.\n������\t%s.\n�Ա�\t%c.\n���䣺\t%d.\n��ѧ��\t%d.\nGPA��\t%d.\n�绰��\t%s.\n��ַ��\t%s.\n",current->id,current->name,current->gender,current->age,current->entry,current->gpa,current->phone,current->addr); 
	printf("\n����ѧ��:\t");
	scanf("%d",&current->id);
	printf("\n��������:\t");
	scanf("%s",&current->name);
	printf("\n�����Ա�M/F:\t");
	scanf(" %c",&current->gender);
	printf("\n��������:\t");
	scanf("%d",&current->age);
	printf("\n������ѧʱ��:\t");
	scanf("%d",&current->entry);
	printf("\n����GPA:\t");
	scanf("%d",&current->gpa);
	printf("\n����绰:\t");
	scanf("%s",&current->phone);
	printf("\n�����ַ:\t");
	scanf("%s",&current->addr);
	system("pause");
	return 0;
}

struct student *insert (struct student *head)
{
	struct student *curr = NULL;
	struct student *tempNode = (struct student *) malloc(sizeof(struct student));
	curr=head;
	printf("\n����ѧ��:\t");
	scanf("%d",&tempNode->id);
	printf("\n��������:\t");
	scanf("%s",&tempNode->name);
	printf("\n�����Ա�M/F:\t");
	scanf(" %c",&tempNode->gender);
	printf("\n��������:\t");
	scanf("%d",&tempNode->age);
	printf("\n������ѧʱ��:\t");
	scanf("%d",&tempNode->entry);
	printf("\n����GPA:\t");
	scanf("%d",&tempNode->gpa);
	printf("\n����绰:\t");
	scanf("%s",&tempNode->phone);
	printf("\n�����ַ:\t");
	scanf("%s",&tempNode->addr);
	tempNode->next = NULL;
	if (head==NULL)
	{
		head=tempNode;//���û�����нڵ�������Ϊͷ�ڵ㡣
	}
	else 
	{
		while (curr->next!=NULL)
		{
			curr=curr->next;
		}
		curr->next=tempNode; //������������ʱ�ڵ����β����
	}
	curr=head;
	sort(head);//����������
	printf("�������\n");
	return head;
}


int main()
{
	int ch;
	struct student *head=NULL;
	
	printf("\n\n\n\n\n\n\n\n\n\t\t\tѧ����Ϣ����ϵͳ\t\t\n\n\n\t\t\t15080120 ������\t\t\n\n\t\t\t2015.12.24\t\t\n\t\t\tVersion 1.0\t\t\n\n\n\n\n");
	system("pause");
		
	while (1)
	{		
		system("cls");
		printf("����ͷ�ĵ�ַ��%p\n\n\n\n\t\t\t��1��Create a student list; \n\t\t\t��2��Sort according to the StudentID��\n\t\t\t��3��Insert a student��\n\t\t\t��4��Delete a student;\n\t\t\t��5��Update a student Info;\n\t\t\t��6��Search a student ;\n\t\t\t��7��Display all students;\n\t\t\t��8��Save to the file;\n\t\t\t��9��Open the file;\n\t\t\t��10��exit\n",head);
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				system("cls");
				head = create(head);//����һ��ѧ���б� 
				break;
			case 2:
				system("cls");
				if (nullchk(head))
					break;
				head = sort(head);//����
				printf("�������\n");
				system("pause");
				break;
			case 3:
				system("cls");
				if (nullchk(head))
					break;
				head = insert(head);//����
				break;
			case 4:
				system("cls");
				if (nullchk(head))
					break;
				head = rm(head);//�Ƴ�
				break;
			case 5:
				system("cls");
				if (nullchk(head))
					break;
				update(head);//���¡�
				break;		
			case 6:
				system("cls");
				if (nullchk(head))
					break;
				search(head);
				break;
			case 7:
				system("cls");
				if (nullchk(head))
					break;
				display(head);
				system("pause");
				break;
			case 8:
				system("cls");
				if (nullchk(head))
					break;
				out(head);
				break;
			case 9:
				system("cls");
				head = in(head);
				break;
			case 10:
				release(head);//�ͷ���������
				return 0;
		}	
	}
}
