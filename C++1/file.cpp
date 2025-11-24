#include <iostream>
#include <vector>
#include <fstream> // Operations with files

class Student
{
    // Initialization inside a class old C++ couldn't
    std::string m_first = "First";
    std::string m_last  = "Last";
    int         m_id    = 0;
    float       m_avg   = 0;
    
    public:
    // Constructor

    Student() {} // Default constructor

    Student(std::string first, std::string last, int id, float avg) // Default constr??
        : m_first  (first)
        , m_last   (last)
        , m_id     (id)
        , m_avg    (avg)
        {
        }
    
    int getAvg() const 
    {
        return m_avg;
    }

    int getID() const
    {
        return m_id;
    }

    std::string getFirst() const
    {
        return m_first;
    }

    std::string getLast() const
    {
        return m_last;
    }
    
    void print() const // La funciio no canvia la class (Const Correctness)
    {
        std::cout << m_first << " " << m_last << " ";
        std::cout << m_id << " " << m_avg << "\n";
    }
};



class Course
{
    std::string m_name = "Course";
    std::vector<Student> m_students;

public:

    Course() {}

    Course(const std::string& name) // Pasem per referencia pa no copiar en el constructor, pero posem const pa no poder canviar lo de dins
        : m_name(name)
        {
        }

    void addStudent(const Student& s)
    {
        m_students.push_back(s);
    }

    const std::vector<Student>& getStudents() const // La segona es que la funcio no cambia res, la primera que no es de tipo cambiable
    {
        return m_students;
    }

    // Load from a file
    void loadFromFile(const std::string& filename) // Not const because we are going to be loading file
    {
        std::ifstream fin(filename);
        //std::string temp;
        std::string first, last;
        int id;
        float avg;


        while (fin >> first) // Desde fin read a temp (if tokens exist (token = strings separated by whitespaces))
        {
            //std::cout << temp << "\n";
            //fin >> last;
            //fin >> id; // Automatically have an int in id
            //fin >> avg;
            fin >> last >> id >> avg;

            addStudent(Student(first, last, id, avg));
        }
    }

    void print() const
    {
        for (const auto& s : m_students)
        {
            s.print();
        }
    }
};



int main (int argc, char * argv[])
{
    Course c("COMP 4300");
    c.loadFromFile("students.txt");
    c.print();
    return 0;
}