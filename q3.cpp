#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd;
    pid_t pid;
    int pipefd[2];
    char buf[1024];
    ssize_t bytesRead;
    char sync_message;

    
    fd = open("testfle.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    
    if (pipe(pipefd) == -1) {
        perror("Failed to create pipe");
        close(fd);
        return 1;
    }

    
    pid = fork();
    if (pid == -1) {
        perror("Failed to fork");
        close(fd);
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }

    if (pid == 0) { 
        close(pipefd[1]); 

        
        read(pipefd[0], &sync_message, 1);
        close(pipefd[0]);

        
        bytesRead = read(fd, buf, sizeof(buf)-1);
        if (bytesRead > 0) {
            buf[bytesRead] = '\0';
            std::cout << "Reading the file by the child process: " << buf << std::endl;
        } else {
            perror("Child failed to read");
        }
        close(fd);
    } else { 
        close(pipefd[0]); 

       
        close(fd);
        unlink("testfile.txt");
        std::cout << "Verifying if file is available with ls:" << std::endl;
        system("ls -l testfile.txt"); 

       
        write(pipefd[1], "c", 1);
        close(pipefd[1]);

        wait(nullptr); 
    }

    return 0;
}
