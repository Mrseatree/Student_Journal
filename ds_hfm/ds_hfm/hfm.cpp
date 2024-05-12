#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;
typedef char** HuffmanCode; //��̬��������洢ÿ���ַ��ĺշ�������� 
typedef struct //�ַ�Ƶ�ȱ� 
{
	int weight; //Ȩֵ 
	char c; //��Ӧ�ַ� 
}F_W;
typedef struct
{
	int weight; //Ȩֵ 
	int parent, lchild, rchild;//˫�׼����Һ���	
	char c; //��Ӧ�ַ� 
}HTNode, * HuffmanTree;
F_W w[100];//�ַ�Ƶ�ȴ������ 
char S1[1000]; //���ַ���������γɵĶ������ַ���������� 
int char_count(string s, char a)  //���㵥���ַ�Ƶ�� 
{
	int i, count = 0;
	for (i = 0; i < s.length(); i++)
		if (s[i] == a) //����ַ�a����һ�� count+1 
			count++;
	return count;
}
void create_w(string s) //�����ַ�Ƶ�ȱ�w 
{
	int i, j, flag;
	w[0].weight = char_count(s, s[0]);//��ͳ�Ƶ�һ���ַ�Ƶ�Ȳ���� 
	w[0].c = s[0];
	int t = 1; //t��ʾ�����ѭ������ 
	for (i = 1; i < s.length(); i++)
	{
		flag = 1; //��ʾ����ַ�֮ǰû�г��ֹ� 
		for (j = 0; j < i; j++)
		{
			if (s[j] == s[i])//�������ַ�֮ǰ�Ѿ����ֹ�
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1) //���֮ǰû���ֹ���ͳ�Ƹ��ַ�Ƶ�Ȳ��Ž�����w 
		{
			w[t].weight = char_count(s, s[i]);
			w[t].c = s[i];
			t++;
		}
	}
}
void Select(HuffmanTree HT, int j, int& s1, int& s2) //�����е��ַ��ڵ�����ѡ����Ȩֵ��С�ĸ�ֵ��s1,s2 
{
	int i, k, min1 = 0, min2 = 0;
	for (i = 1; i <= j; i++)
	{
		if (HT[i].parent != 0) //����ڵ��Ѿ���˫�������ڱȽϷ�Χ�� 
			continue;
		if (HT[min1].weight > HT[i].weight)
			min1 = i;
	}
	for (k = 1; k <= j; k++)
	{
		if (HT[k].parent != 0) //����ڵ��Ѿ���˫�������ڱȽϷ�Χ�� 
			continue;
		if (k == min1)  //���ѭ����min1ֱ��������һ����������min1��ֵ��min2��ֵ��� 
			continue;
		if (HT[min2].weight > HT[k].weight)
		{
			min2 = k;
		}
	}
	s1 = min1;
	s2 = min2;
}
int Init(HuffmanTree& HT, F_W* w, int n) //��ʼ���շ����� 
{
	if (n <= 1)
		return 0;
	int m = 2 * n - 1, i; //m��ʾ�ܽ����
	int s1, s2; //�洢��С���ڵ�ı���
	HuffmanTree p;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//0�Ų����� 
	HT[0].weight = 999;//Ĭ��0��Ϊ���Ȩֵ��Ϊ�����min1,min2��Ĭ��ֵ 
	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)  //��n���ַ�����Ӧ�ĵ������ڵ㸳��Ȩֵ 
	{
		p->lchild = p->rchild = p->parent = 0;
		p->weight = w->weight;
		p->c = w->c;
	}
	for (; i <= m; i++) //��ʣ�µķ�֧�ڵ���Ϊ�� 
		p->lchild = p->rchild = p->parent = p->weight = 0;
	for (i = n + 1; i <= m; i++) //�����շ�����
	{
		Select(HT, i - 1, s1, s2); //ѡ��������С�Ľڵ� 
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;   //Ȩֵ�ϲ�Ϊһ���½ڵ� 
		HT[i].parent = 0;
	}
	return 1;
}
int CreateTable(HuffmanCode& HC, HuffmanTree HT, int n)  //��������� ��ÿ���ַ����б���
{
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	char* cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	int start, c, i, f;
	for (i = 1; i <= n; ++i)
	{
		start = n - 1; //���������λ��
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c) cd[--start] = '0';  //���֧����0�ҷ�֧����1 
			else cd[--start] = '1';
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
	return 1;
}
int Encoding(string S, int n, HuffmanCode HC) //�����ַ��� 
{
	int i, j;
	for (i = 0; i < S.length(); i++)
	{
		for (j = 0; j < n; j++) //��Ƶ�ȱ����Ҷ�Ӧ���ַ� 
			if (w[j].c == S[i])
			{
				strcat(S1, HC[j + 1]);
			}  //�����ַ��ĺշ���������S���� 

	}
	return 1;
}
int Decoding(HuffmanTree HT, HuffmanCode HC, int n) //����
{
	int m = 2 * n - 1, i = 0, j;
	while (S1[i] != '\0')
	{
		if (S1[i] == '0')
			m = HT[m].lchild;
		else
			m = HT[m].rchild;
		if (HT[m].lchild == 0) //�ҵ�Ҷ�ӽڵ�(�շ����������������ڵ㣬����ֻ���ж�һ��������Һ���)	
		{
			for (j = 0; j < n; j++)
				if (w[j].weight == HT[m].weight && HT[m].c == w[j].c) //�ҵ�Ȩֵ��Ӧ���ַ� 
					cout << w[j].c; //��� 
			m = 2 * n - 1; //���´Ӹ��ڵ���� 
		}
		i++;
	}
	return 1;
}
int main()
{
	string s;
	int n = 0, i;
	//cin >> s;
	ifstream file;
	file.open("test2.txt", ios::in);
	if (!file.is_open()) {
		std::cerr << "�޷����ļ�" << std::endl;
		return 1;
	}

	string line;
	while (getline(file, line)) { // ���ж�ȡ�ļ�����
		std::cout << line << std::endl; // ���ÿһ��
		s.append(line);
	}file.close();
	create_w(s);
	HuffmanTree HT;
	HuffmanCode HC;
	for (i = 0; w[i].weight != 0; i++)
		n++;
	Init(HT, w, n);
	CreateTable(HC, HT, n);
	cout << "�����Ϊ��" << endl;
	for (i = 1; i <= n; i++)
		cout << w[i - 1].c << ":" << HC[i] << " ";
	cout << endl;
	cout << "����Ϊ��" << endl;
	Encoding(s, n, HC);
	cout << S1 << endl;
	cout << "����Ϊ��" << endl;
	Decoding(HT, HC, n);
	return 0;
}

