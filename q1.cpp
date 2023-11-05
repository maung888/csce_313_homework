#include <iostream>
#include <unistd.h>

// Prototype of our assembly function
extern "C" int openr(const char *pathname);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <pathname>\n";
        return 1;
    }

    int fd = openr(argv[1]);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(fd);
    return 0;
}
