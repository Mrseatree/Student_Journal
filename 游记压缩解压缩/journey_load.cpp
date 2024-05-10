#include"journey_head.h"

void load()
{
	//std::setlocale(LC_ALL, ".UTF-8");
	FILE* fp = fopen("user1.txt", "r");		
	if (fp != NULL)
	{
		int i = 0;

		struct Node* t = node;
		while (i<nowUserNum)
		{
			char user[MaxLen];
			char password[MaxLen]; 
			char* USER = fgets(user, MaxLen, fp);
			char* PASS = fgets(password, MaxLen, fp);
			
			//²âÊÔµã
			//printf("strlen:%d %d\n", strlen(user), strlen(password));
			printf("%s%s", user, password); cout << user << password << endl;
			//printf("STRLEN:%d %d\n", strlen(USER), strlen(PASS));
			
			struct student* p = (student*)malloc(sizeof(struct student));
			int u = strlen(USER) - 1;
			int pw = strlen(PASS) - 1;
			memcpy(p->name, USER, u); p->name[u] = '\0';
			memcpy(p->password, PASS, pw); p->password[pw]='\0';
			
			//²âÊÔµã
			//printf("STRLEN:%d %d\n", strlen(p->name), strlen(p->password));
			//printf("%s,PASS:%send\n", p->name, p->password);
			//printf("%c\n", p->name[u-1]);

			for (; t->next != NULL; t = t->next);
			t->next=createNode(p); 
			i++;
		}
	}
}