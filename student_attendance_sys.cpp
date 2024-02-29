#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Attendance{
    public:
    virtual void attendance(string *array1, int *array2, int *array3, int *array4, int number) = 0;
};
class Teacher:public Attendance{
    private:
    char present = 'P';
    char absent = 'A';

    public:
    Teacher(){}
    void addStudent(string *names, int no_students){
        ofstream fout("e:students.txt", ios::app); // UPDATE THE FILEPATH TO YOUR FILEPATH
        string name;
        int classes, presents, absents;
        cin.ignore();
        cout << "Enter student name: ";
        getline(cin, name);
        bool check = false;
        for(int i = 0; i < no_students; i++){
            if(names[i] == name){
                check = true;
            }
        }

        if(check){
            cout << "Student already exists" << endl;
        }
        else{
            cout << "Enter " << name << " no of classes: ";
            cin >> classes;
            cout << "Enter " << name << " present: ";
            cin >> presents;
            cout << "Enter " << name << " absents: ";
            cin >> absents;
            fout << name << "\t" << classes << "\t" << presents << "\t" << absents << "\t" << endl;
            cout << "Student has been added in the file" << endl;
        }

        fout.close();
    }
    void attendance(string *names, int *classes, int *presents, int *absents, int no_students){
        char user = '0';
        bool run = true;
        cout << "Conduct Attendance: " << endl;
        for(int i = 0; i < no_students; i++){
            while(run){
                cout << names[i] << "\t\t";
                cin >> user;
                user = toupper(user);
                if(user == 'P' || user == 'A'){
                    break;
                }
            }
            if(user == 'P'){
                presents[i]++;
            }
            else{
                absents[i]++;
            }
            classes[i]++;
        }
    }
    
};
class Student{
    private:
    string withdraw = "Withdraw";
    string enrolled = "Enrolled";

    public:
    Student(){}
    void display(string *names, int *classes, int *presents, int *absents, int no_students){
        cout << "Current Attendance: " << endl;
        cout << "------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Students\t" << "Classes\t\t" << "Presents\t" << "Absents\t\t" << "Percentage\t" << "Status\t" << endl;
        for(int i = 0; i < no_students; i++){
            double percentage = ((double)presents[i]/(double)classes[i])*100;
            if(absents[i] > 11){
                cout << names[i] << "\t\t" << classes[i] << "\t\t" << presents[i] << "\t\t" << absents[i] << "\t\t" << percentage << "\t\t" << withdraw << endl;
            }
            else{
                cout << names[i] << "\t\t" << classes[i] << "\t\t" << presents[i] << "\t\t" << absents[i] << "\t\t" << percentage << "\t\t" << enrolled << endl;
            }
        }
    }
};

void count_students(int &no_students, string *names, int *classes, int *presents, int *absents);
void read_students(ifstream& fin, string *names, int *classes, int *presents, int *absents);
void write_file(string *names, int *classes, int *presents, int *absents, int no_students);
void display_menu();

int main(){

    ifstream fin("e:students.txt"); // UPDATE THE FILEPATH TO YOUR FILEPATH
    int no_students = 0;
    string *names = NULL;
    int *classes = NULL;
    int *presents = NULL;
    int *absents = NULL;

    cout << "\t\t\t Student Attendance System" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    Teacher teacher1;
    Student st1;
    Attendance *attendance = new Teacher();

    bool running = true;

    while(running){

        int add = 0;
        bool run = true;
        while(run){
            cout << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Conduct Attendance" << endl;
            cout << "3. Exit program" << endl;
            cout << "----> ";
            cin >> add;
            tolower(add);
            if(add == 1 || add == 2 || add == 3){
                break;
            }
            else{
                cout << "Enter valid input" << endl;
            }
        }

        switch(add){
            case 1:
                teacher1.addStudent(names, no_students);
                break;
            case 2:
                count_students(no_students, names, classes, presents, absents);
                names = new string[no_students];
                classes = new int[no_students];
                presents = new int[no_students];
                absents = new int[no_students];
                read_students(fin, names, classes, presents, absents);
                attendance->attendance(names, classes, presents, absents, no_students); 
                write_file(names, classes, presents, absents, no_students);
                st1.display(names, classes, presents, absents, no_students);
                break;
            case 3:
                running = false;
                break;
            default:
                cout << "Enter valid input" << endl;
                break;
        }
    }

    delete[] names;
    delete[] classes;
    delete[] presents;
    delete[] absents;
    fin.close();
    return 0;
}
void count_students(int &no_students, string *names, int *classes, int *presents, int *absents){
    ifstream fin1("e:students.txt"); // UPDATE THE FILEPATH TO YOUR FILEPATH
    string temp1, temp2, temp3, temp4; 
    fin1 >> temp1 >> temp2 >> temp3 >> temp4;
    while(fin1 >> temp1 >> temp2 >> temp3 >> temp4){
        no_students++;
    }
    fin1.close();
}
void read_students(ifstream& fin, string *names, int *classes, int *presents, int *absents){
    int i = 0;
    int cl, present, absent;
    string name;

    string temp1, temp2, temp3, temp4;
    fin >> temp1 >> temp2 >> temp3 >> temp4;
    while(fin >> name >> cl >> present >> absent){
        names[i] = name;
        classes[i] = cl;
        presents[i] = present;
        absents[i] = absent;
        i++;
    }
}
void write_file(string *names, int *classes, int *presents, int *absents, int no_students){
    ofstream fout("e:students.txt"); // UPDATE THE FILEPATH TO YOUR FILEPATH
    fout << "Students\t" << "Classes\t\t" << "Presents\t" << "Absents\t" << endl;
    for(int i = 0; i < no_students; i++){
        fout << names[i] << "\t\t" << classes[i] << "\t\t" << presents[i] << "\t\t" << absents[i] << endl;
    }
    fout.close();
}
