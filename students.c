/*
 * This is the file in which you will implement the functionality required by
 * the assignment.  Make sure to add your name and @oregonstate.edu email
 * address below:
 *
 * Name:Li Hung Chen
 * Email:chenlih@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "dynarray.h"

/*
 * This function should allocate and initialize a single student struct with
 * name, ID, and GPA data.
 *
 * Params:
 *   name - a string containing the student's name.  Note that you'll have to
 *     make a copy of this string to store in the student struct instead of
 *     storing this string directly.
 *   id - an integer ID for the student
 *   gpa - the student's GPA
 *
 * Return:
 *   Should return a newly-allocated student structure whose fields are
 *   initialized with the values provided.
 */
struct student* create_student(char* name, int id, float gpa) {		
	struct student* cs=malloc(sizeof(struct student));	//create pointer cs and alloc memory
	int n=strlen(name);					//define name's length to n
	char* cs_name=malloc(n*sizeof(char));			//cs_name's memory is as same as name's
	strncpy(cs_name,name,n);				//copy name's value to cs_name

								
	cs->name=cs_name;					//pointer cs point to name and has value cs_name
	cs->id=id;						//pointer cs point to id and has value id		
	cs->gpa=gpa;						//pointer cs point to gpa and has value gpa
	

  return cs;							//return pointer cs
}


/*
 * This function should free all memory allocated by create_student() for a
 * single student.  This function must free all relevant memory and cannot
 * result in a memory leak.
 *
 * Params:
 *   student - a pointer to the student whose memory should be freed.  This
 *     function must free any memory allocated to the fields of this struct
 *     as well as memory allocated for the struct itself.
 */
void free_student(struct student* student) {
								
free(student->name);						//free the memory which point to the name
free(student);							//free the memory which point to student

}


/*
 * This function should create a struct student for each student represented
 * in the information provided in the function arguments, and it should store
 * those students in a dynamic array (i.e. struct dynarray) allocated by this
 * function.  In particular, you should create a dynamic array and insert new
 * student structs into it, such that the i'th student in the array has the
 * i'th name, the i'th ID, and the i'th GPA from the arrays provided as
 * arguments.  You should use your create_student() function to allocate and
 * initialize each student struct stored in the array, and you should use the
 * provided dynamic array functions to allocate and work with the dynamic
 * array.  At the end of the function, you should return the dynamic array
 * with student structures stored in it.
 *
 * Params:
 *   num_students - the number of students to be stored in the newly allocated
 *     dynamic array
 *   names - an array of the names of the students to be stored in the dynamic
 *     array of student structs.  This array will have length num_students.
 *   ids - an array of the IDs of the students to be stored in the dynamic
 *     array of student structs.  This array will have length num_students.
 *   gpas - an array of the GPAs of the students to be stored in the dynamic
 *     array of student structs.  This array will have length num_students.
 *
 * Return:
 *   Should return a pointer to the newly allocated dynamic array containing
 *   newly-created student structs.  The i'th student in this array should have
 *   the i'th name, the i'th ID, and the i'th GPA from the arrays provided as
 *   arguments.
 */
struct dynarray* create_student_array(int num_students, char** names, int* ids,
    float* gpas) {

	struct dynarray* csa=dynarray_create();			 //create dynarray by using function from dynarray.c
	

	for(int i=0; i<num_students;i++){			 //use loop to put data one by one
	 struct student* stc=create_student(names[i],ids[i],gpas[i]); //create students

	 dynarray_insert(csa,i,stc);			//using function from dynarray.c to insert stc into array csa

	}

  return csa;
}


/*
 * This function should free all of the memory allocated to a dynamic array of
 * student structs, including the memory allocated to the array itself as
 * well as any memory allocated to the individual student structs.  You
 * should use free_student() to free the memory for each individual student,
 * and you should use provided dynamic array functions to free the memory
 * associated with the dynamic array itself.  This function must free *all*
 * memory associated with a dynamic array of students and must not result in
 * any memory leaks.
 *
 * Params:
 *   students - a pointer to the dynamic array of student structs whose memory
 *     is to be freed
 */
void free_student_array(struct dynarray* students) {
int n=dynarray_size(students);
struct student* st;

    for(int i=0;i<n;i++){
      st=dynarray_get(students,i);
      free_student(st);
    }
  dynarray_free(students);  

}


/*
 * This function should print the name, ID, and GPA of each student in an
 * array, one student per line.  You must use provided dynamic array functions
 * to access the student data stored in the array.
 *
 * Params:
 *   students - the dynamic array of students to be printed
 */
void print_students(struct dynarray* students) {
int n=dynarray_size(students);					//find the array size
int i;
struct student* stu;
  for(i=0;i<n;i++){						//use loop to prinf student
     stu=dynarray_get(students,i);
     printf("%s  %d  %f \n",stu->name,stu->id,stu->gpa);
  }

}


/*
 * This function should return a pointer to the student in a given array with
 * the highest GPA.  You should not make a copy of the student being returned,
 * i.e. this function should not allocate any memory.  Instead, you should
 * simply return the pointer to the student struct that's already stored in
 * the array.  You must use the provided dynamic array functions to access
 * the data stored in the array.
 *
 * Params:
 *   students - the array from which to find the student with the highest GPA
 *
 * Return:
 *   Should return a pointer to the student in the array with the highest GPA.
 *   You should not make a copy of the student being returned but should
 *   instead return the pointer to the student struct that's already stored in
 *   the array.
 */
struct student* find_max_gpa(struct dynarray* students) {
int n=dynarray_size(students);				//get the size of array student
float maxgpa=0;						//define max gpa =0

struct student* stud;
int maxgpa_index=-1;


   for(int i;i<n;i++){					//use loop to compare each gpa with maxgpa
   stud=dynarray_get(students,i);			//if greater than maxgpa,then replace to maxgpa
      if(stud->gpa >maxgpa){
	maxgpa=stud->gpa;
	maxgpa_index=i;
	}
   }

  return dynarray_get(students,maxgpa_index);	
}


/*
 * This function should return a pointer to the student in a given array with
 * the lowest GPA.  You should not make a copy of the student being returned,
 * i.e. this function should not allocate any memory.  Instead, you should
 * simply return the pointer to the student struct that's already stored in
 * the array.  You must use the provided dynamic array functions to access
 * the data stored in the array.
 *
 * Params:
 *   students - the array from which to find the student with the lowest GPA
 *
 * Return:
 *   Should return a pointer to the student in the array with the lowest GPA.
 *   You should not make a copy of the student being returned but should
 *   instead return the pointer to the student struct that's already stored in
 *   the array.
 */
struct student* find_min_gpa(struct dynarray* students) {
int n=dynarray_size(students);
float mingpa=100;							//define mingpa=4

struct student* stud;
int mingpa_index=-1;

  for(int j=0;j<n;j++){						//use loop to compare with mingpa
     stud=dynarray_get(students,j);
	 if(stud->gpa <mingpa){					//if smaller than mingpa,then replace to mingpa
           mingpa=stud->gpa;
	   mingpa_index=j;
      }
  }
  return dynarray_get(students,mingpa_index);
}


/*
 * This function should sort the students stored in a dynamic array by
 * descending GPA (i.e. highest GPAs at the beginning of the array).  You may
 * implement any sorting algorithm you want, with the following constraints:
 *   - You must sort in place, i.e. you can't allocate additional memory.
 *   - You may not use built-in sorting functions like qsort(), i.e. you must
 *     implement the sort yourself.  You may implement any in-place sorting
 *     algorithm you like.  Some possibilities are selection sort, insertion
 *     sort, bubble sort, and quicksort.
 *   - You must use provided dynamic array functions (e.g. dynarray_get(),
 *     dynarray_set(), etc.) to access and modify the contents of the dynamic
 *     array.
 *
 * Params:
 *   students - the dynamic array of students to be sorted.  When the function
 *     returns, this array should be sorted by descending GPA.
 */
void sort_by_gpa(struct dynarray* students) {
int n=dynarray_size(students);						//define n as the size of students

  for(int i=0;i<n-1;i++){						
	for(int j=0;j<n-i-1;j++){					
	struct student* st1=dynarray_get(students,j);
	struct student* st2=dynarray_get(students,j+1);

	  if(st1->gpa <st2->gpa){					//if former one smaller than later one
	  struct student* tmp=dynarray_get(students,j);			//switch these two value
	  dynarray_set(students,j,dynarray_get(students,j+1));	
	  dynarray_set(students,j+1,tmp);
	  }
	}

  }
}
