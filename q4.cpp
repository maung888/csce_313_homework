#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    std::string filepath;
    struct stat fileStat;

    std::cout << "Enter the file path: ";
    std::cin >> filepath;

    if (lstat(filepath.c_str(), &fileStat) < 0) {
        perror("Error while getting file stats");
        return 1;
    }

    // Check file type
    if (S_ISREG(fileStat.st_mode))
        std::cout << "File Type: Regular File\n";
    else if (S_ISDIR(fileStat.st_mode))
        std::cout << "File Type: Directory\n";
    else if (S_ISLNK(fileStat.st_mode))
        std::cout << "File Type: Symbolic Link\n";
    else if (S_ISFIFO(fileStat.st_mode))
        std::cout << "File Type: Pipe\n";
    // ... you can add checks for other types like sockets, character devices, etc.

    // Check owner's permissions
    std::cout << "Owner Permissions: ";
    std::cout << ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    std::cout << ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    std::cout << ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    std::cout << std::endl;

    return 0;
}
