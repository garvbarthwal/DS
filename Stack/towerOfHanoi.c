#include <stdio.h>

void moveDisk(int n, char source, char target, char auxiliary) {
    if (n == 1) {
        printf("Move disk 1 from rod %c to rod %c\n", source, target);
        return;
    }
    moveDisk(n - 1, source, auxiliary, target); // Move top n-1 disks from source to auxiliary
    printf("Move disk %d from rod %c to rod %c\n", n, source, target); // Move nth disk to target
    moveDisk(n - 1, auxiliary, target, source); // Move n-1 disks from auxiliary to target
}

int main() {
    int n; // Number of disks
    printf("Enter the number of disks: "); // Prompt the user for input
    scanf("%d", &n); // Read the number of disks from the user
    
    printf("The sequence of moves involved in the Tower of Hanoi are:\n");
    moveDisk(n, 'A', 'C', 'B'); // A, B and C are names of rods
    return 0;
}
