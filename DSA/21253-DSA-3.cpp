#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    int val;
    node *left, *right;
    bool leftThread, rightThread;

    node()
    {
        left = right = NULL;
        leftThread = rightThread = false;
    }
    node(int v)
    {
        val = v;
        left = right = NULL;
        leftThread = rightThread = false;
    }
};

class ThreadBinarySearchTree
{
public:
    node *root = NULL;

    void insert(int key)
    {
        node *ptr = root;
        node *parent = NULL;
        while (ptr != NULL)
        {
            if (key == ptr->val)
            {
                cout << "Element already exists" << endl;
                return;
            }
            parent = ptr;

            if (key < ptr->val)
            {
                if (ptr->leftThread == false)
                    ptr = ptr->left;
                else
                    break;
            }
            else
            {
                if (ptr->rightThread == false)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        node *temp = new node;
        temp->val = key;
        temp->leftThread = true;
        temp->rightThread = true;

        if (parent == NULL)
        {
            root = temp;
            temp->left = NULL;
            temp->right = NULL;
        }
        else if (key < (parent->val))           // left child insert
        {
            temp->left = parent->left;
            temp->right = parent;
            parent->leftThread = false;
            parent->left = temp;
        }
        else                                    // right child insert
        {
            temp->left = parent;
            temp->right = parent->right;
            parent->rightThread = false;
            parent->right = temp;
        }
    }

    node *inSuccesor(node *ptr)
    {
        if (ptr->rightThread == true)
            return ptr->right;

        ptr = ptr->right;
        while (ptr->leftThread == false)
            ptr = ptr->left;
        return ptr;
    }

    void inorder()
    {
        if (root == NULL)
            cout<<"Tree is empty"<<endl;
       
        node *ptr = root;
        while (ptr->leftThread == false)
            ptr = ptr->left;
        while (ptr != NULL)
        {
            cout<<ptr->val<< " ";
            ptr = inSuccesor(ptr);
        }
    }

    void preorder()
    {
        if(root == NULL)
        {
            cout<<"Tree is empty"<<endl;
            return;
        }
        node *ptr = root;
        while(ptr != NULL)
        {
            cout<<ptr->val<<" ";
            if(ptr->leftThread==false)
                ptr=ptr->left;
            else if(ptr->rightThread==false)
                ptr=ptr->right;
            else
            {
                while(ptr != NULL && ptr->rightThread == true)
                {
                    ptr=ptr->right;
                }
                if(ptr != NULL)
                    ptr = ptr->right;
            }
        }
    }

    node* inPredecessor(node* ptr)
    {
        if (ptr->leftThread == true)
            return ptr->left;
    
        ptr = ptr->left;
        while (ptr->rightThread == false)
            ptr = ptr->right;
        return ptr;
    }
 
    node* caseA(node* root, node* par, node* ptr)
    {
        // If node to be deleted is root
        if (par == NULL)
            root = NULL;
    
        // If Node to be deleted is left of its parent
        else if (ptr == par->left) {
            par->leftThread = true;
            par->left = ptr->left;
        }
        else {
            par->rightThread = true;
            par->right = ptr->right;
        }
    
        // Free memory and return new root
        free(ptr);
        return root;
    }
 
    node* caseB(node* root, node* par, node* ptr)
    {
        node* child;
    
        // Initialize child Node to be deleted has left child.
        if (ptr->leftThread == false)
            child = ptr->left;
    
        // Node to be deleted has right child.
        else
            child = ptr->right;
    
        // Node to be deleted is root Node.
        if (par == NULL)
            root = child;
    
        // Node is left child of its parent.
        else if (ptr == par->left)
            par->left = child;
        else
            par->right = child;
    
        // Find successor and predecessor
        node* s = inSuccesor(ptr);
        node* p = inPredecessor(ptr);
    
        // If ptr has left subtree.
        if (ptr->leftThread == false)
            p->right = s;
    
        // If ptr has right subtree.
        else 
        {
            if (ptr->rightThread == false)
                s->left = p;
        }
    
        free(ptr);
        return root;
    }
 
    node* caseC(node* root, node* par, node* ptr)
    {
        // Find inorder successor and its parent.
         node* parsucc = ptr;
         node* succ = ptr->right;
    
        // Find leftmost child of successor
        while (succ->leftThread==false) {
            parsucc = succ;
            succ = succ->left;
        }
    
        ptr->val = succ->val;
    
        if (succ->leftThread == true && succ->rightThread == true)
            root = caseA(root, parsucc, succ);
        else
            root = caseB(root, parsucc, succ);
    
        return root;
    }

    node *deletenode(int key)
    {
        node *ptr = root;
        node *parent = NULL;
        bool found = 0;

        while(ptr != NULL)
        {
            if(key == ptr->val)
            {
                found=1;
                break;
            }
            parent = ptr;
            if(key < ptr->val)
            {
                if(ptr->leftThread == false)
                    ptr=ptr->left;
                else
                    break;      
            }
            else
            {
                if(ptr->rightThread == false)
                    ptr=ptr->right;
                else
                    break;
            }
        }
        if(found == 0)
            cout<<"Key not found"<<endl;
        else if (ptr->leftThread == false && ptr->rightThread == false)
        root = caseC(root, parent, ptr);
 
        // Only Left Child
        else if (ptr->leftThread == false)
        root = caseB(root, parent, ptr);
 
        // Only Right Child
        else if (ptr->rightThread == false)
        root = caseB(root, parent, ptr);
 
        // No child
        else
        root = caseA(root, parent, ptr);
 
        return root;
    }
};

int main()
{
    ThreadBinarySearchTree tbt;

    int choice;
    int choice1;
    bool repeat = true;
    int data;
    
    while(repeat)
    {
        cout<<endl;
        cout<<" **** MENU **** "<<endl;
        cout<<" 1. Insert"<<endl;
        cout<<" 2. Display"<<endl;
        cout<<" 3. Delete"<<endl;
        cout<<" 4. Exit"<<endl;
        cout<<endl;

        cout<<"Enter your choice:";
        cin>>choice;

        switch(choice)
        {
            case 1:
            cout<<"Enter data to be inserted:";
            cin>>data;
            tbt.insert(data);
            break;

            case 2:
            cout<<"Which order to display:"<<endl;
            cout<<"1.Inorder"<<endl;
            cout<<"2.Preorder"<<endl;
            cout<<"Enter your choice:";
            cin>>choice1;
            cout<<endl;
            switch(choice1)
            {
                case 1:
                cout<<"*** TREE ***"<<endl;
                tbt.inorder();
                break;

                case 2:
                cout<<"*** TREE ***"<<endl;
                tbt.preorder();
                break;

                default:
                cout<<"Invalid choice !!"<<endl;
                break;
            }
            break;

            case 3:
            cout<<"Enter data to delete:";
            cin>>data;
            tbt.deletenode(data);
            break;

            case 4:
            repeat=false;
            cout<<"Exitting the code"<<endl;
            break;

            default:
            cout<<"Invalid choice"<<endl;
            break;
        }
    }
    return 0;
}