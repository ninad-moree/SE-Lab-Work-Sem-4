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

    void insert_withreplace(string n, long ph)
    {
        // with replacement
        DataItem ob,ob2;
        int pos,pos1;
        //pos1 stores the hash address of the number already placed in the hash table
        //char ans;
        pos= Hashcode(ph);
        if(ht[pos].phno==0)
        {
            ht[pos].phno=ph;
            ht[pos].name=n;
        }
        else
        {
            if(pos==Hashcode(ht[pos].phno))
            {
                pos1=pos;
                while(ht[pos].link!=-1)
                {
                    pos= ht[pos].link;
                    pos1=pos;
                }
                while(ht[pos].phno!=0)
                {
                    pos=(pos+1)%size;
                }
                ht[pos].name=n;
                ht[pos].phno=ph;
                ht[pos1].link=pos;
            }
            else
            {
                ob2= ht[pos];
                //int add2= Hashcode(ht[pos].phno);
                ht[pos].link=ob2.link;
                ht[pos].phno=ph;
                ht[pos].name=n;
                insert_withreplace(ob2.name,ob2.phno);
            }
        }
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

    void display_withreplacment()
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
        cout<<"1. Insert with replacement"<<endl;
        cout<<"2. Display with replacement"<<endl;
        cout<<"3. Search"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice:";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                char ans;
                string n;
                long ph;
                do
                {
                    cout<<"Enter a name :";
                    cin>>n;
                    cout<<"Enter your mobile number :";
                    cin>>ph;
                    obj.insert_withreplace(n,ph);
                    cout<<"Do you want to continue? (y/n) ";
                    cin>>ans;
                } while(ans=='y'||ans=='Y');
                break;
            }

            case 2:
                obj.display_withreplacment();
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