#include <iostream>
#include <cstring>
#define size 10
using namespace std;

class DataItem
{
    long phno;
    string name;
    int link;
    public:
    DataItem()
    {
        phno=0;
        name="";
        link=-1;
    }
    friend class Hash;
};

class Hash
{
    DataItem ht[size];
    public:

    Hash() // constructor to initialize the default values
    {
        for(int i=0;i<size;i++)
        {
            ht[i].phno=0;
            ht[i].name="";
        }
    }

    int Hashcode(long key)
    {
        return key%size; // hash function= key%size
    }
    void insert_withoutreplace()
    {
        // without replacement
        DataItem ob;
        int pos;
        char ans;
        do
        {
            cout<<"Enter the name :";
            cin>>ob.name;
            cout<<"Enter the telephone number";
            cin>>ob.phno;
            pos= Hashcode(ob.phno);

            while(ht[pos].phno!=0)
            {
                ++pos;
                pos%=size;
            }
            ht[pos]=ob;
            cout<<"Do you want to add more items? (y/n):";
            cin>>ans;
        }while(ans=='y'||ans=='Y');
    }

    
    void search()
    {
        int hashindex, comp=0;
        long x;
        int flag=0;
        cout<<"Enter the telephone number to be searched:";
        cin>>x;
        hashindex= Hashcode(x);
        // move in array till an empty space is found
        while(ht[hashindex].phno!=0)
        {
            if(ht[hashindex].phno==x)
            {
                comp++;
                cout<<"Telephone number found at position "<<hashindex<<endl;
                cout<<"Name="<<ht[hashindex].name<<endl;
                cout<<"The number of comparisons= "<<comp<<endl;
                flag=1;
                break;
            }
            ++hashindex;
            // wrap around the table
            hashindex%=size;
            comp++;
        }
        if(flag==0)
        {
            cout<<"Telephone number is not present in the hash table"<<endl;
            
        }
    }

    void display_without_replacment()
    {
        cout<<"### HASH TABLE ####"<<endl;
        cout<<"\n Srno \tName \tTelephone number "<<endl;
        cout<<"-----------------------------------------"<<endl;
        for(int i=0;i<size;i++)
        {
            cout<<i<<"\t"<<ht[i].name<<"\t"<<ht[i].phno<<endl;
        }
        cout<<"------------------------------------------"<<endl;
    }
};


int main()
{
    int choice;
    bool repeat=true;
    Hash obj;
    do
    {
        cout<<"****MENU*****"<<endl;
        cout<<"1. Insert without replacement"<<endl;
        cout<<"2. Display without replacement"<<endl;
        cout<<"3. Search"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice:";
        cin>>choice;
        switch(choice)
        {
            case 1:
                obj.insert_withoutreplace();
                break;

            case 2:
                obj.display_without_replacment();
                break;

            case 3:
                obj.search();
                break;
            case 4:
                cout<<"Code exit..."<<endl;
                repeat=false;
                break;
            default:
                cout<<"Invalid choice!Please refer the menu"<<endl;
        }
    }while(repeat);
    return 0;
}