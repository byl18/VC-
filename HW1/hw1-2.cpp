#include<iostream>
#include<string>
#include<sstream>
using namespace std;
void main()
{
	cout<<"Input two numbers"<<endl;
	float a=0.0;
	float b=0.0;
	string str;
	cout<<"The first number is:";
	getline(cin,str);
	stringstream(str)>>a;
	cout<<"The second number is:";
	getline(cin,str);
	stringstream(str)>>b;
	cout<<"a+b="<<a+b<<endl<<"a-b="<<a-b<<endl<<"a*b="<<a*b<<endl<<"a/b="<<a/b<<endl;
}