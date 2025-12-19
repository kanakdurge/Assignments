#include <iostream>
using namespace std;


struct Node {
    int bookID;
    Node* left;
    Node* right;
};


Node* createNode(int id) {
    Node* newNode = new Node;
    newNode->bookID = id;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


Node* insert(Node* root, int id) {
    if (root == NULL)
        return createNode(id);

    if (id < root->bookID)
        root->left = insert(root->left, id);
    else if (id > root->bookID)
        root->right = insert(root->right, id);

    return root;
}


bool search(Node* root, int id) {
    if (root == NULL)
        return false;

    if (root->bookID == id)
        return true;
    else if (id < root->bookID)
        return search(root->left, id);
    else
        return search(root->right, id);
}


void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->bookID << " ";
    inorder(root->right);
}

void freeTree(Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}


int main() {
    Node* root = NULL;
    int choice, id;

    do {
        cout << "\n===== Smart Book Tracking System =====\n";
        cout << "1. Return Book (Store Book ID)\n";
        cout << "2. Check Book ID\n";
        cout << "3. Display Returned Book IDs (Ascending Order)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                root = insert(root, id);
                cout << "Book ID stored successfully.\n";
                break;

            case 2:
                cout << "Enter Book ID to check: ";
                cin >> id;
                if (search(root, id))
                    cout << "Book ID has been returned.\n";
                else
                    cout << "Book ID not found.\n";
                break;

            case 3:
                cout << "Returned Book IDs (Ascending Order): ";
                inorder(root);
                cout << endl;
                break;

            case 4:
                freeTree(root);
                cout << "System closed successfully.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
