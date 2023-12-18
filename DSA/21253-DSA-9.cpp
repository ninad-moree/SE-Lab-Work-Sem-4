#include<iostream>
#include<conio.h>
#include<queue>
using namespace std;

class Node {
    int keys;
    string meaning;
    int height;
    Node *left, *right;
    public:
    Node(int k, string m) {
        keys = k;
        meaning = m;
        height =1;
        left = right = nullptr;
    }
    friend class AVLTree;
};

class AVLTree {
    Node *root = nullptr;

    int height(Node *root) {
        if(root==NULL)
            return 0;
        return root->height;
    }

    int balanceFactor(Node *root) {
        if(root==NULL)
            return 0;
        return height(root->left) - height(root->right);
    }

    int updateHeight(Node *root) {
        root->height = 1 + max(height(root->left) , height(root->right));
    }

    Node *rotateLeft(Node *node) {
        Node *newroot = node->right;
        node->right = newroot->left;
        newroot->left = node;
        updateHeight(node);
        updateHeight(newroot);
        return newroot;
    }

    Node *rotateRight(Node *node) {
        Node *newroot = node->left;
        node->left = newroot->right;
        newroot->right = node;
        updateHeight(node);
        updateHeight(newroot);
        return newroot;
    }

    Node *rotateLeftRight(Node *node) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    Node *rotateRightLeft(Node *node) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    Node *balance(Node *node) {
        if(balanceFactor(node) == 2) {
            if(balanceFactor(node->left) < 0)
                node = rotateLeftRight(node);
            else 
                node = rotateRight(node);
        }
        else if (balanceFactor(node) == -2) {
            if(balanceFactor(node->right) > 0)
                node = rotateRightLeft(node);
            else
                node = rotateLeft(node);
        }
        updateHeight(node);
        return node; 
    }

    Node *insert(Node* node, int keys, string meaning) {
        if(node == NULL){
            node =  new Node(keys, meaning);
            return node;
        }
        if (node->keys > keys)
            node->left = insert(node->left, keys, meaning);
        else if (node->keys < keys)
            node->right = insert(node->right, keys, meaning);
        else {    
            node->keys = keys;
            return node;
        }
        return balance(node);
    }

    bool search(Node *node, int keys) {
        if(node==NULL)
            return false;
        if(node->keys > keys)
            return search(node->left, keys);
        else if(node->keys < keys)
            return search(node->right, keys);
        else    
            return true;
    }

    void inorder(Node *root) {
        if(root==NULL)
            return
        inorder(root->left);
        std::cout<<root->keys<<"-"<<root->meaning<<endl;
        inorder(root->right);
    }

    void levelOder(Node *root) {
        if(root==NULL){
            std::cout<<"Empty Tree"<<endl;
        }
        else{
            queue<Node*> q;
            q.push(root);
            while (!q.empty())
            {
                Node *curr = q.front();
                q.pop();
                std::cout<<curr->keys<<":"<<curr->meaning<<endl;
                if(curr->left != NULL)
                    q.push(curr->left);
                if(curr->right != NULL)
                    q.push(curr->right);
            }
        }  
    }

    public:
    void insertion(int keys, string meaning) {
        root = insert(root, keys, meaning);
    }

    void searching(int keys) {
        bool found = search(root, keys);
        if(found == true){
            std::cout<<"Found"<<endl;
        }
        else{
            std::cout<<"Not"<<endl;
        }
    }

    void inordering(){
        inorder(root);
    }

    void levelOrdering() {
        levelOder(root);
    }
};

int main() {
    AVLTree avl;
    bool repeat = true;
    int choice;
    int key;
    char ans;
    string meaning;
    while(repeat) {
        std::cout<<"MENU"<<endl;
        std::cout<<"1. Insert"<<endl;
        std::cout<<"2. Search"<<endl;
        std::cout<<"3. Inoder"<<endl;
        std::cout<<"4. Level Order"<<endl;
        std::cout<<"5. Exit"<<endl;
        std::cout<<endl;

        std::cout<<"Enter choice :";
        std::cin>>choice;

        switch(choice) {
            case 1:
            do {
                std::cout<<"Enter keys(int):";
                std::cin>>key;
                std::cout<<"Enter meaning(string):";
                std::cin>>meaning;
                avl.insertion(key, meaning);

                std::cout<<"Add more?(y/n)";
                std::cin>>ans;
            }while(ans=='y');
            break;

            case 2:
            std::cout<<"Enter key to search:";
            std::cin>>key;
            avl.searching(key);
            break;

            case 3:
            avl.inordering();
            break;

            case 4:
            avl.levelOrdering();
            break;

            case 5:
            std::cout<<"Exitting"<<endl;
            repeat =false;
            break;

            default:
            std::cout<<"Invalid"<<endl;
            break;
        }
    }
    getch();
    return 0;
}