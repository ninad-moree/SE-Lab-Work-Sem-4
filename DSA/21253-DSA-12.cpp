#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Hashtable
{
public:
    int addr;
    Hashtable();
}HT[10];

Hashtable::Hashtable()
{
    addr = -1;
}

class Employee : public Hashtable
{
    int emp_id;
    string salary;
    string name;
    string exp;

public:
    void add_Rec();
    void display_Rec();
    void search_Rec();
    void delete_Rec();
};

void Employee::add_Rec()
{
    int index, count, tablesize = 10;
    int location;
    cout << "How many records..? : ";
    cin >> count;
    cout << endl;
    ofstream fout;
    fout.open("employee.txt", ios::out);
    for (int i = 0; i < count; i++)
    {
        cout << endl;
        cout << "Enter Employee id: ";
        cin >> emp_id;
        cout << "Enter Employee name: ";
        cin >> name;
        cout << "Enter Employee salary: ";
        cin >> salary;
        cout << "Enter Experience: ";
        cin >> exp;
        cout << endl;

        location = fout.tellp();
        index = emp_id % tablesize;
        HT[index].addr = location;

        fout << emp_id << " " << name << " " << exp << " " << salary << endl;
    }
    fout.close();

    
}

void Employee::display_Rec()
{
    string buffer;
    int cnt = 1;
    ifstream fin;

    fin.open("employee.txt", ios::in);

    while (getline(fin, buffer))
    {
        cout << "Record " << cnt << " : " << buffer << endl;
        ++cnt;
    }
    fin.close();
}

void Employee::search_Rec()
{
    int id;
    cout << "Enter the Emp_id to search: ";
    cin >> id;

    ifstream fin;
    fin.open("employee.txt", ios::in);

    string buffer;
    bool recordFound = false;
    while (getline(fin, buffer))
    {
        int curr_id;
        stringstream ss(buffer);
        ss >> curr_id;
        if (curr_id == id)
        {
            recordFound = true;
            break;
        }
    }
    fin.close();
    if(recordFound == true)
    {
        cout<<"Record Found:";
        cout<<buffer<<endl;
    }
    else
        cout<<"Record not found"<<endl;
}

void Employee::delete_Rec()
{
    int id;
    cout << "Enter the Emp_id to delete: ";
    cin >> id;

    ifstream fin;
    fin.open("employee.txt", ios::in);

    ofstream fout;
    fout.open("TempDAF.txt", ios::out);

    string buffer;
    bool recordFound = false;
    while (getline(fin, buffer))
    {
        int curr_id;
        stringstream ss(buffer);
        ss >> curr_id;
        if (curr_id != id)
        {
            fout << buffer << endl;
        }
        else
        {
            recordFound = true;
            HT[curr_id % 10].addr = -1;
        }
    }

    fin.close();
    fout.close();

    remove("employee.txt");
    rename("TempDAF.txt", "employee.txt");

    if (recordFound)
    {
        cout << "Record deleted successfully." << endl;
    }
    else
    {
        cout << "Record not found." << endl;
    }
}

int main()
{
    Employee E;
    bool repeat = true;
    int choice;

    while(repeat)
    {
        cout << endl;
        cout << " ***** MENU *****" << endl;
        cout << "1. Add Data" << endl;
        cout << "2. Display Data" << endl;
        cout << "3. Delete Data" << endl;
        cout << "4. Search Data" << endl;
        cout << "5. Exit" << endl;
        cout << endl;

        cout << "Enter your choice:";
        cin >> choice;

        switch(choice)
        {
            case 1:
            E.add_Rec();
            break;

            case 2:
            E.display_Rec();
            break;

            case 3:
            E.delete_Rec();
            break;

            case 4:
            E.search_Rec();
            break;

            case 5:
            cout<<"Exiting the code"<<endl;
            repeat = false;
            break;

            default:
            cout<<"Invalid Choice"<<endl;
            break;
        }
    }
    return 0;
}
