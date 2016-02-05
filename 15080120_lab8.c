#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct student
{
	int id;
	char name[10];
	char gender;//调试用，记得改回来！！ （已经改了 
	int age;
	int entry;
	int gpa;
	char phone[50];
	char addr[50];
	struct student *self;//指向自己的指针，在本打算使用的排序算法里用到。（现在没卵用了
	struct student *next;//指向下一个节点的指针 
};

struct student *head=NULL; 

int nullchk(struct student *head)//异常处理，否则在链表里没有数据时执行>1的功能会FC
{
	if (head == NULL)
	{
		printf("没有数据.\n");
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
	printf("学生总数:");
	scanf("%d",&num);

	head=NULL;//把头指针初始化为空指针

	for (i=1;i<=num;i++)
	{
		printf("\n\n学生%d：",i); 
		current = (struct student *)malloc(sizeof (struct student));//为链表中的一个结构分配内存，将其地址赋值给current，current是指向当前节点的指针 ！ 
		if (head == NULL)//如果头指针为空则当前为第一个结构 ，将head赋值为current，指向当前节点的指针。 
			head = current;
		else
			prev->next = current;//不是则指将上一个结构的next指针指向当前结构的地址

		current->next = NULL;//将next指向空来表示这是最后一个元素 
		current->self = current;//将自己的地址赋值给current的self 
		printf("\n输入学号:\t"/*,current*/);
		scanf("%d",&current->id);
		printf("\n输入名字:\t");
		scanf("%s",&current->name);
		printf("\n输入性别M/F:\t");
		scanf(" %c",&current->gender);//%c前加空格，防止读入缓冲区中的回车
		printf("\n输入年龄:\t");
		scanf("%d",&current->age);
		printf("\n输入入学时间:\t");
		scanf("%d",&current->entry);
		printf("\n输入GPA:\t");
		scanf("%d",&current->gpa);
		printf("\n输入电话:\t");
		scanf("%s",&current->phone);
		printf("\n输入地址:\t");
		scanf("%s",&current->addr);
		prev = current;//输入完成，使当前的结构成为上一个。 
	}
	return head;
}

int display(struct student *head)
{
	struct student *current;
	int num=0;
	current = head;//将current指针指向链表第一个节点

	while(1)
	{
		printf("\n学号：\t%d.\n姓名：\t%s.\n性别：\t%c.\n年龄：\t%d.\n入学：\t%d.\nGPA：\t%d.\n电话：\t%s.\n地址：\t%s.\n",current->id,current->name,current->gender,current->age,current->entry,current->gpa,current->phone,current->addr); 
		num++;//统计节点数量
		current = current->next;
		if (current == NULL)
			break;
	}
	return num;//返回节点数量，后面输出到文件的时候会用到。
}

int search(struct student *head)
{
	int sid;
	struct student *current;
	printf("输入要搜索的学生id:\t\n");
	scanf("%d",&sid);
	current = head;
	while(1)
	{
		if (current->id == sid)
			break;
		current = current->next;
		if (current == NULL)
		{
			printf("未找到该学生\n");
			system("pause");
			return 0;
		}
	}
	printf("\n学号：\t%d.\n姓名：\t%s.\n性别：\t%c.\n年龄：\t%d.\n入学：\t%d.\nGPA：\t%d.\n电话：\t%s.\n地址：\t%s.\n",current->id,current->name,current->gender,current->age,current->entry,current->gpa,current->phone,current->addr); 
	system("pause");
	return 0;
}

int out(struct student *head)//文件输出
{
	struct student *current;
	FILE *fp;//建立一个文件操作指针
	current = head;//将current指针指向链表第一个元素
	fp=fopen("output.txt","w");//打开output.txt
	if (fp == NULL)
	{
		printf("打开文件失败\n");
		return 1;
	}
	fprintf(fp,"%d\n",display(head));//输出文件的第一行为节点数量
	while(1)
	{
		fprintf(fp,"%d\n%s\n%c\n%d\n%d\n%d\n%s\n%s\n",current->id,current->name,current->gender,current->age,current->entry,current->gpa,current->phone,current->addr); 
		current = current->next;
		if (current == NULL)
			break;
	}
	fclose(fp);//关闭文件
	system("cls");
	printf("文件保存至output.txt\n");
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
		printf("已经有数据存在，是否清空？y/n\n");
		getchar();
		if (getchar() == 'n')
			return head;
	}
	
	memset(fstr, 0, sizeof(fstr));
	fgets(fstr, sizeof(fstr) - 1, fp); 
	num = atoi(fstr);//从文件中读取第一行，表示链表有多少个节点，将从文件中读出的字符串转换为整数
	head=NULL;//把头指针初始化为空指针

	if(fp == NULL)
	{
		printf("failed to open file\n");
		return;
	}

	for (i=1;i<=num;i++)
	{
		printf("\n\n学生%d：",i); 
		current = (struct student *)malloc(sizeof (struct student));//为链表中的一个结构分配内存，将其地址赋值给current，current是指向结构的指针 ！ 
		if (head == NULL)//如果头指针为空则当前为第一个结构 ，将head赋值为current，指向当前结构的地址的指针。 
			head = current;
		else
			prev->next = current;//不是则指将上一个结构的next指针指向当前结构的地址

		current->next = NULL;//将next指向空来表示这是最后一个元素 
		current->self = current;//将自己的地址赋值给current的self

		{
			//每次从文件中读取一行
			memset(fstr, 0, sizeof(fstr));//将fstr的前(fstr的长度)的字节全部改为ascii的0并且返回fstr的地址。
			fgets(fstr, sizeof(fstr) - 1, fp); //从fp中读取(sizeof(fstr))长度的数据，赋值给fstr
			printf("%s", fstr);
			//id
			current->id = atoi(fstr);

			memset(fstr, 0, sizeof(fstr));
			fgets(fstr, sizeof(fstr) - 1, fp); 
			printf("%s", fstr);
			rmenter(fstr);//去除字符串中的\n
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
		prev = current;//输入完成，使当前的结构成为上一个。
	}
	fclose(fp);//关闭文件
	system("cls");
	printf("已从文件读入%d个学生数据。\n",num);
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
	//声明一堆变量，用作交换数据时的临时变量
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

	while (curr->next!=NULL)//循环直到最后一个节点
	{
		if (curr->id>curr->next->id)//如果大于则交换
		{
			//交换id
			swapper_id=curr->id;
			curr->id=curr->next->id;
			curr->next->id=swapper_id;
			//交换name
			strcpy(swapper_name, curr->name);
			strcpy(curr->name, curr->next->name);
			strcpy(curr->next->name, swapper_name);
			//交换gender
			swapper_gender=curr->gender;
			curr->gender=curr->next->gender;
			curr->next->gender=swapper_gender;
			//交换age
			swapper_age=curr->age;
			curr->age=curr->next->age;
			curr->next->age=swapper_age;
			//交换entry
			swapper_entry=curr->entry;
			curr->entry=curr->next->entry;
			curr->next->entry=swapper_entry;
			//交换gpa
			swapper_gpa=curr->gpa;
			curr->gpa=curr->next->gpa;
			curr->next->gpa=swapper_gpa;
			//交换phone
			strcpy(swapper_phone, curr->phone);
			strcpy(curr->phone, curr->next->phone);
			strcpy(curr->next->phone, swapper_phone);
			//交换addr
			strcpy(swapper_addr, curr->addr);
			strcpy(curr->addr, curr->next->addr);
			strcpy(curr->next->addr, swapper_addr);
			flag=1;
		}
		curr=curr->next;//一次循环过后将curr后移一个
	}
	if (flag)
	{
		sort(head);//递归
	}
	return head;

}

struct student *rm(struct student *head)
{
	int rmid;
	struct student *current;
	struct student *prev;
	prev = NULL;
	printf("输入要移除的学生id:\t\n");
	scanf("%d",&rmid);
	current = head;
	//异常处理：如果头节点被移除
	while(1)
	{
		if (current->id == rmid)
			break;
		prev = current;
		current = current->next;
		if (current == NULL)
		{
			printf("未找到该学生\n");
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
	printf("输入要编辑的学生id:\t\n");
	scanf("%d",&modid);
	current = head;
	while(1)
	{
		if (current->id == modid)
			break;
		current = current->next;
		if (current == NULL)
		{
			printf("未找到该学生\n");
			system("pause");
			return 0;
		}
	}
	printf("\n当前状态：\t\n学号：\t%d.\n姓名：\t%s.\n性别：\t%c.\n年龄：\t%d.\n入学：\t%d.\nGPA：\t%d.\n电话：\t%s.\n地址：\t%s.\n",current->id,current->name,current->gender,current->age,current->entry,current->gpa,current->phone,current->addr); 
	printf("\n输入学号:\t");
	scanf("%d",&current->id);
	printf("\n输入名字:\t");
	scanf("%s",&current->name);
	printf("\n输入性别M/F:\t");
	scanf(" %c",&current->gender);
	printf("\n输入年龄:\t");
	scanf("%d",&current->age);
	printf("\n输入入学时间:\t");
	scanf("%d",&current->entry);
	printf("\n输入GPA:\t");
	scanf("%d",&current->gpa);
	printf("\n输入电话:\t");
	scanf("%s",&current->phone);
	printf("\n输入地址:\t");
	scanf("%s",&current->addr);
	system("pause");
	return 0;
}

struct student *insert (struct student *head)
{
	struct student *curr = NULL;
	struct student *tempNode = (struct student *) malloc(sizeof(struct student));
	curr=head;
	printf("\n输入学号:\t");
	scanf("%d",&tempNode->id);
	printf("\n输入名字:\t");
	scanf("%s",&tempNode->name);
	printf("\n输入性别M/F:\t");
	scanf(" %c",&tempNode->gender);
	printf("\n输入年龄:\t");
	scanf("%d",&tempNode->age);
	printf("\n输入入学时间:\t");
	scanf("%d",&tempNode->entry);
	printf("\n输入GPA:\t");
	scanf("%d",&tempNode->gpa);
	printf("\n输入电话:\t");
	scanf("%s",&tempNode->phone);
	printf("\n输入地址:\t");
	scanf("%s",&tempNode->addr);
	tempNode->next = NULL;
	if (head==NULL)
	{
		head=tempNode;//如果没有现有节点则设置为头节点。
	}
	else 
	{
		while (curr->next!=NULL)
		{
			curr=curr->next;
		}
		curr->next=tempNode; //遍历链表，将临时节点接在尾部。
	}
	curr=head;
	sort(head);//结束后排序
	printf("插入完成\n");
	return head;
}


int main()
{
	int ch;
	struct student *head=NULL;
	
	printf("\n\n\n\n\n\n\n\n\n\t\t\t学生信息管理系统\t\t\n\n\n\t\t\t15080120 郭都豪\t\t\n\n\t\t\t2015.12.24\t\t\n\t\t\tVersion 1.0\t\t\n\n\n\n\n");
	system("pause");
		
	while (1)
	{		
		system("cls");
		printf("链表头的地址：%p\n\n\n\n\t\t\t（1）Create a student list; \n\t\t\t（2）Sort according to the StudentID；\n\t\t\t（3）Insert a student；\n\t\t\t（4）Delete a student;\n\t\t\t（5）Update a student Info;\n\t\t\t（6）Search a student ;\n\t\t\t（7）Display all students;\n\t\t\t（8）Save to the file;\n\t\t\t（9）Open the file;\n\t\t\t（10）exit\n",head);
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				system("cls");
				head = create(head);//创建一个学生列表 
				break;
			case 2:
				system("cls");
				if (nullchk(head))
					break;
				head = sort(head);//排序
				printf("排序完成\n");
				system("pause");
				break;
			case 3:
				system("cls");
				if (nullchk(head))
					break;
				head = insert(head);//插入
				break;
			case 4:
				system("cls");
				if (nullchk(head))
					break;
				head = rm(head);//移除
				break;
			case 5:
				system("cls");
				if (nullchk(head))
					break;
				update(head);//更新。
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
				release(head);//释放整个链表
				return 0;
		}	
	}
}
