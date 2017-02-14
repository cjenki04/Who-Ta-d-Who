//			Class.cpp - implementation of Class class
//				   By - Conor Jenkinson

#include <iostream>
#include "Class.h"


using namespace std; 


Class::Class()
{
	student_cap = 5;
    ta_cap = 5;
    student_count = 0;
    ta_count = 0;
    students = new string[student_cap];
    tas = new string[ta_cap];  
    name = "name";

}
Class::Class(string class_name){
	student_cap = 5;
    ta_cap = 5;
    student_count = 0;
    ta_count = 0;
    students = new string[student_cap];
    tas = new string[ta_cap];  
    name = class_name;
}
Class::Class(const Class &source){
	name = source.name;
	student_cap = source.student_cap;
	ta_cap = source.ta_cap;
	student_count = source.student_count;
	ta_count = source.ta_count;
	students = new string[student_cap];
	tas = new string[ta_cap];
	for (int i = 0; i < ta_count; i++){
		tas[i] = source.tas[i];
	}
	for (int i = 0 ; i < student_count; i++){
		students[i] = source.students[i];
	}	
}
Class::~Class(){
	delete [] students;
	delete [] tas; 
	student_cap = 0;
	ta_cap = 0;
	ta_count = 0; 
	student_count = 0;
	name = ""; 
}
void Class::add_student(string stu){
	if (student_count == student_cap){
		expand_students();
	}
	students[student_count] = stu;
	student_count++;
}
void Class::add_ta(string stu){
	if (ta_count == ta_cap){
		expand_tas();
	}
	tas[ta_count] = stu;
	ta_count++;
}
string Class::get_name(){
	return name;
}

void Class::expand_students(){
	int new_cap = student_cap *2;
    string *new_array = new string[new_cap];
	for (int i=0; i < student_count; i++)
		new_array[i] = students[i];
	delete[] students;
	students = new_array;
	student_cap *=2;
}
void Class::expand_tas(){
int new_cap = ta_cap *2;
    string *new_array = new string[new_cap];
	for (int i=0; i < ta_count; i++)
		new_array[i] = tas[i];
	delete[] tas;
	tas = new_array;
	ta_cap *=2;
}
bool Class::operator==(Class new_class){
	if (name == new_class.name){
		return true;
	}
	return false; 
}
void Class::print_class(){
	for (int i = 0 ; i < student_count; i++){
		cout << students[i] << endl;
	}
	
}









