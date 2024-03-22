#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *left, *right;
}Node;

struct Node* new_node(int item){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

    temp -> data = item;
    temp -> left = temp -> right = NULL;

    return temp;
}

struct Node* insert(struct Node* node, int data){
    if(node == NULL) return new_node(data);

    if(data < node -> data)
        node -> left = insert(node -> left, data);

    else if(data > node -> data)
        node -> right = insert(node -> right, data); 
    
    return node;
}

struct Node* min_value_node(struct Node* node){
    struct Node* current = node;

    while(current && current -> left != NULL)
        current = current -> left;

    return current;

}

struct Node* delete_node(struct Node* root, int data){
    if(root == NULL) return root;

    if(data < root -> data)
        root -> left = delete_node(root -> left, data);
    
    else if(data > root -> data)
        root -> right = delete_node(root -> right, data);
    
    else{
        //Node with only one child or no child
        if(root -> left == NULL){
            struct Node* temp = root -> right;
            free(root);
            return temp;  

        }else if(root -> right == NULL){
            struct Node* temp = root -> left;
            free(root);
            return temp;
        }

        struct Node* temp = min_value_node(root -> right);

        root -> data = temp -> data;

        root -> right = delete_node(root -> right, temp -> data);
    }
    return root;

}

int height(struct Node* node){
    if(node == NULL)
        return -1;
    else{
        int left_height = height(node -> left);
        int right_height = height(node -> right);

        if(left_height > right_height)
            return(left_height + 1);
        else
            return(right_height + 1);
    }
}

void print_level_and_height(struct Node* root, int data){
    struct Node* current = root;
    int level = -1;
    while (current != NULL) {
        if (current-> data == data) {
            printf("Node %d is at level %d and its height is %d.\n", data, level, height(current));
            return;
        } else if (data < current -> data) {
            current = current->left;
        } else {
            current = current->right;
        }
        level++;
    }
    printf("Node not found in the BST.\n");
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root -> left);
        printf("%d ", root -> data);
        inorder(root -> right);
    }
}

int main() {
    int bst_array[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(bst_array) / sizeof(bst_array[0]);
    struct Node* root = NULL;

    // Create the BST
    for (int i = 0; i < n; i++) {
        root = insert(root, bst_array[i]);
    }

    // Print in order traversal of the BST
    printf("Inorder traversal of the created BST: ");
    inorder(root);
    printf("\n");

    printf("Height of the BST: %d\n", height(root));

    // Delete a node
    // Change this key to test deletion of other nodes
    root = delete_node(root, 20);
    printf("Inorder traversal after deletion of 20: ");
    inorder(root);
    printf("\n");

    // Print the height of the BST
    printf("Height of the BST: %d\n", height(root));

    // Print the level and height of a node
    // Change this key to test with different nodes
    print_level_and_height(root, 35);

    return 0;
}
