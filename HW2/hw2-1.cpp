#include<iostream>
using namespace std;
class Point
{
private:
	double x,y,z;
public:
    Point(double a,double b,double c);
	void dispaly_coordinate()
	{
	cout<<"The coordinate of this point is ("<<x<<","<<y<<","<<z<<")"<<endl;
	}
	void display_distance(Point a)
	{
	double D=sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y)+(a.z-z)*(a.z-z));
	cout<<"The distance of these two points is "<<D<<endl;
	}
	void display_distance2()
	{
	double D=sqrt(x*x+y*y+z*z);
	cout<<"The distance of this point and (0,0) is "<<D<<endl;
	}
};
Point::Point(double a,double b,double c)
{
	x=a;
	y=b;
	z=c;
}


int main()
{
	
	double ax,ay,az,bx,by,bz;
	cout<<"Please input the coordinate of a point "<<endl;
	cin>>ax>>ay>>az;
	Point A(ax,ay,az);
	A.dispaly_coordinate();
	A.display_distance2();
	cout<<"Please input the coordinate of another point "<<endl;
	cin>>bx>>by>>bz;
	Point B(bx,by,bz);
	A.display_distance(B);
}


