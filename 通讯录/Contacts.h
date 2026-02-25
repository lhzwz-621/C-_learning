#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#define NAME_LENGTH 20	// 设name数组长度为20
#define ID_LENGTH 10	// 设学号数组长度为10
#define SEX_LENGTH 5	// 设性别数组长度为5
#define PHONE_LENGTH 20	// 设电话号码数组长度为20
#define ADDRESS_LENGTH 50	// 设地址数组长度为50
#define EMAIL_LENGTH 30	// 设邮箱数组长度为30
#define POSTCODE_LENGTH 10	// 设邮编数组长度为10

typedef struct ContactPerson CP;
typedef struct Contacts CT;


struct ContactPerson	//存储联系人信息的结构体
{
	char name[NAME_LENGTH];
	char ID[ID_LENGTH];
	char sex[SEX_LENGTH];
	char phone[PHONE_LENGTH];
	char address[ADDRESS_LENGTH];
	char email[EMAIL_LENGTH];
	char postcode[POSTCODE_LENGTH];
};

struct Contacts	//用顺序表方式存储联系人信息的结构体
{
	CP* cp;	//联系人数组，利用动态内存分配实现
	int size;	//联系人数组的大小;也可以用来计算联系人数量
	int capacity;	//联系人数组的容量
};

//尝试使用迭代器来遍历联系人信息，定义一个迭代器结构体
typedef struct
{
	CT* ct;	//指向联系人信息的指针
	int curIndex;	//当前迭代器指向的联系人信息的索引
} Iterator;

//迭代器功能
Iterator IteratorBegin(CT* ct);	//用来创建迭代器，指向第一个联系人信息
void IteratorNext(Iterator* it);	//用来将迭代器指向下一个联系人信息
CP* IteratorGet(Iterator* it);	//用来获取迭代器当前指向的联系人信息
int IteratorIsEnd(Iterator* it);	//用来判断迭代器是否到达末尾

void CTCheck(CT* ct);	//检查存储空间是否足够，不够则扩容
void InitContacts(CT* ct);	//初始化联系人信息
void DestroyContacts(CT* ct);	//销毁联系人信息，释放动态内存
void CreateContact(CT* ct);	//创建联系人信息
void AddContact(CT* ct,const CP* cp);	//添加联系人信息

//查找
int FindContactByID(CT* ct, const char* ID);	//根据学号查找联系人信息，返回索引
int FindContactByName(CT* ct, const char* name);	//根据姓名查找联系人信息，返回索引
int FindContactByPhone(CT* ct, const char* phone);	//根据电话号码查找联系人信息，返回索引

//删除
void DeleteContactByID(CT* ct, const char* ID);	//根据学号删除联系人信息
//修改
void ModifyContactByID(CT* ct, const char* ID);	//根据学号修改联系人信息

//==========扩张功能实现==========

//打印对齐表格
void PrintALLContacts(CT* ct);	//打印所有联系人信息，格式为表格形式
void PrintContact(const CP* cp);	//打印单个联系人信息，格式为表格形式
void SortContactsByName(CT* ct);	//按姓名排序联系人信息
//文件处理操作
void SaveContacts(CT* ct, const char* filename);	//将联系人信息保存到文件中
void LoadContacts(CT* ct, const char* filename);	//从文件中加载联系人信息




// 主菜单
void ShowMenu(void);