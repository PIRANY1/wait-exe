#include <unistd.h> // For usleep() and write()

// Define file descriptors for standard output (1) and standard error (2)
#define STDOUT 1
#define STDERR 2

// A small helper function to get the length of a string,
// avoiding the C standard library.
int str_len(const char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

// A small helper function to print error messages and usage.
void print_usage_and_exit() {
    char *usage = "Usage: wait [-s] <value>[ms|s|m|h]\n\n"
                  "  -s        Silent mode (no progress dots)\n"
                  "  <value>   A non-negative integer\n"
                  "  ms        Milliseconds\n"
                  "  s         Seconds (default)\n"
                  "  m         Minutes\n"
                  "  h         Hours\n\n"
                  "Example: wait 10s\n";
    write(STDERR, usage, str_len(usage));
    // Using _exit() instead of return 1 to bypass exit handlers
    // and keep the compiled size minimal.
    _exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage_and_exit();
    }

    int is_silent = 0;
    char *time_arg = NULL;
    
    // Parse arguments: look for the optional '-s' flag.
    if (argv[1][0] == '-' && argv[1][1] == 's' && argv[1][2] == '\0') {
        is_silent = 1;
        if (argc < 3) {
            print_usage_and_exit();
        }
        time_arg = argv[2];
    } else {
        time_arg = argv[1];
    }

    long long value = 0;
    int len = 0;
    char unit_char1 = 's'; // Default unit is seconds
    char unit_char2 = '\0';

    // Convert the argument string to a number and extract the unit.
    for (int i = 0; time_arg[i] != '\0'; i++) {
        if (time_arg[i] >= '0' && time_arg[i] <= '9') {
            value = value * 10 + (time_arg[i] - '0');
        } else {
            // The first non-digit character is the start of the unit.
            unit_char1 = time_arg[i];
            if (time_arg[i+1] != '\0') { // for 'ms'
               unit_char2 = time_arg[i+1];
            }
            break; // Stop parsing the number
        }
        len++;
    }

    if (len == 0 && value == 0) { // No number found
        print_usage_and_exit();
    }

    // Convert the value to microseconds based on the unit.
    // long long is used to prevent overflows with large values (hours).
    long long wait_micros = 0;
    if (unit_char1 == 'm' && unit_char2 == 's') { // Milliseconds
        wait_micros = value * 1000;
    } else if (unit_char1 == 'm') { // Minutes
        wait_micros = value * 60 * 1000000;
    } else if (unit_char1 == 'h') { // Hours
        wait_micros = value * 3600 * 1000000;
    } else { // Seconds (default)
        wait_micros = value * 1000000;
    }
    
    if (is_silent || wait_micros < 1000000) {
        // In silent mode or for waits less than one second, sleep for the entire duration at once.
        usleep(wait_micros);
    } else {
        // For longer waits, display a progress indicator.
        long long seconds_to_wait = wait_micros / 1000000;
        for (long long i = 0; i < seconds_to_wait; i++) {
            usleep(1000000); // Wait one second
            write(STDOUT, ".", 1); // Print a dot
        }
        // A newline at the end for clean output.
        write(STDOUT, "\n", 1);
    }

    return 0; // Successful execution
}