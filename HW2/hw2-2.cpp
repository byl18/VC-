#include<iostream>
#include<string>
#include"math.h"
using namespace std;
class Complex
{
private:
	double r,i;
public:
	Complex(double a,double b)
	{
	this->r=a;
	this->i=b;
	}
	Complex operator + (const Complex&m)const{return Complex(r+m.r,i+m.i);};
	Complex operator - (const Complex&m)const{return Complex(r-m.r,i-m.i);};
	Complex operator * (const Complex&m)const{return Complex(r*m.r+i*m.i,r*m.i+i*m.r);};
	double get_r(){return r;}
	double get_i(){return i;}
	void display(){cout<<"("<<r<<","<<i<<")"<<endl;}
};






class Calculator{  
private:  
    double num;  
public:  
    Calculator(double a):num(a){};  
    double calculate(Calculator b,string s)
	{
	 if(s=="+")
		  return num+b.num;
	     if(s=="-")
		  cout<<num<<s<<b.num<<"="<<num-b.num;
	     if(s=="*")
	      return num*b.num;
	     if(s=="/")
		  return num/b.num;
		  if(s=="^")
		 return pow(num,b.num);
		  else if(s=="log")
			return  log(num)/log(b.num);
	}
	double display(){return num;}
};     

int main()
{
	
	string str;
	cout<<"Input 1 for the calculation of real number."<<"\n"<<"Input 2 for the calculation of complex number."<<endl;
	int Case;
	cin>>Case;
	switch(Case){
	case 1:
		cout<<"Let's strat to calculate real number!(For logrithm calculation logm(n)is shown as m log n.)"<<endl;
		double num1,num2;
		while(cin>>num1)
		{
		cin>>str>>num2;
		Calculator a(num1);
		Calculator b(num2);
		cout<<a.display()<<str<<b.display()<<"="<<a.calculate(b,str)<<endl;
	    }
		break;
	case 2:
		cout<<"Let's strat to calculate complex number!(Complex a+bi is shown as (a,b).)"<<endl;
		
		double n1,n2,n3,n4;
		while(cin>>n1)
		{
		string s4;
		cin>>n2>>s4>>n3>>n4;
		Complex c1(n1,n2);
		Complex c2(n3,n4);
		if(s4=="+"){
		cout<<"("<<c1.get_r()<<","<<c1.get_i()<<")"<<s4<<"("<<c2.get_r()<<","<<c2.get_i()<<")"<<"=";
		(c1+c2).display();}
		if(s4=="-"){
		cout<<"("<<c1.get_r()<<","<<c1.get_i()<<")"<<s4<<"("<<c2.get_r()<<","<<c2.get_i()<<")"<<"=";
		(c1-c2).display();}
        if(s4=="*"){
		cout<<"("<<c1.get_r()<<","<<c1.get_i()<<")"<<s4<<"("<<c2.get_r()<<","<<c2.get_i()<<")"<<"=";
		(c1*c2).display();}
	    }
		break;
	default:
		cout<<"error!"<<endl;
		break;
}

	return 0;
}



