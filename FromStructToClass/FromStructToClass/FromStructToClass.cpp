// FromStructToClass.cpp : Presents Class objects as a natural extension to struct objects.
//

#include "stdafx.h"
#include <iostream>
using namespace std; // Assigns commonly used functions, such as cout, to ostream.

//Example of definition, initialization and referencing to a struct variable
struct DateStruct {
	int year;
	int month;
	int day;
};

void print(DateStruct &date) {
	cout << date.year << "/" << date.month << "/" << date.day;
}

//A class can be interpreted as the grouping of the data and function above.
class DateClass {
public:
	int m_year;
	int m_month;
	int m_day;

	void print() {
		cout << m_year << "/" << m_month << "/" << m_day;
	}
};

//Both variables have similar initialization: DateClass today {2020,10,14}; or DateStruct today {2020,10,14};

//Example 2: IntPair Class

class IntPair {
public: //Member data and functions are private by default. Hence, here an explicit indication to public rights must be given.
	int n1;
	int n2;

	void set(int num1, int num2) {
		n1 = num1;
		n2 = num2;
	};

	void print() {
		cout << "Pair(" << n1 << ", " << n2 << ")\n"; //\n is equivalent to enter.
	};
};


//EXAMPLE 3: The example demonstrates that access controls work on a per-class basis using a copyFrom function.
class DateClass_v2 { 
	int m_year;	 //private by default, can only be accessed by class member functions
	int m_month; //private by default, can only be accessed by class member functions
	int m_day;   //private by default, can only be accessed by class member functions

public:
	void setDate(int Year, int Month, int Day) {
		m_year = Year;
		m_month = Month;
		m_day = Day;
	};

	void print() {
		cout << m_year << "/" << m_month << "/" << m_day;
	};

	//public CopyFrom function that creates an instane of DateClass_v2 based on the member data of another DateClass_v2 object:
	void CopyFrom(DateClass_v2 &Date){ //Note how the input is also a DateClass_v2 object. The & operator indicates a "reference" to the object, i.e. any changes to Date will affect it outside this function.
		m_year = Date.m_year; //This shows how access controls work on a per-class basis. CopyFromm is a member of DateClass_v2. Hence, it has access to the member data of any object of class DateClass_v2!
		m_month = Date.m_month;
		m_day = Date.m_day;
	}
};

//Example 3.1
class Point3d {
private:
	double m_x, m_y, m_z;

public:
	void setValues(double x, double y, double z) {
		m_x = x;
		m_y = y;
		m_z = z;
	};

	void print() {
		cout << "<" << m_x << "," << m_y << "," << m_z << ">";
	};

	bool isEqual(const Point3d &point) { //Note the const addition. Here it indicates the function should not modify point. In case it does, then a compiling error would occur. Like classes have access rights on data and functions, functions have functionality rights on data.
		return (m_x == point.m_x && m_y == point.m_y && m_z == point.m_z);
	};

};

int main()
{
	DateStruct today{ 2020, 10, 14 }; // use uniform initialization

	today.day = 16; // use member selection operator to select a member of the struct
	print(today);

	DateClass m_today{ 2020, 10, 14 };

	m_today.m_day = 16; // use member selection operator to select a member variable of the class
	m_today.print(); // use member selection operator to call a member function of the class

	//Example 2: Print IntPair
	IntPair p1; //Define variable
	p1.set(1, 1); //Use set method to initialize member data.
	IntPair p2{2,2}; // Initialization without set member function. 
	p1.print();
	p2.print();

	//EXAMPLE 3: Access controls work on a per-class basis.
	DateClass_v2 Date; //Creates memory space for DateClass_v2 type variable.
	Date.setDate(1993, 12, 01); // Initializes instance of DateClass_v2 type variable.
	DateClass_v2 Date_copy;
	Date_copy.CopyFrom(Date); // CopyFrom has access rights to member data of Date because it is a member function of that class.
	Date_copy.print();

	//Example 3.1
	Point3d point; // Note that const is only used in the definition of the function.
	point.setValues(1.0, 2.0, 3.0);
	point.print();

	Point3d point2; 
	point2.setValues(1.0, 2.0, 3.0);
	if (point.isEqual(point2)) 
		cout << "point1 and point2 are equal\n";
	else 
		cout << "point1 and point2 are not equal\n";


	Point3d point3;
	point3.setValues(3.0, 4.0, 5.0);
	if(point.isEqual(point3))
		cout << "point1 and point3 are equal\n";
	else
		cout << "point1 and point3 are not equal\n";

    return 0;
}

