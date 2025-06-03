#include <unistd.h> // For usleep() and write()

// No <stdio.h> is needed as we use write() for minimal output.

int main(int argc, char *argv[]) {
    // Check if any command-line argument (other than the program name) was passed.
    if (argc < 2) {
        // Print a very short error message to stderr (file descriptor 2).
        write(2, "Error: Missing argument.\n", 25); // A slightly more descriptive short message
        // Or, for an extremely short message:
        // write(2, "Arg?\n", 5);
        return 1; // Return an error code
    }

    int input = 0;
    // This loop converts the first command-line argument to an integer.
    // It assumes the argument is a valid non-negative integer.
    // No error checking for non-digit characters is present in the original logic.
    for (int i = 0; argv[1][i] != '\0'; i++) {
        // Check if the character is a digit before converting
        if (argv[1][i] >= '0' && argv[1][i] <= '9') {
            input = input * 10 + (argv[1][i] - '0');
        } else {
            // If a non-digit is found, print an error and exit.
            write(2, "Error: Argument must be a number.\n", 34);
            return 1; // Return an error code
        }
    }

    // Sleep for 'input' multiplied by 500,000 microseconds (0.5 seconds).
    usleep(input * 500000);

    return 0; // Successful execution
}