#include"journey_head.h"
struct Node* node;//node���ڵ�
struct passage* Passage[N];//�������µĸ��ڵ�
struct student* stu;

int nowPassNum = 0;
int nowUserNum = 10;


int main()
{
	//�����ļ�����
	//��ɾ���
	//��¼
	//std::setlocale(LC_ALL, ".UTF-8");

	cout << "�����в�����" << endl;
	bool signUp = false;
	initNode();
	load();
	char name[20];
	char password[10]; 
	printf("�������û���:\n");
	scanf("%s", name); cout << name << endl;
	struct Node* temp = searchUser(name);
	
	//�ҵ��˸��û���˶�����
	if (temp != NULL)
	{
		while (1)
		{
			//printf("%s%s",temp->data.name, temp->data.password);
			printf("���������������return���أ�\n");
			scanf("%s", password);
			if (strcmp(password, "return") == 0)
				break;
			else if (strcmp(password, temp->data.password) == 0)
			{
				printf("��½�ɹ���\n");
				signUp = true;
				break;
			}
			else
			{
				printf("�������;;\n");
			}
		}
	}
	
	//��������ڸ��û����Ǵ����û�
	else if (temp == NULL)
	{
		printf("���û�������;;\n");
		printf("�Ƿ񴴽����˻�����Yes,No)\n");
		char choice[3];
		scanf("%s", choice);
		if (strcmp(choice, "Yes") == 0)
		{
			struct student* p = (student*)malloc(sizeof(struct student));
			while (1)
			{
				printf("�������û���������return���أ�\n");
				scanf("%s", p->name);
				//�û��Ѵ���
				while ( searchUser(p->name) != NULL)
				{
					printf("���û��Ѵ���;;\n");
					printf("�������û���������return���أ�\n");
					scanf("%s", p->name);
				}
				if (strcmp(p->name, "return")==0)//����
				{
					break;
				}
				else//���û��������Ҳ����������ע��
				{
					printf("�������û����루1-10λ���֡���ĸ������:)\n");
					scanf("%s", p->password);
					//�ҵ���ǰ�û������һλ
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
	
	//��¼��ĸ��ֲ���
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
			case 1:recommendsort();//�Ƽ�
				break;
			case 2:searchPass();//��ѯ����
				break;
			case 3:write(user);//��¼�μ�
				break;
			case 4:siteRecommend();//���յص�����Ƽ�
				break;
			case 5:break;
			}
			scanf("%d", &c);
		}
	}
	return 0;
}