#include <iostream>
#include <queue>
#include <stack>
#include <conio.h>
using namespace std;

class Node 
{
    public:
    int data;
    Node* left;
    Node* right;

    friend class BT;
};

class BT
{
    public:
    Node* createNode(int data) 
    {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    void insert(Node* &root, int data) 
    {
        Node* newNode = createNode(data);
        if (root == NULL) 
        {
            root = newNode;
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) 
        {
            Node* current = q.front();
            q.pop();
            if (current->left == NULL) 
            {
                current->left = newNode;
                break;
            }
            else 
            {
                q.push(current->left);
            }
            if (current->right == NULL) 
            {
                current->right = newNode;
                break;
            }
            else 
            {
                q.push(current->right);
            }
        }
    }

    void inorder(Node* root) 
    {
        stack<Node*> s;
        Node* current = root;
        
        while (current != NULL || !s.empty()) 
        {
            while (current != NULL) 
            {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();
            cout << current->data << " ";
            current = current->right;
        }
    }

    void preorder(Node* root)
    {
        if (root == nullptr)
        return;

        stack<Node*> stack;
        stack.push(root);

        while (!stack.empty())
        {
            Node* curr = stack.top();
            stack.pop();
    
            cout << curr->data << " ";
            if (curr->right) 
            {
                stack.push(curr->right);
            }
            if (curr->left) 
            {
                stack.push(curr->left);
            }
        }
    }

    void postorder(Node* root)
    {
        if (root == nullptr) {
            return;
        }
    
        stack<Node*> s;
        s.push(root);
        stack<int> out;
    
        while (!s.empty())
        {
            Node* curr = s.top();
            s.pop();
    
            out.push(curr->data);
            if (curr->left) {
                s.push(curr->left);
            }
    
            if (curr->right) {
                s.push(curr->right);
            }
        }
        
        while (!out.empty())
        {
            cout << out.top() << " ";
            out.pop();
        }
    }

    int height(Node* root)
    {
        queue<Node*> q;
        int height = 0;
        int nodeCount = 0; 
        Node* currentNode; 

        if (root == NULL)
            return 0;

        q.push(root);
        while (!q.empty()) 
        {
            height++;
            nodeCount = q.size();
            while (nodeCount--) 
            {
                currentNode = q.front();
                if (currentNode->left != NULL) 
                    q.push(currentNode->left);

                if (currentNode->right != NULL)
                    q.push(currentNode->right);
                q.pop();
            }
        }
        return height;
    }

    void swapBinaryTree(Node* root) 
    {
        if (root == nullptr)
            return;

        stack<Node*> s;
        s.push(root);

        while (!s.empty()) 
        {
            Node* curr = s.top();
            s.pop();

            Node* temp = curr->left;
            curr->left = curr->right;
            curr->right = temp;

            if (curr->left != nullptr)
                s.push(curr->left);

            if (curr->right != nullptr)
                s.push(curr->right);
        }
    }

    void countLeavesAndInternalNodes(Node* root) 
    {
        int leaves=0;
        if (root == nullptr)
            return;

        stack<Node*> s;
        s.push(root);

        int count = 0;

        while (!s.empty()) 
        {
            Node* curr = s.top();
            s.pop();

            if (curr->left == nullptr && curr->right == nullptr) 
                ++leaves;
            else 
            {
                ++count;
                if (curr->right != nullptr)
                    s.push(curr->right);

                if (curr->left != nullptr)
                    s.push(curr->left);
            }
        }
        cout<<"Leaves:"<<leaves<<endl;
        cout<<"Nodes:"<<count<<endl;
    }

    void deleteTree(Node* root)
    {
        if(root == NULL) return;

        deleteTree(root->left);
        deleteTree(root->right);
        cout<<"Deleting node:"<<root->data<<endl;
        delete root;
    }

    void eraseTree(Node* root) 
    {
        if (root == nullptr)
            return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) 
        {
            Node* curr = q.front();
            q.pop();

            if (curr->left != nullptr)
                q.push(curr->left);

            if (curr->right != nullptr)
                q.push(curr->right);

            delete curr;
        }
    }
 
};


int main() 
{
    BT obj;
    Node* root = NULL;

    int key;
    int choice;
    int choice1;
    bool repeat = true;
    int ht;

    while(repeat)
    {
        cout<<endl;
        cout<<" **** MENU **** "<<endl;
        cout<<" 1. Insert"<<endl;
        cout<<" 2. Display"<<endl;
        cout<<" 3. Height"<<endl;
        cout<<" 4. Swap tree"<<endl;
        cout<<" 5. Count leaves and nodes"<<endl;
        cout<<" 6. Erase tree"<<endl;
        cout<<" 7. Exit"<<endl;
        cout<<endl;

        cout<<"Enter your choice:";
        cin>>choice;

        switch(choice)
        {
            case 1:
            cout<<"Enter number:";
            cin>>key;
            obj.insert(root,key);
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
                obj.inorder(root);
                break;

                case 2:
                cout<<"*** TREE ***"<<endl;
                obj.preorder(root);
                break;

                case 3:
                cout<<"*** TREE ***"<<endl;
                obj.postorder(root);
                break;

                default:
                cout<<"Invalid choice !!"<<endl;
                break;
            }
            break;

            case 3:
            ht=obj.height(root);
            cout<<"Height of the tree is:"<<ht<<endl;
            break;

            case 4:
            obj.swapBinaryTree(root);
            cout<<"Tree Swapped"<<endl;
            break;

            case 5:
            obj.countLeavesAndInternalNodes(root);
            break;

            case 6:
            obj.eraseTree(root);
            cout<<"Tree Deleted"<<endl;
            break;

            case 7:
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