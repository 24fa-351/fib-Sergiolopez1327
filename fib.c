#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fibOverflow(int a, int b) {
    if (a > (INT_MAX - b)) {
        return 1;
    }
    return 0;
}

int fib_iterative(int fibIndex) {
    if (fibIndex <= 2) {
        return fibIndex - 1;
    }

    int previous = 0;
    int current = 1;

    for (int iter = 3; iter <= fibIndex; iter++) {
        int next;
        if (fibOverflow(previous, current)) {
            fprintf(stderr, "Overflow detected at index %d\n", iter + 2);
            return -1;
        }
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
    int firstfibvalue = fib_recursive(fibIndex - 1);
    int secondfibvalue = fib_recursive(fibIndex - 2);
    if (fibOverflow(firstfibvalue, secondfibvalue)) {
        fprintf(stderr, "Overflow detected at index %d\n", fibIndex);
        return -1;
    }

    return firstfibvalue + secondfibvalue;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input number> <fib method> <filename>\n",
                argv[0]);
        return 1;
    }

    int input_number = atoi(argv[1]);
    char fib_method = argv[2][0];
    char* filename = argv[3];

    FILE* file = fopen(filename, "r");
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
        fprintf(
            stderr,
            "Invalid method. Use 'i' for iterative or 'r' for recursive.\n");
        return 1;
    }

    printf("%d\n", fib_result);
    return 0;
}