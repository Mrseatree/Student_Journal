#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <locale>
#include <Windows.h>

using namespace std;

#ifndef JOURNEY_HEAD_H
#define JOURNEY_HEAD_H
//#pragma  execution_character_set("ANSI")
#define N 50
#define MaxLen 20

extern int nowPassNum;
extern int nowUserNum;
extern struct Node* node;//node根节点
extern struct passage* Passage[N];//所有文章的根节点
extern struct student* stu;

struct passage
{
	char title[MaxLen];
	char writer[MaxLen];
	char site[MaxLen];
	int hot;
	float score;
	char text[1000];
	FILE* fp;
	struct passage* next;
};

struct student 
{
	char name[MaxLen];
	char password[MaxLen];
};

struct Node
{
	struct student data;//学生
	struct passage* Passage;//学生所写的文章
	struct Node* next;
};

struct Node* createNode(struct student* p);
void initNode();
void Welcome();
void showList(struct passage* p);
void showPass(struct passage* p);
void recommendsort();
struct passage* searchPass();
void write(struct Node* user);
struct Node* searchUser(char name[]);
void siteRecommend();
void load();
void readPassage(FILE* fp);
void writePassage(struct passage*);

#endif //journey_head_H
