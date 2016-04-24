#include<stdio.h>

#define UL unsigned long
typedef enum
{
	NO_FLAG,
	C_FLAG,
	CPP_FLAG
};
int flag=NO_FLAG;
//定义状态
typedef enum
{
	NO_COMMENT_STATE,
	C_COMMENT_STATE,
	CPP_COMMENT_STATE,
	STR_STATE,
	END_STATE
}STATE_ENUM;

//定义状态机
typedef struct STATE_MACHINE
{
	FILE *inputfile;
	FILE *outputfile;
	STATE_ENUM ulstate;
}STATE_MACHINE;

///////////////////////////////////////////////////
STATE_MACHINE  g_state = {0};
void EventPro(char ch);
void EventProAtNo(char ch);
void EventProAtC(char ch);
void EventProAtCpp(char ch);
void EventProAtStr(char ch);
//////////////////////////////////////////////////

int CommentConvertC(FILE *inputfile, FILE *outputfile)
{
	if(inputfile==NULL || outputfile==NULL)
	{
		printf("Error: Argument Invalid!\n");
		return -1;
	}

	////////////////////////////////////////////////
	//
	g_state.inputfile = inputfile;
	g_state.outputfile = outputfile;
	g_state.ulstate = NO_COMMENT_STATE;
	
	char ch;
	while(g_state.ulstate!= END_STATE)
	{
		ch = fgetc(g_state.inputfile);
		EventPro(ch);
	}
	return 0;
}

void EventPro(char ch)
{
	switch(g_state.ulstate)
	{
	case NO_COMMENT_STATE:
		EventProAtNo(ch);
		break;
	case C_COMMENT_STATE:
		EventProAtC(ch);
		break;
	case CPP_COMMENT_STATE:
		EventProAtCpp(ch);
		break;
	case STR_STATE:
		EventProAtStr(ch);
		break;
	case END_STATE:
		break;
	default:
		break;
	}
}

void EventProAtNo(char ch)
{
	char nextch;
	switch(ch)
	{
	case '/':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/') //C++
		{
			fputc(ch,g_state.outputfile);
			fputc('*',g_state.outputfile);
			g_state.ulstate = CPP_COMMENT_STATE;
		}
		 else if(nextch == '*') // C
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;
		}
		 else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;
		 }
		 break;
	case '"':
		fputc(ch,g_state.outputfile);
		g_state.ulstate =STR_STATE;
		break;
	case EOF:
		fputc(ch,g_state.outputfile);
		g_state.ulstate =END_STATE;
		break;
	default:
		{
			fputc(ch,g_state.outputfile);
			g_state.ulstate =NO_COMMENT_STATE;
			break;
		}
	}
}
void EventProAtC(char ch)
{
	char nextch;
	switch(ch)
	{
	case '"':
		{
			fputc(ch,g_state.outputfile);
			flag=C_FLAG;
			g_state.ulstate=STR_STATE;
			break;
		}
	case '*':
		nextch=fgetc(g_state.inputfile);
		if(nextch=='/')
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate =NO_COMMENT_STATE;
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate =C_COMMENT_STATE;
		}
		break;
		case '/':
			nextch=fgetc(g_state.inputfile);
			if(nextch=='/')
			{
				fputc(' ',g_state.outputfile);
				fputc(' ',g_state.outputfile);
				g_state.ulstate =C_COMMENT_STATE;
			}
			
			else
			{
				fputc(ch,g_state.outputfile);
				fputc(nextch,g_state.outputfile);
				g_state.ulstate =C_COMMENT_STATE;
			}
			break;
		case EOF:
			fputc(ch,g_state.outputfile);
			g_state.ulstate =END_STATE;
			break;
	default:
			fputc(ch,g_state.outputfile);
			g_state.ulstate =C_COMMENT_STATE;
			break;
	}

}
void EventProAtCpp(char ch)
{
	char nextch;
	switch(ch)
	{
	case '\n':
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		fputc('\n',g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		break;
	case '/':
		{
			nextch=getc(g_state.inputfile);
			if(nextch=='/')
			{
				fputc(' ',g_state.outputfile);
				fputc(' ',g_state.outputfile);
				g_state.ulstate = CPP_COMMENT_STATE;
			}
			else if(nextch=='*')
			{
				fputc(' ',g_state.outputfile);
				fputc(' ',g_state.outputfile);
				g_state.ulstate = CPP_COMMENT_STATE;
			}
			else
			{
				fputc(ch,g_state.outputfile);
				fputc(nextch,g_state.outputfile);
				g_state.ulstate = CPP_COMMENT_STATE;
			}
		break;
		}
		
	case '*':
		{
			nextch=fgetc(g_state.inputfile);
			if(nextch=='/')
			{
				fputc(' ',g_state.outputfile);
				fputc(' ',g_state.outputfile);
				g_state.ulstate = CPP_COMMENT_STATE;
			}
			else
			{
				fputc(ch,g_state.outputfile);
				fputc(nextch,g_state.outputfile);
			}
			break;
		}
	case '"':
		{
			fputc(ch,g_state.outputfile);
			flag=CPP_FLAG;
			g_state.ulstate = STR_STATE;
		
		break;
		}	
	default:
		fputc(ch,g_state.outputfile);
		g_state.ulstate = CPP_COMMENT_STATE;
		break;
	}
	
}
void EventProAtStr(char ch)
{
	switch(ch)
	{
		char nextch;
	case '*':
		{
			nextch=getc(g_state.inputfile);
			if(nextch=='/')
			{
				fputc(ch,g_state.outputfile);
				fputc(nextch,g_state.outputfile);
				g_state.ulstate=NO_COMMENT_STATE;
			}
			else
				{
					fputc(ch,g_state.outputfile);
					fputc(nextch,g_state.outputfile);
				}
			break;
		}
	case '\n':
		if(flag==CPP_FLAG)
		{
			fputc('*',g_state.outputfile);
			fputc('/',g_state.outputfile);
			fputc('\n',g_state.outputfile);
			g_state.ulstate=NO_COMMENT_STATE;
		}
		else
			fputc(ch,g_state.outputfile);
		break;

	case '"':
		{
			fputc(ch,g_state.outputfile);
			if(flag==NO_FLAG)
				g_state.ulstate = NO_COMMENT_STATE;
			if(flag==CPP_FLAG)
				g_state.ulstate =CPP_COMMENT_STATE;
			if(flag==C_FLAG)
				g_state.ulstate =C_COMMENT_STATE;
			break;
		}
	case EOF:
		fputc(ch,g_state.outputfile);
		g_state.ulstate =END_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}

}