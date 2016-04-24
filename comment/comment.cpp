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
		printf("*                注释转换                                     *\n");
		printf("*                1.C++注释转换为C                             *\n");
		printf("*                2.C注释转换为C++                             *\n");
		printf("*                3.退出                                       *\n");
		printf("***************************************************************\n");
		scanf("%d",&xuanze);
		if(xuanze==3)
			break;
		else
		{
			printf("请输入您要转换文件的路径");
			scanf("%s",input);
			printf("请输入您要转换文件的路径");
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
				printf("转换完成\n");
			}
			else if(xuanze==1)
			{
				CommentConvertC(fpIn,fpOut);
				printf("转换完成\n");
			}
			fclose(fpIn);
			fclose(fpOut);
			system("pause");
		}
		system("cls");
	}
	return 0;
}