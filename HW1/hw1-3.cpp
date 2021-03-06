#include<iostream>
using namespace std;
void main()
{
char str[100];
char *p;
cout<<"input a chars: "<<endl;
cin.getline(str,100);
p=str;
for(int i=0;i<100;i++)
{
	if(str[i]>='0'&&str[i]<='9')
		cout<<str[i];
}
} 


