#include "Classroom.h"

Classroom::Classroom(const std::vector<Student>& students)
{
    studentList = students;
}

bool Classroom::GetStudent(Student& student, int index)
{
    if(index >= studentList.size())
        return false;

    student = studentList[index];
    return true;
}

void Classroom::AddStudent(const Student& s)
{
    studentList.push_back(s);
}

void Classroom::Print() const
{
    std::cout << "[";
    for(int i = 0; i < studentList.size(); i++)
    {
        studentList[i].Print();
        if(i != (studentList.size() - 1))
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}