#include <stdio.h>

#define UL unsigned long
typedef enum
{
	NO_FLAG,
	C_FLAG,
	CPP_FLAG
};
int flag1=NO_FLAG;
int C_STATE1=0;
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
STATE_MACHINE  g1_state = {0};
void EventPro1(char ch);
void EventProAtNo1(char ch);
void EventProAtC1(char ch);
void EventProAtCpp1(char ch);
void EventProAtStr1(char ch);
//////////////////////////////////////////////////

int CommentConvertCPP(FILE *inputfile, FILE *outputfile)
{
	if(inputfile==NULL || outputfile==NULL)
	{
		printf("Error: Argument Invalid!\n");
		return -1;
	}

	////////////////////////////////////////////////
	//
	g1_state.inputfile = inputfile;
	g1_state.outputfile = outputfile;
	g1_state.ulstate = NO_COMMENT_STATE;
	
	char ch;
	while(g1_state.ulstate!= END_STATE)
	{
		ch = fgetc(g1_state.inputfile);
		EventPro1(ch);
	}
	return 0;
}

void EventPro1(char ch)
{
	switch(g1_state.ulstate)
	{
	case NO_COMMENT_STATE:
		EventProAtNo1(ch);
		break;
	case C_COMMENT_STATE:
		EventProAtC1(ch);
		break;
	case CPP_COMMENT_STATE:
		EventProAtCpp1(ch);
		break;
	case STR_STATE:
		EventProAtStr1(ch);
		break;
	case END_STATE:
		break;
	default:
		break;
	}
}
void EventProAtNo1(char ch)
{
	char nextch;
	switch(ch)
	{
		case '/':
		nextch = fgetc(g1_state.inputfile);
		if(nextch == '/') //C++
		{
			fputc(ch,g1_state.outputfile);
			fputc(nextch,g1_state.outputfile);
			g1_state.ulstate = CPP_COMMENT_STATE;
		}
		 else if(nextch == '*') // C
		{
			C_STATE1=1;
			fputc(ch,g1_state.outputfile);
			fputc('/',g1_state.outputfile);
			g1_state.ulstate = C_COMMENT_STATE;
		}

		break;
	case '"':
		fputc(ch,g1_state.outputfile);
		g1_state.ulstate =STR_STATE;
		break;
	case EOF:
		fputc(ch,g1_state.outputfile);
		g1_state.ulstate =END_STATE;
		break;
	default:
		{
			fputc(ch,g1_state.outputfile);
			g1_state.ulstate =NO_COMMENT_STATE;
			break;
		}
	}
}
void EventProAtC1(char ch)
{
	char nextch;
	switch(ch)
	{
	case '\n':
		{
			fputc('\n',g1_state.outputfile);
			fputc('/',g1_state.outputfile);
			fputc('/',g1_state.outputfile);
			g1_state.ulstate =C_COMMENT_STATE;
			break;
		}
	case '"':
		{
			fputc(ch,g1_state.outputfile);
			flag1=C_FLAG;
			g1_state.ulstate=STR_STATE;
			break;
		}
	case '*':
		nextch=fgetc(g1_state.inputfile);
		if(nextch=='/')
		{	
			if(C_STATE1==1)
			{
				fputc(' ',g1_state.outputfile);
				fputc(' ',g1_state.outputfile);
				fputc('\n',g1_state.outputfile);
				g1_state.ulstate =NO_COMMENT_STATE;
			}
			else
			{
				fputc(' ',g1_state.outputfile);
				fputc(' ',g1_state.outputfile);
				g1_state.ulstate =CPP_COMMENT_STATE;
			}
		}
		else
		{
			fputc(ch,g1_state.outputfile);
			fputc(nextch,g1_state.outputfile);
			g1_state.ulstate =C_COMMENT_STATE;
		}
		break;
	case '/':
		{
			nextch=fgetc(g1_state.inputfile);
			if(nextch=='/')
			{
				fputc(' ',g1_state.outputfile);
				fputc(' ',g1_state.outputfile);
				g1_state.ulstate =C_COMMENT_STATE;
			}
			else if(nextch=='*')
			{
				fputc(' ',g1_state.outputfile);
				fputc(' ',g1_state.outputfile);
				g1_state.ulstate =C_COMMENT_STATE;
			}
			else
			{
				fputc(ch,g1_state.outputfile);
				fputc(nextch,g1_state.outputfile);
				g1_state.ulstate =C_COMMENT_STATE;
			}
			break;
		}
		case EOF:
			fputc(ch,g1_state.outputfile);
			g1_state.ulstate =END_STATE;
			break;
	default:
			fputc(ch,g1_state.outputfile);
			g1_state.ulstate =C_COMMENT_STATE;
			break;
	}

}
void EventProAtCpp1(char ch)
{
	char nextch;
	switch(ch)
	{
	case '\n':
		fputc(ch,g1_state.outputfile);
		g1_state.ulstate = NO_COMMENT_STATE;
		break;
	case '/':
		{
			nextch=fgetc(g1_state.inputfile);
			if(nextch=='/')
			{
				
				g1_state.ulstate = CPP_COMMENT_STATE;
			}
			else if(nextch=='*')
			{
				fputc(' ',g1_state.outputfile);
				fputc(' ',g1_state.outputfile);
				g1_state.ulstate = C_COMMENT_STATE;
			}
			else
			{
				fputc(ch,g1_state.outputfile);
				fputc(nextch,g1_state.outputfile);
				g1_state.ulstate = CPP_COMMENT_STATE;
			}
		break;
		}
		
	case '*':
		{
			nextch=fgetc(g1_state.inputfile);
			if(nextch=='/')
			{
				fputc(' ',g1_state.outputfile);
				fputc(' ',g1_state.outputfile);
				g1_state.ulstate = CPP_COMMENT_STATE;
			}
			else
			{
				fputc(ch,g1_state.outputfile);
				fputc(nextch,g1_state.outputfile);
			}
			break;
		}
	case '"':
		{
			fputc(ch,g1_state.outputfile);
			flag1=CPP_FLAG;
			g1_state.ulstate = STR_STATE;
		
		break;
		}	
	default:
		fputc(ch,g1_state.outputfile);
		g1_state.ulstate = CPP_COMMENT_STATE;
		break;
	}
	
}
void EventProAtStr1(char ch)
{
	switch(ch)
	{
		char nextch;
	case '*':
		{
			nextch=getc(g1_state.inputfile);
			if(nextch=='/')
			{
				fputc(' ',g1_state.outputfile);
				fputc(' ',g1_state.outputfile);
				g1_state.ulstate=NO_COMMENT_STATE;
			}
			else
				{
					fputc(ch,g1_state.outputfile);
					fputc(nextch,g1_state.outputfile);
				}
			break;
		}
	case '\n':
		if(flag1==CPP_FLAG)
		{
			fputc('\n',g1_state.outputfile);
			g1_state.ulstate=NO_COMMENT_STATE;
		}
		else if(flag1==C_FLAG)
		{
			fputc('\n',g1_state.outputfile);
			fputc('/',g1_state.outputfile);
			fputc('/',g1_state.outputfile);
			g1_state.ulstate=C_COMMENT_STATE;
		}
		else
			fputc(ch,g1_state.outputfile);
		break;

	case '"':
		{
			fputc(ch,g1_state.outputfile);
			if(flag1==NO_FLAG)
				g1_state.ulstate = NO_COMMENT_STATE;
			if(flag1==CPP_FLAG)
				g1_state.ulstate =CPP_COMMENT_STATE;
			if(flag1==C_FLAG)
				g1_state.ulstate =C_COMMENT_STATE;
			break;
		}
	case EOF:
		fputc(ch,g1_state.outputfile);
		g1_state.ulstate =END_STATE;
		break;
	default:
		fputc(ch,g1_state.outputfile);
		break;
	}

}