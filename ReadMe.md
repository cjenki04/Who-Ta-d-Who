# ReadMe for COMP 15 HW6
## Degrees of Separation

Conor Jenkinson
Comp 15 - HW6

	Purpose - To correctly implement data structures that hold
                students and the classes the tad and took and to
                find the degrees of ta separation of the paths
                between them
        Files - main.cpp - reads in data from command line,
                fills the vectors of classes and students,
                reads in commands until the end of the file
                Class.cpp - implementation of Class class that holds
                a list of tas and students for that class
                Class.h - header file for Class class
                Student.Cpp - implementation of Student class that holds
                a list of the classes that student took and tad
                Student.h - header file for Student class
                Graph.cpp - implementation of Graph class, used for 
                representing edges between students and finding paths
                Graph.h - header file for Graph class  
      	    ReadMe.md - program description
                Makefile - used to compile and provide program
	Compile - Use included makefile

 Data Structs - dynamic arrays - used by Students and Classes to
                store strings of classes and students 
                Vector<int> - used to hold Students and Classes
                Graph - used to represent edges between students and 
                create paths between them
   Algorithim - Paths were found using a Depth First Search algorithm
                which recursively finds verticies until one is equal to the
                end vertex signifying that the path is correct. Students were
                mostly represented by their position in the students vector
                as Graphs did not have access to the Student class.  