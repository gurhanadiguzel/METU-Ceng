#include "Classroom.h"
#include "Student.h"

int main()
{
	Student s1(999, "Ahmet");

	//const Student& constRefS1 = s1;

	//constRefS1.SetStudentId(123);



	// Student s2 = Student(999, "Mehmet");

	// s1.Print();  std::cout << std::endl;
	// s2.Print();  std::cout << std::endl;

	// std::vector<Student> list;
	// list.push_back(Student(123, "Ali"));
	// list.push_back(Student(123, "Ayse"));
	// list.push_back(Student(123, "Naz"));

	// Classroom classroom(list);
	// classroom.Print();

	return 0;
}