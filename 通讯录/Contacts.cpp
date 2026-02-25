#define  _CRT_SECURE_NO_WARNINGS 1
#include"Contacts.h"

void CTCheck(CT* ct)	//检查存储空间是否足够，不够则扩容
{
	assert(ct);
	if (ct->size == ct->capacity)	//如果联系人数已满，扩容
	{
		int tmp = ct->capacity == 0 ? 4 : ct->capacity * 2;
		CP* newcp = (CP*)realloc(ct->cp, tmp * sizeof(CP));
		if (newcp == NULL)
		{
			perror("realloc failed");
			exit(1);
		}
		ct->cp = newcp;
		ct->capacity = tmp;
	}
}


void InitContacts(CT* ct)	//初始化联系信息
{
	ct->cp = NULL;
	ct->size = ct->capacity = 0;
}

void DestroyContacts(CT* ct)	//销毁联系人信息，释放动态内存
{
	assert(ct);
	free(ct->cp);
	ct->cp = NULL;
	ct->capacity = ct->size = 0;
}

void CreateContact(CT* ct)	//创建联系人信息
{
	assert(ct);
	CP newcp;
	printf("请输入学号：");
	scanf("%s", newcp.ID);
	if(FindContactByID(ct, newcp.ID) != -1)	//如果学号已存在，提示用户重新输入
	{
		printf("学号已存在，请重新输入！\n");
		return;
	}
	printf("请输入姓名：");
	scanf("%s", newcp.name);
	printf("请输入性别：");
	scanf("%s", newcp.sex);
	printf("请输入电话号码：");
	scanf("%s", newcp.phone);
	printf("请输入地址：");
	scanf(" %[^\n]", newcp.address);	// 以空格为分隔符输入地址，直到遇到换行符为止
	printf("请输入邮箱：");
	scanf("%s", newcp.email);
	printf("请输入邮编：");
	scanf("%s", newcp.postcode);
	AddContact(ct, &newcp);
}


void AddContact(CT* ct,const CP* newcp)	//添加联系人信息
{
	assert(ct);
	CTCheck(ct);	//检查存储空间是否足够，不够则扩容
	ct->cp[ct->size++] = *newcp;
}

int FindContactByID(CT* ct, const char* ID)	//根据学号查找联系人信息，返回索引
{
	assert(ct);
	for (int i = 0; i < ct->size; i++)
	{
		if (strcmp(ct->cp[i].ID, ID) == 0)
		{
			return i;
		}
	}
	return -1;	//未找到
}

int FindContactByName(CT* ct, const char* name)	//根据姓名查找联系人信息，返回索引
{
	assert(ct);
	for (int i = 0; i < ct->size; i++)
	{
		if (strcmp(ct->cp[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;	//未找到
}

int FindContactByPhone(CT* ct, const char* phone)	//根据电话号码查找联系人信息，返回索引
{
	assert(ct);
	for (int i = 0; i < ct->size; i++)
	{
		if (strcmp(ct->cp[i].phone, phone) == 0)
		{
			return i;
		}
	}
	return -1;	//未找到
}


void DeleteContactByID(CT* ct, const char* ID)	//根据学号删除联系人信息
{
	assert(ct);
	int index = FindContactByID(ct, ID);
	if (index != -1)
	{
		for (int i = index; i < ct->size - 1; i++)
		{
			ct->cp[i] = ct->cp[i + 1];	//将后面的联系人信息前移
		}
		ct->size--;	//更新联系人数量
		printf("学号%s的联系人信息已删除！\n", ID);
	}
	else
	{
		printf("查无此人，删除失败！\n");
	}
}

void ModifyContactByID(CT* ct, const char* ID)	//根据学号修改联系人信息
{
	assert(ct);
	int index = FindContactByID(ct, ID);
	if (index != -1)
	{
		CP newcp;
		printf("请输入新的学号：");
		scanf("%s", newcp.ID);
		//查看输入的新学号是否已存在，且不是当前联系人的学号
		int conflict = FindContactByID(ct, newcp.ID);
		if (conflict != -1 && conflict != index)
		{
			printf("学号已存在，请重新输入！\n");
			return;
		}
		printf("请输入姓名：");
		scanf("%s", newcp.name);
		printf("请输入性别：");
		scanf("%s", newcp.sex);
		printf("请输入电话号码：");
		scanf("%s", newcp.phone);
		printf("请输入地址：");
		scanf(" %[^\n]", newcp.address);	// 以空格为分隔符输入地址，直到遇到换行符为止
		printf("请输入邮箱：");
		scanf("%s", newcp.email);
		printf("请输入邮编：");
		scanf("%s", newcp.postcode);
		ct->cp[index] = newcp;	//更新联系人信息
		printf("联系人信息已修改！\n");
	}
	else
	{
		printf("查无此人，修改失败！\n");
	}
}


//迭代器功能
Iterator IteratorBegin(CT* ct)	//用来创建迭代器，指向第一个联系人信息
{
	assert(ct);
	//初始化迭代器
	Iterator it;
	it.ct = ct;
	it.curIndex = 0;
	return it;
}

void IteratorNext(Iterator* it)	//用来将迭代器指向下一个联系人信息
{
	assert(it);
	it->curIndex++;
}

CP* IteratorGet(Iterator* it)	//用来获取迭代器当前指向的联系人信息
{
	assert(it);
	if (it->curIndex < it->ct->size)
	{
		return &(it->ct->cp[it->curIndex]);
	}
	return NULL;
}
int IteratorIsEnd(Iterator* it)	//用来判断迭代器是否到达末尾
{
	assert(it);
	return it->ct->size == it->curIndex;
}

void PrintALLContacts(CT* ct)	//打印所有联系人信息，格式为表格形式
{
	assert(ct);
	if (ct->size == 0)
	{
		printf("通讯录为空！\n");
		return;
	}
	printf("%-10s %-8s %-4s %-13s %-20s %-20s %-10s\n",
		"学号", "姓名", "性别", "电话", "地址", "邮箱", "邮编");
	printf("%-10s %-8s %-4s %-13s %-20s %-20s %-10s\n",
		"----------", "--------", "----", "-------------",
		"--------------------", "--------------------", "----------");
	Iterator it = IteratorBegin(ct);
	while (!IteratorIsEnd(&it))
	{
		CP* p = IteratorGet(&it);
		printf("%-10s %-8s %-4s %-13s %-20s %-20s %-10s\n",
			p->ID, p->name, p->sex, p->phone,
			p->address, p->email, p->postcode);
		IteratorNext(&it);
	}
}


void PrintContact(const CP* cp)	//打印单个联系人信息，格式为表格形式
{
	assert(cp);
	printf("%-10s %-8s %-4s %-13s %-20s %-20s %-10s\n",
		"学号", "姓名", "性别", "电话", "地址", "邮箱", "邮编");
	printf("%-10s %-8s %-4s %-13s %-20s %-20s %-10s\n",
		"----------", "--------", "----", "-------------",
		"--------------------", "--------------------", "----------");
	printf("%-10s %-8s %-4s %-13s %-20s %-20s %-10s\n",
		cp->ID, cp->name, cp->sex, cp->phone,
		cp->address, cp->email, cp->postcode);
}

static int CompareByName(const void* a, const void* b)
{
	return strcmp(((CP*)a)->name, ((CP*)b)->name);
}

void SortContactsByName(CT* ct)	//按姓名排序联系人信息
{
	assert(ct);
	if (ct->size == 0)
	{
		printf("通讯录为空！\n");
		return;
	}
	qsort(ct->cp, ct->size, sizeof(CP), CompareByName);	//使用qsort函数按姓名排序联系人信息
	printf("联系人信息已按姓名排序！\n");

}



//文件处理操作
void SaveContacts(CT* ct, const char* filename)	//将联系人信息保存到文件中
{
	assert(ct);
	FILE* fp = fopen(filename, "wb");
	if (fp == NULL)
	{
		perror("保存失败,文件打开失败");
		return;
	}
	fwrite(&ct->size, sizeof(int), 1, fp);	//先写入联系人数量
	fwrite(ct->cp, sizeof(CP), ct->size, fp);	//再写入联系人信息
	fclose(fp);
	printf("已保存%d条联系人信息到文件%s！\n", ct->size, filename);
}

void LoadContacts(CT* ct, const char* filename)	//从文件中加载联系人信息
{
	assert(ct);
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		printf("加载失败，文件打开失败");
		return;
	}
	int count = 0;
	fread(&count, sizeof(int), 1, fp);	//先读取联系人数量
	for (int i = 0; i < count; i++)
	{
		CP tmp;
		fread(&tmp, sizeof(CP), 1, fp);	//再读取联系人信息
		AddContact(ct, &tmp);	//添加到联系人信息中
	}
	fclose(fp);
	printf("已从文件%s加载%d条联系人信息！\n", filename, count);
}

// 主菜单
void ShowMenu(void)
{
	printf("\n========== 通讯录管理系统 ==========\n");
	printf("  1. 添加联系人\n");
	printf("  2. 删除联系人（按学号）\n");
	printf("  3. 修改联系人（按学号）\n");
	printf("  4. 查找联系人（按学号）\n");
	printf("  5. 查找联系人（按姓名）\n");
	printf("  6. 查找联系人（按电话）\n");
	printf("  7. 显示所有联系人\n");
	printf("  8. 按姓名排序\n");
	printf("  9. 保存到文件\n");
	printf("  0. 退出\n");
	printf("=====================================\n");
	printf("请选择：");
}

