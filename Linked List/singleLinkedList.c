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

// Function to detect loop in the linked list
int detectLoop(sl* head) {
    sl* slow = head;
    sl* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1; // Loop detected
        }
    }
    return 0; // No loop
}

// Function to remove loop in the linked list
void removeLoop(sl* head) {
    sl* slow = head;
    sl* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            break;
        }
    }

    if (slow == fast) {
        slow = head;
        while (slow != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        fast->next = NULL;
        printf("Loop removed.\n");
    }
}

// Function to find the Nth node from the end
sl* findNthFromEnd(sl* head, int n) {
    sl* first = head;
    sl* second = head;

    for (int i = 0; i < n; i++) {
        if (second == NULL) {
            printf("List is shorter than %d nodes.\n", n);
            return NULL;
        }
        second = second->next;
    }

    while (second != NULL) {
        first = first->next;
        second = second->next;
    }

    return first;
}

// Function to segregate even and odd nodes
sl* segregateEvenOdd(sl* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    sl* evenHead = NULL, *oddHead = NULL, *evenTail = NULL, *oddTail = NULL;
    sl* current = head;

    while (current != NULL) {
        if (current->data % 2 == 0) {
            if (evenHead == NULL) {
                evenHead = current;
                evenTail = evenHead;
            } else {
                evenTail->next = current;
                evenTail = evenTail->next;
            }
        } else {
            if (oddHead == NULL) {
                oddHead = current;
                oddTail = oddHead;
            } else {
                oddTail->next = current;
                oddTail = oddTail->next;
            }
        }
        current = current->next;
    }

    if (evenTail != NULL) {
        evenTail->next = oddHead;
    }
    if (oddTail != NULL) {
        oddTail->next = NULL;
    }

    return evenHead;
}

// Function to remove duplicates from the list
sl* removeDuplicates(sl* head) {
    sl* current = head;
    sl* prev = NULL;

    while (current != NULL) {
        if (prev != NULL && prev->data == current->data) {
            prev->next = current->next;
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}

// Function to concatenate two lists
sl* concatenateLists(sl* head1, sl* head2) {
    if (head1 == NULL) {
        return head2;
    }

    sl* current = head1;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = head2;
    return head1;
}

// Merge Sort to sort the linked list
sl* mergeSort(sl* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    sl* middle = head;
    sl* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        middle = middle->next;
        fast = fast->next->next;
    }

    sl* left = head;
    sl* right = middle->next;
    middle->next = NULL;

    left = mergeSort(left);
    right = mergeSort(right);

    return mergeLists(left, right);
}

// Merge two sorted lists
sl* mergeLists(sl* head1, sl* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    sl* mergedHead = NULL;
    if (head1->data <= head2->data) {
        mergedHead = head1;
        mergedHead->next = mergeLists(head1->next, head2);
    } else {
        mergedHead = head2;
        mergedHead->next = mergeLists(head1, head2->next);
    }
    return mergedHead;
}

int main() {
    sl* head = NULL;
    sl* secondList = NULL;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. To add in front\n");
        printf("2. To add at the back\n");
        printf("3. To add in between\n");
        printf("4. To delete from front\n");
        printf("5. To delete from end\n");
        printf("6. To delete from anywhere\n");
        printf("7. To find the length of the list\n");
        printf("8. To find the middle element\n");
        printf("9. To display\n");
        printf("10. To check if the list is palindrome or not\n");
        printf("11. To reverse the list\n");
        printf("12. To print alternate nodes\n");
        printf("13. To delete alternate nodes\n");
        printf("14. To merge two lists\n");
        printf("15. To detect and remove loops\n");
        printf("16. To find Nth node from end\n");
        printf("17. To segregate even and odd nodes\n");
        printf("18. To remove duplicates\n");
        printf("19. To concatenate two lists\n");
        printf("20. To sort the list using merge sort\n");
        printf("21. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: head = addInFront(head); break;
            case 2: head = addInLast(head); break;
            case 3: head = addInBetween(head); break;
            case 4: head = deleteFromFront(head); break;
            case 5: head = deleteFromEnd(head); break;
            case 6: head = deleteFromAnywhere(head); break;
            case 7: printf("Length of the list is: %d\n", getLength(head)); break;
            case 8: findMiddle(head); break;
            case 9: display(head); break;
            case 10: 
                if (isPalindrome(head)) {
                    printf("The list is a palindrome.\n");
                } else {
                    printf("The list is not a palindrome.\n");
                }
                break;
            case 11: head = reverse(head); break;
            case 12: printAlternate(head); break;
            case 13: deleteAlternate(head); break;
            case 14: 
                secondList = NULL;
                printf("Enter the second list:\n");
                secondList = addInFront(secondList);  // Simplified for now; can add more code to handle it.
                head = mergeLists(head, secondList); 
                break;
            case 15: 
                if (detectLoop(head)) {
                    printf("Loop detected.\n");
                    removeLoop(head);
                } else {
                    printf("No loop detected.\n");
                }
                break;
            case 16: {
                int n;
                printf("Enter N: ");
                scanf("%d", &n);
                sl* node = findNthFromEnd(head, n);
                if (node != NULL) {
                    printf("Nth node from end: %d\n", node->data);
                }
                break;
            }
            case 17: head = segregateEvenOdd(head); break;
            case 18: head = removeDuplicates(head); break;
            case 19: head = concatenateLists(head, secondList); break;
            case 20: head = mergeSort(head); break;
            case 21: return 0;
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
