//			Student.cpp - implementation of Student class
//					 By - Conor Jenkinson

#include "Student.h"
#include <iostream>
using namespace std; 

Student::Student(){
	name = "name";
	taken_capacity = 5;
	tad_capacity = 5;
	classes_taken = new string[taken_capacity];
	classes_tad = new string[tad_capacity];
	num_taken_classes = 0;
	num_tad_classes = 0;  
} 
Student::Student(string student_name){
	name = student_name;
	taken_capacity = 5; 
	tad_capacity = 5;
	classes_taken = new string[taken_capacity];
	classes_tad = new string[tad_capacity];
	num_taken_classes = 0;
	num_tad_classes = 0;  
}
Student::Student(const Student &source){
	name = source.name;
	taken_capacity = source.taken_capacity;
	tad_capacity = source.tad_capacity;
	num_taken_classes = source.num_taken_classes;
	num_tad_classes = source.num_tad_classes;
	classes_taken = new string[taken_capacity];
	classes_tad = new string[tad_capacity];
	for (int i = 0; i < num_tad_classes; i++){
		classes_tad[i] = source.classes_tad[i];
	}
	for (int i = 0 ; i < num_taken_classes; i++){
		classes_taken[i] = source.classes_taken[i];
	}
}
Student &Student::operator=(const Student &source){
	if (this != &source){
		delete [] classes_taken;
		delete [] classes_tad;
	name = source.name;
	taken_capacity = source.taken_capacity;
	tad_capacity = source.tad_capacity;
	num_taken_classes = source.num_taken_classes;
	num_tad_classes = source.num_tad_classes;
	classes_taken = new string[taken_capacity];
	classes_tad = new string[tad_capacity];
	for (int i = 0; i < num_tad_classes; i++){
		classes_tad[i] = source.classes_tad[i];
	}
	for (int i = 0 ; i < num_taken_classes; i++){
		classes_taken[i] = source.classes_taken[i];
	}
	}
	return *this;
}

Student::~Student(){
	delete[] classes_taken;
	delete[] classes_tad;
	name = "";
	num_taken_classes = 0;
	num_tad_classes = 0;  
	taken_capacity = 0;
	tad_capacity = 0;
}
void Student::add_taken_class(string new_class){
	if (num_taken_classes == taken_capacity){
		expand_taken();
	}
	classes_taken[num_taken_classes] = new_class;
	num_taken_classes++;
}
void Student::add_tad_class(string new_class){
	if (num_tad_classes == tad_capacity){
		expand_tad();
	}
	classes_tad[num_tad_classes] = new_class;
	num_tad_classes++;
}
bool Student::did_take(string new_class){
	for (int i = 0 ; i < taken_capacity; i++){
		if (classes_taken[i] == new_class){
			return true;
		}
	}
	return false;
}
bool Student::did_ta(string new_class){
	for (int i = 0 ; i < tad_capacity; i++){
		if (classes_tad[i] == new_class){
			return true;
		}
	}
	return false;
}
bool Student::did_ta_for(Student stud){
	for (int i = 0 ; i < num_tad_classes ; i++){
		if (stud.did_take(classes_tad[i])){
			return true;
		}
	}
	return false; 
}
string Student::class_tad_for(Student stud){
	string tad_class = "none";
	for (int i = 0 ; i < num_tad_classes ; i++){
		if (stud.did_take(classes_tad[i])){
			tad_class = classes_tad[i];
		}
	}
	return tad_class;
}

void Student::expand_taken(){
	int new_cap = taken_capacity *2;
    string *new_array = new string[new_cap];
	for (int i=0; i < num_taken_classes; i++)
		new_array[i] = classes_taken[i];
	delete[] classes_taken;
	classes_taken = new_array;
	taken_capacity *=2;

}
void Student::expand_tad(){
	int new_cap = tad_capacity *2 ;
	string *new_array = new string[new_cap];
	for (int i=0; i < num_tad_classes; i++)
		new_array[i] = classes_tad[i];
	delete[] classes_tad;
	classes_tad = new_array;
	tad_capacity *=2;
}
string Student::get_name(){
	return name;
}
void Student::print_tad(){
	for (int i = 0 ; i < num_tad_classes; i++){
		cout << classes_tad[i] << endl;
	}
}



