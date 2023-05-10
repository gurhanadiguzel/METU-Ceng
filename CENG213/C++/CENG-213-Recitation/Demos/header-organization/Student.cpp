#include "Student.h"

Student::Student(StudentId id, const std::string& name)
{
	this->name = name;
	this->id = id;
}

StudentId Student::GetStudentId() const
{
	return id;
}

const std::string& Student::GetStudentName() const
{
	return name;
}

void Student::SetStudentId(StudentId newId)
{
	id = newId;
}

void Student::SetStudentName(const std::string& newName)
{
	name = newName;
}

void Student::Print() const
{
	std::cout << "Name: " << name << " Id " << id;
}