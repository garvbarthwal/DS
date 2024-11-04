#include <stdio.h>
#include <stdlib.h>

typedef struct singleList {
    int data;
    struct singleList* next;
} sl;

// Function to add a node in front
sl* addInFront(sl* head) {
    int x;
    sl* temp = (sl*)malloc(sizeof(sl));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    printf("Enter data for the node: ");
    scanf("%d", &x);
    temp->data = x;

    temp->next = head;
    return temp;
}

// Function to add a node at the end
sl* addInLast(sl* head) {
    int x;
    sl* temp = (sl*)malloc(sizeof(sl));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    printf("Enter data for the node: ");
    scanf("%d", &x);
    temp->data = x;
    temp->next = NULL;

    if (head == NULL) {
        return temp;
    }

    sl* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = temp;
    return head;
}

// Function to add a node at a specified position
sl* addInBetween(sl* head) {
    int x, pos;
    sl* temp = (sl*)malloc(sizeof(sl));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    printf("Enter the position to insert at (0 for front): ");
    scanf("%d", &pos);

    if (pos < 0) {
        printf("Invalid position.\n");
        free(temp);
        return head;
    }

    printf("Enter data for the node: ");
    scanf("%d", &x);
    temp->data = x;

    if (pos == 0) {
        temp->next = head;
        return temp;
    }

    sl* current = head;
    for (int i = 0; i < pos - 1; i++) {
        if (current == NULL) {
            printf("Position exceeds list length.\n");
            free(temp);
            return head;
        }
        current = current->next;
    }

    temp->next = current->next;
    current->next = temp;
    return head;
}

// Function to delete a node from the front
sl* deleteFromFront(sl* head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return head;
    }

    sl* temp = head; 
    head = head->next; 
    free(temp); 
    return head; 
}

// Function to delete a node from the end
sl* deleteFromEnd(sl* head) {
    if (head == NULL) {
        printf("Nothing to delete from the existing list.\n");
        return head;
    }
    if (head->next == NULL) {  
        free(head);  
        return NULL; 
    }

    sl *current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    free(current->next);
    current->next = NULL;
    return head;
}

// Function to delete a node from a specified position
sl* deleteFromAnywhere(sl* head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return head;
    }

    int pos;
    printf("Enter the position to delete (0 for head): ");
    scanf("%d", &pos);

    if (pos < 0) {
        printf("Invalid position.\n");
        return head;
    }

    if (pos == 0) {  
        sl* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    sl* current = head;
    for (int i = 0; i < pos - 1; i++) {
        if (current == NULL || current->next == NULL) {
            printf("Position exceeds list length.\n");
            return head;
        }
        current = current->next;
    }

    sl* temp = current->next;
    if (temp == NULL) {
        printf("Position exceeds list length.\n");
        return head;
    }

    current->next = temp->next;  
    free(temp);  
    return head;
}

// Function to display the linked list
void display(sl* head) {
    sl* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to check if the linked list is a palindrome
int isPalindrome(sl* head) {
    if (head == NULL) return 1;

    // Use slow and fast pointers to find the middle
    sl* slow = head;
    sl* fast = head;
    sl* prev = NULL;

    // Reverse the first half of the list while finding the middle
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;

        // Reverse the first half of the list
        sl* next = slow->next;
        slow->next = prev;
        prev = slow;
        slow = next;
    }

    // If the list has odd number of elements, skip the middle element
    if (fast != NULL) {
        slow = slow->next;
    }

    // Compare the two halves
    while (prev != NULL && slow != NULL) {
        if (prev->data != slow->data) {
            return 0; // Not a palindrome
        }
        prev = prev->next;
        slow = slow->next;
    }
    return 1; // Is a palindrome
}

// Function to reverse the linked list
sl* reverse(sl* head) {
    sl* prev = NULL;
    sl* current = head;
    sl* next = NULL;

    while (current != NULL) {
        next = current->next; // Store next node
        current->next = prev; // Reverse current node's pointer
        prev = current;       // Move pointers one position ahead
        current = next;
    }
    return prev; // New head of the reversed list
}

// Function to print alternate nodes
void printAlternate(sl* head) {
    sl* current = head;
    printf("Alternate Nodes: ");
    while (current != NULL) {
        printf("%d ", current->data);
        if (current->next != NULL) {
            current = current->next->next; // Move to the next alternate node
        } else {
            break;
        }
    }
    printf("\n");
}

int main() {
    sl* head = NULL;
    int choice;

    while (1) {
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
            case 0:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
