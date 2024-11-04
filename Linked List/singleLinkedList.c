#include <stdio.h>
#include <stdlib.h>

typedef struct singleList {
    int data;
    struct singleList* next;
} sl;

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

void display(sl* head) {
    sl* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
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
            case 0:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
