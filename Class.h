//    Class.h - header file for Class class
//				Class represents a computer science course 
// 				and holds a list of students and tas
//		   By - Conor Jenkinson 
#ifndef __Class_h_
#define __Class_h_
#include <iostream>
using namespace std; 


class Class
{
public:
	Class();  // default constructor
	Class(string name);	//constructor with name
	Class(const Class &source); //copy constructor
	~Class();  // destructor
	void add_student(string stu); //adds student to student list
	void add_ta(string stu);    //adds ta to ta list
	bool operator==(Class new_class); //overload for == operator
	void expand_students(); //expands student array
	void expand_tas();      //expands ta array
	string get_name();		//returns the name of the class
	void print_class();		//prints the students in the class
private:
	string *students;  //dynamic array of students
	string *tas;	   //dynamic array of tas
	int student_cap;   
	int ta_cap;
	int student_count;
	int ta_count;  
	string name; 
};
#endif 