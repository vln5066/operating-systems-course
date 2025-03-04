#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int variable =42;
int main() {

    printf("Before fork:\n");
    printf("Address of variable: %p, Value: %d\n", (void*)&variable, variable);

    pid_t pid = fork();  // Fork the process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process (before modification):\n");
        printf("Address of variable: %p, Value: %d\n", (void*)&variable, variable);
        
        variable = 99;  // Modify the variable in the child process

        printf("Child process (after modification):\n");
        printf("Address of variable: %p, Value: %d\n", (void*)&variable, variable);
    } else {
        // Parent process
        wait(NULL);  // Wait for child to finish
        printf("Parent process (after child modified its variable):\n");
        printf("Address of variable: %p, Value: %d\n", (void*)&variable, variable);
    }

    return 0;
}

