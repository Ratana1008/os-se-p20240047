#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[256];
    // YOUR CODE HERE
    // 1. Open "output.txt" for reading using open()
    // 2. Read content into buffer using read() in a loop
    // 3. Write the content to the terminal (fd 1) using write()
    // 4. Close the file using close()
    return 0;
}