#include"journey_head.h"
struct Node* node;//node根节点
struct passage* Passage[N];//所有文章的根节点
struct student* stu;

int nowPassNum = 0;
int nowUserNum = 10;


int main()
{
	//读入文件内容
	//增删查改
	//登录
	//std::setlocale(LC_ALL, ".UTF-8");

	cout << "到底行不行呢" << endl;
	bool signUp = false;
	initNode();
	load();
	char name[20];
	char password[10]; 
	printf("请输入用户名:\n");
	scanf("%s", name); cout << name << endl;
	struct Node* temp = searchUser(name);
	
	//找到了该用户则核对密码
	if (temp != NULL)
	{
		while (1)
		{
			//printf("%s%s",temp->data.name, temp->data.password);
			printf("请输入密码或输入return返回：\n");
			scanf("%s", password);
			if (strcmp(password, "return") == 0)
				break;
			else if (strcmp(password, temp->data.password) == 0)
			{
				printf("登陆成功！\n");
				signUp = true;
				break;
			}
			else
			{
				printf("密码错误;;\n");
			}
		}
	}
	
	//如果不存在该用户则考虑创建用户
	else if (temp == NULL)
	{
		printf("该用户不存在;;\n");
		printf("是否创建新账户？（Yes,No)\n");
		char choice[3];
		scanf("%s", choice);
		if (strcmp(choice, "Yes") == 0)
		{
			struct student* p = (student*)malloc(sizeof(struct student));
			while (1)
			{
				printf("请输入用户名或输入return返回：\n");
				scanf("%s", p->name);
				//用户已存在
				while ( searchUser(p->name) != NULL)
				{
					printf("该用户已存在;;\n");
					printf("请输入用户名或输入return返回：\n");
					scanf("%s", p->name);
				}
				if (strcmp(p->name, "return")==0)//返回
				{
					break;
				}
				else//该用户不存在且不返回则继续注册
				{
					printf("请设置用户密码（1-10位数字、字母、符号:)\n");
					scanf("%s", p->password);
					//找到当前用户的最后一位
					struct Node* t = node;
					for (; t->next != NULL; t = t->next);
					t->next = createNode(p);
					signUp = true;
					temp = t->next;
					break;
				}
			}
		}

	}
	
	//登录后的各种操作
	if (signUp)
	{			
		struct Node* user = temp;
		printf("%s,", user->data.name);
		Welcome();
		int c;
		scanf("%d", &c);
		while (c!=0)
		{
			switch (c)
			{
			case 1:recommendsort();//推荐
				break;
			case 2:searchPass();//查询文章
				break;
			case 3:write(user);//记录游记
				break;
			case 4:siteRecommend();//按照地点进行推荐
				break;
			case 5:break;
			}
			scanf("%d", &c);
		}
	}
	return 0;
}