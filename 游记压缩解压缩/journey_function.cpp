#include"journey_head.h"
//创建链表节点
struct Node* createNode(struct student* p)
{
	//printf("开始创建新用户%s...\n",p->name);
	struct Node* pNew = (Node*)malloc(sizeof(struct Node));
	if (pNew == NULL)
	{
		wprintf(L"申请失败*-*\n");
		return NULL;
	}
	pNew->next = NULL;
	pNew->Passage = (passage*)malloc(sizeof(struct passage));
	pNew->Passage->next = NULL;
	strcpy(pNew->data.name, p->name);
	strcpy(pNew->data.password, p->password);
	//printf("新建用户完成\n");
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

//展示推荐列表
void showList(struct passage* p)
{
	struct passage* cur = p;
	while (cur != NULL)
	{
		printf("%s\n", cur->title);
		printf("作者:%s\n", cur->writer);
		printf("热度:%d\n", cur->hot);
		printf("游学地点:%s\n", cur->site);
		printf("\n");
		cur = cur->next;
	}
}

//查看文章、打分在此函数完成
void showPass(struct passage* p)
{
	printf("作者：%s\n", p->writer);
	printf("热度：%d	分数：%.1f\n", p->hot,p->score);
	printf("游学地点：%s\n", p->site);
	printf("%s\n", p->title);
	//输出
	printf("%s\n", p->text);
	readPassage(p->fp);

	printf("请打分（0-5）：\n");
	int score = 0;
	scanf("%d", &score);
	p->hot++;	
	p->score = (p->score + score) / p->hot;
}

//所有文章按热度排序
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

//寻找文章
struct passage* searchPass()
{
	printf("请输入查找的文章\n");
	//读入字符串并进行查找
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
		printf("空空如也呢*_*\n");
	}
	else
	{
		//printf("%s\n", Passage[mid]->title);
		showPass(Passage[mid]);
		return Passage[mid];
	}
	return NULL;
}

//写文章
void write(struct Node* user)
{
	struct passage* newPass;
	//读入用户字符串并写入文件
	newPass = (passage*)malloc(sizeof(struct passage));
	newPass->hot = 0;
	newPass->score = 0;
	strcpy(newPass->writer, user->data.name);
	newPass->next = NULL;
	printf("请填写标题:\n");
	scanf("%s", newPass->title);
	printf("请填写游学地点:");
	scanf("%s", newPass->site);
	
	//写入
	printf("请填写内容（不超过1000字）\n");
	writePassage(newPass);
	//char text[2000];
	//scanf("%s", text);
	//fputs(text, fp);
	//strcpy(newPass->text, text);
	//找到该用户所写的最后一篇文章
	struct passage* p;
	for (p = user->Passage; p->next != NULL; p = p->next);
	p->next = newPass;
	Passage[nowPassNum] = newPass;
	nowPassNum++;
}

//寻找用户
struct Node* searchUser(char name[])
{
	struct Node* temp = node->next; //printf("输入的是：%s\n",name);
	while (temp != NULL)
	{
		//printf("查找\n");
		//printf("%s%s", temp->data.name, temp->data.password);
		if (strcmp(name, temp->data.name)==0)
		{
			break;
		}
		else
		{
			//printf("下一个\n");
			temp = temp->next;
		}
	}
	return temp;
}

//游学文章按地点推荐排序
void siteRecommend()
{
	printf("请输入所选择的地点:\n");
	char s[20];
	scanf("%s", s);
	struct passage** recommend = (passage**)malloc(sizeof(struct passage*)*nowPassNum);
	//遍历寻找site文章
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
	//对site的文章进行排序(或许可省去)
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

//读取文件内容
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

//写文件内容
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