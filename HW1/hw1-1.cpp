#include <iostream>
#include <string>
using namespace std;
void main () 
{ 
	char age[10],name[10],city[10];
	cout<<"What's your age?"<<endl;
	cin.getline(age,10);
	cout<<"What's your name?"<<endl;
	cin.getline(name,10);
	cout<<"Where's your city?"<<endl;
	cin.getline(city,10);
	cout<<"The information of this user is:"<<endl;
	cout<<std::left<<"Age:"<<age<<'\n'<<"Name:"<<name<<'\n'<<"City:"<<city<<'\n';
}
