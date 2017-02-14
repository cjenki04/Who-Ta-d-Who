//			Student.h - header file for Student class
//						Student class holds a list of all the classes
//						the student has taken and a list of all the classes
//						the student has tad
//				   By - Conor Jenkinson

#ifndef __Student_h__
#define __Student_h__
#include <iostream>
using namespace std;


class Student
{ 
public: 
	Student(); //default constuctor
	Student(string student_name);  //constuctor with name
	Student(const Student &source); //copy constructor
	~Student(); 	//destructor
	void add_taken_class(string new_class); //adds class to taken classes
	void add_tad_class(string new_class);   //adds class to tad classes
	bool did_take(string new_class);  //returns true if student took class
	bool did_ta(string new_class);    //returns ture if student tad class
	string get_name();  //returns name of student
	void print_tad();	//prints classes the student has tad
	bool did_ta_for(Student stud); //returns true if student tad for student
	string class_tad_for(Student stud); //returns class student tad for 
	Student &operator=(const Student &source); //assignment overload

private:
	string *classes_taken;  //dynamic array of taken classes
	string *classes_tad;    //dynamic array of tad classes
	string name; 
	int num_taken_classes;
	int num_tad_classes;  
	void expand_taken();
	void expand_tad();
	int taken_capacity;
	int tad_capacity;
}; 

#endif 