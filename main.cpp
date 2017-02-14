//	main.cpp - reads in data from command line and takes commands
//			   from cin until it reaches the end of the file
//  Commands : ls - lists students in files
//			   lc - lists classes in files
//			   roster <Class> - lists the roster of a given class
//			   taed <Student> - lists the class Student has taed
//			   paths <Student1> <Student2> - lists all possible paths 
//			   between Students 1 and 2
//			   shortestpath <Student1> <Student2> - prints the shortest 
//			   path between students 1 and 2
//        By - Conor Jenkinson
#include <iostream>
#include "Student.h"
#include "Class.h"
#include <fstream>
#include <vector>
#include <string>
#include "Graph.h"
#include <queue>
using namespace std;
void list_students(vector<Student> students);
void list_courses(vector<Class> classes);
void list_courses_tad(Student student);
void list_class_roster(Class new_class);
void findPaths(string names, Graph graph, vector<Student> students);
void findShortestPath(string names, Graph graph, 
	vector<Student> students);
bool check_name(string name, vector<Student> students);
bool check_names(string names, vector<Student> students);
bool check_class(string name, vector<Class> classes);
void get_data(int argc, char *argv[],vector<Student> &students,
			  vector<Class> &classes);
void get_student(vector<Student> &students, string name,
 string new_class,
	int argn);
void get_class(vector<Class> &classes, 
	string name, string new_class, int argn);
bool is_student(string name, vector<Student> students);
bool is_class(string name, vector<Class> classes);
int class_index(string name, vector<Class> classes);
int student_index(string name, vector<Student> students);
void read_input(Graph graph, vector<Class> classes,
 vector<Student> students );
void process_input(string command, Graph graph,
 vector<Class> classes, vector<Student> students );
void make_graph(Graph &graph, vector<Student> students);
void DFS(int start, int finish, Graph graph, 
	vector<Student> students, int path[],int &path_count);
void sameDFS(int start,int finish,Graph graph, 
	vector<Student> students, int path[], 
	int path_count, int iter);
void shortestDFS(int start, int finish, Graph graph, 
	vector<Student> students,int path[], int path_count,
	  vector<int> &pathways, vector<int> &path_lengths);
void printShortestPath(vector<int> pathways, 
	vector<int> path_lengths, vector<Student> students);
int find_min(vector <int> path_lengths);
void sameshortestDFS(int start, int finish, Graph graph, 
	vector<Student> students,int path[], int path_count,  
	vector<int> &pathways, vector<int> &path_lengths, int iter );

int main(int argc, char *argv[]){
	
	vector<Student> students;
	vector<Class> classes;
	get_data(argc,argv, students, classes);
	int size = students.size();
	Graph graph(size);
	make_graph(graph, students);
	read_input(graph, classes, students);
	return 0 ;
}
//reads data from command line
void get_data(int argc, char *argv[],vector<Student> &students,
			  vector<Class> &classes)
{
	ifstream finput;
	string fname;
	string name; 
	string class_name;
	string class_date;
	for (int i = 1 ; i < argc ; i++){
		fname = argv[i];
		finput.open(fname.c_str());
		if (finput.is_open()){
			while(finput.good()){
				string new_class;
				getline(finput, name, ':'); //gets the student name
				if (!name.empty()){
					getline(finput,class_name, ':');//class name
					getline(finput,class_date);//class date
					new_class += class_name; // concatonates
					new_class += class_date;
					get_student(students, name, new_class, i);
					get_class(classes, name, new_class,i);	
				}			
			}
		}
		finput.close();
	}
}
//adds class to classes vector if class is not already there
void get_class(vector<Class> &classes,  
	string name, string new_class, int argn){

	if (!is_class(new_class, classes)){ //checks class
		classes.push_back(Class(new_class));
	}
	int cindex = class_index(new_class, classes);
	if (argn ==1){
		classes[cindex].add_student(name); //student data comes first
	}
	else {
		classes[cindex].add_ta(name); //ta data is argn = 2;
	}

}
//adds student to students vector if student is not already there
void get_student(vector<Student> &students, string name,
 string new_class,
	int argn){
	if (!is_student(name, students)){ //checks student
		students.push_back(Student(name));
		}
	int sindex = student_index(name, students);			
	if (argn ==1){
		students[sindex].add_taken_class(new_class);//student data
	}
	else{
		students[sindex].add_tad_class(new_class);// ta data
	}
}
//checks to see if student is already in students vector
bool is_student(string name, vector<Student> students){
	int size = students.size();
	for (int i = 0 ; i < size ; i++){
		if (name == students[i].get_name()){
			return true;
		}
	}
	return false;
}
//checks to see if class is already in class vector
bool is_class(string name, vector<Class> classes){
	int size = classes.size();
	for (int i = 0 ; i < size ; i++){
		if (name == classes[i].get_name()){
			return true;
		}
	}
	return false;
}
//returns the index of the class in classes vector
//returns sentinel -1 if class is not in vector
int class_index(string name, vector<Class> classes){
	int size = classes.size();
	int index = -1;
	for (int i = 0 ; i < size; i++){
		if (name == classes[i].get_name()){
			index = i;
		}
	}
	return index; 
}
//returns the index of the student in student vector
//returns sentinel -1 if student is not in vector
int student_index(string name, vector<Student> students){
	int size = students.size();
	int index = -1;
	for (int i = 0 ; i < size ; i++){
		if (name == students[i].get_name()){
			index = i;
		}
	}
	return index; 
}
//prints the courses one line at a time
void list_courses(vector<Class> classes){
	int size = classes.size();
	for (int i = 0 ; i < size ; i++){
		cout << classes[i].get_name() << endl;
	}

}
//prints the students one line at a time
void list_students(vector<Student> students){
	int size = students.size();
	for (int i = 0 ; i < size ; i++){
		cout << students[i].get_name() << endl;
	}
}
//prints the courses a student taed
void list_courses_tad(Student student){
	student.print_tad();
}
//prints the student in a particular class
void list_class_roster(Class new_class){
	new_class.print_class();
}
//reads commands from cin until end of file
void read_input(Graph graph, vector<Class> classes, vector<Student> students){
	string command;
	while (cin.good()){
		getline(cin, command);
		process_input(command, graph, classes, students);
	}
}
//proccess the command by calling approprate method
void process_input(string command, Graph graph, vector<Class> classes, 
	vector<Student> students){
	if (command == "ls"){
		list_students(students);
	}
	else if (command == "lc"){
		list_courses(classes);
	}//name will always be the rest of the string after the command
	else if (command.substr(0,4) == "taed"){
		if (check_name(command.substr(5), students)){ 
			list_courses_tad(students[student_index(
				command.substr(5), students)]);
		}
	}
	else if (command.substr(0,6) == "roster"){
		if(check_class(command.substr(7), classes)){
			list_class_roster(classes[class_index(
				command.substr(7), classes)]);
		}
	}  // does nothing if names are not in students
	else if (command.substr(0,5) == "paths"){
		if (check_names(command.substr(6),students)){
			findPaths(command.substr(6), graph, students);
		}
	}	
	else if (command.substr(0,12) == "shortestpath"){
		if (check_names(command.substr(13),students)){
			findShortestPath(command.substr(13), graph, students);
		}
	}//does nothing if command isn't recognized
}
//checks to see if the names separated by a space are in students
//prints "Student not found" if false
bool check_names(string names, vector<Student> students){
	int space = names.find_first_of(' ',0);
	string name1 = names.substr(0, space);
	string name2 = names.substr(space+1);
	if ((is_student(name1, students)) and 
		(is_student(name2, students))){
		return true;
	}
	cout << "Student not found" << endl;
	return false;
}
//checks to see if the name is in students
//prints out "Student not found" if false
bool check_name(string name, vector<Student> students){
	if (is_student(name, students)){
		return true;
	}
	cout << "Student not found" << endl;
	return false;
}
//checks to see if class is in classes
//prints out "Class not found" if false
bool check_class(string name, vector<Class> classes){
	if(is_class(name, classes)){
		return true;
	}
	cout << "Class not found" << endl;
	return false;
}
//calls sameDFS or DFS depending on if the path starts
//and ends at the same person
//called for "paths" command
void findPaths(string names, Graph graph,
    vector<Student> students){
	int space = names.find_first_of(' ',0);
	string name1 = names.substr(0, space);
	string name2 = names.substr(space+1);
	int size = students.size();
	int path[size];    //array to save path
	int path_count = 0;
	int start = student_index(name1, students); //starting vertex
	int finish = student_index(name2, students); //end vertex
	graph.unmarkAll();
	int iter = 0; // # of times func has been called
	//check if path starts and ends at same person
	if (start == finish){ 
		//check if tad himself
		if (students[start].did_ta_for(students[finish])){ 
			cout << name1 << " +- "  
			<< students[start].class_tad_for(students[finish])
			<< " -> " << name2 << endl;
		}
		else{  //did not ta himself
		sameDFS(start, finish, graph, students, path, path_count, 
			iter);
		}
	}
	else{
		DFS(start, finish, graph, students, path, path_count);
	}
}
//calls sameShortestDFS or shortestDFS and then calls
//printShortestPath
//called for "shortestpath" command
void findShortestPath(string names, Graph graph, 
	vector<Student> students){
	vector<int> pathways; //holds all correct paths
	vector<int> path_lengths; //holds each paths length in parallel
	int space = names.find_first_of(' ',0);
	string name1 = names.substr(0, space);
	string name2 = names.substr(space+1);
	int size = students.size();
	int path[size];
	int path_count = 0;
	int start = student_index(name1, students); //start vertex
	int finish = student_index(name2, students);//end vertex
	graph.unmarkAll();
	int iter = 0;  //iteration count
	if (start == finish){ //path starts and ends at same place
		if (students[start].did_ta_for(students[finish])){ //tad himself
			cout << name1 << " +- "  
			<< students[start].class_tad_for(students[finish])
			<< " -> " << name2 << endl;
		}
		else{
		sameshortestDFS(start, finish, graph, students, path, 
		path_count, pathways, path_lengths, iter);
		printShortestPath(pathways, path_lengths, students);
		}	
	}
	else{
		shortestDFS(start, finish, graph, students, path, 
		path_count, pathways, path_lengths);
		printShortestPath(pathways, path_lengths, students);
	}	
}
//puts all poosible paths into pathways and their lengths into
//path_lengths using recursive Depth First Algorithm
void shortestDFS(int start, int finish, Graph graph, 
	vector<Student> students,int path[], int path_count,
	  vector<int> &pathways, vector<int> &path_lengths ){
	int size = students.size();
	graph.markVertex(start); 
	path[path_count] = start;
	path_count++;
	if (start == finish){    //end of path
		for (int i = 0 ; i < path_count; i++){
			 pathways.push_back(path[i]);	
		}
		path_lengths.push_back(path_count);
	}
	else{
		for (int i = 0 ; i < size; i++){
			if ((!graph.isMarked(i)) and
				(graph.isAdjacent(start,i))){
				shortestDFS(i, finish, graph, students, path,
				path_count, pathways, path_lengths);
			}
		}
	}
    path_count--;         //gets here if path is unsuccessful
    graph.unmarkVertex(start);
}
//prints the shortest path in pathways
void printShortestPath(vector<int> pathways,
 vector<int> path_lengths, vector<Student> students){
	int min;
	min = find_min(path_lengths);
	int shortestpath;
	shortestpath = path_lengths[min];
	vector<int> path;
	int start = 0;
	for (int i = 0 ; i < min ; i++){
		start += path_lengths[i]; //starting point of shortest path
	}
	int end = start + shortestpath; //ending point of shortest path
	for (int i = start ; i < end ; i++){
		path.push_back(pathways[i]); //puts shortest path into vector path
	} //prints out shortest path in proper format
	for (int i = 0 ; i < shortestpath; i++){
		cout << students[path[i]].get_name();
		if (i + 1 < shortestpath){
			cout << " +- ";
			cout << students[path[i]].class_tad_for
			(students[path[i+1]]);
			cout << " -> ";
		}
	}	
    cout << endl; 
}
//creates the approprate edges represented as true
//in the adjacency matrix
void make_graph(Graph &graph, vector<Student> students){
	int size = students.size();
	for (int i = 0 ; i < size ; i++ ){
		for (int j = 0; j < size ; j++){
			if(i != j){
				if(students[i].did_ta_for(students[j])){
					graph.createEdge(i,j);
				}
			}
		}
	}
}
//prints out all correct paths using recursive depth fist search
//
void DFS(int start, int finish, Graph graph,
 vector<Student> students, int path[],
		int &path_count){
	int size = students.size();
	graph.markVertex(start);
	path[path_count] = start; //verticies are stored in path
	path_count++;
	if (start == finish){ //path has reached the end
		for (int i = 0 ; i < path_count; i++){
			cout << students[path[i]].get_name();
			if (i + 1 < path_count){
				cout << " +- ";
				cout << students[path[i]].class_tad_for(
				students[path[i+1]]);
				cout << " -> ";
			}
		}
		cout << endl ;
	}
	else{
		for (int i = 0 ; i < size; i++){
			if ((!graph.isMarked(i)) and
				(graph.isAdjacent(start,i))){
				DFS(i, finish, graph, students, path, path_count);
			}   // recursive call
		}
	}
    path_count--;     //if path is unsuccessful
    graph.unmarkVertex(start);
}
//finds the minimum value in path_lengths
//used for determining the shortest path
int find_min(vector <int> path_lengths){
	int size = path_lengths.size();
	int smallest = 0;
	for (int i = 0 ; i < size; i++){
		if (path_lengths[i] < path_lengths[smallest]){
			smallest = i;
		}
	}
	return smallest;
}
//prints out all possible paths when the path starts and finishes
//at the same student
void sameDFS(int start,int finish,Graph graph, vector<Student> students,
int path[], 
	int path_count, int iter){
	int size = students.size();
	if (iter != 0){  //start is not marked on first iteration
		graph.markVertex(start); 
	}
	path[path_count] = start;
	path_count++;
	if ((start == finish) and (iter != 0)){  //path not printed on first iter
		for (int i = 0 ; i < path_count; i++){
			cout << students[path[i]].get_name(); //print succesful path
			if (i + 1 < path_count){
				cout << " +- ";
				cout << students[path[i]].class_tad_for(
				students[path[i+1]]);
				cout << " -> ";
			}
		}
		cout << endl ;
	}
	else{
		for (int i = 0 ; i < size; i++){
			if ((!graph.isMarked(i)) and
				(graph.isAdjacent(start,i))){
				iter++;   //iter = iter + 1
				sameDFS(i, finish, graph, students,
				path, path_count,iter); //recursive call
			}
		}
	}
    path_count--; //unsuccessful path
    graph.unmarkVertex(start);
}
//stores all paths that start and finish on same student in
//int vector
void sameshortestDFS(int start, int finish, Graph graph,
 vector<Student> students,int path[], int path_count,
   vector<int> &pathways, vector<int> &path_lengths, int iter ){
	int size = students.size();
	if (iter != 0){ //does not mark when iter is 0
		graph.markVertex(start); 
	}
	path[path_count] = start;
	path_count++;
	if ((start == finish) and (iter != 0)){ //does not store when iter is 0
		for (int i = 0 ; i < path_count; i++){
			pathways.push_back(path[i]); //add successful path	
		}
		path_lengths.push_back(path_count); //add succesful path length
	}
	else{
		for (int i = 0 ; i < size; i++){
			if ((!graph.isMarked(i)) and
				(graph.isAdjacent(start,i))){
				iter++; //iter = iter + 1 
				sameshortestDFS(i, finish, graph, students, path,
				path_count, pathways, 
				path_lengths, iter); //recursive call
			}
		}
	}
    path_count--; //unsuccessful path
    graph.unmarkVertex(start);
}
