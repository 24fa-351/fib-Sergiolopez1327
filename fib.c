#include <stdio.h>
#include <stdlib.h>

unsigned long long fib_iterative(unsigned long long num) {
    if (num <= 2) {
        return num - 1;
    }

    unsigned long long previous_num = 0;
    unsigned long long current_num = 1;
    unsigned long long next_num;

    for (unsigned long long iter = 3; iter <= num; iter++) {
        next_num = previous_num + current_num;
        previous_num = current_num;
        current_num = next_num;
    }

    return current_num;
}

unsigned long long fib_recursive(unsigned long long num) {
    return (num <= 2) ? (num - 1) : (fib_recursive(num - 1) + fib_recursive(num - 2));
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <integer> <method> <filename>\n", argv[0]);
        return 1;
    }

    unsigned long long input_number = strtoull(argv[1], NULL, 10);
    char fib_method = argv[2][0];
    char *filename = argv[3];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    unsigned long long file_number;
    fscanf(file, "%llu", &file_number);
    fclose(file);

    unsigned long long N = input_number + file_number;
    unsigned long long fib_result;

    if (fib_method == 'i') {
        fib_result = fib_iterative(N);
    } else if (fib_method == 'r') {
        fib_result = fib_recursive(N);
    } else {
        fprintf(stderr, "Invalid method. Use 'i' for iterative or 'r' for recursive.\n");
        return 1;
    }

    printf("%llu\n", fib_result);
    return 0;
}