#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include "base64.h"

#define Account_size 20										  //�˺ŵĳ���
#define Password_size 20									  //����ĳ���
#define Password_base64_encode_size Password_size * 4 / 3 + 3 //base64����������ԭ����4/3
#define filename_size Account_size + 8						  //�ļ����ĳ���

//�ļ����ַ������庯��
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
		/**************************************ע�����*******************************************/
		/*****************************************************************************************/

		switch (operation)
		{
		register_again://����ע��ʧ��ʱ����
		case 1: //ִ��ע�����
		{
			system("cls");
			char Filename[filename_size] = {""};//�ļ���
			char Account[Account_size] = {""};//�˺�
			char Password[Password_size] = {""};//����
			char *Password_base64_encode = NULL;//����֮�������

			memset(Filename, 0, filename_size);//����ļ���

			//����ע�����˺�����
			printf("�������˺�(20λ����):\n");
			scanf("%s", Account);

			//��������Ƿ�Ϲ�
			if (filename_strcat(Account, Filename) < 0)
			{
				printf("�����˺��ַ��������");
				break;
			}

			FILE *p1 = fopen(Filename, "r"); //�򿪶�Ӧ�ļ�
			//����Ƿ��Ѿ�ע��
			if (p1 == NULL) //δע�����ڽ���ע��
			{
				printf("�˺�δ��ע��\n�������������(20λ����):\n");

				scanf("%s", Password);//��������
				Password_base64_encode = base64_encode(Password, strlen(Password));//����
				/*****************ע�����*****************/
				FILE *p1 = fopen(Filename, "w");//�������ļ�
				fprintf(p1, "%s\n%s", Account, Password_base64_encode);//д���˺źͼ���֮�������
				printf("ע��ɹ�!!");
				fclose(p1); //�ͷ��ļ�ָ��
			}
			else
			{
				printf("�˺��ѱ�ע��!\n");
				fclose(p1); //�ͷ��ļ�ָ��
				goto register_again;
			}
			Sleep(3000); //����3s
			system("cls");
			break;
		}

			/*****************************************************************************************/
			/**************************************��½����*******************************************/
			/*****************************************************************************************/

		sign_in_again://��½ʧ��ʱ����
		case 2:
		{
			char Filename[filename_size] = {""};//�ļ���
			char Account[Account_size] = {""};//�˺�
			char Password[Password_size] = {""};//����
			char *Password_base64_encode = NULL;//���ܵ���ȷ����
			char Password_base64_encode_cmp[Password_base64_encode_size] = {""};//���ܺ����������

			printf("����������˺�:");
			scanf("%s", Account);//�����˺�

			//��������Ƿ�Ϲ�
			if (filename_strcat(Account, Filename) < 0)
			{
				printf("�����˺��ַ��������");
				break;
			}

			FILE *p1 = fopen(Filename, "r"); //�򿪶�Ӧ�ļ�

			//����˺��Ƿ����
			if (p1 == NULL) //�˺Ų�����
			{
				printf("�˺Ų�����!\n");
				fclose(p1); //�ͷ�ָ��
				goto sign_in_again;//����
			}
			else//�˺Ŵ���
			{
				FILE *p1 = fopen(Filename, "r");//�򿪶�Ӧ�˺������ļ�
				fscanf(p1, "%s\n%s", Account, Password_base64_encode_cmp);//ȡ�üӼ��ܺ������

				printf("�������������:");
				scanf("%s", Password);//��������

				Password_base64_encode = base64_encode(Password, strlen(Password));//���ܺ����ȷ�����������������ܺ�Ա�

				/*****************��֤����*****************/

				if (strcmp(Password_base64_encode, Password_base64_encode_cmp) == 0)
				{
					//������ȷ
					printf("��½�ɹ���\n");
					Sleep(1000); //����1s
					printf("��½�ɹ�Ҫ�����Ҳ��֪��\n");
					Sleep(1000); //����1s
					printf("�Ǿ�������\n");
				}
				else
				{
					//�������
					printf("�������");
					Sleep(3000); //����3s
					system("cls");
					goto sign_in_again;//����
				}
			}
			Sleep(3000); //����3s
			system("cls");
			break;
		}
		default:
		{
			printf("Invalid input");//û����ע����ߵ�¼ϵͳ
			Sleep(3000); //����3s
			system("cls");
			break;
		}
		}
			/*****************************************************************************************/
			/**************************************�˳�����*******************************************/
			/*****************************************************************************************/
		printf("exit?\n����Y���˳�,�����������\n:");

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
