#include "Student.h"

// YOU CAN COMPLETELY CHANGE THIS FILE AS YOU NEED. //

/****************************************************/
/****               *** STUDENT ***              ****/

/* Constructor : initializes <id> of the object to
   the given integer, and <fullname> and <department>
   to the given strings, respectively.
   Also, initalizes the <gpa> of the object to 100.0.
   Also, it is recommended to hold a bool variable to
   carry the upgrade information and initalize it to
   false. This may be needed in the other methods
   later on.
*/
Student::Student(int _id, string _fullname, string _department) {
	// TODO
	this->id = _id;
   this->fullname = _fullname;
   this->department = _department;
   this->gpa = 0.0;
   this->upgrade = false;
}

/* Destructor  : It is responsible of the destruction of
   the CourseInstance objects owned by the current student.
*/
Student::~Student() {
	// TODO
   courses.clear();
}

/* Copy constructor : It totally applies shallow copy.
*/
Student::Student(const Student& student) {
	// TODO
   this->id = student.id;
   this->fullname = student.fullname;
   this->department = student.department;
   this->gpa = student.gpa;
   this->upgrade = student.upgrade;
   this->courses = student.courses;
}

/* This method returns the id of the student.
*/
int Student::getId() const {
	// TODO
	return this->id;
}

/* This method returns the GPA of the student.
*/
float Student::getGPA() const {
	// TODO
	return this->gpa;
}

/* This method returns the courses taken by
   this student. Note that the grade taken in that
   course is not important. You should return
   all the passed and failed courses.
*/
vector<const CourseInstance*> Student::listCourses() const {
	// TODO
	return courses;
}

/* This method grades the given course for this student.
   In order to grade the course, learnGrade() method is 
   called. learnGrade() method is already implemented by 
   the HW admin, yet it is invisible to you. You call it
   by giving the course name as the first argument and
   student id as the second argument. For instance;
       learnGrade("Programming Languages", 1234567);
   Then, you should save the grade returned by learnGrade().
   
   Also, after learning the grade, you should recalculate
   the GPA of the student in this method.
   GPA is a float value calculated by simply taking the 
   average of all the graded courses (The courses for which
   gradeCourse() method is called before or now).
*/
void Student::gradeCourse(const OpenCourse& openCourse) {
	// TODO
   enum Grade grade = learnGrade(openCourse.getName(), id);

}

/* This method sets the upgrade information for the current
   student to true. You may not need this method, yet still
   it is defined in case that it may be beneficial later.
*/
void Student::setUpgradeStatus() {
	// TODO
   this->upgrade = true;
}


/****************************************************/
/****              *** FRESHMAN ***              ****/

/* Constructor : initializes <id> of the object to
   the given integer, and <fullname> and <department>
   to the given strings, respectively.
   Also, initalizes the <gpa> of the object to 100.0.
   Also, it is recommended to hold a bool variable to 
   carry the upgrade information and initalize it to 
   false. This may be needed in the other methods 
   later on.
*/
Freshman::Freshman(int id, string fullname, string department):Student(id,fullname,department)
{
	// TODO
   this->gpa = 0.0;
   this->upgrade = false;
}

/* Destructor  : It is responsible of the destruction of
   the CourseInstance objects owned by the current freshman.
*/
Freshman::~Freshman() {
	// TODO
   this->courses.clear();
}

/* Copy constructor : It totally applies shallow copy.
*/
Freshman::Freshman(const Freshman &freshman) : Student(id, fullname, department)
{
   // TODO
   this->gpa = freshman.gpa;
   this->upgrade = freshman.upgrade;
   this->courses = freshman.courses;
}

/* This method tries to add the given opencourse.
   In order to add, it just checks the prerequisites of the
   course is satisfied ot not. If all the prerequisites are
   satisfied (the prerequisite courses had been taken before),
   then it adds the course by constructiong a new CourseInstance
   object by using given OpenCourse object, then the newly
   created CourseInstance should be stored in an array of taken
   courses.
   If the course could be added successfuly, the method returns
   true. Otherwise (if there is at least one non-satisfied 
   prerequisite), it returns false.
*/
bool Freshman::addCourse(const OpenCourse& opencourse) {
	// TODO
   bool taken = true;
   for (int i = 0; i < opencourse.getPrerequisites().size(); i++){
      taken = false;
      for (int j = 0; j < this->courses.size(); j++){
         taken = true;
      }
      if (taken == false)
         return false;
   }
   Student student = Student(id, fullname, department);
   CourseInstance *new_course = new CourseInstance(opencourse, student);
   this->courses.push_back(new_course);
   return true;  
}

/****************************************************/
/****              *** SOPHOMORE ***             ****/

/* Constructor : initializes <id> of the object to
   the given integer, and <fullname> and <department>
   to the given strings, respectively.
   Also, initalizes the <gpa> of the object to 100.0.
   Also, it is recommended to hold a bool variable to
   carry the upgrade information and initalize it to
   false. This may be needed in the other methods
   later on.
   Also, this class should hold two bool variables to
   store the information about the completion of 
   INTERNSHIP-1 and INTERNSHIP-2. Constructor should
   initialize those variables to false.
*/
Sophomore::Sophomore(int id, string fullname, string department) : Freshman(id, fullname, department)
{
   // TODO
   this->gpa = 0.0;
   this->upgrade = false;
   this->int1 = false;
   this->int2 = false;
}

/* Constructor : initializes the derived members of the
   Freshman class with the one given as first parameter.
   Also, this class should hold two bool variables to
   store the information about the completion of 
   INTERNSHIP-1 and INTERNSHIP-2. Constructor should
   initialize those variables to false.
 */
Sophomore::Sophomore(const Freshman &freshman) : Freshman(id, fullname, department)
{
   // TODO
   this->upgrade = false;
   this->int1 = false;
   this->int2 = false;
}

/* Destructor  : It is responsible of the destruction of
   the CourseInstance objects owned by the current sophomore.
*/
Sophomore::~Sophomore() {
	// TODO
   this->courses.clear();
}

/* Copy constructor : It totally applies shallow copy.
*/
Sophomore::Sophomore(const Sophomore &sophomore) : Freshman(id, fullname, department)
{
   // TODO
   this->gpa = sophomore.gpa;
   this->courses = sophomore.courses;
   this->upgrade = sophomore.upgrade;
   this->int1 = sophomore.int1;
   this->int2 = sophomore.int2;
}

/* This method grades the internship with the given id
   (1 or 2).
   In order to grade the internship, learnGrade() method 
   is called. learnGrade() method is already implemented 
   by the HW admin, yet it is invisible to you. You call 
   it by giving the internship name as the first argument 
   and student id as the second argument. For instance;
       learnGrade("INTERNSHIP-1", 1234567); or
	   learnGrade("INTERNSHIP-2", 1234567);
   If the grade returned by learnGrade() method is greater
   than or equal to DD, then restore the value of the 
   corresponding internship variable as true, else leave it
   as false.
*/
void Sophomore::doAnInternship(int intership_no) {
	// TODO
   if(intership_no == 1){
      enum Grade intern1 = learnGrade("INTERNSHIP-1", this->getId());
      if(intern1 >= DD)
         this->int1 = true;
      else
         this->int1 = false;
   }
   else if (intership_no  == 2){
      enum Grade intern2 = learnGrade("INTERNSHIP-2", this->getId());
      if(intern2 >= DD)
         this->int2 = true;
      else
         this->int2 = false;
   } 
}

/* This method returns the status of the internship with
   the given id (1 or 2). The status is the fact that 
   it is completed successfully or not (true or false, 
   respectively).
*/
bool Sophomore::getInternshipStatus(int intership_no) {
	// TODO
   if(intership_no == 1)
      return this->int1;
   else if(intership_no == 2)
      return this->int2;
}

/****************************************************/
/*                                                  */
/*           IT IS ENOUGH TO IMPLEMENT              */
/*    JUST CONSTRUCTORs, DESTRUCTOR & COPY CONS.    */
/*        FOR THE CLASS JUNIOR and SENIOR           */
/*     SIMILAR TO CLASS FRESHMAN and SOPHOMORE.     */
/*                                                  */
/*     JUNIOR and SENIOR OBJECTS MAY BE DEFINED     */
/*     IN TESTS, YET selectElectiveCourse() and     */ 
/*        graduate() METHOD WILL NOT BE USED.       */
/*                                                  */
/****************************************************/


/****************************************************/
/****                *** JUNIOR ***              ****/

Junior::Junior(int id, string fullname, string department) : Sophomore(id, fullname, department)
{
   // TODO
}

Junior::Junior(const Sophomore &sophomore) : Sophomore(id, fullname, department)
{
   // TODO
}

Junior::~Junior() {
	// TODO
   this->courses.clear();
}

Junior::Junior(const Junior &junior) : Sophomore(id, fullname, department)
{
   // TODO
   this->gpa = junior.gpa;
   this->courses = junior.courses;
   this->upgrade = junior.upgrade;
   this->int1 = junior.int1;
   this->int2 = junior.int2;
}

void Junior::selectElectiveCourse() {
	// LEAVE EMPTY
}

/****************************************************/
/****                *** SENIOR ***              ****/

Senior::Senior(int id, string fullname, string department) :Junior(id, fullname, department)
{
   // TODO
}

Senior::Senior(const Junior &junior) : Junior(id, fullname, department)
{
   // TODO
}

Senior::~Senior() {
	// TODO
   this->courses.clear();
}

Senior::Senior(const Senior &senior) : Junior(id, fullname, department)
{
   // TODO
   this->gpa = senior.gpa;
   this->courses = senior.courses;
   this->upgrade = senior.upgrade;
   this->int1 = senior.int1;
   this->int2 = senior.int2;
}

bool Senior::graduate() {
	// LEAVE EMPTY
	return true;
}

