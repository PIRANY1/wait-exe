#include <unistd.h>

int main(int argc, char *argv[]) {
    int input = 0;
    for (int i = 0; argv[1][i] != '\0'; i++) {
        input = input * 10 + (argv[1][i] - '0');
    }

    usleep(input * 500000);
    return 0;
}
