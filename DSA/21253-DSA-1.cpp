#include <iostream>
#include <string.h>
#include <iomanip>
#include <conio.h>
using namespace std;

class node
{
    public:
    string word;
    string meaning;
    node *left;
    node *right;

    node()
    {
        left = nullptr;
        right = nullptr;
    }
    friend class BST;
};

class BST
{
    public:
    node *root;
    BST()
    {
        root = NULL;
    }

    void insert(string key, string value)
    {
        node *tempNode;
        tempNode = new node;
        tempNode->word = key;
        tempNode->meaning = value;

        if (root == NULL)
            root = tempNode;
        else
        {
            node *current = root;
            node *parent = NULL;
            while (true)
            {
                parent = current;
                if (key < parent->word)
                {
                    current = current->left;
                    if (current == NULL)
                    {
                        parent->left = tempNode;
                        return;
                    }
                }
                else
                {
                    current = current->right;
                    if (current == NULL)
                    {
                        parent->right = tempNode;
                        return;
                    }
                }
            }
        }
    }

    node *search(string element)
    {
        int cnt=0;
        node *current = root;
        node *parent = NULL;
        while (current->word != element)
        {
            cnt++;
            if (current != NULL)
            {
                if (element < current->word)
                {
                    cnt++;
                    parent = current;
                    current = current->left;
                }
                else
                {
                    cnt++;
                    parent = current;
                    current = current->right;
                }
                if (current == NULL)
                    return NULL;
            }
        }
        cout<<"Number of comparisons done are:"<<cnt<<endl;
        return current;
    }

    void deletion(string element)
    {
        node *parent = NULL;
        node *current = root;
        while (current->word != element)
        {
            if (current != NULL)
            {
                if (element < current->word)
                {
                    parent = current;
                    current = current->left;
                }
                else
                {
                    parent = current;
                    current = current->right;
                }
                if (current == NULL)
                {
                    cout<<"Data Not Found"<<endl;
                    return;
                }
            }
        }

        //both child present
        if(current->left!=NULL && current->right!=NULL)
        {
            node *succ;
            parent=current;
            succ=current->right;
            while (succ->left !=NULL)
            {
                parent=succ;
                succ=succ->left;
            }
            current->word = succ->word;
            current->meaning = succ->meaning;
            current=succ;
        }

        //both child not present
        if(current->left==NULL && current->right==NULL)
        {
            if(current==parent->left)
                parent->left=NULL;
            else
                parent->right=NULL;
            delete current;
        }

        //left child present
        if(current->left!=NULL && current->right==NULL)
        {
            if(current==parent->left)
                parent->left=current->left;
            else
                parent->right=current->left;
            delete current;
        }

        //right child present
        if(current->left==NULL && current->right!=NULL)
        {
            if(current==parent->left)
                parent->left=current->right;
            else
                parent->right=current->right;
            delete current;
        }
    }

    void inorder(node *result)
    {
        if (result == NULL)
            return;
        inorder(result->left);
        cout<<result->word<<"-"<<result->meaning<<endl;
        inorder(result->right);
    }

    void preorder(node *result)
    {
        if (result == NULL)
            return;
        cout<<result->word<<"-"<<result->meaning<<endl;
        preorder(result->left);
        preorder(result->right);
    }

    void postorder(node *result)
    {
        if (result == NULL)
            return;
        postorder(result->left);
        postorder(result->right);
        cout<<result->word<<"-"<<result->meaning<<endl;
    }

    int height(node *result)
    {
        int left,right;
        if(result==NULL)
            return -1;
        left=height(result->left)+1;
        right=height(result->right)+1;
        return max(left,right);
    }

    void minData(node *result)
    {
        if(result==NULL)
            return;
        while(result->left!=NULL)
        {
            result = result->left;
        }
        cout<<"Minimum value is:"<<result->word;
    }

    void maxData(node *result)
    {
        if(result==NULL)
            return;
        while(result->right!=NULL)
        {
            result = result->right;
        }
        cout<<"Minimum value is:"<<result->word;
    }

    void swap(node *result)
    {
        node *ptr=result;
        node *temp;
        if(ptr)
        {
            if(ptr->left || ptr->right)
            {
                temp=ptr->left;
                ptr->left=ptr->right;
                ptr->right=temp;
            }
            swap(ptr->left);
            swap(ptr->right);
        }
    }

    void upDate()
    {
        string key,meaning;
        cout<<"Enter key to update the meaning:";
        cin>>key;
        deletion(key);
        cout<<"Enter new meaning:";
        cin>>meaning;
        insert(key,meaning);
        cout<<"Word Updated"<<endl;
    }
};

int main()
{
    BST obj;
    node *ptr=NULL;

    int choice;
    int choice1;
    bool repeat = true;
    string meaning,key;
    int ht;

    while(repeat)
    {
        cout<<endl;
        cout<<" **** MENU **** "<<endl;
        cout<<" 1. Insert"<<endl;
        cout<<" 2. Display"<<endl;
        cout<<" 3. Search"<<endl;
        cout<<" 4. Delete"<<endl;
        cout<<" 5. Height"<<endl;
        cout<<" 6. Min Value"<<endl;
        cout<<" 7. Max Value"<<endl;
        cout<<" 8. Update key"<<endl;
        cout<<" 9. Swap tree"<<endl;
        cout<<"10. Exit"<<endl;
        cout<<endl;

        cout<<"Enter your choice:";
        cin>>choice;

        switch(choice)
        {
            case 1:
            cout<<"Enter word:";
            cin>>key   ;
            cout<<"Enter meaning:";
            cin>>meaning;
            obj.insert(key,meaning);
            break;

            case 2:
            cout<<"Which order to display:"<<endl;
            cout<<"1.Inorder"<<endl;
            cout<<"2.Preorder"<<endl;
            cout<<"3.Postorder"<<endl;
            cout<<"Enter your choice:";
            cin>>choice1;
            cout<<endl;
            switch(choice1)
            {
                case 1:
                cout<<"*** TREE ***"<<endl;
                obj.inorder(obj.root);
                break;

                case 2:
                cout<<"*** TREE ***"<<endl;
                obj.preorder(obj.root);
                break;

                case 3:
                cout<<"*** TREE ***"<<endl;
                obj.postorder(obj.root);
                break;

                default:
                cout<<"Invalid choice !!"<<endl;
                break;
            }
            break;

            case 3:
            cout<<"Enter word to search:";
            cin>>key;
            ptr=obj.search(key);
            if(ptr!=NULL)
                cout<<"Found"<<endl;
            else
                cout<<"Not Found"<<endl;
            break;

            case 4:
            cout<<"Enter key to delete:";
            cin>>key;
            obj.deletion(key);
            break;

            case 5:
            ht=obj.height(obj.root);
            cout<<"Height of the tree is:"<<ht<<endl;
            break;

            case 6:
            obj.minData(obj.root);
            break;

            case 7:
            obj.maxData(obj.root);
            break;

            case 8:
            obj.upDate();
            break;

            case 9:
            obj.swap(obj.root);
            cout<<"Tree Swapped"<<endl;
            break;

            case 10:
            repeat=false;
            cout<<"Exitting the code"<<endl;
            break;

            default:
            cout<<"Invalid choice"<<endl;
            break;
        }
    }
    getch();
    return 0;
}