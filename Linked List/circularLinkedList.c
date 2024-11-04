#include<stdio.h>
#include<stdlib.h>

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
    } while (choice < 10);

    return 0;
}
