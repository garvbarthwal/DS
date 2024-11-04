#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int priorityQueue[MAX];
int size = 0;

void insert(int data) {
    if (size == MAX) {
        printf("Queue overflow\n");
        return;
    }
    int i = size - 1;
    while (i >= 0 && priorityQueue[i] > data) {
        priorityQueue[i + 1] = priorityQueue[i];
        i--;
    }
    priorityQueue[i + 1] = data;
    size++;
}

void delete() {
    if (size == 0) {
        printf("Queue underflow\n");
        return;
    }
    printf("Deleted element: %d\n", priorityQueue[0]);
    for (int i = 1; i < size; i++) {
        priorityQueue[i - 1] = priorityQueue[i];
    }
    size--;
}

void display() {
    if (size == 0) {
        printf("Queue is empty\n");
        return;
    }
    printf("Priority Queue: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", priorityQueue[i]);
    }
    printf("\n");
}

int main() {
    int choice, data;
    do {
        printf("\nPriority Queue Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insert(data);
                break;
            case 2:
                delete();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 4);
    return 0;
}