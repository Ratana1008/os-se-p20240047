/* dir_list_sys.c */
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>    // Only used for snprintf()

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat fileStat;
    char buffer[512];
    int len;

    if (dir == NULL) {
        write(2, "Error opening directory\n", 24);
        return 1;
    }

    // We manually write the header text to stdout (fd 1)
    const char *header = "Filename                       Size (bytes)\n";
    const char *line   = "------------------------------ ----------\n";
    write(1, header, strlen(header));
    write(1, line, strlen(line));

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            // We format the string into a buffer first
            len = snprintf(buffer, sizeof(buffer), "%-30s %10ld\n", 
                           entry->d_name, fileStat.st_size);
            
            // Then we write the raw bytes of that buffer to the screen
            write(1, buffer, len);
        }
    }

    closedir(dir);
    return 0;
}