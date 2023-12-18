#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

class Node 
{
    string key;
    string value;
    Node *next = nullptr;

    friend class Dictionary;
};

class Dictionary 
{
    Node **table;
    int tableSize;

    int hash(string value)
    {
        int v= (int)value[0];
        return v%10;
    }

    Node *insertLL(Node *headNode, string key, string value) 
    {
        Node *currentNode = headNode;
        while(currentNode->next != nullptr)
            currentNode = currentNode->next;

        Node *newNode = new (Node);
        newNode->key = key;
        newNode->value = value;
        currentNode->next = newNode;
    }

    Node* findLL (Node *headNode, string key)
    {
        int flag=0;
        Node *currentNode = headNode;
        while( currentNode != nullptr )
        {
            if( currentNode->key == key )
            {
                flag=1;
                break;

            }
            currentNode = currentNode->next;
        }
        if(flag==1)
            return currentNode;
        else
            return nullptr;
    }

    void printLL( Node* headNode ) 
    {
        Node* currentNode = headNode;
        while( currentNode != nullptr ) 
        {
            cout << currentNode -> key << " " << currentNode -> value << ",\t" ;
            currentNode = currentNode -> next ;
        }
    }

    void deleteLL( int index, Node* headNode, string key ) 
    {
        if( headNode->key == key ) 
        {
            Node *nextNode = headNode->next;
            delete table[ index ];
            table[ index ] = nextNode;
        }

        else 
        {
            Node *currentNode = headNode;
            Node *prevNode = nullptr;
            while( currentNode->next == nullptr ) 
            {
                if( currentNode->key == key )
                    break;
                prevNode = currentNode;
                currentNode = currentNode->next;
            }
            prevNode->next = currentNode->next;
            delete currentNode;
            cout<<"Node Deleted"<<endl;
        }
    }

    public:
    Dictionary ( int n ) 
    {
        this->tableSize = n;
        table = new Node*[tableSize];
        for( int i = 0; i < tableSize; i++ ) 
        {
            table[i] = nullptr;
        }
    }

    void insert( string key, string value ) 
    {
        int hashAddress = hash(key);
        if( table[hashAddress] == nullptr) 
        {
            Node *newNode = new ( Node );
            newNode->key = key;
            newNode->value = value;
            table[hashAddress] = newNode;
        }

        else 
            insertLL(table[hashAddress], key, value);
    }

    void display()
    {
        for( int i = 0; i < tableSize; i++ ) 
        {
            cout<<i<<" ";
            printLL( table[i] );
            cout<<endl;
        }
    }

    void search (string key)
    {
        int hashAddress = hash(key);
        Node *foundNode = findLL(table[hashAddress], key);
        if( foundNode == nullptr )
            cout<<"No record found!"<<endl;
        else 
        {
            cout<<"Record Found"<<endl;
            cout<<"\nKey: "<<key<<endl;
            cout<<"Value: "<<foundNode->value<<endl;
        }
    }

    void del( string key ) 
    {
        int hashAddress = hash(key);
        deleteLL( hashAddress, table[ hashAddress ], key);
        cout<<"Key successfully deleted"<<endl;
    }
};

int main()
{
    Dictionary dict(10);
    bool repeat=true;
    int choice;
    while(repeat)
    {
        cout<<"******MENU******"<<endl;
        cout<<"1. Insert"<<endl;
        cout<<"2. Display"<<endl;
        cout<<"3. Find"<<endl;
        cout<<"4. Delete"<<endl;
        cout<<"5. EXIT"<<endl;
        cout<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
            case 1:
            {
                string key,value;
                cout<<"Enter a key: ";
                cin>>key;
                cout<<"Enter its value: ";
                cin>>value;
                dict.insert(key, value);
                break;
            }

            case 2:
            {
                dict.display();
                break;
            }

            case 3:
            {
                string key;
                cout<<"Enter key to search: ";
                cin>>key;
                dict.search(key);
                break;
            }

            case 4:
            {
                string key;
                cout<<"Enter key to delete: ";
                cin>>key;
                dict.del(key);
                break;
            }

            case 5:
            {
                cout<<"Program Ended!"<<endl;
                repeat=false;
                break;
            }
        }
    }
    return 0;
}