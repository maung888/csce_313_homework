#include <iostream>
#include <unistd.h>    
#include <fcntl.h>     


extern "C" int openr(const char *pathname);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file-path>\n";
        return 1;
    }

    int fd = openr(argv[1]);

    if (fd < 0) {
        perror("openr failed");
        return 1;
    }

    const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    close(fd);

    return 0;
}
