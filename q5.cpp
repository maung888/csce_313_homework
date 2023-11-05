#include <iostream>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>

int main() {
    int fd;
    int count = 0;

    while (true) {
        fd = open("/dev/null", O_RDONLY);
        if (fd == -1) {
            if (errno == EMFILE) {
                std::cout << "Maximum number of open files reached: " << count << std::endl;
                break;
            } else {
                perror("Error opening file");
                return 1;
            }
        } else {
            count++;
        }
    }

    return 0;
}
