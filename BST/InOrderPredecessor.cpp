#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *left, *right;
};
 
//Function which creates a new BST having a given key
Node* newNode(int key){
    Node* node = new Node;
    node->data = key;
    node->left = node->right = nullptr;

    return node;
}

///Recursive Function to insert a key into BST
Node* insert(Node* root, int key){
    ///If root is nullptr, create a new root and return it
    if(root == nullptr){
        return newNode(key);
    }

    ///If key is less than the root node, recur for the left subtree
    if(key < root->data){
        root->left = insert(root->left, key);
    }

    ///If key is more than the root node, recur for the right subtree
    else{
        root->right = insert(root->right, key);
    }

    return root;
}

///Helper Function to find max value node in BST
Node* findMaximum(Node* root){
    while(root->right){
        root = root->right;
    }
    return root;
}

///Recursive Function to find inOrder Predecessor for a given key in BST
///Note the predecessor 'prec' is passed by reference to the function
void findPredecessor(Node *root, Node* &prec, int key){
    ///base case
    if(root == nullptr){
        prec = nullptr;
        return;
    }

    ///if the node with key's value is found, the predecessor is max value node in its left subtree(if any)
    if(root->data == key){
        if(root->left){
            prec = findMaximum(root->left);
        }
    }
   
    ///If the given key is less than the root node , recur for the left subtree
    else if(key < root->data){
        findPredecessor(root->left, prec, key);
    }

    ///if the key is more than the root node, recur for the right subtree
    else{
        ///Update predecessor to current node before recursing in right subtree
        prec = root;
        findPredecessor(root->right, prec, key);
    }
}

int main(){
    /** Contruct this tree
             *          15
             *        /   \
             *      /      \
             *    10       20
                /   \     /   \
              /      \   16    25
      *      8       12   
    */

   int keys[] = {15, 10, 20, 8, 12, 16, 25};

   Node *root = nullptr;

   for(int key:keys){
       insert(root, key);
   }

   for(int key:keys){
       Node *prec = nullptr;
       findPredecessor(root, prec, key);

       if(prec != nullptr){
           cout << "Predeccessor of node" << key << " is " << prec->data << endl;
       }
       else{
           cout << "Predeccessor for" << key << " does'nt exist" << endl;
       }
   }

   return 0;
}