#include<stdio.h>
#include<stdlib.h>

/****************************************
 * Function name:  main
 * Argument     :  void
 * Destribute   :  
 * Return value :
 * when   why   what    who
 * 
 ****************************************/

extern int CommentConvertCPP(FILE *, FILE *);
extern int CommentConvertC(FILE *, FILE *);

int main()
{
	while(1)
	{
		FILE *fpIn;
		FILE *fpOut;
		int xuanze;
		char input[50];
		char output[50];
		printf("***************************************************************\n");
		printf("*                ע��ת��                                     *\n");
		printf("*                1.C++ע��ת��ΪC                             *\n");
		printf("*                2.Cע��ת��ΪC++                             *\n");
		printf("*                3.�˳�                                       *\n");
		printf("***************************************************************\n");
		scanf("%d",&xuanze);
		if(xuanze==3)
			break;
		else
		{
			printf("��������Ҫת���ļ���·��");
			scanf("%s",input);
			printf("��������Ҫת���ļ���·��");
			scanf("%s",output);
			fpIn = fopen(input,"r");
			if(NULL == fpIn)
			{
				printf("Error: Open input.c file fail!\n");
				return -1;
			}
			fpOut = fopen(output,"w");
			if(NULL == fpOut)
			{
				printf("Error: Open output.c file fail!\n");
				return -1;
			}
			if(xuanze==2)
			{
				CommentConvertCPP(fpIn,fpOut);
				printf("ת�����\n");
			}
			else if(xuanze==1)
			{
				CommentConvertC(fpIn,fpOut);
				printf("ת�����\n");
			}
			fclose(fpIn);
			fclose(fpOut);
			system("pause");
		}
		system("cls");
	}
	return 0;
}