#include <iostream>

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
                std::cout << "Element already exists" << std::endl;
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

        node *temp = new node(key);
        temp->leftThread = true;
        temp->rightThread = true;

        if (parent == NULL)
        {
            root = temp;
            temp->left = NULL;
            temp->right = NULL;
        }
        else if (key < parent->val) // left child insert
        {
            temp->left = parent->left;
            temp->right = parent;
            parent->leftThread = false;
            parent->left = temp;
        }
        else // right child insert
        {
            temp->left = parent;
            temp->right = parent->right;
            parent->rightThread = false;
            parent->right = temp;
        }
    }

    node *inSuccessor(node *ptr)
    {
        if (ptr->rightThread)
            return ptr->right;

        ptr = ptr->right;
        while (ptr->leftThread == false)
            ptr = ptr->left;
        return ptr;
    }

    void inorder()
    {
        if (root == NULL)
        {
            std::cout << "Tree is empty" << std::endl;
            return;
        }

        node *ptr = root;
        while (ptr->leftThread == false)
            ptr = ptr->left;

        while (ptr != NULL)
        {
            std::cout << ptr->val << " ";
            ptr = inSuccessor(ptr);
        }
        std::cout << std::endl;
    }

    node *caseA(node *root, node *par, node *ptr)
    {
        if (par == NULL)
            root = NULL;
        else if (ptr == par->left)
        {
            par->leftThread = true;
            par->left = ptr->left;
        }
        else
        {
            par->rightThread = true;
            par->right = ptr->right;
        }

        delete ptr;
        return root;
    }

    node *deletenode(int key)
    {
        node *ptr = root;
        node *parent = NULL;
        bool found = false;

        while (ptr != NULL)
        {
            if (key == ptr->val)
            {
                found = true;
                break;
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

        if (!found)
        {
            std::cout << "Key not found" << std::endl;
            return root;
        }

        if (ptr->leftThread == true && ptr->rightThread == true)
        {
            if (ptr->left != NULL || ptr->right != NULL)
            {
                std::cout << "Cannot delete non-leaf node" << std::endl;
                return root;
            }

            root = caseA(root, parent, ptr);
            return root;
        }
        else
        {
            std::cout << "Cannot delete non-leaf node" << std::endl;
            return root;
        }
    }


};

int main()
{
    ThreadBinarySearchTree tbt;

    int choice;
    int data;
    bool repeat = true;

    while (repeat)
    {
        std::cout << "**** MENU ****" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Insert" << std::endl;
        std::cout << "2. Display" << std::endl;
        std::cout << "3. Delete" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter data to be inserted: ";
            std::cin >> data;
            tbt.insert(data);
            break;

        case 2:
            std::cout << "*** TREE ***" << std::endl;
            tbt.inorder();
            break;

        case 3:
            std::cout << "Enter data to delete: ";
            std::cin >> data;
            tbt.deletenode(data);
            break;

        case 4:
            repeat = false;
            std::cout << "Exiting the code" << std::endl;
            break;

        default:
            std::cout << "Invalid choice" << std::endl;
            break;
        }
    }

    return 0;
}


