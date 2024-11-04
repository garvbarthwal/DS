#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int deque[MAX];
int front = -1;
int rear = -1;

void insertFront(int);
void insertRear(int);
void deleteFront();
void deleteRear();
void display();

int main() {
    int choice, value;
    do {
        printf("\n\nDoubly Ended Queue Operations:\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Delete from Front\n");
        printf("4. Delete from Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to be inserted at front: ");
                scanf("%d", &value);
                insertFront(value);
                break;
            case 2:
                printf("Enter the value to be inserted at rear: ");
                scanf("%d", &value);
                insertRear(value);
                break;
            case 3:
                deleteFront();
                break;
            case 4:
                deleteRear();
                break;
            case 5:
                display();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void insertFront(int value) {
    if ((front == 0 && rear == MAX - 1) || (front == rear + 1)) {
        printf("Deque is full!\n");
        return;
    }
    if (front == -1) {
        front = rear = 0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front--;
    }
    deque[front] = value;
    printf("Inserted %d at front\n", value);
}

void insertRear(int value) {
    if ((front == 0 && rear == MAX - 1) || (front == rear + 1)) {
        printf("Deque is full!\n");
        return;
    }
    if (rear == -1) {
        front = rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear++;
    }
    deque[rear] = value;
    printf("Inserted %d at rear\n", value);
}

void deleteFront() {
    if (front == -1) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deleted %d from front\n", deque[front]);
    if (front == rear) {
        front = rear = -1;
    } else if (front == MAX - 1) {
        front = 0;
    } else {
        front++;
    }
}

void deleteRear() {
    if (rear == -1) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deleted %d from rear\n", deque[rear]);
    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = MAX - 1;
    } else {
        rear--;
    }
}

void display() {
    if (front == -1) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque elements are:\n");
    int i = front;
    if (front <= rear) {
        while (i <= rear)
            printf("%d ", deque[i++]);
    } else {
        while (i <= MAX - 1)
            printf("%d ", deque[i++]);
        i = 0;
        while (i <= rear)
            printf("%d ", deque[i++]);
    }
    printf("\n");
}