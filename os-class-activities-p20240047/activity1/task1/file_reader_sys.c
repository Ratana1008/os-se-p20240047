
#include <fcntl.h>    // For open() and O_RDONLY
#include <unistd.h>   // For read(), write(), close()

int main() {
    char buffer[1024]; // Our "bucket" to hold the text
    int fd;
    ssize_t bytesRead;

    // 1. Open "output.txt" for reading only
    fd = open("output.txt", O_RDONLY);
    
    // Check if the file exists/opened correctly
    if (fd < 0) {
        write(2, "Error: Could not open output.txt\n", 33);
        return 1;
    }

    // 2. Read the content into our buffer
    // read() returns the number of bytes it actually found
    bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead > 0) {
        // 3. Print the content to the terminal (fd 1 = stdout)
        write(1, "File content: ", 14);
        write(1, buffer, bytesRead);
    }

    // 4. Close the file
    close(fd);

    return 0;
}