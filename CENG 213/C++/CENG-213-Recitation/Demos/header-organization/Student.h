
#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <iostream>
#include <string>

typedef int StudentId;

class Student
{
private:
	StudentId 		id;
	std::string 	name;

public:
	// Constructor(s)
	Student(StudentId, const std::string& string);

	// Member Functions
	StudentId GetStudentId() const;
	const std::string& GetStudentName() const;
	//
	void SetStudentId(StudentId);
	void SetStudentName(const std::string&);
	void Print() const;
};

// HEADER DEFINITION
// Student::Student(StudentId name, const std::string& string id)
// {
// 	this->name = name;
// 	this->id = id;
// }
// StudentId Student::GetStudentId() const
// {
// 	return id;
// }

// const std::string& Student::GetStudentName() const
// {
// 	return name;
// }

// void Student::SetStudentName(StudentId newId)
// {
// 	id = newId;
// }

// void Student::SetStudentName(const std::string& newName)
// {
// 	name = newName;
// }

// void Student::Print() const
// {
// 	std::cout << "Name: " << name << " Id " << id << std::endl;
// }

#endif