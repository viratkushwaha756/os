#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

void cp(const char *source, const char *destination) { 
    FILE *src = fopen(source, "rb"); 
    if (src == NULL) { 
        perror("Source file opening failed"); 
        exit(1); 
    } 

    FILE *dst = fopen(destination, "wb"); 
    if (dst == NULL) { 
        perror("Destination file opening failed"); 
        fclose(src); 
        exit(1); 
    } 

    char buffer[1024]; 
    size_t bytes; 
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) { 
        if (fwrite(buffer, 1, bytes, dst) != bytes) { 
            perror("Write failed"); 
            fclose(src); 
            fclose(dst); 
            exit(1); 
        } 
    } 

    fclose(src); 
    fclose(dst); 
    printf("File copied successfully from %s to %s\n", source, destination); 
} 

void grep(const char *pattern, const char *filename) { 
    FILE *file = fopen(filename, "r"); 
    if (file == NULL) { 
        perror("File opening failed"); 
        exit(1); 
    } 

    char line[1024]; 
    int line_number = 1; 
    int found = 0; 

    while (fgets(line, sizeof(line), file)) { 
        if (strstr(line, pattern)) { 
            printf("Line %d: %s", line_number, line); 
            found = 1; 
        } 
        line_number++; 
    } 

    if (!found) { 
        printf("Pattern not found in %s\n", filename); 
    } 

    fclose(file); 
} 

int main(int argc, char *argv[]) { 
    int choice; 

    printf("Select an operation:\n"); 
    printf("1. File Copy (cp)\n"); 
    printf("2. String Search in File (grep)\n"); 
    printf("Enter your choice (1 or 2): "); 
    scanf("%d", &choice); 

    if (choice == 1) { 
        char source[256], destination[256]; 
        printf("Enter source file name: "); 
        scanf("%255s", source); 
        printf("Enter destination file name: "); 
        scanf("%255s", destination); 
        cp(source, destination); 
    } else if (choice == 2) { 
        char pattern[256], filename[256]; 
        printf("Enter pattern to search: "); 
        scanf("%255s", pattern); 
        printf("Enter file name to search in: "); 
        scanf("%255s", filename); 
        grep(pattern, filename); 
    } else { 
        printf("Invalid choice. Please enter 1 or 2.\n"); 
    } 
    return 0; 
}
