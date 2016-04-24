#include "BigData.h"

BigData::BigData(INT64 value)
	:m_value(value)
	,m_strData("")
{
	INT64toStr();
}

BigData::BigData(const char* strData)
	:m_value(0)
{
	assert(strData);
	char *str=(char*)strData;
	char symbol;
	if((str[0]=='+')||(str[0]>='0'&&str[0]<='9'))
	{
		symbol='+';
		if(str[0]=='+')
		{
			str++;
		}
	}
	else if(str[0]=='-')
	{
		symbol='-';
		str++;
	}
	else
	{
		return;
	}
	while(*str=='0')
	{
		str++;
	}
	if(*str!='\0')
	{
			m_strData.append(1,symbol);
	}
	while(*str!='\0')
	{
		if(*str>='0'&&*str<='9')
		{
			m_strData.append(1,*str);
			m_value=m_value*10+*str-'0';
			str++;
		}
		else 
			break;
	}
	if(strData[0]=='-')
	{
		m_value*=-1;
	}
}

void BigData::INT64toStr()
{
	char symbol='+';
	if(m_value<0)
	{
		symbol='-';
	}
	INT64 value=m_value;
	int iCount=0;
	while(value)
	{
		value/=10;
		iCount++;
	}
	value=m_value;
	m_strData.resize(iCount+1);
	m_strData[0]=symbol;
	int i=1;
	while(iCount)
	{
		m_strData[i++]=value/((INT64)pow(10.0,iCount-1))+'0';
		value=value%((INT64)pow(10.0,iCount-1));
		iCount--;
	}

}

bool BigData::INT64isOver()const
{
	BigData MaxData(INT64_MAX);
	BigData MinData(INT64_MIN);
	if(m_strData[0]=='+'&&(m_strData.size()>MaxData.m_strData.size()||(m_strData.size()==MaxData.m_strData.size()&&m_strData>MaxData.m_strData)))
	{
		return true;
	}
	if(m_strData[0]=='-'&&(m_strData.size()>MinData.m_strData.size()||(m_strData.size()==MinData.m_strData.size()&&m_strData>MaxData.m_strData)))
	{
		return true;
	}

	return false;
}

 BigData BigData::operator+(const BigData& b)
{
	if(this->INT64isOver()==0&&(b.INT64isOver())==0)
	{
		if(m_strData[0]!=b.m_strData[0])
		{
			return BigData(m_value+b.m_value);
		}
		else if(m_strData[0]=='+'&&INT64_MAX-m_value>=b.m_value)
		{
			return BigData(m_value+b.m_value);
		}
		else if(m_strData[0]=='-'&&INT64_MIN-m_value<=b.m_value)
		{
			return BigData(m_value+b.m_value);
		}
	}
	return BigData(Add(m_strData,b.m_strData).c_str());
} 

 string BigData::Add(string left,string right)
 {
	 int Left=left.size();
	 int Right=right.size();
	 if(Left<Right)
	 {
		 swap(left,right);
		 swap(Left,Right);
	 }
	 string s;
	 s.resize(Left+1);
	 if(left[0]==right[0])
	 {
		 char step=0;
		 s[0]=left[0];
		 for(int idx=1;idx<Left;idx++)
		 {
			 char str;
			 if(Right-idx<1)
			 {
				 str=(left[Left-idx]-'0')+step;
			 }
			 else
			 {
				 str=(left[Left-idx]-'0')+(right[Right-idx]-'0')+step;
			 }
			 s[Left+1-idx]=str%10+'0';
			 step=str/10;
		 }
		 s[1]=step+'0';
	 }
	 else
	 {
		 if(left[0]=='-')
		 {
			 left[0]='+';
			s= Sub(right,left);
		 }
		 else
		 {
			 right[0]='+';
			 s= Sub(left,right);
		 }
	 }
	 return s;
 }


 ostream& operator<<(ostream& os,const BigData& b)
 {
	 if(b.INT64isOver())
		 os<<b.m_strData.c_str();
	 else
	 {
		 os<<b.m_value;
	 }
	 return os;
 }

BigData BigData::operator-(const BigData& bigData)
	{
		if(this->INT64isOver()==0&&bigData.INT64isOver()==0)
		{
			if(m_strData[0]==bigData.m_strData[0])
			{
				return BigData(m_value-bigData.m_value);
			}
			else if(m_strData[0]=='+'&&(m_value-bigData.m_value)<=INT64_MAX)
			{
				return BigData(m_value-bigData.m_value);
			}
			else if(m_strData[0]=='-'&&(m_value-bigData.m_value)>=INT64_MIN)
			{
				return BigData(m_value-bigData.m_value);
			}
		}
		return BigData(Sub(m_strData,bigData.m_strData).c_str());
	}

string BigData::Sub(string left,string right)
{
	int Left=left.size();
	int Right=right.size();
	string str;
	if(left[0]!=right[0])
	{
		if(left[0]=='+')
		{
			right[0]='+';
			str=Add(left,right);
		}
		else
		{
			left[0]='+';
			right[0]='+';
			str=Add(left,right);
			str[0]='-';
		}
	}
	else 
	{
		char symbol='+';
		if((left[0]=='+'&&Left<Right&&left<right)||(left[0]=='-'&&Left>Right&&left>right))
		{
			symbol='-';
			swap(Left,Right);
			swap(left,right);
		}
		else if(Left<Right||(Left==Right&&left.c_str()+1<right.c_str()+1))
		{
			swap(Left,Right);
			swap(left,right);
		}
		str.resize(Left);
		char step=0;
		for(int idx=1;idx<Left;idx++)
		{
			char ch;
			left[Left-idx]-=step;
			step=0;
			if(Right-idx<1)
			{
				ch=left[Left-idx]-'0';
			}
			else
			{
				ch=left[Left-idx]-'0'-(right[Right-idx]-'0');
			}

			if(ch<0)
			{
				ch+=10;
				step=1;
			}
			str[Left-idx]=ch+'0';
		}	
		str[0]=symbol;
	}
	return str;
}

BigData BigData::operator*(const BigData& bigData)
{
	if(this->INT64isOver()==0&&bigData.INT64isOver()==0)
	{
		if(m_strData[0]==bigData.m_strData[0])
		{
			if((m_strData[0]=='+'&&INT64_MAX/m_value>=bigData.m_value)||(m_strData[0]=='-'&&INT64_MAX/m_value<=bigData.m_value))
			{
				return BigData(m_value*bigData.m_value);
			}		
		}
		else
		{
			if((m_strData[0]=='+'&&INT64_MIN/m_value<=bigData.m_value)||(m_strData[0]=='-'&&INT64_MIN/m_value>=bigData.m_value))
				return BigData(m_value*bigData.m_value);
		}
	}
	return BigData(Mul(m_strData,bigData.m_strData).c_str());
}

string BigData::Mul(string left,string right)
{
	int Left=left.size();
	int Right=right.size();
	char symbol='+';
	if(Left>Right)
	{
		swap(Left,Right);
		swap(left,right);
	}
	if(left[0]!=right[0])
	{
		symbol='-';
	}
	string s;
	s.resize(Left+Right-1);
	char step=0;
	for(int idx=1,cross=0;idx<=Left-1;idx++)
	{
		step=0;
		char ch;
		if(left[Left-idx]==0)
		{
			cross++;
			continue;
		}
		for(int jdx=1;jdx<=Right-1;jdx++)
		{
			ch=(left[Left-idx]-'0')*(right[Right-jdx]-'0')+step;
			step=ch/10;
			if(s[Left+Right-1-jdx-cross]+ch%10>=10)
			{
				s[Left+Right-1-jdx-cross]+=ch%10-10;
				step++;
			}
			else
			{
				s[Left+Right-1-jdx-cross]+=ch%10;
			}
		}
		s[Left-cross-1]=step;
		cross++;
	}
	for(int i=1;i<Left+Right-1;i++)
	{
		s[i]+='0';
	}
	s[0]=symbol;
	return s;
}

BigData BigData::operator/(const BigData& bigData)
{
	if(this->INT64isOver()==0&&bigData.INT64isOver()==0)
	{
		return BigData(m_value/bigData.m_value);
	}
	return BigData(Div(m_strData,bigData.m_strData).c_str());
}

string BigData::Div(string left,string right)
{
	int Left=left.size();
	int Right=right.size();
	char symbol='+';
	if(Left<Right||(Left==Right&&strcmp((left.c_str()+1),(right.c_str()+1))==-1))
	{
		return "0";
	}
	if(left[0]!=right[0])
	{
		symbol='-';
	}
	string str;
	str.resize(Left);
	left[0]='+';
	right[0]='+';
	int iEnd=Right-1;
	int iBegin=1;
	while(iEnd<Left)
	{
		if(IsLeftStrBig((char*)left.c_str(),(char*)right.c_str(),iBegin,iEnd))
		{
			str[iEnd]=SubLoop((char*)left.c_str(),(char*)right.c_str(),iBegin,iEnd);
		}
		else
		{
			iEnd++;
			continue;
		}
		while(left[iBegin]=='0')
		{
			if(iBegin==Left-1)
			{
				iBegin++;
				break;
			}
			iBegin++;
		}
		iEnd=iBegin+Right-2;  //保持让它们相差Right-1位
	}

	str[0]=symbol;
	for(int i=1;i<Left;i++)
	{
		str[i]+='0';
	}
	return str;
}

bool BigData::IsLeftStrBig(char *pleft,char * pright,size_t Lsize,size_t Rsize)
{
	while(pleft[Lsize]=='0')
	{
		Lsize++;
	}
	if(Rsize-Lsize+1==strlen(pright)-1&&strncmp(pleft+Lsize,pright+1,Rsize-Lsize+1)>=0)
	{
		return 1;
	}
	else if(Rsize-Lsize==strlen(pright)-1)
	{
		return 1;
	}
	return 0;
}

char BigData::SubLoop(char *pleft,char * pright,size_t Lsize,size_t Rsize)
{
	int iCount=0;
	int pright_size=strlen(pright)-1;
	do
	{
		int step=0;
		int RSIZE=Rsize;
		pright_size=strlen(pright)-1;
		while(RSIZE>=Lsize)
		{
			if(pright_size==0)
			{
				pleft[Lsize]=pleft[Lsize]-'0'-step+'0';
				break;
			}
			if(pleft[RSIZE]<pright[pright_size]||(step==1&&pleft[RSIZE]==pright[pright_size]))
			{
				pleft[RSIZE]=10+(pleft[RSIZE]-'0')-(pright[pright_size--]-'0')-step+'0';
				RSIZE--;
				step=1;
			}
			else
			{
				pleft[RSIZE]=(pleft[RSIZE]-'0')-(pright[pright_size--]-'0')-step+'0';
				RSIZE--;
				step=0;
			}
		}
		iCount++;
	}
	while(IsLeftStrBig(pleft,pright,Lsize,Rsize));
	return iCount;
}
