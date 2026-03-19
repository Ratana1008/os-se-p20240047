/* file_creator_sys.c */
#include <fcntl.h>    // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>   // write(), close()
#include <string.h>   // strlen()

int main() {
    // 1. Open/create "output.txt" using open()
    // O_WRONLY: Write-only mode
    // O_CREAT: Create the file if it doesn't exist
    // O_TRUNC: If it exists, truncate (wipe) it to 0 bytes
    // 0644: Standard file permissions
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        write(2, "Error opening file\n", 19);
        return 1;
    }

    // 2. Write content to the file using write()
    const char *text = "Hello from Operating Systems class!\n";
    write(fd, text, strlen(text));

    // 3. Close the file using close()
    close(fd);

    // 4. Print confirmation to the terminal (fd 1 = stdout)
    const char *msg = "File created successfully!\n";
    write(1, msg, strlen(msg));

    return 0;
}