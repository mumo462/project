#include <iostream>
#include "BigData.h"
using namespace std;
void Test1()
{
	BigData b1("199999999999999998");
	BigData b2("-0099999");
	BigData b3("ad99999");
	BigData b4("99999adas");
	BigData b5("+");
}

void Test2()
{
	BigData b1("+999999999999999994524525525242342");
	BigData b2("+123424664443423432423");
	BigData b3("+999999999999999994524525525242342");
	BigData b4("-123424664443423432423");
	cout<<(b1+b2)<<endl;
	cout<<(b1+b3)<<endl;
	cout<<(b1+b4)<<endl;
	cout<<(b4+b1)<<endl;
}
void Test3()
{
	BigData b1("+999999999999999994524525525242342");
	BigData b2("+123424664443423432423");
	BigData b3("+999999999999999994524525525242342");
	BigData b4("-123424664443423432423");
	cout<<(b1-b2)<<endl;
	cout<<(b1-b3)<<endl;
	cout<<(b2-b4)<<endl;
	cout<<(b4-b1)<<endl;
}
//void Test4()
//{
//	BigData b1("-11230000123000");
//	BigData b2("+234234523525234242");
//	BigData b3("+999999999999999994524525525242342");
//	BigData b4("-123424664443423432423");
//	cout<<(b1*b2)<<endl;
//	cout<<(b1*b3)<<endl;
//	cout<<(b2*b4)<<endl;
//	cout<<(b4*b1)<<endl;
//	
//}
void Test5()
{
	BigData b1("888888888888888888888888888888888888");
	BigData b2("232423");
	cout<<(b1/b2)<<endl;
}
int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	Test5();
	return 0;
}