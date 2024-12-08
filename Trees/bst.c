#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct binarySearchTree {
    struct binarySearchTree *left;
    int data;
    struct binarySearchTree *right;
} bst;

void insert(bst** root, int d);
bst* inorder_successor(bst* root);
void delete(bst** root, int del);
bst* find_min(bst* root);
bst* find_max(bst* root);
bst* search(bst* root, int value);
void inorder(bst* root);
void preorder(bst* root);
void postorder(bst* root);
void kth_smallest(bst* root, int k, int* count);
void nodes_with_common_parent(bst* root, int* count);
void print_paths(bst* root, int path[], int path_len);
bst* find_lca(bst* root, int n1, int n2);
void level_order(bst* root);
void print_nodes_at_level(bst* root, int level);
void count_total_nodes(bst* root, int* count);
void count_leaf_nodes(bst* root, int* count);
void count_nodes_with_common_parent(bst* root, int* count);
int check_prime(int data);
void print_prime(bst* root);
int height(bst* root);
int is_balanced(bst* root);
int diameter(bst* root, int* diam);

void insert(bst** root, int d) {
    
    if (*root == NULL) {
        bst* temp;
        temp = (bst*)malloc(sizeof(bst));
        if (temp == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
        temp->data = d;
        temp->left = NULL;
        temp->right = NULL;
        *root = temp;
    } else if ((*root)->data > d) {
        insert(&(*root)->left, d);
    } else if ((*root)->data < d) {
        insert(&(*root)->right, d);
    }
}

bst* inorder_successor(bst* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

void delete(bst** root, int del) {
    if (*root == NULL) {
        printf("Tree is empty. Nothing to delete\n");
        return;
    }

    if ((*root)->data == del) {
        bst* temp;
        if ((*root)->left == NULL && (*root)->right == NULL) {
            temp = *root;
            *root = NULL;
            free(temp);
        } else if ((*root)->left == NULL) {
            temp = *root;
            *root = (*root)->right;
            free(temp);
        } else if ((*root)->right == NULL) {
            temp = *root;
            *root = (*root)->left;
            free(temp);
        } else {
            bst* successor = inorder_successor((*root)->right);
            (*root)->data = successor->data;
            delete(&((*root)->right), successor->data);
        }
    } else if ((*root)->data > del) {
        delete(&(*root)->left, del);
    } else {
        delete(&(*root)->right, del);
    }
}

bst* find_min(bst* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

bst* find_max(bst* root) {
    while (root && root->right != NULL) {
        root = root->right;
    }
    return root;
}

bst* search(bst* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }
    if (root->data > value) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

void inorder(bst* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(bst* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(bst* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void kth_smallest(bst* root, int k, int* count) {
    if (root == NULL || *count >= k) return;

    kth_smallest(root->left, k, count);
    (*count)++;
    if (*count == k) {
        printf("The %dth smallest element is: %d\n", k, root->data);
        return;
    }
    kth_smallest(root->right, k, count);
}

void nodes_with_common_parent(bst* root, int* count) {
    if (root == NULL) return;
    if (root->left != NULL && root->right != NULL) {
        (*count)++;
    }
    nodes_with_common_parent(root->left, count);
    nodes_with_common_parent(root->right, count);
}

void print_paths(bst* root, int path[], int path_len) {
    if (root == NULL) return;

    path[path_len] = root->data;
    path_len++;

    if (root->left == NULL && root->right == NULL) {
        for (int i = 0; i < path_len; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        print_paths(root->left, path, path_len);
        print_paths(root->right, path, path_len);
    }
}

bst* find_lca(bst* root, int n1, int n2) {
    if (root == NULL) return NULL;

    if (root->data > n1 && root->data > n2) {
        return find_lca(root->left, n1, n2);
    }
    if (root->data < n1 && root->data < n2) {
        return find_lca(root->right, n1, n2);
    }
    return root;
}

void level_order(bst* root) {
    if (root == NULL) return;

    // Create a queue for level-order traversal
    bst* queue[1000];
    int front = 0, rear = 0;

    // Enqueue root
    queue[rear++] = root;

    while (front < rear) {
        // Dequeue and process the node
        bst* node = queue[front++];
        printf("%d ", node->data);

        // Enqueue left and right children if present
        if (node->left != NULL) {
            queue[rear++] = node->left;
        }
        if (node->right != NULL) {
            queue[rear++] = node->right;
        }
    }
    printf("\n");
}

void print_nodes_at_level(bst* root, int level) {
    if (root == NULL) return;
    if (level == 0) {
        printf("%d ", root->data);
    } else {
        print_nodes_at_level(root->left, level - 1);
        print_nodes_at_level(root->right, level - 1);
    }
}

void count_total_nodes(bst* root, int* count) {
    if (root == NULL) return;
    (*count)++;
    count_total_nodes(root->left, count);
    count_total_nodes(root->right, count);
}

void count_leaf_nodes(bst* root, int* count) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        (*count)++;
    }
    count_leaf_nodes(root->left, count);
    count_leaf_nodes(root->right, count);
}

void count_nodes_with_common_parent(bst* root, int* count) {
    if (root == NULL) return;
    if (root->left != NULL && root->right != NULL) {
        (*count) += 1;
    }
    count_nodes_with_common_parent(root->left, count);
    count_nodes_with_common_parent(root->right, count);
}

int check_prime(int data) {
    if (data <= 1) return 0;
    for (int i = 2; i <= sqrt(data); i++) {
        if (data % i == 0) {
            return 0;
        }
    }
    return 1;
}

void print_prime(bst* root) {
    if (root == NULL) return;
    if (check_prime(root->data)) {
        printf("%d ", root->data);
    }
    print_prime(root->left);
    print_prime(root->right);
}

int height(bst* root) {
    if (root == NULL) return 0;
    int left_height = height(root->left);
    int right_height = height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

int is_balanced(bst* root) {
    if (root == NULL) return 1;
    int left_height = height(root->left);
    int right_height = height(root->right);
    return abs(left_height - right_height) <= 1 && is_balanced(root->left) && is_balanced(root->right);
}

int diameter(bst* root, int* diam) {
    if (root == NULL) return 0;

    int left_diameter = diameter(root->left, diam);
    int right_diameter = diameter(root->right, diam);

    int height_left = height(root->left);
    int height_right = height(root->right);

    int local_diameter = height_left + height_right + 1;
    if (local_diameter > *diam) {
        *diam = local_diameter;
    }

    return (height_left > height_right ? height_left : height_right) + 1;
}

int main() {
    bst* root = NULL;
    int choice, val, k, count, diam = 0, level;
    do {
        printf("1. To Insert\n2. To Delete\n3. To Search for a node\n4. To Display BST (Inorder/Preorder/Postorder)\n5. To Find Minimum Value\n6. To Find Maximum Value\n7. To Check if BST is Balanced\n8. To Find Lowest Common Ancestor\n9. To Find Kth Smallest Element\n10. To Count Nodes with Common Parent\n11. To Calculate Diameter\n12. To Display All Root-to-Leaf Paths\n13. To Print Prime Numbers in BST\n14. To Count Total Nodes\n15. To Perform Level-Order Traversal\n16. To Find Nodes at a Given Level\n17. To Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &val);
            insert(&root, val);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &val);
            delete(&root, val);
            break;
        case 3:
            printf("Enter value to search: ");
            scanf("%d", &val);
            bst* search_result = search(root, val);
            if (search_result != NULL)
                printf("Found value %d\n", val);
            else
                printf("Value %d not found\n", val);
            break;
        case 4:
            printf("Inorder: ");
            inorder(root);
            printf("\nPreorder: ");
            preorder(root);
            printf("\nPostorder: ");
            postorder(root);
            printf("\n");
            break;
        case 5:
            bst* min = find_min(root);
            if (min != NULL) printf("Minimum Value: %d\n", min->data);
            break;
        case 6:
            bst* max = find_max(root);
            if (max != NULL) printf("Maximum Value: %d\n", max->data);
            break;
        case 7:
            if (is_balanced(root)) {
                printf("The tree is balanced\n");
            } else {
                printf("The tree is not balanced\n");
            }
            break;
        case 8:
            printf("Enter two values for LCA: ");
            int n1, n2;
            scanf("%d %d", &n1, &n2);
            bst* lca = find_lca(root, n1, n2);
            if (lca != NULL)
                printf("LCA of %d and %d is: %d\n", n1, n2, lca->data);
            else
                printf("LCA not found\n");
            break;
        case 9:
            printf("Enter k: ");
            scanf("%d", &k);
            int count = 0;
            kth_smallest(root, k, &count);
            break;
        case 10:
            count = 0;
            nodes_with_common_parent(root, &count);
            printf("Number of nodes with a common parent: %d\n", count);
            break;
        case 11:
            diameter(root, &diam);
            printf("Diameter of the tree is: %d\n", diam);
            break;
        case 12:
            int path[1000];
            print_paths(root, path, 0);
            break;
        case 13:
            print_prime(root);
            printf("\n");
            break;
        case 14:
            count = 0;
            count_total_nodes(root, &count);
            printf("Total nodes: %d\n", count);
            break;
        case 15:
            level_order(root);
            break;
        case 16:
            printf("Enter level: ");
            scanf("%d", &level);
            print_nodes_at_level(root, level);
            printf("\n");
            break;
        case 17:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 17);
    return 0;
}
