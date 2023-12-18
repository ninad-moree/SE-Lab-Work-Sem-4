#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Student
{
    int rollNo;
    string name;
    string divison;
    string area_in_city;
    string city;

    public:

    void addRecord()
    {
        ofstream fout;
        int records;

        cout << "How many records do you want to insert:";
        cin >> records;
        fout.open("ninad.txt", ios::out);
        for (int i = 0; i < records; i++) 
        {
            cout << endl;
            cout << "Enter roll number:";
            cin >> rollNo;
            cout << "Enter name:";
            cin.ignore();
            getline(cin, name);
            cout << "Enter class:";
            cin >> divison;
            cout << "Enter area of the city:";
            cin >> area_in_city;
            cout << "Enter city:";
            cin >> city;
            cout << endl;

            if (!fout) 
                cout << "Error while opening the file";
            else
                fout<<rollNo<<left<<setw(10)<<name<<left<<setw(10)<<divison<<left<<setw(10)<<area_in_city<<left<<setw(10)<<city<< endl;
        }
        fout.close();
    }

    void displayRecord()
    {
        char buffer[100];
        cout << " ***** RECORDS *****" << endl;
        ifstream fin;
        fin.open("ninad.txt", ios::in);
        if (!fin)
            cout << "Error while opening the file";
        else 
        {
            cin.ignore();
            int recordCount = 0;
            while (fin.getline(buffer, 100))
                cout << "\nRecord " << ++recordCount << " : " << buffer << endl;
            fin.close();  // Move the file closing statement here
        }
    }

    void searchRecord(int rollNo)
    {
        ifstream infile("ninad.txt", ios::in);
        if(!infile)
        {
            cout << "Error while opening the file";
            return;
        }
        int currentRollNo;
        string line;

        while (getline(infile, line))
        {
            istringstream iss(line);
            iss >> currentRollNo;

            if (currentRollNo == rollNo)
            {
                cout<<"Record Found : ";
                cout << line << endl;
            }
            else
                cout<<"Record Not Foune:";
        }
        infile.close();
    }

    void deleteRecord(int rollNo)
    {
        ifstream infile("ninad.txt", ios::in);
        ofstream outfile("ninad2.txt", ios::out | ios::app);

        if (!infile || !outfile)
        {
            cout << "Error while opening the file";
            return;
        }

        int currentRollNo;
        string line;

        while (getline(infile, line))
        {
            istringstream iss(line);
            iss >> currentRollNo;

            if (currentRollNo != rollNo)
                outfile << line << endl;
        }

        infile.close();
        outfile.close();

        remove("ninad.txt");
        rename("ninad2.txt", "ninad.txt");
    }
};

int main() 
{ 
    Student stu;

    int rollNo;
    string name;
    string divison;
    string area_in_city;
    string city;

    int number_of_records;
    bool repeat = true;
    int choice;
    int r;
    int sr;

    remove("ninad.txt");

    while (repeat) 
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

        switch (choice) 
        {
            case 1:
                stu.addRecord();
                break;

            case 2:
                stu.displayRecord();
                break;

            case 3:
                cout<<"Enter roll number to delete:";
                cin>>r;
                stu.deleteRecord(r);
                break;

            case 4:
                cout<<"Enter roll number to search:";
                cin>>sr;
                stu.searchRecord(sr);
                break;

            case 5:
                cout << "Exiting the code" << endl;
                repeat = false;
                break;

            default:
                cout << "Invalid Choice" << endl;
                break;
        }
    }
    return 0;
}
