#include"journey_head.h"
//��������ڵ�
struct Node* createNode(struct student* p)
{
	//printf("��ʼ�������û�%s...\n",p->name);
	struct Node* pNew = (Node*)malloc(sizeof(struct Node));
	if (pNew == NULL)
	{
		wprintf(L"����ʧ��*-*\n");
		return NULL;
	}
	pNew->next = NULL;
	pNew->Passage = (passage*)malloc(sizeof(struct passage));
	pNew->Passage->next = NULL;
	strcpy(pNew->data.name, p->name);
	strcpy(pNew->data.password, p->password);
	//printf("�½��û����\n");
	return pNew;
}

void initNode()
{
	node = (Node*)malloc(sizeof(struct Node));
	node->next = NULL;
	Passage[0] = NULL;
	//Passage[0]->fp = NULL;
}

void Welcome()
{
	wprintf(L"welcome!\n");
}

//չʾ�Ƽ��б�
void showList(struct passage* p)
{
	struct passage* cur = p;
	while (cur != NULL)
	{
		printf("%s\n", cur->title);
		printf("����:%s\n", cur->writer);
		printf("�ȶ�:%d\n", cur->hot);
		printf("��ѧ�ص�:%s\n", cur->site);
		printf("\n");
		cur = cur->next;
	}
}

//�鿴���¡�����ڴ˺������
void showPass(struct passage* p)
{
	printf("���ߣ�%s\n", p->writer);
	printf("�ȶȣ�%d	������%.1f\n", p->hot,p->score);
	printf("��ѧ�ص㣺%s\n", p->site);
	printf("%s\n", p->title);
	//���
	printf("%s\n", p->text);
	readPassage(p->fp);

	printf("���֣�0-5����\n");
	int score = 0;
	scanf("%d", &score);
	p->hot++;	
	p->score = (p->score + score) / p->hot;
}

//�������°��ȶ�����
void recommendsort()
{
	for (int i = 0; i < nowPassNum; i++)
	{
		for (int j = 0; j < nowPassNum - i - 1; j++)
		{
			if (Passage[j]->hot < Passage[j + 1]->hot)
			{
				struct passage* temp = Passage[j];
				Passage[j] = Passage[j + 1];
				Passage[j + 1] = temp;
			}
		}
	}
	showList(Passage[0]);
}

//Ѱ������
struct passage* searchPass()
{
	printf("��������ҵ�����\n");
	//�����ַ��������в���
	char c[20];
	scanf("%s", c);
	int l = 0, r = nowPassNum-1, mid;
	while(l<=r)
	{
		mid = (l + r) / 2;
		int result = strcmp(Passage[mid]->title, c);
		if ( result == 0)
		{
			break;
		}
		else if(result<0)
		{
			l = mid + 1;
		}
		else if (result > 0)
		{
			r = mid - 1;
		}
	}
	if (l > r)
	{
		printf("�տ���Ҳ��*_*\n");
	}
	else
	{
		//printf("%s\n", Passage[mid]->title);
		showPass(Passage[mid]);
		return Passage[mid];
	}
	return NULL;
}

//д����
void write(struct Node* user)
{
	struct passage* newPass;
	//�����û��ַ�����д���ļ�
	newPass = (passage*)malloc(sizeof(struct passage));
	newPass->hot = 0;
	newPass->score = 0;
	strcpy(newPass->writer, user->data.name);
	newPass->next = NULL;
	printf("����д����:\n");
	scanf("%s", newPass->title);
	printf("����д��ѧ�ص�:");
	scanf("%s", newPass->site);
	
	//д��
	printf("����д���ݣ�������1000�֣�\n");
	writePassage(newPass);
	//char text[2000];
	//scanf("%s", text);
	//fputs(text, fp);
	//strcpy(newPass->text, text);
	//�ҵ����û���д�����һƪ����
	struct passage* p;
	for (p = user->Passage; p->next != NULL; p = p->next);
	p->next = newPass;
	Passage[nowPassNum] = newPass;
	nowPassNum++;
}

//Ѱ���û�
struct Node* searchUser(char name[])
{
	struct Node* temp = node->next; //printf("������ǣ�%s\n",name);
	while (temp != NULL)
	{
		//printf("����\n");
		//printf("%s%s", temp->data.name, temp->data.password);
		if (strcmp(name, temp->data.name)==0)
		{
			break;
		}
		else
		{
			//printf("��һ��\n");
			temp = temp->next;
		}
	}
	return temp;
}

//��ѧ���°��ص��Ƽ�����
void siteRecommend()
{
	printf("��������ѡ��ĵص�:\n");
	char s[20];
	scanf("%s", s);
	struct passage** recommend = (passage**)malloc(sizeof(struct passage*)*nowPassNum);
	//����Ѱ��site����
	int j = 0;
	for (int i = 0; i < nowPassNum; i++)
	{
		if (strcmp(Passage[i]->site, s) == 0)
		{
			recommend[j] = Passage[i];
			j++;
			recommend[j] = NULL;
		}
	}
	//��site�����½�������(�����ʡȥ)
	for (int i = 0; i < nowPassNum; i++)
	{
		for (int j = 0; j < nowPassNum - i - 1; j++)
		{
			if (recommend[j]->hot < recommend[j + 1]->hot)
			{
				struct passage* temp = recommend[j];
				recommend[j] = recommend[j + 1];
				recommend[j + 1] = temp;
			}
		}
	}
	showList(recommend[0]);
}

//��ȡ�ļ�����
void readPassage(FILE* fp)
{
	while (1)
	{
		char ch = fgetc(fp);
		if (ch == EOF)
			break;
		else
			printf("%c", ch);
	}
}

//д�ļ�����
void writePassage(struct passage* p)
{
	
	FILE* rp = fopen(p->title, "w+");
	//while (1)
	{
		char ch[1000];
		scanf("%s", ch); printf("%s", ch);
		fputs(ch, rp);
		//if (ch == '#')
			//break;
	}
	p->fp = rp;
}