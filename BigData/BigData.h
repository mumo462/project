#ifndef BIG_DATA
#define BIG_DATA
#include <iostream>
using namespace std;
#include <string>
#include <assert.h>
typedef long long INT64;
#define INT64_MAX 0x7fffffffffffffff 
#define INT64_MIN 0x8000000000000000 
class BigData
{
public:
	BigData(INT64 value=0);
	BigData(const char* strData);
	BigData operator+(const BigData& bigData);
	BigData operator-(const BigData& bigData);
	BigData operator*(const BigData& bigData);
	BigData operator/(const BigData& bigData);
	friend ostream& operator<<(ostream& os,const BigData& b);
private:
	bool INT64isOver()const;
	void INT64toStr();
	string Add(string left,string right);
	string Sub(string left,string right);
	string Mul(string left,string right);
	string Div(string left,string right);
	bool IsLeftStrBig(char *pleft,char * pright,size_t Lsize,size_t Rsize);
	char SubLoop(char *pleft,char * pright,size_t Lsize,size_t Rsize);
	INT64 m_value;
	std::string m_strData;
};


#endif