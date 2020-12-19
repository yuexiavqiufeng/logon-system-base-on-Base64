#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include "base64.h"

#define Account_size 20										  //账号的长度
#define Password_size 20									  //密码的长度
#define Password_base64_encode_size Password_size * 4 / 3 + 3 //base64编码后体积是原来的4/3
#define filename_size Account_size + 8						  //文件名的长度

//文件名字符串定义函数
int filename_strcat(char *account, char *file_name)
{

	strcat(file_name, "file_");
	if (strlen(account) > filename_size - 9)
	{
		return -1;
	}
	strcat(file_name, account);
	strcat(file_name, ".dat");

	return 0;
}

int main()
{

	int operation;

	while (1)
	{

		printf("hello!\nregister:1\nSign in:2\n");
		operation = getchar() - 48;
		/*****************************************************************************************/
		/**************************************注册程序*******************************************/
		/*****************************************************************************************/

		switch (operation)
		{
		register_again://用作注册失败时重启
		case 1: //执行注册操作
		{
			system("cls");
			char Filename[filename_size] = {""};//文件名
			char Account[Account_size] = {""};//账号
			char Password[Password_size] = {""};//密码
			char *Password_base64_encode = NULL;//加密之后的密码

			memset(Filename, 0, filename_size);//清空文件名

			//输入注册用账号密码
			printf("请输入账号(20位以内):\n");
			scanf("%s", Account);

			//检测输入是否合规
			if (filename_strcat(Account, Filename) < 0)
			{
				printf("超出账号字符数最大限");
				break;
			}

			FILE *p1 = fopen(Filename, "r"); //打开对应文件
			//检测是否已经注册
			if (p1 == NULL) //未注册现在进行注册
			{
				printf("账号未被注册\n请输入你的密码(20位以内):\n");

				scanf("%s", Password);//输入密码
				Password_base64_encode = base64_encode(Password, strlen(Password));//加密
				/*****************注册操作*****************/
				FILE *p1 = fopen(Filename, "w");//打开数据文件
				fprintf(p1, "%s\n%s", Account, Password_base64_encode);//写入账号和加密之后的密码
				printf("注册成功!!");
				fclose(p1); //释放文件指针
			}
			else
			{
				printf("账号已被注册!\n");
				fclose(p1); //释放文件指针
				goto register_again;
			}
			Sleep(3000); //挂起3s
			system("cls");
			break;
		}

			/*****************************************************************************************/
			/**************************************登陆程序*******************************************/
			/*****************************************************************************************/

		sign_in_again://登陆失败时重启
		case 2:
		{
			char Filename[filename_size] = {""};//文件名
			char Account[Account_size] = {""};//账号
			char Password[Password_size] = {""};//密码
			char *Password_base64_encode = NULL;//加密的正确密码
			char Password_base64_encode_cmp[Password_base64_encode_size] = {""};//加密后输入的密码

			printf("请输入你的账号:");
			scanf("%s", Account);//输入账号

			//检测输入是否合规
			if (filename_strcat(Account, Filename) < 0)
			{
				printf("超出账号字符数最大限");
				break;
			}

			FILE *p1 = fopen(Filename, "r"); //打开对应文件

			//检测账号是否存在
			if (p1 == NULL) //账号不存在
			{
				printf("账号不存在!\n");
				fclose(p1); //释放指针
				goto sign_in_again;//重启
			}
			else//账号存在
			{
				FILE *p1 = fopen(Filename, "r");//打开对应账号数据文件
				fscanf(p1, "%s\n%s", Account, Password_base64_encode_cmp);//取得加加密后的密码

				printf("请输入你的密码:");
				scanf("%s", Password);//输入密码

				Password_base64_encode = base64_encode(Password, strlen(Password));//加密后的正确密码与输入的密码加密后对比

				/*****************验证密码*****************/

				if (strcmp(Password_base64_encode, Password_base64_encode_cmp) == 0)
				{
					//密码正确
					printf("登陆成功！\n");
					Sleep(1000); //挂起1s
					printf("登陆成功要干嘛，我也不知道\n");
					Sleep(1000); //挂起1s
					printf("那就这样吧\n");
				}
				else
				{
					//密码错误
					printf("密码错误！");
					Sleep(3000); //挂起3s
					system("cls");
					goto sign_in_again;//重启
				}
			}
			Sleep(3000); //挂起3s
			system("cls");
			break;
		}
		default:
		{
			printf("Invalid input");//没进入注册或者登录系统
			Sleep(3000); //挂起3s
			system("cls");
			break;
		}
		}
			/*****************************************************************************************/
			/**************************************退出程序*******************************************/
			/*****************************************************************************************/
		printf("exit?\n输入Y键退出,按任意键重启\n:");

		if ('Y' == getchar() || 'y' == getchar())
		{
			return 0;
		}
		else
		{
			system("cls");
		}
	}

	return 0;
}
