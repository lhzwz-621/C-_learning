#define _CRT_SECURE_NO_WARNINGS 1
#include "Contacts.h"

#define SAVE_FILE "contacts.dat"

// 清空输入缓冲区，防止输入字母导致死循环
void ClearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int main(void)
{
	CT ct;
	InitContacts(&ct);
	LoadContacts(&ct, SAVE_FILE);	//启动时自动加载存档

	int choice = 0;
	do
	{
		ShowMenu();
		
		// 防止用户输入非数字导致死循环
		if (scanf("%d", &choice) != 1)
		{
			ClearInputBuffer();
			printf("输入无效，请输入数字选项！\n");
			system("pause"); // 暂停让用户看清提示
			system("cls");   // 清屏
			continue;
		}

		switch (choice)
		{
		case 1:	//添加联系人
			CreateContact(&ct);
			break;

		case 2:	//删除联系人
		{
			char id[ID_LENGTH];
			printf("请输入要删除的学号：");
			scanf("%s", id);
			DeleteContactByID(&ct, id);
			break;
		}

		case 3:	//修改联系人
		{
			char id[ID_LENGTH];
			printf("请输入要修改的学号：");
			scanf("%s", id);
			ModifyContactByID(&ct, id);
			break;
		}

		case 4:	//按学号查找
		{
			char id[ID_LENGTH];
			printf("请输入学号：");
			scanf("%s", id);
			int idx = FindContactByID(&ct, id);
			if (idx != -1)
				PrintContact(&ct.cp[idx]);
			else
				printf("查无此人！\n");
			break;
		}

		case 5:	//按姓名查找
		{
			char name[NAME_LENGTH];
			printf("请输入姓名：");
			scanf("%s", name);
			int idx = FindContactByName(&ct, name);
			if (idx != -1)
				PrintContact(&ct.cp[idx]);
			else
				printf("查无此人！\n");
			break;
		}

		case 6:	//按电话查找
		{
			char phone[PHONE_LENGTH];
			printf("请输入电话号码：");
			scanf("%s", phone);
			int idx = FindContactByPhone(&ct, phone);
			if (idx != -1)
				PrintContact(&ct.cp[idx]);
			else
				printf("查无此人！\n");
			break;
		}

		case 7:	//显示所有联系人
			PrintALLContacts(&ct);
			break;

		case 8:	//按姓名排序
			SortContactsByName(&ct);
			break;

		case 9:	//保存到文件
			SaveContacts(&ct, SAVE_FILE);
			break;

		case 0:	//退出（自动保存）
			SaveContacts(&ct, SAVE_FILE);
			printf("已退出，数据已自动保存。\n");
			break;

		default:
			printf("无效选项，请重新选择！\n");
			break;
		}

		// 如果不是退出操作，暂停一下让用户看清输出结果，然后清屏
		if (choice != 0)
		{
			printf("\n");
			system("pause"); // 提示“请按任意键继续...”.
			system("cls");   // 清除屏幕，保持界面整洁
		}

	} while (choice != 0);

	DestroyContacts(&ct);
	return 0;
}