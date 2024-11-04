#include<stdio.h>
#include<stdlib.h>

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
    } while (choice != 0);

    return 0;
}
