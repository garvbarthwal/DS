#include <stdio.h>
#include <stdlib.h>

typedef struct doubleList {
    struct doubleList* previous;
    int data;
    struct doubleList* next;
} dl;

dl* addInFront(dl* head) {
    dl* temp = (dl*)malloc(sizeof(dl));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    int x;
    printf("Enter data: ");
    scanf("%d", &x);
    temp->data = x;

    if (head == NULL) {
        temp->previous = NULL;
        temp->next = NULL;
    } else {
        temp->next = head;
        temp->previous = NULL;
        head->previous = temp;
    }

    head = temp;
    return head;
}

dl* addInLast(dl* head) {
    dl* temp = (dl*)malloc(sizeof(dl));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    int x;
    printf("Enter data: ");
    scanf("%d", &x);
    temp->data = x;
    temp->next = NULL;

    if (head == NULL) {
        temp->previous = NULL;
        head = temp;
        return head;
    }

    dl* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = temp;
    temp->previous = current;

    return head;
}

dl* addInBetween(dl* head) {
    int x, pos, i = 1;
    printf("Enter data: ");
    scanf("%d", &x);

    printf("Enter position after which to insert (1 for after head): ");
    scanf("%d", &pos);

    dl* temp = (dl*)malloc(sizeof(dl));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    temp->data = x;

    if (head == NULL) {
        temp->next = temp->previous = NULL;
        head = temp;
        return head;
    }

    dl* current = head;
    while (current != NULL && i < pos) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Position out of bounds.\n");
        free(temp);
    } else {
        temp->next = current->next;
        temp->previous = current;

        if (current->next != NULL) {
            current->next->previous = temp;
        }
        current->next = temp;
    }

    return head;
}

dl* deleteFromFront(dl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    dl* temp = head;
    head = head->next;

    if (head != NULL) {
        head->previous = NULL;
    }

    free(temp);
    printf("Node deleted from front.\n");

    return head;
}

dl* deleteFromEnd(dl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    dl* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    if (current->previous != NULL) {
        current->previous->next = NULL;
    } else {
        head = NULL; // List becomes empty if we delete the only element
    }

    free(current);
    printf("Node deleted from end.\n");

    return head;
}

dl* deleteFromAnywhere(dl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    int pos, i = 1;
    printf("Enter position to delete: ");
    scanf("%d", &pos);

    dl* current = head;
    while (current != NULL && i < pos) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Position out of bounds.\n");
    } else {
        if (current->previous != NULL) {
            current->previous->next = current->next;
        } else {
            head = current->next;
        }

        if (current->next != NULL) {
            current->next->previous = current->previous;
        }

        free(current);
        printf("Node deleted from position %d.\n", pos);
    }

    return head;
}

void display(dl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    dl* current = head;
    printf("Doubly Linked List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int isPalindrome(dl* head) {
    if (head == NULL) return 1;

    dl* left = head;
    dl* right = head;
    // Find the last node
    while (right->next != NULL) {
        right = right->next;
    }

    while (left != NULL && right != NULL && left != right && left->previous != right) {
        if (left->data != right->data) {
            return 0; // Not a palindrome
        }
        left = left->next;
        right = right->previous;
    }
    return 1; // Is a palindrome
}

dl* reverse(dl* head) {
    if (head == NULL) return NULL;

    dl* temp = NULL;
    dl* current = head;

    while (current != NULL) {
        temp = current->previous;
        current->previous = current->next;
        current->next = temp;
        current = current->previous;
    }

    if (temp != NULL) {
        head = temp->previous; // New head
    }

    return head;
}

void printAlternate(dl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    dl* current = head;
    int count = 0;

    printf("Alternate nodes: ");
    while (current != NULL) {
        if (count % 2 == 0) {
            printf("%d ", current->data);
        }
        count++;
        current = current->next;
    }
    printf("\n");
}

// Merge two sorted lists
dl* merge(dl* left, dl* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->data < right->data) {
        left->next = merge(left->next, right);
        left->next->previous = left;
        left->previous = NULL;
        return left;
    } else {
        right->next = merge(left, right->next);
        right->next->previous = right;
        right->previous = NULL;
        return right;
    }
}

// Merge Sort for Doubly Linked List
dl* mergeSort(dl* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    dl* middle = head;
    dl* fast = head->next;
    
    // Split the list into two halves
    while (fast != NULL && fast->next != NULL) {
        middle = middle->next;
        fast = fast->next->next;
    }

    dl* left = head;
    dl* right = middle->next;
    middle->next = NULL;

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

int main() {
    dl* head = NULL;
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. To add in front\n");
        printf("2. To add at the back\n");
        printf("3. To add in between\n");
        printf("4. To delete from front\n");
        printf("5. To delete from end\n");
        printf("6. To delete from anywhere\n");
        printf("9. To display\n");
        printf("10. To check if the list is palindrome or not\n");
        printf("11. To reverse the list\n");
        printf("12. To print alternate nodes\n");
        printf("13. To sort the list using merge sort\n");
        printf("0. To exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    
        switch (choice) {
            case 1:
                head = addInFront(head);
                break;
            case 2:
                head = addInLast(head);
                break;
            case 3:
                head = addInBetween(head);
                break;
            case 4:
                head = deleteFromFront(head);
                break;
            case 5:
                head = deleteFromEnd(head);
                break;
            case 6:
                head = deleteFromAnywhere(head);
                break;
            case 9:
                display(head);
                break;
            case 10:
                if (isPalindrome(head)) {
                    printf("The list is a palindrome.\n");
                } else {
                    printf("The list is not a palindrome.\n");
                }
                break;
            case 11:
                head = reverse(head);
                printf("The list has been reversed.\n");
                break;
            case 12:
                printAlternate(head);
                break;
            case 13:
                head = mergeSort(head);
                printf("The list has been sorted using merge sort.\n");
                break;
            case 0:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
