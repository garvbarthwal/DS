#include <stdio.h>
#include <stdlib.h>

typedef struct circularList {
    int data;
    struct circularList* next;
} cl;

cl* addInFront(cl* head) {
    cl* temp = (cl*)malloc(sizeof(cl));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    int x;
    printf("Enter data: ");
    scanf("%d", &x);
    temp->data = x;

    if (head == NULL) {
        temp->next = temp; // Points to itself, making it circular
        head = temp;
    } else {
        cl* last = head;
        while (last->next != head) {
            last = last->next;
        }
        temp->next = head;
        last->next = temp;
        head = temp; // New head is now the new node
    }

    return head;
}

cl* addInLast(cl* head) {
    cl* temp = (cl*)malloc(sizeof(cl));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    int x;
    printf("Enter data: ");
    scanf("%d", &x);
    temp->data = x;

    if (head == NULL) {
        temp->next = temp; // Points to itself, making it circular
        head = temp;
    } else {
        cl* last = head;
        while (last->next != head) {
            last = last->next;
        }
        last->next = temp;
        temp->next = head;
    }

    return head;
}

cl* addInBetween(cl* head) {
    int x, pos, i = 1;
    printf("Enter data: ");
    scanf("%d", &x);
    printf("Enter position after which to insert (1 for after head): ");
    scanf("%d", &pos);

    cl* temp = (cl*)malloc(sizeof(cl));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    temp->data = x;

    if (head == NULL) {
        temp->next = temp;
        head = temp;
        return head;
    }

    cl* current = head;
    while (i < pos && current->next != head) {
        current = current->next;
        i++;
    }

    temp->next = current->next;
    current->next = temp;

    return head;
}

cl* deleteFromFront(cl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    cl* temp = head;

    if (head->next == head) {
        // Only one node in the list
        head = NULL;
    } else {
        cl* last = head;
        while (last->next != head) {
            last = last->next;
        }
        head = head->next;
        last->next = head;
    }

    free(temp);
    printf("Node deleted from front.\n");

    return head;
}

cl* deleteFromEnd(cl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    cl* current = head;
    cl* prev = NULL;

    if (head->next == head) {
        // Only one node in the list
        head = NULL;
        free(current);
        printf("Node deleted from end.\n");
        return head;
    }

    while (current->next != head) {
        prev = current;
        current = current->next;
    }

    prev->next = head;
    free(current);
    printf("Node deleted from end.\n");

    return head;
}

cl* deleteFromAnywhere(cl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    int pos, i = 1;
    printf("Enter position to delete: ");
    scanf("%d", &pos);

    cl* current = head;
    cl* prev = NULL;

    if (pos == 1) {
        return deleteFromFront(head);
    }

    while (i < pos && current->next != head) {
        prev = current;
        current = current->next;
        i++;
    }

    if (i != pos) {
        printf("Position out of bounds.\n");
    } else {
        prev->next = current->next;
        free(current);
        printf("Node deleted from position %d.\n", pos);
    }

    return head;
}

void display(cl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    cl* current = head;
    printf("Circular Linked List: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

int isPalindrome(cl* head) {
    if (head == NULL) return 1; // An empty list is a palindrome

    cl *slow = head, *fast = head;
    cl *stack[100]; // Stack to store the first half of the list
    int top = -1;

    // Push first half of the list onto stack
    while (fast != head && fast->next != head) {
        stack[++top] = slow; // Store node
        slow = slow->next;
        fast = fast->next->next;
    }

    // For odd nodes, skip the middle node
    if (fast != head) {
        slow = slow->next;
    }

    // Compare second half with stack
    while (slow != head) {
        if (slow->data != stack[top--]->data) {
            return 0; // Not a palindrome
        }
        slow = slow->next;
    }

    return 1; // It's a palindrome
}

cl* reverse(cl* head) {
    if (head == NULL || head->next == head) {
        return head; // Empty list or single node
    }

    cl *prev = NULL, *current = head, *next = NULL;
    cl *last = head;

    // Find the last node
    while (last->next != head) {
        last = last->next;
    }

    // Reverse the list
    do {
        next = current->next; // Store next node
        current->next = prev; // Reverse current node's pointer
        prev = current; // Move prev to current
        current = next; // Move to next node
    } while (current != head);

    last->next = prev; // Update last node's next to new head
    head = prev; // New head is the last processed node

    return head;
}

void printAlternate(cl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    cl* current = head;
    int count = 0;

    printf("Alternate nodes: ");
    do {
        if (count % 2 == 0) {
            printf("%d ", current->data);
        }
        current = current->next;
        count++;
    } while (current != head);
    printf("\n");
}

// Additional Operations

cl* rotate(cl* head) {
    if (head == NULL || head->next == head) {
        return head; // Single element or empty list
    }

    cl* last = head;
    while (last->next != head) {
        last = last->next;
    }

    head = head->next;
    last->next = head;

    return head;
}

cl* findMiddle(cl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }

    cl* slow = head;
    cl* fast = head;

    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

cl* merge(cl* head1, cl* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    cl* last = head1;
    while (last->next != head1) {
        last = last->next;
    }
    
    last->next = head2;
    
    cl* temp = head2;
    while (temp->next != head2) {
        temp = temp->next;
    }

    temp->next = head1;
    return head1;
}

cl* split(cl* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }

    cl* slow = head;
    cl* fast = head;

    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    cl* secondHalf = slow->next;
    slow->next = head;

    // Find the last node of the second half
    cl* temp = secondHalf;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = secondHalf;

    return secondHalf;
}

int length(cl* head) {
    if (head == NULL) return 0;

    int len = 1;
    cl* current = head;

    while (current->next != head) {
        len++;
        current = current->next;
    }

    return len;
}

int detectLoop(cl* head) {
    if (head == NULL) return 0;

    cl* slow = head;
    cl* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1; // Loop detected
        }
    }

    return 0; // No loop detected
}

cl* toNormalList(cl* head) {
    if (head == NULL) {
        return NULL;
    }

    cl* current = head;
    cl* newHead = NULL;
    cl* newTail = NULL;

    do {
        cl* newNode = (cl*)malloc(sizeof(cl));
        newNode->data = current->data;
        newNode->next = NULL;

        if (newHead == NULL) {
            newHead = newNode;
            newTail = newNode;
        } else {
            newTail->next = newNode;
            newTail = newNode;
        }

        current = current->next;
    } while (current != head);

    return newHead;
}

int main() {
    cl* head = NULL;
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. To add in front\n");
        printf("2. To add at the back\n");
        printf("3. To add in between\n");
        printf("4. To delete from front\n");
        printf("5. To delete from end\n");
        printf("6. To delete from anywhere\n");
        printf("7. To reverse the list\n");
        printf("8. To split the list\n");
        printf("9. To merge two lists\n");
        printf("10. To find the length of the list\n");
        printf("11. To rotate the list\n");
        printf("12. To find the middle element\n");
        printf("13. To detect a loop in the list\n");
        printf("14. To convert to normal list\n");
        printf("15. To check if the list is palindrome or not\n");
        printf("16. To print alternate nodes\n");
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
            case 7:
                head = reverse(head);
                printf("The list has been reversed.\n");
                break;
            case 8:
                head = split(head);
                break;
            case 9:
                head = merge(head, head);
                break;
            case 10:
                printf("Length of the list: %d\n", length(head));
                break;
            case 11:
                head = rotate(head);
                break;
            case 12:
                cl* middle = findMiddle(head);
                if (middle != NULL) {
                    printf("Middle element: %d\n", middle->data);
                }
                break;
            case 13:
                if (detectLoop(head)) {
                    printf("Loop detected.\n");
                } else {
                    printf("No loop detected.\n");
                }
                break;
            case 14:
                cl* normalList = toNormalList(head);
                display(normalList);
                break;
            case 15:
                if (isPalindrome(head)) {
                    printf("The list is a palindrome.\n");
                } else {
                    printf("The list is not a palindrome.\n");
                }
                break;
            case 16:
                printAlternate(head);
                break;
            case 0:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (1); // Loop indefinitely until user chooses to exit

    return 0;
}
