#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fib_iterative(int fibIndex) {
    if (fibIndex <= 2) {
        return fibIndex - 1;
    }

    int previous = 0;
    int current = 1;

    for (int iter = 3; iter <= fibIndex; iter++) {
        int next;
        next = previous + current;
        previous = current;
        current = next;
    }

    return current;
}

int fib_recursive(int fibIndex) {
    if (fibIndex <= 2) {
        return fibIndex - 1;
    }

    return fib_recursive(fibIndex - 1) + fib_recursive(fibIndex - 2);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input number> <fib method> <filename>\n", argv[0]);
        return 1;
    }

    int input_number = atoi(argv[1]);
    char fib_method = argv[2][0];
    char *filename = argv[3];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    int file_number;
    fscanf(file, "%d", &file_number);
    fclose(file);

    int N = input_number + file_number;
    int fib_result;

    if (fib_method == 'i') {
        fib_result = fib_iterative(N);
    } else if (fib_method == 'r') {
        fib_result = fib_recursive(N);
    } else {
        fprintf(stderr, "Invalid method. Use 'i' for iterative or 'r' for recursive.\n");
        return 1;
    }

    printf("%d\n", fib_result);
    return 0;
}