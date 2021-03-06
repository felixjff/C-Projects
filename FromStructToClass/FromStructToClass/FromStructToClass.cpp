// FromStructToClass.cpp : Presents Class objects as a natural extension to struct objects.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>
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
	}

	void print() {
		cout << "Pair(" << n1 << ", " << n2 << ")\n"; //\n is equivalent to enter.
	}
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
	}

	void print() {
		cout << m_year << "/" << m_month << "/" << m_day;
	}

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
	}

	void print() {
		cout << "<" << m_x << "," << m_y << "," << m_z << ">";
	}

	bool isEqual(const Point3d &point) { //Note the const addition. Here it indicates the function should not modify point. In case it does, then a compiling error would occur. Like classes have access rights on data and functions, functions have functionality rights on data.
		return (m_x == point.m_x && m_y == point.m_y && m_z == point.m_z);
	}

};


//Example 4: Coding a stack class from scratch 
class Stack {
private:
	static const int s_maxStacklength{ 10 };
	int tasks[s_maxStacklength];  //array of size 10 to hold tasks
	int length;

public:
	void reset() { //This plays the role of constructor and defines an initial instance for an Stack object
		length = 0;
		for (int i = 0; i < sizeof(tasks); i++)
			tasks[i] = 0;
	}

	bool push(int value) {
		if (length == s_maxStacklength)
			return false; //Stack is already full and 

		tasks[length] = value; //stack the input value in current position of the stack.
		length++; //change pointer to he next available position.
		return true; //finalize successful stacking.
	}

	int pop() {
		assert(length > 0 && "Can not pop empty stack");

		int val = tasks[length - 1]; //length points to a free entry. Hence, last non-free is length - 1.
		length--; //move the pointer to the next "free" entry. Note, there is not need to set the "free" entry to 0.
		return val;
	}

	void print() {
		//Method to print in the console with for loop:
		cout << "( ";
		for (int i = 0; i < length; i++)
			cout << tasks[i] << " ";
		cout << ")\n";
	}
};


//Example 5: CLass Object Initialization (Constructors and Desctructors)
class Foo{
public: //Note the access rights are public. Hence, data can be accessed by an external client.
	int m_x;
	int m_y;
};

class Fraction {
private:
	int n_numerator;
	int n_denominator;

public:
	//Object can be automatically initialized when created if a constructor is defined. Constructors have specific rules for how they must be named:
	//1. Constructors must have the same name as the class (with the same capitalization).
	//2. Constructors have no return type (not even void).

	Fraction(){ //Default constructor = constructor that takes no parameters. (with value assignments)
		n_numerator = 0; // This is an assignments, not initialization
		n_denominator = 1; // This is an assignments, not initialization
	};

	//Alternative: constructor with parameterization (and value assignments)
	Fraction(int numerator, int denominator) {
		n_numerator = numerator; // This is an assignments, not initialization
		n_denominator = denominator; // This is an assignments, not initialization
	};

	//Alternative: value assignment can be problematic for special variables such as const and reference variables as they must be initialized at the moment they are defined. Hence, use member initializer lists:
	Fraction(int value1, double value2) : n_numerator(value1), n_denominator(value2) {
		//No need for assignment here.
	}//// directly initialize the member variables

	//If no constructor is provided, then C++ would automatically define and call the default constructor Fraction(){ }. However, it is best practice to provide at least one constructor, even if it is an empty default constructor.

	int getNumerator() { return n_numerator; };
	int getDenominator() { return n_denominator; };
	double getValue() { return static_cast<double>(n_numerator) / n_denominator; };

	//Desctructor definition must follow three rules:
	//1. The destructor must have the same name as the class, preceded by a tilde (~).
	//2. The destructor can not take arguments.
	//3. The destructor has no return type.
	~Fraction() {
		//If no further specification provided here, then it is a default destructor.
	}
	
};


	//Example 6: Parent and Derived Classes (Inheritance)



int main()
{
	DateStruct today{ 2020, 10, 14 }; // use uniform initialization

	//Side note on arrays: an array of structs can be defined as follows: DateStruct week[7]; Then each array entry can store a day, month and year value.

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


	//Example 4: Stack class implementation 
	Stack stack;
	stack.reset();

	stack.print(); //Should print "( )"

	stack.push(5);
	stack.push(3);
	stack.push(8);
	stack.print(); //Should print "( 5 3 8 )"

	stack.pop();
	stack.print(); //Should print "( 5 3 )"

	stack.pop();
	stack.pop();

	stack.print(); //Should print "( )"

	//Example 5: CLass Object Initialization

	Foo foo1 = { 4, 5 }; //Member data of foo1 is initialized using an "initialization list".
	Foo foo2{ 5,6 }; // This type of initialization is called "uniform initialization without constructor" (C++11)
		//Note, both can be initialized from int Main(){} because member data is public!
		//If member data is not public, then a "constructor" is used for initialization. 

	Fraction frac; // Since no arguments, calls Fraction() default constructor and is assigned default initializaiton values.
	cout << frac.getNumerator() << "/" << frac.getDenominator() << '\n';

	Fraction fiveThirds{ 5, 3 }; //Uniform initialization with default constructor .
	Fraction fiveThirds(5, 3); //Direct initialization with default construction. Given the default parameterized constructor, there is no difference between {} and ().

	Fraction frac1(1, 2.2);


	//Example 6: Parent and Derived Classes (Inheritance)

    return 0;
}// frac1 is destroyed here, so the ~Fraction() destructor function is called here

