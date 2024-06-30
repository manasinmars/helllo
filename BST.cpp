#include <iostream>
#include <queue>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

node* create(node* &root, int d) {
    if (root == NULL) {
        root = new node(d);
        return root;
    }
    if (d < root->data) {
        root->left = create(root->left, d);
    } else {
        root->right = create(root->right, d);
    }
    return root;
}

node* takeinput(node* &root) {
    int data;
    cout << "Enter data: ";
    cin >> data;
    while (data != -1) {
        create(root, data);
        cout << "Enter data: ";
        cin >> data;
    }
    return root;
}

void levelorder(node* root) {
    if (root == NULL) {
        return;
    }
    
    queue<node*> q;
    q.push(root);
    q.push(NULL); // Level separator

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        if (temp == NULL) {
            cout << endl;
            if (!q.empty()) {
                q.push(NULL);
            }
        } else {
            cout << temp->data << " ";
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
    }
}

void inorder(node* root){
    //base case
    if(root == NULL){
        return;
    }
    //L
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(node* root){
    //base case
    if(root == NULL){
        return;
    }
    
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(node* root){
    //base case
    if(root == NULL){
        return;
    }
    //L
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

node* minval(node* &root){
    node* temp = root;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

node* maxval(node* &root){
    node* temp = root;
    while(temp->right != NULL){
        temp = temp->right;
    }
    return temp;
}

node* deletebst(node* &root, int val){
    if(root == NULL){
        return root;
    }

    if(root->data == val){
        // 0 child
        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        }
        // 1 child or subtree in left and right is NULL
        if(root->left != NULL && root->right == NULL){
            node* temp = root->left;
            delete root;
            return temp;
        }
        //1 child or subtree in right and there is no child on left
        if(root->left == NULL && root->right != nullptr){
            node* temp = root->right;
            delete root;
            return temp;
        }
        // 2 child or subtree present
        if(root->left != NULL && root->right != NULL){
            //replace root with minimun value present in right subtree then delte this minimum value
            int mini = minval(root->right)->data;
            root->data = mini;
            root->right = deletebst(root->right,mini);
            return root;
        }
    }
    if(root->data < val ){
        root->right = deletebst(root->right,val);
        return root;
    } else{
        root->left = deletebst(root->left,val);
        return root;
    }
}

int main() {
    node* root = NULL;
    cout << "Take input of the BST: "; 
    root = takeinput(root);
    cout << "Printing the BST level order:" << endl;
    levelorder(root);
    cout <<" inorder traversal is :";
    inorder(root);
    cout << endl;
    cout<< "preoder traversal is :";
    preorder(root);
    cout<< endl;
    cout<<"postorder travversal is :";
    postorder(root);

    return 0;
}
