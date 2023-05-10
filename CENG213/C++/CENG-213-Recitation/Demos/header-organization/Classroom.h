#ifndef __CLASSROOM_H__
#define __CLASSROOM_H__

#include <vector>
#include "Student.h"

class Classroom
{
private:
    std::vector<Student> studentList;
public:
    Classroom(const std::vector<Student>&);

    bool GetStudent(Student&, int index);
    void AddStudent(const Student&);
    void Print() const;
};

#endif